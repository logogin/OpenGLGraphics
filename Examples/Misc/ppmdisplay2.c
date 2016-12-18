#include <stdio.h>
#include <stdlib.h>

#include <GL/glut.h>

int n;
int m;


GLubyte *image;


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2i(0,0);
    glDrawPixels(n,m,GL_RGB, GL_UNSIGNED_BYTE, image);
	glFlush();
}


void myreshape(int h, int w)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLfloat) n, 0.0, (GLfloat) m);
	glMatrixMode(GL_MODELVIEW);
}

main(int argc, char *argv[])
{
	FILE *fd;
	int  k, nm;
	char c;
	int i;
	char b[100];
	float s;
	int red, green, blue;

	fd = fopen(argv[1], "r");
	fscanf(fd,"%[^\n] ",b);
	if(b[0]!='P'|| b[1] != '3')
	{
		printf("%s is not a PPM file!\n",argv[1]); 
		exit(0);
	}
	printf("%s is a PPM file\n", argv[1]);
	fscanf(fd, "%c",&c);
	while(c == '#') 
	{
		fscanf(fd, "%[^\n] ", b);
		printf("%s\n",b);
		fscanf(fd, "%c",&c);
	}
	ungetc(c,fd); 
	fscanf(fd, "%d %d %d", &n, &m, &k);

	printf("%d rows  %d columns  max value= %d\n",n,m,k);

	nm = n*m;

	image=malloc(3*sizeof(GLuint)*nm);


	s=255./k;


	if (k==255) for(i=0;i<nm;i++) 
	{
		fscanf(fd,"%d %d %d",&red, &green, &blue );
		image[3*nm-3*i-3]=red;
		image[3*nm-3*i-2]=green;
		image[3*nm-3*i-1]=blue;
	}
	else for(i=0;i<nm;i++) 
	{
		fscanf(fd,"%d %d %d",&red, &green, &blue );
		image[3*nm-3*i-3]=red*s;
		image[3*nm-3*i-2]=green*s;
		image[3*nm-3*i-1]=blue*s;
	}

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(n, m);
    glutCreateWindow("image");
    glClearColor (1.0, 1.0, 1.0, 1.0);
	glutReshapeFunc(myreshape);
    glutDisplayFunc(display);
    glutMainLoop();


}


