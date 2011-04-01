#include "cataloguemanager.h"
#include <QFile>

CatalogueManager::CatalogueManager(QObject *parent) :
    QObject(parent)
{
    myCatalogue = "";
    mySize = 0;

    QFile file("catalogue.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
       return;

    while (!file.atEnd()) {
        myCatalogue += file.readLine().trimmed().append("\r\n");
    }

    mySize = myCatalogue.size();
}

QByteArray CatalogueManager::catalogue()
{
   QMutexLocker lock(&mutex);
   return myCatalogue;
}

int CatalogueManager::catalogueSize()
{
    QMutexLocker lock(&mutex);
    return mySize;
}
