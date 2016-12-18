// ROBOT.cpp : Defines the entry point for the console application.
//
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdlib.h>	
#include "glut.h"
#include<math.h>

#define PI          3.1415926
#define SPEED_M	    .3
#define SPEED_R	    .05

GLUquadricObj *galil;
static GLfloat angle[]={0.0, 0.0, 0.0, 0.0};
static GLint axis = 0;
static GLint axis1 = 0;
static GLint axis2 = 0;
static GLint axis3 = 0;
static GLint axis4 = 0;
static GLint axis5 = 0;
int directions=1;
//float angl_x=0 ,angl_y=0,angl_z=0;
//float angle1=0,angle2=360,angle3=0;
GLfloat eyex = 0., eyez = 1., azimuth = PI/2;
int main_wind, plan_wnd = 0;

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

void Robot_plan(void);
/*void DrawRobot         (void);
void init_structures   (void);
void struct_bust       (void);
void struct_pelvis     (void);
void struct_Right_hend (void);
void struct_Left_hend  (void);
void struct_Right_hdown(void);
void struct_Left_hdown (void);
void struct_Right_leg  (void);
void struct_Left_leg   (void);
void struct_Right_ldown(void);
void struct_Left_ldown (void);
void struct_head       (void);
void SetMaterial(GLfloat spec[], GLfloat amb[], GLfloat diff[], GLfloat shin[]);*/

//////////////////////////////////STRUCTURE////////////////////////////////
/*void init_structures   (void)
{
 struct_bust       ();
 struct_pelvis     ();
 struct_Right_hend ();
 struct_Left_hend  ();
 struct_Right_hdown();
 struct_Left_hdown ();
 struct_Right_leg  ();
 struct_Left_leg   ();
 struct_Right_ldown();
 struct_Left_ldown ();
 struct_head       ();


}*/


//////////////////////////////////////////////////
/*void struct_bust()
{ 
	glNewList(bust,GL_COMPILE);
	SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
    glColor3f(1.0,1.0,1.0);
	glScalef(1.8,1.0,1.0);
	glutSolidSphere(0.6,10,5);
	glTranslatef(0.0,-0.75,0.0);
	glScalef(1.0,1.0,1.0);
	SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
	glColor3f(1.0,1.0,0.0);
	glutSolidCube(0.5);
	glTranslatef(0,0.3,0);
	SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
	glColor3ub(128,128,128);
	glutSolidSphere(0.5,5,5);
	
	/*SetMaterial(mat_specularBLUE, mat_ambientBLUE, mat_diffuseBLUE, mat_shininessBLUE);
	glColor3ub(0,0,255);
	glScalef(1.0,0.2,1.0);
	glutSolidCube(1.0);*/
//	glScalef(1.0,0.2,1.0);
//	glEndList();
//}
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
   // glColor3f(5.0,1.0,0.0);
	glTranslatef(-2.3,4.3,0.0);
	glScalef(0.5,0.7,0.5);
	glColor3f(0.45,1.4,1.4);
	glutSolidSphere(1.5,20,20);

	glTranslatef(0.0,-2.0,0.0);
	glScalef(1.3,4.5,1.3);
	glColor3f(1.,1.,0.);
	glutSolidCube(1.0);
	glPopMatrix();
}/********************************/
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

}/**************************/

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
}/****************************************/
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
	/*glClearColor(0., 0., 0., 0.);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glRotatef(1.9*directions, 0., 1., 0.);*/
  glPushMatrix();
    glTranslatef(0.,5.,0.);
    glColor3f(1.45,1.34,1.34);
	glScalef(1.8,1.0,1.0);
	glutSolidSphere(2.5,11,15);
	
	glTranslatef(0,-1.,0);
	glColor3f(1.45,1.34,1.34);
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
	 glRotatef(angle[1],1.0,0.0, 0.0 );
	 glTranslatef(0.0,-5.,0.0);
     struct_Left_hand ();
   /************************/  
	 glPushMatrix();
	 glTranslatef(0.0,1.,0.0);
	 glRotatef(angle[2],1.0,0.0, 0.0 );
	 glTranslatef(0.0,-1.,0.0);
     struct_Left_hdown (); 
	 glPopMatrix();
	  glPopMatrix();
//////////////////[Right hand]////////////////////
  glPushMatrix();
	 glTranslatef(0.0,5.,0.0);
	 glRotatef(angle[4],1.0,0.0, 0.0 );
	 glTranslatef(0.0,-5.,0.0);
      struct_Right_hand ();
	  /************************/
     glPushMatrix();
	 glTranslatef(0.0,1.,0.0);
	 glRotatef(angle[3],1.0,0.0, 0.0 );
	 glTranslatef(0.0,-1.,0.0);
	 struct_Right_hdown (); 
	 glPopMatrix();
  glPopMatrix();
