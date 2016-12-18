#include <windows.h>
#include <stdlib.h>
#include <glut.h>

GLfloat spin;
int singleb, doubleb;

void displayd()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glRectf(-25.0, -25.0, 25.0, 25.0);
    glutSwapBuffers();
}

void displays()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glRectf(-25.0, -25.0, 25.0, 25.0);
    glFlush();
}

void spin_display()
{
    spin += 2.0;
    if (spin == 360)
        spin = 0;
    glutSetWindow(singleb);
    glLoadIdentity();
    glRotatef(spin, 0.0, 0.0, 1.0);
    glutPostRedisplay();
    glutSetWindow(doubleb);
    glLoadIdentity();
    glRotatef(spin, 0.0, 0.0, 1.0);
    glutPostRedisplay();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glShadeModel(GL_FLAT);
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        glutIdleFunc(spin_display);
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        glutIdleFunc(NULL);
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-25.0, 25.0, -25.0, 25.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    singleb = glutCreateWindow("Simgle Buffered");
    init();
    glutDisplayFunc(displays);
    glutReshapeFunc(reshape);
    glutIdleFunc(spin_display);
    glutMouseFunc(mouse);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    doubleb = glutCreateWindow("Double Buffered");
    init();
    glutDisplayFunc(displayd);
    glutReshapeFunc(reshape);
    glutIdleFunc(spin_display);
    glutMouseFunc(mouse);

    glutMainLoop();
}
