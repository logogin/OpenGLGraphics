#include <iostream.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>
#include <stack>

GLuint n=100;
GLuint m=100;

GLsizei hw=500;
GLsizei ww=500;
const GLfloat step=10.0;
GLfloat borderx;
GLfloat bordery;
GLfloat res;

GLubyte *matrix;
const GLbyte deltax[4]={1,-1,0,0};
const GLbyte deltay[4]={0,0,1,-1};
//							  ->|  |<-  ~    _
const GLubyte walls_mask[4]={0x02,0x04,0x08,0x10};

void init_matrix()
{
	matrix=new GLubyte[n*m];
	if (matrix==NULL)
	{
		cerr <<"Cannot alocate memory !!! (matrix)"<<endl;
		exit(1);
	}
	for (int i=0; i<n*m; i++)
		matrix[i]=0x1E;
}

void delay(GLushort sec)
{
	__asm
	{
		mov	cx,200;
outer:	push cx
		mov cx,0
inner:	loop inner
		pop cx
		loop outer
	}
/*	{
   time_t e_time = time(0) + sec;
   while(time(0) < e_time);}*/

}

void write_matrix(const GLuint &i,const GLuint &j,const GLubyte &value)
{
	matrix[i*m+j]=value;
}

GLubyte read_matrix(const GLuint &i,const GLuint &j)
{
	return matrix[i*m+j];
}

bool in_grid(const GLuint &i,const GLuint &j,const GLint dir)
{
	if ((i+deltay[dir])>=0&&(i+deltay[dir])<n&&
		(j+deltax[dir])>=0&&(j+deltax[dir])<m)
		return true;
	else
		return false;
}
void break_wall(const GLuint &j,const GLuint &i,const GLbyte dir)
{
	write_matrix(i,j,read_matrix(i,j)&(walls_mask[dir]^0xFF));
	if (dir%2)
		write_matrix(i+deltay[dir],j+deltax[dir],
		read_matrix(i+deltay[dir],j+deltax[dir])&
		(walls_mask[dir-1]^0xFF));
	else
		write_matrix(i+deltay[dir],j+deltax[dir],
		read_matrix(i+deltay[dir],j+deltax[dir])&
		(walls_mask[dir+1]^0xFF));
	
	write_matrix(i+deltay[dir],j+deltax[dir],
		read_matrix(i+deltay[dir],j+deltax[dir])|0x01);
	
	glBegin(GL_LINES);
		switch (dir)
		{
		case 0:
			glVertex2f(borderx+(j+1)*step,
				bordery+i*step);
			glVertex2f(borderx+(j+1)*step,
				bordery+(i+1)*step);
			break;
		case 1:
			glVertex2f(borderx+j*step,
				bordery+i*step);
			glVertex2f(borderx+j*step,
				bordery+(i+1)*step);
			break;
		case 2:
			glVertex2f(borderx+j*step,
				bordery+(i+1)*step);
			glVertex2f(borderx+(j+1)*step,
				bordery+(i+1)*step);
			break;
		case 3:
			glVertex2f(borderx+j*step,
				bordery+i*step);
			glVertex2f(borderx+(j+1)*step,
				bordery+i*step);
			break;
		}
	glEnd();
	glFlush();
//	delay(10);
}

GLbyte find_dir(const GLint &j,const GLint &i)
{
	GLubyte enable_dir[4]={0};
	GLubyte dir_num=0;
	for (GLbyte dir=0; dir<4; dir++)
		if (in_grid(i,j,dir)&&
			!(read_matrix(i+deltay[dir],j+deltax[dir])&0x01))
		{
			enable_dir[dir_num]=dir;
			dir_num++;
		}

	if (dir_num)
		return enable_dir[rand()%dir_num];
	else 
		return -1;
}

