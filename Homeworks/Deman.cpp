#include "glut.h"

GLfloat vertices[][3] = {{0., 0.5, 0.}, {-0.5, -0.5, 0.5}, {-0.5, -0.5, -0.5}, {0.5, -0.5, 0.5}, {0.5, -0.5, -0.5}};

int dur = 1;
void polygon(int a, int b, int c)
{
    glBegin(GL_POLYGON);
    glVertex3fv(vertices[a]);
    glVertex3fv(vertices[b]);
    glVertex3fv(vertices[c]);

    glEnd();
}

void make_Tethrahedron()
{
    glColor3f(1., 1., 1.);
    polygon(1, 3, 2);
    glColor3f(1., 0., 0.);
    polygon(1, 3, 7);
    glColor3f(0., 1., 0.);
    polygon(2, 3, 7);
    glColor3f(0., 0., 1.);
    polygon(1, 2, 6);
    glColor3f(0., 1., 1.);
    polygon(1, 3, 6);
}

void disp_Tethrahedron(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    make_Tethrahedron();

    glutSwapBuffers();

    glFlush();
}

void rotate(void)
{

    glRotatef(2. * dur, 1., 1., 1.);
    disp_Tethrahedron();
    glTranslatef(0.01, -0.01, 0.);
}

void mouse(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        dur = -1;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        dur = 1;
}

void Keyboard(unsigned char button, int x, int y)
{
    if (button == 'q' || button == 'Q')
        exit(1);
}

void initial()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3., 3., -3., 3., -3., 3.);
    glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(40, 40);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Tethrahedron");
    glutDisplayFunc(disp_Tethrahedron);
    glutIdleFunc(rotate);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(mouse);
    initial();
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}