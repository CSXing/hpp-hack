#pragma once

#include "Main.h"

namespace OpenGL
{
	typedef void ( APIENTRY *glBegin_t )( GLenum );
	typedef void ( APIENTRY *glVertex3fv_t )( const GLfloat * );
	typedef void ( APIENTRY *glColor4f_t )( float r, float g, float b, float a );

	extern glBegin_t pglBegin;
	extern glVertex3fv_t pglVertex3fv;
	extern glColor4f_t pglColor4f;

	extern bool Hands;

	void APIENTRY Hooked_glBegin ( GLenum mode );
	void APIENTRY Hooked_glVertex3fv ( GLfloat *v );
	void APIENTRY Hooked_glColor4f ( float r, float g, float b, float a );

	void* DetourFunc ( BYTE *src, const BYTE *dst, const int len );
}