/*
*
*	Rotating cube. SINGLE and DOUBLE buffering (two windows).
*
*/

#include "glut.h"

GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
		{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, 
		{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

int directions = 1, directiond = 1, singleb, doubleb;


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
	glColor3f(1.,0.,0.);
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

void disp_cubes(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	make_cube();

	glFlush();
}

void disp_cubed(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	make_cube();

	glutSwapBuffers ();		// Swapping buffers

	glFlush();
}

void rotate(void)
{
	// rotating the cube while Idle
	// single
	glutSetWindow(singleb);
	glRotatef(0.5*directions, 1., 1., 1.);
    glutPostRedisplay();
	// double
	glutSetWindow(doubleb);
	glRotatef(0.5*directiond, 1., 1., 1.);
    glutPostRedisplay();
}

void directs(int button, int state, int x, int y)
{
	// changing the direction of the rotation according to 
	// the mouse button have been pressed (for SINGLE)

	if(button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN)
		directions = -1;
	if(button == GLUT_RIGHT_BUTTON  && state == GLUT_DOWN)
		directions = 1;
}

void directd(int button, int state, int x, int y)
{
	// changing the direction of the rotation according to 
	// the mouse button have been pressed (for DOUBLE)

	if(button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN)
		directiond = -1;
	if(button == GLUT_RIGHT_BUTTON  && state == GLUT_DOWN)
		directiond = 1;
}

void initial(void)
{
	// initialization
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	glOrtho(-2., 2., -2., 2., -2., 2.);
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	// First window - single buffered
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(200, 200);
	singleb = glutCreateWindow("SINGLE BUFFERED");
	glutDisplayFunc(disp_cubes);	// display callback function
	glutIdleFunc(rotate);		// idle callback function
	glutMouseFunc(directs);		// mouse callback function
	initial();

	// Second window - double buffered
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(250, 0);
	glutInitWindowSize(200, 200);
	doubleb = glutCreateWindow("DOUBLE BUFFERED");
	glutDisplayFunc(disp_cubed);	// display callback function
	glutIdleFunc(rotate);		// idle callback function
	glutMouseFunc(directd);		// mouse callback function
	initial();
	glutMainLoop();
}