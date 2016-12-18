/*
 *  Program 4.
 *  Use glBindTexture to manage multiple textures.
 *
 *
 */

#include <windows.h>
#include <glut.h>
#include <stdio.h>
#include <stdlib.h>


#define MAX_NO_TEXTURES 2

#define EARTH_TEXTURE   0
#define CLOUD_TEXTURE   1

// Storage for texture names
GLuint  texture_id[MAX_NO_TEXTURES];

// Angles here
float angle, angle2, cloud_rot;

int moving, startx, starty;

GLfloat  ambient_light[] = {0.2, 0.2, 0.2, 1.0};
GLfloat   source_light[] = {0.9, 0.8, 0.8, 1.0};
GLfloat      light_pos[] = {7.0, 0.0, 3.0, 1.0};

/* //////////////////////////////////////////////////////////////////////////
   'load_texture' takes the file name, size and OpenGL texture format of an
   image.  This is used inside the function to load the image and set the
   mipmap level, texture parameters and environment settings.
   As it does this inside the function, it doesn't return anything.


   glGenTextures (1, texture_id);
   glBindTexture(GL_TEXTURE_2D, texture_id[0]);
   load_texture("earth_r.raw", 640, 320, 3, GL_RGB, GL_NEAREST);

   Notice how you don't need to repeat all those texture parameters?
*/ //////////////////////////////////////////////////////////////////////////
void load_texture ( char *file_name, int width, int height, int depth,
                    GLenum colour_type, GLenum filter_type )
{
   GLubyte *raw_bitmap ;
   FILE *file;

   if (( file = fopen(file_name, "rb"))==NULL )
   {
      printf ( "File Not Found : %s\n", file_name );
      exit   ( 1 );
   }

   raw_bitmap = (GLubyte *)malloc(width * height * depth * (sizeof(GLubyte)));

   if ( raw_bitmap == NULL )
   {
      printf ( "Cannot allocate memory for texture\n" );
      fclose ( file );
      exit   ( 1 );
   }

   fread  ( raw_bitmap , width * height * depth, 1 , file );
   fclose ( file);

   //  Set Filtering type
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_type );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_type );

   //  Set Texture Evironment
   glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

   //  Build Mipmaps
   gluBuild2DMipmaps ( GL_TEXTURE_2D, colour_type, width, height, colour_type,
                       GL_UNSIGNED_BYTE, raw_bitmap );

   //  Free up the array
   free ( raw_bitmap );
}

void init ( void )
{
   // Set up simple lighting model
   glEnable ( GL_LIGHTING );
   glLightModelfv ( GL_LIGHT_MODEL_AMBIENT, ambient_light );
   glLightfv ( GL_LIGHT0, GL_DIFFUSE,  source_light );
   glLightfv ( GL_LIGHT0, GL_POSITION, light_pos    );
   glEnable  ( GL_LIGHT0 );

   // Enable material properties for lighting
   glEnable ( GL_COLOR_MATERIAL );
   glColorMaterial ( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );

   glEnable ( GL_TEXTURE_2D );
   glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
   glGenTextures ( 2, texture_id );

   glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
   load_texture  ( "earth_r.raw", 640, 320, 3, GL_RGB, GL_NEAREST );

   glBindTexture ( GL_TEXTURE_2D, texture_id[1]);
   load_texture  ( "cl_lum.raw", 640, 320, 1, GL_LUMINANCE, GL_NEAREST );

   // Leave depth test off for speed, theres no 'in and out' movement anyhoo :)
   // glEnable (GL_DEPTH_TEST);

   glEnable ( GL_CULL_FACE );
   glEnable ( GL_BLEND     );
   glBlendFunc ( GL_ONE, GL_ONE );

   glClearColor ( 0.0, 0.0, 0.0, 0.0 );
}

