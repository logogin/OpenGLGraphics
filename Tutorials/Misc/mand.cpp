/***************************************************************************************/
//
// THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.
//
/***************************************************************************************/

#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <alloc.h>
 
int MX, MY;
 
int MC; /* max color */
 
void init( void )
{
  int gd = 0, gm = VGALO;
  initgraph( &gd, &gm,"D:/BORLANDC/BGI");
}
 
void initPalette( void )
{ int i;
 
   for( i = 0; i < 32; i++ )
     setrgbpalette( i, i*8,
                       0,
                       252-i*8 );
 
   for( i = 32; i < 64; i++ )
     setrgbpalette( i, 252 - ( i - 32 ) * 8,
                       ( i - 32 ) * 8,
                       0 );
   setrgbpalette( 20, 177, 0, 144 );
   setrgbpalette(  0, 15, 15, 15 );
 
}
 
void scrollPalette( void )
{ int i;
  char rgbpal[ 256 ][3];
 
   for( i = 0; i < 32; i++ )
     rgbpal[ i ][ 0 ] = i*8 ,
     rgbpal[ i ][ 1 ] =  0 ,
     rgbpal[ i ][ 2 ] =  252-i*8 ;
 
   for( i = 32; i < 64; i++ )
     rgbpal[ i ][ 0 ] = 252 - ( i - 32 ) * 8,
     rgbpal[ i ][ 1 ] = ( i - 32 ) * 8,
     rgbpal[ i ][ 2 ] = 0 ;
 
   rgbpal[ 20 ][ 0 ] = 177,
   rgbpal[ 20 ][ 1 ] =  0,
   rgbpal[ 20 ][ 2 ] = 144 ;
 
   rgbpal[  0 ][ 0 ] = 15,
   rgbpal[ 20 ][ 1 ] = 15,
   rgbpal[ 20 ][ 2 ] = 15 ;
 
   while( ! kbhit())
     { char tmpr = rgbpal[0][0],
            tmpg = rgbpal[0][1],
            tmpb = rgbpal[0][2];
 
       for( i = 0 ; i < 64; i++ )
         setrgbpalette( i, rgbpal[i][0], rgbpal[ i ][ 2 ], rgbpal[ i ][ 2 ]);
 
       for( i = 0; i < 63; i++ )
         rgbpal[ i ][ 0 ] = rgbpal[ i+1 ][ 0 ],
         rgbpal[ i ][ 1 ] = rgbpal[ i+1 ][ 1 ],
         rgbpal[ i ][ 2 ] = rgbpal[ i+1 ][ 2 ];
 
         rgbpal[ 63 ][ 0 ] = tmpr,
         rgbpal[ 63 ][ 1 ] = tmpg,
         rgbpal[ 63 ][ 2 ] = tmpb;
    }
 
}
 
void saveScreen( void )
{ int i;
 
#define N 4
  unsigned size = imagesize( 0, 0, MX, MY / N );
  char far *p, *nm, nnm[ 80 ];
  FILE *f;
 
  nm = ( char * )malloc( 80 );
  tmpnam( nm );
  p = ( char * )malloc( size );
 
  if(( f = fopen( nm, "wb" )) == NULL )
    printf( "Unable to open file\n" ),
    exit( -2 );
 
  for( i = 0; i < N; i ++)
    {
      getimage( 0, i * MY / N + 1 , MX, ( i + 1 ) * MY / N, p );
      fwrite(( void * )p, sizeof( char ), size, f );
    }
 
  fclose( f );
 
  free(( void * )p );
 
  closegraph();
  printf( "Enter new name for saved screen:" );
  cscanf( "%79s", nnm );
 
  if( rename( nm, nnm ) == -1 )
    { printf( "\n\nRename failed: " );
      printf( "%s", strerror( errno ));
    }
  else
    puts( "\n\nRename successful " );
 
  puts( "ESC to continue" );
  while( getch() != '\x1b' )
   ;
  init();
 
}
 
