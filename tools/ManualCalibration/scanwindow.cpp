#include "scanwindow.h"
#include "ui_scanwindow.h"
#include <QDebug>


scanWindow::scanWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scanWindow)
{
    ui->setupUi(this);
}

scanWindow::~scanWindow()
{
    delete ui;
}

void scanWindow::makeScan()
{
    qDebug()<< "makeScan!";
    m3d::_3dUnitConfig cfg;
    cfg.rotLaserIp = ui->laserIp->text().toStdString();
    cfg.unitIp = ui->unitIP->text().toStdString();

    m3d::_3dUnitDriver* driver =new m3d::_3dUnitDriver(cfg);
    driver->initialize();
    driver->setSpeed(ui->speed->sliderPosition());

    driver->requestPointcloud();
    driver->waitForPointCloud();

    driver->getRawPointCloud(*rawPc1);
    qDebug()<<"got first pointcloud ";
    driver->waitForPointCloud();
    driver->getRawPointCloud(*rawPc2);
    qDebug()<<"got second pointcloud ";

    driver->deinitialize();
    this->hide();
    //delete driver;
}
std::string scanWindow::getIpRotLaser()
{
    return ui->laserIp->text().toStdString();
}

std::string scanWindow::getIpUnit()
{
    return ui->unitIP->text().toStdString();
}
