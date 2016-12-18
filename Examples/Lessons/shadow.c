/* 
* 
*	'shadow.c' - this simple program creates the shadow
*	on the plane.
* 
*/

#include "glut.h" 
#include <stdlib.h>

//	projection matrix used to shadow the object
float proj_m[16] = {	1., 0., 0., 0.,		0., 1., 0., -.2,      //matrix
						0., 0., 1., 0.,		0., 0., 0., 0.};

void scene(void)                        //triangle
{	glBegin(GL_TRIANGLES);
		glVertex3i(1,1,1);
		glVertex3i(2,2,3);
		glVertex3i(3,1,2);
	glEnd();
}

void table(void)                               //mishor
{	glColor3f(0., 1., 0.);
	glBegin(GL_QUADS);
		glVertex3i(-2, 0, -2);
		glVertex3i(-2, 0, 7);
		glVertex3i(7, 0, 7);
		glVertex3i(7, 0, -2);
	glEnd();
}

void display(void)
{	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(-3., .1, 0., 0., -1., 1., 0., 1., 0.);     //nikudat mabat
	table();                                             //mishor   
	glColor3f(1., 0., 1.);
	scene();
 
//for sphere  (makor aor)
	glTranslatef(2., 5., 0.);
	glColor3f(1., 1., 0.);
	glutWireSphere(.15, 6, 6);

//for shadow	
	glMultMatrixf(proj_m);
	glTranslatef(-2., -5., 0.);
	glColor3f(0., 0., 1.);
	scene();

    glFlush();
}

void myinit() 
{	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-6., 8., 0., 7., -15., 15.);
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char **argv) 
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("shadow");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
}

