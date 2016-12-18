#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glaux.h>
#include <math.h>

#define M_PI 3.14
#define M_PI_2 3.14/2
typedef GLfloat point3d[3];

GLfloat angle,axis[3],trans[3];
int tracking_mouse,redraw,track_move;
GLfloat last_pos[3];
int curx,cury;
int startx,starty;
int height=500,width=500;
//GLdouble viewer[3]={0.0,0.0,0.5};
point3d vertex[8]=
      {{0.5,0.5,0.5},{0.5,-0.5,0.5},{-0.5,-0.5,0.5},{-0.5,0.5,0.5},
       {0.5,0.5,-0.5},{0.5,-0.5,-0.5},{-0.5,-0.5,-0.5},{-0.5,0.5,-0.5}};

/*point3d vertex[6]={{0.0,0.8,0.0},{-0.5,0.0,0.5},{0.5,0.0,0.5},
                   {0.5,0.0,-0.5},{-0.5,0,-0.5},{0.0,-0.8,0.0}};*/

/*point3d vertex[20]={{-0.9,1.2,0.3},{0.0,1.5,-0.3},{0.9,1.2,0.3},{1.2,0.5,-0.3},
                    {1.2,-0.3,0.3},{0.9,-1.2,-0.3},{0.0,-1.5,0.3},{-0.9,-1.2,-0.3},
                    {-1.2,-0.3,0.3},{-1.2,0.5,-0.3},{-0.5,0.9,1.0},{0.5,0.9,1.0},
                    {0.8,0.0,1.0},{0.0,-0.6,1.0},{-0.8,0.0,1.0},{0.0,1.1,-1.0},
                    {0.8,0.4,-1.0},{0.5,-0.4,-1.0},{-0.5,-0.4,-1.0},{-0.8,0.4,-1.0}};*/
/*GLfloat face_colors[6][3]={{1.0,0.0,0.0},{0.0,1.0,1.0},{0.0,0.0,1.0},
                           {1.0,1.0,0.0},{1.0,0.0,1.0},{0.0,1.0,0.0}};*/
GLfloat face_colors[8][3]={{0.0,0.0,0.0},{1.0,0.0,0.0},{1.0,1.0,0.0},
                           {0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,0.0,1.0},
                           {1.0,1.0,1.0},{0.0,1.0,1.0}};              
GLubyte face_indeces[24]={0,3,2,1,0,1,5,4,4,5,6,7,7,6,2,3,1,2,6,5,0,4,7,3}; 
/*GLubyte face_indeces[24]={0,1,2,0,2,3,0,3,4,0,4,1,5,2,1,5,3,2,5,4,3,5,1,4};*/
/*GLubyte face_indeces[60]={0,10,11,2,1,2,11,12,4,3,4,12,13,6,5,6,13,14,8,7,8,14,10,0,9,
                          1,2,3,16,15,3,4,5,17,16,5,6,7,18,17,7,8,9,19,18,9,0,1,15,19,
                          10,14,13,12,11,15,16,17,18,19};*/

void draw_cube()
 {
//  for (int i=0; i<12; i++)
//  int i=1;
//   glDrawElements(GL_LINE_LOOP,5,GL_UNSIGNED_BYTE,&face_indeces[i*5]);
  glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,face_indeces);
 }

void project(int x,int y,int w,int h,float v[3])
 {
  float d,a;
  v[0]=(2.0*x-w)/w;
  v[1]=(h-2.0*y)/h;
  d=sqrt(v[0]*v[0]+v[1]*v[1]);
  v[2]=cos(M_PI_2*(d<1 ? d : 1));
  a=1/sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
  v[0]*=a;
  v[1]*=a;
  v[2]*=a;
 }

void motion(int x,int y)
 {
  float cur_pos[3],dx,dy,dz;
  project(x,y,width,height,cur_pos);
  if (tracking_mouse)
   {
    dx=cur_pos[0]-last_pos[0];
    dy=cur_pos[1]-last_pos[1];
    dz=cur_pos[2]-last_pos[2];
    if (dx || dy || dz)
     {
      angle=90*sqrt(dx*dx+dy*dy+dz*dz);
      axis[0]=last_pos[1]*cur_pos[2]-last_pos[2]*cur_pos[1];
      axis[1]=last_pos[2]*cur_pos[0]-last_pos[0]*cur_pos[2];
      axis[2]=last_pos[0]*cur_pos[1]-last_pos[1]*cur_pos[0];

      last_pos[0]=cur_pos[0];
      last_pos[1]=cur_pos[1];
      last_pos[2]=cur_pos[2];
     }
   }
  glutPostRedisplay();
 }

void start_motion(int x,int y)
 {
  tracking_mouse=1;
  redraw=0;
  startx=x; starty=y;
  curx=x; cury=y;
  project(x,y,width,height,last_pos);
  track_move=1;
 }

void stop_motion(int x, int y)
 {
  tracking_mouse=1;
  if (startx!=x || starty!=y)
   redraw=1;
  else
   {
    angle=0;
    redraw=0;
    track_move=0;
   }
 }

void display()
 {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//  glLoadIdentity();
//  gluLookAt(viewer[0],viewer[1],viewer[2],0.0,0.0,0.0,0.0,4.0,0.0);
  if (track_move)
   glRotatef(angle,axis[0],axis[1],axis[2]);
  draw_cube();
  glutSwapBuffers();
 }

void keyboard(unsigned char key,int x,int y)
 {
  if (key=='q' || key=='Q') exit(0);
  if (key=='z')
   {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRotatef(3,0,0,1);
    draw_cube();
    glutSwapBuffers();
   }
  if (key=='a')
   {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRotatef(-3,0,0,1);
    draw_cube();
    glutSwapBuffers();
   }
  if (key=='x')
   {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRotatef(3,1,0,0);
    draw_cube();
    glutSwapBuffers();
   }
  if (key=='s')
   {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRotatef(-3,1,0,0);
    draw_cube();
    glutSwapBuffers();
   }
  if (key=='c')
   {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRotatef(3,0,1,0);
    draw_cube();
    glutSwapBuffers();
   }
  if (key=='d')
   {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRotatef(-3,0,1,0);
    draw_cube();
    glutSwapBuffers();
   }
 }

void mouse(int button,int state,int x,int y)
 {
  if(button==GLUT_LEFT_BUTTON)
   {
    y=height-y;
    if (button==GLUT_DOWN)
     start_motion(x,y);
    else
     stop_motion(x,y);
   }
  if(button==GLUT_RIGHT_BUTTON) exit(0);
 }

void reshape(int w,int h)
 {
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
//  gluPerspective(45.0,w/h,1.0,10.0);
  width=w;
  height=h;
 }

void spin_cube()
 {
  if (redraw) glutPostRedisplay();
 }

void init()
 {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.5,1.5,-1.5,1.5,-1.5,1.5);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0.0,0.0,0.0,1.0);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3,GL_FLOAT,0,face_colors);
  glVertexPointer(3,GL_FLOAT,0,vertex);
//  glFlush();
//  glShadeModel(GL_FLAT);
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
 glutIdleFunc(spin_cube);
 glutMotionFunc(motion);
 init();
 glEnable(GL_DEPTH_TEST);



 glutMainLoop();
}
