/*
   OpenGL Water

   File		: water.c
   Date		: 28/12/00
   Author	: Mustata Bogdan (LoneRunner)
   Contact	: lonerunner@planetquake.com

   Change Log
   ----------
   28/12/2000 - added code for FPS counter and scale prog. with the CPU power
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include "tga.h"

#define SQRTOFTWOINV 1.0 / 1.414213562

typedef float vec_t;
typedef vec_t vec3_t[3];

enum {
    LEFT = 0, 
    RIGHT,
};

int mButton = -1;
int mOldY, mOldX;

vec3_t eye = {68.0f, 0.0f, 100.0f};
vec3_t rot = {45.0f, 45.0f, 0.0f};

int		fullscreen=0;
int		texmode=1, envMap=1, go=1;

DWORD	tStart,tCur, tFps;
DWORD	tf=0, nf=0, showFps=0;
int		speed=40;	/* speed is in frame/second */

int		size=25;
int		hw=10;
float	dt=(float) 0.02;
float	tval=(float) 1.0f/25;

float surf[100][100][3];
float norm[100][100][3];
float force[100][100];
float veloc[100][100];

float LightAmbient[]=	{ 1.0f, 1.0f, 1.0f, 1.0f };
float LightDiffuse[]=	{ 1.0f, 1.0f, 1.0f, 1.0f };
float LightPosition[]=	{ 0.0f, 0.0f, -20.0f, 1.0f };

void ResetSurface(void);
void DrawSurface(void);
void MakeNorm(void);
void Wave(void);

void glutResize(int width, int height)
{   
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55.0, (float)width/(float)height, 1.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
}

void glutKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:	exit(0);

		case 32:
			ResetSurface();
			return;

		case 'g':
		case 'G':
			go = !go;
			return;

		case 't':
		case 'T':
			texmode = !texmode;
			if (texmode)
			{
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_DEPTH_TEST);
				glEnable(GL_LIGHTING);
			}
			else
			{
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_DEPTH_TEST);
				glDisable(GL_LIGHTING);
			}
			return;

		case 'e':
		case 'E':
			envMap = !envMap;
            if (envMap)
            {
                glBindTexture(GL_TEXTURE_2D, 1);
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
                glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
                glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
                glEnable(GL_TEXTURE_GEN_S);
                glEnable(GL_TEXTURE_GEN_T);
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, 1);
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                glDisable(GL_TEXTURE_GEN_S);
                glDisable(GL_TEXTURE_GEN_T);
            }
            return;

		case 'a':
		case 'A':
			hw++;
			printf("wave %d\n", hw);
			return;
		case 'z':
		case 'Z':
			hw--;
			printf("wave %d\n", hw);
			return;
		
		case 's':
		case 'S':
			if (speed<1000) speed++;
			printf("speed: %d (fps)\n", speed);
			return;
		
		case 'x':
		case 'X':
			if (speed>1) speed--;
			printf("speed: %d (fps)\n", speed);
			return;

		case 'f':
		case 'F':
			fullscreen = !fullscreen;
			if (fullscreen) glutFullScreen();
			else glutReshapeWindow(400, 300);
			return;

		case '1': loadTGA("textures\\phong.tga", 1);
			if(envMap)
			{
			glBindTexture(GL_TEXTURE_2D, 1);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			}
			return;

		case '2': loadTGA("textures\\64firery-1.tga", 1);
			if(envMap)
			{
			glBindTexture(GL_TEXTURE_2D, 1);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			}
			return;

		case '3': loadTGA("textures\\proto_zzztblu2.tga", 1);
			if(envMap)
			{
			glBindTexture(GL_TEXTURE_2D, 1);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			}
			return;
	}
}

void clamp(vec3_t v)
{
    int i;
    
    for (i = 0; i < 3; i ++)
        if (v[i] > 360 || v[i] < -360)
            v[i] = 0;
}

