#pragma once

#include "Main.h"

namespace Client
{
	namespace Functions
	{
		namespace Visuals
		{
			class Crosshair
			{
			public:
				static void HUD_Redraw ( );

			private:
				static int Size, Gap;
				static int Thickness;
				static BYTE Color[4];

				static void SetSettings ( );

				static void DrawCrosshair ( const int &x, const int &y, BYTE R, BYTE G, BYTE B, BYTE A );
				static void DrawDot ( const int &x, const int &y, BYTE R, BYTE G, BYTE B, BYTE A );
			};
		}
	}
}