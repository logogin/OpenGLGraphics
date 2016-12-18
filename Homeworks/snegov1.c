/* 
* 
* 'robot1.c' program (see Week7) with additional changes. 
* Here we define traverse tree to display the object. 
* 
*/

#include "glut.h"
#include <stdlib.h>
#include <math.h>

#define BASE_HEIGHT 3.0 
#define BASE_RADIUS 1.0 
#define LOWER_ARM_HEIGHT 5.0 
#define LOWER_ARM_WIDTH 0.5 
//#define UPPER_ARM_HEIGHT 5.0 
#define UPPER_ARM_WIDTH 0.5

// This structure defines a node of the tree
typedef struct treenode
{       GLfloat m[16];
        void (*f)();
        struct treenode *sibling;
        struct treenode *child;
}treenode; 

static GLfloat theta[] = {0.0,0.0,0.0,0.0}; 
static GLint axis = 0;
float angle1=0,angle2=360,angle3=0;
float y,x=1.5,i,j;
float angl_x=0 ,angl_y=0,angl_z=0;
//////////////////////////////
static GLfloat lightPosition[4];
//////////////////////////////        ///////////            ////////////     /////
GLfloat light0_pos[] = {3., 5., 3., 1.};
GLfloat light0_dir[] = {-1.,- 1., -1., 0.};
GLfloat light0_ambient[] = {.5, .5., .5, 1.};
GLfloat light0_diffuse[] = {.5, .5, .5, 1.};
GLfloat light0_spec[] = {1., 1., 1., 1.};
GLfloat global_amb[] = {2.2, 2.2, 0.2, 1.};

//      Material properties
GLfloat mat_ad[4][4] = {{0., 0., 0., 1.}, {.15, 0., .15, 1.},
                                        {.5, 0., .5, 1.}, {1., 0., 1., 1.} };
GLfloat mat_s[4][4] = {{0., 0., 0., 1.}, {.15, .15, .15, 1.},
                                        {.5, .5, .5, 1.}, {1., 1., 1., 1.} };
GLfloat shine[3] = { 5., 40., 120. };
GLfloat zoom_x=0,zoom_y=0;

/////////////////////////////////////////////         //////////         //////

// Our tree consists of three nodes
treenode base_node, lower_arm_node, upper_arm_node,left_arm_node;

// This is a recursive function that traverses the tree
void traverse(treenode* root)
{       if(root==NULL) return;
        glPushMatrix();
        glMultMatrixf(root->m);
        root->f();
        if(root->child!=NULL) traverse(root->child);
        glPopMatrix();
        if(root->sibling!=NULL) traverse(root->sibling);
}

void base() 
{ 
	    glPushMatrix();
        //glRotatef(-90.0, 1.0, 0.0, 0.0);
		//glutSolidSphere(3,25,25);
        glPushMatrix();
		 glTranslatef(0.0,2.0,0.0);
         glScalef(1.3, 0.5, 2.3);
		glutSolidCube(4);

		glPushMatrix();
		glTranslatef(1.0,0.0,0.0);
		glutSolidSphere(2,10,10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-1.0,0.0,0.0);
		glutSolidSphere(2,10,10);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-1.6,1.0,3.0);
		glRotatef( 90.0, 0.0, 1.0, .0);
		glutSolidTorus(.5,1,7,11);
        glPopMatrix(); 

		glPushMatrix();
		glTranslatef(-1.6,1.0,-3.0);
		glRotatef( 90.0, 0.0, 1.0, .0);
		glutSolidTorus(.5,1,7,11);
        glPopMatrix(); 

			glPushMatrix();
		glTranslatef(1.6,1.0,3.0);
		glRotatef( 90.0, 0.0, 1.0, .0);
		glutSolidTorus(.5,1,7,11);
        glPopMatrix(); 

		glPushMatrix();
		glTranslatef(1.6,1.0,-3.0);
		glRotatef( 90.0, 0.0, 1.0, .0);
		glutSolidTorus(.5,1,7,11);
        glPopMatrix(); 
glPopMatrix();
}

void lower_arm() 
{ 
	    glPushMatrix();
		//glRotatef(-90.0, 1.0, 0.0, 0.0);
        glTranslatef(0.0,0.9,0.0);
		glColor3f(1.,0.7,0.1);
        glutSolidSphere(2,20,20);
        glPopMatrix(); 
}

