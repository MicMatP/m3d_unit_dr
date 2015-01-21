#ifndef myglwidget_hpp
#define myglwidget_hpp
#include <QGLWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <GL/glu.h>
#include <3dUnitDriver.hpp>
class myGlWidget:public QGLWidget
{
    Q_OBJECT
public:
    myGlWidget(QWidget *parent);
    ~myGlWidget();
    void render();
    virtual void initializeGL();
    virtual void paintGL();
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    inline void  setPoincloud(m3d::pointcloud *pc1,m3d::pointcloud *pc2)
    {
        this->pc1 = pc1;
        this->pc2 = pc2;

    }

private:
    float translate_z,rotate_x,rotate_y;
    QPoint lastPos;
    m3d::pointcloud *pc1;
    m3d::pointcloud *pc2;
    glm::mat4 calibMatrix;
};
#endif
