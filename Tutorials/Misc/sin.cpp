#include <math.h>
#include <GL/glut.h>

GLsizei width=500;
GLsizei height=500;
GLfloat cpts[16][3];

const GLfloat minterp[4][4] = 
{
    { 1.0, 0.0, 0.0, 0.0 },
    { -5.0/6.0, 3.0, -3.0/2.0, 1.0/3.0 },
    { 1.0/3.0, -3.0/2.0, 3.0, -5.0/6.0 },
    { 0.0, 0.0, 0.0, 1.0 }, 
};

void mult_vectors(const GLfloat vectors[4][3],GLfloat result[4][3])
{
	for (int i=0; i<4; i++)
		for (int j=0; j<3; j++)
		{
			result[i][j]=0;
			for (int k=0; k<4; k++)
				result[i][j]+=minterp[i][k]*vectors[k][j];
		}
}

void draw_curves()
{
	GLfloat newcpts[4][3];
	glColor3f(0.0,1.0,0.0);
	glPointSize(3.0);
	for (int i=0; i+3<16; i+=3)
	{
		mult_vectors(&cpts[i],newcpts);
		glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,4,&newcpts[0][0]);
		glMapGrid1f(30,0.0,1.0);
		glEvalMesh1(GL_LINE,0,30);
		glBegin(GL_POINTS);
		for (int j=0; j<4; j++)
			glVertex3fv(newcpts[j]);
		glEnd();
	}
	
	glColor3f(1.0,0.0,0.0);
	for (i=0; i+3<16; i+=3)
	{
		glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,4,&cpts[i][0]);
		glMapGrid1f(30,0.0,1.0);
		glEvalMesh1(GL_LINE,0,30);
	}
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
	draw_curves();
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(3.0);
	
    glBegin(GL_POINTS);
    for (int i = 0; i < 16; i++)
        glVertex3fv(cpts[i]);
    glEnd();

    glFlush();
}

void reshape(int w, int h)
{
    width = w;
    height = h;

    /* Set the transformations */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}

void init()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glViewport(0, 0, 500, 500);
	for (int i=0; i<16; i++)
	{
		cpts[i][0]=-12+(5+i);
		cpts[i][1]=sin(5+i);
		cpts[i][2]=0;
	}
	glEnable(GL_MAP1_VERTEX_3);
}

void main(int argc, char **argv)
{
    /* Intialize the program */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("curves");
	init();
    /* Register the callbacks */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
}