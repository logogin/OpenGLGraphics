
/* Interactive Figure Program from Chapter 8 using cylinders (quadrics) */
/* Style similar to robot program but here we must traverse tree to display */
/* Cylinders are displayed as filled and light/material properties */
/* are set as in sphere approximation program */

#include <GL/glut.h>
#include <stdlib.h>
#include <assert.h>

#define TORSO_HEIGHT 5.0
#define UPPER_ARM_HEIGHT 3.0
#define LOWER_ARM_HEIGHT 2.0
#define UPPER_LEG_RADIUS  0.5
#define LOWER_LEG_RADIUS  0.5
#define LOWER_LEG_HEIGHT 2.0
#define UPPER_LEG_HEIGHT 3.0
#define UPPER_LEG_RADIUS  0.5
#define TORSO_RADIUS 1.0
#define UPPER_ARM_RADIUS  0.5
#define LOWER_ARM_RADIUS  0.5
#define HEAD_HEIGHT 1.5
#define HEAD_RADIUS 1.0

void draw_head();
void draw_torso();
void darw_luparm();
void darw_lloarm();
void draw_ruparm();
void draw_rloarm();
void draw_lupleg();
void draw_lloleg();
void draw_rupleg();
void draw_rloleg();

//typedef float point[3];


typedef struct treenode
{
  GLfloat matrix[16];
  GLubyte children_num;
  void (*fptr)(void);
  struct treenode **children;
} treenode; 

static GLfloat theta[11] = {90.0,0.0,0.0,70.0,-70.0,0.0,0.0,
            180.0,0.0,180.0,0.0}; /* initial joint angles */
static GLint angle = 2;

GLfloat torso_matrix[16];

GLUquadricObj *torso, *head,
 *luparm, *lloarm,
 *ruparm, *rloarm,
 *lloleg, *rloleg,
 *rupleg, *lupleg;

double size=1.0;

treenode torso_node, head_node, luparm_node, ruparm_node, lloleg_node, rloleg_node,
				lloarm_node, rloarm_node, rupleg_node, lupleg_node;

void init_node(treenode &root,const GLubyte child_num)
{
	root.children_num=child_num;
	if (child_num)
	{
		root.children=new treenode *[root.children_num];
		assert(root.children!=NULL);
	}
}

void traverse(treenode *root)
{
	if (root->children_num)
		for (int i=0; i<root->children_num; i++)
		{
			glPushMatrix();
				glMultMatrixf(root->matrix);
				root->fptr();
				traverse(root->children[i]);
			glPopMatrix();
		}
	else
	{
		glPushMatrix();
			glMultMatrixf(root->matrix);
			root->fptr();
		glPopMatrix();
	}


  /* if(root==NULL) return;
   glPushMatrix();
   glMultMatrixf(root->m);
   root->f();
   if(root->child!=NULL) traverse(root->child);
   glPopMatrix();
   if(root->sibling!=NULL) traverse(root->sibling);*/
}

void draw_torso()
{
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		gluCylinder(torso,TORSO_RADIUS, TORSO_RADIUS, TORSO_HEIGHT,10,10);
	glPopMatrix();
}

void draw_head()
{
	glPushMatrix();
		glTranslatef(0.0, 0.5*HEAD_HEIGHT,0.0);
		glScalef(HEAD_RADIUS, HEAD_HEIGHT, HEAD_RADIUS);
		gluSphere(head,1.0,10,10);
	glPopMatrix();
}

void draw_luparm()
{
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		gluCylinder(luparm,UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);
	glPopMatrix();
}

void draw_lloarm()
{
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		gluCylinder(lloarm,LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT,10,10);
	glPopMatrix();
}

void draw_ruparm()
{
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		gluCylinder(ruparm,UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);
	glPopMatrix();
}

void draw_rloarm()
{
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		gluCylinder(rloarm,LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT,10,10);
	glPopMatrix();
}

void draw_lupleg()
{
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		gluCylinder(lupleg,UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT,10,10);
	glPopMatrix();
}

void draw_lloleg()
{
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		gluCylinder(lloleg,LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT,10,10);
	glPopMatrix();
}

void draw_rupleg()
{
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		gluCylinder(rupleg,UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT,10,10);
	glPopMatrix();
}

void draw_rloleg()
{
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		gluCylinder(rloleg,LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT,10,10);
	glPopMatrix();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0, 0.0, 0.0);
    traverse(&torso_node);
	glutSwapBuffers();
}



void mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
        {
        theta[angle] += 5.0;
        if( theta[angle] > 360.0 ) theta[angle] -= 360.0;
        }
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) 
        {
        theta[angle] -= 5.0;
        if( theta[angle] < 360.0 ) theta[angle] += 360.0;
        }
	glPushMatrix();
	switch(angle)
	{

	case 0 :
		glLoadIdentity();
		//glMultMatrixf(torso_matrix);
        glRotatef(theta[0], 0.0, 1.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,torso_node.matrix);
		break;

	case 1 : case 2 :
		glLoadIdentity();
        glTranslatef(0.0, TORSO_HEIGHT+0.5*HEAD_HEIGHT, 0.0);
        glRotatef(theta[1], 1.0, 0.0, 0.0);
        glRotatef(theta[2], 0.0, 1.0, 0.0);
        glTranslatef(0.0, -0.5*HEAD_HEIGHT, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,head_node.matrix);
		break;

	case 3 :
		glLoadIdentity();
        glTranslatef(-(TORSO_RADIUS+UPPER_ARM_RADIUS), 0.9*TORSO_HEIGHT, 0.0);
        glRotatef(theta[3], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,luparm_node.matrix);
		break;

	case 5 :
		glLoadIdentity();
        glTranslatef(TORSO_RADIUS+UPPER_ARM_RADIUS, 0.9*TORSO_HEIGHT, 0.0);
        glRotatef(theta[5], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,ruparm_node.matrix);
		break;

	case 9 :
		glLoadIdentity();
        glTranslatef(TORSO_RADIUS+UPPER_LEG_RADIUS, 0.1*UPPER_LEG_HEIGHT, 0.0);
        glRotatef(theta[9], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,rupleg_node.matrix);
		break;

	case 7 :
		glLoadIdentity();
        glTranslatef(-(TORSO_RADIUS+UPPER_LEG_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);
        glRotatef(theta[7], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,lupleg_node.matrix);
		break;

	case 4 :
		glLoadIdentity();
        glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
        glRotatef(theta[4], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,lloarm_node.matrix);
		break;

	case 8 :
		glLoadIdentity();
        glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
        glRotatef(theta[8], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,lloleg_node.matrix);
		break;

	case 10 :
		glLoadIdentity();
        glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
        glRotatef(theta[10], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,rloleg_node.matrix);
		break;

	case 6 :
		glLoadIdentity();
        glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
        glRotatef(theta[6], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,rloarm_node.matrix);
		break;
	}
	glPopMatrix();
    glutPostRedisplay();
}

void menu(int id)
{
   if(id <11 ) angle=id;
   if(id ==11 ) exit(0);
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-10.0, 10.0, -10.0 * (GLfloat) h / (GLfloat) w,
            10.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-10.0 * (GLfloat) w / (GLfloat) h,
            10.0 * (GLfloat) w / (GLfloat) h, 0.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init_scene()
{
	GLfloat mat_specular[]={1.0, 1.0, 1.0, 1.0};
	GLfloat mat_diffuse[]={1.0, 1.0, 1.0, 1.0};
	GLfloat mat_ambient[]={1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess={100.0};
	GLfloat light_ambient[]={0.0, 0.0, 0.0, 1.0};
	GLfloat light_diffuse[]={1.0, 0.0, 0.0, 1.0};
	GLfloat light_specular[]={1.0, 1.0, 1.0, 1.0};
	GLfloat light_position[]={10.0, 10.0, 10.0, 0.0};

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING); 
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST); 

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);

/* allocate quadrics with filled drawing style */

	head=gluNewQuadric();
	gluQuadricDrawStyle(head, GLU_FILL);
	torso=gluNewQuadric();
	gluQuadricDrawStyle(torso, GLU_FILL);
	luparm=gluNewQuadric();
	gluQuadricDrawStyle(luparm, GLU_FILL);
	lloarm=gluNewQuadric();
	gluQuadricDrawStyle(lloarm, GLU_FILL);
	ruparm=gluNewQuadric();
	gluQuadricDrawStyle(ruparm, GLU_FILL);
	rloarm=gluNewQuadric();
	gluQuadricDrawStyle(rloarm, GLU_FILL);
	lupleg=gluNewQuadric();
	gluQuadricDrawStyle(lupleg, GLU_FILL);
	lloleg=gluNewQuadric();
	gluQuadricDrawStyle(lloleg, GLU_FILL);
	rupleg=gluNewQuadric();
	gluQuadricDrawStyle(rupleg, GLU_FILL);
	rloleg=gluNewQuadric();
	gluQuadricDrawStyle(rloleg, GLU_FILL);
}

