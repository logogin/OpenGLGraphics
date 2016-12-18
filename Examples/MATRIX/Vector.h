// (C) Pasha Malinnikov, mpa@cci.lg.ua

// ¬ы можете найти ответ и на свой вопрос. «аходите:
// Here you can find answer on your question too! Welcome:

//							http://www.3d.lg.ua
//							~~~~~~~~~~~~~~~~~~~
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CVector_H__1C4C1B80_02AB_11D4_A040_00105A6EBE46__INCLUDED_)
#define AFX_CVector_H__1C4C1B80_02AB_11D4_A040_00105A6EBE46__INCLUDED_
#pragma once

#define DEG2RAD(a)	(PI/180*(a))
#define RAD2DEG(a)	(180/PI*(a))

class CVector  
{
public:
    double x, y, z;

public:
    CVector(double x_, double y_, double z_): x(x_), y(y_), z(z_) {}
    CVector(): x(0), y(0), z(0) {}
    CVector(const CVector &V): x(V.x), y(V.y), z(V.z) {}

	const bool operator == (const CVector& Vector) const
	{
		return (x == Vector.x && y == Vector.y && z == Vector.z);
	}
	const bool operator != (const CVector& Vector) const
	{
		return !(*this == Vector);
	}

    // + -
    CVector operator + (const CVector &V) const
    {
        return CVector(x + V.x, y + V.y, z + V.z);
    }

    CVector &operator += (const CVector &V)
    {
        x += V.x; y += V.y; z += V.z;
        return *this;
    }
    CVector operator - () const
    {
        return CVector(-x, -y, -z);
    }
    CVector operator - (const CVector &V) const
    {
        return CVector(x - V.x, y - V.y, z - V.z);
    }
    CVector &operator -= (const CVector &V)
    {
        x -= V.x; y -= V.y; z -= V.z;
        return *this;
    }
    CVector &operator * (const CVector &V)//////////////
    {
        x *= V.x; y *= V.y; z *= V.z;
        return *this;
    }////////////////////////////////////////////////////
    CVector operator * (double f) const 
    {
        return CVector(x * f, y * f, z * f); 
    }
    CVector &operator *= (double f)
    {
        x *= f; y *= f; z *= f;
        return *this;
    }
    // dot product - векторное произведение
    CVector operator^(const CVector& V) const
    {
        return CVector(y*V.z - z*V.y, z*V.x - x*V.z, x*V.y - y*V.x);
    }
    // scalar product - скал€рное произведение
    double operator | (const CVector &V) const
    {
        // A | B = A.Magnitude() * A.Magnitude() * Cos(AB);
        return x*V.x + y*V.y + z*V.z;
        // NormOfVector | Vector = LengthOfVector
    }

public:
    double Magnitude()
    {
        return sqrt(x*x + y*y + z*z);
    }
    CVector &Normalize()
    {
        double OneDivMagnitude = 1.0f/Magnitude();
        x *= OneDivMagnitude;
        y *= OneDivMagnitude;
        z *= OneDivMagnitude;
        return *this;
    }
    CVector GetNormalized()
    {
        return CVector(*this).Normalize();
    }
};

typedef CVector cPoint;

#endif // !defined(AFX_CVector_H__1C4C1B80_02AB_11D4_A040_00105A6EBE46__INCLUDED_)


