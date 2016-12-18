
#include <stdlib.h>
#include <GL/glut.h>

int n;
int m;

/* Use unsigned bytes for image */

/* GLuint image[768][1024]; */
/* GLuint image[436][465]; */

GLuint *p;


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(n,m,GL_COLOR_INDEX, GL_UNSIGNED_INT, p);
}


void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
    gluOrtho2D(0.0, 0.0, (GLfloat) n, (GLfloat) m* (GLfloat) h / (GLfloat) w);
    else
    gluOrtho2D(0.0, 0.0, (GLfloat) n * (GLfloat) w / (GLfloat) h,(GLfloat) m);
    glMatrixMode(GL_MODELVIEW);
    display();
}

void myinit()
{
    float redmap[256], greenmap[256],bluemap[256];
    int i;

    glClearColor (1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0.0, 0.0, (GLfloat) n, (GLfloat) m);


    for(i=0;i<256;i++) 
    {
         redmap[i]=i/255.;
         greenmap[i]=i/255.;
         bluemap[i]=i/255.;
    }

    glPixelMapfv(GL_PIXEL_MAP_I_TO_R, 256, redmap);
    glPixelMapfv(GL_PIXEL_MAP_I_TO_G, 256, greenmap);
    glPixelMapfv(GL_PIXEL_MAP_I_TO_B, 256, bluemap); 
}

main(int argc, char *argv[])
{
    int i, nm, k,j, ik,jk;
	float d;
	GLuint *image;
	scanf("%d%d\n", &n ,&m);
	printf("%d %d\n",n,m);
	nm=n*m;
	image=malloc(sizeof(GLuint)*nm);
	p=image;
	scanf("%d", &image[0]);
	ik=jk=0;
	k=j=image[0];
	for(i=1;i<nm;i++)
	{
		scanf("%d", &image[i]);
		if(image[i]>k) 
		{
		   k=image[i];
		   ik=i;
		}
		if(image[i]<j) 
		{
		   j=image[i];
		   jk=i;
		}
    }
	printf("%d %d \n",k, j);
	printf("%d %d\n",ik,jk);
	d=255./(k-j);
	for(i=0;i<nm;i++)
	{
        image[i]=(image[i]-j)*d;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(n, m);
    glutCreateWindow("image");
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);

    glutMainLoop();


}
