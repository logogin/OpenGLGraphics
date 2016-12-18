#include <math.h>
#include <GL/glut.h>

#define M_PI	3.14159265358979323846

const GLfloat intmatrix[4][4] = 
{
    { 1.0, 0.0, 0.0, 0.0 },
    { -5.0/6.0, 3.0, -3.0/2.0, 1.0/3.0 },
    { 1.0/3.0, -3.0/2.0, 3.0, -5.0/6.0 },
    { 0.0, 0.0, 0.0, 1.0 }, 
};

GLfloat grid4x4[4][4][3] =
{
  {
    {-3.0, -3.0, 0.0},
    {-1.0, -3.0, 0.0},
    {1.0, -3.0, 0.0},
    {3.0, -3.0, 0.0}},
  {
    {-3.0, -1.0, 0.0},
    {-1.0, -1.0, 0.0},
    {1.0, -1.0, 0.0},
    {3.0, -1.0, 0.0}},
  {
    {-3.0, 1.0, 0.0},
    {-1.0, 1.0, 0.0},
    {1.0, 1.0, 0.0},
    {3.0, 1.0, 0.0}},
  {
    {-3.0, 3.0, 0.0},
    {-1.0, 3.0, 0.0},
    {1.0, 3.0, 0.0},
    {3.0, 3.0, 0.0}}
};

GLfloat cpts[4][4][3];
GLubyte GridSize=10;
GLuint SelectBuffer[64];
GLbyte SelectedPoint=-1;
GLint viewport[4];
GLdouble ProjMatrix[16];
GLdouble ModelMatrix[16];

GLsizei ww=500;
GLsizei wh=500;

GLfloat camera[3]={0.0,0.0,1.0};
const GLfloat camera_theta[2]={0.05,0.05};
GLfloat radius;
GLfloat alpha,betta;
GLdouble objx, objy, objz;
static int x_last,y_last;
bool start_motion=false;
bool view_mode=true;
bool edit_mode=false;

void mult_vectors(const GLfloat vectors[4][3],GLfloat result[4][3])
{
	for (int i=0; i<4; i++)
		for (int j=0; j<3; j++)
		{
			result[i][j]=0;
			for (int k=0; k<4; k++)
				result[i][j]+=intmatrix[i][k]*vectors[k][j];
		}
}

void SetOrtho(GLsizei w,GLsizei h)
{
	if (w <= h)
		glOrtho(-5.0, 5.0, -5.0 * (GLfloat) h / w,
			5.0 * (GLfloat) h / w, -10.0, 10.0);
	else
		glOrtho(-5.0 * (GLfloat) w / (GLfloat) h,
			5.0 * (GLfloat) w / (GLfloat) h, -5.0, 5.0, -10.0, 10.0);
}

void InitMesh(void)
{
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(GridSize, 0.0, 1.0, GridSize, 0.0, 1.0);
}

void EvaluateMesh()
{
	glColor3f(1.0, 1.0, 1.0);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4 , 0, 1, 12 , 4, &cpts[0][0][0]);
	glEvalMesh2(GL_LINE, 0, GridSize, 0, GridSize);
}

void ConverteSurface(void)
{
	for (int i=0; i<4; i++)
		mult_vectors(&grid4x4[i][0],cpts[i]);
}

void DrawPoints(void)
{
	glBegin(GL_POINTS);
	for (int i=0; i<4; i++)
		for (int j=0; j<4; j++)
		{
			glColor3f(1.0,0.0,0.0);
			glVertex3fv(cpts[i][j]);
			glColor3f(0.0,1.0,0.0);
			glVertex3fv(grid4x4[i][j]);
		}
	glEnd();
	glColor3f(1.0,1.0,1.0);
}

void LoadPoints(void)
{
	GLubyte name=0;
	for (int i=0; i<4; i++)
		for (int j=0; j<4; j++)
		{
			glLoadName(name);
			glBegin(GL_POINTS);
				glVertex3fv(grid4x4[i][j]);
			glEnd();
			name++;
		}
}

void SetCamera(void)
{
	gluLookAt(camera[0],camera[1],camera[2],0.0,0.0,0.0,0.0,1.0,0.0);
}

