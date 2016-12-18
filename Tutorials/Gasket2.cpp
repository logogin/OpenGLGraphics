#include <windows.h>
#include <stdlib.h>
#include <glut.h>

typedef struct
{
    GLfloat x, y, z;
} point3d;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    //glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-500.0, 500.0, 0.0, 500.0, -500.0, 500);
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    point3d vertices[4] = {{0.0, 0.0, -450.0}, {-450.0, 0.0, 450.0}, {450.0, 0.0, 450.0}, {0.0, 450.0, 0.0}};
    int rand();
    point3d point = {250.0, 100.0, 250.0};
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < 5000; i++)
    {
        randomize();
        int k = rand() % 4;
        point.x = (point.x + vertices[k].x) / 2;
        point.y = (point.y + vertices[k].y) / 2;
        point.z = (point.z + vertices[k].z) / 2;

        glBegin(GL_POINTS);
        glColor3f(1.0 - point.z / 250, point.z / 250, 0.0);
        glVertex3f(point.x, point.y, point.z);
        glEnd();
    }
    glFlush();
}
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON & state == GLUT_DOWN)
        glutIdleFunc(display);

    if (button == GLUT_MIDDLE_BUTTON & state == GLUT_DOWN)
        glutIdleFunc(NULL);

    if (button == GLUT_RIGHT_BUTTON & state == GLUT_DOWN)
        exit(0);
}
void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Sierpinski Gasket");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
}
