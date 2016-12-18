#include <GL/glut.h>
#include <GL/glaux.h>
#include <iostream.h>
#include <windows.h>
#include <math.h>
#include "Fido.h"

bool fullscreen=false; // fullscreen
bool perspective=false;
bool fmotion=true;
bool spectrR=false,spectrG=false,spectrB=false; // spectr of light

void draw_scene()
{
	glPushMatrix();
		lights();
	glPopMatrix();
	
	set_mat(fido_amb,fido_diff,fido_spec,fido_shine);
	draw_fido();
	draw_generator();

	glPushMatrix();
		glTranslatef(0.0,-0.20,0.0);
		glScalef(3.0,0.0,3.0);
		set_mat(floor_amb,floor_diff,floor_spec,floor_shine);
		drawFloor();
		
	glPopMatrix();
}

void init()
{
	set_textures();
	init_fido_node();
	init_generator_node();
	radius=get_radius(camera);
	get_polar(camera);
	
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_FOG);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	draw_scene();
	glutSwapBuffers();
}

void reshape(GLsizei w,GLsizei h)
{
	ww=w;
	wh=h;
	if (perspective==false)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0,0,w,h);
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();
		if (w <= h)
			glOrtho(left, right, bottom*(GLfloat)h/(GLfloat)w,
				top*(GLfloat)h/(GLfloat)w, back, front);
		else
			glOrtho(left*(GLfloat)w/(GLfloat)h,
				right*(GLfloat)w/(GLfloat)h, bottom, top, back, front);
			gluLookAt(camera[0],camera[1],camera[2],
						look_at[0],look_at[1],look_at[2],0.0,1.0,0.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	if (perspective==true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0,0,w,h);
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0,(GLfloat)ww/(GLfloat)wh,0.1,-back);
		glTranslatef(0,-9,-25);
		glScalef(.5,.5,.5);
		gluLookAt(camera[0],camera[1],camera[2],
					look_at[0],look_at[1],look_at[2],0.0,1.0,0.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}


// keyboard function
void keyboard(unsigned char key,int x,int y)
{
	if (key>='A' && key<='Z') key=key+32;
	switch (key) {
// Quit	
	case VK_ESCAPE:
			if (MessageBox(NULL,"Are you sure you want to exit?", 
				"Fido-Fast Attacking Cobot v2.204alpha",MB_YESNO|MB_ICONQUESTION)==IDYES)
			exit(1);
			break;
// Switch to fullscreen	
	case 'a':
			if (fullscreen==false)
			{
				glutFullScreen();
				fullscreen=true;
				break;
			}
			if (fullscreen==true)
			{
				glutPositionWindow(110,23);
				glutReshapeWindow(800,500);
				fullscreen=false;
			}
			break;
// move light left	
	case 's':
			light1_dir[0]-=1;
			light1_pos[0]-=1;
			a-=1;
			break;
// move light right	
	case 'd':
			light1_dir[0]+=1;
			light1_pos[0]+=1;
			a+=1;
			break;
// move light up	
	case 'e':
			light1_dir[1]+=1;
			light1_pos[1]+=1;
			b+=1;
			break;
// move light down	
	case 'c':
			light1_dir[1]-=1;
			light1_pos[1]-=1;
			b-=1;
			break;
// move light forward	
	case 'f':
			light1_dir[2]+=1;
			light1_pos[2]+=1;
			c+=1;
			break;
// move light backward	
	case 'b':
			light1_dir[2]-=1;
			light1_pos[2]-=1;
			c-=1;
			break;
// normalize light position	
	case 'l':
			light1_dir[0]=45.0;
			light1_dir[1]=45.0;
			light1_dir[2]=0.0;
			light1_pos[0]=-45.0;
			light1_pos[1]=-45.0;
			light1_pos[2]=0.0;
			a=45.0;
			b=45.0;
			c=0.0;
			break;
// changing light spectr to red	
	case 'i':
			if (spectrR==false)
			{
				light1_ambient[0]=1.0;
				light1_diffuse[0]=1.0;
				light1_spec[0]	 =1.0;
				spectrR=true;
				break;
			}
			else 
			{
				light1_ambient[0]=0.0;
				light1_diffuse[0]=0.0;
				light1_spec[0]	 =0.0;
				spectrR=false;
			}
			break;
// changing light spectr to green	
	case 'j':
			if (spectrG==false)
			{
				light1_ambient[1]=1.0;
				light1_diffuse[1]=1.0;
				light1_spec[1]	 =1.0;
				spectrG=true;
				break;
			}
			else 
			{
				light1_ambient[1]=0.0;
				light1_diffuse[1]=0.0;
				light1_spec[1]	 =0.0;
				spectrG=false;
			}
			break;
// changing light spectr to blue
	case 'k':
			if (spectrB==false)
			{
				light1_ambient[2]=1.0;
				light1_diffuse[2]=1.0;
				light1_spec[2]	 =1.0;
				spectrB=true;
				break;
			}
			else 
			{
				light1_ambient[2]=0.0;
				light1_diffuse[2]=0.0;
				light1_spec[2]	 =0.0;
				spectrB=false;
			}
			break;
// switch to perspective view	
	case 'p':
			if (perspective==false)
			{
				perspective=true;
				glViewport(0,0,ww,wh);
				glMatrixMode (GL_PROJECTION);
				glLoadIdentity ();
				gluPerspective(60.0,(GLfloat)ww/(GLfloat)wh,0.1,-back);
				glTranslatef(0.0,-9.0,-25.0);
				glScalef(0.5,0.5,0.5);
				gluLookAt(camera[0],camera[1],camera[2],
							look_at[0],look_at[1],look_at[2],0.0,1.0,0.0);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				break;
			}
			else
			{
				perspective=false;
				glViewport(0,0,ww,wh);
				glMatrixMode (GL_PROJECTION);
				glLoadIdentity ();
				if (ww <= wh)
					glOrtho(left, right, bottom*(GLfloat)wh/(GLfloat)ww,
						top*(GLfloat)wh/(GLfloat)ww, back, front);
				else
					glOrtho(left*(GLfloat)ww/(GLfloat)wh,
					right*(GLfloat)ww/(GLfloat)wh, bottom, top, back, front);
					gluLookAt(camera[0],camera[1],camera[2],
								look_at[0],look_at[1],look_at[2],0.0,1.0,0.0);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				break;
			}
	case 'z':
			glutPositionWindow(110,23);
			glutReshapeWindow(800,500);
			break;
	case ',':
			ww-=10;
			wh-=10;
			glutReshapeWindow(ww,wh);
			break;
	case '.':
			ww+=10;
			wh+=10;
			glutReshapeWindow(ww,wh);
			break;
	case 'm':
			if (fmotion==true)
			{
				fmotion=false;
				glutIdleFunc(NULL);
				break;
			}
			else 
			{
				fmotion=true;
				glutIdleFunc(display);
				break;
			}
	}
	glutPostRedisplay(); 
}

void main(int argn,char **argv)
{
	glutInit(&argn,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww,wh);
	glutInitWindowPosition(110,10);
	glutCreateWindow("Fido-Fast Attacking Cobot v2.204alpha");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMotionFunc(motion);
	glutMouseFunc(mouse);
	glutIdleFunc(display);
	Create_Menu();
	glutMainLoop();
}