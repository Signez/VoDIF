#ifndef CATALOGUESERVER_H
#define CATALOGUESERVER_H

#include <QTcpServer>
#include "cataloguemanager.h"
#include "vodifglobals.h"

class CatalogueServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit CatalogueServer(QObject *parent = 0);
    void incomingConnection(int handle);

protected:
    CatalogueManager * catalogManager;

signals:
    void log(QString message, VodIF::DebugLevel level = VodIF::Log);
    void statusChanged(bool);

public slots:
    void start();
    void stop();
};

#endif // CATALOGUESERVER_H
