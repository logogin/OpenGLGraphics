/*	F1 - for change view
    ESC - for exit
    Arrows : left, right, up, down - for rotating a robot
    Space - for explose a robot
*/
/*****************************/
/*	A,S,D,X - for rotating a lamp */
/* Students : Andreenko Dmitry
*			  Sahin Yakov	
*			  Gotlev Evgeny
*			  Berdichevsky Michael
*			  Balkovsky Vitaly
*			  Konovalenko Alla	
*			  Katalimov Vyacheslav
*/
#include "glut.h"
#include "robot.h"

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <stdio.h>

#define NUM_PARTICLES 1000 /* Number of particles  */
#define NUM_DEBRIS 500     /* Number of debris     */

/*Drawing Text*/
void draw_string_stroke(void *font, const char *string)
{
    while (*string)
        glutStrokeCharacter(font, *string++);
}

/* A piece of particle */

struct particleData
{
    float position[3];
    float speed[3];
    float color[3];
};
typedef struct particleData particleData;

/* A piece of debris */

struct debrisData
{
    float position[3];
    float speed[3];
    float orientation[3]; /* Rotation angles around x, y, and z axes */
    float orientationSpeed[3];
    float color[3];
    float scale[3];
};
typedef struct debrisData debrisData;

/* Globals */

particleData particles[NUM_PARTICLES];
debrisData debris[NUM_DEBRIS];
int fuel = 0; /* "fuel" of the explosion */

float angle = 0.0; /* camera rotation angle */

/* Light sources and material */

GLfloat light2Amb[4] = {1.0, 0.0, 0.0, 1.0};
GLfloat light2Dif[4] = {1.0, 0.0, 0.0, 1.0};
GLfloat light2Spec[4] = {1.0, 1.0, 0.0, 1.0};
GLfloat light2Pos[4] = {0.0, 1.0, 0.0, 1.0};

int wantNormalize = 0; /* Speed vector normalization flag */

/*
 * newSpeed
 *
 * Randomize a new speed vector.
 *
 */

void newSpeed(float dest[3])
{
    float x;
    float y;
    float z;
    float len;

    x = (2.0 * ((GLfloat)rand()) / ((GLfloat)RAND_MAX)) - 1.0;
    y = (2.0 * ((GLfloat)rand()) / ((GLfloat)RAND_MAX)) - 1.0;
    z = (2.0 * ((GLfloat)rand()) / ((GLfloat)RAND_MAX)) - 1.0;

    /*
   * Normalizing the speed vectors gives a "fireball" effect
   *
   */

    if (wantNormalize)
    {
        len = sqrt(x * x + y * y + z * z);

        if (len)
        {
            x = x / len;
            y = y / len;
            z = z / len;
        }
    }

    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
}

/*
 * newExplosion
 *
 * Create a new explosion.
 *
 */

void newExplosion(void)
{
    int i;

    for (i = 0; i < NUM_PARTICLES; i++)
    {
        particles[i].position[0] = 0.0;
        particles[i].position[1] = 0.0;
        particles[i].position[2] = 0.0;

        particles[i].color[0] = 1.0;
        particles[i].color[1] = 1.0;
        particles[i].color[2] = 0.5;

        newSpeed(particles[i].speed);
    }

    for (i = 0; i < NUM_DEBRIS; i++)
    {
        debris[i].position[0] = 0.0;
        debris[i].position[1] = 0.0;
        debris[i].position[2] = 0.0;

        debris[i].orientation[0] = 0.0;
        debris[i].orientation[1] = 0.0;
        debris[i].orientation[2] = 0.0;

        debris[i].color[0] = 0.7;
        debris[i].color[1] = 0.7;
        debris[i].color[2] = 0.7;

        debris[i].scale[0] = (2.0 *
                              ((GLfloat)rand()) / ((GLfloat)RAND_MAX)) -
                             1.0;
        debris[i].scale[1] = (2.0 *
                              ((GLfloat)rand()) / ((GLfloat)RAND_MAX)) -
                             1.0;
        debris[i].scale[2] = (2.0 *
                              ((GLfloat)rand()) / ((GLfloat)RAND_MAX)) -
                             1.0;

        newSpeed(debris[i].speed);
        newSpeed(debris[i].orientationSpeed);
    }

    fuel = 100;
}

