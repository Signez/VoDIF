#ifndef VIDEOTCPSERVER_H
#define VIDEOTCPSERVER_H

#include <QTcpServer>
#include "videomanager.h"
#include "vodifglobals.h"

class VideoTcpServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit VideoTcpServer(bool isPush, VideoManager * videoManager, int port, QObject *parent = 0);

protected:
    void incomingConnection(int handle);
    bool myIsPush;
    int myPort;
    VideoManager * videoManager;

signals:
    void log(QString message, VodIF::DebugLevel level = VodIF::Log);
    void statusChanged(bool);

public slots:
    void start();
    void stop();

};

#endif // VIDEOTCPSERVER_H
