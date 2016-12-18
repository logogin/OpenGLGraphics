#include <iostream.h>
//#include <stack.h>
#include <stdlib.h>
#include <conio.h>
#include "glut.h"
#include <time.h>
#define SIZEH 66 //visota
#define SIZEW 66 //shirina

int h;
int w;

float mashtabH = 1.8 / SIZEH;
float mashtabW = 1.8 / SIZEW;
int mart[SIZEH][SIZEW] = {0}; //fot test
void Draw(void);
void Reshape(int, int);
void Delay(int);
void Switch_Brake(int &, int &, int);
void change(int, int);
bool Test(int mart[][SIZEW], int, int);

//+++++++++++++++++MAIN+++++++++++++++++++++++++++++++++
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 50);

    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow("Dima");

    glutReshapeFunc(Reshape);
    glutDisplayFunc(Draw);
    glClearColor(0, 0, 0, 0);
    glutMainLoop();
    return 0;
}

//+++++++++++++++++++end main+++++++++++++++++++++++++++++++++++++++

void Reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool Test(int mart[][SIZEW], int h, int w)
{
    if (((mart[h + 1][w] == 0) || (mart[h - 1][w] == 0) ||
         (mart[h][w + 1] == 0) || (mart[h][w - 1] == 0)) &&

        ((mart[h - 1][w] == 0) || (mart[h][w + 1] == 0) ||
         (mart[h][w - 1] == 0) || (h != SIZEH - 1)) &&

        ((mart[h + 1][w] == 0) || (mart[h - 1][w] == 0) ||
         (mart[h][w - 1] == 0) || (w != SIZEW - 1)) &&

        ((mart[h + 1][w] == 0) || (mart[h - 1][w] == 0) ||
         (mart[h][w + 1] == 0) || (w != 0)) &&

        ((mart[h + 1][w] == 0) || (mart[h][w + 1] == 0) ||
         (mart[h][w - 1] == 0) || (h != 0)) &&

        ((mart[h - 1][w] == 0) || (w != SIZEW - 1) ||
         (mart[h][w - 1] == 0) || (h != SIZEH - 1)) &&

        ((mart[h + 1][w] == 0) || (h != 0) ||
         (mart[h][w - 1] == 0) || (w != SIZEW - 1)) &&

        ((mart[h + 1][w] == 0) || (h != 0) ||
         (mart[h][w + 1] == 0) || (w != 0)) &&

        ((mart[h - 1][w] == 0) || (w != 0) ||
         (mart[h][w + 1] == 0) || (h != SIZEH - 1)))
        return true;
    else
        return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 10.0f, 0.0f);
    glLineWidth(1);

    for (int e = 0; e < SIZEH; e++)
        for (int n = 0; n < SIZEW; n++)
            mart[e][n] = 0;
    glBegin(GL_LINES); //size line
    float cellH = -0.9;
    float cellW = -0.9;
    for (int i = 0; i <= SIZEH; i++)

    {
        glVertex2f(-0.9, -cellH);
        glVertex2f(0.9, -cellH);
        cellH += mashtabH;
    }
    for (int j = 0; j <= SIZEW; j++)
    {
        glVertex2f(cellW, 0.9);
        glVertex2f(cellW, -0.9);
        cellW += mashtabW;
    }

    glEnd();
    glFlush();
    srand((unsigned)time(NULL));
    int w = rand() % SIZEW;
    int h = rand() % SIZEH;
    change(h, w);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++

void Switch_Brake(int &h, int &w, int direct)
{
    float x1;
    float x2;
    float y1;
    float y2;

    switch (direct)

    {
    case 1: //up

        if (h == 0 || mart[h - 1][w] == 1)
        {

            if (mart[h][w + 1] != 1)
                direct = 2;
            if (mart[h + 1][w] != 1)
                direct = 4;
            if (mart[h][w - 1] != 1)
                direct = 3;
            direct = rand() % 4 + 1;
            break;
        }
        else
        {
            x1 = -0.9 + mashtabW * w;
            x2 = -0.9 + mashtabW + mashtabW * w;
            y1 = y2 = 0.9 - mashtabH * h;
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
            mart[h][w] = 1;
            if (h != 0)
                h--;
            else
                h++;
        }
        break;

    case 2: //right

        if (w == SIZEW - 1 || mart[h][w + 1] == 1)
        {
            if (mart[h][w - 1] != 1)
                direct = 3;
            if (mart[h + 1][w] != 1)
                direct = 4;
            if (mart[h - 1][w] != 1)
                direct = 1;

            direct = rand() % 4 + 1;
            break;
        }
        else
        {
            x1 = x2 = -0.9 + mashtabW * w + mashtabW;
            y1 = 0.9 - mashtabH * h - mashtabH;
            y2 = 0.9 - mashtabH * h;
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
            mart[h][w] = 1;
            if (w != SIZEW - 1)
                w++;
            else
                w--;
        }
        break;
    case 3: //left
        if (w == 0 || mart[h][w - 1] == 1)
        {
            if (mart[h][w + 1] != 1)
                direct = 2;
            if (mart[h + 1][w] != 1)
                direct = 4;
            if (mart[h - 1][w] != 1)
                direct = 1;

            direct = rand() % 4 + 1;
            break;
        }
        else
        {
            x1 = x2 = -0.9 + mashtabW * w;
            y1 = 0.9 - mashtabH * h - mashtabH;
            y2 = 0.9 - mashtabH * h;

            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
            mart[h][w] = 1;
            if (w != 0)
                w--;
            else
                w++;
        }
        break;
    case 4: //down
        if (h == SIZEH - 1 || mart[h + 1][w] == 1)
        {
            if (mart[h - 1][w] != 1)
                direct = 1;
            if (mart[h][w + 1] != 1)
                direct = 2;
            if (mart[h][w - 1] != 1)
                direct = 3;

            direct = rand() % 4 + 1;
            break;
        }
        else
        {
            x1 = -0.9 + mashtabW * w;
            x2 = -0.9 + mashtabW + mashtabW * w;
            y1 = y2 = 0.9 - mashtabH * h - mashtabH;
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
            mart[h][w] = 1;
            if (h != SIZEH - 1)
                h++;
            else
                h--;
        }
        break;
    }
    //	mart[h][w] = 1;
    glEnd();
    glFlush();
}
//++++++++++++++++++++++++++++++++++++++++++++++++++
void Delay(int sec)
{
    time_t e_time = time(0) + sec;
    while (time(0) < e_time)
        ;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void change(int h, int w)
{

    //int help1 = h;
    // int help2 = w;
    // change(h,w);
    //h = help1;
    //w = help2;

    glLineWidth(1);
    glColor3f(0, 0, 0);

    //	int	mart[SIZEH][SIZEW] ={0}  ;//fot test

    //		srand( (unsigned)time( NULL ) );
    //	int w = rand() % SIZEW  ;
    //   int h = rand() % SIZEH  ;

    /* for(int j = 0; j < SIZEH; j++)
       for(int f = 0; f < SIZEW; f++)
           martSum += mart[j][f];*/

    do
    {

        glBegin(GL_LINES);

        //   Delay(1);
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++=
        int direct = rand() % 4 + 1;
        cout << "direct : " << direct << endl;

        Switch_Brake(h, w, direct);

        for (int b = 0; b < SIZEW; b++)
        {
            for (int t = 0; t < SIZEH; t++)
                cout << mart[b][t];
            cout << endl;
        }

    } while (Test(mart, h, w) == true);
}
