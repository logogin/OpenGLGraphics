#ifndef Fido_H
#define Fido_H

#include <assert.h>
#include "Fido_Data.h"
#include "Includes.h"

/*******Prototypes********/
#define FACE4 GL_QUADS/*GL_LINE_LOOP*/
#define FACE3 GL_TRIANGLES/*GL_LINE_LOOP*/

GLsizei ww=800,wh=500; // size
GLsizei ww_last=800,wh_last=500; // size

/******Projection Volume*********/
GLfloat left=-50.0;
GLfloat right=50.0;
GLfloat bottom=-10.0;
GLfloat top=50.0;
GLfloat back=-50.0;
GLfloat front=50.0;

/***********Textures Images***********/
AUX_RGBImageRec *base_image0;
AUX_RGBImageRec *base_image1;
AUX_RGBImageRec *base_image2;
AUX_RGBImageRec *post_image;
AUX_RGBImageRec *blades_image0;
AUX_RGBImageRec *blades_image1;
AUX_RGBImageRec *blades_image2;
AUX_RGBImageRec *torso_image;
AUX_RGBImageRec *hand_image;
AUX_RGBImageRec *pelvis_image;
AUX_RGBImageRec *arm_image;
AUX_RGBImageRec *turret_image;
AUX_RGBImageRec *gauss_image;
AUX_RGBImageRec *floor_image;

/*******Textures Indeces***********/
unsigned int base_tex[3];
unsigned int post_tex;
unsigned int blades_tex[3];
unsigned int torso_tex;
unsigned int hand_tex;
unsigned int pelvis_tex;
unsigned int arm_tex;
unsigned int turret_tex;
unsigned int gauss_tex;
unsigned int floor_tex;

static GLint axis = 0;

static GLfloat fido_theta[16]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}; 
GLfloat fido_delta[16]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}; 

static GLfloat generator_theta[2]={0.0,0.0}; 
const GLfloat generator_delta[2]={2,6};

 

GLfloat pelvis_viewmatrix[16];

treenode base_node,post_node,blades_node;
treenode pelvis_node,torso_node;
treenode luparm_node,ruparm_node,lloarm_node,rloarm_node,lhand_node,rhand_node;
treenode lthing_node,rthing_node,lleg_node,rleg_node,lfoot_node,rfoot_node;
treenode turret_node,gauss_node;

/********Camera position***********/
static GLfloat camera[3]={1.0,5.0,10.0};
const GLfloat camera_theta[2]={0.05,0.05};
static GLfloat look_at[3]={0.0,0.0,0.0};
static GLfloat radius;
static GLfloat alpha,betta;
static int x_last,y_last;
bool start_motion=false;

/*********Main Functions*********/
void draw_scene(void);
void display(void);
void init(void);
void reshape(GLsizei,GLsizei);
void mouse(int,int,int,int);
void motion(int,int);
void keyboard(unsigned char,int,int);

/*******Fido********/
void draw_pelvis(void);
void draw_torso(void);
void draw_ruparm(void);
void draw_luparm(void);
void draw_rloarm(void);
void draw_lloarm(void);
void draw_rhand(void);
void draw_lhand(void);
void draw_turret(void);
void draw_gauss(void);
void draw_rthing(void);
void draw_lthing(void);
void draw_rleg(void);
void draw_lleg(void);
void draw_rfoot(void);
void draw_lfoot(void);
void draw_fido(void);
void walk_fido(void);

/**********Wind Generator********/
void draw_base(void);
void draw_post(void);
void draw_blades(void);
void draw_generator(void);

/***********Node Functions**********/
void traverse(treenode *);
void init_node(treenode *,const GLubyte);
void init_generator_node(void);
void init_fido_node(void);

/*********Texture functions*********/
void generate_texture(unsigned int,AUX_RGBImageRec *);
void set_textures(void);

/********Light and Matireal Functions*********/
void init_lights(void);
void lights(void);
void init_mat(void);
void set_mat(GLfloat amb[],GLfloat diff[],GLfloat spec[],GLfloat shin);

/************Implemntations********/

/********Node Functions*********/
void traverse(treenode *root)
{	

	if(root->children_number)
	{
		for (int i=0; i<root->children_number; i++)
		{
			glPushMatrix();
				glMultMatrixf(root->matrix);
				root->fptr();
				traverse(root->children[i]);
			glPopMatrix();
		}
	}
	else
	{
		glPushMatrix();
			glMultMatrixf(root->matrix);
			root->fptr();
		glPopMatrix();
	}

}

