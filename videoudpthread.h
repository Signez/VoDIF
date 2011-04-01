#ifndef VIDEOUDPTHREAD_H
#define VIDEOUDPTHREAD_H

#include <QThread>
#include <QHostAddress>

class VideoUdpThread : public QThread
{
    Q_OBJECT
public:
    explicit VideoUdpThread(QObject *parent = 0);
    virtual QHostAddress getClientAddress() = 0;
    virtual quint16 getClientPort() = 0;

protected:
    virtual void run() = 0;

signals:

public slots:
    virtual void requestReceived(QByteArray & requestData) = 0;
    virtual void stop() = 0;
};

#endif // VIDEOUDPTHREAD_H
