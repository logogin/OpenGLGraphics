/*
*
*	Rotating cube. DOUBLE buffering.
*
*/

#include "glut.h"


GLfloat vertices[][3] = {{-0.5,-0.5,-1.0},{0.5,-0.5,-1.0},
		{0.5,0.5,-0.5}, {-0.5,0.5,-0.5}, {-0.5,-0.5,0.5}, 
		{0.5,-0.5,0.5}, {0.5,0.5,1.0}, {-0.5,0.5,1.0}};

int direction = 1;


void polygon(int a, int b, int c , int d)
{
	glBegin(GL_POLYGON);
		glVertex3fv(vertices[a]);
		glVertex3fv(vertices[b]);
		glVertex3fv(vertices[c]);
		glVertex3fv(vertices[d]);
	glEnd();
}

void make_cube()
{
	glColor3f(1.,1.,1.);
	polygon(0,3,2,1);
	glColor3f(1.,1.,0.);
	polygon(2,3,7,6);
	glColor3f(0.,1.,0.);
	polygon(0,4,7,3);
	glColor3f(0.,1.,1.);
	polygon(1,2,6,5);
	glColor3f(0.,0.,1.);
	polygon(4,5,6,7);
	glColor3f(1.,0.,1.);
	polygon(0,1,5,4);
	
}

void disp_cube(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	make_cube();

	glutSwapBuffers ();		// Swapping buffers

	glFlush();
}

void rotate(void)
{
	// rotating the cube while Idle

	glRotatef(2.*direction, 1., 1., 1.);
	disp_cube();
}

void Keyboard(unsigned char button, int x, int y)
{
	
if(button=='q' || button=='Q')
exit(1);
}

void mouse(int button,int state, int x, int y)
{
	// changing the direction of the rotation according to 
	// the mouse button have been pressed

if(button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN)
		direction = -1;
	if(button == GLUT_LEFT_BUTTON  && state == GLUT_UP)
		direction = 1;
}
void initial(void)
{
	// initialization

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	glOrtho(-2., 2., -2., 2., -2., 2.);
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	// We include new option: GLUT_DOUBLE for double buffering
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(20, 20);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Rotating cube - Double buffering");
	glutDisplayFunc(disp_cube);	// display callback function
//	glutIdleFunc(rotate);		// idle callback function
	//glutKeyboardFunc(Keyboard);		// mouse callback function
	//glutMouseFunc(mouse);
	initial();
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}

