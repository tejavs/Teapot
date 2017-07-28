#include <GL\glut.h>
#define RED 1
#define BLUE 2
#define GREEN 3
#define ORTHO 4

GLfloat xRotated, yRotated, zRotated;
GLdouble size = 1;
int mainwindow, subwindow;

void display()
{

	glMatrixMode(GL_MODELVIEW);
	// clear the drawing buffer.
	glClear(GL_COLOR_BUFFER_BIT);
	// clear the identity matrix.
	glLoadIdentity();
	// traslate the draw by z = -4.0
	// Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
	glTranslatef(-0.9, 0.2, -4.5);
	// Red color used to draw.
	//glColor3f(0.8, 0.5, 0.1);
	// changing in transformation matrix.
	// rotation about X axis
	glRotatef(xRotated, 1, 1.0, 0.0);
	// rotation about Y axis
	glRotatef(yRotated, 0.0, 1.0, 0.0);
	// rotation about Z axis
	glRotatef(zRotated, 0.0, 0.0, 0.0);
	// scaling transfomation 
	glScalef(0.9, 0.9, 0.9);
	// built-in (glut library) function , draw you a Teapot.
	glutSolidTeapot(size);
	// Flush buffers to screen
	
	glFlush();
	// sawp buffers called because we are using double buffering 
	 glutSwapBuffers();


}

void renderScenesw1()
{
	glutSetWindow(subwindow);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	/*gluLookAt(0, -2, 0,
		0, 0, 0,
		-0.9, -0.7, -4.5);*/
}

void reshapeFunc(int x, int y)
{
	if (y == 0 || x == 0) return;  //Nothing is visible then, so return
								   //Set a new projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Angle of view:40 degrees
	//Near clipping plane distance: 0.5
	//Far clipping plane distance: 20.0

	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
	

	glViewport(0, 0, x, y);  //Use the whole window for rendering
}


void processMenuEvents(int option)
{
	int x, y;
	switch (option)
	{
	case RED:
		glColor3f(1.0, 0.0, 0.0);
		break;
	case BLUE:
		glColor3f(0.0f, 0.0f, 1.0f);
		break;
	case GREEN:
		glColor3f(0.0f, 1.0f, 0.0f);
		break;
	case ORTHO:
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-2, 4, -1, 2, 1, 50);
		break;
	
	}

}
int createGLUTMenus()
{
	int menu;
	
	menu = glutCreateMenu(processMenuEvents);

		glutAddMenuEntry("red",RED);
		glutAddMenuEntry("blue",BLUE);
		glutAddMenuEntry("green", GREEN);
		glutAddMenuEntry("ortho",ORTHO);
		
		glutAttachMenu(GLUT_RIGHT_BUTTON);

		return menu;
}



void idleFunc(void)
{
	xRotated += 0.03;
	display();
}


int main(int argc, char **argv)
{
	//Initialize GLUT
	glutInit(&argc, argv);
	//double buffering used to avoid flickering problem in animation
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// window size
	glutInitWindowSize(1080, 720);
	// create the window 
	mainwindow = glutCreateWindow("Teapot Rotating Animation");
	glutDisplayFunc(display);
	glutReshapeFunc(reshapeFunc);
	glutIdleFunc(idleFunc);

	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	xRotated = yRotated = zRotated = 30.0;
	xRotated = 33;
	yRotated = 40;
	createGLUTMenus();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//Assign  the function used in events
	
	//Let start glut loop
	glutMainLoop();
	return 0;
}

