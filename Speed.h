#pragma once

#include "Main.h"

namespace Client
{
	namespace Functions
	{
		namespace Misc
		{
			class Speed
			{
			public:
				static bool BoostActive, SlowmotionActive;

				static void AdjustSpeed ( double Speed );
				static void CL_CreateMove (  );

			private:
				static void Helper ( );
				static void Boost ( );
				static void Slowmo ( );
			};
		}
	}
}