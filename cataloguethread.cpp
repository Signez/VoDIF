#include "cataloguethread.h"
#include <QDate>
#include <QRegExp>
#include <QHostAddress>
using namespace VodIF;

CatalogueThread::CatalogueThread(QObject *parent, CatalogueManager * catalog, int socketHandle) :
    QThread(parent), socketHandle(socketHandle), catalogManager(catalog)
{
}

void CatalogueThread::run()
{
    bool success;
    QString request;
    QTcpSocket socket;
    socket.setSocketDescriptor(socketHandle);

    while((success = socket.waitForReadyRead())){
        while(socket.bytesAvailable() && !request.endsWith(CRLF CRLF)){
            request += socket.read(1);
        }

        if(request.endsWith(CRLF CRLF))
            break;

        // Empêche une saturation mémoire
        if(request.size() > 1000)
        {
            success = false;
            emit log("Saturation de requête par un client de catalogue (" + socket.peerAddress().toString() +") ; "
                     "fermeture immédiate. "
                     "(N'oubliez pas le CRLF CRLF en fin de requête !)", VodIF::Warning);
            break;
        }
    }

    // Timeout
    if(!success){
        emit log("Timeout ou erreur de connection avec un client de catalogue.", VodIF::Debug);
    }
    else
    {
        emit log(request, VodIF::Received);

        QByteArray dataEnvoi;
        QTextStream fluxEnvoi(&dataEnvoi);

        // TODO: Implémenter un mode strict
        QRegExp parser("GET (/|/?catalogu?e?.txt) HTTP/[0-1].[019]");

        if(parser.indexIn(request) != -1)
        {
            fluxEnvoi << "HTTP/1.1 200 OK" << CRLF
                      << "Server: " << VODIF_VERSION << " (Whatever)" << CRLF
                      << "Content-Length: " << catalogManager->catalogueSize() << CRLF
                      << "Connection: close" << CRLF
                      << "Content-Type: text/html; charset=UTF-8" << CRLF << CRLF << flush;
            emit log(dataEnvoi, VodIF::Sent);
            emit log(QString("Demande de catalogue, de la part de ") + socket.peerAddress().toString() + "." , VodIF::Log);
            socket.write(dataEnvoi);
            socket.write(catalogManager->catalogue());
        }
        else
        {
            fluxEnvoi << "HTTP/1.1 403 Forbidden" << CRLF
                      << "Server: " << VODIF_VERSION << " (Whatever)" << CRLF << CRLF << flush;
            emit log(dataEnvoi, VodIF::Sent);
            emit log(QString("Demande de fichier inconnu au lieu d'un catalogue, "
                             "de la part de ") + socket.peerAddress().toString() + "." , VodIF::Log);
            socket.write(dataEnvoi);
        }

        socket.flush();

        emit log(QString("Serveur de catalogue : déconnection de ") + socket.peerAddress().toString() + "." , VodIF::Debug);

        socket.disconnectFromHost();
        if(socket.state() != QAbstractSocket::UnconnectedState)
            socket.waitForDisconnected();

        // Destruction automatique du thread à la sortie de cette boucle.
    }
}
