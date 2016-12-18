/*
Howm Work2.Andreenko Dmitry
*/

#include "glut.h"
GLUquadricObj *galil; //defenition of galil
void  s_f(unsigned char c, int x,int y);
GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
		{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0},{0.0,-2.5,0.0},
////////////////////////[GIMEL]/////////////////////////////////
{-0.5,0.5,1.1},{0.0,0.5,1.1},{0.0,0.25,1.1},{-0.5,0.25,1.1},
{0.5,-0.5,1.1},{0.25,-0.5,1.1},{0.125,0.0,1.1},{0.16,-0.125,1.1},
{-0.5,-0.5,1.1},{-0.25,-0.5,1.1},
////////////////////////[PEI]//////////////////////////////////
{-0.5,0.5,-1.1},{-0.5,0.2,-1.1},{0.5,0.5,-1.1},{0.5,0.2,-1.1},
{-0.5,-0.5,-1.1},{-0.2,-0.5,-1.1},{-0.2,0.5,-1.1},/*23*/{-0.5,-0.35,-1.1},
{0.5,-0.35,-1.1},{0.5,-0.5,-1.1},/*28*/{0.5,-0.5,-1.1},
{0.5,0.0,-1.1},{0.35,0.0,-1.1},{0.35,0.5,-1.1},
/////////////////////////[NUN]/////////////////////////////////
/*33*/{1.1,0.125,-0.5},{1.1,-0.5,-0.45},{1.1,-0.5,-0.35},{1.1,0.125,-0.35},
/*37*/{1.1,-0.5,0.5},{1.1,-0.35,0.5},{1.1,-0.35,-0.49},
/*40*/{1.1,0.0,-0.5},{1.1,0.0,-0.25},{1.1,0.125,-0.25},
/////////////////////////[HEI]////////////////////////////////
/*43*/{-1.1,0.5,0.5},{-1.1,0.35,0.5},{-1.1,0.35,-0.5},{-1.1,0.5,-0.5},
/*47*/{-1.1,-0.5,0.5},{-1.1,-0.5,0.25},{-1.1,0.5,0.25},
/*50*/{-1.1,0.0,-0.25},{-1.1,-0.5,-0.25},{-1.1,-0.5,-0.5},{-1.1,0.0,-0.5}};



float directions = 1., directiond = 1.;
int  singleb, doubleb;

 void draw_string_stroke(void *font, const char* string) //Fonts draw
{
  while (*string)
    glutStrokeCharacter(font, *string++);
}

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
    
	
	glColor3f(0.,1.,0.);//gimel
	polygon(9,10,11,12);
	glColor3f(0.,1.,0.);
	polygon(10,11,13,14);
	glColor3f(0.,1.,0.);
	polygon(15,16,17,18);
////////////////////////////////////////
	glColor3f(0.,0.,1.);//pei
	polygon(19,20,21,22);
	glColor3f(0.,0.,1.);
	polygon(19,23,24,25);
	glColor3f(0.,0.,1.);
	polygon(23,26,27,28);
    glColor3f(0.,0.,1.);
	polygon(21,30,31,32);
////////////////////////////////////////
	glColor3f(1.,0.,0.);//nun
	polygon(33,34,35,36); 
    glColor3f(1.,0.,0.);
	polygon(34,37,38,39); 
    glColor3f(1.,0.,0.);
	polygon(33,40,41,42); 
////////////////////////////////////////
    glColor3f(1.,1.,1.);//hei
	polygon(43,44,45,46); 
    glColor3f(1.,1.,1.);
	polygon(43,47,48,49); 
    glColor3f(1.,1.,1.);
	polygon(50,51,52,53); 


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
	
	glPushMatrix();    //
	glTranslatef(0,0.0,0.0);
	glRotatef(-90.,1.,0.,0.);
	glColor3f(0.0,0.78,0.78);
	gluCylinder(galil,0.45,0.45,2,15,15);
	glPopMatrix();

}


void disp_cubes(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
     glLineWidth(2.0);
	 glPushMatrix();
     glLoadIdentity();
	 glTranslatef(-7.0,7.0,0.0);
	 glScalef(0.01,0.01,0.01);
     glColor3f(1.0,0.0,1.0);
	 draw_string_stroke(GLUT_STROKE_ROMAN, "Sevivon Double Buffer");
	 glFlush();
	 glPopMatrix();

	make_cube();

	glFlush();
}

void disp_cubed(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLineWidth(3.0f);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(-7.0, 7.0, 0.0);
	glScalef(0.01f, 0.01f, 0.01f);
	glColor3f(1.0,0.0,1.0);
	draw_string_stroke(GLUT_STROKE_ROMAN, "Sevivon Double Buffer");
	glFlush();
	glPopMatrix();

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
    //glTranslatef(-0.01,0.0,0.0);
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
	glOrtho(-9., 9., -9., 9., -9.,9.);
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
	//gluQuadricDrawStyle(galil,GLU_FILL);

	
	
	
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


