#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <QObject>
#include <QVector>
#include <QByteArray>
#include <QMutex>
#include "vodifglobals.h"

class VideoManager : public QObject
{
    Q_OBJECT
public:
    VideoManager(int objectId, QString name, QString type, QString location, QString filter, double ips, QObject *parent = 0);
    QByteArray * getImage(int imageId);
    int objectId();
    int size();
    QString type();
    QString name();
    int getDelayMs();

protected:
    int myObjectId;
    QString myName;
    QString myType;
    QString location;
    QString filter;
    QVector<QByteArray *> images;
    QMutex mutex;
    double ips;

signals:
    void log(QString message, VodIF::DebugLevel level = VodIF::Log);

public slots:
    bool load();
};

#endif // VIDEOMANAGER_H
