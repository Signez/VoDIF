#ifndef CATALOGUEMANAGER_H
#define CATALOGUEMANAGER_H

#include <QObject>
#include <QByteArray>
#include <QMutex>

class CatalogueManager : public QObject
{
    Q_OBJECT
public:
    explicit CatalogueManager(QObject *parent = 0);
    QByteArray catalogue();
    int catalogueSize();

protected:
    QByteArray myCatalogue;
    int mySize;
    QMutex mutex;

signals:

public slots:

};

#endif // CATALOGUEMANAGER_H
