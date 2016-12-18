//---------------------------------------------------------------------------

//#include <vcl.h>
//#pragma hdrstop

//#include "Gasket.h"

//---------------------------------------------------------------------------

//#pragma package(smart_init)
#include <windows.h>
#include <stdlib.h>
#include <glut.h>

typedef struct
{
    GLfloat x, y, z
}, point3d;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    //glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    point3d vertices[4] = {{0.0, 0.0, 0.0}, {250.0, 500.0, 100.0}, {500.0, 250.0, 250.0}, {250.0, 100.0, 250}};
    int i, j, k;
    int rand();
    float point[2] = {75.0, 50.0};
    glClear(GL_COLOR_BUFFER_BIT);
    for (k = 0; k < 5000; k++)
    {
        j = rand() % 3;
        point[0] = (point[0] + vertices[j][0]) / 2;
        point[1] = (point[1] + vertices[j][1]) / 2;

        glBegin(GL_POINTS);
        glVertex2fv(point);
        glEnd();
    }
    glFlush();
}
void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Sierpinski Gasket");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}
