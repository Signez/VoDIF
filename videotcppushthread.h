#ifndef VIDEOTCPPUSHTHREAD_H
#define VIDEOTCPPUSHTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "videomanager.h"
#include "vodifglobals.h"

class VideoTcpPushThread : public QThread
{
    Q_OBJECT
public:
    VideoTcpPushThread(QObject *parent, VideoManager * videoManager, int socketHandle);
    void run();

protected:
    int socketHandle;
    VideoManager * videoManager;
    QTcpSocket * socket;
    QTcpSocket * dataSocket;
    QString currentRequest;
    int currentNumImage;
    bool isPlaying;

signals:
    void log(QString message, VodIF::DebugLevel level = VodIF::Log);
    void timeout();

public slots:
    void traiteRequete();
    void envoieImage();
};

#endif // VIDEOTCPPUSHTHREAD_H
