/********************************************************************************
** Form generated from reading UI file 'servercontrol.ui'
**
** Created: Tue Mar 22 17:22:29 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERCONTROL_H
#define UI_SERVERCONTROL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerControl
{
public:
    QAction *actionDemarrer;
    QAction *actionStopper;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QPushButton *butDemarrer;
    QSpacerItem *horizontalSpacer;
    QPushButton *butStopper;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QTextBrowser *txtLogs;
    QLabel *label_8;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSlider *verticalSlider;
    QVBoxLayout *verticalLayout;
    QLabel *labVerbTout;
    QLabel *labVerbPaquets;
    QLabel *labVerbDebug;
    QLabel *labVerbInfos;
    QLabel *labVerbAvert;
    QLabel *labVerbErreurs;
    QLabel *labVerbRien;
    QTextBrowser *textBrowser;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkBox;
    QWidget *tab_3;
    QGridLayout *gridLayout_3;
    QLabel *label_9;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton;

    void setupUi(QMainWindow *ServerControl)
    {
        if (ServerControl->objectName().isEmpty())
            ServerControl->setObjectName(QString::fromUtf8("ServerControl"));
        ServerControl->resize(468, 312);
        ServerControl->setMinimumSize(QSize(468, 0));
        actionDemarrer = new QAction(ServerControl);
        actionDemarrer->setObjectName(QString::fromUtf8("actionDemarrer"));
        actionStopper = new QAction(ServerControl);
        actionStopper->setObjectName(QString::fromUtf8("actionStopper"));
        centralWidget = new QWidget(ServerControl);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        butDemarrer = new QPushButton(centralWidget);
        butDemarrer->setObjectName(QString::fromUtf8("butDemarrer"));

        gridLayout_2->addWidget(butDemarrer, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);

        butStopper = new QPushButton(centralWidget);
        butStopper->setObjectName(QString::fromUtf8("butStopper"));
        butStopper->setEnabled(false);

        gridLayout_2->addWidget(butStopper, 0, 2, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        txtLogs = new QTextBrowser(tab);
        txtLogs->setObjectName(QString::fromUtf8("txtLogs"));
        txtLogs->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(txtLogs, 0, 0, 1, 1);

        label_8 = new QLabel(tab);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 1, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_2 = new QVBoxLayout(tab_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(16777215, 175));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalSlider = new QSlider(groupBox);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setEnabled(true);
        verticalSlider->setMinimum(0);
        verticalSlider->setMaximum(6);
        verticalSlider->setPageStep(1);
        verticalSlider->setValue(3);
        verticalSlider->setSliderPosition(3);
        verticalSlider->setOrientation(Qt::Vertical);
        verticalSlider->setInvertedAppearance(true);
        verticalSlider->setInvertedControls(true);
        verticalSlider->setTickPosition(QSlider::TicksBelow);
        verticalSlider->setTickInterval(1);

        horizontalLayout->addWidget(verticalSlider);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labVerbTout = new QLabel(groupBox);
        labVerbTout->setObjectName(QString::fromUtf8("labVerbTout"));

        verticalLayout->addWidget(labVerbTout);

        labVerbPaquets = new QLabel(groupBox);
        labVerbPaquets->setObjectName(QString::fromUtf8("labVerbPaquets"));
        labVerbPaquets->setMinimumSize(QSize(50, 0));

        verticalLayout->addWidget(labVerbPaquets);

        labVerbDebug = new QLabel(groupBox);
        labVerbDebug->setObjectName(QString::fromUtf8("labVerbDebug"));

        verticalLayout->addWidget(labVerbDebug);

        labVerbInfos = new QLabel(groupBox);
        labVerbInfos->setObjectName(QString::fromUtf8("labVerbInfos"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        labVerbInfos->setFont(font);

        verticalLayout->addWidget(labVerbInfos);

        labVerbAvert = new QLabel(groupBox);
        labVerbAvert->setObjectName(QString::fromUtf8("labVerbAvert"));

        verticalLayout->addWidget(labVerbAvert);

        labVerbErreurs = new QLabel(groupBox);
        labVerbErreurs->setObjectName(QString::fromUtf8("labVerbErreurs"));

        verticalLayout->addWidget(labVerbErreurs);

        labVerbRien = new QLabel(groupBox);
        labVerbRien->setObjectName(QString::fromUtf8("labVerbRien"));

        verticalLayout->addWidget(labVerbRien);


        horizontalLayout->addLayout(verticalLayout);


        horizontalLayout_2->addLayout(horizontalLayout);

        textBrowser = new QTextBrowser(groupBox);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setAutoFillBackground(false);
        textBrowser->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"\n"
"p {\n"
"  margin-bottom: 0px !important;\n"
"}"));
        textBrowser->setFrameShape(QFrame::NoFrame);

        horizontalLayout_2->addWidget(textBrowser);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setEnabled(false);

        verticalLayout_3->addWidget(checkBox);


        verticalLayout_2->addWidget(groupBox_2);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_3 = new QGridLayout(tab_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_9 = new QLabel(tab_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_9->setMaximumSize(QSize(100, 16777215));
        label_9->setPixmap(QPixmap(QString::fromUtf8(":/icones/projecteur.png")));
        label_9->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout_3->addWidget(label_9, 0, 0, 4, 1);

        widget = new QWidget(tab_3);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 92));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 8, 0, 8);
        label_10 = new QLabel(widget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font);

        verticalLayout_4->addWidget(label_10);

        label_11 = new QLabel(widget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        label_11->setFont(font1);

        verticalLayout_4->addWidget(label_11);

        label_12 = new QLabel(widget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        verticalLayout_4->addWidget(label_12);


        gridLayout_3->addWidget(widget, 0, 1, 1, 1);

        label_13 = new QLabel(tab_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setWordWrap(true);

        gridLayout_3->addWidget(label_13, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        pushButton = new QPushButton(tab_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(false);
        pushButton->setMinimumSize(QSize(80, 0));

        horizontalLayout_3->addWidget(pushButton);


        gridLayout_3->addLayout(horizontalLayout_3, 3, 1, 1, 1);

        tabWidget->addTab(tab_3, QString());

        gridLayout_2->addWidget(tabWidget, 1, 0, 1, 3);

        ServerControl->setCentralWidget(centralWidget);

        retranslateUi(ServerControl);
        QObject::connect(butDemarrer, SIGNAL(clicked()), actionDemarrer, SLOT(trigger()));
        QObject::connect(butStopper, SIGNAL(clicked()), actionStopper, SLOT(trigger()));
        QObject::connect(verticalSlider, SIGNAL(valueChanged(int)), ServerControl, SLOT(changeLogLevel(int)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ServerControl);
    } // setupUi

    void retranslateUi(QMainWindow *ServerControl)
    {
        ServerControl->setWindowTitle(QApplication::translate("ServerControl", "VoDIF", 0, QApplication::UnicodeUTF8));
        actionDemarrer->setText(QApplication::translate("ServerControl", "Demarrer", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionDemarrer->setToolTip(QApplication::translate("ServerControl", "D\303\251marre le serveur.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionDemarrer->setShortcut(QApplication::translate("ServerControl", "Ctrl+Space", 0, QApplication::UnicodeUTF8));
        actionStopper->setText(QApplication::translate("ServerControl", "Arr\303\252ter", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionStopper->setToolTip(QApplication::translate("ServerControl", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Tahoma'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Arr\303\252te le serveur.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:7pt;\">Ctrl+W</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionStopper->setShortcut(QApplication::translate("ServerControl", "Ctrl+W", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        butDemarrer->setToolTip(QApplication::translate("ServerControl", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Tahoma'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">D\303\251marre le serveur.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:7pt;\">Ctrl+Espace</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        butDemarrer->setText(QApplication::translate("ServerControl", "&D\303\251marrer", 0, QApplication::UnicodeUTF8));
        butDemarrer->setShortcut(QApplication::translate("ServerControl", "Ctrl+Space", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        butStopper->setToolTip(QApplication::translate("ServerControl", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Tahoma'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Arr\303\252te le serveur.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:7pt;\">Ctrl+W</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        butStopper->setText(QApplication::translate("ServerControl", "Arr\303\252&ter", 0, QApplication::UnicodeUTF8));
        butStopper->setShortcut(QApplication::translate("ServerControl", "Ctrl+W", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("ServerControl", "<Statut>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ServerControl", "M&ain courante", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ServerControl", "&Verbosit\303\251 de la main courante", 0, QApplication::UnicodeUTF8));
        labVerbTout->setText(QApplication::translate("ServerControl", "Tout", 0, QApplication::UnicodeUTF8));
        labVerbPaquets->setText(QApplication::translate("ServerControl", "Paquets", 0, QApplication::UnicodeUTF8));
        labVerbDebug->setText(QApplication::translate("ServerControl", "Debug", 0, QApplication::UnicodeUTF8));
        labVerbInfos->setText(QApplication::translate("ServerControl", "Infos", 0, QApplication::UnicodeUTF8));
        labVerbAvert->setText(QApplication::translate("ServerControl", "Avert.", 0, QApplication::UnicodeUTF8));
        labVerbErreurs->setText(QApplication::translate("ServerControl", "Erreurs", 0, QApplication::UnicodeUTF8));
        labVerbRien->setText(QApplication::translate("ServerControl", "Rien", 0, QApplication::UnicodeUTF8));
        textBrowser->setHtml(QApplication::translate("ServerControl", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:5px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Tahoma'; font-size:8pt;\">Toutes les informations utiles au quotidien sont affich\303\251es.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:5px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Tahoma'; font-size:8pt;\">Ce mode est conseill\303\251 pour un \302\253 usage en production \302\273. Il permet d'avoir un bon compromis verbosit\303\251/clart\303\251/performances.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:5px; margin-left:0px; margin-right:0"
                        "px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Tahoma'; font-size:8pt;\">Si le but est de programmer des clients, il est conseill\303\251 d'augmenter le niveau de verbosit\303\251 pour obtenir une plus grande tracabilit\303\251 des \303\251v\303\251nements.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("ServerControl", "Fonctionnalit\303\251s suppl\303\251mentaires", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("ServerControl", "Activer la publication &Multicast du catalogue", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("ServerControl", "&Configuration", 0, QApplication::UnicodeUTF8));
        label_9->setText(QString());
        label_10->setText(QApplication::translate("ServerControl", "VodIF \342\210\222 Serveur de vid\303\251o \303\240 la demande", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("ServerControl", "TP Multim\303\251dia/R\303\251seau \342\210\222 INSA de Lyon, IF", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("ServerControl", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Tahoma'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">R\303\251alis\303\251 par :</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic;\">Stanislas Signoud</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic;\">Alexis Jossinet</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("ServerControl", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Tahoma'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Ce programme utilise (vraiment) la biblioth\303\250que Qt 4.7.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:7pt;\">Qt est un framework C++ permettant la cr\303\251ation d'applications graphiques stables et robustes, avec un minimum d'impact sur les performances et avec une portabilit\303\251 maximale.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ServerControl", "Licence", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("ServerControl", "\303\200 &propos", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ServerControl: public Ui_ServerControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERCONTROL_H
