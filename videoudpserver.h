#ifndef VIDEOUDPSERVER_H
#define VIDEOUDPSERVER_H

#include <QObject>
#include "vodifglobals.h"
#include "videomanager.h"
#include "videoudpthread.h"
#include <QUdpSocket>
#include <QHash>

class VideoUdpServer : public QObject
{
    Q_OBJECT

public:
    explicit VideoUdpServer(bool isPush, VideoManager * videoManager, int port, QObject *parent) ;

protected:
    void incomingDatagram(QByteArray & content, QHostAddress & fromAddress, quint16 fromPort);
    bool myIsPush;
    int myPort;
    VideoManager * videoManager;

    QHash<QString, VideoUdpThread *> threads;

    // Equivalent de QTcpServer, à notre sauce pour UDP
    bool listen(QHostAddress adresse, quint16 port);
    bool isListening();
    void close();

    QUdpSocket * socket;
    bool listening;
    QHostAddress addressListening;
    int portListening;

signals:
    void log(QString message, VodIF::DebugLevel level = VodIF::Log);
    void statusChanged(bool);

public slots:
    void start();
    void stop();
    void somethingReceived();

    void removeFinished();
};

#endif // VIDEOUDPSERVER_H
