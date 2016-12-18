// (C) Pasha Malinnikov, mpa@cci.lg.ua

// Вы можете найти ответ и на свой вопрос. Заходите:
// Here you can find answer on your question too! Welcome:

//							http://www.cci.lg.ua/~mpa
//							~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "Scene.h"

HWND	hWnd;
HDC		hDC;
RECT	rect;
int		sw = 500;
int		sh = 600;
POINT	click;
POINT	p;

bool	Captured = false;


CScene Scene;


// EnableOpenGL ---------------------------------------------------------------

VOID EnableOpenGL( HWND hWnd, HDC * hDC, HGLRC * hRC )
{
	PIXELFORMATDESCRIPTOR pfd;
	int iFormat;

	*hDC = GetDC( hWnd );

	ZeroMemory( &pfd, sizeof( pfd ) );
	pfd.nSize = sizeof( pfd );
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 16;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	iFormat = ChoosePixelFormat( *hDC, &pfd );

	SetPixelFormat( *hDC, iFormat, &pfd );


	//Detecting, if hardware acceleration is available
/*	PIXELFORMATDESCRIPTOR pfd_new;
	DescribePixelFormat (*hDC, iFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd_new);

	int generic_format = pfd_new.dwFlags & PFD_GENERIC_FORMAT;
	int generic_accelerated = pfd_new.dwFlags & PFD_GENERIC_ACCELERATED;

	if (generic_format && ! generic_accelerated)
	{
		// software
		MessageBox(NULL,"software","Detecting hardware acceleration",MB_OK);
	}
	else if (generic_format && generic_accelerated)
	{
		// hardware - MCD
		MessageBox(NULL,"hardware - MCD","Detecting hardware acceleration",MB_OK);
	}
	else if (! generic_format && ! generic_accelerated)
	{
		// hardware - ICD
		MessageBox(NULL,"hardware - ICD","Detecting hardware acceleration",MB_OK);
	}*/

	*hRC = wglCreateContext( *hDC );
	wglMakeCurrent( *hDC, *hRC );
}

// Disable OpenGL -------------------------------------------------------------

VOID DisableOpenGL( HWND hWnd, HDC hDC, HGLRC hRC )
{
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( hRC );
	ReleaseDC( hWnd, hDC );
}
// ----------------------------------------------------------------------------

void FreeTexture( GLuint texture )
{
	glDeleteTextures( 1, &texture );
}

// Window Proc ----------------------------------------------------------------

LRESULT CALLBACK WndProc( HWND hWnd, UINT message,
						  WPARAM wParam, LPARAM lParam )
{

	switch ( message )
	{
		case WM_CREATE:
			GetClientRect(hWnd, &rect);
			sw = rect.right;
			sh = rect.bottom;
			Scene.ResizeViewport(sw, sh);
			return 0;

		case WM_SIZE:
			GetClientRect(hWnd, &rect);
			sw = rect.right;
			sh = rect.bottom;

			if(sw>0 && sh>0)
				Scene.ResizeViewport(sw, sh);
			return 0;/**/

		case WM_CLOSE:
			::ShowWindow (hWnd, SW_HIDE);
			PostQuitMessage( 0 );
			return 0;

		case WM_LBUTTONUP:
			::ShowCursor(true);
			Captured = false;
			return 0;

		case WM_LBUTTONDOWN:
			::ShowCursor(false);
			GetWindowRect(hWnd, &rect);
			click.x = LOWORD(lParam) + rect.left;
			click.y = HIWORD(lParam) + rect.top;
			Captured = true;
			return 0;

		case WM_DESTROY:
			return 0;

		case WM_KEYDOWN:
			switch( wParam )
			{
			case VK_ESCAPE:
				PostMessage(hWnd, WM_CLOSE, 0, 0);
				break;
			}
			return 0;

	default:
	return DefWindowProc( hWnd, 
	message, wParam, lParam );
  }
}



// WinMain --------------------------------------------------------------------

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPSTR lpCmdLine, int iCmdShow )
{
	WNDCLASS wc;
	HGLRC hRC;
	MSG msg;
	bool bQuit = false;

	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Name";
	RegisterClass( &wc );

	hWnd = CreateWindowEx(NULL,
							"Name",
							"Pasha Malinnikov demo [http://www.cci.lg.ua/~mpa]",
							WS_TILEDWINDOW | WS_CLIPSIBLINGS | WS_VISIBLE,
							GetSystemMetrics( SM_CXSCREEN )/4,
							GetSystemMetrics( SM_CYSCREEN )/4,
							GetSystemMetrics( SM_CXSCREEN )/2,
							GetSystemMetrics( SM_CYSCREEN )/2,
							NULL, NULL,
							hInstance,
							NULL );


	//Initialisation
	EnableOpenGL( hWnd, &hDC, &hRC );
	Scene.Init();
/*
	MessageBox(NULL,(char *)glGetString(GL_VENDOR),"Detecting VENDOR",MB_OK);
	MessageBox(NULL,(char *)glGetString(GL_RENDERER),"Detecting RENDERER",MB_OK);
	MessageBox(NULL,(char *)glGetString(GL_VERSION),"Detecting VERSION",MB_OK);
	MessageBox(NULL,(char *)glGetString(GL_EXTENSIONS),"Detecting EXTENSIONS",MB_OK);
*/
	while ( !bQuit )
	{
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
			if ( msg.message == WM_QUIT )
				bQuit = true;
			else 
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		else
		{

			// OpenGL animation
			Scene.Show();

			SwapBuffers( hDC );

		}
	}

	//Shutdown
	Scene.ShutDown();

	DisableOpenGL( hWnd, hDC, hRC );

	::ShowWindow (hWnd, SW_HIDE);
	DestroyWindow( hWnd );

	return msg.wParam;
}

