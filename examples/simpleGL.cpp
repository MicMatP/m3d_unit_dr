
#include <GL/glut.h>
#include <boost/thread/mutex.hpp>
#include <boost/date_time.hpp>
#include <3dUnitDriver.hpp>
#include <3dUnitTypeSerialization.hpp>
#include <fstream>
#define KEY_ESCAPE 27

#define _SCALE 1
#define _ROTATE 2
bool saveRequestTXT = false;
bool saveRequestRAW = false;

#define _GLUT_MENU_TXT 1
#define _GLUT_MENU_RAW 2
#define _GLUT_MENU_RAWTXT 3
#define _GLUT_MENU_PAUSE 4
#define _GLUT_MENU_RENEW 5

m3d::_3dUnitConfig cfg;

bool makingMeasurment = false;
bool newPointCloud = false;
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
m3d::pointcloud pc;
boost::mutex pcMutex;
float backGrounColor[3];
m3d::_3dUnitDriver* driver;
float _3dUnitSpeed =20;

enum _PC_COLOR
{
	_PC_COLOR1,_PC_COLOR2,_PC_COLOR3
};
_PC_COLOR color = _PC_COLOR1;

std::string getDateTimeFileName()
{
	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
	return cfg.outputPath+"/scan"+boost::posix_time::to_iso_string(now);
}
void colorize(float in, float max)
{
	float _in = in/max;
	if (_in>1.0f) _in =1.0f;
	if (color == _PC_COLOR1) glColor3f (0, _in ,_in);
	if (color == _PC_COLOR2) glColor3f (_in, 0 ,1);
	if (color == _PC_COLOR3) glColor3f (_in,0.6 ,0);

}


void savePointcloud()
{
	if (saveRequestTXT)
	{
		glutSetWindowTitle("saving...");
		saveRequestTXT = false;
		std::ofstream ofile;
		std::string fn = getDateTimeFileName()+".txt";
		ofile.open(fn.c_str());
		if (ofile.is_open()) std::cout <<"file is opened "<< fn<<"\n";
		for (int i=0; i < pc.data.size(); i++)
		{
			ofile << -0.001*pc.data[i].x<<"\t"<<0.001*pc.data[i].y<<"\t"<<0.001*pc.data[i].z;
			if (pc.intensity.size() == pc.data.size()) {ofile<<"\t"<<pc.intensity[i];};
			ofile<<"\n";
		}
		std::cout <<"saved\n";
		ofile.close();
		glutSetWindowTitle("done!");
	}
	if (saveRequestRAW)
	{
		glutSetWindowTitle("saving...");
		saveRequestRAW =false;
		std::cout << "getting raw pointcloud \n";
		m3d::rawPointcloud raw;
		driver->getRawPointCloud(raw);

		std::string fn = getDateTimeFileName()+".meas";
		std::cout << "raw pointcloud saving to "<<fn<<"\n";
		ptree pt;
		std::cout << "serializing \n";
		m3d::typeSerialization::serialize(pt,raw, "raw1");
		std::cout << "saving \n";

		write_xml(fn, pt);
		std::cout << "DONE! \n";
		glutSetWindowTitle("done!");
	}
	if (driver->get_is_initialized())driver->deinitialize();
}
void display() 
{
	if (makingMeasurment)
	{
		glClearColor(1.0f, 0.1f, 0.0f, 0.0f);
	}
	else
	{
		glClearColor(0.95f, 0.95f, 0.95f, 0.0f);
	}
	if (newPointCloud && makingMeasurment) 
	{
		savePointcloud();
		makingMeasurment = false;
	}
	newPointCloud=false;
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


	std::string actualprogress = boost::lexical_cast<std::string,int>(100*driver->getCurrentProgress());
	actualprogress = "actual progress "+actualprogress+"%";
	if (!driver->get_is_initialized()) actualprogress = "SENSOR PAUSED";
	glutSetWindowTitle(actualprogress.c_str());
	glPointSize(pointSize);
	
	newPointCloud = false;
	glBegin(GL_POINTS);
	pcMutex.lock();
	for (int i=0; i < pc.data.size(); i++)
	{
		if (pc.intensity.size() == pc.data.size()) colorize(pc.intensity[i],500);
		glVertex3f(pc.data[i].x,pc.data[i].z,pc.data[i].y);
	}
	
	pcMutex.unlock();
	glEnd();
	glPopMatrix();										  


	glutSwapBuffers();
}

