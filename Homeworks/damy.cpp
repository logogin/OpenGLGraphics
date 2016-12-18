// damy.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "glut.h"

GLUquadricObj *galil;
GLUquadricObj *sphere;

float direction = 1.;
void disp_Sphere(void)
{

    glClearColor(1.0, 0.0, 0.0, 0.);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLineWidth(1);
    glPushMatrix();
    glTranslatef(0, 0.0, 0.0);
    glRotatef(0., 1., 0., 0.);
    glColor3f(-30., .67, 0.78);
    gluCylinder(galil, 0.5, 0.1, 10, 15, 15);
    glColor3f(-30., .67, 0.78);
    glTranslatef(0.0, 0.0, -2.0);
    gluSphere(sphere, 2., 20, 15);
    glPopMatrix();
    glutSwapBuffers();

    glFlush();
}
void rotate(void) // Idle
{

    glRotatef(0.5, 0., 1., 0.);
    glutSwapBuffers();
    glutPostRedisplay();
}

void myinit(void)
{
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-14., 14., -14., 14., -14., 14.);
    glMatrixMode(GL_MODELVIEW);
    glutSwapBuffers();
    glFlush();
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
    glutIdleFunc(rotate);
    myinit();
    galil = gluNewQuadric();
    sphere = gluNewQuadric();
    gluQuadricDrawStyle(galil, GLU_SILHOUETTE);
    gluQuadricDrawStyle(sphere, GLU_SILHOUETTE);
    gluQuadricTexture(galil, GL_FALSE);
    gluQuadricTexture(sphere, GL_FALSE);

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
