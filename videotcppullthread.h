#ifndef VIDEOTCPPULLTHREAD_H
#define VIDEOTCPPULLTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "videomanager.h"
#include "vodifglobals.h"

class VideoTcpPullThread : public QThread
{
    Q_OBJECT
public:
    VideoTcpPullThread(QObject *parent, VideoManager * videoManager, int socketHandle);
    void run();

protected:
    bool traiteRequete();

    int socketHandle;
    VideoManager * videoManager;
    QTcpSocket * socket;
    QTcpSocket * dataSocket;
    int currentNumImage;

signals:
    void log(QString message, VodIF::DebugLevel level = VodIF::Log);
    void timeout();

public slots:
};

#endif // VIDEOTCPPULLTHREAD_H