void display(void)
{
    int i;
    float look_at_r = look_at * PI / 90.;
    glClearColor(0., 0., 0., 0.);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glLineWidth(2.0f); //width of line in text
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-8.0, 7.0, -20.0);
    glScalef(0.01f, 0.009f, 0.01f);
    glColor3f(1.0, 0.0, 0.0);
    draw_string_stroke(GLUT_STROKE_ROMAN, "Press Space to Explode"); //stroke text
    glFlush();
    glPopMatrix();

    glLineWidth(2.0f); //width of line in text
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-10.0, 6.0, -20.0);
    glScalef(0.01f, 0.009f, 0.01f);
    glColor3f(1.0, 1.0, 0.0);
    draw_string_stroke(GLUT_STROKE_ROMAN, "Left Mouse Button for Menu"); //stroke text
    glFlush();
    glPopMatrix();
    //////////////////////////////////////////////////////////
    /* Place the camera */
    glTranslatef(0.0, 0.0, -10.0); //chabge camera lefi scene

    /* If no explosion, draw robot */
    if (fuel == 0)
    {
        glEnable(GL_DEPTH_TEST);
        glTranslatef(0.0, 0.0, -25.0);
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, men_amb_dif);
        glMaterialfv(GL_FRONT, GL_SPECULAR, men_spec);
        glMaterialf(GL_FRONT, GL_SHININESS, men_shine);

        /////////////////////////////////////

        glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
        glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_dir);

        glPushMatrix();
        glTranslatef(/*light1_pos[0], light1_pos[1], light1_pos[2]*/ 0, 10.5, 0);
        glRotatef(-angle, 0., 1., 0.);
        glRotatef(100. * atan2(2.3, 4.) / 3.14162, 0., 0., 1.);
        glRotatef(-90., 1., 0., 0.);
        glTranslatef(0., 0., -1.);

        /* puting & properties of projektor */
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, no_val);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_val);
        glMaterialf(GL_FRONT, GL_SHININESS, 0.);
        glMaterialfv(GL_FRONT, GL_EMISSION, prog_emiss);
        glutSolidCone(.3, .5, 12, 10);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0., 1., 1.);
        glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light0_ambient);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0_ambient);
        glTranslatef(light0_pos[0], light0_pos[1], light0_pos[2]);
        //	glutSolidSphere(1. ,17 ,19);
        glutSolidCone(.3, .5, 12, 10);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_val);
        glPopMatrix();
        glPopMatrix();
        //////////////////////////////
        //	glLoadIdentity ();

        if (up_view)
            gluLookAt(0, 0., 0, 0., -10., 0.,
                      -cos(look_at_r), 0., sin(look_at_r));
        else
            gluLookAt(0. * cos(look_at_r), 0., -10. * sin(look_at_r),
                      0., 0., 0., 0., 1., 0.);

        gluLookAt(eyex, 0., eyez,
                  eyex + cos(azimuth), 0., eyez - sin(azimuth),
                  0., 1., 0.);

        Robot_plan();
        glPopMatrix();
    }
    if (fuel > 0)
    {
        glPushMatrix();

        glLoadIdentity();
        glMultMatrixf(m);

        glBegin(GL_POINTS);
        for (i = 0; i < NUM_PARTICLES; i++)
        {
            glColor3fv(particles[i].color);
            glVertex3fv(particles[i].position);
        }
        glEnd();

        glPopMatrix();

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT2);
        glEnable(GL_DEPTH_TEST);

        glNormal3f(0.0, 0.0, 1.0);

        glLoadIdentity();
        glTranslatef(0.0, 0.5, 5.0);

        glMultMatrixf(m);
        for (i = 0; i < NUM_DEBRIS; i++)
        {
            glColor3fv(debris[i].color);

            glPushMatrix();

            glTranslatef(debris[i].position[0],
                         debris[i].position[1],
                         debris[i].position[2]);

            glRotatef(debris[i].orientation[0], 1.0, 0.0, 0.0);
            glRotatef(debris[i].orientation[1], 0.0, 1.0, 0.0);
            glRotatef(debris[i].orientation[2], 0.0, 0.0, 1.0);

            glScalef(debris[i].scale[0],
                     debris[i].scale[1],
                     debris[i].scale[2]);

            glBegin(GL_TRIANGLES);
            glVertex3f(0.0, 0.25, 0.0);
            glVertex3f(-0.25, 0.0, 0.0);
            glVertex3f(0.25, 0.0, 0.0);
            glEnd();

            glPopMatrix();
        }
    }
    //glDisable(GL_LIGHTING);
    glPopMatrix();
    /////////////////////////////

    glutSwapBuffers();
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{

    float spd_m = SPEED_M, spd_r = SPEED_R;

    ////////////////////Left hend////////////////////////
    if (key == 'J' || key == 'j') //work with menu
    {
        angle1[axis1] += 5.0;
        if (angle1[axis1] > 360.0)
            angle1[axis1] -= 360.0;
    }
    if (key == 'H' || key == 'h')
    {
        angle1[axis1] -= 5.0;
        if (angle1[axis1] < 0.0)
            angle1[axis1] += 360.0;
    }

    if (key == 'L' || key == 'l')
    {
        if (angle1[axis] < 0.0)
            angle1[axis] += 5.0;
    }
    if (key == 'K' || key == 'k')
    {
        angle1[axis] -= 5.0;
        if (angle1[axis] < -135.0)
            angle1[axis] += 5.0;
    }
    //////////////////Right hend/////////////////////////

    if (key == 'L' || key == 'l')
    {
        if (angle1[axis] < 0.0)
            angle1[axis] += 5.0;
    }
    if (key == 'K' || key == 'k')
    {
        angle1[axis] -= 5.0;
        if (angle1[axis] < -135.0)
            angle1[axis] += 5.0;
    }
    if (key == 'J' || key == 'j')
    {
        angle1[axis1] += 5.0;
        if (angle1[axis1] > 360.0)
            angle1[axis1] -= 360.0;
    }
    if (key == 'H' || key == 'h')
    {
        angle1[axis1] -= 5.0;
        if (angle1[axis1] < 0.0)
            angle1[axis1] += 360.0;
    }

    /////////////////[ Left leg ]////////////////////////////////

    if (key == 'W' || key == 'w')
    {
        if (angle1[axis2] < 25.0)
            angle1[axis2] += 5.0;
    }
    if (key == 'E' || key == 'e')
    {
        angle1[axis2] -= 5.0;
        if (angle1[axis2] < -125.0)
            angle1[axis2] += 5.0;
    }

    if (key == 'R' || key == 'r')
    {
        angle1[axis3] -= 5.0;
        if (angle1[axis3] < -20.0)
            angle1[axis3] += 5.0;
    }
    if (key == 't' || key == 't')
    {
        if (angle1[axis3] < 90.0)
            angle1[axis3] += 5.0;
    }

    /////////////////[ Right leg ]////////////////////////////////
    if (key == 'P' || key == 'p')
    {
        if (angle1[axis4] < 25.0)
            angle1[axis4] += 5.0;
    }
    if (key == 'O' || key == 'o')
    {
        angle1[axis4] -= 5.0;
        if (angle1[axis4] < -125.0)
            angle1[axis4] += 5.0;
    }

    if (key == 'I' || key == 'i')
    {
        angle1[axis5] -= 5.0;
        if (angle1[axis5] < -20.0)
            angle1[axis5] += 5.0;
    }
    if (key == 'U' || key == 'u')
    {
        if (angle1[axis5] < 90.0)
            angle1[axis5] += 5.0;
    }

    if (key == ' ')
        newExplosion();
    if (key == 27)
        exit(0);

    /////////////////////////////////////////////////
    if (key == 'A' || key == 'a')
    {

        if (light0_pos[0] > -7)
            light0_pos[0] -= 0.3;
    }
    if (key == 'D' || key == 'd')
    {
        if (light0_pos[0] < 7)
            light0_pos[0] += 0.3;
    }
    if (key == 'S' || key == 's')
    {
        if (light0_pos[2] < 40)
            light0_pos[2] += 0.3;
    }
    if (key == 'X' || key == 'x')
    {
        if (light0_pos[2] > 0)
            light0_pos[2] -= 0.3;
    }
    ////////////////////////////////////
    glutPostRedisplay();
    display();
}

