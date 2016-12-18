/*
Howm Work1.Andreenko Dmitry.
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "glut.h"
#include <time.h>

#define Width 15
#define Height 15
#define scale 20

typedef struct
{
    int x;
    int y;
} Place;

int Board(Place);
void BreakWall(Place, int);
void Labirint();
Place Coordinates();
Place NCoord(Place, int);
void drawLab();
void drawMatrix();
void myInit();
void display();
void Execute(int[Height][Width], Place);
int NFree(int[Height][Width], Place);

// main
void main(int argc, char **argv)
{
    srand((unsigned)time(NULL)); //change the values every time of program executing
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 400);
    glutCreateWindow("MAZE");
    glutDisplayFunc(display);
    myInit();
    glutMainLoop();
}

//myInit
void myInit()
{
    glClearColor(0, 0, 0, 1);
    glColor3f(0.68, 0.57, 0.87);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50, scale * Width + 50, -50, scale * Height + 50); //the changing of maze's size
    glMatrixMode(GL_MODELVIEW);
}

//display
void display()
{
    drawMatrix();
    Labirint();
}

//drawMatrix
void drawMatrix()
{
    int sp[2], ep[2];
    int r, c;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0., 0.53, 0.97);
    glLineWidth(2);
    sp[0] = 0;             //start coordinate of x
    ep[0] = scale * Width; //end coordinate of f
    for (r = 0; r <= Height; r++)
    {
        sp[1] = ep[1] = 0 + scale * r; //coordinates of y
        glBegin(GL_LINES);             //draw lines by width
        glVertex2iv(sp);
        glVertex2iv(ep);
        glEnd();
    }
    sp[1] = 0;              //start coordinate of y
    ep[1] = scale * Height; //end coordinate of y
    for (c = 0; c <= Width; c++)
    {
        sp[0] = ep[0] = 0 + scale * c; //coordinates of x
        glBegin(GL_LINES);             //draw lines by hight
        glVertex2iv(sp);
        glVertex2iv(ep);
        glEnd();
    }
    glFlush();
}

//---------------- BreakWall -------------------

void BreakWall(Place current, int dir)
{
    int sp[2], ep[2];
    glColor3f(0.0, 0.0, 0.0);
    switch (dir)
    {
    case 0: //up
    {
        sp[0] = 0 + scale * current.x;              //start coordinate of x
        ep[0] = sp[0] + scale;                      //end coordinate of x
        sp[1] = scale * Height - scale * current.y; //start coordinate of y
        ep[1] = sp[1];                              //end coordinate of y
        printf("s(%d %d) e(%d %d) dir= %d\n", sp[0], sp[1], ep[0], ep[1], dir);
        glBegin(GL_LINES); //draw black line - break wall
        glVertex2iv(sp);
        glVertex2iv(ep);
        glEnd();
        break;
    }
    case 1: //down
    {
        sp[0] = 0 + scale * current.x;                    //start coordinate of x
        ep[0] = sp[0] + scale;                            //end coordinate of x
        sp[1] = scale * Height - scale * (current.y + 1); //start coordinate of y
        ep[1] = sp[1];                                    //end coordinate of y
        printf("s(%d %d) e(%d %d) drive=%d\n", sp[0], sp[1], ep[0], ep[1], dir);
        glBegin(GL_LINES); //draw black line - break wall
        glVertex2iv(sp);
        glVertex2iv(ep);
        glEnd();
        break;
    }
    case 2: //left
    {
        sp[0] = 0 + scale * current.x;              //start coordinate of x
        ep[0] = sp[0];                              //end coordinate of x
        sp[1] = scale * Height - scale * current.y; //start coordinate of y
        ep[1] = sp[1] - scale;                      //end coordinate of y
        printf("s(%d %d) e(%d %d) dir=%d\n", sp[0], sp[1], ep[0], ep[1], dir);
        glBegin(GL_LINES); //draw black line - break wall
        glVertex2iv(sp);
        glVertex2iv(ep);
        glEnd();
        break;
    }
    case 3: //right
    {
        sp[0] = 0 + scale * (current.x + 1);        //start coordinate of x
        ep[0] = sp[0];                              //end coordinate of x
        sp[1] = scale * Height - scale * current.y; //start coordinate of y
        ep[1] = sp[1] - scale;                      //end coordinate of y
        printf("s(%d %d) e(%d %d) drive=%d\n", sp[0], sp[1], ep[0], ep[1], dir);
        glBegin(GL_LINES); //draw black line - break wall
        glVertex2iv(sp);
        glVertex2iv(ep);
        glEnd();
        break;
    }
    }
    glFlush();
}

// Random place
Place Coordinates()
{
    Place rp;
    do
    {
        rp.x = rand() % Width;
        rp.y = rand() % Height;
    } while (Board(rp));
    return rp;
}
//cheack board
int Board(Place rp)
{
    return ((0 <= rp.x && rp.x < Width) && (0 <= rp.y && rp.y < Height)) ? 0 : 1;
}
//build maze
void Labirint()
{
    Place Rand_Place;
    int Check[Height][Width] = {0};
    //int count=(Width-1)*(Height-1);
    int i, j, flag;
    Rand_Place = Coordinates();
    printf("%d %d\n", Rand_Place.x, Rand_Place.y);
    Check[Rand_Place.y][Rand_Place.x] = 1;
    do
    {
        flag = 0;
        for (i = 0; i < Width; i++)
            for (j = 0; j < Height; j++)
                if (Check[i][j] == 1)
                {
                    Rand_Place.x = j;
                    Rand_Place.y = i;
                    if (NFree(Check, Rand_Place))
                    {
                        i = Width;
                        j = Height;
                        flag = 1;
                    }
                }
        if (flag)
            Execute(Check, Rand_Place);
    } while (flag);
    //the enter to maze
    Rand_Place.x = 0;
    Rand_Place.y = 0;
    BreakWall(Rand_Place, 0);
    //the exit from maze
    Rand_Place.x = (Width - 1);
    Rand_Place.y = (Height - 1);
    BreakWall(Rand_Place, 1);
}

Place NCoord(Place rp)
{
    x + 1;
    help.y = rp.y;
    if ((ch[help.y][help.x] == 0) && Board(help) == 0)
        return 1;

    help.x = rp.x;
    help.y = rp.y - 1;
    if ((ch[help.y][help.x] == 0) && Board(help) == 0)
        return 1;

    help.x = rp.x;
    help.y = rp.y + 1;
    if ((ch[help.y][help.x] == 0) && Board(help) == 0)
        return 1;
    return 0;
}

void Execute(int ch[Height][Width], Place rp)
{
    int neighbour;
    long i;
    Place nc;
    while (NFree(ch, rp))
    {
        neighbour = rand() % 4;
        nc = NCoord(rp, neighbour);
        if (!Board(nc) && ch[nc.y][nc.x] != 1)
        {
            ch[nc.y][nc.x] = 1;
            BreakWall(rp, neighbour);
            for (i = 0; i < 200000; i++)
                ;
            printf("col=%d row=%d deleted\n", nc.x, nc.y);
            rp = nc;
        }
    }
}