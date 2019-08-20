/********************************************************************************
** Form generated from reading UI file 'screen.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCREEN_H
#define UI_SCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MediaManager/dispwidget.h"

QT_BEGIN_NAMESPACE

class Ui_screen
{
public:
    QAction *actionStop;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    dispwidget *screenWidget;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *ssButton;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menubar;
    QMenu *menuOptions;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *screen)
    {
        if (screen->objectName().isEmpty())
            screen->setObjectName(QString::fromUtf8("screen"));
        screen->resize(800, 622);
        screen->setMinimumSize(QSize(800, 500));
        screen->setMaximumSize(QSize(1104, 800));
        actionStop = new QAction(screen);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        centralwidget = new QWidget(screen);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        screenWidget = new dispwidget(centralwidget);
        screenWidget->setObjectName(QString::fromUtf8("screenWidget"));
        screenWidget->setMinimumSize(QSize(640, 0));
        screenWidget->setMaximumSize(QSize(1080, 720));

        verticalLayout->addWidget(screenWidget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        ssButton = new QPushButton(centralwidget);
        ssButton->setObjectName(QString::fromUtf8("ssButton"));
        ssButton->setMinimumSize(QSize(250, 45));

        horizontalLayout->addWidget(ssButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        screen->setCentralWidget(centralwidget);
        menubar = new QMenuBar(screen);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        screen->setMenuBar(menubar);
        statusbar = new QStatusBar(screen);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        screen->setStatusBar(statusbar);

        menubar->addAction(menuOptions->menuAction());
        menuOptions->addAction(actionStop);

        retranslateUi(screen);

        QMetaObject::connectSlotsByName(screen);
    } // setupUi

    void retranslateUi(QMainWindow *screen)
    {
        screen->setWindowTitle(QApplication::translate("screen", "Source Display", nullptr));
        actionStop->setText(QApplication::translate("screen", "Stop", nullptr));
        ssButton->setText(QApplication::translate("screen", "Start", nullptr));
        menuOptions->setTitle(QApplication::translate("screen", "Options", nullptr));
    } // retranslateUi

};

namespace Ui {
    class screen: public Ui_screen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREEN_H
