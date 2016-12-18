/*
   OpenGL BPatch (Bezier Patch)

   File		: bpatch.c
   Date		: 29/10/00
   Author	: Mustata Bogdan (LoneRunner)
   Contact	: lonerunner@planetquake.com
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>
#include "tga.h"

typedef float vec_t;
typedef vec_t vec3_t[3];

enum {
    LEFT = 0, 
    RIGHT,
};

int mButton = -1;
int mOldY, mOldX;

vec3_t eye = {6.0f, 0.0f, 40.0f};
vec3_t rot = {45.0f, 45.0f, 0.0f};

int   texmode=0, envMap=1, submenu, mainmenu;
const int pr=10;
const int cp=3;
float val  = (float) 1.f/10;
float tval = (float) 1.f/21;
float p[4+4][4+4][3];
float bases[4][11];
float surf[11+11][11+11][3];
float norm[11+11][11+11][3];

float LightAmbient[]=	{ 1.0f, 1.0f, 1.0f, 1.0f };
float LightDiffuse[]=	{ 1.0f, 1.0f, 1.0f, 1.0f };
float LightPosition[]=	{ 0.0f, 0.0f, -20.0f, 1.0f };

void InitBezierBasis(void);
void DrawBezierBasis(void);

void InitBezierPatch(void);
void DrawBezierPatch(void);

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
		case 32:
			InitBezierPatch();
			return;
		case 'f':
		case 'F':
			glutFullScreen();
			return;
		case '1': loadTGA("phong.tga", 1);
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
		case '2': loadTGA("64firery-1.tga", 1);
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
		case '3': loadTGA("testenv.tga", 1);
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
    if (mButton == LEFT) 
    {
        rot[0] -= ((mOldY - y) * 180.0f) / 200.0f;
        rot[1] -= ((mOldX - x) * 180.0f) / 200.0f;
        clamp(rot);
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

void glutDisplay(void)
{   
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	if (!texmode) DrawBezierBasis();
	DrawBezierPatch();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void glutSubMenu(int value)
{
	switch (value)
	{
		case 1: loadTGA("phong.tga", 1);
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
		case 2: loadTGA("64firery-1.tga", 1);
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
		case 3: loadTGA("testenv.tga", 1);
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

void glutMenu(int value)
{
	switch (value)
	{
		case 1:
			InitBezierPatch(); return;
		case 2:
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
		case 3:
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_LIGHTING);
			texmode = 1;
			return;
		case 4:
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_LIGHTING);
			texmode = 0;
			return;
		case 5:
			glutFullScreen(); return;
		case 6:
			exit(0);
	}
}

void InitBezierBasis(void)
{
	int v;
	float t;

	t=0;
	for(v=0; v<=pr; v++)
	{
		bases[0][v] = pow(1-t,3);
		bases[1][v] = 3*t*pow(1-t,2);
		bases[2][v] = 3*pow(t,2)*(1-t);
		bases[3][v] = pow(t,3);
		t += val;
	}
}

void DrawBezierBasis(void)
{
	float size[ 4 ] = { 0, 4, 0, 4 };
	float offsetX = 0.1f;
	float offsetY = 0.1f;
	
	int v, i;
	float t;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho( size[ 0 ], size[ 1 ], size[ 2 ], size[ 3 ], -1, 1);
	glTranslatef( offsetX, offsetY, 0.0f);

	glColor3f( 0, 1, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f( 0, 0);
	glVertex2f( 1, 0);
	glVertex2f( 1, 1);
	glVertex2f( 0, 1);
	glEnd();
	
	glColor3f(1, 1, 1);
	for(i=0; i<4; i++)
	{
		v=0;
		glBegin(GL_LINE_STRIP);
		for(t=0; t<=1.1f; t += 0.1f)
		{
			glVertex3f(t, (float)bases[i][v], 0);
			v++;
		}
		glEnd();
	}
	
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
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

void InitBezierPatch(void)
{
   int i, j, prn=20;
   int iu=0, iv=0;
   float x=0, y=0, z=0;
   float a[3],b[3],c[3];

   srand( (unsigned)time(NULL) );

   for(i=0; i<4+4; i++)
     for(j=0; j<4+4; j++)
	 {
		p[i][j][0] = ((float)(i - cp * 0.5) / cp) * 14;
		p[i][j][1] = 0;
		p[i][j][2] = ((float)(j - cp * 0.5) / cp) * 14;

		p[i][j][1] = (((float)rand() / (float)RAND_MAX) - 0.5) * 14;
		
		if (j==4)
		{
			if (p[i][2][1]>p[i][3][1]) p[i][j][1] = p[i][3][1]-(p[i][2][1]-p[i][3][1]);
			else p[i][j][1] = p[i][3][1]+(p[i][3][1]-p[i][2][1]);
		}
		
		if (i==4)
		{
			if (p[2][j][1]>p[3][j][1]) p[i][j][1] = p[3][j][1]-(p[2][j][1]-p[3][j][1]);
			else p[i][j][1] = p[3][j][1]+(p[3][j][1]-p[2][j][1]);
		}
	 }
 
   /* - 1 - */
   for(iu=0; iu<11; iu++)
   for(iv=0; iv<11; iv++)
   {
	 x=0; y=0; z=0;

	 for(i=0; i<4; i++)
	 for(j=0; j<4; j++)
	 {
		x += p[i][j][0] * bases[i][iu] * bases[j][iv];
		y += p[i][j][1] * bases[i][iu] * bases[j][iv];
		z += p[i][j][2] * bases[i][iu] * bases[j][iv];
	 }
	
	 surf[iu][iv][0] = x;
	 surf[iu][iv][1] = y;
	 surf[iu][iv][2] = z;
   }

   /* - 2 - */
   for(iu=0; iu<11; iu++)
   for(iv=0; iv<11; iv++)
   {
	 x=0; y=0; z=0;

	 for(i=0; i<4; i++)
	 for(j=0; j<4; j++)
	 {
		x += p[i][j+3][0] * bases[i][iu] * bases[j][iv];
		y += p[i][j+3][1] * bases[i][iu] * bases[j][iv];
		z += p[i][j+3][2] * bases[i][iu] * bases[j][iv];
	 }
	
	 surf[iu][iv+10][0] = x;
	 surf[iu][iv+10][1] = y;
	 surf[iu][iv+10][2] = z;
   }

   /* - 3 - */
   for(iu=0; iu<11; iu++)
   for(iv=0; iv<11; iv++)
   {
	 x=0; y=0; z=0;

	 for(i=0; i<4; i++)
	 for(j=0; j<4; j++)
	 {
		x += p[i+3][j][0] * bases[i][iu] * bases[j][iv];
		y += p[i+3][j][1] * bases[i][iu] * bases[j][iv];
		z += p[i+3][j][2] * bases[i][iu] * bases[j][iv];
	 }
	
	 surf[iu+10][iv][0] = x;
	 surf[iu+10][iv][1] = y;
	 surf[iu+10][iv][2] = z;
   }

   /* - 4 - */
   for(iu=0; iu<11; iu++)
   for(iv=0; iv<11; iv++)
   {
	 x=0; y=0; z=0;

	 for(i=0; i<4; i++)
	 for(j=0; j<4; j++)
	 {
		x += p[i+3][j+3][0] * bases[i][iu] * bases[j][iv];
		y += p[i+3][j+3][1] * bases[i][iu] * bases[j][iv];
		z += p[i+3][j+3][2] * bases[i][iu] * bases[j][iv];
	 }
	
	 surf[iu+10][iv+10][0] = x;
	 surf[iu+10][iv+10][1] = y;
	 surf[iu+10][iv+10][2] = z;
   }
   
   for(i=0; i<=prn; i++)
   for(j=0; j<=prn; j++)
   {
		if (i!=prn && j!=prn)
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

		if (i==0 && j==prn)
		{
			sub(a, surf[i][j-1], surf[i][j]);
			sub(b, surf[i+1][j], surf[i][j]);

			cross(c, a, b);
			normz(c);

			c[0]=-c[0]; c[1]=-c[1]; c[2]=-c[2];
		}
		
		if (i==prn && j==0)
		{
			sub(a, surf[i-1][j], surf[i][j]);
			sub(b, surf[i][j+1], surf[i][j]);

			cross(c, a, b);
			normz(c);
		}		
		
		copy(norm[i][j], c);
   }
}

