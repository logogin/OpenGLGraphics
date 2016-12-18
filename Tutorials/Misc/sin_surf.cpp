#include <math.h>
#include <GL/glut.h>

GLsizei width=500;
GLsizei height=500;
GLfloat cpts[16][16][3];

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



void draw_surface()
{
	GLfloat newcpts[4][4][3];
	for (int i=0; (i+3)<16; i+=3)
		for (int j=0; (j+3)<16; j+=3)
		{
			
			for (int k=0; k<4; k++)
				mult_vectors(&cpts[k+j][i],newcpts[k]);

			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_POINTS);
			for (int i=0; i<4; i++)
				for (int j=0; j<4; j++)
					glVertex3fv(newcpts[i][j]);
			glEnd();
			glColor3f(1.0, 1.0, 1.0);
			glMap2f(GL_MAP2_VERTEX_3,0.0,1.0,3,4,0,1.0,12,4,&newcpts[0][0][0]);
			glMapGrid2f(10,0.0,1.0,10,0.0,1.0);
			glEvalMesh2(GL_LINE,0,10,0,10);
			
			
			
			
			/*glMap2f(GL_MAP2_VERTEX_3,0.0,1.0,3,4,0,1.0,12,4,&cpts[0][0][0]);
			glMapGrid2f(10,0.0,1.0,10,0.0,1.0);
			glEvalMesh2(GL_LINE,0,10,0,10);*/
		}
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(50,1.0,1.0,1.0);
	draw_surface();
	glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
			glVertex3fv(cpts[i][j]);
    glEnd();
	glPopMatrix();
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
	for (int y=0; y<16; y++)
		for (int x=0; x<16; x++)
		{
			cpts[y][x][0]=-12+(5+x);
			cpts[y][x][1]=-12+(5+y);
			cpts[y][x][2]=sin(5+x)+cos(5+y);
		}

	glEnable(GL_MAP2_VERTEX_3);
	glPointSize(3.0);
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