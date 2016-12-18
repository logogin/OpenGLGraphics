#include <GL\glut.h>
#include <stdlib.h>
#include <math.h>

/* There is keys to move the sun: 
   w -> up  
   x -> down 
   a -> left
   d -> right
   
   To rotate all objects:
   l -> left
   r -> right
   
   Walking  thrue the scene:
   ->  left
   <-  right 
   arrows up -  up
   arrows down - down 
                      
   Attention !!! the nouse  move  */
//____________________________________

#define base_radius 1
#define head_radius 0.6
#define eyes_radius 0.1
#define arm_length 1.5
#define arm_width 0.3
#define leg_length 2.7
#define leg_width 0.4
#define lokot_length 0.5
#define lokot_width 0.3
#define nouse_radius 0.2
#define nouse_length 0.7
#define PI 3.1415

void base();
void head();
void Right_eye();
void Left_eye();
void Right_arm();
void Left_arm();
void Right_lokot();
void Left_lokot();
void RightLeg();
void LeftLeg();
void nose();
void heare();
void house();
void Gag();
void reshape(int w, int h);
void IncreseLight();
void DecreseLight();
void idle();
void menu(int id);
void keyboard(unsigned char ch, int x, int y);
void arrows(int key, int x, int y);
void mouse(int btn, int state, int x, int y);
void color_menu(int id);
void general_menu(int id);
void Inc_Dec_menu(int id);
void Prop_Of_Word_menu(int id);

/* globals */

int W = 500;
int H = 500;

GLfloat men_amb_dif[] = {1., 1., 1., 1.};
GLfloat men_spec[] = {.4, 0.4, 0.4, 1.};
GLfloat men_shine = 20;

GLfloat house_amb_dif[] = {.3, .3, .3, 1.};
GLfloat house_spec[] = {1., 1., 1., 1.};
GLfloat house_shine = 70;

GLfloat light0_pos[] = {0., 6., 1., 1.};
GLfloat light0_ambient[] = {0.5, 0.5, 0.5, 1.};
GLfloat light0_diffuse[] = {0.5, 0.5, 0.5, 1.};
GLfloat light0_spec[] = {.5, .5, .5, 1.};

GLfloat light1_pos[] = {0., 4., -1., 1.};
GLfloat light1_dir[] = {0., -4., 0., 0.};
GLfloat light1_ambient[] = {.4, .4, .2, 1.};
GLfloat light1_diffuse[] = {.5, .5, 0, 1.};
GLfloat light1_spec[] = {.1, .2, .1, 1.};
GLfloat light1_cutoff = 20.;
GLfloat light1_exp = 9.;
GLfloat global_amb[] = {0.2, 0.2, 0, 1.};

GLfloat no_val[] = {0., 0., 0., 1.};
GLfloat prog_emiss[] = {.2, .8, .2, 1.};
GLfloat sun_emiss[] = {.1, .2, .3, 1.};