void restoreScreen( void )
{ int i;
  unsigned size = imagesize( 0, 0, MX, MY / N );
  char *p, nm[80];
  FILE *f;
 
  closegraph();
  printf( "Enter name for saved screen:" );
  cscanf( "%79s", nm );
 
  if(( f = fopen( nm, "rb" )) == NULL )
    printf( "Unable to open file\n" ),
    exit( -2 );
 
  p = ( char * )malloc( size );
 
  init();
  for( i = 0; i < N; i++ )
    {
      fread( p, sizeof( char ), size, f );
      putimage( 0, i * MY / 4 + 1 , p, COPY_PUT );
    }
 
  fclose( f );
 
  initPalette();
  getch();
  free( p );
 
#undef N
}
int min (int a,int b)
{
 if (a>=b) return b;
 else return a;
}
void mandel( int nx, int ny,                        /* screen size */
	     long double xmin, long double xmax,    /* min and max on x axis */
	     long double ymin, long double ymax,    /* min and max on y axis */
	     unsigned maxiter
	   )
{ short ix, iy;
  unsigned iter;
  long double cx, cy;
  long double x, y, x2, y2, temp;
  char s[80];
 
  sprintf( s, "%8.7Lg L=%8.7Lg %8.7Lg L=%8.7Lg N <%d",
               xmin, xmax - xmin,
               ymin, ymax - ymin,
               maxiter
         );
  setcolor( MC );
  outtextxy( 100, ny - 10, s );
 
  for( iy = 0; iy < ny - 12; iy ++ )
    { if( kbhit())  return;
      cy = ymin + iy * ( ymax - ymin ) / ( ny - 1 );
 
      setfillstyle( SOLID_FILL, MC );
      bar( 1, ny - 10, 70, ny );
      setcolor( 0 );
      sprintf( s, "%8.7Lg", cy );
      outtextxy( 1, ny - 8, s );
 
      for( ix = 0; ix < nx; ix ++ )
	{ cx = xmin + ix * ( xmax - xmin ) / ( nx - 1 );
	  x = y = x2 = y2 = 0.0;
	  iter = 0;
	  while( iter < maxiter && ( x2 + y2 ) < 4.0  /*10000.0*/  )
	    { temp = x2 - y2 + cx;
	      y = 2 * x * y + cy;
	      x = temp;
	      x2 = x * x;
	      y2 = y * y;
	      iter++;
	    }
	  putpixel( ix, iy, iter );
 
	}
    }
}
 
void back( void )
{ int i, j, k = 0;
  for( j = 6; j < MY-16; j += MY / 16 )
    for( i = 8; i < MX-16; i += MX / 16 )
      setfillstyle( SOLID_FILL, k++ ),
      bar( i, j, i - 3 + MX / 16 , j - 3 + MY / 16 );
}
 
