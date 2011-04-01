#include "catalogueserver.h"
#include "cataloguethread.h"

CatalogueServer::CatalogueServer(QObject *parent) :
    QTcpServer(parent)
{
}

void CatalogueServer::incomingConnection(int handle)
{
    emit log("Connection de requête de catalogue effectuée par un client.", VodIF::Debug);

    // Création d'un nouveau thread pour traiter la requête
    CatalogueThread * thread = new CatalogueThread(this, catalogManager, handle);

    // Relai des logs de la part du thread, en renvoyant un signal log de la part du serveur
    connect(thread, SIGNAL(log(QString,VodIF::DebugLevel)), this, SIGNAL(log(QString,VodIF::DebugLevel)));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    // Démarrage du thread \o/
    thread->start();
}

void CatalogueServer::start()
{
    if(isListening())
    {
        emit log(QString("Le serveur de catalogue est déjà lancé."), VodIF::Warning);
        return;
    }

    // Création du catalogue, nécessaire (il contient ce que l'on cherche à envoyer)
    catalogManager = new CatalogueManager();

    if(catalogManager->catalogueSize() == 0)
        emit log("Le catalogue est vide. Le serveur répondra aux requêtes mais il est probable "
                 "que vous ayez oublié quelque chose.", VodIF::Warning);

    if(!listen(QHostAddress::Any, VodIF::CataloguePort))
    {
        emit log(QString("Impossible d'écouter sur le port ") + QString::number(VodIF::CataloguePort) +
                 ". Le serveur de catalogue n'est pas démarré.", VodIF::Error);
        return;
    };

    emit log(QString("Serveur de catalogue lancé, accessible sur le port ") + QString::number(VodIF::CataloguePort) + ".", VodIF::Info);
    emit statusChanged(true);
}

void CatalogueServer::stop()
{
    close();
    if(catalogManager)
    {
        delete catalogManager;
        catalogManager = 0;
    }
    emit log(QString("Serveur de catalogue arrêté."), VodIF::Info);
    emit statusChanged(false);
}
