#ifndef VIDEOUDPPULLTHREAD_H
#define VIDEOUDPPULLTHREAD_H

#include <QThread>
#include "videomanager.h"
#include "videoudpthread.h"
#include <QUdpSocket>

class VideoUdpPullThread : public VideoUdpThread
{
    Q_OBJECT

public:
    VideoUdpPullThread(QObject *parent, VideoManager * videoManager, QHostAddress clientAddress,
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

    QString request;

signals:
    void log(QString message, VodIF::DebugLevel level = VodIF::Log);
    void timeout();

public slots:
    void requestReceived(QByteArray & requestData);
    void stop();
};

#endif // VIDEOUDPPULLTHREAD_H