void i_display(int)
{
	
	display();
	glutTimerFunc(250, i_display, 0);
}

void mouseMove(int x, int y) {

	if (vPortAct == _ROTATE)
	{
		float dx = lastX-x;
		float dy = lastY-y;
		_rotX +=-dx*0.2;
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
	display();
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
	display();
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
	driver->getPointCloud(pc);
	newPointCloud = true;
	// we unlock data
	pcMutex.unlock();
}

void keyboard ( unsigned char key, int mousePositionX, int mousePositionY )		
{ 
	switch ( key ) 
	{
	case KEY_ESCAPE: 
		driver->deinitialize();
		delete driver;
		exit ( 0 );   
		break;
	case '1':
		color = _PC_COLOR1;
		break;
	case '2':
		color = _PC_COLOR2;
		break;
	case '3':
		color = _PC_COLOR3;
		break;
	case 'a':        
		_3dUnitSpeed += 2;
		driver->setSpeed(_3dUnitSpeed);
		break;    
	case 'z':        
		_3dUnitSpeed -= 2;
		driver->setSpeed(_3dUnitSpeed);
		break;  
	case 'q':        
		pointSize += 0.2;
		break;  
	case '=':
		scale +=0.02;
		if (scale <0) scale = (0);
		break;
	case '-':
		scale -=0.02;
		if (scale <0) scale = (0);
		break;
	case 'w':        
		pointSize -= 0.2;
		break;  
	case 's' :
		if (!driver->get_is_initialized())driver->initialize();
		driver->setSpeed(_3dUnitSpeed);
		boost::this_thread::sleep(boost::posix_time::millisec(500));
		driver->startOver();
		makingMeasurment = true;
		saveRequestTXT = true;
		saveRequestRAW = true;
		break;
	case 'r' :
		_rotX=0;
		_rotY=0;
		scale = 1.0;
		break;
	default:      
		break;
	}
	display();
}
void handle_menu(int i)
{
	std::cout <<i<<"\n";
	if (i == _GLUT_MENU_TXT)
	{
		saveRequestTXT = true;
	}
	if (i== _GLUT_MENU_RAW)
	{
		saveRequestRAW = true;
	}
	if (i == _GLUT_MENU_PAUSE)
	{
		driver->setSpeed(0);
		if (driver->get_is_initialized())driver->deinitialize();
	}
	if (i == _GLUT_MENU_RENEW)
	{

		if (!driver->get_is_initialized())driver->initialize();
		driver->setSpeed(_3dUnitSpeed);

	}

}
int main(int argc, char **argv) 
{
	// FreeGLUT STUFF
	{

		win.width = 640;
		win.height = 480;
		char title[] = "OpenGL/GLUT Example.";
		win.title = title;
		win.field_of_view_angle = 45;
		win.z_near = 1.0f;
		win.z_far = 500.0f;

		// initialize and run program
		glutInit(&argc, argv);                                     
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  
		glutInitWindowSize(win.width,win.height);			
		glutCreateWindow(win.title);			
		glutDisplayFunc(display);						
		//glutIdleFunc( display );						
		glutMouseFunc(mouseButton);
		glutKeyboardFunc( keyboard );
		glutCreateMenu(handle_menu);
		glutAddMenuEntry("save as TXT",_GLUT_MENU_TXT);
		glutAddMenuEntry("save as RAW_MEAS",_GLUT_MENU_RAW);
		glutAddMenuEntry("PAUSE",_GLUT_MENU_PAUSE);
		glutAddMenuEntry("RENEW",_GLUT_MENU_RENEW);

		glutAttachMenu(GLUT_MIDDLE_BUTTON);

		initialize();
	}

	//// m3d stuff

	//
	
	cfg.readConfigFromXML("3dUnitCfg.xml");
	driver = new m3d::_3dUnitDriver(cfg);
	// initialization of Mandala 3d unit
	driver->initialize();
	// rotation speed
	driver->setSpeed(_3dUnitSpeed);
	// subscribe pointcloud
	driver->requestPointcloud();
	//register method. This method is called from internal driver thread.
	//That means you have to provide way to synchronize data with your application

	driver->setCallbackPointCloud(pointcloudCallback);

	glutTimerFunc(250, i_display, 0);
	glutMainLoop();	
	driver->deinitialize();
	delete driver;
	return 0;
}
