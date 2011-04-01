#include "videoudppullthread.h"
#include <QRegExp>
#include <QHostAddress>

VideoUdpPullThread::VideoUdpPullThread(QObject *parent, VideoManager *videoManager, QHostAddress clientAddress,
                                       quint16 clientPort) :
    VideoUdpThread(parent), clientAddress(clientAddress), clientPort(clientPort),
    videoManager(videoManager), currentNumImage(0), fragmentSize(0), hostConnected(false)
{
}

void VideoUdpPullThread::run()
{
    emit log(QString("Démarrage d'un thread de traitement de requête pour ")
             + clientAddress.toString()
             + ":" + QString::number(clientPort) + ".", VodIF::Debug);

    exec();

    emit log("Fin du thread, nettoyage...", VodIF::Debug);
}

void VideoUdpPullThread::requestReceived(QByteArray &requestData)
{
    request += requestData;

    // Empêche une saturation mémoire
    if(request.size() > 1000)
    {
        emit log("Saturation de requête par un client de serveur vidéo UDP-Pull. "
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
                emit log("Requête de démarrage incomprise reçue sur un serveur UDP Pull.", VodIF::Warning);
                disconnectNow = true;
            }

            if(!disconnectNow && parser.cap(1).toInt() != videoManager->objectId())
            {
                emit log("Mauvaise vidéo demandée sur un serveur UDP Pull.", VodIF::Warning);
                disconnectNow = true;
            }

            if(!disconnectNow && parser.cap(2).toInt() < 1)
            {
                emit log("Impossible de parser le port d'une requête d'un client sur un serveur UDP Pull.", VodIF::Warning);
                disconnectNow = true;
            }

            if(!disconnectNow && parser.cap(3).toInt() < 1)
            {
                emit log("Impossible de parser la taille de fragment d'une requête d'un client sur un serveur UDP Pull.", VodIF::Warning);
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

            emit log("En attente d'une requête du client... (UdpPull)", VodIF::Debug);

            hostConnected = true;
        }
        else // Ah, c'est bon, on est connecté \o/
        {
            QRegExp parseGet("GET (-?\\d*)\\s*" CRLF CRLF);
            QRegExp parseEnd("END\\s*" CRLF CRLF);

            if(parseGet.exactMatch(request))
            {
                int nbImage = parseGet.cap(1).toInt();
                int posCurPack = 0;

                if(nbImage < 0)
                {
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

                    if(tailleEnvoyee != paquet.size()) // TODO: Relancer le paquet ?
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
            else if(parseEnd.exactMatch(request))
            {
                emit log("Fin de \"connection\" (UDP-Pull) pour le client " + clientAddress.toString() + ":" + QString::number(clientPort) + ".",
                         VodIF::Debug);

                exit();
                return;
            }
            else
            {
                emit log("Requête incomprise reçue par un client de serveur vidéo UDP-Pull ; requête ignorée.", VodIF::Warning);
            }
        }

        request = "";
    }
}

void VideoUdpPullThread::stop()
{
    emit log("Arrêt immédiat du thread dédié au client UDP-Pull " + clientAddress.toString() + ":" + QString::number(clientPort) + ".",
             VodIF::Debug);

    exit();
}

QHostAddress VideoUdpPullThread::getClientAddress()
{
    return clientAddress;
}

quint16 VideoUdpPullThread::getClientPort()
{
    return clientPort;
}
