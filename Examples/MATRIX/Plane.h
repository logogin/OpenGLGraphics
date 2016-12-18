// (C) Pasha Malinnikov, mpa@cci.lg.ua

// Вы можете найти ответ и на свой вопрос. Заходите:
// Here you can find answer on your question too! Welcome:

//							http://www.3d.lg.ua
//							~~~~~~~~~~~~~~~~~~~
//////////////////////////////////////////////////////////////////////

// Plane.h: interface for the Plane class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLANE_H__5180E2B7_319C_11D5_8FAA_000000000000__INCLUDED_)
#define AFX_PLANE_H__5180E2B7_319C_11D5_8FAA_000000000000__INCLUDED_

#include "includes.h"
#include "Vector.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class Plane
{
public:
	CVector N;
	double	D;

	Plane(double A=1, double B=0, double C=0, double D1=0)
	{
			N = CVector(A, B, C).GetNormalized();
			D = D1;
	}
	Plane( CVector& Normal, double D=0) : N(Normal), D(D) { }
	Plane( Plane& Plane) : N(Plane.N), D(Plane.D) { }

	Plane( CVector& VertexA, CVector& VertexB, CVector& VertexC)
	{
		CVector NormalA = ((VertexC - VertexA).GetNormalized());
		CVector NormalB = ((VertexC - VertexB).GetNormalized());
		D = - VertexA | (N = (NormalA ^ NormalB).GetNormalized());
	}

	Plane& operator = ( Plane& Plane)
	{
		N = Plane.N;
		D = Plane.D;
		return *this;
	}

	//	Boolean Operators
	bool operator == ( Plane& Plane)
	{
		return N == Plane.N && D == Plane.D;
	}
	bool operator != ( Plane& Plane)
	{
		return !(*this == Plane);
	}

	//	Just your average plane functions
	bool PointOnPlane( CVector& Point)
	{
		return DistanceToPlane(Point) == 0;
	}
	double DistanceToPlane( CVector& Point)
	{
		return (N | Point) + D;
	}
	CVector RayIntersection( CVector& RayPos,  CVector& RayDir)
	{
		double a = N | RayDir;
		if (a == 0) return RayPos;	//error line parallel to plane
		
		return RayPos - RayDir * (DistanceToPlane(RayPos) / a);
	}

	//Drawing
	void Draw( double nrows, double ncols, double step)
	{
		CVector ax(1, 0, 0);
		CVector horizproj(N.x, N.y, 0.0);
		horizproj.Normalize();

		glPushMatrix();

			glRotated(RAD2DEG(acos(horizproj | ax)), 0, 0, 1);
			glRotated(90-RAD2DEG(acos(horizproj | N)),
				0, 1, 0);

			glTranslated(0, 0, D);

			glBegin(GL_LINES);
				for( double r=0; r<nrows*step; r+=step)
				{
					glVertex3d(-nrows*step/2 + r,  -ncols*step/2,  0.0 );
					glVertex3d(-nrows*step/2 + r,   ncols*step/2,  0.0 );
				}
			glEnd();
			glBegin(GL_LINES);
				for( double c=0; c<nrows*step; c+=step)
				{
					glVertex3d(-nrows*step/2,  -ncols*step/2 + c,  0.0 );
					glVertex3d( nrows*step/2,  -ncols*step/2 + c,  0.0 );
				}
			glEnd();


		glPopMatrix();

		//Normal
/*		glBegin(GL_LINES);
			glVertex3d( 0.0, 0.0,  0.0 );
			glVertex3d( N.x, N.y,  N.z );
		glEnd();*/
	}
};

#endif // !defined(AFX_PLANE_H__5180E2B7_319C_11D5_8FAA_000000000000__INCLUDED_)
