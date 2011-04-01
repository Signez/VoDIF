#include "servercontrol.h"
#include "ui_servercontrol.h"

#include "videomanager.h"
#include "videotcpserver.h"
#include "videoudpserver.h"

#include <QFont>


ServerControl::ServerControl(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerControl)
{
    ui->setupUi(this);

    logLevel = VodIF::Info;

    cs = new CatalogueServer(this);

    connect(ui->actionDemarrer, SIGNAL(triggered()), cs, SLOT(start()));
    connect(ui->actionStopper, SIGNAL(triggered()), cs, SLOT(stop()));
    connect(cs, SIGNAL(log(QString,VodIF::DebugLevel)), this, SLOT(writeLog(QString,VodIF::DebugLevel)));

    connect(cs, SIGNAL(statusChanged(bool)), this, SLOT(updateCatalogueServerStatus(bool)));

    vm1 = new VideoManager(1, "BigBuckBunny", "JPEG", "./bbb/resized/light/", "*.jpg", 15,  this);
    connect(vm1, SIGNAL(log(QString,VodIF::DebugLevel)), this, SLOT(writeLog(QString,VodIF::DebugLevel)));
    vm1->load();

    VideoTcpServer * vs1 = new VideoTcpServer(false, vm1, 8090, this);
    connect(ui->actionDemarrer, SIGNAL(triggered()), vs1, SLOT(start()));
    connect(ui->actionStopper, SIGNAL(triggered()), vs1, SLOT(stop()));
    connect(vs1, SIGNAL(log(QString,VodIF::DebugLevel)), this, SLOT(writeLog(QString,VodIF::DebugLevel)));

    VideoTcpServer * vs2 = new VideoTcpServer(true, vm1, 8091, this);
    connect(ui->actionDemarrer, SIGNAL(triggered()), vs2, SLOT(start()));
    connect(ui->actionStopper, SIGNAL(triggered()), vs2, SLOT(stop()));
    connect(vs2, SIGNAL(log(QString,VodIF::DebugLevel)), this, SLOT(writeLog(QString,VodIF::DebugLevel)));

    VideoUdpServer * vs3 = new VideoUdpServer(false, vm1, 8092, this);
    connect(ui->actionDemarrer, SIGNAL(triggered()), vs3, SLOT(start()));
    connect(ui->actionStopper, SIGNAL(triggered()), vs3, SLOT(stop()));
    connect(vs3, SIGNAL(log(QString,VodIF::DebugLevel)), this, SLOT(writeLog(QString,VodIF::DebugLevel)));

    VideoUdpServer * vs4 = new VideoUdpServer(true, vm1, 8093, this);
    connect(ui->actionDemarrer, SIGNAL(triggered()), vs4, SLOT(start()));
    connect(ui->actionStopper, SIGNAL(triggered()), vs4, SLOT(stop()));
    connect(vs4, SIGNAL(log(QString,VodIF::DebugLevel)), this, SLOT(writeLog(QString,VodIF::DebugLevel)));
}

ServerControl::~ServerControl()
{
    delete ui;
    // C'est tout : tout le reste est supprimé car les objets connaissent leur parent.
}

void ServerControl::writeLog(QString message, VodIF::DebugLevel level)
{
    QMutexLocker locker(&writingMutex);
    QString type;
    switch (level)
    {
    case VodIF::DataLoaded:
        type = "Chargement";
        break;
    case VodIF::Received:
        type = "Message reçu";
        message.replace(CRLF, "<span style=\"color: grey; font-style: italic;\">CRLF</span><br/>");
        break;
    case VodIF::Sent:
        message.replace(CRLF, "<span style=\"color: grey; font-style: italic;\">CRLF</span><br/>");
        type = "Message envoyé";
        break;
    case VodIF::Debug:
        type = "Debug";
        break;
    case VodIF::Log:
        type = "Log";
        break;
    case VodIF::Warning:
        type = "Attention";
        break;
    case VodIF::Error:
        type = "Erreur";
        break;
    default:
        type = "Info";
    }

    if(level >= logLevel){
        ui->txtLogs->append(type + " » " + message.trimmed());
    }
}

void ServerControl::updateCatalogueServerStatus(bool newStatus)
{
    ui->butDemarrer->setEnabled(!newStatus);
    ui->butStopper->setEnabled(newStatus);
}

void ServerControl::changeLogLevel(int level)
{
    VodIF::DebugLevel niveaux[] = {VodIF::AllLogs, VodIF::Sent, VodIF::Debug, VodIF::Log,
                                   VodIF::Warning, VodIF::Error, VodIF::NoLogs};

    QLabel * labels[] = {ui->labVerbTout, ui->labVerbPaquets, ui->labVerbDebug, ui->labVerbInfos,
                        ui->labVerbAvert, ui->labVerbErreurs, ui->labVerbRien};

    for(int i = 0; i < 7; i++)
    {
        QFont font = labels[i]->font();
        font.setBold(false);
        labels[i]->setFont(font);
    }

    if(level < 0 || level > 7)
        level = 3;

    logLevel = niveaux[level];
    QFont font = labels[level]->font();
    font.setBold(true);
    labels[level]->setFont(font);

    return;
}
