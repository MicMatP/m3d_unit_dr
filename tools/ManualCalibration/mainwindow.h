#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "scanwindow.h"
#include <QMainWindow>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    scanWindow _scanWindow;
    m3d::rawPointcloud rawPointcloud1;
    m3d::rawPointcloud rawPointcloud2;

    m3d::pointcloud pc1;
    m3d::pointcloud pc2;
    void setCalib(float x,float y, float z, float yaw,float pitch, float roll);
    glm::mat4 calib;
public slots:
    void onTrigger(QAction* action);
    void UpdatePC ();
    void setMatrix();


};

#endif // MAINWINDOW_H
