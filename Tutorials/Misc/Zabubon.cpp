#include <iostream.h>
#include <math.h>
#include <GL/glut.h>

const GLfloat zabubon[17][3]={{0.0,-4,0.0},{2.0,-1.0,2.0},
						{2.0,-1.0,-2.0},{-2.0,-1.0,-2.0},
						{-2.0,-1.0,2.0},/*pyramid*/
						{2.0,4.0,2.0},{2.0,4.0,-2.0},
						{-2.0,4.0,-2.0},{-2.0,4.0,2.0},/*cube*/
						{0.5,4.0,0.5},{0.5,4.0,-0.5},
						{-0.5,4.0,-0.5},{-0.5,4.0,0.5},
						{0.5,8.0,0.5},{0.5,8.0,-0.5},
						{-0.5,8.0,-0.5},{-0.5,8.0,0.5}/*handle*/};
const GLubyte zabubon_indeces[52]={0,4,1,
								0,1,2,
								0,2,3,
								0,3,4,/*pyramid*/
								4,8,5,1,
								1,5,6,2,
								2,6,7,3,
								3,7,8,4,
								8,7,6,5,/*cube*/
								12,16,13,9,
								9,13,14,10,
								10,14,15,11,
								11,15,16,12,
								13,14,15,16/*handle*/};

const GLfloat zabubon_colors[17][3]={{1.0,0.0,0.0},{0.0,1.0,0.0},
{0.0,0.0,1.0},{1.0,1.0,0.0},{1.0,0.0,1.0},{0.0,1.0,1.0},
{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,1.0,0.0},
{1.0,0.0,1.0},{0.0,1.0,1.0},{1.0,0.0,0.0},{0.0,1.0,0.0},
{0.0,0.0,1.0},{1.0,1.0,0.0},{1.0,0.0,1.0}};

GLsizei ww=500,wh=500;
GLdouble omega_top;
GLdouble omegay;
GLdouble omegaz;

GLdouble theta_top=15.0;
GLdouble thetay=5.0;
GLdouble thetaz=0.1;

void draw_zabubon()
{
	
	glDrawElements(GL_TRIANGLES/*GL_LINE_LOOP*/,12,
		GL_UNSIGNED_BYTE,zabubon_indeces);
	for (int i=0; i<5; i++)
	{
		glDrawElements(GL_QUADS/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,zabubon_indeces+12+4*i);
		
		glDrawElements(GL_QUADS/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,zabubon_indeces+32+4*i);
	}
}

void reset()
{
	theta_top=15.0;
	thetay=5.0;
	thetaz=0.1;
	omega_top=0.0;
	omegay=0.0;
	omegaz=0.0;
	glutPostRedisplay();
}

void inc_speed()
{
	if (theta_top<30)
			theta_top+=0.5;
		glutPostRedisplay();
}

void dec_speed()
{
	if (theta_top>0)
			theta_top-=0.5;
		glutPostRedisplay();
}

void fall_right()
{
	theta_top=10.0;
	omega_top=0.0;
	thetay=5.0;
	omegay=0.0;
	thetaz=0.1;
	omegaz=0.0;
	glutPostRedisplay();
	omegaz=20.0;
	glutPostRedisplay();
}

void fall_left()
{
	theta_top=10.0;
	omega_top=0.0;
	thetay=5.0;
	omegay=0.0;
	thetaz=-0.1;
	omegaz=0.0;
	glutPostRedisplay();
	omegaz=-20.0;
	glutPostRedisplay();
}
 
void top_menu(int id)
{
	switch (id)
	{
	case 1:
		reset();
		break;
	case 2:
		inc_speed();
		break;
	case 3:
		dec_speed();
		break;
	case 4:
		fall_right();
		break;
	case 5:
		fall_left();
		break;
	case 6:
		exit(0);
	}
}

void my_init()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glViewport(0,0,ww,wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15.0,15.0,-15.0,15.0,-15.0,15.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,zabubon);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3,GL_FLOAT,0,zabubon_colors);
	glutCreateMenu(top_menu);
	glutAddMenuEntry("reset",1);
	glutAddMenuEntry("increase top speed",2);
	glutAddMenuEntry("decrease top speed",3);
	glutAddMenuEntry("fall right",4);
	glutAddMenuEntry("fall left",5);
	glutAddMenuEntry("quit",6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
//	glRotatef(90,1.0,0.0,0.0);
}

void change_velocity()
{
	if (theta_top>0.0)
	{
		omega_top+=theta_top;
		theta_top-=0.01;
		if (omega_top>360.0)
				omega_top-=360.0;
		if (theta_top<10.0)
		{
			omegay+=thetay;
			thetay+=0.01;
			
			if (omegay>360.0)
				omegay-=360.0;
			if ((omegaz<80.0&&thetaz>0.0)||(omegaz>-80.0&&thetaz<0.0))
				omegaz+=thetaz;
		}
	}
}	

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glTranslatef(0.0,-4.0,0.0);
		glRotatef(omegay,0.0,1.0,0.0);
		glPushMatrix();
			glRotatef(omegaz,0.0,0.0,1.0);
			glTranslatef(0.0,4.0,0.0);
			glRotatef(omega_top,0.0,1.0,0.0);
			draw_zabubon();
		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
	change_velocity();
}

void reshape(GLsizei w,GLsizei h)
{
	ww=w;
	wh=h;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,w,h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	if (w <= h)
		glOrtho(-15.0, 15.0, -15.0*(GLfloat)h/(GLfloat)w,
			15.0*(GLfloat)h/(GLfloat)w, -15.0, 15.0);
	else
		glOrtho(-15.0*(GLfloat)w/(GLfloat)h,
			15.0*(GLfloat)w/(GLfloat)h, -15.0, 15.0, -15.0, 15.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,zabubon);
}

void keyboard(unsigned char key,int x,int y)
{
	switch (key)
	{
	case 'S':
		dec_speed();
		break;
	case 's':
		dec_speed();
		break;
	case 'F':
		inc_speed();
		break;
	case 'f':
		inc_speed();
		break;
	case 'N':
		reset();
		break;
	case 'n':
		reset();
		break;
	case 'Q':
		exit(0);
	case 'q':
		exit(0);
	}
}

void mouse(GLint button,GLint state,GLsizei x,GLsizei y)
{
	if (button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
	{
		if (x<(ww/2))
			fall_right();
		if (x>(ww/2))
			fall_left();
	}
}

void main(int argn,char **argv)
{
	glutInit(&argn,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(150,10);
	glutCreateWindow("Zabubon");
	my_init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(display);
	glutMainLoop();
}
