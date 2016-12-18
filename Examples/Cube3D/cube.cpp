#include <windows.h>
#include <stdlib.h>
#include <glut.h>
#include <math.h>

typedef GLfloat point3d[3];
int bx,by;
point3d vertex[8]=
      {{0.5,0.5,0.5},{0.5,-0.5,0.5},{-0.5,-0.5,0.5},{-0.5,0.5,0.5},
       {0.5,0.5,-0.5},{0.5,-0.5,-0.5},{-0.5,-0.5,-0.5},{-0.5,0.5,-0.5}};

GLfloat *faces[6][4][3]={{{&vertex[0][0],&vertex[0][1],&vertex[0][2]},
                          {&vertex[1][0],&vertex[1][1],&vertex[1][2]},
                          {&vertex[2][0],&vertex[2][1],&vertex[2][2]},
                          {&vertex[3][0],&vertex[3][1],&vertex[3][2]}},

                         {{&vertex[0][0],&vertex[0][1],&vertex[0][2]},
                          {&vertex[1][0],&vertex[1][1],&vertex[1][2]},
                          {&vertex[5][0],&vertex[5][1],&vertex[5][2]},
                          {&vertex[4][0],&vertex[4][1],&vertex[4][2]}},

                         {{&vertex[4][0],&vertex[4][1],&vertex[4][2]},
                          {&vertex[5][0],&vertex[5][1],&vertex[5][2]},
                          {&vertex[6][0],&vertex[6][1],&vertex[6][2]},
                          {&vertex[7][0],&vertex[7][1],&vertex[7][2]}},

                         {{&vertex[7][0],&vertex[7][1],&vertex[7][2]},
                          {&vertex[6][0],&vertex[6][1],&vertex[6][2]},
                          {&vertex[2][0],&vertex[2][1],&vertex[2][2]},
                          {&vertex[3][0],&vertex[3][1],&vertex[3][2]}},

                         {{&vertex[1][0],&vertex[1][1],&vertex[1][2]},
                          {&vertex[2][0],&vertex[2][1],&vertex[2][2]},
                          {&vertex[6][0],&vertex[6][1],&vertex[6][2]},
                          {&vertex[5][0],&vertex[5][1],&vertex[5][2]}},

                         {{&vertex[0][0],&vertex[0][1],&vertex[0][2]},
                          {&vertex[3][0],&vertex[3][1],&vertex[3][2]},
                          {&vertex[7][0],&vertex[7][1],&vertex[7][2]},
                          {&vertex[4][0],&vertex[4][1],&vertex[4][2]}}};

GLfloat face_colors[6][3]={{1.0,0.0,0.0},{0.0,1.0,1.0},{0.0,0.0,1.0},
                           {1.0,1.0,0.0},{1.0,0.0,1.0},{0.0,1.0,0.0}};
/*GLfloat face_colors[8][3]={{0.0,0.0,0.0},{1.0,0.0,0.0},{1.0,1.0,0.0},
                           {0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,0.0,1.0},
                           {1.0,1.0,1.0},{0.0,1.0,1.0}};  */
GLubyte face_indices[24]={0,3,2,1,0,1,5,4,4,5,6,7,7,6,2,3,1,2,6,5,0,4,7,3};
void draw_face(int i)
 {
  glColor3fv(face_colors[i]);
  glBegin(GL_POLYGON);
    glVertex3fv(*faces[i][0]);
    glVertex3fv(*faces[i][1]);
    glVertex3fv(*faces[i][2]);
    glVertex2fv(*faces[i][3]);
  glEnd();
  glFlush();
 }    

void draw_cube()
 {
 // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for (int i=0; i<6; i++)
 //  glDrawElements(GL_POLYGON,4,GL_UNSIGNED_BYTE,&face_indices[4*i]);
   draw_face(i);
  glFlush();
//  glEnableClientState(3,GL_FLOAT,0,vertex);
//  glEnableClientState(3,GL_FLOAT,0,face_colors);
 // glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,face_indices);
 }