GLfloat rotate[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
GLint index_of_rotate = 0;
GLfloat up_view = 0;
GLfloat angle = 0;
GLfloat eyex = 0;
GLfloat eyez = 10;
GLfloat dir_of_nose = 1;
GLfloat azimuth = PI / 2;
GLfloat SPEED_M = 10 * PI / 180;
GLfloat SPEED_R = 10 * PI / 180;

int mazav = 1;
int kivun = 1;

int inc_dec_menu;
int c_menu;
int properties_menu;
int prop_of_world;

/*****************************************************************/
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (up_view)
        gluLookAt(eyex, 7., eyez, 0., 0., 0.,
                  0, 1, 0);
    //							-cos(azimuth), 0.,-sin(azimuth) );
    else
        gluLookAt(eyex, 0.1, eyez,
                  eyex + cos(azimuth), 0., eyez - sin(azimuth), 0., 1., 0.);

    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_dir);

    glPushMatrix();
    glTranslatef(light1_pos[0], light1_pos[1], light1_pos[2]);
    glRotatef(-angle, 0., 1., 0.);
    glRotatef(100. * atan2(2.3, 4.) / 3.1416, 0., 0., 1.);
    glRotatef(-90., 1., 0., 0.);
    glTranslatef(0., 0., -1.);

    /* puting & properties of projektor */
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, no_val);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_val);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.);
    glMaterialfv(GL_FRONT, GL_EMISSION, prog_emiss);
    glutSolidCone(.3, 1, 12, 10);
    glPopMatrix();

    /* puting the sun */
    glPushMatrix();
    glColor3f(1., 1., 0.);
    glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light0_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_ambient);
    glTranslatef(light0_pos[0], light0_pos[1], light0_pos[2]);
    glutSolidSphere(1., 17, 19);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_val);
    glPopMatrix();

    /* building men */
    glRotatef(rotate[9], 0, 1, 0);
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, men_amb_dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, men_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, men_shine);

    glColor3f(.6, .6, .8);
    glRotatef(rotate[0], 0, 1, 0);
    base();

    glPushMatrix();
    glColor3f(.6, .6, .8);
    glRotatef(rotate[1], 0, 1, 0);
    head();
    heare();
    glColor3f(1, 0.3, 0.2);
    glPushMatrix();
    glRotatef(rotate[11], 0, 1, 0);
    nose();
    glPopMatrix();
    glColor3f(0, 0, 0);
    Right_eye();
    Left_eye();
    glPopMatrix();

    glColor3f(.6, .6, .8);
    glPushMatrix();
    glTranslatef(base_radius - 0.3, 0.4, 0);
    glRotatef(-40, 0, 0, 1);
    glRotatef(rotate[2], 0, 0, 1);
    Left_arm();

    glColor3f(1, 0, .2);
    glTranslatef(arm_length, 0, 0);
    glRotatef(rotate[4], 0, 0, 1);
    Left_lokot();
    glPopMatrix();

    glColor3f(.6, .6, .8);
    glPushMatrix();
    glTranslatef(-base_radius + 0.3, 0.4, 0);
    glRotatef(40, 0, 0, 1);
    glRotatef(rotate[3], 0, 0, 1);
    Right_arm();

    glColor3f(1, 0, .2);
    glTranslatef(-arm_length, 0, 0);
    glRotatef(rotate[5], 0, 0, 1);
    Right_lokot();
    glPopMatrix();

    glPushMatrix();
    glColor3f(.6, .6, .8);
    glRotatef(rotate[6], 1, 0, 0);
    glTranslatef(0., -base_radius, 0);
    RightLeg();
    glPopMatrix();

    glPushMatrix();
    glRotatef(rotate[7], 1, 0, 0);
    glTranslatef(0., -base_radius, 0);
    LeftLeg();
    glPopMatrix();

    glPopMatrix();

    /* building house */
    glPushMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, house_amb_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, house_spec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, house_shine);

    glTranslatef(6., 1., -5);
    glRotatef(rotate[8], 0, 1, 0);
    house();
    glTranslatef(0., 1., 0.);
    Gag();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

/****************************************************************/

