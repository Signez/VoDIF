#include "videoudppushthread.h"
#include <QRegExp>
#include <QHostAddress>

VideoUdpPushThread::VideoUdpPushThread(QObject *parent, VideoManager *videoManager, QHostAddress clientAddress,
                                       quint16 clientPort) :
    VideoUdpThread(parent), clientAddress(clientAddress), clientPort(clientPort),
    videoManager(videoManager), currentNumImage(0), fragmentSize(0), hostConnected(false)
{
}

void VideoUdpPushThread::run()
{
    emit log(QString("Démarrage d'un thread de traitement de requête pour ")
             + clientAddress.toString()
             + ":" + QString::number(clientPort) + ".", VodIF::Debug);

    exec();

    emit log("Fin du thread, nettoyage...", VodIF::Debug);
}

void VideoUdpPushThread::requestReceived(QByteArray &requestData)
{
    request += requestData;

    // Empêche une saturation mémoire
    if(request.size() > 1000)
    {
        emit log("Saturation de requête par un client de serveur vidéo UDP-Push. "
                 "(N'oubliez pas le CRLF CRLF en fin de requête !)", VodIF::Warning);
        request = "";
        return;
    }

    if(request.endsWith(CRLF CRLF))
    {
        emit log(request, VodIF::Received);

        if(!hostConnected)
        {
            bool disconnectNow = false;

            QRegExp parser("GET (\\d*)\\s*LISTEN_PORT (\\d*)\\s*FRAGMENT_SIZE (\\d*)\\s*" CRLF CRLF);

            if(!parser.exactMatch(request))
            {
                emit log("Requête de démarrage incomprise reçue sur un serveur UDP Push.", VodIF::Warning);
                disconnectNow = true;
            }

            if(!disconnectNow && parser.cap(1).toInt() != videoManager->objectId())
            {
                emit log("Mauvaise vidéo demandée sur un serveur UDP Push.", VodIF::Warning);
                disconnectNow = true;
            }

            if(!disconnectNow && parser.cap(2).toInt() < 1)
            {
                emit log("Impossible de parser le port d'une requête d'un client sur un serveur UDP Push.", VodIF::Warning);
                disconnectNow = true;
            }

            if(!disconnectNow && parser.cap(3).toInt() < 1)
            {
                emit log("Impossible de parser la taille de fragment d'une requête d'un client sur un serveur UDP Push.", VodIF::Warning);
                disconnectNow = true;
            }

            if(disconnectNow)
            {
                exit();
                return;
            }

            dataPort = parser.cap(2).toInt();
            emit log(QString("Enregistrement de l'IP:port du client auxquelles les données seront envoyées (")
                                + clientAddress.toString()
                                + ":" + QString::number(clientPort) + ")...", VodIF::Debug);

            fragmentSize = parser.cap(3).toInt();

            emit log("En attente d'une requête du client... (UdpPush)", VodIF::Debug);

            connect(&timerImages, SIGNAL(timeout()), this, SLOT(sendImage()), Qt::DirectConnection);
            timerImages.start(videoManager->getDelayMs());

            connect(&timerAlive, SIGNAL(timeout()), this, SLOT(aliveTimeout()), Qt::DirectConnection);
            timerAlive.start(60 * 1000); // TODO: Make this a constant

            hostConnected = true;
        }
        else // Ah, c'est bon, on est connecté \o/
        {
            QRegExp parseCmd("([A-Z]*)\\s*" CRLF CRLF);
            QRegExp parseAlive("ALIVE (\\d*)\\s*(?:LISTEN_PORT (\\d*))?\\s*" CRLF CRLF);

            if(parseCmd.exactMatch(request))
            {
                QString commande = parseCmd.cap(1);

                if(commande == "START")
                {
                    isPlaying = true;
                }
                else if(commande == "PAUSE")
                {
                    isPlaying = false;
                }
                else if(commande == "END")
                {
                    emit log("Arrêt immédiat du thread dédié au client UDP-Pull " + clientAddress.toString() + ":" + QString::number(clientPort) + ".",
                             VodIF::Debug);

                    exit();
                }
            }
            else if(parseAlive.exactMatch(request))
            {
                timerAlive.start(); // Ceci redémarre le timer.
            }
            else
            {
                emit log("Requête incomprise reçue par un client de serveur vidéo UDP-Push ; requête ignorée.", VodIF::Warning);
            }
        }

        request = "";
    }
}

void VideoUdpPushThread::stop()
{
    emit log(QString("Arrêt immédiat du thread dédié au client UDP-Push ") + clientAddress.toString() + ":" + QString::number(clientPort) + ".",
             VodIF::Debug);

    exit();
}

void VideoUdpPushThread::aliveTimeout()
{
    timerAlive.stop();
    emit log("Timeout (pas d'Alive à temps) du client " + clientAddress.toString() + ":" + QString::number(clientPort) + ".",
             VodIF::Warning);

    exit();
}

QHostAddress VideoUdpPushThread::getClientAddress()
{
    return clientAddress;
}

quint16 VideoUdpPushThread::getClientPort()
{
    return clientPort;
}

void VideoUdpPushThread::sendImage()
{
    if(isPlaying){
        int posCurPack = 0;
        int nbImage = 0;

        if(currentNumImage + 1 > videoManager->size())
        {
            nbImage = 0;
            currentNumImage = qMin(videoManager->size() - 1, 1);
        }
        else
        {
            nbImage = currentNumImage;
            currentNumImage++;
        }

        if(nbImage >= videoManager->size() - 1)
            nbImage = 0;

        int totalSize = videoManager->getImage(nbImage)->size();

        while(posCurPack < totalSize)
        {
            QByteArray paquet;
            QTextStream fluxPaquet(&paquet);
            int curFragmentSize;

            paquet.clear();

            // TODO: Refactorize this crap and implement strict mode

            fluxPaquet << nbImage << CRLF
                       << totalSize << CRLF
                       << posCurPack << CRLF << flush;

            curFragmentSize = fragmentSize - (QString::number(fragmentSize).size() + paquet.size() + 2);
            curFragmentSize = qMin(curFragmentSize, totalSize - posCurPack);

            fluxPaquet << curFragmentSize << CRLF << flush;

            paquet.append(videoManager->getImage(nbImage)->mid(posCurPack, curFragmentSize));

            int tailleEnvoyee = dataSocket.writeDatagram(paquet, clientAddress, dataPort);

            if(tailleEnvoyee == -1 && dataSocket.error() == QAbstractSocket::DatagramTooLargeError)
            {
               emit log(QString("Paquet non envoyé, pour le client ") + clientAddress.toString()
                                + ":" + QString::number(clientPort) + " ; taille de paquet"
                                "trop importante.", VodIF::Warning);
               continue;
            }

            if(tailleEnvoyee != paquet.size())
            {
                emit log(QString("Paquet envoyé partiellement, à l'adresse ") + clientAddress.toString()
                         + ":" + QString::number(clientPort) + ".", VodIF::Warning);
            }

            posCurPack += curFragmentSize;
        }

        emit log(QString("Image n°") + QString::number(nbImage) + " de la vidéo " + videoManager->name()
             + " (#" + QString::number(videoManager->objectId()) + ") complètement envoyée, pour le "
             + " client " + clientAddress.toString()
             + ":" + QString::number(clientPort) + ".", VodIF::Sent);
    }
}
