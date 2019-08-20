/********************************************************************************
** Form generated from reading UI file 'paraminterface.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMINTERFACE_H
#define UI_PARAMINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParamInterface
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *contourCombo;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSlider *alphaSlider;
    QLabel *alphaValLabel;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QSlider *betaSlider;
    QLabel *betaValLabel;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QSlider *gammaSlider;
    QLabel *gammaValLabel;
    QCheckBox *snakePointCheck;
    QCheckBox *snakeLineCheck;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QComboBox *sobelCombo;
    QSpacerItem *verticalSpacer_2;
    QCheckBox *sobelDSCheck;
    QPushButton *doneButton;
    QPushButton *cancelButton;
    QGroupBox *groupBox_3;
    QCheckBox *sobelView;
    QCheckBox *snakeView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ParamInterface)
    {
        if (ParamInterface->objectName().isEmpty())
            ParamInterface->setObjectName(QString::fromUtf8("ParamInterface"));
        ParamInterface->resize(480, 400);
        ParamInterface->setMinimumSize(QSize(480, 300));
        ParamInterface->setMaximumSize(QSize(480, 400));
        centralwidget = new QWidget(ParamInterface);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 211, 281));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        contourCombo = new QComboBox(groupBox);
        contourCombo->setObjectName(QString::fromUtf8("contourCombo"));

        verticalLayout->addWidget(contourCombo);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_2->addLayout(verticalLayout);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        alphaSlider = new QSlider(groupBox);
        alphaSlider->setObjectName(QString::fromUtf8("alphaSlider"));
        alphaSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(alphaSlider);

        alphaValLabel = new QLabel(groupBox);
        alphaValLabel->setObjectName(QString::fromUtf8("alphaValLabel"));

        horizontalLayout->addWidget(alphaValLabel);


        verticalLayout_5->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        betaSlider = new QSlider(groupBox);
        betaSlider->setObjectName(QString::fromUtf8("betaSlider"));
        betaSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(betaSlider);

        betaValLabel = new QLabel(groupBox);
        betaValLabel->setObjectName(QString::fromUtf8("betaValLabel"));

        horizontalLayout_2->addWidget(betaValLabel);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        gammaSlider = new QSlider(groupBox);
        gammaSlider->setObjectName(QString::fromUtf8("gammaSlider"));
        gammaSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(gammaSlider);

        gammaValLabel = new QLabel(groupBox);
        gammaValLabel->setObjectName(QString::fromUtf8("gammaValLabel"));

        horizontalLayout_3->addWidget(gammaValLabel);


        verticalLayout_5->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(verticalLayout_5);

        snakePointCheck = new QCheckBox(groupBox);
        snakePointCheck->setObjectName(QString::fromUtf8("snakePointCheck"));

        verticalLayout_2->addWidget(snakePointCheck);

        snakeLineCheck = new QCheckBox(groupBox);
        snakeLineCheck->setObjectName(QString::fromUtf8("snakeLineCheck"));

        verticalLayout_2->addWidget(snakeLineCheck);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(240, 10, 221, 171));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_3->addWidget(label_2);

        sobelCombo = new QComboBox(groupBox_2);
        sobelCombo->setObjectName(QString::fromUtf8("sobelCombo"));

        verticalLayout_3->addWidget(sobelCombo);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        verticalLayout_4->addLayout(verticalLayout_3);

        sobelDSCheck = new QCheckBox(groupBox_2);
        sobelDSCheck->setObjectName(QString::fromUtf8("sobelDSCheck"));

        verticalLayout_4->addWidget(sobelDSCheck);

        doneButton = new QPushButton(centralwidget);
        doneButton->setObjectName(QString::fromUtf8("doneButton"));
        doneButton->setGeometry(QRect(240, 310, 113, 32));
        cancelButton = new QPushButton(centralwidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(120, 310, 113, 32));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(240, 180, 211, 111));
        sobelView = new QCheckBox(groupBox_3);
        sobelView->setObjectName(QString::fromUtf8("sobelView"));
        sobelView->setGeometry(QRect(10, 30, 141, 20));
        snakeView = new QCheckBox(groupBox_3);
        snakeView->setObjectName(QString::fromUtf8("snakeView"));
        snakeView->setGeometry(QRect(10, 60, 141, 20));
        ParamInterface->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ParamInterface);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 480, 22));
        ParamInterface->setMenuBar(menubar);
        statusbar = new QStatusBar(ParamInterface);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ParamInterface->setStatusBar(statusbar);

        retranslateUi(ParamInterface);

        QMetaObject::connectSlotsByName(ParamInterface);
    } // setupUi

    void retranslateUi(QMainWindow *ParamInterface)
    {
        ParamInterface->setWindowTitle(QApplication::translate("ParamInterface", "Snake Options", nullptr));
        groupBox->setTitle(QApplication::translate("ParamInterface", "Active Contour Settings", nullptr));
        label->setText(QApplication::translate("ParamInterface", "Number of Points", nullptr));
        label_3->setText(QApplication::translate("ParamInterface", "Alpha    ", nullptr));
#ifndef QT_NO_WHATSTHIS
        alphaSlider->setWhatsThis(QApplication::translate("ParamInterface", "Contour Scalar", nullptr));
#endif // QT_NO_WHATSTHIS
        alphaValLabel->setText(QApplication::translate("ParamInterface", "___", nullptr));
        label_4->setText(QApplication::translate("ParamInterface", "Beta      ", nullptr));
#ifndef QT_NO_WHATSTHIS
        betaSlider->setWhatsThis(QApplication::translate("ParamInterface", "Curve Scalar", nullptr));
#endif // QT_NO_WHATSTHIS
        betaValLabel->setText(QApplication::translate("ParamInterface", "___", nullptr));
        label_5->setText(QApplication::translate("ParamInterface", "Gamma", nullptr));
#ifndef QT_NO_WHATSTHIS
        gammaSlider->setWhatsThis(QApplication::translate("ParamInterface", "Image Scalar", nullptr));
#endif // QT_NO_WHATSTHIS
        gammaValLabel->setText(QApplication::translate("ParamInterface", "___", nullptr));
        snakePointCheck->setText(QApplication::translate("ParamInterface", "Draw Snake Points", nullptr));
        snakeLineCheck->setText(QApplication::translate("ParamInterface", "Draw Snake Lines", nullptr));
        groupBox_2->setTitle(QApplication::translate("ParamInterface", "Sobel Settings", nullptr));
        label_2->setText(QApplication::translate("ParamInterface", "Sobel Threshold", nullptr));
        sobelDSCheck->setText(QApplication::translate("ParamInterface", "Sobel Dead Space", nullptr));
        doneButton->setText(QApplication::translate("ParamInterface", "Done", nullptr));
        cancelButton->setText(QApplication::translate("ParamInterface", "Cancel", nullptr));
        groupBox_3->setTitle(QApplication::translate("ParamInterface", "Screen Viewer", nullptr));
        sobelView->setText(QApplication::translate("ParamInterface", "View Sobel Output", nullptr));
        snakeView->setText(QApplication::translate("ParamInterface", "View Snake Output", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ParamInterface: public Ui_ParamInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMINTERFACE_H
