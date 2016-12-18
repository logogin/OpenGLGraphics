/*
*
*	Rotating cube. SINGLE and DOUBLE buffering (two windows).
*
*/

#include "glut.h"
GLUquadricObj *galil; //defenition of galil
void  s_f(unsigned char c, int x,int y);
GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
		{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0},{0.0,-2.5,0.0},
/////////////////////////////////////////////////////////////
{-0.4,-0.6,-1.1},{-0.1,-.6,-1.1},{-0.1,0.4,-1.1},{-0.4,0.4,-1.1}
,{0.5,0.4,-1.1},{0.5,0.2,-1.1},{-0.4,0.2,-1.1}
,{0.5,-0.6,-1.1},{0.2,-0.6,-1.1},{0.2,-0.1,-1.1},{0.5,-0.1,-1.1}
,{0.5,-0.6,1.1},{0.2,-0.6,1.1},{0.2,0.4,1.1},{0.5,0.4,1.1}
,{-.1,.4,1.1},{-.1,.2,1.1},{.2,.2,1.1}
,{-.6,-.6,1.1},{-.6,-.3,1.1},{0.2,-0.3,1.1}};



float directions = 1., directiond = 1.;
int  singleb, doubleb;


void polygon(int a, int b, int c , int d)
{
	glBegin(GL_POLYGON);
		glVertex3fv(vertices[a]);
		glVertex3fv(vertices[b]);
		glVertex3fv(vertices[c]);
		glVertex3fv(vertices[d]);
		glEnd();
}

void make_cube()
{
	glColor3f(1.,0.,0.);
	polygon(0,3,2,1);
	glColor3f(1.,1.,0.);
	polygon(2,3,7,6);
	glColor3f(0.,1.,0.);
	polygon(0,4,7,3);
	glColor3f(0.,1.,1.);
	polygon(1,2,6,5);
	glColor3f(0.,0.,1.);
	polygon(4,5,6,7);
	glColor3f(1.,0.,1.);
	polygon(0,1,5,4);
    
	
	glColor3f(0.8,0.,0.5);
	polygon(0,8,1,0);
    glColor3f(0.5,0.2,0.2);
	polygon(1,8,5,1);
	glColor3f(0.3,0.8,0.5);
	polygon(8,5,4,8);
    glColor3f(0.7,0.0,1.);
	polygon(4,0,8,4);
	glColor3f(0.0,0.0,1.);
	polygon(9,10,11,12);
	glColor3f(0.0,0.0,1.);
	polygon(11,13,14,15);
	glColor3f(0.0,0.0,1.);
	polygon(16,17,18,19);
    glColor3f(1.0,0.0,0.);
	polygon(20,21,22,23);
	glColor3f(1.0,0.0,0.);
	polygon(23,24,25,26);
    glColor3f(1.0,0.0,0.);
	polygon(27,28,29,21);

	glPushMatrix();    //
	glTranslatef(0,0.0,0.0);
	glColor3f(0.5,1.0,1.);
	glRotatef(-90.,1.,0.,0.);
	gluCylinder(galil,0.1,0.45,2,15,15);
	glPopMatrix();

}


void disp_cubes(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	make_cube();

	glFlush();
}

void disp_cubed(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	make_cube();

	glutSwapBuffers ();		// Swapping buffers

	glFlush();
}

void rotate(void)  // Idle
{
	// rotating the cube while Idle
	// single
	glutSetWindow(singleb);
	glRotatef(0.5*directions, 1., 1., 1.);
    glutPostRedisplay();
	// double
	glutSetWindow(doubleb);
	glRotatef(0.5*directiond, 0.1, 1., 0.);
    
	glutPostRedisplay();
}

void directs(int button, int state, int x, int y)
{
	// changing the direction of the rotation according to 
	// the mouse button have been pressed (for SINGLE)

	if(button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN)
		directions = -1;
	if(button == GLUT_RIGHT_BUTTON  && state == GLUT_DOWN)
		directions = 1;
}

void directd(int button, int state, int x, int y)
{
	// changing the direction of the rotation according to 
	// the mouse button have been pressed (for DOUBLE)

	if(button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN)
		directiond = -1;
	if(button == GLUT_RIGHT_BUTTON  && state == GLUT_DOWN)
		directiond = 1;
}

void initial(void)
{
	// initialization
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	glOrtho(-4., 4., -4., 4., -4., 4.);
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	// First window - single buffered
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(200, 200);
	singleb = glutCreateWindow("SINGLE BUFFERED");
	glutDisplayFunc(disp_cubes);	// display callback function
	// to draw a galil we put theis 2 lines
    galil=gluNewQuadric();
//name of galil , will be filled we will not see it like a net
//	gluQuadricDrawStyle(galil,GLU_FILL);

	
	
	
	glutIdleFunc(rotate);		// idle callback function
	glutMouseFunc(directs);		// mouse callback function
    glutKeyboardFunc(s_f); // callback of keyboard
	initial();

	// Second window - double buffered
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(250, 0);
	glutInitWindowSize(500, 500);
	doubleb = glutCreateWindow("DOUBLE BUFFERED");
	glutDisplayFunc(disp_cubed);	// display callback function
	glutIdleFunc(rotate);		// idle callback function
	glutMouseFunc(directd);		// mouse callback function
	glutKeyboardFunc(s_f);// callback of keyboard
	initial();
	glutMainLoop();



}

void s_f(unsigned char c, int x,int y)
{
	int i;

	i=glutGetWindow();
	if(i==doubleb){
		
		if(c=='q'||c=='Q')
		     exit(1);
		else{
		if(c=='s'||c=='S') 
			directiond/=1.2;
		
		if(c=='f'||c=='F')
			directiond*=1.2;
		}		
         
	}
       

	
	if(i==singleb){
		if(c=='s'||c=='S') 
			directions/=1.2;
		if(c=='f'||c=='F') 
			directions*=1.2;
	}	

}