GLbyte pick(GLint x, GLint y)
{
	GLubyte hits;
	(void) glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(1);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		
		glLoadIdentity();
		gluPickMatrix(x, wh - y, 8.0, 8.0, viewport);
		SetOrtho(ww,wh);
		SetCamera();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		LoadPoints();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	hits = glRenderMode(GL_RENDER);
	if (hits)
		return SelectBuffer[3];
	else
		return -1;
}

GLfloat get_radius(const GLfloat eye[])
{
	return sqrt(eye[0]*eye[0]+eye[1]*eye[1]+eye[2]*eye[2]);
}

void get_normal(GLfloat *eye)
{
	eye[0]=radius*cos(alpha)*cos(betta);
	eye[1]=radius*sin(alpha);
	eye[2]=-radius*cos(alpha)*sin(betta);
}

void get_polar(const GLfloat eye[])
{
	alpha=asin(eye[1]/radius);
	betta=acos(eye[0]/sqrt(eye[0]*eye[0]+eye[2]*eye[2]));
	//if(eye[2]>0.0)
	//	betta=2*M_PI-betta;
}

void reshape(GLsizei w,GLsizei h)
{
	ww=w;
	wh=h;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	SetOrtho(w,h);
	glGetDoublev(GL_PROJECTION_MATRIX, ProjMatrix);
	SetCamera();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetDoublev(GL_MODELVIEW_MATRIX, ModelMatrix);
	viewport[2] = ww;
	viewport[3] = wh;
}

void motion(int x,int y)
{
	if (view_mode)
		if (start_motion)
		{
			betta+=(x-x_last)*camera_theta[0];
			alpha+=(y-y_last)*camera_theta[1];
			x_last=x;
			y_last=y;
			get_normal(&camera[0]);
			reshape(ww,wh);
			glutPostRedisplay();
		}
	if (edit_mode)
		if (SelectedPoint!=-1)
		{
			gluUnProject(x, wh - y, 0.95,
				ModelMatrix, ProjMatrix, viewport,
				&objx, &objy, &objz);
			grid4x4[SelectedPoint/4][SelectedPoint%4][0] = objx;
			grid4x4[SelectedPoint/4][SelectedPoint%4][1] = objy;
			glutPostRedisplay();
		}

}

void mouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON&&view_mode==true)
	{
		if (state==GLUT_DOWN)
		{
			start_motion=true;
			x_last=x;
			y_last=y;
		}
		else
			start_motion=false;
	}

	if(button==GLUT_LEFT_BUTTON&&edit_mode==true)
	{
		if (state==GLUT_DOWN)
			SelectedPoint=pick(x,y);
		else
			SelectedPoint=-1;
	}
}

void menu(int value)
{
	switch (value)
	{
	case 0:
		exit(0);
	case 1:
		edit_mode=true;
		view_mode=false;
		break;
	case 2:
		edit_mode=false;
		view_mode=true;
		break;
	}
}

void SetMenu(void)
{
	glutCreateMenu(menu);
	glutAddMenuEntry("Edit Mode",1);
	glutAddMenuEntry("View Mode",2);
	glutAddMenuEntry("Exit",0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init(void)
{
	glViewport(0,0,ww,wh);
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glGetDoublev(GL_PROJECTION_MATRIX, ProjMatrix);
	SetOrtho(ww,wh);
	radius=get_radius(camera);
	get_polar(camera);
	SetCamera();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetDoublev(GL_MODELVIEW_MATRIX, ModelMatrix);
	viewport[2] = ww;
	viewport[3] = wh;
	InitMesh();
	glPointSize(5.0);
	SetMenu();
	glSelectBuffer(sizeof(SelectBuffer),SelectBuffer);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	ConverteSurface();
	glPopMatrix();
	//	glRotatef(90.0,1.0,0.0,0.0);
		EvaluateMesh();
	glPushMatrix();
	DrawPoints();
	glutSwapBuffers();
}

void main(int argn,char **argv)
{
	glutInit(&argn,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(ww,wh);
	glutInitWindowPosition(10,10);
	glutCreateWindow("Shaping Surface");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutMainLoop();
}