void glutMotion(int x, int y) 
{
    int m, n;

	if (mButton == LEFT) 
    {
		m = (int)((float)x/glutGet(GLUT_WINDOW_WIDTH) * size);
		n = (int)((float)y/glutGet(GLUT_WINDOW_HEIGHT) * size);

		surf[m][n][1] = hw;
		surf[m][n+1][1] = hw;
		surf[m+1][n][1] = hw;
		surf[m+1][n+1][1] = hw;
    }
	else if (mButton == RIGHT) 
    {
        eye[2] -= ((mOldY - y) * 180.0f) / 200.0f;
        clamp(rot);
    } 

    mOldX = x; 
    mOldY = y;
}

void glutMouse(int button, int state, int x, int y) 
{
    if (state == GLUT_DOWN) 
    {
        mOldX = x;
        mOldY = y;

        switch (button)  
        {
            case GLUT_LEFT_BUTTON: mButton = LEFT; break;
            case GLUT_RIGHT_BUTTON: mButton = RIGHT; break;
        }
	}
	else if (state == GLUT_UP) mButton = -1;
}

void glprint(int x_in, int y_in, float size, char *s, ...)
{
   unsigned char c;
   int i, l, x,y;
   
   float tx,ty, xsize, ysize, fxsize=.0625, fysize=.125;
   
   va_list	msg;
   char buffer[1024] = {'\0'};

   va_start(msg, s);
   vsprintf(buffer, s, msg);	
   va_end(msg);
	
   x = x_in;
   y = glutGet(GLUT_WINDOW_HEIGHT) - y_in;
   l = strlen(s);
   xsize = size * 0.5f;
   ysize = size;
   size *= 0.45f;
   glColor4d(1, 1, 1, 1);
   
   glEnable(GL_BLEND);
   glDisable(GL_LIGHTING);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);
   glBindTexture(GL_TEXTURE_2D, 2);
   if (envMap)
   {
      glBindTexture(GL_TEXTURE_2D, 2);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
      glDisable(GL_TEXTURE_GEN_S);
      glDisable(GL_TEXTURE_GEN_T);
   }
   glPushAttrib(GL_POLYGON_MODE);
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glPushMatrix();
         glPushAttrib(GL_VIEWPORT_BIT);
         glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
         glMatrixMode(GL_PROJECTION);
         glLoadIdentity();
         glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), -1.0f, 1.0f);
         glMatrixMode(GL_MODELVIEW);
         glLoadIdentity();
         
         for (i=0; i<l; i++)
		 {
            c = buffer[i]-32;
            if (c)
			{
               tx = (c % 16) * fxsize + 0.01f;
               ty = (1 - fysize) - (int) (c * 0.0625f) * fysize - 0.01f;
               glBegin(GL_QUADS);
                  glTexCoord2f(tx       , ty);         glVertex2f(x      , y);
                  glTexCoord2f(tx+fxsize, ty);         glVertex2f(x+xsize, y);
                  glTexCoord2f(tx+fxsize, ty+fysize);  glVertex2f(x+xsize, y+ysize);
                  glTexCoord2f(tx       , ty+fysize);  glVertex2f(x      , y+ysize);
                  glEnd();
			}
            x+=size;
		}
         glPopMatrix();
      glPopAttrib();
    
   glDisable(GL_BLEND);
   glEnable(GL_LIGHTING);
   if (envMap)
   {
      glBindTexture(GL_TEXTURE_2D, 2);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
      glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
      glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
      glEnable(GL_TEXTURE_GEN_S);
      glEnable(GL_TEXTURE_GEN_T);
   }
   glPopAttrib();

   glutResize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void glutDisplay(void)
{   
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	
	DrawSurface();		

	// set curent animation
	if (go)
	{ 
		if (tCur-tFps > (DWORD)(1000/speed))
		{
			MakeNorm();
			Wave();
			tFps = tCur;
		}
	}
	
	// draw fps
	if(texmode) glprint(glutGet(GLUT_WINDOW_WIDTH)-64, 25, 18.f, "%3d fps", showFps);
	glPopMatrix();
	
	glFlush();
	glutSwapBuffers();

	// get curent time and modify fps
	tCur = timeGetTime();

    if (tCur-tf>=1000)
	{
		showFps = nf;
		tf = tCur;
		nf = 0;
	}
	else nf++;
}

