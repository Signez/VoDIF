#ifndef VODIFGLOBALS_H
#define VODIFGLOBALS_H

#define CRLF "\r\n"
#define VODIF_VERSION "VodIF/0.1b2"

#include <QHostAddress>

namespace VodIF {
    enum DebugLevel {
        AllLogs = 0,
        DataLoaded = 5,
        Sent = 10,
        Received = 11,
        Debug = 20,
        Log = 30,
        Info = 40,
        Warning = 50,
        Error = 60,
        NoLogs = 100
    };
    const int CataloguePort = 8100;
};

#endif // VODIFGLOBALS_H
