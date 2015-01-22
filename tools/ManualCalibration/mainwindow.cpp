#include "3dUnitTypeSerialization.hpp"
#include <boost/log/expressions.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //viewer->setWindowName("test");
    // Set up the QVTK window
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTrigger(QAction* action)
{
    qDebug()<< action;
    _scanWindow.rawPc1 = &rawPointcloud1;
    _scanWindow.rawPc2 = &rawPointcloud2;

    if (action->objectName() == "actionMake_A_measurment")
    {
        _scanWindow.show();
    }
    else
    if (action->objectName() =="actionSave_Measurment")
    {
        QString fileName = QFileDialog::getSaveFileName(this,
                 tr("Open XML File 1"), "/home", tr("Measurments (*.m3dMeas)"));
        if (fileName.size()==0) return;
        boost::property_tree::ptree pt;
        m3d::typeSerialization::serialize(pt, rawPointcloud1, "rawPointcloud1");
        m3d::typeSerialization::serialize(pt, rawPointcloud2, "rawPointcloud2");
#ifdef _WIN32
		boost::property_tree::write_xml(fileName.toStdString(), pt);
#else
		boost::property_tree::xml_writer_settings<char> settings('\t', 1);
        boost::property_tree::write_xml(fileName.toStdString(), pt, std::locale(), settings);
#endif
		
    }

    if (action->objectName() =="actionOpenMeasurment")
    {
        QString fileName = QFileDialog::getOpenFileName(this,
                 tr("Open XML File 1"), "/home", tr("Measurments (*.m3dMeas)"));
        if (fileName.size()==0) return;
        boost::property_tree::ptree pt;
        boost::property_tree::read_xml(fileName.toStdString(), pt);
        m3d::typeSerialization::deserialize(pt, rawPointcloud1, "rawPointcloud1");
        m3d::typeSerialization::deserialize(pt, rawPointcloud2, "rawPointcloud2");

    }

    if (action->objectName() =="actionSave_m3dUnit_config")
    {
        QString fileName = QFileDialog::getSaveFileName(this,
                 tr("Open XML File 1"), "/home", tr("Config (*.xml)"));
        if (fileName.size()==0) return;

        boost::property_tree::ptree pt;

        boost::property_tree::ptree m3dConfig;

        boost::property_tree::ptree adresses;

        adresses.add("frontLaser","0.0.0.0");
        adresses.add("rotLaser",_scanWindow.getIpRotLaser());
        adresses.add("unit",_scanWindow.getIpUnit());


        m3dConfig.add_child("adresses", adresses);
        m3d::typeSerialization::serialize(m3dConfig, calib, "calibration");
        pt.add_child("m3dUnitDriver", m3dConfig);

#ifdef _WIN32
		//no pretty print on windows - bug in BOOST??
		boost::property_tree::write_xml(fileName.toStdString(), pt);
#else
        boost::property_tree::xml_writer_settings<char> settings('\t', 1);
        boost::property_tree::write_xml(fileName.toStdString(), pt, std::locale(), settings);
#endif
    }
    myGlWidget* gl = dynamic_cast<myGlWidget*>(ui->widget);
    gl->setPoincloud(&pc1,&pc2);
    UpdatePC();
}
void MainWindow::UpdatePC ()
{
    setMatrix();
    qDebug()<<"updating pc";
    pc1.data.clear();
    pc2.data.clear();

    for (int j=0; j<rawPointcloud1.angles.size(); j++)
    {
        float ang = rawPointcloud1.angles[j];
        glm::mat4 affine3Dunit = glm::rotate(glm::mat4(1.0f), ang, glm::vec3(0.0f, 0.0f, 1.0f));
        lms_measurement* meas = &(rawPointcloud1.ranges[j]);
        for (int i =0; i < meas->echoes[0].data.size(); i++)
        {
            float d =   meas->echoes[0].data[i]*meas->echoes[0].scallingFactor;
            float lasAng = float(1.0*i *( meas->echoes[0].angStepWidth)  -135.0f);

            glm::vec4 in (d, 0.0, 0.0f, 1.0f);
            glm::mat4 affineLaser = glm::rotate(glm::mat4(1.0f), glm::radians(lasAng),glm::vec3(0.0f, 0.0f, 1.0f));
            //glm::mat4 calib = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, -50.0f));
            glm::mat4 cor = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f),glm::vec3(0.0f, 1.0f, 0.0f));

            //glm::mat4 dAffine = glm::matrixCompMult(affineLaser, affine);
            glm::vec4 out =affine3Dunit* cor* calib* affineLaser * in;
            pc1.data.push_back(glm::vec3(out));
            //if (lit->profile.rssis.size()>0)collectingPointCloud.intensity.push_back( lit->profile.rssis[0].data[i]);
        }
    }
    for (int j=0; j<rawPointcloud2.angles.size(); j++)
    {
        float ang = rawPointcloud2.angles[j];
        glm::mat4 affine3Dunit = glm::rotate(glm::mat4(1.0f), ang, glm::vec3(0.0f, 0.0f, 1.0f));
        lms_measurement* meas = &(rawPointcloud2.ranges[j]);
        for (int i =0; i < meas->echoes[0].data.size(); i++)
        {
            float d =   meas->echoes[0].data[i]*meas->echoes[0].scallingFactor;
            float lasAng = float(1.0*i *( meas->echoes[0].angStepWidth)  -135.0f);

            glm::vec4 in (d, 0.0, 0.0f, 1.0f);
            glm::mat4 affineLaser = glm::rotate(glm::mat4(1.0f), glm::radians(lasAng),glm::vec3(0.0f, 0.0f, 1.0f));
            //glm::mat4 calib = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, -50.0f));
            glm::mat4 cor = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f),glm::vec3(0.0f, 1.0f, 0.0f));

            //glm::mat4 dAffine = glm::matrixCompMult(affineLaser, affine);
            glm::vec4 out =affine3Dunit* cor* calib* affineLaser * in;
            pc2.data.push_back(glm::vec3(out));
            //if (lit->profile.rssis.size()>0)collectingPointCloud.intensity.push_back( lit->profile.rssis[0].data[i]);
        }
    }
}

void MainWindow::setMatrix()
{
    float x = ui->doubleSpinBox_X->value();
    float y = ui->doubleSpinBox_Y->value();
    float z = ui->doubleSpinBox_Z->value();
    float yaw = ui->doubleSpinBox_yaw->value();
    float roll = ui->doubleSpinBox_roll->value();
    float pitch = ui->doubleSpinBox_pitch->value();
    setCalib(x,y,z,yaw,pitch,roll);

}

void MainWindow::setCalib(float x,float y, float z, float yaw,float pitch, float roll)
{

    calib =  glm::translate(glm::eulerAngleYXZ(yaw,pitch,roll), glm::vec3(x,y,z));
    qDebug()<<calib[0][0]<<calib[0][1]<<calib[0][2]<<calib[0][3];
    qDebug()<<calib[1][0]<<calib[1][1]<<calib[1][2]<<calib[1][3];
    qDebug()<<calib[2][0]<<calib[2][1]<<calib[2][2]<<calib[2][3];
    qDebug()<<calib[3][0]<<calib[3][1]<<calib[3][2]<<calib[3][3];

}
