/********************************************************************************
** Form generated from reading UI file 'custonsnakeparams.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTONSNAKEPARAMS_H
#define UI_CUSTONSNAKEPARAMS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CustonSnakeParams
{
public:
    QWidget *centralwidget;
    QPushButton *doneButton;
    QPushButton *cancelButton;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CustonSnakeParams)
    {
        if (CustonSnakeParams->objectName().isEmpty())
            CustonSnakeParams->setObjectName(QString::fromUtf8("CustonSnakeParams"));
        CustonSnakeParams->resize(604, 476);
        centralwidget = new QWidget(CustonSnakeParams);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        doneButton = new QPushButton(centralwidget);
        doneButton->setObjectName(QString::fromUtf8("doneButton"));
        doneButton->setGeometry(QRect(480, 380, 113, 32));
        cancelButton = new QPushButton(centralwidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(350, 380, 113, 32));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 10, 221, 121));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(270, 10, 321, 301));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(30, 160, 211, 151));
        CustonSnakeParams->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CustonSnakeParams);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 604, 22));
        CustonSnakeParams->setMenuBar(menubar);
        statusbar = new QStatusBar(CustonSnakeParams);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        CustonSnakeParams->setStatusBar(statusbar);

        retranslateUi(CustonSnakeParams);

        QMetaObject::connectSlotsByName(CustonSnakeParams);
    } // setupUi

    void retranslateUi(QMainWindow *CustonSnakeParams)
    {
        CustonSnakeParams->setWindowTitle(QApplication::translate("CustonSnakeParams", "Snake Options", nullptr));
        doneButton->setText(QApplication::translate("CustonSnakeParams", "Done", nullptr));
        cancelButton->setText(QApplication::translate("CustonSnakeParams", "Cancel", nullptr));
        groupBox->setTitle(QApplication::translate("CustonSnakeParams", "Sobel", nullptr));
        groupBox_2->setTitle(QApplication::translate("CustonSnakeParams", "Snake", nullptr));
        groupBox_3->setTitle(QApplication::translate("CustonSnakeParams", "Display Options", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CustonSnakeParams: public Ui_CustonSnakeParams {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTONSNAKEPARAMS_H
