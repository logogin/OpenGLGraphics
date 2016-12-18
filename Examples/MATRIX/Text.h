// Text.h: interface for the Text class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXT_H__5194DD23_313A_11D5_8FA9_000000000000__INCLUDED_)
#define AFX_TEXT_H__5194DD23_313A_11D5_8FA9_000000000000__INCLUDED_

#include "includes.h"
#include "Text.h"

extern HDC	hDC;

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class Text  
{
public:
	bool Init( int mode )
	{
		SelectObject(hDC, GetStockObject(SYSTEM_FIXED_FONT));
		wglUseFontBitmaps (hDC, 0, 255, 1000);
		glListBase (1000);

		return true;
	}

	void Draw3D(float x, float y, float z, char * string)
	{
		glRasterPos3f(x, y, z);
		glCallLists (strlen(string), GL_UNSIGNED_BYTE, string);
	}

	void Draw2D(float x, float y, char * string)
	{
		glPushMatrix();
		glLoadIdentity();

		glOrtho (0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

		glRasterPos2f(x, y);
		glCallLists (strlen(string), GL_UNSIGNED_BYTE, string);

		glPopMatrix();

	}

	Text(){}
	virtual ~Text(){}

};

#endif // !defined(AFX_TEXT_H__5194DD23_313A_11D5_8FA9_000000000000__INCLUDED_)
