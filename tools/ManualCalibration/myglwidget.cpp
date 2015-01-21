#include "myglwidget.h"
#include <QTime>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
myGlWidget::myGlWidget(QWidget *parent) : QGLWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1);


    translate_z=-50.0f;
    rotate_x=-90.0f;
    rotate_y=85.0f;
    calibMatrix = glm::mat4();
    pc1 = NULL;
    pc2 = NULL;


}
myGlWidget::~myGlWidget()
{

}

void myGlWidget::initializeGL()
{
    this->setMouseTracking(true);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_TEXTURE_2D);
}


void myGlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1,1,1, 1.0);

    glViewport(0, 0, width(), height());

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    gluPerspective(60, width()/float(height()), 100, 100000.0);

    glTranslatef(0.0, 0.0, translate_z);
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 0.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1,1,1);

    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(100,0,0);

    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,100,0);

    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,100);
    glEnd();
if (pc1 != NULL)
{



    glBegin(GL_POINTS);
    glColor3f(1,0,0);
        for (int i =0; i < pc1->data.size(); i++)
        {
            glVertex3f(pc1->data[i][0],pc1->data[i][1],pc1->data[i][2]);
        }

    glColor3f(0,0,1);
        for (int i =0; i < pc2->data.size(); i++)
        {
            glVertex3f(pc2->data[i][0],pc2->data[i][1],pc2->data[i][2]);
        }
    glEnd();
}
}


void myGlWidget::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug()<< "sssss";
    int dx=event->x()-lastPos.x();
    int dy=event->y()-lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        rotate_x+=dy*0.2f;
        rotate_y+=dx*0.2f;
    }
    else
    {
        if (event->buttons() & Qt::RightButton)
        {
            float d=0.01f*translate_z;
            if(d>-0.0001)
                d=-0.0001;
            translate_z+=dy*d;
        }
    }
    lastPos=event->pos();

}

void myGlWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos=event->pos();
    if (event->buttons() & Qt::LeftButton)
    {

    }

}