void left_arm() 
{ 
        
	    glPushMatrix();
		glTranslatef(1.5,-3.5,0.0);
		glColor3f(1.0,0.0,0.0);
        glutSolidSphere(1,10,10);
        glPushMatrix(); 
		glRotatef(-60.0, 1.0, 0.0, -1.0);
        glScalef(0.1, 0.1, 14);
		glutSolidCube(1);
		glPopMatrix();
        
        glTranslatef(-4.8,0.0,0.0);
		glColor3f(1.0,0.0,0.0);
        glutSolidSphere(1,10,10);

		// glTranslatef(0.0,2.0,0.0);
		glRotatef(-60.0, 1.0, 0.0, 1.0);
        glScalef(0.1, 0.1, 14);
		glutSolidCube(1);

        glPopMatrix(); 
}

void upper_arm()
{       glPushMatrix();
//gluLookAt(0., 0., 10., 0., 0., 0., 1., 1., 0.);
	    //glRotatef(-90.0, 1.0, 0.0, 0.0);
        glTranslatef(0.0,-1.0 ,0.0);
        //glScalef(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, UPPER_ARM_WIDTH);
		glutSolidSphere(1.3,15,15);
		glPushMatrix();
		  glPushMatrix();
			glRotatef(-90.0, 1.0, 0.0, 0.0);
	       glTranslatef(0.0,0.0 ,0.9);	   
		   glColor3f(1.0, 0.6, 0.0);
           glutSolidCone(2.4,1,7,11);
			glPopMatrix();
		    //glRotatef(-90.0, 1.0, 0.0, 0.0);
			glPushMatrix();
		   glTranslatef(0.0,0.0 ,1.2);
		   glColor3f(0.0, 0.6, 1.0);
		   glutSolidCone(0.4,2,7,11);
		   glPopMatrix();
        glPopMatrix();
}

void display(void)
{       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
		glTranslatef(0., -5., -40.);
        glColor3f(1.0, 0.6, 1.0);
        traverse(&base_node);
		glLoadIdentity();
		glPushMatrix();
		glTranslatef(0., -5., -40.);
        gluLookAt(cos(angle3), 0.,sin(angle3), 0., 0., 0., 0., 1., 0.);
		for( y=13;y>-4;y--)
		{
			glPushMatrix();
			    glTranslatef(7.0,y,3.0);
				glRotatef(-90.0, 1.0, 0.0, 0.0);
			    glColor3f(1.0, 0.6, 1.0);
			    glutSolidCone(x,2,7,7);
			glPopMatrix();
			x+=0.3;
		}
		x=0;
		glPopMatrix();

 glFlush();
        glutSwapBuffers(); 
}

///////////////////////////////////////////////////////////////

// The keyboard callback 
void keyboard(unsigned char ch, int x, int y) 
{
	
/* 'l' increase joint angle, 'r' decreases it */
        if(ch == 'L' || ch == 'l')
        {
			if(axis==3)
			{
			theta[axis] += 5.0;
        if( theta[axis] > 30.0 ) theta[axis] -= 30.0;
			}
			else
			{
		theta[axis] += 5.0;
        if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
			}

        }
        if(ch == 'R' || ch == 'r')
        { 
			if(axis==3)
			{
			theta[axis] -= 5.0;
        if( theta[axis] < -30.0 ) theta[axis] += 30.0;
			}
			else
			{
		theta[axis] -= 5.0;
        if( theta[axis] < 0.0 ) theta[axis] += 360.0;
			}		
        }
		if(ch =='Z' || ch== 'z')
		{
			angl_x-=0.5;
		}
		if(ch =='X' || ch== 'x')
		{
			angl_x+=0.5;
		}
		if(ch =='C' || ch== 'c')
		{
			angl_y-=0.5;
		}
		if(ch =='D' || ch== 'd')
		{
			angl_y+=0.5;
		}
			if(ch =='a' || ch== 'A')
		{
			angl_z-=0.5;
		}
		if(ch =='S' || ch== 's')
		{
			angl_z+=0.5;
		}
        
        glPushMatrix();
		
        switch(axis)
        {       case 0 :glLoadIdentity();
		glTranslatef(angl_x,angl_y,angl_z);
                                glRotatef(theta[0], 0.0, 1.0, 0.0);
                                glGetFloatv(GL_MODELVIEW_MATRIX,base_node.m);
                                break;
                case 1 :glLoadIdentity();
                                glTranslatef(0.0, BASE_HEIGHT, 0.0);
                                glRotatef(theta[1], 0.0, 1.0, 0.0);
                                glGetFloatv(GL_MODELVIEW_MATRIX,lower_arm_node.m);
                                break;
                case 2 :glLoadIdentity();
                                glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);
                                glRotatef(theta[2], 0.0, 1.0, 0.0);
                                glGetFloatv(GL_MODELVIEW_MATRIX,upper_arm_node.m);
                                break;
				case 3 :glLoadIdentity();
                                glPushMatrix();
                                glTranslatef(1.0, 5.0, 0.0);
								glPushMatrix();
                                glRotatef(theta[3], 1.0, 0.0, 0.0);
                                glGetFloatv(GL_MODELVIEW_MATRIX,left_arm_node.m);
								glPopMatrix();
								glPopMatrix();								
                                break;
			
        }

        glPopMatrix();
        glutPostRedisplay(); 
}