void init_node(treenode *root,const GLubyte child_num)
{
	root->children_number=child_num;
	root->children=new treenode *[child_num];
	assert(root->children!=NULL);
}

void init_generator_node()
{
	// Base
	glLoadIdentity();
	glTranslatef(-20.0,0.0,0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, base_node.matrix);
	base_node.fptr = draw_base;
	init_node(&base_node,1);
	base_node.children[0] =  &post_node;
 
	// Post
	glLoadIdentity();
	memcpy(post_node.center,post_center,sizeof(float)*3);
	glGetFloatv(GL_MODELVIEW_MATRIX, post_node.matrix);
	post_node.fptr = draw_post;
	init_node(&post_node,1);
	post_node.children[0] =  &blades_node;
	
	// Blades
	glLoadIdentity();
	memcpy(blades_node.center,blades_center,sizeof(float)*3);
	glGetFloatv(GL_MODELVIEW_MATRIX, blades_node.matrix);
	blades_node.fptr = draw_blades;
	init_node(&blades_node,0);
	blades_node.children =  NULL;
}

void init_fido_node()
{
	/*****Pelvis******/
	glLoadIdentity();
	//glTranslatef(20.0,0.0,0.0);
	//glScalef(3.0,3.0,3.0);
	memcpy(pelvis_node.center,pelvis_center,sizeof(float)*3);
	glGetFloatv(GL_MODELVIEW_MATRIX, pelvis_viewmatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, pelvis_node.matrix);
	pelvis_node.fptr = draw_pelvis;
	init_node(&pelvis_node,4);
	pelvis_node.children[0] = &torso_node;
	pelvis_node.children[1] = &turret_node;
	pelvis_node.children[2] = &lthing_node;
	pelvis_node.children[3] = &rthing_node;

	/*****Torso******/
	glLoadIdentity();
	memcpy(torso_node.center,torso_center,sizeof(float)*3);
	glGetFloatv(GL_MODELVIEW_MATRIX, torso_node.matrix);
	torso_node.fptr = draw_torso;
	init_node(&torso_node,2);
	torso_node.children[0] = &luparm_node;
	torso_node.children[1] = &ruparm_node;

	/*****Luparm******/
	glLoadIdentity();
	memcpy(luparm_node.center,luparm_center,sizeof(float)*3);
	glGetFloatv(GL_MODELVIEW_MATRIX, luparm_node.matrix);
	luparm_node.fptr = draw_ruparm;
	init_node(&luparm_node,1);
	luparm_node.children[0] = &lloarm_node;

	/*****Ruparm******/
	glLoadIdentity();
	memcpy(ruparm_node.center,ruparm_center,sizeof(float)*3);
	glGetFloatv(GL_MODELVIEW_MATRIX, ruparm_node.matrix);
	ruparm_node.fptr = draw_luparm;
	init_node(&ruparm_node,1);
	ruparm_node.children[0] = &rloarm_node;

	/*****Lloarm******/
	glLoadIdentity();
	memcpy(lloarm_node.center,lloarm_center,sizeof(float)*3);
	glGetFloatv(GL_MODELVIEW_MATRIX, lloarm_node.matrix);
	lloarm_node.fptr = draw_rloarm;
	init_node(&lloarm_node,1);
	lloarm_node.children[0] = &lhand_node;

	/*****Rloarm******/
	glLoadIdentity();
	memcpy(rloarm_node.center,rloarm_center,sizeof(float)*3);
	glGetFloatv(GL_MODELVIEW_MATRIX, rloarm_node.matrix);
	rloarm_node.fptr = draw_lloarm;
	init_node(&rloarm_node,1);
	rloarm_node.children[0] = &rhand_node;

	/*****Lhand******/
	glLoadIdentity();
	memcpy(lhand_node.center,lhand_center,sizeof(float)*3);
	glGetFloatv(GL_MODELVIEW_MATRIX, lhand_node.matrix);
	lhand_node.fptr = draw_rhand;
	init_node(&lhand_node,0);
	lhand_node.children = NULL;

	/*****Rhand******/
	glLoadIdentity();
	memcpy(rhand_node.center,rhand_center,sizeof(float)*3);
	glGetFloatv(GL_MODELVIEW_MATRIX, rhand_node.matrix);
	rhand_node.fptr = draw_lhand;
	init_node(&rhand_node,0);
	rhand_node.children = NULL;

	/*****Turret******/
	glLoadIdentity();
	memcpy(turret_node.center,turret_center,sizeof(float)*3);
	glGetFloatv(GL_MODELVIEW_MATRIX, turret_node.matrix);
	turret_node.fptr = draw_turret;
	init_node(&turret_node,1);
	turret_node.children[0] = &gauss_node;

	/*****Gauss******/
	glLoadIdentity();
	memcpy(gauss_node.center,gauss_center,sizeof(float)*3);
	glGetFloatv(GL_MODELVIEW_MATRIX, gauss_node.matrix);
	gauss_node.fptr = draw_gauss;
	init_node(&gauss_node,0);
	gauss_node.children = NULL;

	/*****Lthing******/
	glLoadIdentity();
	memcpy(lthing_node.center,lthing_center,sizeof(float)*3);
	glGetFloatv(GL_MODELVIEW_MATRIX, lthing_node.matrix);
	lthing_node.fptr = draw_rthing;
	init_node(&lthing_node,1);
	lthing_node.children[0] = &lleg_node;

	/*****Rthing******/
	glLoadIdentity();
	memcpy(rthing_node.center,rthing_center,sizeof(float)*3);
	glGetFloatv(GL_MODELVIEW_MATRIX, rthing_node.matrix);
	rthing_node.fptr = draw_lthing;
	init_node(&rthing_node,1);
	rthing_node.children[0] = &rleg_node;

	/*****Lleg******/
	glLoadIdentity();
	memcpy(lleg_node.center,lleg_center,sizeof(float)*3);
	glGetFloatv(GL_MODELVIEW_MATRIX, lleg_node.matrix);
	lleg_node.fptr = draw_rleg;
	init_node(&lleg_node,1);
	lleg_node.children[0] = &lfoot_node;

	/*****Rleg******/
	glLoadIdentity();
	memcpy(rleg_node.center,rleg_center,sizeof(float)*3);
	glGetFloatv(GL_MODELVIEW_MATRIX, rleg_node.matrix);
	rleg_node.fptr = draw_lleg;
	init_node(&rleg_node,1);
	rleg_node.children[0] = &rfoot_node;

	/*****Lfoot******/
	glLoadIdentity();
	memcpy(lfoot_node.center,lfoot_center,sizeof(float)*3);
	glGetFloatv(GL_MODELVIEW_MATRIX, lfoot_node.matrix);
	lfoot_node.fptr = draw_rfoot;
	init_node(&lfoot_node,0);
	lfoot_node.children = NULL;

	/*****Rfoot******/
	glLoadIdentity();
	memcpy(rfoot_node.center,rfoot_center,sizeof(float)*3);
	glGetFloatv(GL_MODELVIEW_MATRIX, rfoot_node.matrix);
	rfoot_node.fptr = draw_lfoot;
	init_node(&rfoot_node,0);
	rfoot_node.children = NULL;

//	traverse(&torso_node);
//	glLoadIdentity();
}

