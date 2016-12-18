#include <windows.h>
#include <stdlib.h>
#include <glut.h>
#include <stdafx.h>
typedef GLfloat point3d[3];

//point3d vertices[4]={{0.0,0.0,1.0},{0.0,0.942809,-0.33333},
//                     {-0.86497,-0471405,-0.33333},{0.816497,-0.471405,0.33333}};
point3d vertices[4] = {{0.0, 0.8, 0.0}, {-0.8, -0.8, 0.8}, {0.8, -0.8, 0.8}, {0.0, -0.3, -0.8}};
int n;
int type = 1;
void triangle(point3d a, point3d b, point3d c)
{
    if (type)
        glBegin(GL_TRIANGLES);
    else
        glBegin(GL_LINE_LOOP);
    glNormal3fv(a);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    /*  glVertex3fv(vertices[0]);
   glVertex3fv(vertices[1]);
   glVertex3fv(vertices[2]);
   glVertex3fv(vertices[3]);   */

    glEnd();
}
void divide_triangle(point3d a, point3d b, point3d c, int k)
{
    point3d ab, ac, bc;
    if (k)
    {
        for (int i = 0; i < 3; i++)
        {
            ab[i] = (a[i] + b[i]) / 2; //+(rand()%10)/500.0;
            ac[i] = (a[i] + c[i]) / 2; //+(rand()%10)/500.0;
            bc[i] = (b[i] + c[i]) / 2; //+(rand()%10)/500.0;
        }
        divide_triangle(a, ab, ac, k - 1);
        divide_triangle(b, ab, bc, k - 1);
        divide_triangle(c, ac, bc, k - 1);
    }
    else
        triangle(a, b, c);
}
void tetrahedron(int m)
{
    divide_triangle(vertices[0], vertices[2], vertices[1], m);
    glColor3f(0.0, 1.0, 0.0);
    divide_triangle(vertices[3], vertices[2], vertices[1], m);
    glColor3f(0.0, 0.0, 1.0);
    divide_triangle(vertices[0], vertices[3], vertices[1], m);
    glColor3f(1.0, 1.0, 1.0);
    divide_triangle(vertices[0], vertices[2], vertices[3], m);
    glColor3f(1.0, 0.0, 0.0);
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    tetrahedron(n);
    //  triangle();
    glFlush();
}
void keyboard(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q')
        exit(0);
    if (key == '1')
    {
        type = 1;
        display();
    }
    if (key == '0')
    {
        type = 0;
        display();
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.0, 1.0, -1.0 * w / h, 1.0 * w / h, -1.0, 1.0);
    else
        glOrtho(-1.0 * w / h, 1.0 * w / h, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}
void main(int argc, char **argv)
{
    n = 5;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("3D Sierpinski Gasket");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glEnable(GL_DEPTH_TEST);

    // init();
    glutMainLoop();
}
