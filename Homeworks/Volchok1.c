/*
COURSE:		Computer Graphics
HW2:		Sahin Yakov
*/
#include <stdio.h>
#include "glut.h"

GLUquadricObj *galil; //defenition of galil

void Keymenu(unsigned char c, int x, int y);

GLfloat vertices[][3] = {{-2.0, -2.0, -2.0}, {2.0, -2.0, -2.0}, {2.0, 2.0, -2.0}, {-2.0, 2.0, -2.0}, {-2.0, -2.0, 2.0}, {2.0, -2.0, 2.0}, {2.0, 2.0, 2.0}, {-2.0, 2.0, 2.0}, {0.0, -5.0, 0.0},
                         ///////////////////////[GIMEL]/////////////////////////////////
                         {-1.0, 1.0, 2.2},
                         {0.0, 1.0, 2.2},
                         {0.0, 0.5, 2.2},
                         {-1.0, 0.5, 2.2},
                         {1.0, -1.0, 2.2},
                         {0.5, -1.0, 2.2},
                         {0.25, 0.0, 2.2},
                         {0.32, -0.25, 2.2},
                         {-1.0, -1.0, 2.2},
                         {-0.5, -1.0, 2.2},
                         ///////////////////////[PEI]//////////////////////////////////
                         {-1.0, 1.0, -2.2},
                         {-1.0, 0.4, -2.2},
                         {1.0, 1.0, -2.2},
                         {1.0, 0.4, -2.2},
                         {-1.0, -1.0, -2.2},
                         {-0.4, -1.0, -2.2},
                         {-0.4, 1.0, -2.2},
                         /*23*/ {-1.0, -0.7, -2.2},
                         {1.0, -0.7, -2.2},
                         {1.0, -1.0, -2.2},
                         /*28*/ {1.0, -1.0, -2.2},
                         {1.0, 0.0, -2.2},
                         {0.7, 0.0, -2.2},
                         {0.7, 1.0, -2.2},
                         /////////////////////////[NUN]/////////////////////////////////
                         /*33*/ {2.2, 0.25, -1.0},
                         {2.2, -1.0, -0.9},
                         {2.2, -1.0, -0.7},
                         {2.2, 0.25, -0.7},
                         /*37*/ {2.2, -1.0, 1.0},
                         {2.2, -0.7, 1.0},
                         {2.2, -0.7, -0.98},
                         /*40*/ {2.2, 0.0, -1.0},
                         {2.2, 0.0, -0.5},
                         {2.2, 0.25, -0.5},
                         /////////////////////////[HEI]////////////////////////////////
                         /*43*/ {-2.2, 1.0, 1.0},
                         {-2.2, 0.7, 1.0},
                         {-2.2, 0.7, -1.0},
                         {-2.2, 1.0, -1.0},
                         /*47*/ {-2.2, -1.0, 1.0},
                         {-2.2, -1.0, 0.5},
                         {-2.2, 1.0, 0.5},
                         /*50*/ {-2.2, 0.0, -0.5},
                         {-2.2, -1.0, -0.5},
                         {-2.2, -1.0, -1.0},
                         {-2.2, 0.0, -1.0}};

float directions = 1., directiond = 1.;
int singlebuf, doublebuf;
int WindW, WindH;

void draw_string_stroke(void *font, const char *string) //Fonts draw
{
    while (*string)
        glutStrokeCharacter(font, *string++);
}

void polygon(int a, int b, int c, int d)
{
    glBegin(GL_POLYGON);
    glVertex3fv(vertices[a]);
    glVertex3fv(vertices[b]);
    glVertex3fv(vertices[c]);
    glVertex3fv(vertices[d]);
    glEnd();
}

