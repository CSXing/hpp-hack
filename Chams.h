#pragma once

#include "Main.h"

namespace Client
{
	namespace Functions
	{
		namespace Visuals
		{
			class Chams
			{
			public:
				inline static float GetPlayerColorR ( ) { return PlayerR; }
				inline static float GetPlayerColorG ( ) { return PlayerG; }
				inline static float GetPlayerColorB ( ) { return PlayerB; }

				inline static float GetWeaponsColorR ( ) { return WeaponsR; }
				inline static float GetWeaponsColorG ( ) { return WeaponsG; }
				inline static float GetWeaponsColorB ( ) { return WeaponsB; }

				static void StudioRenderModel ( );

			private:
				static float PlayerR, PlayerG, PlayerB;
				static float WeaponsR, WeaponsG, WeaponsB;
			};
		}
	}
}