void DrawBezierPatch(void)
{
	int i, j;

	glTranslatef(-eye[0], -eye[1], -eye[2]);

    glRotatef(rot[0], 1.0f, 0.0f, 0.0f);
    glRotatef(rot[1], 0.0f, 1.0f, 0.0f);
    glRotatef(rot[2], 0.0f, 0.0f, 1.0f);

	if (texmode)
	{
		glColor3f(0, 0.7, 0);	
		glBindTexture(GL_TEXTURE_2D, 1);

		for(j=0; j<20; j++)
		{
			glBegin(GL_TRIANGLE_STRIP);	
			for(i=0; i<=20; i++)
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
		for(i=0; i<20; i++)
		for(j=0; j<20; j++)
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
		for(i=0; i<=20; i++)
		for(j=0; j<=20; j++)
		{
			glBegin(GL_LINES);
			glVertex3f((float)surf[i][j][0], (float)surf[i][j][1], (float)surf[i][j][2]);
			glVertex3f((float)surf[i][j][0]+norm[i][j][0], (float)surf[i][j][1]+norm[i][j][1], (float)surf[i][j][2]+norm[i][j][2]);
			glEnd();
		}
	}
}

int main(int argc, char *argv[])
{   
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("bpatch");

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

	loadTGA("phong.tga", 1);	
	
	glBindTexture(GL_TEXTURE_2D, 1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	InitBezierBasis();
	InitBezierPatch();

	submenu = glutCreateMenu(glutSubMenu);
    glutAddMenuEntry("phong", 1);
    glutAddMenuEntry("64firery-1", 2);
	glutAddMenuEntry("testenv", 3);

	mainmenu = glutCreateMenu(glutMenu);
	glutAddSubMenu("Tex", submenu);
	glutAddMenuEntry("Generate surf", 1);
	glutAddMenuEntry("Envmap", 2);
	glutAddMenuEntry("Textured", 3);
	glutAddMenuEntry("Wireframe", 4);
	glutAddMenuEntry("Full Screen", 5);
	glutAddMenuEntry("Exit", 6);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

    glutMainLoop();
	
	return 0;
}