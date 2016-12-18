/*
*
*	'solar_walk.c' - "sun" and "planets" (like 'solar.c').
*	Use arrow keys to walk around the scene.
*	Use F1-key to switch the plan on/off
*	Use F10-key to exit
*
*/
#include "glut.h"
#include <stdlib.h>
#include <math.h>

#define PI		   3.1415926
#define SPEED_M	    .3
#define SPEED_R	    .05

#define SUN_RADIUS 1.
#define SUN_SLICE1 20
#define SUN_SLICE2 16
#define PL1_RADIUS 0.15
#define PL1_SLICE1 8
#define PL1_SLICE2 6
#define PL1_DIST   1.3

#define PL2_RADIUS 0.3
#define PL2_SLICE1 10
#define PL2_SLICE2 8
#define PL2_DIST  -2.2

#define MN21_RADIUS 0.08
#define MN21_SLICE1 8
#define MN21_SLICE2 6
#define MN21_DIST   0.5

#define PL3_RADIUS 0.55
#define PL3_SLICE1 12
#define PL3_SLICE2 9
#define PL3_DIST   4.

#define MN31_RADIUS 0.07
#define MN31_SLICE1 8
#define MN31_SLICE2 6
#define MN31_DIST   0.63

#define MN32_RADIUS 0.1
#define MN32_SLICE1 8
#define MN32_SLICE2 6
#define MN32_DIST   0.69

#define MN33_RADIUS 0.1
#define MN33_SLICE1 8
#define MN33_SLICE2 6
#define MN33_DIST   0.72

void main(int, char**);
void display(void);
void plan(void);
void create_scene(void);
void idle(void);
void reshape(int, int);
void create_plan(void);
void arrows(int, int, int);

GLfloat eyex = 0., eyez = 10., azimuth = PI/2;

GLfloat year[] = {0., 0., 0., 0., 0., 0., 0.}, 
		day[] = {0., 0., 0., 0., 0., 0., 0.},
		inc_y[] = {.09, .13, .15, .09, -.1, .2, .15},
		inc_d[] = {.48, .17, .09, .05, .2, .15, .03};

int main_wnd, plan_wnd = 0;

void main(int argc, char **argv)
{	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
    glutInitWindowPosition(10, 10);    
	main_wnd = glutCreateWindow("Moving through the Solar system");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
    glutIdleFunc(idle);
	glutSpecialFunc(arrows);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}

void create_plan(void)
{	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	plan_wnd = glutCreateSubWindow(main_wnd, 0, 0, 150, 150);
	glutDisplayFunc(plan);
	glutIdleFunc(idle);
	glutSpecialFunc(arrows);
	glMatrixMode(GL_PROJECTION);    
	glLoadIdentity();
	glOrtho(-16., 16., -16., 16., -16., 16.);
	glMatrixMode(GL_MODELVIEW);
	glutSetWindow(main_wnd);
}

void display(void)
{	glClearColor(0., 0., 0., 1.);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(	eyex, 0., eyez,
				eyex + cos(azimuth), 0., eyez - sin(azimuth),
				0., 1., 0.);
	create_scene();
	glFlush();
	glutSwapBuffers();
}

void plan(void)
{	glClearColor(.4, .4, .4, 1.);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0., 10., 0., 0., 0., 0., 0., 0., -1.);
	create_scene();
	glColor3f(0., 0., 0.);
	glBegin(GL_LINE_LOOP);
		glVertex3f(-15., 0., -15.);
		glVertex3f(-15., 0., 15.);
		glVertex3f(15., 0., 15.);
		glVertex3f(15., 0., -15.);
	glEnd();

	glTranslatef(eyex, 0., eyez);
	glRotatef(180.*azimuth/PI - 90.,0., 1., 0.);
	glBegin(GL_LINES);
		glVertex3f(0., 0., 0.);
		glVertex3f(0., 0., 1.5);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex3f(0., 0., 0.);
		glVertex3f(-.5, 0., .7);
		glVertex3f(.5, 0., .7);
	glEnd();
	glFlush();
	glutSwapBuffers();
}

