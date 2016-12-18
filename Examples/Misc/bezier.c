/*
**  curves.c
**
**  Simple curve drawing program.
**
**  The following keyboard commands are used to control the
**  program:
**
**    q - Quit the program
**    c - Clear the screen
**    e - Erase the curves
**    b - Draw Bezier curves
**
*/

#include <GL/glut.h>

void keyboard(unsigned char key, int x, int y);

#define MAX_CPTS  25            /* Fixed maximum number of control points */

GLfloat cpts[MAX_CPTS][3];
int ncpts = 0;

static int width = 500, height = 500;           /* Window width and height */

void drawCurves()
{
    int i;
    /* Draw the curves */

    for(i=0; i<ncpts-3; i +=3) 
    {
        /* Draw the curve using OpenGL evaluators */
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, cpts[i]);
        glMapGrid1f(30, 0.0, 1.0);
        glEvalMesh1(GL_LINE, 0, 30);
    }
    glFlush();
}

/* This routine displays the control points */
static void display(void)
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT);


    glBegin(GL_POINTS);
    for (i = 0; i < ncpts; i++)
        glVertex3fv(cpts[i]);
    glEnd();

    glFlush();
}


/* This routine inputs new control points */
static void mouse(int button, int state, int x, int y)
{
    float wx, wy;

    /* We are only interested in left clicks */
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
        return;

    /* Translate back to our coordinate system */
    wx = (2.0 * x) / (float)(width - 1) - 1.0;
    wy = (2.0 * (height - 1 - y)) / (float)(height - 1) - 1.0;


    /* See if we have room for any more control points */
    if (ncpts == MAX_CPTS)
        return;

    /* Save the point */
    cpts[ncpts][0] = wx;
    cpts[ncpts][1] = wy;
    cpts[ncpts][2] = 0.0;
    ncpts++;

    /* Draw the point */
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex3f(wx, wy, 0.0);
    glEnd();
 
    glFlush();
}


/* This routine handles keystroke commands */
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q': case 'Q':
            exit(0);
            break;
        case 'c': case 'C':
            ncpts = 0;
            glutPostRedisplay();
            break;
        case 'e': case 'E':
            glutPostRedisplay();
            break;
        case 'b': case 'B':
            drawCurves();
            break;
    }
}


/* This routine handles window resizes */
void reshape(int w, int h)
{
    width = w;
    height = h;

    /* Set the transformations */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}


int main(int argc, char **argv)
{
    /* Intialize the program */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("curves");

    /* Register the callbacks */
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);
    glEnable(GL_MAP1_VERTEX_3);


    glutMainLoop();
}