/////////////////////////////////////////////////
glPushMatrix();//Left leg
   	 glTranslatef(0.0,0.,0.0);
	 glRotatef(angle[5],1.0,0.0, 0.0 );
	 glTranslatef(0.0,0.,0.0);
     struct_Left_leg ();	

     
    glPushMatrix();///down
	 glTranslatef(-1.3,-3.9,0.0);
	 glRotatef(angle[6],1.0,0.0, 0.0 );
	 glTranslatef(0.0,-1.,0.0);
     struct_Left_ldown ();
	 glPopMatrix();    
	glPopMatrix();
/*************[right leg]********************/
 glPushMatrix();
	 
	 glTranslatef(0.0,0.,0.0);
	 glRotatef(angle[7],1.0,0.0, 0.0 );
	 glTranslatef(0.0,0.,0.0);
     struct_Right_leg ();	
	 
	 
	 glPushMatrix();
	 glTranslatef(0.0,-3.7,0.0);
	 glRotatef(angle[8],1.0,0.0, 0.0 );
	 glTranslatef(0.0,3.7,0.0);
	 struct_Right_ldown ();
	 glPopMatrix(); 
 
 glPopMatrix(); 

 

  glPopMatrix();//For all body
//  glutSwapBuffers ();	
//	glFlush();
}
void display()
{
glClearColor(0., 0., 0., 0.);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
	gluLookAt(	eyex, 0., eyez,
				eyex + cos(azimuth), 0., eyez - sin(azimuth),
				0., 1., 0.);

  Robot_plan();
glutSwapBuffers ();	
	glFlush();
}
void rotate(void)
{
		
	glRotatef((1.9)*directions, 0., 1., 0.);
	glTranslatef(0.0,0.,0.0);	
	glutPostRedisplay();
	
	

}


void keyboard(unsigned char key,int x,int y)
{
	////////////////////Left hend////////////////////////
	if(key =='J' || key =='j')//work with menu
	{ angle[axis1] += 5.0;
        if( angle[axis1] > 360.0 ) angle[axis1] -= 360.0;
	}
if(key== 'H' || key == 'h')
	{ angle[axis1] -= 5.0;
        if( angle[axis1] < 0.0 ) angle[axis1] += 360.0;
	}

if(key =='L' || key== 'l')
	{ 
        if( angle[axis] < 0.0 ) angle[axis] += 5.0;
	}
	if(key== 'K' || key == 'k')
	{ angle[axis] -= 5.0;
        if( angle[axis] < -135.0 ) angle[axis] += 5.0;
	}
	//////////////////Right hend/////////////////////////

if(key =='D' || key =='d')
	{ 
        if( angle[axis] < 0.0 ) angle[axis] += 5.0;
	}
if(key== 'F' || key == 'f')
	{ angle[axis] -= 5.0;
        if( angle[axis] < -135.0 ) angle[axis] += 5.0;
	}
if(key =='A' || key =='a')
	{ angle[axis1] += 5.0;
        if( angle[axis1] > 360.0 ) angle[axis1] -= 360.0;
	}
if(key== 'S' || key == 's')
	{ angle[axis1] -= 5.0;
        if( angle[axis1] < 0.0 ) angle[axis1] += 360.0;
	}

/////////////////[ Left leg ]////////////////////////////////

if(key =='W'|| key =='w')
	{ 
        if( angle[axis2] < 25.0 ) angle[axis2] += 5.0;
	}
	if(key== 'E'||key== 'e' )
	{ angle[axis2] -= 5.0;
        if( angle[axis2] < -125.0 ) angle[axis2] += 5.0;
	}

	if(key =='R' || key =='r')
	{ angle[axis3] -= 5.0;
        if( angle[axis3] <0.0 ) angle[axis3] += 5.0;
	}
if(key== 'T' || key == 't')
	{ angle[axis3] += 5.0;
        if( angle[axis3] > 90.0 ) angle[axis3] += 5.0;
	}

/////////////////[ Right leg ]////////////////////////////////
if(key =='P' || key== 'p')
	{ 
        if( angle[axis4] < 25.0 ) angle[axis4] += 5.0;
	}
	if(key== 'O' || key == 'o')
	{ angle[axis4] -= 5.0;
        if( angle[axis4] < -125.0 ) angle[axis4] += 5.0;
	}

if(key =='I' || key =='i')
	{ angle[axis5] -= 5.0;
        if( angle[axis5] <0.0 ) angle[axis5] += 5.0;
	}
if(key== 'U' || key == 'u')
	{ angle[axis5] += 5.0;
        if( angle[axis5] > 90.0 ) angle[axis5] += 5.0;
	}
/////////////////////////////////////////////////
float spd_m = SPEED_M, spd_r = SPEED_R;
	if(glutGetModifiers() == GLUT_ACTIVE_SHIFT)
	{	spd_m *= .1;
		spd_r *= .1;
	}
	if(key == '8'/*GLUT_KEY_UP*/) 
	{	eyex += spd_m*cos(azimuth);
		eyez -= spd_m*sin(azimuth);
	}
	if(key == '2'/*GLUT_KEY_DOWN*/)
	{	eyex -= spd_m*cos(azimuth);
		eyez += spd_m*sin(azimuth);
	}
	if(key == '7'/*GLUT_KEY_LEFT*/)	azimuth += spd_r;
	if(key == '9'/*GLUT_KEY_RIGHT*/)	azimuth -= spd_r;
	if(azimuth > 2*PI) azimuth -= 2*PI;
	if(azimuth < 0.) azimuth += 2*PI;
	if(eyex < -15.)	eyex = -15.;
	if(eyex > 15.)	eyex = 15.;
	if(eyez < -15.)	eyez = -15.;
	if(eyez > 15.)	eyez = 15.;
	/*if(key == GLUT_KEY_F1)
	{	if(!plan_wnd)	create_plan();
		else
		{	glutDestroyWindow(plan_wnd);
			plan_wnd = 0;
	}	}
	if(key == GLUT_KEY_F10)	exit(1);
	glutSetWindow(main_wind);*/
	glutPostRedisplay();
	/*if(plan_wnd)
	{	glutSetWindow(plan_wnd);
		glutPostRedisplay();
	}
	glutSetWindow(main_wind);*/
///////////////////[ EXIT ]//////////////////////////////
	if(key == 'Q' || key == 'q')
	{
     exit(1);	
	}
	display(); 
}/*******************************/
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
///////////////////////////////////////////////////////////////////////
/*void myReshape(int w,int h)
{
  glViewport(0, 0, w,h);
        glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
/*    if (w <= h)
        glOrtho(-20.0, 20.0, -10.0 * (GLfloat) h / (GLfloat) w,
                30.0 * (GLfloat) h / (GLfloat) w, -20.0, 20.0);
    else
        glOrtho(-20.0 * (GLfloat) w / (GLfloat) h,
        20.0 * (GLfloat) w / (GLfloat) h, -10.0, 30.0, -20.0, 20.0);
*/
//	gluPerspective(60., (GLfloat) w/(GLfloat) h, .1, 90.);
  // glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity(); 

