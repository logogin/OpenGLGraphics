/*
*
*	'lights.c' - Lights and objects.
*	F1 - switch view, F10 - exit
*	'Left' and 'Right' keys - rotating around the scene
*
*/

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

void main(int, char**);
void init(void);
void display(void);
void arrows(int, int, int);
void idle(void);
void reshape(int, int);

int up_view = 0;

GLfloat look_at = 320., angle = 0.;

GLfloat light0_pos[] = {2., 2., 4., 1.};
GLfloat light0_ambient[] = {.5, .5., .5, 1.};
GLfloat light0_diffuse[] = {.5, .5, .5, 1.};
GLfloat light0_spec[] = {1., 1., 1., 1.};

GLfloat light1_pos[] = {0., 4., 0., 1.};
GLfloat light1_dir[] = {0., -4., 0., 0.};
GLfloat light1_ambient[] = {0., 1., 0., 1.};
GLfloat light1_diffuse[] = {0., 1., 0., 1.};
GLfloat light1_spec[] = {0., 1., 0., 1.};
GLfloat light1_cutoff = 10.;
GLfloat light1_exp = 2.;

GLfloat global_amb[] = {0.2, 0.2, 0.2, 1.};

GLfloat no_mat[] = {0., 0., 0., 1.};

GLfloat tab_amb_diff[] = {.5, .8, .5, 1.};
GLfloat tea_amb_diff[] = {.1, .1, 1., 1.};
GLfloat tea_spec[] = {1., 1., 1., 1.};
GLfloat tea_shine = 120.;
GLfloat ball_amb_diff[] = {.4, .1, .1, 1.};
GLfloat ball_spec[] = {.3, .3, .4, .2};
GLfloat ball_shine = 40;
GLfloat cube_amb_diff[] = {.4, .4, .4, 1.};
GLfloat cube_spec[] = {.3, .3, .3, .2};
GLfloat cube_shine = 10;
GLfloat cone_emiss[] = {.2, .8, .2, 1.};
GLfloat lamp_emiss[] = {1., 1., 1., 1.};

void main(int argc, char **argv)
{	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
    glutInitWindowPosition(10, 10);    
	glutCreateWindow("Lights");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutSpecialFunc(arrows);
    glutIdleFunc(idle);
	init();
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}

void init(void)
{	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_spec);

	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_spec);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_dir);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, light1_exp);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, light1_cutoff);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_amb);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glEnable(GL_LIGHTING);
}

void display(void)
{	register int i, j;
	float look_at_r = look_at*3.1415926/180.;
	glClearColor(0., 0., 0., 1.);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if(up_view)	gluLookAt(	0, 10., 0, 0., 0., 0.,
							-cos(look_at_r), 0., sin(look_at_r));
	else	gluLookAt(	10.*cos(look_at_r), 3., -10.*sin(look_at_r), 
						0., 0., 0., 0., 1., 0.);

	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_dir);
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, tab_amb_diff);
	glNormal3f(0., 1., 0.);
	for(i=0; i<200; i++)
	{	for(j=0; j<200; j++)
		{	glBegin(GL_POLYGON);
				glVertex3f(	-4.+8.*((float)(i))/200., -1.,
							-4.+8.*((float)(j))/200.);
				glVertex3f(	-4.+8.*((float)(i))/200., -1.,
							-4.+8.*((float)(j+1))/200.);
				glVertex3f(	-4.+8.*((float)(i+1))/200., -1.,
							-4.+8.*((float)(j+1))/200.);
				glVertex3f(	-4.+8.*((float)(i+1))/200., -1.,
							-4.+8.*((float)(j))/200.);
			glEnd();
	}	}
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, tea_amb_diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, tea_spec);
	glMaterialf(GL_FRONT, GL_SHININESS, tea_shine);

	glTranslatef(0., 0., 2.);
	glutSolidTeapot(1);

	glTranslatef(2.5, 0., -2.);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ball_amb_diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ball_spec);
	glMaterialf(GL_FRONT, GL_SHININESS, ball_shine);
	glutSolidSphere(.8, 40, 38);

	glTranslatef(-4, 0., -2.);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cube_amb_diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cube_spec);
	glMaterialf(GL_FRONT, GL_SHININESS, cube_shine);
	glutSolidCube(2.);

	glPopMatrix();
	glPushMatrix();
	glTranslatef(light1_pos[0], light1_pos[1], light1_pos[2]);
	glRotatef(-angle, 0., 1., 0.);
	glRotatef(180.*atan2(2.3, 4.)/3.1416, 0., 0., 1.);
	glRotatef(-90., 1., 0., 0.);
	glTranslatef(0., 0., -1.);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, no_mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.);
	glMaterialfv(GL_FRONT, GL_EMISSION, cone_emiss);
	glutSolidCone(.3, 1, 12, 10);

	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, lamp_emiss);
	glTranslatef(light0_pos[0], light0_pos[0], light0_pos[2]);
	glutSolidSphere(.1, 14, 14);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glFlush();
	glutSwapBuffers();
}

void arrows(int key, int x, int y)
{	float incr = 10.;
	if(glutGetModifiers() == GLUT_ACTIVE_SHIFT)	incr =1.;
	if(key == GLUT_KEY_LEFT)	look_at -= incr;
	if(key == GLUT_KEY_RIGHT)	look_at += incr;
	if(look_at < 0.)	look_at += 360.;
	if(look_at > 360.)	look_at -= 360.;
	if(key == GLUT_KEY_F10)		exit(1);
	if(key == GLUT_KEY_F1)		up_view = 1 - up_view;
}

void idle(void)
{	float angle_r;
	angle += 20.;
	if(angle < 0.)	angle += 360.;
	if(angle > 360.)	angle -= 360.;
	angle_r = angle*3.1415926/180.;
	light1_dir[0] = 2.3*cos(angle_r);
	light1_dir[2] = 2.3*sin(angle_r);
	glutPostRedisplay();
}

void reshape(int w, int h)
{	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);    
	glLoadIdentity();
	gluPerspective(60., (GLfloat) w/(GLfloat) h, 1, 20);
	glMatrixMode(GL_MODELVIEW);
}