/***********Texture Functions************/
void generate_texture(unsigned int tex_index,AUX_RGBImageRec *image)
{
	glBindTexture(GL_TEXTURE_2D, tex_index);
	gluBuild2DMipmaps(GL_TEXTURE_2D,3,
		image->sizeX,image->sizeY,GL_RGB,GL_UNSIGNED_BYTE,
		image->data);
}

void set_textures()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	base_image0 = auxDIBImageLoad("Textures/plate1a.bmp");
	glGenTextures(1, &base_tex[0]);
	base_image1 = auxDIBImageLoad("Textures/armv01b.bmp");
	glGenTextures(1, &base_tex[1]);
	base_image2 = auxDIBImageLoad("Textures/clo3a.bmp");
	glGenTextures(1, &base_tex[2]);

	post_image = auxDIBImageLoad("Textures/noise5b.bmp");
	glGenTextures(1, &post_tex);

	blades_image0 = auxDIBImageLoad("Textures/clo2a.bmp");
	glGenTextures(1, &blades_tex[0]);
	blades_image1 = auxDIBImageLoad("Textures/arm01a.bmp");
	glGenTextures(1, &blades_tex[1]);
	blades_image2 = auxDIBImageLoad("Textures/32xlogos.bmp");
	glGenTextures(1, &blades_tex[2]);

	torso_image = auxDIBImageLoad("Textures/corap03.bmp");
	glGenTextures(1, &torso_tex);
	hand_image = auxDIBImageLoad("Textures/arm4b.bmp");
	glGenTextures(1, &hand_tex);
	pelvis_image = auxDIBImageLoad("Textures/corcam1a.bmp");
	glGenTextures(1, &pelvis_tex);
	arm_image = auxDIBImageLoad("Textures/corut1b.bmp");
	glGenTextures(1, &arm_tex);
	turret_image = auxDIBImageLoad("Textures/corsea3b.bmp");
	glGenTextures(1, &turret_tex);
	gauss_image = auxDIBImageLoad("Textures/armpanel.bmp");
	glGenTextures(1, &gauss_tex);
	floor_image = auxDIBImageLoad("Textures/santa.bmp");
	glGenTextures(1, &floor_tex);
}

