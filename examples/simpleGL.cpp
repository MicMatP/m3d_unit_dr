
#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header
#include <boost/thread/mutex.hpp>
#include <3dUnitDriver.hpp>
#define KEY_ESCAPE 27

#define _SCALE 1
#define _ROTATE 2


typedef struct {
    int width;
	int height;
	char* title;

	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;

glutWindow win;

float _rotX=0;
float _rotY=0;

int lastX=0;
int lastY=0;

int vPortAct =0;

float scale = 1.0;

float pointSize =4;
pointcloud pc;
boost::mutex pcMutex;

_3dUnitDriver driver;
float _3dUnitSpeed =20;



void colorize(float in, float max)
{
	float _in = in/max;
	_in = _in*3;
	if (_in>3) _in = 3;

	if (_in<1)	glColor3f(0,0,_in);
	if (_in>1 &&_in<2)	glColor3f(0,_in-1,1);
	if (_in>2&&_in<3)	glColor3f(_in-2,1,1);

}

void display() 
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		     
	glLoadIdentity();

	gluLookAt( 4,2,0, 0,0,0, 0,1,0);					  
 
 
	glPushMatrix();										
		glColor3f(1,0,0);
		glTranslatef(0,0,0);
		glRotatef(_rotY,0,0,1);
		glRotatef(_rotX,0,1,0);
		
		glScalef(0.01*scale, 0.01*scale,0.01*scale);
		glRotatef(90,0,1,0);

		// Draw the teapot
	    //glutSolidTeapot(1);
		glPointSize(pointSize);
		glBegin(GL_POINTS);
		pcMutex.lock();
		for (int i=0; i < pc.data.size(); i++)
		{
			if (pc.intensity.size() == pc.data.size()) colorize(pc.intensity[i],1000);
			glVertex3f(pc.data[i].x,pc.data[i].z,pc.data[i].y);
		}
		pcMutex.unlock();
		glEnd();
	glPopMatrix();										  
 
 
	glutSwapBuffers();
}
void mouseMove(int x, int y) {

if (vPortAct == _ROTATE)
{
	float dx = lastX-x;
	float dy = lastY-y;
	_rotX +=dx*0.2;
	_rotY +=dy*0.2;
	lastX = x;
	lastY = y;
}
if (vPortAct == _SCALE)
{
	float dx = lastX-x;
	float dy = lastY-y;
	scale +=dy*0.002;
	if (scale <0) scale = (0);
	lastX = x;
	lastY = y;
}
}

void mouseButton(int button, int state, int x, int y) {

	vPortAct =0;
	if (button == GLUT_LEFT_BUTTON) {
		lastX = x;
		lastY = y;
		vPortAct = _ROTATE;
		
	}
	if (button == GLUT_RIGHT_BUTTON) {
		lastX = x;
		lastY = y;
		vPortAct = _SCALE;
	}
}

void initialize () 
{
    glMatrixMode(GL_PROJECTION);												
    glViewport(0, 0, win.width, win.height);									
    glMatrixMode(GL_PROJECTION);												
    glLoadIdentity();															
    GLfloat aspect = (GLfloat) win.width / win.height;
	gluPerspective(60, aspect, win.z_near, win.z_far);		
	glMatrixMode(GL_MODELVIEW);													
	glutMotionFunc(mouseMove);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable (GL_DEPTH_TEST);
}

void pointcloudCallback()
{

	//we locks data to avoid multiple access.
	pcMutex.lock();
	// we read pointcloud
	driver.getPointCloud(pc);
	// we unlock data
	pcMutex.unlock();
}

void keyboard ( unsigned char key, int mousePositionX, int mousePositionY )		
{ 
  switch ( key ) 
  {
    case KEY_ESCAPE:        
      exit ( 0 );   
      break;    
	case 'a':        
		_3dUnitSpeed += 2;
		driver.setSpeed(_3dUnitSpeed);
      break;    
	case 'z':        
		_3dUnitSpeed -= 2;
		driver.setSpeed(_3dUnitSpeed);
      break;  
	 case 's':        
		pointSize += 0.2;
	
      break;    
	case 'x':        
		pointSize -= 0.2;
      break;    
    default:      
      break;
  }
}

int main(int argc, char **argv) 
{
	// FreeGLUT STUFF
	{
		win.width = 640;
		win.height = 480;
		win.title = "OpenGL/GLUT Example.";
		win.field_of_view_angle = 45;
		win.z_near = 1.0f;
		win.z_far = 500.0f;

		// initialize and run program
		glutInit(&argc, argv);                                     
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  
		glutInitWindowSize(win.width,win.height);			
		glutCreateWindow(win.title);			
		glutDisplayFunc(display);						
		glutIdleFunc( display );						
		glutMouseFunc(mouseButton);
		glutKeyboardFunc( keyboard );					
		initialize();
	}

	//// m3d stuff
	// initialization of Mandala 3d unit
	driver.initialize();
	// rotation speed
	driver.setSpeed(_3dUnitSpeed);
	// subscribe pointcloud
	driver.requestPointcloud();
	//register method. This method is called from internal driver thread.
	//That means you have to provide way to synchronize data with your application
	
	driver.setCallbackPointCloud(pointcloudCallback);


	glutMainLoop();							
	return 0;
}