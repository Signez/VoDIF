#include "videomanager.h"
#include <QFile>
#include <QDir>
#include <QDebug>

#include <iostream>

VideoManager::VideoManager(int objectId,
                           QString name, QString type,
                           QString location, QString filter,
                           double ips,
                           QObject *parent):
    QObject(parent), myObjectId(objectId), myName(name), myType(type), location(location), filter(filter), ips(ips)
{
}

bool VideoManager::load()
{
    QDir dir(location);
    dir.setFilter(QDir::Files);
    dir.setNameFilters(QStringList(filter));

    emit log(QString("Chargement des données de l'objet ") + QString::number(myObjectId) + "...", VodIF::Debug);

    foreach(const QString filename, dir.entryList())
    {
        QFile myFile(location + filename);
        if(myFile.open(QIODevice::ReadOnly)){
            QByteArray * imageData = new QByteArray(myFile.readAll());
            images.append(imageData);
            emit log(myName + " (#" + QString::number(myObjectId) + ") ; image " + filename + " chargée." + "...", VodIF::DataLoaded);
        }
        else
        {
            emit log(myName + " (#" + QString::number(myObjectId) + ") ; impossible de charger l'image " + filename + ".", VodIF::Warning);
        }
    }

    return true;
}

QByteArray * VideoManager::getImage(int imageId)
{
    QMutexLocker lock(&mutex);
    return images.at(imageId);
}

int VideoManager::size()
{
    return images.size();
}

int VideoManager::objectId()
{
    return myObjectId;
}

QString VideoManager::name()
{
    return myName;
}

int VideoManager::getDelayMs()
{
    return 1 / ips * 1000;
}
