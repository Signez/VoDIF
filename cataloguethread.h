#ifndef CATALOGUETHREAD_H
#define CATALOGUETHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "cataloguemanager.h"
#include "vodifglobals.h"

class CatalogueThread : public QThread
{
    Q_OBJECT
public:
    CatalogueThread(QObject *parent, CatalogueManager * catalog, int socketHandle);
    void run();

protected:
    int socketHandle;
    CatalogueManager * catalogManager;

signals:
    void log(QString message, VodIF::DebugLevel level = VodIF::Log);
    void timeout();

public slots:

};

#endif // CATALOGUETHREAD_H
