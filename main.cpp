#include <QtGui/QApplication>
#include <QTextCodec>
#include "servercontrol.h"
#include <QMetaType>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    qRegisterMetaType<VodIF::DebugLevel>("VodIF::DebugLevel");

    QApplication a(argc, argv);
    ServerControl w;
    w.show();

    return a.exec();
}