/********Light and Matireal Functions*********/
void lights()
{
  glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
  glLightfv(GL_LIGHT0, GL_AMBIENT,  light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0_spec);

  glLightfv(GL_LIGHT1,  GL_POSITION, light1_pos);
  glLightfv(GL_LIGHT1,  GL_AMBIENT,  light1_ambient);
  glLightfv(GL_LIGHT1,  GL_DIFFUSE,  light1_diffuse);
  glLightfv(GL_LIGHT1,  GL_SPECULAR, light1_spec);
  glLightfv(GL_LIGHT1,  GL_SPOT_DIRECTION, light1_dir);
  glLightf (GL_LIGHT1,  GL_SPOT_EXPONENT,  light1_exp);
  glLightf (GL_LIGHT1,  GL_SPOT_CUTOFF,    light1_cutoff);

  glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);
  glLightfv(GL_LIGHT2, GL_AMBIENT,  light2_ambient);
  glLightfv(GL_LIGHT2, GL_DIFFUSE,  light2_diffuse);
  glLightfv(GL_LIGHT2, GL_SPECULAR, light2_spec);
  
  glPushMatrix();
	glTranslatef(a, b, c);
	glutSolidSphere(1, 20, 24);
  glPopMatrix();
  
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_amb);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
  
  glFogf(GL_FOG_DENSITY,.05);
  glEnable(GL_FOG);
  glEnable(GL_LIGHTING);
}

void set_mat(GLfloat amb[],GLfloat diff[],GLfloat spec[],GLfloat shin)
{
	glMaterialfv(GL_FRONT,GL_AMBIENT,amb);
	glMaterialfv(GL_FRONT,GL_SPECULAR,spec);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diff);
	glMaterialf(GL_FRONT,GL_SHININESS,shin);
}

/*********Fido********/
void draw_pelvis()
{
	glVertexPointer(3,GL_FLOAT,0,pelvis);
	generate_texture(pelvis_tex,pelvis_image);	
	glTexCoordPointer(3, GL_FLOAT, 0, pelvis);
	glEnable(GL_TEXTURE_2D);
	for (int i=0; i<6; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,pelvis_vertex[i]);
	glDisable(GL_TEXTURE_2D);
}

void draw_torso()
{
	glVertexPointer(3,GL_FLOAT,0,torso);
	generate_texture(torso_tex,torso_image);
	glTexCoordPointer(3, GL_FLOAT, 0, torso);
	glEnable(GL_TEXTURE_2D);
	for (int i=0; i<6; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,cube_vertex[i]);
	glDisable(GL_TEXTURE_2D);
}

void draw_ruparm()
{
	glVertexPointer(3,GL_FLOAT,0,ruparm);
	generate_texture(arm_tex,arm_image);
	glTexCoordPointer(3, GL_FLOAT, 0, ruparm);
	glEnable(GL_TEXTURE_2D);
	for (int i=0; i<6; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,cube_vertex[i]);
	glEnable(GL_TEXTURE_2D);
}

void draw_rloarm()
{
	glVertexPointer(3,GL_FLOAT,0,rloarm);
	generate_texture(blades_tex[2],blades_image2);
	glTexCoordPointer(3, GL_FLOAT, 0, rloarm);
	glEnable(GL_TEXTURE_2D);
	for (int i=0; i<6; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,cube_vertex[i]);
	glDisable(GL_TEXTURE_2D);
}

