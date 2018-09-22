#pragma once

#include "Main.h"

namespace Renderer
{
	class Drawing
	{
	public:
		void FillArea ( int x, int y, int w, int h, BYTE R, BYTE G, BYTE B, BYTE A );

		inline void Box ( int x, int y, int w, int h, int lw, BYTE R, BYTE G, BYTE B, BYTE A )
		{
			FillArea ( x, y, w, lw, R, G, B, A );
			FillArea ( x + w - lw, y + lw, lw, h - lw, R, G, B, A );
			FillArea ( x, y + lw, lw, h - lw, R, G, B, A );
			FillArea ( x + lw, y + h - lw, w - lw * 2, lw, R, G, B, A );
		}

		inline void BoxOutline ( int x, int y, int w, int h, int lw, BYTE R, BYTE G, BYTE B, BYTE A )
		{
			Box ( x - 1, y - 1, w + 2, h + 2, lw + 2, 0, 0, 0, A );
			Box ( x, y, w, h, lw, R, G, B, A );
		}

		inline void BoxCorner ( int x, int y, int w, int h, int lw, BYTE R, BYTE G, BYTE B, BYTE A )
		{
			FillArea ( x, y, w / 4, lw, R, G, B, A );
			FillArea ( x + w - w / 4, y, w / 4, lw, R, G, B, A );
			FillArea ( x, y + lw, lw, h / 4 - lw, R, G, B, A );
			FillArea ( x, y + h - h / 4, lw, h / 4, R, G, B, A );
			FillArea ( x + w - lw, y + lw, lw, h / 4 - lw, R, G, B, A );
			FillArea ( x + w - lw, y + h - h / 4, lw, h / 4, R, G, B, A );
			FillArea ( x + lw, y + h - lw, w / 4 - lw, lw, R, G, B, A );
			FillArea ( x + w - w / 4, y + h - lw, w / 4 - lw, lw, R, G, B, A );
		}

		inline void BoxCornerOutline ( int x, int y, int w, int h, int lw, BYTE R, BYTE G, BYTE B, BYTE A )
		{
			BoxCorner ( x - 1, y + 1, w, h, lw, 0, 0, 0, A );
			BoxCorner ( x - 1, y - 1, w, h, lw, 0, 0, 0, A );
			BoxCorner ( x + 1, y + 1, w, h, lw, 0, 0, 0, A );
			BoxCorner ( x + 1, y - 1, w, h, lw, 0, 0, 0, A );

			BoxCorner ( x, y, w, h, lw, R, G, B, A );
		}

		inline void Circle ( int x, int y, int rad, int amount, int lw, BYTE R, BYTE G, BYTE B, BYTE A )
		{
			glDisable ( GL_TEXTURE_2D );
			glEnable ( GL_BLEND );
			glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			glColor4ub ( R, G, B, A );
			glLineWidth ( GLfloat ( lw ) );
			glBegin ( GL_LINE_LOOP );

			for ( int i = 0; i < amount; ++i )
			{
				double Angle = 2.0 * M_PI * i / amount;
				double X = rad * cos ( Angle );
				double Y = rad * sin ( Angle );

				glVertex2d ( x + X, y + Y );
			}

			glEnd ( );
			glEnable ( GL_TEXTURE_2D );
			glDisable ( GL_BLEND );
		}
	};

	extern Drawing *g_Drawing;
}