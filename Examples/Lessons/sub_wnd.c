/*
*
*	Subwindows example.
*	Use keys '1' and '2' to destroy subwindows,
*	key '0' - to destroy the parent window.
*
*/

#include <GL/glut.h>

GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
		{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, 
		{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

int directions = 1, directiond = 1, singleb, doubleb, parent;


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

void display(void)
{
	glClearColor(1., 1., 1., 1.);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void disp_cubes(void)
{

	glClearColor(0., 0., 0., 1.);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	make_cube();

	glFlush();
}

void disp_cubed(void)
{
	glClearColor(0., 0., 0., 1.);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	make_cube();

	glutSwapBuffers ();		// Swapping buffers

	glFlush();
}

void rotate(void)
{
	// rotating the cube while Idle
	// single
	if(singleb)
	{	glutSetWindow(singleb);
		glRotatef(0.5*directions, 1., 1., 1.);
		glutPostRedisplay();
	}
	// double
	if(doubleb)
	{	glutSetWindow(doubleb);
		glRotatef(0.5*directiond, 1., 1., 1.);
		glutPostRedisplay();
	&& state == GLUT_DOWN)
		directiond = -1;
	if(button == GLUT_RIGHT_BUTTON  && state == GLUT_DOWN)
		directiond = 1;
}

void kill_wnd(unsigned char key, int x, int y)
{
	if(key == '0')
	{	glutDestroyWindow(parent);
		exit(1);
	}
	if(key == '1')
	{	glutDestroyWindow(singleb);
		singleb = 0;
	}
	if(key == '2')
	{	glutDestroyWindow(doubleb);
		doubleb = 0;
	}
	display();
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

	// The main parent window
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	parent = glutCreateWindow("The Parent Window");
	glutDisplayFunc(display);	// display callback function
	glutKeyboardFunc(kill_wnd);	// kyboard callback

	// First subwindow - single buffered
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	singleb = glutCreateSubWindow(parent, 0, 0, 200, 200);
	glutDisplayFunc(disp_cubes);// display callback function
	glutIdleFunc(rotate);		// idle callback function
	glutMouseFunc(directs);		// mouse callback function
	glutKeyboardFunc(kill_wnd);	// kyboard callback
	initial();

	// Second subwindow - double buffered
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	doubleb = glutCreateSubWindow(parent, 250, 0, 200, 200);
	glutDisplayFunc(disp_cubed);// display callback function
	glutIdleFunc(rotate);		// idle callback function
	glutMouseFunc(directd);		// mouse callback function
	glutKeyboardFunc(kill_wnd);	// kyboard callback
	initial();
	glutMainLoop();
}

