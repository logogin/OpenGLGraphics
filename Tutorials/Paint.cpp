#include <windows.h>
#include <stdlib.h>
#include <glut.h>

#define LINE 1
#define RECTANGLE 3
#define TRIANGLE 2
#define POINTS 4
#define _TEXT 5

GLsizei hight = 500, width = 500;
int draw_mode = 0;
int rx, ry;
int size = 3;
GLfloat red = 0.0, green = 0.0, blue = 0.0;
int fill = 0;

void draw_button(int x1, int y1, int x2, int y2, int state)
{
  glColor3ub(192, 192, 192);
  glBegin(GL_POLYGON);
  glVertex2i(x1 + 2, y1 + 2);
  glVertex2i(x2 - 2, y1 + 2);
  glVertex2i(x2 - 2, y2 - 2);
  glVertex2i(x1 + 2, y2 - 2);
  glEnd();

  if (state)
    glColor3ub(203, 203, 203);
  else
    glColor3ub(0, 0, 0);
  glBegin(GL_LINE_STRIP);
  glVertex2i(x1, y1 + 1);
  glVertex2i(x1, y2);
  glVertex2i(x2 - 1, y2);
  glEnd();

  if (state)
    glColor3ub(255, 255, 255);
  else
    glColor3ub(128, 128, 128);
  glBegin(GL_LINE_STRIP);
  glVertex2i(x1 + 1, y1 + 2);
  glVertex2i(x1 + 1, y2 - 1);
  glVertex2i(x2 - 2, y2 - 1);
  glEnd();

  if (state)
    glColor3ub(128, 128, 128);
  else
    glColor3ub(255, 255, 255);
  glBegin(GL_LINE_STRIP);
  glVertex2i(x2 - 2, y2 - 1);
  glVertex2i(x2 - 2, y1 + 1);
  glVertex2i(x1 + 1, y1 + 2);
  glEnd();

  if (state)
    glColor3ub(0, 0, 0);
  else
    glColor3ub(203, 203, 203);
  glBegin(GL_LINE_STRIP);
  glVertex2f(x2 - 1, y2);
  glVertex2f(x2 - 1, y1);
  glVertex2f(x1, y1 + 1);
  glEnd();
  glFlush();
}

void draw_point(int x, int y)
{
  y = hight - y;
  glPointSize(size);
  glBegin(GL_POINTS);
  glVertex2f(x, y);
  glEnd();
  glPointSize(1);
  glFlush();
}

void draw_line(int x1, int y1, int x2, int y2)
{
  y1 = hight - y1;
  y2 = hight - y2;
  glBegin(GL_LINES);
  glVertex2f(x1, y1);
  glVertex2f(x2, y2);
  glEnd();
}

void draw_rectangle(int x1, int y1, int x2, int y2)
{
  y1 = hight - y1;
  y2 = hight - y2;
  if (fill)
    glBegin(GL_POLYGON);
  else
    glBegin(GL_LINE_LOOP);
  glVertex2f(x1, y1);
  glVertex2f(x2, y1);
  glVertex2f(x2, y2);
  glVertex2f(x1, y2);
  glEnd();
}

void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
  y1 = hight - y1;
  y2 = hight - y2;
  y3 = hight - y3;
  if (fill)
    glBegin(GL_POLYGON);
  else
    glBegin(GL_LINE_LOOP);
  glVertex2f(x1, y1);
  glVertex2f(x2, y2);
  glVertex2f(x3, y3);
  glEnd();
}

int cursor_in(int x, int y)
{
  if (x >= 110 && x <= width - 10 && y >= 10 && y <= hight - 10)
    return 1;
  else
    return 0;
}

void reshape(GLsizei w, GLsizei h)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, w, 0.0, h);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glViewport(0, 0, w, h);
  //glClearColor(1.0,1.0,1.0,1.0);
  //glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
  width = w;
  hight = h;
}

int pick(int x, int y)
{
  int result;
  if (x >= 25 && x <= 75 && y <= 275)
  {
    if (y >= 25)
      result = LINE;
    if (y >= 75)
      result = TRIANGLE;
    if (y >= 125)
      result = RECTANGLE;
    if (y >= 175)
      result = POINTS;
    if (y >= 225)
      result = _TEXT;
  }
  else
    result = 0;
  return result;
}

void color_menu(int id)
{
  switch (id)
  {
  case 1:
  {
    red = 1.0;
    green = 0.0;
    blue = 0.0;
  }
  break;
  case 2:
  {
    red = 0.0;
    green = 1.0;
    blue = 0.0;
  }
  break;
  case 3:
  {
    red = 0.0;
    green = 0.0;
    blue = 1.0;
  }
  break;
  case 4:
  {
    red = 0.0;
    green = 1.0;
    blue = 1.0;
  }
  break;
  case 5:
  {
    red = 1.0;
    green = 0.0;
    blue = 1.0;
  }
  break;
  case 6:
  {
    red = 1.0;
    green = 1.0;
    blue = 0.0;
  }
  break;
  case 7:
  {
    red = 1.0;
    green = 1.0;
    blue = 1.0;
  }
  break;
  case 8:
  {
    red = 0.0;
    green = 0.0;
    blue = 0.0;
  }
  break;
  }
}
void pixel_menu(int id)
{
  if (id == 1)
    size += 2;
  else if (size > 1)
    size -= 2;
}

void fill_menu(int id)
{
  fill = id;
}

