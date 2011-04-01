#ifndef SERVERCONTROL_H
#define SERVERCONTROL_H

#include <QMainWindow>
#include <QMutex>
#include "videomanager.h"
#include "catalogueserver.h"
#include "vodifglobals.h"

namespace Ui {
    class ServerControl;
}

class ServerControl : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerControl(QWidget *parent = 0);
    ~ServerControl();
    CatalogueServer * cs;
    VideoManager * vm1;

public slots:
    void writeLog(QString message, VodIF::DebugLevel level = VodIF::Log);
    void updateCatalogueServerStatus(bool newStatus);
    void changeLogLevel(int level);

protected:
    QMutex writingMutex;
    VodIF::DebugLevel logLevel;

private:
    Ui::ServerControl *ui;
};

#endif // SERVERCONTROL_H
