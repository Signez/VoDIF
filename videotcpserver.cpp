#include "videotcpserver.h"
#include "videotcppullthread.h"
#include "videotcppushthread.h"

VideoTcpServer::VideoTcpServer(bool isPush, VideoManager * videoManager, int port, QObject *parent) :
    QTcpServer(parent), myIsPush(isPush), myPort(port), videoManager(videoManager)
{
}

void VideoTcpServer::incomingConnection(int handle)
{
    emit log("Connection de requête de vidéo effectuée par un client.", VodIF::Debug);

    if(myIsPush)
    {
        // TCP PUSH ===========================================================================

        // Création d'un nouveau thread pour traiter la requête
        VideoTcpPushThread * thread = new VideoTcpPushThread(this, videoManager, handle);

        // Relai des logs de la part du thread, en renvoyant un signal log de la part du serveur
        connect(thread, SIGNAL(log(QString,VodIF::DebugLevel)), this, SIGNAL(log(QString,VodIF::DebugLevel)));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

        // Démarrage du thread \o/
        thread->start();
    }
    else
    {
        // TCP PULL ===========================================================================

        // Création d'un nouveau thread pour traiter la requête
        VideoTcpPullThread * thread = new VideoTcpPullThread(this, videoManager, handle);

        // Relai des logs de la part du thread, en renvoyant un signal log de la part du serveur
        connect(thread, SIGNAL(log(QString,VodIF::DebugLevel)), this, SIGNAL(log(QString,VodIF::DebugLevel)));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

        // Démarrage du thread \o/
        thread->start();
    }


}

void VideoTcpServer::start()
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

void VideoTcpServer::stop()
{
    close();
    emit log(QString("Serveur de diffusion de la vidéo " + videoManager->name() + " (#" + QString::number(videoManager->objectId()) + ")"
                     " arrêté."), VodIF::Info);
    emit statusChanged(false);
}