void draw_rhand()
{
	glVertexPointer(3,GL_FLOAT,0,rhand);
	generate_texture(hand_tex,hand_image);
	glTexCoordPointer(3, GL_FLOAT, 0, rhand);
	glEnable(GL_TEXTURE_2D);
	for (int i=0; i<3; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,hand_vertex[i]);
	for (i=0; i<2; i++)
		glDrawElements(FACE3/*GL_LINE_LOOP*/,3,
		GL_UNSIGNED_BYTE,hand_vertex[i+3]);
	glDisable(GL_TEXTURE_2D);
}

void draw_luparm()
{
	glVertexPointer(3,GL_FLOAT,0,luparm);
	generate_texture(arm_tex,arm_image);
	glTexCoordPointer(3, GL_FLOAT, 0, luparm);
	glEnable(GL_TEXTURE_2D);
	for (int i=0; i<6; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,cube_vertex[i]);
	glDisable(GL_TEXTURE_2D);
}

void draw_lloarm()
{
	glVertexPointer(3,GL_FLOAT,0,lloarm);
	generate_texture(blades_tex[2],blades_image2);
	glTexCoordPointer(3, GL_FLOAT, 0, lloarm);
	glEnable(GL_TEXTURE_2D);
	for (int i=0; i<6; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,cube_vertex[i]);
	glDisable(GL_TEXTURE_2D);
}

void draw_lhand()
{
	glVertexPointer(3,GL_FLOAT,0,lhand);
	generate_texture(hand_tex,hand_image);
	glTexCoordPointer(3, GL_FLOAT, 0, lhand);
	glEnable(GL_TEXTURE_2D);
	for (int i=0; i<3; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,hand_vertex[i]);
	for (i=0; i<2; i++)
		glDrawElements(FACE3/*GL_LINE_LOOP*/,3,
		GL_UNSIGNED_BYTE,hand_vertex[i+3]);
	glDisable(GL_TEXTURE_2D);
}

void draw_turret()
{
	glVertexPointer(3,GL_FLOAT,0,turret);
	generate_texture(turret_tex,turret_image);
	glTexCoordPointer(3, GL_FLOAT, 0, turret);
	glEnable(GL_TEXTURE_2D);
	for (int i=0; i<3; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,turret_vertex[i]);
	for (i=0; i<2; i++)
		glDrawElements(FACE3/*GL_LINE_LOOP*/,3,
		GL_UNSIGNED_BYTE,turret_vertex[i+3]);
	glDisable(GL_TEXTURE_2D);
}

void draw_gauss()
{
	glVertexPointer(3,GL_FLOAT,0,gauss);
	generate_texture(base_tex[1],base_image1);
	glTexCoordPointer(3, GL_FLOAT, 0, gauss);
	glEnable(GL_TEXTURE_2D);
	for (int i=0; i<6; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,gauss_vertex[i]);
	
	generate_texture(gauss_tex,gauss_image);
	glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,gauss_vertex[6]);

	generate_texture(base_tex[1],base_image1);
	for (i=0; i<2; i++)
		glDrawElements(FACE3/*GL_LINE_LOOP*/,3,
		GL_UNSIGNED_BYTE,gauss_vertex[i+7]);
	glDisable(GL_TEXTURE_2D);
}

void draw_rthing()
{
	glVertexPointer(3,GL_FLOAT,0,rthing);
	generate_texture(arm_tex,arm_image);
	glTexCoordPointer(3, GL_FLOAT, 0, rthing);
	glEnable(GL_TEXTURE_2D);
	for (int i=0; i<6; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,cube_vertex[i]);
	glDisable(GL_TEXTURE_2D);
}

void draw_lthing()
{
	glVertexPointer(3,GL_FLOAT,0,lthing);
	generate_texture(arm_tex,arm_image);
	glTexCoordPointer(3, GL_FLOAT, 0, lthing);
	glEnable(GL_TEXTURE_2D);
	for (int i=0; i<6; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,cube_vertex[i]);
	glDisable(GL_TEXTURE_2D);
}

void draw_rleg()
{
	glVertexPointer(3,GL_FLOAT,0,rleg);
	generate_texture(blades_tex[2],blades_image2);
	glTexCoordPointer(3, GL_FLOAT, 0, rleg);
	glEnable(GL_TEXTURE_2D);
	for (int i=0; i<6; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,cube_vertex[i]);
	glDisable(GL_TEXTURE_2D);
}

