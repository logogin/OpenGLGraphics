// (C) Pasha Malinnikov, mpa@cci.lg.ua

// Вы можете найти ответ и на свой вопрос. Заходите:
// Here you can find answer on your question too! Welcome:

//							http://www.3d.lg.ua
//							~~~~~~~~~~~~~~~~~~~
//////////////////////////////////////////////////////////////////////

#include "includes.h"
#include "Scene.h"
#include "Text.h"
#include "Plane.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Text	text;


cPoint p1(0.3, 0.5, 0);
cPoint p2(0, 0.7, -1);
cPoint p3(0, 1, 0.5);

double	A = 4;
double	B = 2;
double	C = 3;
double	D = 0.7;


Plane	plane(A, B, C, D);
//Plane	plane(p1,p2,p3);

long	xCurPosOld;
long	yCurPosOld;
double	aspect;

extern POINT click;
extern POINT p;
extern bool Captured;

bool ShowCylinder = false;


void MatrixTranspose(double matrix2[16], double matrix1[16])
{
    matrix2[ 0] = matrix1[ 0];
    matrix2[ 1] = matrix1[ 4];
    matrix2[ 2] = matrix1[ 8];
    matrix2[ 3] = matrix1[12];

    matrix2[ 4] = matrix1[ 1];
    matrix2[ 5] = matrix1[ 5];
    matrix2[ 6] = matrix1[ 9];
    matrix2[ 7] = matrix1[13];

    matrix2[ 8] = matrix1[ 2];
    matrix2[ 9] = matrix1[ 6];
    matrix2[10] = matrix1[10];
    matrix2[11] = matrix1[14];

    matrix2[12] = matrix1[ 3];
    matrix2[13] = matrix1[ 7];
    matrix2[14] = matrix1[11];
    matrix2[15] = matrix1[15];
}

CScene::CScene()
{
	MyX		= 3.5;
	MyY		= 0.0;
	MyZ		= 0.3;
	MyV		= 70.0;
	MyH		= 280.0;
	Speed	= 0.06;
}

CScene::~CScene()
{

}

void CScene::Init(int w, int h)
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );
	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);

	glViewport(0, 0, w, h);
	aspect = (double) (w / h);

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluPerspective( 60.0, aspect, 0.01, 10.0 );

	POINT p;
	GetCursorPos(&p);
	xCurPosOld = p.x;
	yCurPosOld = p.y;

	text.Init(0);

}