void myinit()
{
    glClearColor(0.12, 0.12, 0.12, 1.0);
    glColor3f(1, 0.6, 0.8);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_spec);

    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_spec);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_dir);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, light1_exp);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, light1_cutoff);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_amb);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    glEnable(GL_LIGHTING);
}
/****************************************************************/
void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Kleopa mudak");
    myinit();
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrows);

    properties_menu = glutCreateMenu(menu);
    glutAddMenuEntry("Body", 1);
    glutAddMenuEntry("Head", 2);
    glutAddMenuEntry("Left Arm", 3);
    glutAddMenuEntry("Right Arm", 4);
    glutAddMenuEntry("Left Lokot", 5);
    glutAddMenuEntry("Right Lokot", 6);
    glutAddMenuEntry("Left Leg", 7);
    glutAddMenuEntry("Right Leg", 8);
    glutAddMenuEntry("House", 9);
    glutAddMenuEntry("Whole World", 10);

    inc_dec_menu = glutCreateMenu(Inc_Dec_menu);
    glutAddMenuEntry("Increse The Light of sun", 1);
    glutAddMenuEntry("Decrese The Light of sun", 2);

    prop_of_world = glutCreateMenu(Prop_Of_Word_menu);
    glutAddMenuEntry("Change View", 1);
    glutAddMenuEntry("Perspective/Ortho", 2);
    glutAddMenuEntry("Exit", 3);

    c_menu = glutCreateMenu(color_menu);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);

    glutCreateMenu(general_menu);
    glutAddSubMenu("Rotate Objects", properties_menu);
    glutAddSubMenu("Change colors of project", c_menu);
    glutAddSubMenu("Increase/Decrease Light Of Sun", inc_dec_menu);
    glutAddSubMenu("Change Properties Of World", prop_of_world);

    glutAttachMenu(GLUT_LEFT_BUTTON);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glutMainLoop();
}
/***************************************************************/
void base()
{
    glutSolidSphere(base_radius, 300, 200);
}
/***************************************************************/
void head()
{
    glPushMatrix();
    glTranslatef(0, base_radius + head_radius - 0.05, 0);
    glutSolidSphere(head_radius, 300, 200);
    glPopMatrix();
}
/**************************************************************/
void heare()
{
    glPushMatrix();
    glColor3f(1, .7, 0);
    glTranslatef(0, base_radius + head_radius + head_radius - 0.5, -0.2);
    glutSolidSphere(head_radius + 0.06, 300, 200);
    glPopMatrix();
}
/**************************************************************/
void Right_eye()
{
    glPushMatrix();
    glTranslatef(0, base_radius + head_radius + (0.25 * head_radius), 0);
    glTranslatef(0.3, 0, head_radius - 0.1);
    glutSolidSphere(eyes_radius, 30, 20);
    glPopMatrix();
}
/**************************************************************/
void Left_eye()
{
    glPushMatrix();
    glTranslatef(0, base_radius + head_radius + (0.25 * head_radius), 0);
    glTranslatef(-0.3, 0, head_radius - 0.1);
    glutSolidSphere(eyes_radius, 30, 20);
    glPopMatrix();
}
/**************************************************************/
void nose()
{
    glPushMatrix();
    glTranslatef(0, base_radius + head_radius, 0);
    glTranslatef(0, 0, head_radius - 0.05);
    glutSolidCone(nouse_radius, nouse_length, 7, 11);
    glPopMatrix();
}
/**************************************************************/
void Left_arm()
{
    glPushMatrix();
    glTranslatef(0.5 * arm_length, 0, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(arm_width, arm_length, arm_width);
    glutSolidCube(1.0);
    glPopMatrix();
}
/************************************************************/
void Right_arm()
{
    glPushMatrix();
    glTranslatef(-(0.5 * arm_length), 0, 0);
    glRotatef(-90, 0, 0, 1);
    glScalef(arm_width, arm_length, arm_width);
    glutSolidCube(1.0);
    glPopMatrix();
}
/************************************************************/
void Left_lokot()
{
    glPushMatrix();
    glTranslatef((0.5 * lokot_length), 0, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(lokot_width, lokot_length, lokot_width);
    glutSolidCube(1.0);
    glPopMatrix();
}
/************************************************************/
void Right_lokot()
{
    glPushMatrix();
    glTranslatef(-(0.5 * lokot_length), 0, 0);
    glRotatef(-90, 0, 0, 1);
    glScalef(lokot_width, lokot_length, lokot_width);
    glutSolidCube(1.0);
    glPopMatrix();
}
/************************************************************/
void RightLeg()
{
    glPushMatrix();
    glRotatef(25, 0, 0, 1);
    glTranslatef(0.35 * base_radius, -(0.5 * leg_length), 0);
    glScalef(leg_width, leg_length, leg_width);
    glutSolidCube(1.0);

    glPopMatrix();
}
/************************************************************/
void LeftLeg()
{
    glPushMatrix();
    glRotatef(-25, 0, 0, 1);
    glTranslatef(-(0.35 * base_radius), -(0.5 * leg_length), 0);
    glScalef(leg_width, leg_length, leg_width);
    glutSolidCube(1.0);

    glPopMatrix();
}
/************************************************************/
void house()
{
    glColor3f(0., 0.1, 1.0);
    glPushMatrix();
    glutSolidCube(2);

    glColor3f(0., 0., 0.);
    glutWireCube(2);

    glPushMatrix();

    /* Drawing Entery */
    glTranslatef(-0.2, -0.5, 1);
    glScalef(0.8, 1, 0.001);
    glColor3f(0, 0, 0);
    glutSolidCube(1);

    // Drawing door
    glColor3f(1., 1., 0);
    glTranslatef(0, 0, 1.01);
    glScalef(0.4, 1, 0.001);
    glutSolidCube(1);

    glPopMatrix();

    glPopMatrix();
}
/************************************************************/
void Gag()
{
    glPushMatrix();
    glColor3f(0.8, 0., 0.7);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(1.5, 1., 30, 20.);
    glColor3f(0., 0.5, 0.);
    glPopMatrix();
}
/************************************************************/
void idle()
{
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

    glutPostRedisplay();
}
/************************************************************/
void keyboard(unsigned char ch, int x, int y)
{

    if (ch == 'L' || ch == 'l')
    {
        rotate[index_of_rotate] += 10;
        if (rotate[index_of_rotate] > 360)
            rotate[index_of_rotate] -= 360;
        if (rotate[6] > 125)
            rotate[6] = -125;
    }
    if (ch == 'R' || ch == 'r')
    {
        rotate[index_of_rotate] -= 10;
        if (rotate[index_of_rotate] < 0)
            rotate[index_of_rotate] += 360;
        if (rotate[6] < -25)
            rotate[6] = 25;
    }
    if (ch == 'A' || ch == 'a')
    {

        if (light0_pos[0] > -7)
            light0_pos[0] -= 0.3;
    }
    if (ch == 'D' || ch == 'd')
    {
        if (light0_pos[0] < 7)
            light0_pos[0] += 0.3;
    }
    if (ch == 'W' || ch == 'w')
    {
        if (light0_pos[2] < 40)
            light0_pos[2] += 0.3;
    }
    if (ch == 'X' || ch == 'x')
    {
        if (light0_pos[2] > 0)
            light0_pos[2] -= 0.3;
    }
    glutPostRedisplay();
}
/************************************************************/
void menu(int id)
{
    switch (id)
    {
    case 1:
        index_of_rotate = 0;
        break;
    case 2:
        index_of_rotate = 1;
        break;
    case 3:
        index_of_rotate = 2;
        break;
    case 4:
        index_of_rotate = 3;
        break;
    case 5:
        index_of_rotate = 4;
        break;
    case 6:
        index_of_rotate = 5;
        break;
    case 7:
        index_of_rotate = 6;
        break;
    case 8:
        index_of_rotate = 7;
        break;
    case 9:
        index_of_rotate = 8;
        break;
    case 10:
        index_of_rotate = 9;
        break;
    }
}
/************************************************************/
void Inc_Dec_menu(int id)
{
    switch (id)
    {
    case 1:
        IncreseLight();
        break;
    case 2:
        DecreseLight();
        break;
    }
}
/************************************************************/
void Prop_Of_Word_menu(int id)
{
    switch (id)
    {
    case 1:
        up_view = 1 - up_view;
        break;
    case 2:
        mazav = 1 - mazav;
        reshape(W, H);
        break;
    case 3:
        exit(1);
        break;
    }
}
/************************************************************/
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
        eyex += spd_m * cos(azimuth) + .1;
        eyez -= spd_m * sin(azimuth) + .1;
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
    if (azimuth > 2. * PI)
        azimuth -= 2. * PI;
    if (azimuth < 0.)
        azimuth += 2. * PI;
    if (eyex < -20.)
        eyex = -20.;
    if (eyex > 20.)
        eyex = 20.;
    if (eyez < -10.)
        eyez = -10.;
    if (eyez > 40.)
        eyez = 40.;

    glutPostRedisplay();
}
/************************************************************/
void IncreseLight()
{
    for (int i = 0; i < 3; i++)
        if (light0_ambient[i] < 1)
            light0_ambient[i] += 0.2;
    glutPostRedisplay();
}
/************************************************************/
void DecreseLight()
{
    for (int i = 0; i < 3; i++)
        if (light0_ambient[i] > 0)
            light0_ambient[i] -= 0.2;
    glutPostRedisplay();
}
/****************************************************************/
void reshape(int w, int h)
{
    W = w;
    H = h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (mazav)
        gluPerspective(30., (GLfloat)w / (GLfloat)h, .1, 40.);
    else
        glOrtho(-8., 8., -8., 8., 0., 40.);

    glMatrixMode(GL_MODELVIEW);
}
/****************************************************************/
void color_menu(int id)
{
    light1_ambient[0] = 0;
    light1_ambient[1] = 0;
    light1_ambient[2] = 0;
    switch (id)
    {
    case 1:
        light1_ambient[0] = .8;
        break;
    case 2:
        light1_ambient[1] = .8;
        break;
    case 3:
        light1_ambient[2] = .8;
        break;
    }
}
/*******************************************************************/
void general_menu(int id)
{
}
/*******************************************************************/