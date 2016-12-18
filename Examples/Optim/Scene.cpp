// (C) Pasha Malinnikov, mpa@cci.lg.ua

// Вы можете найти ответ и на свой вопрос. Заходите:
// Here you can find answer on your question too! Welcome:

//							http://www.cci.lg.ua/~mpa
//							~~~~~~~~~~~~~~~~~~~~~~~~~
//////////////////////////////////////////////////////////////////////

#include "includes.h"
#include "Scene.h"
#include "Texture.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

long	xCurPosOld;
long	yCurPosOld;
double	aspect;

Texture tex;
extern int		sw;
extern int		sh;
extern POINT click;
extern POINT p;
extern bool Captured;

GLfloat ambientProperties[]		= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat diffuseProperties[]		= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat specularProperties[]	= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat	lightPosition0[]		= { 0.0f, 0.0f, 0.0f, 1.0f };

CScene::CScene()
{
	MyX		= 3.5;
	MyY		= 0.0;
	MyZ		= 0.3;
	MyV		= 70.0;
	MyH		= 0.0;
	Speed	= 0.06;
}

CScene::~CScene()
{

}

void CScene::Init()
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );
	glEnable(GL_DEPTH_TEST);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glViewport(0, 0, sw, sh);
	aspect = (double) (sw / sh);

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluPerspective( 70.0, aspect, 0.01, 50.0 );

	POINT p;
	GetCursorPos(&p);
	xCurPosOld = p.x;
	yCurPosOld = p.y;

	tex.LoadTGA( "Texture.tga", true );
	glBindTexture( GL_TEXTURE_2D, tex.texID );

	//*****************************************************
	//The first step:glEnableClientState
	//*****************************************************
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);


	glEnable(GL_LIGHTING);
	glLightfv( GL_LIGHT0, GL_AMBIENT,  ambientProperties);
	glLightfv( GL_LIGHT0, GL_DIFFUSE,  diffuseProperties);
	glLightfv( GL_LIGHT0, GL_SPECULAR, specularProperties);
	glLightfv(GL_LIGHT0,  GL_POSITION, lightPosition0);
	glEnable( GL_LIGHT0 );

}

void CScene::SetMyView()
{
	glTranslated(0.0, 0.0, -3.0);
	glRotated( -MyV, 1.0, 0.0, 0.0);
	glRotated( MyH, 0.0, 0.0, 1.0);
}

void CScene::Show()
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	HandleControls();

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glPushMatrix();
		SetMyView();

	const int NumElements = 10;
	//*****************************************************
	//Second step:arrays
	//*****************************************************

GLfloat vertices[] = {
			-1.0f, -1.0f, -1.0f, //1
			-1.0f,  1.0f, -1.0f, //2
			-1.0f, -1.0f,  1.0f, //3
			-1.0f,  1.0f,  1.0f, //4
			 1.0f, -1.0f,  1.0f, //5
			 1.0f,  1.0f,  1.0f, //6
			 1.0f, -1.0f, -1.0f, //7
			 1.0f,  1.0f, -1.0f, //8
			-1.0f, -1.0f, -1.0f, //9
			-1.0f,  1.0f, -1.0f, //10
		};

GLfloat texcoord[] =
		{
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			2.0f, 1.0f,
			2.0f, 0.0f,
			3.0f, 1.0f,
			3.0f, 0.0f,
			4.0f, 1.0f,
			4.0f, 0.0f,
		};

GLfloat normals[] = {
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

	GLuint indices[NumElements];

	for(int i=0;i<NumElements;i++)
		indices[i] = (GLuint)i;

	//*****************************************************
	//Third step: Pointers
	//*****************************************************

	glVertexPointer( 3, GL_FLOAT,  0, vertices );
	glTexCoordPointer( 2, GL_FLOAT,  0, texcoord );
	glNormalPointer( GL_FLOAT,  0,  normals );

	//*****************************************************
	//And viola: glDrawElements
	//*****************************************************

	glDrawElements(GL_TRIANGLE_STRIP, NumElements, GL_UNSIGNED_INT, indices);

		glPushMatrix();
			glTranslated(0.0, 0.0, 0.0);

			glDisable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
				gluSphere(gluNewQuadric(),0.2,10,10);
			glEnable(GL_LIGHTING);
			glEnable(GL_TEXTURE_2D);
		glPopMatrix();

	glPopMatrix();
}

void CScene::HandleControls()
{
	if( Captured )
	{
		GetCursorPos(&p);

		MyV += ((click.y-p.y)*0.15);
		MyH -= ((click.x-p.x)*0.15);

		SetCursorPos(click.x,click.y);
	}
}

void CScene::ShutDown()
{
	FreeTexture( tex.texID );
}

void CScene::ResizeViewport(int w, int h)
{
	aspect = (double) (sw / sh);

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glViewport(0, 0, sw, sh);

	gluPerspective( 70.0, aspect, 0.01, 50.0 );

}