void rotate_z(float angel)
 {
  float x,y;
  float cosine=cos(angel);
  float sine=sin(angel);
  for (int i=0; i<8; i++)
   {
    x=(cosine*vertex[i][0]-sine*vertex[i][1]);
    y=(sine*vertex[i][0]+cosine*vertex[i][1]);

    vertex[i][0]=x;
    vertex[i][1]=y;
   }
  glRotatef(3,0,0,1);
 }

void rotate_x(float angel)
 {
  float y,z;
  float cosine=cos(angel);
  float sine=sin(angel);
  for (int i=0; i<8; i++)
   {
    y=(cosine*vertex[i][1]-sine*vertex[i][2]);
    z=(sine*vertex[i][1]+cosine*vertex[i][2]);

    vertex[i][1]=y;
    vertex[i][2]=z;
   }
 }

void rotate_y(float angel)
 {
  float x,z;
  float cosine=cos(angel);
  float sine=sin(angel);
  for (int i=0; i<8; i++)
   {
    x=(cosine*vertex[i][0]+sine*vertex[i][2]);
    z=(-sine*vertex[i][0]+cosine*vertex[i][2]);

    vertex[i][0]=x;
    vertex[i][2]=z;
   }
 }

void display()
 {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  draw_cube();
 //
  glutSwapBuffers();
 }


void init()
 {
 // glViewport(0,0,500,500);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.5,1.5,-1.5,1.5,-1.5,1.5);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //glClearColor(1.0,1.0,1.0,1.0);
  glClearColor(0.0,0.0,0.0,1.0);
  glColor3f(1.0,1.0,1.0);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3,GL_FLOAT,0,face_colors);
  glVertexPointer(3,GL_FLOAT,0,vertex);
  glFlush();
//  glShadeModel(GL_FLAT);
 }

void keyboard(unsigned char key,int x,int y)
 {
  if (key=='z')
   {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    rotate_z(3*3.14/180);
    draw_cube();
    glFlush();
    glutSwapBuffers();
   }

  if (key=='x')
   {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    rotate_x(3*3.14/180);
    draw_cube();
    glFlush();
    glutSwapBuffers();
   }
  if (key=='c')
   {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    rotate_y(3*3.14/180);
    draw_cube();
    glFlush();
    glutSwapBuffers();
   }
  if (key=='a')
   {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    rotate_z(-3*3.14/180);
    draw_cube();
    glFlush();
    glutSwapBuffers();
   }

  if (key=='s')
   {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    rotate_x(-3*3.14/180);
    draw_cube();
    glFlush();
    glutSwapBuffers();
   }
  if (key=='d')
   {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    rotate_y(-3*3.14/180);
    draw_cube();
    glFlush();
    glutSwapBuffers();
   }
 }

void motion(int x,int y)
 {
  int deltax=x-bx,deltay=y-by;
  bx=x,by=y;
  if (deltax && deltay && deltax==deltay)
   {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    rotate_z(3*3.14/180);
    draw_cube();
    glFlush();
    glutSwapBuffers();

   }
  if (deltax && !deltay)
   {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    rotate_y(3*3.14/180);
    draw_cube();
    glFlush();
    glutSwapBuffers();
   }
  if (!deltax && deltay)
   {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    rotate_x(3*3.14/180);
    draw_cube();
    glFlush();
    glutSwapBuffers();
   }
 }
void mouse(int button,int state,int x,int y)
 {
  if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
   {
    bx=0;by=0;
   }
  if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) exit(0);
 }

void reshape(int w,int h)
 {
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.5,1.5,-1.5,1.5,-1.5,1.5);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glutPostRedisplay();
//  glFlush();
 }

void main(int argc, char** argv)
{
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(500,500);
 glutInitWindowPosition(150,0);
 glutCreateWindow("3D Cube");
 glutMouseFunc(mouse);
 glutDisplayFunc(display);
 glutReshapeFunc(reshape);
 glutKeyboardFunc(keyboard);
 glutMotionFunc(motion);
// glEnable(GL_DEPTH_TEST);
// glutIdleFunc(rotate_z);
 init();
 glEnable(GL_DEPTH_TEST);



/* glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 doubleb=glutCreateWindow("Double Buffered");
 init();
 glutDisplayFunc(displayd);
 glutReshapeFunc(reshape);
 glutIdleFunc(spin_display);
 glutMouseFunc(mouse);    */

 glutMainLoop();
}
