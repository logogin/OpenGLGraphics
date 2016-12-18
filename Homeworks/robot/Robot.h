// ROBOT.cpp : Defines the entry point for the console application.
//
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdlib.h>	
#include <GL/glut.h>
#include <math.h>

#define PI          3.1415926
#define SPEED_M	    .3
#define SPEED_R	    .05

GLUquadricObj *galil;
static GLfloat angle1[]={0.0, 0.0, 0.0, 0.0};
static GLint axis = 0;
static GLint axis1 = 0;
static GLint axis2 = 0;
static GLint axis3 = 0;
static GLint axis4 = 0;
static GLint axis5 = 0;
int up_view = 0;
int lamp_view=0;
int directions=20;
GLfloat look_at = 320.,angle0=0.;
float angl_x=0 ,angl_y=0,angl_z=0;
float angle4=0,angle2=360,angle3=0;
GLfloat eyex = 0., eyez = 0., azimuth = PI/2;
int main_wind, plan_wnd = 0;
//////////////////////////////////////////
void general_menu(int id);
GLfloat rotate[]         = {0,0,0,0,0,0,0,0,0,0,0,0};
GLint index_of_rotate = 0;
GLfloat dir_of_nose = 1;
///////////////////////////////////////////
#define bust        1      
#define pelvis      2
#define Left_hand   0.0
#define Right_hand  4
#define Left_hdown  5
#define Right_hdown 6
#define Left_leg    7
#define Right_leg   8
#define Left_ldown  9
#define Right_ldown 10
#define head        11
///////////////////////////////////////////////////////
GLfloat mat_specularGRAY[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientGRAY[] ={0.5,0.5,0.5,1.0};
GLfloat mat_diffuseGRAY[] ={0.50,0.50,0.50,1.0};
GLfloat mat_shininessGRAY[] ={128.0 * 0.6};
////////////////////////////////////////////////////
GLfloat men_amb_dif[]   = {0.8, 0.7, 0.5, 1.};
GLfloat men_spec[]      = {.4, 0.4, 0.4, 1.};
GLfloat men_shine       = 20;

/*GLfloat house_amb_dif[] = {.3, .3, .3, 1.};
GLfloat house_spec[]    = {1., 1., 1., 1.};
GLfloat house_shine     = 70;*/

GLfloat light0_pos[]     = {0.5, 8.7, 1., 1.};
GLfloat light0_ambient[] = {0.5,0.4 ,0.7,1.};
GLfloat light0_diffuse[] = {0.5,0.5 ,0.5,1.};
GLfloat light0_spec[]    = {.5, .5, .5, 1.};

GLfloat light1_pos[]     = {0., 10, -1., 1.};
GLfloat light1_dir[]     = {0., -4., 0., 0.};
GLfloat light1_ambient[] = {.4, .4, .2, 1.};
GLfloat light1_diffuse[] = {.5, .5, 0, 1.};
GLfloat light1_spec[]    = {.1, .2, .1, 1.};
GLfloat light1_cutoff    = 20.;
GLfloat light1_exp       = 9.;
GLfloat global_amb[]     = {0.2, 0.2, 0, 1.};

GLfloat no_val[]         = {0., 0., 0., 1.};
GLfloat prog_emiss[]     = {.2, .8, .2, 1.};
GLfloat sun_emiss[]      = {.1, .2, .3 ,1.};
int c_menu;
int properties_menu;


///////////////////////////////////////////////////

void Robot_plan(void);
void myinit();


void struct_head()
{
glPushMatrix();
glTranslatef(0.0,7.5,0.0);
glScalef(0.5,0.7,.75);
glColor3f(1.0,1.0,0.0);
glutSolidSphere(1.5,20,20);

glTranslatef(0.0,0.5,0.3);
glScalef(2.,1.,2.);
glColor3f(0.0,0.,1.);
glutSolidCube(1.);

glPopMatrix();

}
/**********************************/
void struct_Left_hand ()
{
glPushMatrix();
  glTranslatef(2.3,4.3,0.0);
	glScalef(0.5,0.7,0.5);
	glColor3f(0.45,1.4,1.4);
	glutSolidSphere(1.5,20,20);

	glTranslatef(0.0,-2.,0.0);
	glScalef(1.3,4.5,1.3);
	glColor3f(1.,1.,0.);
	glutSolidCube(1.0);
glPopMatrix();
}
/********************************/
void struct_Right_hand ()
{
	glPushMatrix();
	glTranslatef(-2.3,4.3,0.0);
	glScalef(0.5,0.7,0.5);
	glColor3f(0.45,1.4,1.4);
	glutSolidSphere(1.5,20,20);

	glTranslatef(0.0,-2.0,0.0);
	glScalef(1.3,4.5,1.3);
	glColor3f(1.,1.,0.);
	glutSolidCube(1.0);
	glPopMatrix();
}
/********************************/
void struct_Left_hdown ()
{
glPushMatrix();
  glTranslatef(2.3,1.,0.0);
  glScalef(0.5,0.5,0.5);
  glColor3f(1.,1.,1.);
  glutSolidSphere(1.,20,20);
  
  glTranslatef(0.0,-3.2,0.0);
  glScalef(2.5,5.5,2.3);
  glColor3f(0.45,1.4,1.4);
  glutSolidCube(1.0);
  
  glTranslatef(0.0,-0.5,0.0);
  glScalef(1.,1.,2.2);
  glColor3f(0.45,1.4,1.4);
  glutSolidCube(0.5);
  
glPopMatrix();

}
/**************************/
void struct_Right_hdown ()
{
glPushMatrix();
  glTranslatef(-2.3,1.,0.0);
  glScalef(0.5,0.5,0.5);
  glColor3f(1.,1.,1.);
  glutSolidSphere(1.,20,20);
  
  glTranslatef(0.0,-3.2,0.0);
  glScalef(2.5,5.5,2.3);
  glColor3f(0.45,1.4,1.4);
  glutSolidCube(1.0);
  
  glTranslatef(0.0,-0.5,0.0);
  glScalef(1.,1.,2.2);
  glColor3f(0.45,1.4,1.4);
  glutSolidCube(0.5);
  
glPopMatrix();

}
/*******************[ LEGS ]*******************************************/
/////////////////////Left leg////////////////////////////////////
void struct_Left_leg ()
{
glPushMatrix();
  glTranslatef(1.,0.,0.0);
  glScalef(0.4,0.5,0.5);
  glColor3f(1.,1.,1.);
  glutSolidSphere(1.,20,20);
  
 glRotatef(90.,1.,0.,0.);
  glTranslatef(0.0,0.,0.0);
  glColor3f(0.45,1.4,1.4);
  gluCylinder(galil,1.3,0.6,7,15,15);
glPopMatrix();
}
/**************************/
void struct_Left_ldown ()
{
glPushMatrix();
  glTranslatef(2.3,1.,0.0);
  glScalef(0.5,0.5,0.5);
  glColor3f(1.,1.,1.);
  glutSolidSphere(1.,20,20);
  
  glTranslatef(0.0,-2.2,0.0);
  glScalef(2.,3.,2.);
  glColor3f(1.0,1.0,0.0);
  glutSolidCube(1.0);
  
  glTranslatef(0.0,-0.5,0.0);
  glScalef(2.3,1.,2.3);
  glColor3f(1.0,1.0,0.0);
  glutSolidCube(0.5);
  
  glTranslatef(0.0,-0.5,0.0);
  glScalef(1.2,1.,1.2);
  glColor3f(1.0,1.0,0.0);
  glutSolidCube(0.5);

  glTranslatef(0.0,-0.5,0.0);
  glScalef(1.,2.5,1.);
  glColor3f(1.0,1.0,0.0);
  glutSolidCube(0.5);

  glTranslatef(0.0,-0.3,0.0);
  glScalef(1.2,0.5,1.2);
  glColor3f(1.0,1.0,0.0);
  glutSolidCube(0.5);

glPopMatrix();

}
/////////////////[Right_leg]/////////////////////////////
void struct_Right_leg ()
{
glPushMatrix();
  glTranslatef(-1.,0.,0.0);
  glScalef(0.4,0.5,0.5);
  glColor3f(1.,1.,1.);
  glutSolidSphere(1.,20,20);
  
 glRotatef(90.,1.,0.,0.);
  glTranslatef(0.0,0.,0.0);
  glColor3f(0.45,1.4,1.4);
  gluCylinder(galil,1.3,0.6,7,15,15);
glPopMatrix();
}
/****************************************/
void struct_Right_ldown ()
{
glPushMatrix();
  glTranslatef(-1.,-3.9,0.0);
  glScalef(0.5,0.5,0.5);
  glColor3f(1.,1.,1.);
  glutSolidSphere(1.,20,20);
  
  glTranslatef(0.0,-2.2,0.0);
  glScalef(2.,3.,2.);
  glColor3f(1.0,1.0,0.0);
  glutSolidCube(1.0);
  
  glTranslatef(0.0,-0.5,0.0);
  glScalef(2.3,1.,2.3);
  glColor3f(1.0,1.0,0.0);
  glutSolidCube(0.5);
  
  glTranslatef(0.0,-0.5,0.0);
  glScalef(1.2,1.,1.2);
  glColor3f(1.0,1.0,0.0);
  glutSolidCube(0.5);

  glTranslatef(0.0,-0.5,0.0);
  glScalef(1.,2.5,1.);
  glColor3f(1.0,1.0,0.0);
  glutSolidCube(0.5);

  glTranslatef(0.0,-0.3,0.0);
  glScalef(1.2,0.5,1.2);
  glColor3f(1.0,1.0,0.0);
  glutSolidCube(0.5);

glPopMatrix();

}
////////////////////////////////////////////////////////////////////
void Robot_plan()
{
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, men_amb_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, men_spec);
	glMaterialf(GL_FRONT, GL_SHININESS, men_shine);
	
//myinit(); 
	glPushMatrix();
    glTranslatef(0.,5.,0.);
    glColor3f(.6,.6,.8);
	glScalef(1.8,1.,1.0);
	glutSolidSphere(2.6,20,15);
	
	glTranslatef(0,-1.,0);
	glColor3f(.6,.6,.8);
	glutSolidSphere(2.4,5,5);

	glTranslatef(0.0,-1.75,0.0);
	glScalef(1.0,1.0,1.0);
	glColor3f(1.0,1.0,0.0);
	glutSolidCube(2.6);

	glTranslatef(0.0,-1.7,0.0);
	glScalef(1.0,1.0,1.0);
	glColor3f(1.0,1.0,0.0);
	glutSolidCube(1.);
    
     struct_head();
/////////////////Left hend///////////////////////     
	 glPushMatrix();
	 glTranslatef(0.0,5.,0.0);
	 glRotatef(angle1[1],1.0,0.0, 0.0 );
	 glTranslatef(0.0,-5.,0.0);
     struct_Left_hand ();
   /************************/  
	 glPushMatrix();
	 glTranslatef(0.0,1.,0.0);
	 glRotatef(angle1[2],1.0,0.0, 0.0 );
	 glTranslatef(0.0,-1.,0.0);
     struct_Left_hdown (); 
	 glPopMatrix();
	  glPopMatrix();
//////////////////[Right hand]////////////////////
  glPushMatrix();
	 glTranslatef(0.0,5.,0.0);
	 glRotatef(angle1[4],1.0,0.0, 0.0 );
	 glTranslatef(0.0,-5.,0.0);
      struct_Right_hand ();
	  /************************/
     glPushMatrix();
	 glTranslatef(0.0,1.,0.0);
	 glRotatef(angle1[3],1.0,0.0, 0.0 );
	 glTranslatef(0.0,-1.,0.0);
	 struct_Right_hdown (); 
	 glPopMatrix();
  glPopMatrix();
/////////////////////////////////////////////////
glPushMatrix();//Left leg
   	 glTranslatef(0.0,0.,0.0);
	 glRotatef(angle1[5],1.0,0.0, 0.0 );
	 glTranslatef(0.0,0.,0.0);
     struct_Left_leg ();	

     
    glPushMatrix();///down
	 glTranslatef(-1.3,-3.9,0.0);
	 glRotatef(angle1[6],1.0,0.0, 0.0 );
	 glTranslatef(0.0,-1.,0.0);
     struct_Left_ldown ();
	 glPopMatrix();    
	glPopMatrix();
/*************[right leg]********************/
 glPushMatrix();
	 
	 glTranslatef(0.0,0.,0.0);
	 glRotatef(angle1[7],1.0,0.0, 0.0 );
	 glTranslatef(0.0,0.,0.0);
     struct_Right_leg ();	
	 
	 
	 glPushMatrix();
	 glTranslatef(0.0,-3.7,0.0);
	 glRotatef(angle1[8],1.0,0.0, 0.0 );
	 glTranslatef(0.0,3.7,0.0);
	 struct_Right_ldown ();
	 glPopMatrix(); 
 
	 glPopMatrix(); 
	 
	 glPopMatrix();//For all body

glPopMatrix();
}
/*******************************/
void menu(int k)
{
if(k==1)  axis1=1;
if(k==2)  axis=2;
if(k==3)  axis=3;
  if(k==4)  axis1=4;
  if(k==5)  axis2=5;
  if(k==6)  axis3=6;
  if(k==7)  axis4=7;
  if(k==8)  axis5=8;
if(k==9)  exit(1);
}
///////////////////////////////////////////////////
void color_menu(int id)
{
	light1_ambient[0] = 0; 
	light1_ambient[1] = 0;
	light1_ambient[2] = 0;
	switch(id)
	{	
	    case 1 : light1_ambient[0] = .8;  break;
		case 2 : light1_ambient[1] = .8;  break;
		case 3 : light1_ambient[2] = .8;  break;			
	}
}

//////////////////////////////////////////////////////////////////////
void myinit()
{
	glClearColor(0.12,0.12, 0.12, 1.0);
	glColor3f(1,0.6,0.8);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_spec);

	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_spec);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_dir);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, light1_exp);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, light1_cutoff);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_amb);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glEnable(GL_LIGHTING);
	/*glClearColor(0.0,0.0,0.0,0.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	glOrtho(-20., 20., -20., 20., -20., 20.);
	glMatrixMode(GL_MODELVIEW);*/
}
////////////////////////////
void general_menu(int id)
{
}

