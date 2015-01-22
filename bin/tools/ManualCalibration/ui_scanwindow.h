/********************************************************************************
** Form generated from reading UI file 'scanwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCANWINDOW_H
#define UI_SCANWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_scanWindow
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *laserIp;
    QLineEdit *unitIP;
    QSlider *speed;
    QLabel *label_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *scanWindow)
    {
        if (scanWindow->objectName().isEmpty())
            scanWindow->setObjectName(QStringLiteral("scanWindow"));
        scanWindow->resize(388, 281);
        verticalLayout = new QVBoxLayout(scanWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(scanWindow);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(scanWindow);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        laserIp = new QLineEdit(scanWindow);
        laserIp->setObjectName(QStringLiteral("laserIp"));

        gridLayout->addWidget(laserIp, 0, 1, 1, 1);

        unitIP = new QLineEdit(scanWindow);
        unitIP->setObjectName(QStringLiteral("unitIP"));

        gridLayout->addWidget(unitIP, 1, 1, 1, 1);

        speed = new QSlider(scanWindow);
        speed->setObjectName(QStringLiteral("speed"));
        speed->setMinimum(12);
        speed->setMaximum(55);
        speed->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(speed, 2, 1, 1, 1);

        label_3 = new QLabel(scanWindow);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        pushButton = new QPushButton(scanWindow);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(scanWindow);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);


        retranslateUi(scanWindow);
        QObject::connect(pushButton_2, SIGNAL(clicked()), scanWindow, SLOT(reject()));
        QObject::connect(pushButton, SIGNAL(clicked()), scanWindow, SLOT(makeScan()));

        QMetaObject::connectSlotsByName(scanWindow);
    } // setupUi

    void retranslateUi(QDialog *scanWindow)
    {
        scanWindow->setWindowTitle(QApplication::translate("scanWindow", "Dialog", 0));
        label_2->setText(QApplication::translate("scanWindow", "m3d IP", 0));
        label->setText(QApplication::translate("scanWindow", "Laser IP", 0));
        laserIp->setText(QApplication::translate("scanWindow", "192.168.0.201", 0));
        unitIP->setText(QApplication::translate("scanWindow", "192.168.0.150", 0));
        label_3->setText(QApplication::translate("scanWindow", "Measurment Speed", 0));
        pushButton->setText(QApplication::translate("scanWindow", "Make A measurment", 0));
        pushButton_2->setText(QApplication::translate("scanWindow", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class scanWindow: public Ui_scanWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANWINDOW_H