void CScene::SetMyView()
{
	glTranslated(0.0, 0.0, -2.2);
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

		//Axes
		glBegin(GL_LINES);
			glVertex3f(-1.0f,  0.0f,  0.0f);
			glVertex3f( 1.0f,  0.0f,  0.0f); 
			glVertex3f( 0.0f, -1.0f,  0.0f);
			glVertex3f( 0.0f,  1.0f,  0.0f);
			glVertex3f( 0.0f,  0.0f, -1.0f);
			glVertex3f( 0.0f,  0.0f,  1.0f);
		glEnd();

		text.Draw3D(1.05f,  0.0f,  0.0f, "X");
		text.Draw3D(0.0f,  1.05f,  0.0f, "Y");
		text.Draw3D(0.0f,  0.0f,  1.05f, "Z");

		plane.Draw(10, 10, 0.1);

		//***********************************
		glPushMatrix();

			glPushAttrib(GL_CURRENT_BIT);

				cPoint  ObjectPos(0.0, 0.0, 0.0);

				// Origin object position
				double m[17];
				double matrix[17] =
				{
					 1.0,  0.0,  0.0,  -ObjectPos.x,
					 0.0,  1.0,  0.0,  -ObjectPos.y,
					 0.0,  0.0,  1.0,  -ObjectPos.z,
					 0.0,  0.0,  0.0,  1.0
				};

				MatrixTranspose(m, matrix);//prepare for OpenGL
				glMultMatrixd(m);

				glColor3d(1.0, 1.0, 0.0);
				GLUquadricObj * origin = gluNewQuadric();
				gluQuadricDrawStyle(origin, GLU_LINE);

				if(ShowCylinder)
					gluCylinder( origin, 0.3, 0.3, 0.5, 10, 1 );
				else
					gluPartialDisk(origin, 0.1, 0.5, 5, 7, 30, 50);



				//Attention! Here are several steps of aphine transformation

				// Step 1. Invert (Scale) relative Y0Z******************************
				double distace = plane.DistanceToPlane(ObjectPos);
				CVector axeX(1,0,0);
				CVector axeY(0,1,0);
				CVector axeZ(0,0,1);

				double matrix1[17] =
				{
					-1.0,  0.0,  0.0,  0.0,
					 0.0,  1.0,  0.0,  0.0,
					 0.0,  0.0,  1.0,  0.0,
					 0.0,  0.0,  0.0,  1.0
				};

				MatrixTranspose(m, matrix1);//prepare for OpenGL
				glMultMatrixd(m);

				//I define angles to rotate coord. system
				CVector horisproj(plane.N.x, plane.N.y, 0.0);
				CVector crosshorisproj = plane.N ^ axeZ;
				CVector crossverticproj = crosshorisproj.GetNormalized() ^ plane.N;
				crosshorisproj.x*=-1;
				crossverticproj.x*=-1;
				double angleToY = (PI/2-acos(axeX | crosshorisproj.GetNormalized()));
				double angleToZ = -(acos(plane.N | axeZ)-PI/2)*2;


				// Step 2. Rotate to Y around Z**************************************
				double matrix2[17] =
				{
					 cos(angleToY), -sin(angleToY),  0.0,  0.0,
					 sin(angleToY),  cos(angleToY),  0.0,  0.0,
					 0.0,					   0.0,  1.0,  0.0,
					 0.0,					   0.0,  0.0,  1.0
				};

				MatrixTranspose(m, matrix2);//prepare for OpenGL
				glMultMatrixd(m);


				// Step 3. Rotate around Y*******************************************
				double matrix3[17] =
				{
					 cos(angleToZ), 0.0,  sin(angleToZ),	0.0,	
					 0.0,			1.0, 			0.0,	0.0,
					-sin(angleToZ), 0.0,  cos(angleToZ),	0.0,
					 0.0,			0.0,			0.0,	1.0
				};

				MatrixTranspose(m, matrix3);//prepare for OpenGL
				glMultMatrixd(m);

				// Step 4. Rotate to Y around Z again*********************************
				double matrix4[17] =
				{
					 cos(angleToY), -sin(angleToY),  0.0,  0.0,
					 sin(angleToY),  cos(angleToY),  0.0,  0.0,
					 0.0,					   0.0,  1.0,  0.0,
					 0.0,					   0.0,  0.0,  1.0
				};

				MatrixTranspose(m, matrix4);//prepare for OpenGL
				glMultMatrixd(m);

				// Step 5. Translate to mirror *********************************
				double matrix5[17] =
				{
					 1.0,  0.0,  0.0,  -plane.N.x * distace * 2,
					 0.0,  1.0,  0.0,  -plane.N.y * distace * 2,
					 0.0,  0.0,  1.0,  -plane.N.z * distace * 2,
					 0.0,  0.0,  0.0,  1.0
				};

				MatrixTranspose(m, matrix5);//prepare for OpenGL
				glMultMatrixd(m);
/**/
				//Now we can draw result of reflection


				glColor3d(1.0, 0.0, 0.0);

				glBegin(GL_LINES);
					glVertex3f(-1.0f,  0.0f,  0.0f);
					glVertex3f( 1.0f,  0.0f,  0.0f); 
					glVertex3f( 0.0f, -1.0f,  0.0f);
					glVertex3f( 0.0f,  1.0f,  0.0f);
					glVertex3f( 0.0f,  0.0f, -1.0f);
					glVertex3f( 0.0f,  0.0f,  1.0f);
				glEnd();

				text.Draw3D(1.05f,  0.0f,  0.0f, "X");
				text.Draw3D(0.0f,  1.05f,  0.0f, "Y");
				text.Draw3D(0.0f,  0.0f,  1.05f, "Z");

				GLUquadricObj * result = gluNewQuadric();
				gluQuadricDrawStyle(result, GLU_LINE);

				if(ShowCylinder)
					gluCylinder( origin, 0.3, 0.3, 0.5, 10, 1 );
				else
					gluPartialDisk(origin, 0.1, 0.5, 5, 7, 30, 50);

			glPopAttrib();

		glPopMatrix();
		//***********************************

		char *str = "";
		sprintf(str, "Plane equation: %.3fx + %.3fy + %.3fz + %.1f  = 0",
			A, B, C, D );

		text.Draw2D(0.1f, 0.1f, str);


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

	if(GetAsyncKeyState(65))//A
		A+=0.1;
	if(GetAsyncKeyState(65) && GetAsyncKeyState(VK_SHIFT))
		A-=0.2;

	if(GetAsyncKeyState(66))//B
		B+=0.1;
	if(GetAsyncKeyState(66) && GetAsyncKeyState(VK_SHIFT))
		B-=0.2;

	if(GetAsyncKeyState(67))//C
		C+=0.1;
	if(GetAsyncKeyState(67) && GetAsyncKeyState(VK_SHIFT))
		C-=0.2;

	if(GetAsyncKeyState(68))//D
		D+=0.01;
	if(GetAsyncKeyState(68) && GetAsyncKeyState(VK_SHIFT))
		D-=0.02;

	if(A<0) A=0;
	if(B<0) B=0;
	if(C<0) C=0;

	plane.N = CVector(A, B, C).GetNormalized();
	plane.D = D;

}

void CScene::ShutDown()
{

}

void CScene::ResizeViewport(int w, int h)
{
	aspect = (double) (w / h);

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective( 70.0, aspect, 0.01, 50.0 );

}
