#pragma once

#include "Main.h"

namespace Client
{
	namespace Functions
	{
		namespace Visuals
		{
			class Other
			{
			public:
				static void HUD_Redraw ( );

			private:
				static void DrawAimSpot ( );
				static void DrawAimFOV ( );
				static void DrawPunch ( );
				static void DrawSpread ( );
				static void StatusAimBot ( );
				static void StatusTriggerBot ( );
			};
		}
	}
}