void main( void )
{
  int r, sizex, sizey, posx, posy;
  long double xm, xM, ym, yM, sizexr, sizeyr;
  char s[ 80 ];
 
  init();
 
  MX = getmaxx(),
  MY = getmaxy(),
  MC = getmaxcolor(),
  setcolor( MC ),
  rectangle( 0, 0, MX, MY );
  setwritemode( 1 );   /* xor */
 
  back();
  initPalette();
 
  xm = -2.0; xM = 0.5;
  ym = -1.25; yM = 1.25;
 
  posx = MX / 2;   posy = MY / 2;
  sizex = ( int )( sizexr = MX / 10 );
  sizey = ( int )( sizeyr = MY / 10 );
  setcolor( MC );
  rectangle( posx - sizex, posy - sizey, posx + sizex, posy + sizey );
  setwritemode( 1 );  
 
  do
    {
	  switch( r = getch())
	    { case '4' : rectangle( posx - sizex, posy - sizey, posx + sizex, posy + sizey );
			 posx -= 5;
			 rectangle( posx - sizex, posy - sizey, posx + sizex, posy + sizey );
			 break;
	      case '6' : rectangle( posx - sizex, posy - sizey, posx + sizex, posy + sizey );
			 posx += 5;
			 rectangle( posx - sizex, posy - sizey, posx + sizex, posy + sizey );
			 break;
	      case '8' : rectangle( posx - sizex, posy - sizey, posx + sizex, posy + sizey );
			 posy -= 5;
			 rectangle( posx - sizex, posy - sizey, posx + sizex, posy + sizey );
			 break;
	      case '2' : rectangle( posx - sizex, posy - sizey, posx + sizex, posy + sizey );
			 posy += 5;
			 rectangle( posx - sizex, posy - sizey, posx + sizex, posy + sizey );
			 break;
	      case '+' : rectangle( posx - sizex, posy - sizey, posx + sizex, posy + sizey );
                         sizex = ( int )( sizexr *= 1.1 );
                         sizey = ( int )( sizeyr *= 1.1 );
			 rectangle( posx - sizex, posy - sizey, posx + sizex, posy + sizey );
			 break;
	      case '-' : rectangle( posx - sizex, posy - sizey, posx + sizex, posy + sizey );
                         sizex = ( int )( sizexr *= 0.909 );
                         sizey = ( int )( sizeyr *= 0.909 );
			 rectangle( posx - sizex, posy - sizey, posx + sizex, posy + sizey );
			 break;
	      case 13  : rectangle( posx - sizex, posy - sizey, posx + sizex, posy + sizey );
                         { long double tmp = xm;
			   xm = xm  + ( posx - sizex ) * ( xM - xm ) / ( MX );
			   xM = tmp + ( posx + sizex ) * ( xM - tmp) / ( MX);
			   tmp = ym;
			   ym = ym  + ( posy - sizey ) * ( yM - ym ) / ( MY );
			   yM = tmp + ( posy + sizey ) * ( yM - tmp) / ( MY );
                         }
			 cleardevice();
                         while( kbhit()) getch();
                         setwritemode( 0 );   /* OR */
			 mandel( MX, MY, xm, xM,
                                         ym, yM,
                                 min(
                                 ( unsigned )( 64.0 * ( 1.0 + fabs( log( fabs( xM - xm ))))),
                                      250
                                    )
                               );
                         while( kbhit()) getch(); /* !!! */
                         setwritemode( 1 );   /* XOR */
			 posx  = MX / 2;  posy  = MY / 2;
                         sizex = ( int )( sizexr = MX / 10 );
                         sizey = ( int )( sizeyr = MY / 10 );
                         setcolor( MC );
                         rectangle( posx - sizex, posy - sizey, posx + sizex, posy + sizey );
                         break;
 
              case 'p' : scrollPalette();
                         break;
              case 's' : saveScreen();
                         setwritemode( 1 );
                         break;
 
              case 'r' : restoreScreen();
                         setwritemode( 1 );
                         continue;
 
	      default  : rectangle( posx - sizex, posy - sizey, posx + sizex, posy + sizey );
			 break;
	    }
 
 
	  setfillstyle( SOLID_FILL, MC );
	  bar( 0, 0, 400, 12 );
	  setcolor( 0 );
	  sprintf( s, "%8.7Lg %8.7Lg %8.7Lg %8.7Lg ",
					xm + ( posx - sizex ) * ( xM - xm ) / ( MX ),
					xm + ( posx + sizex ) * ( xM - xm ) / ( MX ),
					ym + ( posy - sizey ) * ( yM - ym ) / ( MY ),
					ym + ( posy + sizey ) * ( yM - ym ) / ( MY )
		 );
	  outtextxy( 1, 1, s );
	  setcolor( MC );
    }
  while( r != '\x1b' );
 
  closegraph();
 
  puts( "**** That's all folks ! ****" );
 
  getch();
}
 
 
 
 
