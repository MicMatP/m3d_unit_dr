/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <myglwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpenCalibration_File;
    QAction *actionMake_A_measurment;
    QAction *actionSave_Project;
    QAction *actionSave_pointcloud;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    myGlWidget *widget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QDoubleSpinBox *doubleSpinBox_Y;
    QLabel *label;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox_yaw;
    QDoubleSpinBox *doubleSpinBox_pitch;
    QLabel *label_5;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_Z;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox_X;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBox_roll;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        actionOpenCalibration_File = new QAction(MainWindow);
        actionOpenCalibration_File->setObjectName(QStringLiteral("actionOpenCalibration_File"));
        actionMake_A_measurment = new QAction(MainWindow);
        actionMake_A_measurment->setObjectName(QStringLiteral("actionMake_A_measurment"));
        actionSave_Project = new QAction(MainWindow);
        actionSave_Project->setObjectName(QStringLiteral("actionSave_Project"));
        actionSave_pointcloud = new QAction(MainWindow);
        actionSave_pointcloud->setObjectName(QStringLiteral("actionSave_pointcloud"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setMouseTracking(true);
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        widget = new myGlWidget(frame);
        widget->setObjectName(QStringLiteral("widget"));

        horizontalLayout_2->addWidget(widget);


        horizontalLayout->addWidget(frame);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMaximumSize(QSize(250, 16777215));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        doubleSpinBox_Y = new QDoubleSpinBox(groupBox);
        doubleSpinBox_Y->setObjectName(QStringLiteral("doubleSpinBox_Y"));
        doubleSpinBox_Y->setMinimum(-10000);
        doubleSpinBox_Y->setMaximum(100000);

        gridLayout->addWidget(doubleSpinBox_Y, 1, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        doubleSpinBox_yaw = new QDoubleSpinBox(groupBox);
        doubleSpinBox_yaw->setObjectName(QStringLiteral("doubleSpinBox_yaw"));
        doubleSpinBox_yaw->setMinimum(-100000);
        doubleSpinBox_yaw->setMaximum(100000);

        gridLayout->addWidget(doubleSpinBox_yaw, 3, 1, 1, 1);

        doubleSpinBox_pitch = new QDoubleSpinBox(groupBox);
        doubleSpinBox_pitch->setObjectName(QStringLiteral("doubleSpinBox_pitch"));
        doubleSpinBox_pitch->setMinimum(-100000);
        doubleSpinBox_pitch->setMaximum(100000);

        gridLayout->addWidget(doubleSpinBox_pitch, 4, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        doubleSpinBox_Z = new QDoubleSpinBox(groupBox);
        doubleSpinBox_Z->setObjectName(QStringLiteral("doubleSpinBox_Z"));
        doubleSpinBox_Z->setMinimum(-100000);
        doubleSpinBox_Z->setMaximum(100000);

        gridLayout->addWidget(doubleSpinBox_Z, 2, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        doubleSpinBox_X = new QDoubleSpinBox(groupBox);
        doubleSpinBox_X->setObjectName(QStringLiteral("doubleSpinBox_X"));
        doubleSpinBox_X->setMaximum(1e+06);

        gridLayout->addWidget(doubleSpinBox_X, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        doubleSpinBox_roll = new QDoubleSpinBox(groupBox);
        doubleSpinBox_roll->setObjectName(QStringLiteral("doubleSpinBox_roll"));
        doubleSpinBox_roll->setMinimum(-100000);
        doubleSpinBox_roll->setMaximum(100000);

        gridLayout->addWidget(doubleSpinBox_roll, 5, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_2->addWidget(pushButton);


        horizontalLayout->addWidget(groupBox);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpenCalibration_File);
        menuFile->addAction(actionMake_A_measurment);
        menuFile->addAction(actionSave_Project);
        menuFile->addAction(actionSave_pointcloud);

        retranslateUi(MainWindow);
        QObject::connect(menubar, SIGNAL(triggered(QAction*)), MainWindow, SLOT(onTrigger(QAction*)));
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(UpdatePC()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpenCalibration_File->setText(QApplication::translate("MainWindow", "OpenCalibration File", 0));
        actionMake_A_measurment->setText(QApplication::translate("MainWindow", "Make A measurment", 0));
        actionSave_Project->setText(QApplication::translate("MainWindow", "Save Project", 0));
        actionSave_pointcloud->setText(QApplication::translate("MainWindow", "Save pointcloud", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "LaserOffset", 0));
        label->setText(QApplication::translate("MainWindow", "X:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Y:", 0));
        label_5->setText(QApplication::translate("MainWindow", "pitch:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Z:", 0));
        label_4->setText(QApplication::translate("MainWindow", "yaw:", 0));
        label_6->setText(QApplication::translate("MainWindow", "roll:", 0));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