void draw_lleg()
{
	glVertexPointer(3,GL_FLOAT,0,lleg);
	generate_texture(blades_tex[2],blades_image2);
	glTexCoordPointer(3, GL_FLOAT, 0, lleg);
	glEnable(GL_TEXTURE_2D);
	for (int i=0; i<6; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,cube_vertex[i]);
	glDisable(GL_TEXTURE_2D);
}

void draw_rfoot()
{
	glVertexPointer(3,GL_FLOAT,0,rfoot);
	generate_texture(hand_tex,hand_image);
	glTexCoordPointer(3, GL_FLOAT, 0, rfoot);
	glEnable(GL_TEXTURE_2D);
	for (int i=0; i<6; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,cube_vertex[i]);
	glDisable(GL_TEXTURE_2D);
}

void draw_lfoot()
{
	glVertexPointer(3,GL_FLOAT,0,lfoot);
	generate_texture(hand_tex,hand_image);
	glTexCoordPointer(3, GL_FLOAT, 0, lfoot);
	glEnable(GL_TEXTURE_2D);
	for (int i=0; i<6; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,cube_vertex[i]);
	glDisable(GL_TEXTURE_2D);
}


/*void idle()
{
	anim1.Play();
	glutPostRedisplay();
}*/

/******Wind Generator*******/
void draw_base()
{
	glVertexPointer(3,GL_FLOAT,0,base);
	generate_texture(base_tex[1],base_image1);
	glTexCoordPointer(3, GL_FLOAT, 0, base);
	glEnable(GL_TEXTURE_2D);
	for (int i=0; i<8; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,base_vertex[i]);
	generate_texture(base_tex[2],base_image2);
	for (i=8; i<10; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,base_vertex[i]);
	generate_texture(blades_tex[2],blades_image2);
	for (i=10; i<16; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,base_vertex[i]);
	generate_texture(base_tex[0],base_image0);
	for (i=16; i<43; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,base_vertex[i]);
	glDisable(GL_TEXTURE_2D);
}

void draw_post()
{
	glVertexPointer(3,GL_FLOAT,0,post);
	generate_texture(post_tex,post_image);
	glTexCoordPointer( 3, GL_FLOAT,  0, post);
	glEnable(GL_TEXTURE_2D);
	glVertexPointer(3,GL_FLOAT,0,post);
	for (int i=0; i<39; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,post_vertex[i]);
	glDisable(GL_TEXTURE_2D);
}

void draw_blades()
{
	glVertexPointer(3,GL_FLOAT,0,blades);
	
	glTexCoordPointer( 3, GL_FLOAT,  0, blades);
	glEnable(GL_TEXTURE_2D);
	generate_texture(blades_tex[1],blades_image1);
	for (int i=0; i<13; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,blades_vertex[i]);
	generate_texture(blades_tex[0],blades_image0);
	for (i=3; i<10; i++)
		glDrawElements(FACE4/*GL_LINE_LOOP*/,4,
		GL_UNSIGNED_BYTE,blades_vertex[i]);
	generate_texture(blades_tex[2],blades_image2);
	for (i=0; i<3; i++)
		glDrawElements(FACE3/*GL_LINE_LOOP*/,3,
		GL_UNSIGNED_BYTE,blades_vertex[i+13]);
	glDisable(GL_TEXTURE_2D);
}