void make_cube()
{
    glColor3f(1., 0., 0.);
    polygon(0, 3, 2, 1);
    glColor3f(1., 1., 0.);
    polygon(2, 3, 7, 6);
    glColor3f(0., 1., 0.);
    polygon(0, 4, 7, 3);
    glColor3f(0., 1., 1.);
    polygon(1, 2, 6, 5);
    glColor3f(0., 0., 1.);
    polygon(4, 5, 6, 7);
    glColor3f(1., 0., 1.);
    polygon(0, 1, 5, 4);

    ////////////////////////////////////////
    glColor3f(1., 0., 0.); //nun
    polygon(33, 34, 35, 36);
    glColor3f(1., 0., 0.);
    polygon(34, 37, 38, 39);
    glColor3f(1., 0., 0.);
    polygon(33, 40, 41, 42);
    ////////////////////////////////////////
    glColor3f(0., 1., 0.); //gimel
    polygon(9, 10, 11, 12);
    glColor3f(0., 1., 0.);
    polygon(10, 11, 13, 14);
    glColor3f(0., 1., 0.);
    polygon(15, 16, 17, 18);
    ////////////////////////////////////////
    glColor3f(1., 1., 1.); //hei
    polygon(43, 44, 45, 46);
    glColor3f(1., 1., 1.);
    polygon(43, 47, 48, 49);
    glColor3f(1., 1., 1.);
    polygon(50, 51, 52, 53);
    ////////////////////////////////////////
    glColor3f(0., 0., 1.); //pei
    polygon(19, 20, 21, 22);
    glColor3f(0., 0., 1.);
    polygon(19, 23, 24, 25);
    glColor3f(0., 0., 1.);
    polygon(23, 26, 27, 28);
    glColor3f(0., 0., 1.);
    polygon(21, 30, 31, 32);

    glColor3f(1.0, 0.0, 0.0); // color of konys
    polygon(0, 8, 1, 0);
    glColor3f(0.0, 1.0, 1.0);
    polygon(1, 8, 5, 1);
    glColor3f(0.0, 0.0, 1.0);
    polygon(8, 5, 4, 8);
    glColor3f(0.0, 1.0, 0.0);
    polygon(4, 0, 8, 4);
    glColor3f(1.0, 1.0, 1.0);
    polygon(9, 10, 11, 12);

    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(-90., 1., 0., 0.);
    glColor3f(0.0, 0.78, 0.78);
    gluCylinder(galil, 0.9, 0.9, 4, 30, 30);
    glPopMatrix();
}

void Reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);

    WindW = width;
    WindH = height;
}

void disp_cubes(void) //single buffer
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLineWidth(2.0f); //width of line in text
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-7.0, 7.0, 0.0);
    glScalef(0.01f, 0.01f, 0.01f);
    glColor3f(1.0, 0.0, 0.0);
    draw_string_stroke(GLUT_STROKE_ROMAN, "Sevivon Single Buffer"); //stroke text
    glFlush();
    glPopMatrix();

    make_cube();

    glFlush();
}

void disp_cubed(void) //double buffer
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLineWidth(3.0f);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-7.0, 7.0, 0.0);
    glScalef(0.01f, 0.01f, 0.01f);
    glColor3f(1.0, 0.0, 1.0);
    draw_string_stroke(GLUT_STROKE_ROMAN, "Sevivon Double Buffer");
    glFlush();
    glPopMatrix();

    make_cube();

    glutSwapBuffers(); // Swapping buffers

    glFlush();
}

void rotate(void) // rotating the cube while Idle
{
    // single
    glutSetWindow(singlebuf);
    glRotatef(-12 * directions, 1., 1., 0.); //rotating about Ox+Oy
    glutPostRedisplay();

    // double
    glutSetWindow(doublebuf);
    glRotatef(12 * directiond, 0., 1., 0.); //rotating about Oy
    glutPostRedisplay();
}

void directs(int button, int state, int x, int y)
{
    // changing the direction of the rotation according to
    // the mouse button SINGLE BUFFER

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        directions = -1;
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        directions = 1;
}

void directd(int button, int state, int x, int y)
{
    // changing the direction of the rotation according to
    // the mouse button DOUBLE BUFFER

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        directiond = -1;
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        directiond = 1;
}

void myinit(void)
{
    // myinit function
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10., 10., -10., 10., -10., 10.);
    glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char **argv)
{
    printf("Press s to make it slower...   \n");
    printf("Press f to make it faster...   \n");
    printf("Press q or Q or Esc to exit... \n");

    glutInit(&argc, argv);
    // First Window - single buffered
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(0, 100);
    singlebuf = glutCreateWindow("SINGLE BUFFER");
    glutReshapeFunc(Reshape);
    glutDisplayFunc(disp_cubes); // display callback function
    glutIdleFunc(rotate);        // idle callback function
    glutMouseFunc(directs);      // mouse callback function
    glutKeyboardFunc(Keymenu);   // kyboard callback
    myinit();

    // Second Window - double buffered
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(300, 100);
    doublebuf = glutCreateWindow("DOUBLE BUFFER");
    glutReshapeFunc(Reshape);
    glutDisplayFunc(disp_cubed); // display callback function
    glutIdleFunc(rotate);        // idle callback function
    glutMouseFunc(directd);      // mouse callback function
    glutKeyboardFunc(Keymenu);   // kyboard callback
    myinit();

    galil = gluNewQuadric(); //standard function

    glutMainLoop();
}

void Keymenu(unsigned char c, int x, int y)
{
    int i;
    i = glutGetWindow(); // getting the active window
    if (i == singlebuf)  //for single buffer
    {
        if (c == 'f' || c == 'F')
            directions /= 0.5;
        if (c == 's' || c == 'S')
            directions *= 0.5;
        if (c == 'q' || c == 'Q' || c == 27)
        {
            exit(1);
        }
    }
    if (i == doublebuf) //for double buffer
    {
        if (c == 'f' || c == 'F')
            directiond /= 0.5;
        if (c == 's' || c == 'S')
            directiond *= 0.5;
        if (c == 'q' || c == 'Q' || c == 27)
        {
            exit(1);
        }
    }
}