void arrows(int key, int x, int y)
{
    float spd_m = SPEED_M, spd_r = SPEED_R;
    if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
    {
        spd_m *= .1;
        spd_r *= .1;
    }
    if (key == GLUT_KEY_UP)
    {
        eyex += spd_m * cos(azimuth);
        eyez -= spd_m * sin(azimuth);
    }
    if (key == GLUT_KEY_DOWN)
    {
        eyex -= spd_m * cos(azimuth);
        eyez += spd_m * sin(azimuth);
    }

    if (key == GLUT_KEY_LEFT)
        azimuth += spd_r;
    if (key == GLUT_KEY_RIGHT)
        azimuth -= spd_r;
    if (azimuth > 2 * PI)
        azimuth -= 2 * PI;
    if (azimuth < 0.)
        azimuth += 2 * PI;

    if (key == GLUT_KEY_F1)
        up_view = 1 - up_view;
    glutPostRedisplay();
}

/*
 * idle
 *
 * Update animation variables.
 *
 */

void idle(void)
{
    int i;
    //////////////////////////////////////////////
    float angle_r;

    rotate[10] += 20;

    if (rotate[10] > 180)
    {
        rotate[10] *= -1;
    }

    angle += 10.;
    if (angle < 0.)
        angle += 360.;
    if (angle > 360.)
        angle -= 360.;
    angle_r = angle * 3.1415926 / 180.;
    light1_dir[0] = 2.3 * cos(angle_r);
    light1_dir[2] = 2.3 * sin(angle_r);

    if (rotate[11] > 5)
        dir_of_nose = -1;
    if (rotate[11] < -5)
        dir_of_nose = 1;
    rotate[11] += 5 * dir_of_nose;

    ////////////////////////
    if (fuel > 0)
    {
        for (i = 0; i < NUM_PARTICLES; i++)
        {
            particles[i].position[0] += particles[i].speed[0] * 0.2;
            particles[i].position[1] += particles[i].speed[1] * 0.2;
            particles[i].position[2] += particles[i].speed[2] * 0.2;

            particles[i].color[0] -= 1.0 / 500.0;
            if (particles[i].color[0] < 0.0)
            {
                particles[i].color[0] = 0.0;
            }

            particles[i].color[1] -= 1.0 / 100.0;
            if (particles[i].color[1] < 0.0)
            {
                particles[i].color[1] = 0.0;
            }

            particles[i].color[2] -= 1.0 / 50.0;
            if (particles[i].color[2] < 0.0)
            {
                particles[i].color[2] = 0.0;
            }
        }

        for (i = 0; i < NUM_DEBRIS; i++)
        {
            debris[i].position[0] += debris[i].speed[0] * 0.1;
            debris[i].position[1] += debris[i].speed[1] * 0.1;
            debris[i].position[2] += debris[i].speed[2] * 0.1;

            debris[i].orientation[0] += debris[i].orientationSpeed[0] * 10;
            debris[i].orientation[1] += debris[i].orientationSpeed[1] * 10;
            debris[i].orientation[2] += debris[i].orientationSpeed[2] * 10;
        }

        --fuel;
    }

    angle += 0.3; /* Always continue to rotate the camera */

    glutPostRedisplay();
}

