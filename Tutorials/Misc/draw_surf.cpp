#include <iostream.h>
#include <math.h>
#include <GL/Glut.h>

const GLfloat inter2bezier1[4][4]=
{
	{1.0,0.0,0.0,0.0},
	{-5.0/6.0,3,-3.0/2.0,1.0/3.0},
	{1.0/3.0,-3.0/2.0,3.0,-5.0/6.0},
	{0.0,0.0,0.0,1.0}
};

const GLfloat inter2bezier2[4][4]=
{
	{1,-5.0/6.0,1.0/3.0,0.0},
	{0.0,3.0,-3.0/2.0,0.0},
	{0.0,-3.0/2.0,3.0,0.0},
	{0.0,1.0/3.0,-5.0/6.0,1.0}
};

GLfloat initps[16][16][3];
GLfloat ctrps[16][16][3];

GLsizei width=500;
GLsizei height=500;

void add_vector(GLfloat *v1,const GLfloat *v2,GLfloat *result)
{
	for (int i=0; i<3; i++)
		result[i]=v1[i]+v2[i];
}

void mult_vector(const GLfloat scalar,GLfloat *vector,GLfloat *result)
{
	for (int i=0; i<3; i++)
		result[i]=scalar*vector[i];
}

void set_vector(const GLfloat *from,GLfloat *to)
{
	for (int i=0; i<3; i++)
		to[i]=from[i];
}

void init_points(void)
{
	for (int x=0; x<16; x++)
		for (int y=0; y<16; y++)
		{
			initps[y][x][0]=x-8.0;
			initps[y][x][1]=y-8.0;
			initps[y][x][2]=sin(sqrt((x-8.0)*(x-8.0)+(y-8.0)*(y-8.0)));
			//cout<<initps[x][y][0]<<" "<<initps[x][y][1]<<" "<<initps[x][y][2]<<endl;
		}
}
 
void converte2bezier(GLfloat inter_points[4][4][3],GLfloat control_points[4][4][3])
{
	GLfloat temp[3];
	GLfloat result[3];
	GLfloat temp_patch[4][4][3];

	for (int i=0; i<4; i++)
		for (int j=0; j<4; j++)
		{
			for (int k=0; k<3; k++)
				result[k]=0.0;
			for (k=0; k<4; k++)
			{
				mult_vector(inter2bezier1[j][k],inter_points[k][i],temp);
				add_vector(result,temp,result);
			}
			set_vector(result,temp_patch[j][i]);
		}

	for (i=0; i<4; i++)
		for (int j=0; j<4; j++)
		{
			for (int k=0; k<3; k++)
				result[k]=0.0;
			for (k=0; k<4; k++)
			{
				mult_vector(inter2bezier2[k][i],temp_patch[j][k],temp);
				add_vector(result,temp,result);
			}
			set_vector(result,control_points[j][i]);
		}
}


/*void compute_ctrps(void)
{
	GLfloat temp[3];
	GLfloat result[3];

	for (int i=0; i<4; i++)
		for (int j=0; j<4; j++)
		{
			for (int k=0; k<3; k++)
				result[k]=0.0;
			for (k=0; k<4; k++)
			{
				mult_vector(inter2bezier1[j][k],initps[k][i],temp);
				add_vector(result,temp,result);
			}
			set_vector(result,tempps[j][i]);
		}

	for (i=0; i<4; i++)
		for (int j=0; j<4; j++)
		{
			for (int k=0; k<3; k++)
				result[k]=0.0;
			for (k=0; k<4; k++)
			{
				mult_vector(inter2besier2[k][i],tempps[j][k],temp);
				add_vector(result,temp,result);
			}
			set_vector(result,ctrps[j][i]);
		}
	
}*/

void initlights(void)
{
	GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0};
	GLfloat position[] = {0.0, 0.0, 2.0, 1.0};
	GLfloat mat_diffuse[] = {0.6, 0.6, 0.6, 1.0};
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {50.0};
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
	
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void draw_surface()
{
	GLfloat inter_patch[4][4][3];
	GLfloat bezier_patch[4][4][3];

	

	for (int i=0; (i+3)<16; i+=3)
		for (int j=0; (j+3)<16; j+=3)
		{
			for (int k=0; k<4; k++)
				for (int m=0; m<4; m++)
					set_vector(initps[i+k][j+m],inter_patch[k][m]);

			converte2bezier(inter_patch,bezier_patch);
			
			for (k=0; k<4; k++)
				for (int m=0; m<4; m++)
					set_vector(bezier_patch[k][m],ctrps[i+k][j+m]);
			//for (int k=0; k<4; k++)
			//	mult_vectors(&cpts[k+j][i],newcpts[k]);
			
			glColor3f(1.0, 1.0, 1.0);
			glMap2f(GL_MAP2_VERTEX_3,0.0,1.0,3,4,0,1.0,12,4,&bezier_patch[0][0][0]);
			glMapGrid2f(10,0.0,1.0,10,0.0,1.0);
			glEvalMesh2(GL_LINE,0,10,0,10);

/*	glColor3f(1.0, 1.0, 1.0);
	glMap2f(GL_MAP2_VERTEX_3,0.0,1.0,3,4,0,1.0,12,4,&ctrps[0][0][0]);
	glMapGrid2f(10,0.0,1.0,10,0.0,1.0);
	glEvalMesh2(GL_LINE,0,10,0,10);*/
		}
/*	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	for (i=0; i<16; i++)
		for (int j=0; j<16; j++)
			glVertex3fv(ctrps[i][j]);
	glEnd();

	glColor3f(0.0,1.0,0.0);
	glBegin(GL_POINTS);
	for (i=0; i<16; i++)
		for (int j=0; j<16; j++)
			glVertex3fv(initps[i][j]);
	glEnd();*/
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
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

    //glEnable(GL_NORMALIZE);
	
	//initlights();
	glPointSize(3.0);
	init_points();
	//converte2bezier(initps,ctrps);
	//compute_ctrps();
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

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glPushMatrix();
//	glRotatef(0.90,.0,1.0,0.0);
	draw_surface();
	//glPopMatrix();
    glFlush();
}

void idle(void)
{
	glRotatef(0.1,1.0,1.0,1.0);
	glutSwapBuffers();
	glutPostRedisplay();
}

void main(int argn, char **argv)
{
   /* Intialize the program */
    glutInit(&argn, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("curves");
	init();
    /* Register the callbacks */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	glutIdleFunc(idle);

    glutMainLoop();
}