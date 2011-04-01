#include "videotcppushthread.h"
#include <QRegExp>
#include <QHostAddress>
#include <QTimer>

VideoTcpPushThread::VideoTcpPushThread(QObject *parent, VideoManager *videoManager, int socketHandle) :
    QThread(parent), socketHandle(socketHandle), videoManager(videoManager), currentNumImage(0)
{
}

void VideoTcpPushThread::run()
{
    bool success;
    QString request;
    socket = new QTcpSocket();
    socket->setSocketDescriptor(socketHandle);

    dataSocket = new QTcpSocket();

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
            socket->deleteLater();
            return;
        }

        socket->flush();

        isPlaying = false;

        emit log("Démarrage du timer de la vidéo " + videoManager->name()
                 + " (#" + QString::number(videoManager->objectId()) + ") "
                 + "pour le client " + dataSocket->peerAddress().toString()
                 + ":" + QString::number(dataSocket->peerPort())  + ".", VodIF::Debug);

        QTimer * timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(envoieImage()), Qt::DirectConnection);
        timer->start(videoManager->getDelayMs());

        connect(socket, SIGNAL(readyRead()), this, SLOT(traiteRequete()), Qt::DirectConnection);

        isPlaying = true;

        exec();

        timer->deleteLater();
    }

    emit log("Fin du thread pour l'envoi d'une vidéo, nettoyage...", VodIF::Debug);

    dataSocket->flush();
    dataSocket->deleteLater();

    socket->flush();
    socket->deleteLater();
}

void VideoTcpPushThread::envoieImage()
{
    if(isPlaying)
    {
        QByteArray entetesData;
        QTextStream entetes(&entetesData);

        entetes << currentNumImage << CRLF
                << videoManager->getImage(currentNumImage)->size() << CRLF << flush;

        emit log(QString(entetesData), VodIF::Sent);

        dataSocket->write(entetesData);
        dataSocket->write(*(videoManager->getImage(currentNumImage)));

        emit log(QString("Image n°") + QString::number(currentNumImage) + " de la vidéo " + videoManager->name()
                 + " (#" + QString::number(videoManager->objectId()) + ") envoyée, pour le client "
                 + dataSocket->peerAddress().toString()
                 + ":" + QString::number(dataSocket->peerPort())  + ".", VodIF::Sent);

        currentNumImage++;

        if(currentNumImage >= videoManager->size())
        {
            currentNumImage = 0;
        }
    }
}

void VideoTcpPushThread::traiteRequete()
{
    QRegExp parseRequest("(\\w*)\\s*" CRLF CRLF);

    while(socket->bytesAvailable() && !currentRequest.endsWith(CRLF CRLF)){
        currentRequest += socket->read(1);
    }

    if(currentRequest.endsWith(CRLF CRLF))
    {
        if(parseRequest.exactMatch(currentRequest))
        {
            QString action = parseRequest.cap(1);

            if(action == "START")
            {
                isPlaying = true;
            }
            else if (action == "PAUSE")
            {
                isPlaying = false;
            }
            else if (action == "END")
            {
                emit log("Fin de connection pour le client " + dataSocket->peerAddress().toString() + ".", VodIF::Debug);
                exit();
            }
        }

        currentRequest = "";
    }
}