/*
 * reshape
 *
 * Window reshape callback.
 *
 */

void reshape(int w, int h)
{
    glViewport(0.0, 0.0, (GLfloat)w, (GLfloat)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
    //**************************************************
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutCreateWindow("Explode a Robot-Verter");
    glutFullScreen();
    myinit();
    glutDisplayFunc(display);
    galil = gluNewQuadric();
    gluQuadricDrawStyle(galil, GLU_FILL);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrows);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);

    c_menu = glutCreateMenu(color_menu);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);

    properties_menu = glutCreateMenu(menu);

    srand(time(NULL));
    // Menu
    glutAddMenuEntry("left hend:(H,J)", 1);
    glutAddMenuEntry("left down hend:(L,K)", 2);
    glutAddMenuEntry("right down hend:(K,L)", 3);
    glutAddMenuEntry("right hend:(H,J)", 4);
    glutAddMenuEntry("left leg :(W,E)", 5);
    glutAddMenuEntry("left down leg :(R,T)", 6);
    glutAddMenuEntry("right leg :(O,P)", 7);
    glutAddMenuEntry("right down leg :(U,I)", 8);
    glutAddMenuEntry("quit           ", 9);
    //glutAttachMenu(GLUT_LEFT_BUTTON);

    glutCreateMenu(general_menu);
    glutAddSubMenu("Rotate Objects", properties_menu);
    glutAddSubMenu("Change colors of project", c_menu);

    glutAttachMenu(GLUT_LEFT_BUTTON);

    //****************************************************
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glutMainLoop();

    return 0;
}