// Menu function 
void menu(int id)
{       if(id == 1) axis = 0;
        if(id == 2) axis = 1;
        if(id == 3) axis = 2;
		if(id == 4) axis = 3;
        if(id == 6) exit(1); 
}

// The reshape callback 
void myReshape(int w, int h) 
{ glViewport(0, 0, w,h);
        glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
/*    if (w <= h)
        glOrtho(-20.0, 20.0, -10.0 * (GLfloat) h / (GLfloat) w,
                30.0 * (GLfloat) h / (GLfloat) w, -20.0, 20.0);
    else
        glOrtho(-20.0 * (GLfloat) w / (GLfloat) h,
        20.0 * (GLfloat) w / (GLfloat) h, -10.0, 30.0, -20.0, 20.0);
*/	gluPerspective(60., (GLfloat) w/(GLfloat) h, .1, 90.);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
}

// Initialization 
void myinit() 
{ glClearColor(0.0, 0.0, 0.0, 0.0);
        //glColor3f(1.0, 0.6, 1.0);
        glEnable(GL_DEPTH_TEST);
        /* Set up tree */
        glLoadIdentity();
        glRotatef(theta[0], 0.0, 1.0, 0.0);
        glGetFloatv(GL_MODELVIEW_MATRIX, base_node.m);
        base_node.f = base;
        base_node.sibling = NULL;
        base_node.child =  &lower_arm_node;

        glLoadIdentity();
    glTranslatef(0.0, BASE_HEIGHT, 0.0);
    glRotatef(theta[1], 0.0, 0.0, 1.0);
        glGetFloatv(GL_MODELVIEW_MATRIX, lower_arm_node.m);
        lower_arm_node.f = lower_arm;
        lower_arm_node.sibling = NULL;
        lower_arm_node.child = &left_arm_node;

		    glLoadIdentity();
    glTranslatef(1.0,5.0, 0.0);
    glRotatef(theta[3], 0.0, 0.0, 1.0);
        glGetFloatv(GL_MODELVIEW_MATRIX, left_arm_node.m);
        left_arm_node.f = left_arm;
        left_arm_node.sibling = &upper_arm_node;//&upper_arm_node;
        left_arm_node.child = NULL;


        glLoadIdentity();
    glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
        glGetFloatv(GL_MODELVIEW_MATRIX, upper_arm_node.m);
        upper_arm_node.f = upper_arm;
        upper_arm_node.sibling = NULL;
        upper_arm_node.child = NULL;

}
void idle(void)
{
	angle1+=3.;
	if(angle1>360.) angle1 -=360;
	angle2 -=5.;
	if(angle2<0.) angle2+=360.;
	angle3 +=0.04;
	if(angle3>360.) angle3-=360.;
	glutPostRedisplay();
}

void main(int argc, char **argv) 
{
	int i=-1;
	float pos1[4] = {4,10,4,1};
	float pos2[4] = {-6,-4,-3,1};
	float pos3[4] = {0,10,0,1};
	float pos4[4] = {0,-4,-7,1};
	
	float dir[3] = {1,-1,-1};
	GLfloat mat_specular[] = {6,1,6,1};

        glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("robot");
    myinit();
    glutReshapeFunc(myReshape);
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutCreateMenu(menu);
	glutIdleFunc(idle);
    glutAddMenuEntry("base", 1);
    glutAddMenuEntry("lower arm", 2);
    glutAddMenuEntry("upper arm", 3);
	glutAddMenuEntry("left arm", 4);
    glutAddMenuEntry("quit", 5);
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
