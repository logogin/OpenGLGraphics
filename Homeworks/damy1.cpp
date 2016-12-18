// damy.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "glut.h"
#define BASE_HEIGHT 2.0
#define BASE_RADIUS 1.0

static GLfloat theta[] = {0.0, 0.0, 0.0, 0.0};

static GLint axis = 0;

GLUquadricObj *galil;
GLUquadricObj *sphere;

float direction = 1.;

void base()
{
    glPushMatrix();
    /* rotate cylinder to align with y axis */
    glRotatef(0.0, 0.0, 0.0, 1.0);
    /* cyliner aligned with z axis, render with
    5 slices for base and 5 along length */
    gluCylinder(galil, 0.5, 0.0, 10, 5, 5);
    glPopMatrix();
}

void disp_Sphere(void)
{

    glClearColor(1.0, 0.0, 0.0, 0.);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLineWidth(1);
    glPushMatrix();
    /*glTranslatef(0,0.0,0.0);
glRotatef(0.,1.,0.,0.);
glColor3f(-30.,.67,0.78);
gluCylinder(galil,0.5,0.1,10,15,15);*/
    glColor3f(-30., .67, 0.78);
    glTranslatef(0.0, 0.0, 0.0);
    gluSphere(sphere, 2., 20, 15);
    glPopMatrix();
    glutSwapBuffers();

    glFlush();
}
void rotate(void) // Idle
{

    glRotatef(0.5, 1., 0., 0.);
    glutSwapBuffers();
    glutPostRedisplay();
}

void display(void)
{
    /* Accumulate ModelView Matrix as we traverse tree */
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0, 0.0, 1.0);

    glRotatef(theta[0], 0.0, 1.0, 0.0);
    base();

    glTranslatef(0.0, BASE_HEIGHT, 0.0);
    glRotatef(theta[1], 0.0, 0.0, 1.0);
    disp_Sphere();

    glFlush();
    glutSwapBuffers();
}

void ds_key(unsigned char ch, int x, int y)
{
    /* 'l' increase joint angle, 'r' decreases it */
    if (ch == 'L' || ch == 'l')
    {
        theta[axis] += 5.0;
        if (theta[axis] > 360.0)
            theta[axis] -= 360.0;
    }
    if (ch == 'R' || ch == 'r')
    {
        theta[axis] -= 5.0;
        if (theta[axis] < 0.0)
            theta[axis] += 360.0;
    }
    display();
}

void myinit(void)
{
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-14., 14., -14., 14., -14., 14.);
    glMatrixMode(GL_MODELVIEW);
    glutSwapBuffers();
    glFlush();
    /*	glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-10.0, 10.0, -5.0 * (GLfloat) h / (GLfloat) w,
        15.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-10.0 * (GLfloat) w / (GLfloat) h,
        10.0 * (GLfloat) w / (GLfloat) h, -5.0, 15.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); }*/
}
void menu(int id)
{
    /* menu selects which angle to change or whether to quit */
    if (id == 1)
        axis = 0;
    if (id == 2)
        exit(1);
}

void main(int argc, char *argv[])
{

    float pos[4] = {3, 3, 3, 3};
    float dir[3] = {3, 3, 3};

    GLfloat mat_specular[] = {10, 10, 10, 10};

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(250, 0);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Sphere");
    glutDisplayFunc(disp_Sphere);
    glutDisplayFunc(base);
    glutIdleFunc(rotate);
    glutKeyboardFunc(ds_key);
    myinit();
    galil = gluNewQuadric();
    sphere = gluNewQuadric();
    gluQuadricDrawStyle(galil, GLU_SILHOUETTE);
    gluQuadricDrawStyle(sphere, GLU_SILHOUETTE);
    gluQuadricTexture(galil, GL_FALSE);
    gluQuadricTexture(sphere, GL_FALSE);

    glutCreateMenu(menu);
    glutAddMenuEntry("base", 1);
    glutAddMenuEntry("quit", 2);
    glutAttachMenu(GLUT_LEFT_BUTTON);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT4, GL_POSITION, pos);
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dir);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);

    glutMainLoop();
}
