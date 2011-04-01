#ifndef VIDEOUDPPUSHTHREAD_H
#define VIDEOUDPPUSHTHREAD_H

#include <QThread>
#include "videomanager.h"
#include "videoudpthread.h"
#include <QUdpSocket>
#include <QTimer>

class VideoUdpPushThread : public VideoUdpThread
{
    Q_OBJECT

public:
    VideoUdpPushThread(QObject *parent, VideoManager * videoManager, QHostAddress clientAddress,
                       quint16 clientPort);
    QHostAddress getClientAddress();
    quint16 getClientPort();

protected:
    void run();
    bool traiteRequete();

    QHostAddress clientAddress;
    quint16 clientPort;
    VideoManager * videoManager;
    QUdpSocket dataSocket;
    int dataPort;
    int currentNumImage;
    int fragmentSize;

    int hostConnected;
    bool isPlaying;

    QString request;

    QTimer timerImages;
    QTimer timerAlive;

signals:
    void log(QString message, VodIF::DebugLevel level = VodIF::Log);
    void timeout();

public slots:
    void requestReceived(QByteArray & requestData);
    void stop();
    void sendImage();
    void aliveTimeout();
};

#endif // VIDEOUDPPUSHTHREAD_H
