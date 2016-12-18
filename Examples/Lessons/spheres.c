/*
*
*	'spheres.c' - Light and spheres.
*
*	From left to right - specular component increases.
*	From bottom to up - ambient and diffuse components increase.
*	Three columns on the right-hand side has the same ambient,
*	diffuse and specular components, but different shininess,
*	which increases from left to right.
*
*	Alt+X - exit
*
*/

#include "glut.h"

void main(int, char**);
void init(void);
void display(void);
void keyboard(unsigned char, int, int);
void reshape(int, int);

//	Light parameters
GLfloat light0_pos[] = {1., 1., 1., 1.};//light position
GLfloat light0_dir[] = {1., 1., 1., 0.};//option of light
GLfloat light0_ambient[] = {.5, .5., .5, 1.};//
GLfloat light0_diffuse[] = {.5, .5, .5, 1.};//
GLfloat light0_spec[] = {1., 1., 1., 1.};//
GLfloat global_amb[] = {0.2, 0.2, 0.2, 1.};//

//	Material properties
GLfloat mat_ad[4][4] = {{0., 0., 0., 1.}, {.15, 0., .15, 1.},
					{.5, 0., .5, 1.}, {1., 0., 1., 1.} };
GLfloat mat_s[4][4] = {{0., 0., 0., 1.}, {.15, .15, .15, 1.},
					{.5, .5, .5, 1.}, {1., 1., 1., 1.} };
GLfloat shine[3] = { 5., 40., 120. };

void main(int argc, char **argv)
{	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 400);
    glutInitWindowPosition(10, 10);    
	glutCreateWindow("Lights");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	init();
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}

void init(void)
{	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
//	Try to use the next row instead of the previous one
//	glLightfv(GL_LIGHT0, GL_POSITION, light0_dir);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_spec);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_amb);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);    
	glLoadIdentity();
	glOrtho(-11., 19., -10., 10., 3., 7.);
	glMatrixMode(GL_MODELVIEW);
}

void display(void)
{	register int i, j;
	glClearColor(0., 0., 0., 1.);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	for(i=0; i<4; i++)
	{	for(j=0; j<4; j++)
		{	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ad[i]);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_s[j]);
			glMaterialf(GL_FRONT, GL_SHININESS, shine[0]);
			glTranslatef(-6. + (float)j*4., -6. + (float)i*4., -5.);
			glutSolidSphere(1., 16, 12);
			glLoadIdentity();
		}
		for(j=1; j<3; j++)
		{	glMaterialf(GL_FRONT, GL_SHININESS, shine[j]);
			glTranslatef(6. + (float)j*4., -6. + (float)i*4., -5.);
			glutSolidSphere(1., 16, 12);
			glLoadIdentity();
	}	}
	glFlush();
}

void keyboard(unsigned char key, int x, int y)
{	if((key == 'x' || key == 'X') && 
	   (glutGetModifiers() == GLUT_ACTIVE_ALT))	exit(1);
}

void reshape(int w, int h)
{	GLfloat aspect;
	aspect = (GLfloat) w/(GLfloat) h;
	if(aspect < 1.5) glViewport(0, 0, w, (int)(((float) w) / 1.5));
	else			 glViewport(0, 0, (int)(((float) h) * 1.5), h);
}