void draw_generator()
{
	glPushMatrix();
		glTranslatef(post_center[0],post_center[1],post_center[2]);
		generator_theta[0]+=generator_delta[0];
		glRotatef(generator_theta[0], 0.0, 1.0, 0.0);
		glTranslatef(-post_center[0],-post_center[1],-post_center[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,post_node.matrix);
	glPopMatrix();

	glPushMatrix();
		glLoadIdentity();
		glTranslatef(blades_center[0],blades_center[1],blades_center[2]);
		generator_theta[1]+=generator_delta[1];
		glRotatef(generator_theta[1], 0.0, 0.0, 1.0);
		glTranslatef(-blades_center[0],-blades_center[1],-blades_center[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,blades_node.matrix);
	glPopMatrix();

	traverse(&base_node);
}

void menu(int id)
{
	if (id==1) axis=0;
	if (id==2) axis=1;
	if (id==3) axis=2;
	if (id==4) axis=3;
	if (id==5) axis=4;
	if (id==6) axis=5;
	if (id==7) axis=6;
	if (id==8) axis=7;
	if (id==9) axis=8;
	if (id==10) axis=9;
	if (id==11) axis=10;
	if (id==12) axis=11;
	if (id==13) axis=12;
	if (id==14) axis=13;
	if (id==15) axis=14;
	if (id==16) axis=15;
	if (id==17) 
	{
		if (MessageBox(NULL,"Are you sure you want to exit?", 
			"Fido-Fast Attacking Cobot v2.204alpha",MB_YESNO|MB_ICONQUESTION)==IDYES)
		exit(0);
	}
}
void draw_fido()
{
	glPushMatrix();
		glTranslatef(torso_center[0],torso_center[1],torso_center[2]);
		fido_theta[0]+=fido_delta[0];
		glRotatef(fido_theta[0], 0.0, 0.0, 1.0);
		glTranslatef(-torso_center[0],-torso_center[1],-torso_center[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,torso_node.matrix);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(pelvis_center[0],pelvis_center[1],pelvis_center[2]);
		fido_theta[1]+=fido_delta[1];
		glRotatef(fido_theta[1], 0.0, 1.0, 0.0);
		glTranslatef(-pelvis_center[0],-pelvis_center[1],-pelvis_center[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,pelvis_node.matrix);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(luparm_center[0],luparm_center[1],luparm_center[2]);
		fido_theta[2]+=fido_delta[2];
		glRotatef(fido_theta[2], 1.0, 0.0, 0.0);
		glTranslatef(-luparm_center[0],-luparm_center[1],-luparm_center[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,luparm_node.matrix);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(ruparm_center[0],ruparm_center[1],ruparm_center[2]);
		fido_theta[3]+=fido_delta[3];
		glRotatef(fido_theta[3], 1.0, 0.0, 0.0);
		glTranslatef(-ruparm_center[0],-ruparm_center[1],-ruparm_center[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,ruparm_node.matrix);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(lloarm_center[0],lloarm_center[1],lloarm_center[2]);
		fido_theta[4]+=fido_delta[4];
		glRotatef(fido_theta[4], 1.0, 0.0, 0.0);
		glTranslatef(-lloarm_center[0],-lloarm_center[1],-lloarm_center[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,lloarm_node.matrix);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(rloarm_center[0],rloarm_center[1],rloarm_center[2]);
		fido_theta[5]+=fido_delta[5];
		glRotatef(fido_theta[5], 1.0, 0.0, 0.0);
		glTranslatef(-rloarm_center[0],-rloarm_center[1],-rloarm_center[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,rloarm_node.matrix);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(lhand_center[0],lhand_center[1],lhand_center[2]);
		fido_theta[6]+=fido_delta[6];
		glRotatef(fido_theta[6], 1.0, 0.0, 0.0);
		glTranslatef(-lhand_center[0],-lhand_center[1],-lhand_center[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,lhand_node.matrix);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(rhand_center[0],rhand_center[1],rhand_center[2]);
		fido_theta[7]+=fido_delta[7];
		glRotatef(fido_theta[7], 1.0, 0.0, 0.0);
		glTranslatef(-rhand_center[0],-rhand_center[1],-rhand_center[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,rhand_node.matrix);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(lthing_center[0],lthing_center[1],lthing_center[2]);
		fido_theta[8]+=fido_delta[8];
		glRotatef(fido_theta[8], 1.0, 0.0, 0.0);
		glTranslatef(-lthing_center[0],-lthing_center[1],-lthing_center[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,lthing_node.matrix);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(rthing_center[0],rthing_center[1],rthing_center[2]);
		fido_theta[9]+=fido_delta[9];
		glRotatef(fido_theta[9], 1.0, 0.0, 0.0);
		glTranslatef(-rthing_center[0],-rthing_center[1],-rthing_center[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,rthing_node.matrix);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(lleg_center[0],lleg_center[1],lleg_center[2]);
		fido_theta[10]+=fido_delta[10];
		glRotatef(fido_theta[10], 1.0, 0.0, 0.0);
		glTranslatef(-lleg_center[0],-lleg_center[1],-lleg_center[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,lleg_node.matrix);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(rleg_center[0],rleg_center[1],rleg_center[2]);
		fido_theta[11]+=fido_delta[11];
		glRotatef(fido_theta[11], 1.0, 0.0, 0.0);
		glTranslatef(-rleg_center[0],-rleg_center[1],-rleg_center[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,rleg_node.matrix);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(lfoot_center[0],lfoot_center[1],lfoot_center[2]);
		fido_theta[12]+=fido_delta[12];
		glRotatef(fido_theta[12], 1.0, 0.0, 0.0);
		glTranslatef(-lfoot_center[0],-lfoot_center[1],-lfoot_center[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,lfoot_node.matrix);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(rfoot_center[0],rfoot_center[1],rfoot_center[2]);
		fido_theta[13]+=fido_delta[13];
		glRotatef(fido_theta[13], 1.0, 0.0, 0.0);
		glTranslatef(-rfoot_center[0],-rfoot_center[1],-rfoot_center[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,rfoot_node.matrix);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(turret_center[0],turret_center[1],turret_center[2]);
		fido_theta[14]+=fido_delta[14];
		glRotatef(fido_theta[14], 0.0, 1.0, 0.0);
		glTranslatef(-turret_center[0],-turret_center[1],-turret_center[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,turret_node.matrix);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(gauss_center[0],gauss_center[1],gauss_center[2]);
		fido_theta[15]+=fido_delta[15];
		glRotatef(fido_theta[15], 1.0, 0.0, 0.0);
		glTranslatef(-gauss_center[0],-gauss_center[1],-gauss_center[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,gauss_node.matrix);
	glPopMatrix();
	
	traverse(&pelvis_node);
}

void special(int key,int x,int y)
{
	if (key==GLUT_KEY_RIGHT)
	{ 
		fido_delta[axis] += 3.0;
        if( fido_delta[axis] > 360.0 ) fido_delta[axis] -= 360.0;
	}
	if(key==GLUT_KEY_LEFT)
	{ 
		fido_delta[axis] -= 3.0;
        if( fido_delta[axis] < 0.0 ) fido_delta[axis] += 360.0;
	}
	draw_fido(); 
}

/********Camera Functions********/
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
	if(eye[2]>0.0)
		betta=2*PI-betta;
}

/**********Main Functions*********/
void motion(int x,int y)
{
	if (start_motion)
	{
		betta+=(x-x_last)*camera_theta[0];
		alpha+=(y-y_last)*camera_theta[1];
		x_last=x;
		y_last=y;
		get_normal(&camera[0]);
		reshape(ww,wh);
	}
}

void mouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON)
	{
		if (button==GLUT_DOWN)
		{
			start_motion=true;
			x_last=x;
			y_last=y;
		}
		else
			start_motion=false;
	}
}

// Draw floor with texture
static void drawFloor(void)
{
  glDisable(GL_LIGHTING);

	generate_texture(floor_tex,floor_image);
    glEnable(GL_TEXTURE_2D);

  glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3fv(floorVertices[0]);
    glTexCoord2f(0.0, 16.0);
    glVertex3fv(floorVertices[1]);
    glTexCoord2f(16.0, 16.0);
    glVertex3fv(floorVertices[2]);
    glTexCoord2f(16.0, 0.0);
    glVertex3fv(floorVertices[3]);
  glEnd();

    glDisable(GL_TEXTURE_2D);

  glEnable(GL_LIGHTING);
}

// Create menu
void Create_Menu()
{
    glutCreateMenu(menu);
    glutAddMenuEntry("torso", 1);
    glutAddMenuEntry("pelvis", 2);
    glutAddMenuEntry("left upper arm", 3);
    glutAddMenuEntry("right upper arm", 4);
    glutAddMenuEntry("left lower arm", 5);
    glutAddMenuEntry("right lower arm", 6);
    glutAddMenuEntry("left hand", 7);
    glutAddMenuEntry("right hand", 8);
    glutAddMenuEntry("left thigh", 9);
    glutAddMenuEntry("right thigh", 10);
    glutAddMenuEntry("left leg", 11);
    glutAddMenuEntry("right leg", 12);
    glutAddMenuEntry("left foot", 13);
    glutAddMenuEntry("right foot", 14);
    glutAddMenuEntry("turret", 15);
    glutAddMenuEntry("gauss", 16);
    glutAddMenuEntry("quit", 17);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

#endif Fido_H