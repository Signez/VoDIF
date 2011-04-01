# -------------------------------------------------
# Project created by QtCreator 2011-02-28T18:33:41
# -------------------------------------------------
QT += core \
    gui \
    network
TARGET = VoDIF
TEMPLATE = app
SOURCES += main.cpp \
    servercontrol.cpp \
    catalogueserver.cpp \
    cataloguethread.cpp \
    cataloguemanager.cpp \
    videomanager.cpp \
    videotcpserver.cpp \
    videotcppullthread.cpp \
    videotcppushthread.cpp \
    videoudpserver.cpp \
    videoudppullthread.cpp \
    videoudpthread.cpp \
    videoudppushthread.cpp
HEADERS += servercontrol.h \
    catalogueserver.h \
    vodifglobals.h \
    cataloguethread.h \
    cataloguemanager.h \
    videomanager.h \
    videotcpserver.h \
    videotcppullthread.h \
    videotcppushthread.h \
    videoudpserver.h \
    videoudppullthread.h \
    videoudpthread.h \
    videoudppushthread.h
FORMS += servercontrol.ui
OTHER_FILES += ../vodif-build-desktop/catalogue.txt \
    ../vodif-build-desktop/catalogue.txt
RESOURCES += elementsgraphiques.qrc
