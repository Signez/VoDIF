#include "videotcppullthread.h"
#include <QRegExp>
#include <QHostAddress>

VideoTcpPullThread::VideoTcpPullThread(QObject *parent, VideoManager *videoManager, int socketHandle) :
    QThread(parent), socketHandle(socketHandle), videoManager(videoManager), currentNumImage(0)
{
}

void VideoTcpPullThread::run()
{
    bool success;
    QString request;
    socket = new QTcpSocket();
    socket->setSocketDescriptor(socketHandle);

    while((success = socket->waitForReadyRead())){
        while(socket->bytesAvailable() && !request.endsWith(CRLF CRLF)){
            request += socket->read(1);
        }

        if(request.endsWith(CRLF CRLF))
            break;

        // Empêche une saturation mémoire
        if(request.size() > 1000)
        {
            success = false;
            emit log("Saturation de requête par un client de serveur vidéo TCP-Pull ; fermeture immédiate. "
                     "(N'oubliez pas le CRLF CRLF en fin de requête !)", VodIF::Warning);
            break;
        }
    }

    // Timeout
    if(!success){
        emit log("Timeout ou erreur de connection avec un client de vidéo.", VodIF::Debug);
    }
    else
    {
        emit log(request, VodIF::Received);

        bool disconnectNow = false;

        QRegExp parser("GET (\\d*)\\s*LISTEN_PORT (\\d*)\\s*" CRLF CRLF);

        if(!parser.exactMatch(request))
        {
            socket->write("Wait... What ?");
            emit log("Requête incomprise reçue sur un serveur TCP Pull ; déconnecté.", VodIF::Warning);
            disconnectNow = true;
        }

        if(!disconnectNow && parser.cap(1).toInt() != videoManager->objectId())
        {
            socket->write("Ressource inconnue.");
            emit log("Mauvaise vidéo demandée sur un serveur TCP Pull ; déconnecté.", VodIF::Warning);
            disconnectNow = true;
        }

        if(!disconnectNow && parser.cap(2).toInt() < 1)
        {
            socket->write("Port non valide.");
            emit log("Impossible de parser le port d'une requête d'un client sur un serveur TCP Pull ; déconnecté.", VodIF::Warning);
            disconnectNow = true;
        }

        if(!disconnectNow)
        {
            dataSocket = new QTcpSocket();
            dataSocket->connectToHost(socket->peerAddress(), parser.cap(2).toInt());
            emit log(QString("Connection à un client (") + socket->peerAddress().toString()
                             + ":" + parser.cap(2)  + ")...", VodIF::Sent);
            if(!dataSocket->waitForConnected(5000))
            {
                disconnectNow = true;
                emit log(QString("Timeout ou erreur pour se connecter au client ") + socket->peerAddress().toString()
                         + ":" + parser.cap(2)  + ".", VodIF::Sent);
            }
        }

        if(disconnectNow)
        {
            socket->flush();
            socket->disconnectFromHost();
            if(socket->state() != QAbstractSocket::UnconnectedState)
                socket->waitForDisconnected();
            return;
        }

        socket->flush();

        emit log("En attente d'une requête du client... (TcpPull)", VodIF::Debug);

        while(traiteRequete())
        {
        }
    }

     emit log("Fin du thread, nettoyage...", VodIF::Debug);
     socket->deleteLater();
}

bool VideoTcpPullThread::traiteRequete()
{
    bool success;
    QString request;

    QRegExp parseGet("GET (-?\\d*)\\s*" CRLF CRLF);
    QRegExp parseEnd("END\\s*" CRLF CRLF);

    while((success = socket->waitForReadyRead())){
        while(socket->bytesAvailable() && !request.endsWith(CRLF CRLF)){
            request += socket->read(1);
        }

        if(request.endsWith(CRLF CRLF))
            break;

        // Empêche une saturation mémoire
        if(request.size() > 1000)
        {
            success = false;
            emit log("Saturation de requête par un client de serveur vidéo TCP-Pull ; fermeture immédiate. "
                     "(N'oubliez pas le CRLF CRLF en fin de requête !)", VodIF::Warning);
            request += "END" CRLF "" CRLF;
            break;
        }
    }

    emit log(request, VodIF::Received);

    if(!success)
        request = "END" CRLF "" CRLF;

    if(parseGet.exactMatch(request))
    {
        QByteArray envoiData;
        QTextStream envoiStream(&envoiData);
        int nbImage = parseGet.cap(1).toInt();

        if(nbImage < 0)
        {
            currentNumImage++;

            if(currentNumImage > videoManager->size())
                currentNumImage = 0;

            nbImage = currentNumImage;
        }

        if(nbImage >= videoManager->size() - 1)
            nbImage = 0;

        envoiStream << nbImage << CRLF
                    << videoManager->getImage(nbImage)->size() << CRLF << flush;
        dataSocket->write(envoiData);
        dataSocket->write(*(videoManager->getImage(nbImage)));
        dataSocket->flush();

        emit log(QString("Image n°") + QString::number(nbImage) + " de la vidéo " + videoManager->name()
                 + " (#" + QString::number(videoManager->objectId()) + ") envoyée, pour le client " + dataSocket->peerAddress().toString()
                 + ":" + QString::number(dataSocket->peerPort())  + ".", VodIF::Sent);
    }
    else if(parseEnd.exactMatch(request))
    {
        emit log("Fin de connection pour le client " + dataSocket->peerAddress().toString() + ".", VodIF::Debug);

        dataSocket->flush();
        dataSocket->disconnectFromHost();
        if(socket->state() != QAbstractSocket::UnconnectedState)
            socket->waitForDisconnected();

        socket->flush();
        socket->disconnectFromHost();
        if(socket->state() != QAbstractSocket::UnconnectedState)
            socket->waitForDisconnected();

        return false;
    }
    else
    {
        emit log("Requête incomprise reçue par un client de serveur vidéo TCP-Pull ; requête ignorée.", VodIF::Warning);
    }

    return true;
}
