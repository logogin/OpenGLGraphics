#include <windows.h>
#include <stdlib.h>
#include <glut.h>

//typedef GLfloat point3d[3];
int ww = 500, hh = 500;
void square(int x, int y)
{
    y = ww - y;
    glColor3ub(rand() % 256, rand() % 256, rand() % 256);
    glBegin(GL_POLYGON);
    glVertex2f(x + 3, y + 3);
    glVertex2f(x - 3, y + 3);
    glVertex2f(x - 3, y - 3);
    glVertex2f(x + 3, y - 3);
    glEnd();
    glFlush();
}
void display()
{
}
void myReshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, w, 0.0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay();
    glFlush();
    ww = w;
    hh = h;
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q')
        exit(0);
}
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        square(x, y);
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        exit(0);
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Boxes");
    // int id=glutCreateWindow("Second Window");
    // glutSetWindow(id);
    glutReshapeFunc(myReshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(square);
    glutDisplayFunc(display);
    // glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