void draw_path(GLuint x, GLuint y)
{
	GLbyte dir;
	write_matrix(y,x,read_matrix(y,x)|0x01);
	dir=find_dir(x,y);
	if (dir!=-1)
	{
		break_wall(x,y,dir);
		draw_path(x+deltax[dir],y+deltay[dir]);
	}
	
	dir=find_dir(x,y);
	if (dir!=-1)
	{
		break_wall(x,y,dir);
		draw_path(x+deltax[dir],y+deltay[dir]);
	}
}

void find_path()
{
	GLuint i=n-1;
	GLuint j=0;
	GLbyte dir;
	bool flag;

	std::stack <GLbyte> path;
	write_matrix(i,j,(read_matrix(i,j)|0x80));
	while (i!=0||j!=(m-1))
	{
		flag=false;
		dir=0;
		while (dir<4&&!flag)
		{
			if (in_grid(i,j,dir)&&!(read_matrix(i,j)&walls_mask[dir])&&
				!(read_matrix(i+deltay[dir],j+deltax[dir])&0x80))
			{
				flag=true;
				i+=deltay[dir];
				j+=deltax[dir];
				path.push(dir);
				write_matrix(i,j,(read_matrix(i,j)|0x80));
			}
			else
				dir++;
		}
		if (!flag)
		{
			
			dir=path.top();
			path.pop();
			i-=deltay[dir];
			j-=deltax[dir];
		}
	}

	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_STRIP);
	while (!path.empty())
	{
		glVertex2f(borderx+j*step+step/2,bordery+i*step+step/2);
		dir=path.top();
		path.pop();
		i-=deltay[dir];
		j-=deltax[dir];
	}
		glVertex2f(borderx+j*step+step/2,bordery+i*step+step/2);
	glEnd();
}

void define_scale()
{
	if (n<=m)
	{
		borderx=25.0;
		bordery=step*(m-n)/2+borderx;
		res=m*step+2*borderx;
	}
	else
	{
		bordery=25.0;
		borderx=step*(n-m)/2+bordery;
		res=n*step+2*bordery;
	}
}

void myinit()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	define_scale();
	gluOrtho2D(0.0,res,0.0,res);
	glViewport(0,0,ww,hw);
	glMatrixMode(GL_MODELVIEW);
}

void myreshape(GLsizei w,GLsizei h)
{
	ww=w;
	hw=h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		gluOrtho2D (0.0,res,0.0,res*h/(GLfloat)w);
		bordery=(res*h/(GLfloat)w-n*step)/2;
		borderx=(res-m*step)/2;
	}
	else
	{
		gluOrtho2D (0.0,res*w/(GLfloat)h,0.0,res);
		borderx=(res*w/(GLfloat)h-m*step)/2;
		bordery=(res-n*step)/2;
	}
	glViewport(0,0,ww,hw);
	glMatrixMode(GL_PROJECTION);
}
void draw_grid()
{
	glColor3f(0.0,1.0,1.0);
	glBegin(GL_LINES);
	for (int i=0; i<=n; i++)
	{
		glVertex2f(borderx,bordery+i*step);
		glVertex2f(borderx+m*step,bordery+i*step);
	}
	
	for (i=0; i<=m; i++)
	{
		glVertex2f(borderx+i*step,bordery);
		glVertex2f(borderx+i*step,bordery+n*step);
	}
	
	glColor3f(0.0,0.0,0.0);
		glVertex2f(borderx,bordery+n*step);
		glVertex2f(borderx+step,bordery+n*step);
		glVertex2f(borderx+(m-1)*step,bordery);
		glVertex2f(borderx+m*step,bordery);
	
	glEnd();

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	init_matrix();
	draw_grid();
	draw_path(rand()%m,rand()%n);
	find_path();
	glFlush();
}

void main(int narg, char **argv)
{
	glutInit(&narg, argv);
	srand((unsigned)time(NULL));
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww,hw);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Maze Builder, Ver 2.1");
	glutDisplayFunc(display);
	myinit();
	glutReshapeFunc(myreshape);
	glutMainLoop();
	delete []matrix;
}