void create_scene(void)
{	glRotatef(10., 0., 0., 1.);

	glPushMatrix();
	glColor3f(1., 1., 0.5);
	glRotatef(day[0], 0., 1., 0.);
	glRotatef(90., 1., 0., 0.);
	glutWireSphere(SUN_RADIUS, SUN_SLICE1, SUN_SLICE2);
	glPopMatrix();

	glPushMatrix();
	glRotatef(year[0], 0., 1., 0.);
	glTranslatef(PL1_DIST, 0., 0.);
	glRotatef(day[0], 0., 1., 0.);
	glColor3f(1., 0., 0.6);
	glRotatef(90., 1., 0., 0.);
	glutWireSphere(PL1_RADIUS, PL1_SLICE1, PL1_SLICE2);
	glPopMatrix();

	glPushMatrix();
	glRotatef(year[1], 0., 1., 0.);
	glTranslatef(PL2_DIST, 0., 0.);
	glPushMatrix();
	glRotatef(day[1], 0., 1., 0.);
	glColor3f(0., 0., 1.);
	glRotatef(90., 1., 0., 0.);
	glutWireSphere(PL2_RADIUS, PL2_SLICE1, PL2_SLICE2);
	glPopMatrix();
   	glRotatef(year[2], 0., 0., 1.);
	glTranslatef(MN21_DIST, 0., 0.);
	glRotatef(day[2], 0., 1., 0.);
	glColor3f(1., 1., 1.);
	glRotatef(90., 1., 0., 0.);
	glutWireSphere(MN21_RADIUS, MN21_SLICE1, MN21_SLICE2);
	glPopMatrix();

	glPushMatrix();
	glRotatef(year[3], 0., 1., 0.);
	glTranslatef(PL3_DIST, 0., 0.);
	glPushMatrix();
	glRotatef(day[3], 0., 1., 0.);
	glColor3f(0., 1., 1.);
	glRotatef(90., 1., 0., 0.);
	glutWireSphere(PL3_RADIUS, PL3_SLICE1, PL3_SLICE2);
	glPopMatrix();
	
   	glPushMatrix();
	glRotatef(year[4], 0., 0., 1.);
	glTranslatef(MN31_DIST, 0., 0.);
	glRotatef(day[4], 0., 1., 0.);
	glColor3f(.8, .6, .3);
	glRotatef(90., 1., 0., 0.);
	glutWireSphere(MN31_RADIUS, MN31_SLICE1, MN31_SLICE2);
	glPopMatrix();

   	glPushMatrix();
	glRotatef(year[5], 0., 1., 0.);
	glTranslatef(MN32_DIST, 0., 0.);
	glRotatef(day[5], 0., 1., 0.);
	glColor3f(1., .7, .7);
	glRotatef(90., 1., 0., 0.);
	glutWireSphere(MN32_RADIUS, MN32_SLICE1, MN32_SLICE2);
	glPopMatrix();

   	glPushMatrix();
	glRotatef(year[6], 0., 0., 1.);
	glTranslatef(MN33_DIST, 0., 0.);
	glRotatef(day[6], 0., 1., 0.);
	glColor3f(.2, .2, 1.);
	glRotatef(90., 1., 0., 0.);
	glutWireSphere(MN33_RADIUS, MN33_SLICE1, MN33_SLICE2);
	glPopMatrix();
	glPopMatrix();
}

void idle(void)
{	register int i;
	for(i=0; i<7; i++)
	{	day[i] += inc_d[i];
		year[i] += inc_y[i];
		if(day[i] > 360.0) day[i] -= 360.0;
		if(day[i] < 0.0) day[i] += 360.0;
		if(year[i] > 360.0) year[i] -= 360.0;
		if(year[i] < 0.0) year[i] += 360.0;
	}
	glutSetWindow(main_wnd);
	glutPostRedisplay();
	if(plan_wnd)
	{	glutSetWindow(plan_wnd);
		glutPostRedisplay();
	}
	glutSetWindow(main_wnd);
}

void reshape(int w, int h)
{	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);    
	glLoadIdentity();
	gluPerspective(60., (GLfloat) w/(GLfloat) h, .1, 20.);
	glMatrixMode(GL_MODELVIEW);
}

void arrows(int key, int x, int y)
{	float spd_m = SPEED_M, spd_r = SPEED_R;
	if(glutGetModifiers() == GLUT_ACTIVE_SHIFT)
	{	spd_m *= .1;
		spd_r *= .1;
	}
	if(key == GLUT_KEY_UP) 
	{	eyex += spd_m*cos(azimuth);
		eyez -= spd_m*sin(azimuth);
	}
	if(key == GLUT_KEY_DOWN)
	{	eyex -= spd_m*cos(azimuth);
		eyez += spd_m*sin(azimuth);
	}
	if(key == GLUT_KEY_LEFT)	azimuth += spd_r;
	if(key == GLUT_KEY_RIGHT)	azimuth -= spd_r;
	if(azimuth > 2*PI) azimuth -= 2*PI;
	if(azimuth < 0.) azimuth += 2*PI;
	if(eyex < -15.)	eyex = -15.;
	if(eyex > 15.)	eyex = 15.;
	if(eyez < -15.)	eyez = -15.;
	if(eyez > 15.)	eyez = 15.;
	if(key == GLUT_KEY_F1)
	{	if(!plan_wnd)	create_plan();
		else
		{	glutDestroyWindow(plan_wnd);
			plan_wnd = 0;
	}	}
	if(key == GLUT_KEY_F10)	exit(1);
	glutSetWindow(main_wnd);
	glutPostRedisplay();
	if(plan_wnd)
	{	glutSetWindow(plan_wnd);
		glutPostRedisplay();
	}
	glutSetWindow(main_wnd);
}