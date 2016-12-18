#include <windows.h>
#include <stdlib.h>
#include <glut.h>

GLfloat point[3][2] = {{-1.0, -0.50}, {1.0, -0.50}, {0.0, 1.5}};
int n;

void init()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glColor3f(1.0, 0.0, 0.0);
  //  glPointSize(1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1.5, 1.5, -1.5, 2.0);
  glMatrixMode(GL_MODELVIEW);
}
void triangle(GLfloat a[2], GLfloat b[2], GLfloat c[2])
{
  glBegin(GL_TRIANGLES);
  glVertex2fv(a);
  glVertex2fv(b);
  glVertex2fv(c);
  glEnd();
}
void divide_triangle(GLfloat a[2], GLfloat b[2], GLfloat c[2], int k)
{
  GLfloat ab[2], ac[2], bc[2];
  if (k)
  {
    for (int i = 0; i < 2; i++)
    {
      ab[i] = (a[i] + b[i]) / 2;
      ac[i] = (a[i] + c[i]) / 2;
      bc[i] = (b[i] + c[i]) / 2;
    }
    divide_triangle(a, ab, ac, k - 1);
    divide_triangle(b, ab, bc, k - 1);
    divide_triangle(c, ac, bc, k - 1);
  }
  else
    triangle(a, b, c);
}
void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  divide_triangle(point[0], point[1], point[2], n);
  glFlush();
}
void main(int argc, char **argv)
{
  n = 5;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Sierpinski Gasket");
  glutDisplayFunc(display);
  init();
  glutMainLoop();
}