void keyboard(unsigned char key, int x, int y)
{
  if (draw_mode == _TEXT && cursor_in(rx + 10, hight - y))
  {
    glColor3f(red, green, blue);
    glRasterPos2i(rx, ry);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15 /*GLUT_STROKE_ROMAN*/, key);
    rx += glutBitmapWidth(GLUT_BITMAP_9_BY_15, key);
  }
}

void on_buttons(int button_number, int state)
{
  int shift = 0;
  switch (button_number)
  {
  case LINE:
    draw_button(25, hight - 75, 75, hight - 25, state);
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(30, hight - 30);
    glVertex2i(70, hight - 70);
    glEnd();
    glColor3f(red, green, blue);
    break;

  case TRIANGLE:
    draw_button(25, hight - 125, 75, hight - 75, state);
    glColor3ub(0, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2i(30, hight - 120);
    glVertex2i(70, hight - 120);
    glVertex2i(50, hight - 80);
    glEnd();
    glColor3f(red, green, blue);
    break;

  case RECTANGLE:
    draw_button(25, hight - 175, 75, hight - 125, state);
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2i(30, hight - 170);
    glVertex2i(70, hight - 170);
    glVertex2i(70, hight - 130);
    glVertex2i(30, hight - 130);
    glEnd();
    glColor3f(red, green, blue);
    break;

  case POINTS:
    draw_button(25, hight - 225, 75, hight - 175, state);
    glColor3ub(0, 0, 0);
    glPointSize(6);
    glBegin(GL_POINTS);
    glVertex2i(50, hight - 200);
    glEnd();
    glPointSize(1);
    glColor3f(red, green, blue);
    break;

  case _TEXT:
    draw_button(25, hight - 275, 75, hight - 225, state);
    glColor3ub(0, 0, 0);
    glRasterPos2i(37, hight - 253);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
    shift = glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'A');

    glRasterPos2i(shift + 37, hight - 253);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'B');
    shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'B');

    glRasterPos2i(shift + 37, hight - 253);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
    glColor3f(red, green, blue);
    break;
  }
  glFlush();
}

void display()
{
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glClearColor(0.8, 0.8, 0.8, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  draw_button(0, 0, 100, hight, 1);
  on_buttons(LINE, 1);
  on_buttons(TRIANGLE, 1);
  on_buttons(RECTANGLE, 1);
  on_buttons(POINTS, 1);
  on_buttons(_TEXT, 1);
  glColor3ub(255, 255, 255);
  glBegin(GL_POLYGON);
  glVertex2i(110, 10);
  glVertex2i(width - 10, 10);
  glVertex2i(width - 10, hight - 10);
  glVertex2i(110, hight - 10);
  glEnd();
  glColor3f(red, green, blue);
  glPopAttrib();
  glFlush();
}

void rigth_menu(int id)
{
  if (id)
    display();
  else
    exit(0);
}

void mouse(int button, int state, int x, int y)
{
  static int count, pred_button = 0;
  static int xp[2], yp[2];
  int mode;
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    mode = pick(x, y);
    if (mode)
    {
      count = 0;
      draw_mode = mode;
      on_buttons(mode, 0);
      if (mode - pred_button)
        on_buttons(pred_button, 1);
      pred_button = mode;
    }
    if (!mode && cursor_in(x, hight - y))
      switch (draw_mode)
      {
      case LINE:
        if (count == 0)
        {
          xp[count] = x;
          yp[count] = y;
          count++;
        }
        else
        {
          glColor3f(red, green, blue);
          draw_line(xp[0], yp[0], x, y);
          count = 0;
        }
        break;
      case RECTANGLE:
        if (count == 0)
        {
          xp[count] = x;
          yp[count] = y;
          count++;
        }
        else
        {
          glColor3f(red, green, blue);
          draw_rectangle(xp[0], yp[0], x, y);
          count = 0;
        }
        break;
      case TRIANGLE:
        if (count < 2)
        {
          xp[count] = x;
          yp[count] = y;
          count++;
        }
        else
        {
          glColor3f(red, green, blue);
          draw_triangle(xp[0], yp[0], xp[1], yp[1], x, y);
          count = 0;
        }
        break;
      case POINTS:
        glColor3f(red, green, blue);
        draw_point(x, y);
        break;

      case _TEXT:
        rx = x;
        ry = hight - y;
        // glRasterPos2i(rx,ry);
        break;
      }

    glPopAttrib();
    glFlush();
  }
}
void middle_menu(int id)
{
}
void menus()
{
  int c_menu, p_menu, f_menu;

  c_menu = glutCreateMenu(color_menu);
  glutAddMenuEntry("Red", 1);
  glutAddMenuEntry("Green", 2);
  glutAddMenuEntry("Blue", 3);
  glutAddMenuEntry("Cyan", 4);
  glutAddMenuEntry("Magneta", 5);
  glutAddMenuEntry("Yellow", 6);
  glutAddMenuEntry("White", 7);
  glutAddMenuEntry("Black", 8);

  p_menu = glutCreateMenu(pixel_menu);
  glutAddMenuEntry("Increase pixel size", 1);
  glutAddMenuEntry("Decrease pixel size", 2);

  f_menu = glutCreateMenu(fill_menu);
  glutAddMenuEntry("Fill On", 1);
  glutAddMenuEntry("Fill Off", 0);

  glutCreateMenu(rigth_menu);
  glutAddSubMenu("Colors", c_menu);
  glutAddSubMenu("Pixel", p_menu);
  glutAddSubMenu("Fill", f_menu);
  glutAddMenuEntry("Clear All", 1);
  glutAddMenuEntry("Quit", 0);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Painter");
  // init();
  menus();
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);
  //glutMotionFunc(square);
  glutDisplayFunc(display);
  glutMainLoop();
}
