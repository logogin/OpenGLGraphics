#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <GL/glut.h>

GLsizei ww=500;
GLsizei wh=500;

GLushort max_iter=100;

long double centerx=-0.7;
long double centery=0.0;
long double heigth=3;
long double width=3;
long double stepx;
long double stepy;

GLubyte *image;

void create_image()
{
	long double cx;
	long double cy;
	long double xmin;
	long double ymin;
	long double x,y,temp,rel2,img2;
	GLushort iter;
	stepx=width/500;
	stepy=heigth/500;
	xmin=centerx-width/2;
	ymin=centery-heigth/2;
	cy=ymin-stepy;
	for (int i=0; i<500; i++)
	{
		cy+=stepy;
		cx=xmin-stepx;
		for (int j=0; j<500; j++)
		{
			cx+=stepx;
			x=y=rel2=img2=0.0;
			iter=0;
			
			while (iter<250&&(rel2+img2)<4.0)
			{
				temp=rel2-img2+cx;
				y=2*x*y+cy;
				x=temp;
				rel2=x*x;
				img2=y*y;
				iter++;
			}
			if ((rel2+img2)<4.0)
				image[j+i*500]=(rel2+img2)*256;
			if ((rel2+img2)>4.0)
				image[j+i*500]=iter;
			//if ((rel2+img2)><4.0)

		//		image[j+i*500]=1.0;
		//	if (rel2+img2<1.0)
				//image[j+i*500]=255*(rel2+img2);
		}
	}
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(500,500,GL_COLOR_INDEX, GL_UNSIGNED_BYTE, image);
}


void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
    gluOrtho2D(0.0, 0.0, (GLfloat) 500, (GLfloat) 500* (GLfloat) h / (GLfloat) w);
    else
    gluOrtho2D(0.0, 0.0, (GLfloat) 500 * (GLfloat) 500 / (GLfloat) h,(GLfloat) 500);
    glMatrixMode(GL_MODELVIEW);
}

void init()
{
    GLfloat redmap[256], greenmap[256],bluemap[256];
	
    glClearColor (0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(0.0, 0.0, (GLfloat) 500, (GLfloat) 500);

    for(int i=0; i<256; i++) 
	{
		redmap[i]=(rand()%256)/255.0;
		greenmap[i]=(rand()%256)/255.0;
		bluemap[i]=(rand()%256)/255.0;
	}

    glPixelMapfv(GL_PIXEL_MAP_I_TO_R, 256, redmap);
    glPixelMapfv(GL_PIXEL_MAP_I_TO_G, 256, greenmap);
    glPixelMapfv(GL_PIXEL_MAP_I_TO_B, 256, bluemap); 

/*	glGetPixelMapfv(GL_PIXEL_MAP_I_TO_R,redmap);
	glGetPixelMapfv(GL_PIXEL_MAP_I_TO_G,greenmap);
	glGetPixelMapfv(GL_PIXEL_MAP_I_TO_B,bluemap);*/

	image=new GLubyte[500*500];
	assert(image!=NULL);
	create_image();
	for (i=0;i<256; i++ )
		image[i]=i;
}


void main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(500, 500);
    glutCreateWindow("Mandlebrot Set");
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    init();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);

    glutMainLoop();

	delete []image;
}
