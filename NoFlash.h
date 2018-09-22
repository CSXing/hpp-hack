#pragma once

#include "Main.h"

namespace Client
{
	namespace Functions
	{
		namespace Visuals
		{
			class NoFlash
			{
			public:
				static float GetFlashedPercentage ( );

				static void HUD_Redraw ( );

			private:
				static float flCurstateFlashed;
				static float flPrevstateFlashed;

				static BYTE FadeColor[3];
				static BYTE ShowPecentColor[3];

				static bool SetColor;

				static void UpdateFlashedData ( );

				static void DrawFlashed ( const int& Percentage );
				static void DrawFlashedBox ( const int& Percentage );

				static void InterpolatedShowPercentColor ( const int& Percentage );

				static void SetFadeColorRandom ( );
				static void SetFadeColor ( );
			};
		}
	}
}