void copy(float vec0[3], float vec1[3])
{
    vec0[0] = vec1[0];
    vec0[1] = vec1[1];
    vec0[2] = vec1[2];
}

void sub(float vec0[3], float vec1[3], float vec2[3])
{
    vec0[0] = vec1[0] - vec2[0];
    vec0[1] = vec1[1] - vec2[1];
    vec0[2] = vec1[2] - vec2[2];
}

void add(float vec0[3], float vec1[3], float vec2[3])
{
    vec0[0] = vec1[0] + vec2[0];
    vec0[1] = vec1[1] + vec2[1];
    vec0[2] = vec1[2] + vec2[2];
}

void scalDiv(float vec[3], float c)
{
    vec[0] /= c; vec[1] /= c; vec[2] /= c;
}

void cross(float vec0[3], float vec1[3], float vec2[3])
{
    vec0[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
    vec0[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
    vec0[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

void normz(float vec[3])
{
    float c = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
    scalDiv(vec, c); 
}

void set(float vec[3], float x, float y, float z)
{
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
}

void ResetSurface(void)
{
	int i,j;

	for(i=0; i<size; i++)
	for(j=0; j<size; j++)
	{
		surf[i][j][0] = (float)i/(float)size * 100;
		surf[i][j][1] = 0;
		surf[i][j][2] = (float)j/(float)size * 100;

		force[i][j] = 0;
		veloc[i][j] = 0;
	}
}

void DrawSurface(void)
{
	int i, j;

	glTranslatef(-eye[0], -eye[1], -eye[2]);

    glRotatef(rot[0], 1.0f, 0.0f, 0.0f);
    glRotatef(rot[1], 0.0f, 1.0f, 0.0f);
    glRotatef(rot[2], 0.0f, 0.0f, 1.0f);

	if (texmode)
	{
		glColor3f(1, 1, 1);	
		glBindTexture(GL_TEXTURE_2D, 1);

		for(j=0; j<size-1; j++)
		{
			glBegin(GL_TRIANGLE_STRIP);	
			for(i=0; i<size; i++)
			{
				glTexCoord2f((float)i*tval, (float)j*tval);
				glNormal3f((float)norm[i][j][0],	(float)norm[i][j][1],	(float)norm[i][j][2]);
				glVertex3f((float)surf[i][j][0],	(float)surf[i][j][1],	(float)surf[i][j][2]);

				glTexCoord2f((float)i*tval, (float)(j+1)*tval);
				glNormal3f((float)norm[i][j+1][0],	(float)norm[i][j+1][1],	(float)norm[i][j+1][2]);
				glVertex3f((float)surf[i][j+1][0],	(float)surf[i][j+1][1],	(float)surf[i][j+1][2]);
			}
			glEnd();
		}
	}
	else
	{
		glColor3f(1, 1, 1);
		for(i=0; i<size-1; i++)
		for(j=0; j<size-1; j++)
		{
			glBegin(GL_LINE_STRIP);	
			glVertex3f((float)surf[i][j][0],		(float)surf[i][j][1],		(float)surf[i][j][2]);
			glVertex3f((float)surf[i+1][j][0],		(float)surf[i+1][j][1],		(float)surf[i+1][j][2]);
			glVertex3f((float)surf[i+1][j+1][0],	(float)surf[i+1][j+1][1],	(float)surf[i+1][j+1][2]);
			glVertex3f((float)surf[i][j+1][0],		(float)surf[i][j+1][1],		(float)surf[i][j+1][2]);
			glVertex3f((float)surf[i][j][0],		(float)surf[i][j][1],		(float)surf[i][j][2]);
			glEnd();
		}

		glColor3f(0, 1, 0);
		for(i=0; i<size; i++)
		for(j=0; j<size; j++)
		{
			glBegin(GL_LINES);
			glVertex3f((float)surf[i][j][0], (float)surf[i][j][1], (float)surf[i][j][2]);
			glVertex3f((float)surf[i][j][0]+norm[i][j][0], (float)surf[i][j][1]+norm[i][j][1], (float)surf[i][j][2]+norm[i][j][2]);
			glEnd();
		}
	}
}

void MakeNorm(void)
{
	int i, j;
	float a[3],b[3],c[3];

	for(i=0; i<size; i++)
	for(j=0; j<size; j++)
	{
		if (i!=size-1 && j!=size-1)
		{
			sub(a, surf[i][j+1], surf[i][j]);
			sub(b, surf[i+1][j], surf[i][j]);
		}
		else
		{
			sub(a, surf[i][j-1], surf[i][j]);
			sub(b, surf[i-1][j], surf[i][j]);
		}
		
		cross(c, a, b);
		normz(c);

		if (i==0 && j==size-1)
		{
			sub(a, surf[i][j-1], surf[i][j]);
			sub(b, surf[i+1][j], surf[i][j]);

			cross(c, a, b);
			normz(c);

			c[0]=-c[0]; c[1]=-c[1]; c[2]=-c[2];
		}
		
		if (i==size-1 && j==0)
		{
			sub(a, surf[i-1][j], surf[i][j]);
			sub(b, surf[i][j+1], surf[i][j]);

			cross(c, a, b);
			normz(c);
		}		
		
		copy(norm[i][j], c);
   }
}

void Wave(void)
{
	int i,j;
	float d;

	for(i=0; i<size; i++)
	for(j=0; j<size; j++)
		force[i][j] = 0.0f;

	for(i=1; i<size-1; i++)
	for(j=1; j<size-1; j++)
	{
		d=surf[i][j][1]-surf[i][j-1][1];
		force[i][j] -= d;
		force[i][j-1] += d;

		d=surf[i-1][j][1]-surf[i-1][j][1];
		force[i][j] -= d;
		force[i-1][j] += d;

		d=surf[i][j][1]-surf[i][j+1][1];
		force[i][j] -= d;
		force[i][j+1] += d;

		d=surf[i][j][1]-surf[i+1][j][1];
		force[i][j] -= d;
		force[i+1][j] += d;

		d=(surf[i][j][1]-surf[i+1][j+1][1])*SQRTOFTWOINV;
		force[i][j] -= d;
		force[i+1][j+1] += d;

		d=(surf[i][j][1]-surf[i-1][j-1][1])*SQRTOFTWOINV;
		force[i][j] -= d;
		force[i-1][j-1] += d;

		d=(surf[i][j][1]-surf[i+1][j-1][1])*SQRTOFTWOINV;
		force[i][j] -= d;
		force[i+1][j-1] += d;

		d=(surf[i][j][1]-surf[i+1][j-1][1])*SQRTOFTWOINV;
		force[i][j] -= d;
		force[i+1][j-1] += d;
	}

	for(i=0; i<size; i++)
	for(j=0; j<size; j++)
		veloc[i][j] += force[i][j] * dt;
	
	for(i=0; i<size; i++)
	for(j=0; j<size; j++)
	{
		surf[i][j][1] += veloc[i][j];
		
		if (surf[i][j][1]>0) surf[i][j][1] -= surf[i][j][1]/size;
		else surf[i][j][1] -= surf[i][j][1]/size;
	}
}

int main(int argc, char *argv[])
{   
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("water");

	glutReshapeFunc(glutResize);
	glutDisplayFunc(glutDisplay);
	glutIdleFunc(glutDisplay);
    glutKeyboardFunc(glutKeyboard);
	glutMouseFunc(glutMouse);
    glutMotionFunc(glutMotion);

	glClearColor(0.0, 0.0, 0.0, 0);
    
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
	glEnable(GL_LIGHT1);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	loadTGA("textures\\phong.tga", 1);
	loadTGA("textures\\font.tga", 2);
	
	glBindTexture(GL_TEXTURE_2D, 1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	ResetSurface();
	
	tStart = timeGetTime();
	
	glutMainLoop();
	
	return 0;
}