void myinit()
{
	init_scene();
/* Set up tree */
	
	glLoadIdentity();
	glScalef(1.5,1.5,1.5);
	//glTranslatef(5.0,-3.0,0.0);
	//glRotatef(theta[0], 0.0, 1.0, 0.0);
	//glGetFloatv(GL_MODELVIEW_MATRIX,torso_matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX,torso_node.matrix);
	torso_node.fptr = draw_torso;
	init_node(torso_node,5);
	torso_node.children[0] =  &head_node;
	torso_node.children[1] =  &luparm_node;
	torso_node.children[2] =  &ruparm_node;
	torso_node.children[3] =  &lupleg_node;
	torso_node.children[4] =  &rupleg_node;

	glLoadIdentity();
	glTranslatef(0.0, TORSO_HEIGHT+0.5*HEAD_HEIGHT, 0.0);
	glRotatef(theta[1], 1.0, 0.0, 0.0);
	glRotatef(theta[2], 0.0, 1.0, 0.0);
	glTranslatef(0.0, -0.5*HEAD_HEIGHT, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX,head_node.matrix);
	head_node.fptr = draw_head;
	init_node(head_node,0);
	head_node.children = NULL;

	glLoadIdentity();
	glTranslatef(-(TORSO_RADIUS+UPPER_ARM_RADIUS), 0.9*TORSO_HEIGHT, 0.0);
	glRotatef(theta[3], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX,luparm_node.matrix);
	luparm_node.fptr = draw_luparm;
	init_node(luparm_node,1);
	luparm_node.children[0] = &lloarm_node;

	glLoadIdentity();
	glTranslatef(TORSO_RADIUS+UPPER_ARM_RADIUS, 0.9*TORSO_HEIGHT, 0.0);
	glRotatef(theta[5], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX,ruparm_node.matrix);
	ruparm_node.fptr = draw_ruparm;
	init_node(ruparm_node,1);
	ruparm_node.children[0] = &rloarm_node;

	glLoadIdentity();
	glTranslatef(-(TORSO_RADIUS+UPPER_LEG_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);
	glRotatef(theta[7], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX,lupleg_node.matrix);
	lupleg_node.fptr = draw_lupleg;
	init_node(lupleg_node,1);
	lupleg_node.children[0] = &lloleg_node;

	glLoadIdentity();
	glTranslatef(TORSO_RADIUS+UPPER_LEG_RADIUS, 0.1*UPPER_LEG_HEIGHT, 0.0);
	glRotatef(theta[9], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX,rupleg_node.matrix);
	rupleg_node.fptr = draw_rupleg;
	init_node(rupleg_node,1);
	rupleg_node.children[0] = &rloleg_node;

	glLoadIdentity();
	glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
	glRotatef(theta[4], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX,lloarm_node.matrix);
	lloarm_node.fptr = draw_lloleg;
	init_node(lloleg_node,0);
	lloleg_node.children = NULL;

	glLoadIdentity();
	glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
	glRotatef(theta[6], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX,rloarm_node.matrix);
	rloarm_node.fptr = draw_rloarm;
	init_node(rloarm_node,0);
	rloarm_node.children = NULL;

	glLoadIdentity();
	glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
	glRotatef(theta[8], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX,lloleg_node.matrix);
	lloleg_node.fptr = draw_lloleg;
	init_node(lloleg_node,0);
	lloleg_node.children = NULL;

	glLoadIdentity();
	glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
	glRotatef(theta[10], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX,rloleg_node.matrix);
	rloleg_node.fptr = draw_rloleg;
	init_node(rloleg_node,0);
	rloleg_node.children = NULL;

	glLoadIdentity();
		
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("robot");
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutCreateMenu(menu);
    glutAddMenuEntry("torso", 0);
    glutAddMenuEntry("head1", 1);
    glutAddMenuEntry("head2", 2);
    glutAddMenuEntry("right_upper_arm", 3);
    glutAddMenuEntry("right_lower_arm", 4);
    glutAddMenuEntry("left_upper_arm", 5);
    glutAddMenuEntry("left_lower_arm", 6);
    glutAddMenuEntry("right_upper_leg", 7);
    glutAddMenuEntry("right_lower_leg", 8);
    glutAddMenuEntry("left_upper_leg", 9);
    glutAddMenuEntry("left_lower_leg", 10);
    glutAddMenuEntry("quit", 11);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);

    glutMainLoop();
}
