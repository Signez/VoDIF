#include "videoudpserver.h"
#include "videoudppullthread.h"
#include "videoudppushthread.h"

VideoUdpServer::VideoUdpServer(bool isPush, VideoManager * videoManager, int port, QObject *parent) :
    QObject(parent), myIsPush(isPush), myPort(port), videoManager(videoManager), listening(false)
{
    socket = new QUdpSocket();
}

void VideoUdpServer::start()
{
    if(isListening())
    {
        emit log(QString("Le serveur de diffusion de la vidéo ") + videoManager->name() + " (#" + QString::number(videoManager->objectId())
                        + ") est déjà lancé.", VodIF::Warning);
        return;
    }

    if(videoManager->size() == 0)
    {
        emit log(QString("La vidéo ") + videoManager->name() + " (#" + QString::number(videoManager->objectId()) + ")"
                 + " ne comprends pas d'image. Le serveur de diffusion de cette vidéo ne se lancera pas.", VodIF::Error);
        return;
    }

    if(!listen(QHostAddress::Any, myPort))
    {
        emit log(QString("Impossible d'écouter sur le port ") + QString::number(myPort) +
                 ". Le serveur de diffusion de la vidéo "
                 + videoManager->name() + " (#" + QString::number(videoManager->objectId()) + ") "
                 "n'est pas démarré.", VodIF::Error);
        return;
    };

    emit log(QString("Serveur de diffusion de la vidéo ") + videoManager->name() + " (#" + QString::number(videoManager->objectId()) + ") "
                     "lancé, accessible sur le port " + QString::number(myPort) + ".", VodIF::Info);
    emit statusChanged(true);
}

void VideoUdpServer::stop()
{
    close();
    emit log(QString("Serveur de diffusion de la vidéo ") + videoManager->name() + " (#" + QString::number(videoManager->objectId()) + ")"
                     " arrêté.", VodIF::Info);
    emit statusChanged(false);
}

bool VideoUdpServer::listen(QHostAddress adresse, quint16 port)
{
    addressListening = adresse;
    portListening = port;

    if(socket->bind(addressListening, portListening, QUdpSocket::ShareAddress))
    {
        connect(socket, SIGNAL(readyRead()), this, SLOT(somethingReceived()));
        listening = true;
    }
    else
    {
        listening = false;
    }

    return listening;
}

void VideoUdpServer::somethingReceived()
{
    QHostAddress clientAddress;
    quint16 clientPort;
    QByteArray datagramme;

    while(socket->hasPendingDatagrams())
    {
        datagramme.resize(socket->pendingDatagramSize());

        socket->readDatagram(datagramme.data(), datagramme.size(),
                             &clientAddress, &clientPort);

        incomingDatagram(datagramme, clientAddress, clientPort);
    }
}

void VideoUdpServer::incomingDatagram(QByteArray &content, QHostAddress &fromAddress, quint16 fromPort)
{
    QString reference = fromAddress.toString() + ":" + QString::number(fromPort);

    if(threads.contains(reference))
    {
        threads.value(reference)->requestReceived(content);
    }
    else
    {
        // TODO: Implémenter la version Push
        if(myIsPush){
            // Création d'un nouveau thread pour traiter la requête
            VideoUdpPushThread * thread = new VideoUdpPushThread(this, videoManager, fromAddress, fromPort);

            // Relai des logs de la part du thread, en renvoyant un signal log de la part du serveur
            connect(thread, SIGNAL(log(QString,VodIF::DebugLevel)), this, SIGNAL(log(QString,VodIF::DebugLevel)));
            connect(thread, SIGNAL(finished()), this, SLOT(removeFinished()));

            // Démarrage du thread \o/
            thread->start();

            thread->requestReceived(content);

            threads.insert(reference, thread);
        }
        else
        {
            // Création d'un nouveau thread pour traiter la requête
            VideoUdpPullThread * thread = new VideoUdpPullThread(this, videoManager, fromAddress, fromPort);

            // Relai des logs de la part du thread, en renvoyant un signal log de la part du serveur
            connect(thread, SIGNAL(log(QString,VodIF::DebugLevel)), this, SIGNAL(log(QString,VodIF::DebugLevel)));
            connect(thread, SIGNAL(finished()), this, SLOT(removeFinished()));

            // Démarrage du thread \o/
            thread->start();

            thread->requestReceived(content);

            threads.insert(reference, thread);
        }
    }
}


void VideoUdpServer::close()
{
    if(listening)
    {
        QHashIterator<QString, VideoUdpThread *> it(threads);
        while(it.hasNext()){
            it.next();
            if(it.value())
            {
                it.value()->stop();
                connect(it.value(), SIGNAL(finished()), it.value(), SLOT(deleteLater()));
                threads.remove(it.key());
            }
        }

        socket->deleteLater();
    }
    listening = false;
}

bool VideoUdpServer::isListening()
{
    return listening;
}

void VideoUdpServer::removeFinished()
{
    VideoUdpThread * thread = qobject_cast<VideoUdpThread *>(sender());
    QString reference = thread->getClientAddress().toString() + ":" + QString::number(thread->getClientPort());

    int nbDeleted = threads.remove(reference);

    emit log(QString::number(nbDeleted) + " threads déréférencés pour " + reference + ".", VodIF::Debug);

    thread->deleteLater();
}
