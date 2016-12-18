#include "glut.h"

GLUquadricObj *galil;
GLUquadricObj *sphere;
GLUquadricObj *sphere1;
GLUquadricObj *sphere2;

GLfloat vertices[][3] = {/*0*/ {-8., -8., 0.0}, {-8., -8., 1.}, {-4., -8., 1.},
                         /*3*/ {-4., -8., 0.0},
                         {-8., -9., 0.},
                         {-8., -9., 1.},
                         {-4., -9., 1.},
                         {-4., -9., 0.}};

int directions = 1, directiond = 1, parent, singleb, doubleb;

void polygon(int a, int b, int c, int d)
{
    glBegin(GL_POLYGON);
    glVertex3fv(vertices[a]);
    glVertex3fv(vertices[b]);
    glVertex3fv(vertices[c]);
    glVertex3fv(vertices[d]);
    glEnd();
}

void display(void)
{

    glClearColor(0., 0., 0., 0.);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLineWidth(2);
    //////////////////////////////////////////
    glColor3f(1., 0., 0.);
    polygon(0, 1, 2, 3);
    glColor3f(1., 0., 0.);
    polygon(1, 2, 6, 5);
    glColor3f(1., 0., 0.);
    polygon(2, 3, 7, 6);
    glColor3f(1., 0., 0.);
    polygon(0, 1, 5, 4);
    glColor3f(1., 0., 0.);
    polygon(0, 3, 4, 7);
    glColor3f(1., 0., 0.);
    polygon(4, 5, 6, 7);

    ////////////////////////////////////////
    glPushMatrix();
    glTranslatef(0., 0., 0.);
    glRotatef(0., 0., 0., 0.);
    glColor3f(1.45, 1.34, 1.34);
    gluSphere(sphere, 5, 115, 15);
    ///////////////////////////////////
    glColor3f(0., 1., 0.);
    glTranslatef(0., 0., 2.5);
    glutSolidSphere(3, 45, 15);
    ////////////////////////////////
    glColor3f(0., 0., 0.);
    glTranslatef(0., 0., 1.6);
    glutSolidSphere(1.6, 45, 15);
    //////////////////////////////////
    glColor3f(0., 0., 0.);
    glTranslatef(0., 0., 1.6);
    gluCylinder(galil, 1.6, 0.1, 8, 15, 15);

    glPopMatrix();
    glutSwapBuffers();
    glFlush();
}

void rotate(void)
{

    glRotatef(.9 * directions, 0., 1., 0.);
    glTranslatef(0.0, 0., 0.0);
    glutPostRedisplay();
}

void directs(int button, int state, int x, int y)
{
    // changing the direction of the rotation according to
    // the mouse button have been pressed (for SINGLE)

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        directions = -1;
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        directions = 1;
}

/*void directd(int button, int state, int x, int y)
{
    // changing the direction of the rotation according to 
    // the mouse button have been pressed (for DOUBLE)

    if(button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN)
        directiond = -1;
    if(button == GLUT_RIGHT_BUTTON  && state == GLUT_DOWN)
        directiond = 1;
}

void kill_wnd(unsigned char key, int x, int y)
{
    if(key == '0')
    {	glutDestroyWindow(parent);
        exit(1);
    }
    if(key == '1')
    {	glutDestroyWindow(singleb);
        singleb = 0;
    }
    if(key == '2')
    {	glutDestroyWindow(doubleb);
        doubleb = 0;
    }
    if(key == 'w')
    {	//glutDestroyWindow(singleb);
    directions =5;	//singleb = 0;
    }
    if(key == 's')
    {	//glutDestroyWindow(singleb);
    directions =-5;	//singleb = 0;
    }

    display();
}*/

void initial(void)
{
    // initialization
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-12., 12., -12., 12., -12., 12.);
    glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char **argv)
{

    float pos[4] = {10, 10, 10, 2};
    float dir[4] = {-1, -1, -1}; //
    float Matr[4] = {1, 1, 1, 1};

    float LightMod[] = {1.2, 0.2, 0.2, 1.0};

    glutInit(&argc, argv);

    // The main parent window
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("The Parent Window");
    glutDisplayFunc(display);
    //glutDisplayFunc(disp_cubed);// display callback function
    ///////////////////////////////////////////
    sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL /*SILHOUETTE*/);
    ///////////////////////////////////////////
    sphere1 = gluNewQuadric();
    gluQuadricDrawStyle(sphere1, GLU_SILHOUETTE);
    ///////////////////////////////////////////////
    sphere2 = gluNewQuadric();
    gluQuadricDrawStyle(sphere2, GLU_SILHOUETTE);
    ////////////////////////////////////////////
    galil = gluNewQuadric();
    gluQuadricDrawStyle(galil, GLU_FILL);

    //	glutKeyboardFunc(kill_wnd);	// kyboard callback
    glutMouseFunc(directs);
    glutIdleFunc(rotate); // idle callback function
    initial();

    //////////[1]//////////////////////////////////////////////////////

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, LightMod);

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

    glMaterialfv(GL_FRONT, GL_SPECULAR, Matr);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);

    glutMainLoop();
}
