#pragma once

#include "Main.h"

namespace Renderer
{
	class Fonts
	{
	public:
		inline void InitText ( const char *Font, int Height, int Width )
		{
			HDC hDC = wglGetCurrentDC ( );

			g_FontListID = glGenLists ( 256 );

			HFONT hFont = CreateFont ( Height, Width, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, RUSSIAN_CHARSET,
				OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, CLEARTYPE_NATURAL_QUALITY, FF_DONTCARE | VARIABLE_PITCH, Font );

			HFONT hOldFont = ( HFONT )SelectObject ( hDC, hFont );

			if ( !wglUseFontBitmapsA ( hDC, 0, 255, g_FontListID ) )
				wglUseFontBitmapsA ( hDC, 0, 255, g_FontListID );

			for ( int i = 0; i < 255; ++i )
			{
				SIZE s;

				char Line[2] = { ( char )i, 0 };

				GetTextExtentPoint ( hDC, Line, 1, &s );

				this->Width[i] = s.cx;
				this->Height = s.cy;
			}

			SelectObject ( hDC, hOldFont );
			DeleteObject ( hFont );
		}

		inline void Print ( int x, int y, BYTE R, BYTE G, BYTE B, BYTE A, int Flags, const char *String, ... )
		{
			char Text[256];

			va_list ArgumentPtr;
			va_start ( ArgumentPtr, String );
			vsprintf_s ( Text, String, ArgumentPtr );
			va_end ( ArgumentPtr );

			glDisable ( GL_TEXTURE_2D );
			glEnable ( GL_BLEND );
			glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

			int DrawLen = 0;

			for ( char *p = Text; *p; ++p )
			{
				DrawLen += Width[*p];
			}

			if ( Flags & FL_CENTER )
			{
				x -= DrawLen / 2;
			}

			if ( Flags & FL_OUTLINE )
			{
				if ( g_Vars.Main.FontOutlineStyle == 1 )
				{
					Render ( x + 1, y + 1, 0, 0, 0, A, Text );
				}
				else if ( g_Vars.Main.FontOutlineStyle >= 2 )
				{
					Render ( x, y - 1, 0, 0, 0, A, Text );
					Render ( x, y + 1, 0, 0, 0, A, Text );
					Render ( x + 1, y, 0, 0, 0, A, Text );
					Render ( x - 1, y, 0, 0, 0, A, Text );

					Render ( x - 1, y - 1, 0, 0, 0, A, Text );
					Render ( x + 1, y - 1, 0, 0, 0, A, Text );
					Render ( x - 1, y + 1, 0, 0, 0, A, Text );
					Render ( x + 1, y + 1, 0, 0, 0, A, Text );
				}
			}

			Render ( x, y, R, G, B, A, Text );

			glDisable ( GL_BLEND );
			glEnable ( GL_TEXTURE_2D );
		}

		int Height, Width[255];

	private:
		GLuint g_FontListID;

		inline void Render ( int x, int y, BYTE R, BYTE G, BYTE B, BYTE A, const char *String )
		{
			int i;

			for ( i = 0; x < 0; ++i )
			{
				x += Width[String[i]];

				if ( !String[i] )
					return;
			}

			glColor4ub ( R, G, B, A );
			glRasterPos2i ( x, y );
			glHint ( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
			glPushAttrib ( GL_LIST_BIT );
			glListBase ( g_FontListID );
			glCallLists ( strlen ( String ) - i, GL_UNSIGNED_BYTE, String + i );
			glPopAttrib ( );
		}
	};

	extern Fonts *g_Fonts, *g_Verdana;
}