//}
//////////////////////////////////////////////////////////////////////
void myinit()
{
glClearColor(0.0,0.0,0.0,0.0);
glEnable(GL_DEPTH_TEST);
glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	glOrtho(-20., 20., -20., 20., -20., 20.);
	glMatrixMode(GL_MODELVIEW);

}
/*void idle(void)
{
	angle1+=3.;
	if(angle1>360.) angle1 -=360;
	angle2 -=5.;
	if(angle2<0.) angle2+=360.;
	angle3 +=0.04;
	if(angle3>360.) angle3-=360.;
	glutPostRedisplay();
}*/
/////////////////////////////////////////////////////////////////////
void main(int argc, char* argv[])
{

  int i=-1;
  float pos1[4] = {3,6,3,1};/*{1,5,7,1};*/
  float pos2[4] = {3,6,3,1};/*{5,-4,-3,1};*/
  float pos3[4] = {3,6,3,1}; /*{0,10,0,1};*/
  float pos4[4] = {3,6,3,1}; /*{0,-4,-7,1};*/
	
	float dir[3] = {1,-1,-1};
	GLfloat mat_specular[] = {6,1,6,1};

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    main_wind=glutCreateWindow("ROBOT-ROBERT");
     myinit();
     //glutReshapeFunc(myReshape);
	 glutDisplayFunc(display);
	// glutIdleFunc(rotate);

    galil=gluNewQuadric();
	gluQuadricDrawStyle(galil,GLU_FILL);

	glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutCreateMenu(menu);
	//glutIdleFunc(idle);

    glutAddMenuEntry("left hend:(H,J)", 1);
    glutAddMenuEntry("left down hend:(L,K)", 2);
    glutAddMenuEntry("right down hend:(D,F)", 3);
	glutAddMenuEntry("right hend:(A,S)", 4);
	glutAddMenuEntry("left leg :(W,E)", 5);
	glutAddMenuEntry("left down leg :(R,T)", 6);
	glutAddMenuEntry("right leg :(O,P)", 7);
	glutAddMenuEntry("right down leg :(U,I)", 8);
    glutAddMenuEntry("quit           :(Q)", 9);
    glutAttachMenu(GLUT_LEFT_BUTTON);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);


	glLightfv(GL_LIGHT0,GL_POSITION,pos1);
	glLightfv(GL_LIGHT1,GL_POSITION,pos2);
	glLightfv(GL_LIGHT0,GL_POSITION,pos3);
	glLightfv(GL_LIGHT1,GL_POSITION,pos4);


	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,dir);

	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialf(GL_FRONT,GL_SHININESS,28.0);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);

glutMainLoop();
	
}