void draw_sphere ( int tex_id )
{
   glPushMatrix  ( );
   glRotatef     ( 90.0, 1.0, 0.0, 0.0 );
   glColor4f     ( 1.0, 1.0, 1.0, 1.0  );
   glBindTexture ( GL_TEXTURE_2D, texture_id[tex_id] );
   GLUquadricObj*  q = gluNewQuadric ( );
   gluQuadricDrawStyle ( q, GLU_FILL   );
   gluQuadricNormals   ( q, GLU_SMOOTH );
   gluQuadricTexture   ( q, GL_TRUE    );
   gluSphere ( q, 1.0, 20, 20 );
   gluDeleteQuadric ( q );
   glPopMatrix ( );
}


void display ( void )
{
   //glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClear   ( GL_COLOR_BUFFER_BIT );
   glLightfv ( GL_LIGHT0, GL_POSITION, light_pos );
   glPushMatrix ( );
   glTranslatef ( 0.0, 0.0, -4.0 );
   glRotatef ( angle2, 1.0, 0.0, 0.0 );
   glRotatef ( angle, 0.0, 1.0, 0.0  );
   draw_sphere ( EARTH_TEXTURE );

   glRotatef   ( cloud_rot, 0.0, 1.0, 0.0 );
   draw_sphere ( CLOUD_TEXTURE );
   glPopMatrix ( );

   glutSwapBuffers ( );
}

void reshape ( int w, int h )
{
   glViewport ( 0, 0, (GLint) w, (GLint) h );
   glMatrixMode ( GL_PROJECTION );
   glLoadIdentity ( );
   if ( h==0 )
      gluPerspective( 45, (GLdouble)w, 1.0, 2000.0 );
   else
      gluPerspective( 45, (GLdouble)w/ (GLdouble)h,1.0, 2000.0 );

   glMatrixMode ( GL_MODELVIEW );
   glLoadIdentity ( );
}

void mouse ( int button, int state, int x, int y )
{
   if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
   {
      moving = 1;
      startx = x;
      starty = y;
   }
   if ( button == GLUT_LEFT_BUTTON && state == GLUT_UP )
      moving = 0;
}

void motion ( int x, int y )
{
   if ( moving )
   {
      angle = angle + (x - startx);
      angle2 = angle2 + (y - starty);
      startx = x;
      starty = y;
      glutPostRedisplay ( );
   }
}

void idle_func ( void )
{
   angle = angle + 0.1;
   if ( angle >= 360 )
      angle = 0;

   // Make the clouds go a bit faster than the earth
   cloud_rot = cloud_rot + 0.18;
   if ( cloud_rot >= 360 )
      cloud_rot = 0;

   glutPostRedisplay ( );
}

#pragma argsused
void keyboard ( unsigned char key, int x, int y )
{
   int i;

   switch (key) {
      case 27:  /*  Escape key  */
         exit(0);
         break;
      case 'l':
         for ( i = 0; i <= MAX_NO_TEXTURES; i++ )
         {
            glBindTexture ( GL_TEXTURE_2D, texture_id[i] );
            glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
            glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
         }
         break;
      case 'n':
         for ( i = 0; i <= MAX_NO_TEXTURES; i++ )
         {
            glBindTexture ( GL_TEXTURE_2D, texture_id[i] );
            glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
            glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
         }
        break;
      case 'f':
         glutFullScreen();
         break;
      case 'w':
         glutReshapeWindow(500,500);
         break;
      default:
         break;
   }
}

/*  Main Loop
 *  Open window with initial window size, title bar,
 *  RGBA display mode, and handle input events.
 */
int main ( int argc, char** argv)
{
   glutInit ( &argc, argv );
   glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE );
   glutInitWindowSize  ( 250, 250);
   glutCreateWindow ( argv[0] );

   init();

   glutReshapeFunc  ( reshape   );
   glutMouseFunc    ( mouse     );
   glutMotionFunc   ( motion    );
   glutKeyboardFunc ( keyboard  );
   glutDisplayFunc  ( display   );
   glutIdleFunc     ( idle_func );
   glutMainLoop ( );

   return 0;
}
