/***
*
*	Copyright (c) 1999, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
//  Vector.h
// A subset of the extdll.h in the project HL Entity DLL
//

#if !defined FILE_UTIL_VECTOR_H
#define FILE_UTIL_VECTOR_H

// Misc C-runtime library headers
#include "STDIO.H"
#include "STDLIB.H"
#include "MATH.H"

// Header file containing definition of globalvars_t and entvars_t
typedef int	func_t;					//
typedef int	string_t;				// from engine's pr_comp.h;
typedef float vec_t;				// needed before including progdefs.h

//=========================================================
// 2DVector - used for many pathfinding and many other 
// operations that are treated as planar rather than 3d.
//=========================================================
class Vector2D
{
public:
	inline Vector2D ( )
		: x ( 0.0f ), y ( 0.0f )
	{
	}

	inline Vector2D ( float X, float Y )
		: x ( X ), y ( Y )
	{
	}

	inline Vector2D ( float XY )
		: x ( XY ), y ( XY )
	{
	}

	inline float operator [] ( int i ) const
	{
		return ( ( float* )this )[i];
	}

	inline float& operator [] ( int i )
	{
		return ( ( float* )this )[i];
	}

	inline Vector2D& operator += ( const Vector2D &v )
	{
		x += v.x;
		y += v.y;

		return *this;
	}

	inline Vector2D& operator -= ( const Vector2D &v )
	{
		x -= v.x;
		y -= v.y;

		return *this;
	}

	inline Vector2D& operator *= ( const Vector2D &v )
	{
		x *= v.x;
		y *= v.y;

		return *this;
	}

	inline Vector2D& operator /= ( const Vector2D &v )
	{
		x /= v.x;
		y /= v.y;

		return *this;
	}

	inline Vector2D& operator += ( float v )
	{
		x += v;
		y += v;

		return *this;
	}

	inline Vector2D& operator -= ( float v )
	{
		x -= v;
		y -= v;

		return *this;
	}

	inline Vector2D& operator *= ( float v )
	{
		x *= v;
		y *= v;

		return *this;
	}

	inline Vector2D& operator /= ( float v )
	{
		x /= v;
		y /= v;

		return *this;
	}

	inline Vector2D operator - ( ) const
	{
		return Vector2D ( -x, -y );
	}

	inline Vector2D operator - ( const Vector2D &v ) const
	{
		return Vector2D ( x - v.x, y - v.y );
	}

	inline Vector2D operator + ( const Vector2D &v ) const
	{
		return Vector2D ( x + v.x, y + v.y );
	}

	inline Vector2D operator * ( const Vector2D &v ) const
	{
		return Vector2D ( x * v.x, y * v.y );
	}

	inline Vector2D operator / ( const Vector2D &v ) const
	{
		return Vector2D ( x / v.x, y / v.y );
	}

	inline float Length ( ) const
	{
		return sqrtf ( x * x + y * y );
	}

	inline float LengthSqr ( ) const
	{
		return ( x * x + y * y );
	}

	inline bool IsZero ( ) const
	{
		return ( x > -0.01f && x < 0.01f &&	y > -0.01f && y < 0.01f );
	}

	inline float DistTo ( const Vector2D &v ) const
	{
		return ( *this - v ).Length ( );
	}

	inline float DistToSqr ( const Vector2D &v ) const
	{
		return ( *this - v ).LengthSqr ( );
	}

	inline float Dot ( const Vector2D &v ) const
	{
		return ( x * v.x + y * v.y );
	}

	inline operator float *( )
	{
		return &x;
	}

	inline operator const float *( ) const
	{
		return &x;
	}

	inline Vector2D Normalize ( void ) const
	{
		float flLen = Length ( );

		if ( !flLen )
		{
			return Vector2D ( 0.0f, 0.0f );
		}
		else
		{
			flLen = 1.0f / flLen;

			return Vector2D ( x * flLen, y * flLen );
		}
	}

	vec_t	x, y;
};

inline Vector2D operator * ( float f, const Vector2D &v )
{
	return v * f;
}

//=========================================================
// 3D Vector
//=========================================================
class Vector						// same data-layout as engine's vec3_t,
{								//		which is a vec_t[3]
public:
	// Construction/destruction
	inline Vector ( )
		: x ( 0.0f ), y ( 0.0f ), z ( 0.0f )
	{
	}

	inline Vector ( float X, float Y, float Z )
		: x ( X ), y ( Y ), z ( Z )
	{
	}

	inline Vector ( float XYZ )
		: x ( XYZ ), y ( XYZ ), z ( XYZ )
	{
	}

	inline Vector ( float* v )
		: x ( v[0] ), y ( v[1] ), z ( v[2] )
	{
	}

	inline Vector ( const float* v )
		: x ( v[0] ), y ( v[1] ), z ( v[2] )
	{
	}

	// Operators
	inline float operator [] ( int i ) const
	{
		return ( ( float* )this )[i];
	}

	inline float& operator [] ( int i )
	{
		return ( ( float* )this )[i];
	}

	inline Vector& operator += ( const Vector &v )
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	inline Vector& operator -= ( const Vector &v )
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	inline Vector& operator *= ( const Vector &v )
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;

		return *this;
	}

	inline Vector& operator /= ( const Vector &v )
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;

		return *this;
	}

	inline Vector& operator += ( float v )
	{
		x += v;
		y += v;
		z += v;

		return *this;
	}

	inline Vector& operator -= ( float v )
	{
		x -= v;
		y -= v;
		z -= v;

		return *this;
	}

	inline Vector& operator *= ( float v )
	{
		x *= v;
		y *= v;
		z *= v;

		return *this;
	}

	inline Vector& operator /= ( float v )
	{
		x /= v;
		y /= v;
		z /= v;

		return *this;
	}

	inline Vector operator - ( ) const
	{
		return Vector ( -x, -y, -z );
	}

	inline Vector operator - ( const Vector &v ) const
	{
		return Vector ( x - v.x, y - v.y, z - v.z );
	}

	inline Vector operator + ( const Vector &v ) const
	{
		return Vector ( x + v.x, y + v.y, z + v.z );
	}

	inline Vector operator * ( const Vector &v ) const
	{
		return Vector ( x * v.x, y * v.y, z * v.z );
	}

	inline Vector operator / ( const Vector &v ) const
	{
		return Vector ( x / v.x, y / v.y, z / v.z );
	}

	// Methods
	inline float Length ( ) const
	{
		return sqrtf ( x * x + y * y + z * z );
	}

	inline float LengthSqr ( ) const
	{
		return ( x * x + y * y + z * z );
	}

	inline float LengthXY ( ) const
	{
		return sqrtf ( x * x + y * y );
	}

	inline float LengthXZ ( ) const
	{
		return sqrtf ( x * x + z * z );
	}

	inline bool IsZero ( ) const
	{
		return ( x > -0.01f && x < 0.01f &&	y > -0.01f && y < 0.01f && z > -0.01f && z < 0.01f );
	}

	inline float DistTo ( const Vector &v ) const
	{
		return ( *this - v ).Length ( );
	}

	inline float DistToSqr ( const Vector &v ) const
	{
		return ( *this - v ).LengthSqr ( );
	}

	inline float Dot ( const Vector &v ) const
	{
		return ( x * v.x + y * v.y + z * v.z );
	}

	inline Vector Cross ( const Vector &v ) const
	{
		return Vector ( y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x );
	}

	inline operator float *( )
	{
		return &x;
	}

	inline operator const float *( ) const
	{
		return &x;
	}

	inline Vector2D Make2D ( ) const
	{
		Vector2D v;

		v.x = x;
		v.y = y;

		return v;
	}

	inline Vector Normalize ( ) const
	{
		float flLen = Length ( );

		if ( !flLen )
			return Vector ( 0.0f, 0.0f, 1.0f );

		flLen = 1.0f / flLen;

		return Vector ( x * flLen, y * flLen, z * flLen );
	}

	// Members
	vec_t x, y, z;
};

inline Vector operator * ( float f, const Vector &v )
{
	return v * f;
}

inline void ClampAngles ( Vector &Angles )
{
	if ( Angles.y < -180.0f )
		Angles.y += 360.0f;

	if ( Angles.y > 180.0f )
		Angles.y -= 360.0f;

	if ( Angles.x < -89.0f )
		Angles.x = -89.0f;

	if ( Angles.x > 89.0f )
		Angles.x = 89.0f;
}

inline float DotProduct ( const Vector& a, const Vector& b ) 
{
	return( a.x * b.x + a.y * b.y + a.z * b.z ); 
}

#define vec3_t Vector

#define VectorAdd(a,b,c) {(c)[0]=(a)[0]+(b)[0];(c)[1]=(a)[1]+(b)[1];(c)[2]=(a)[2]+(b)[2];}
#define VectorCopy(a,b) {(b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2];}
#define VectorClear(a) { a[0]=0.0;a[1]=0.0;a[2]=0.0;}

#endif
