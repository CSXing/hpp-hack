#pragma once

#include "Main.h"

namespace Client
{
	namespace Functions
	{
		namespace Misc
		{
			struct GStrafeScrollStruct
			{
				float flLastScrollTime;
				int ScrollCounter;
				bool ScrollDuck;
				bool DuckPressed;
			};

			class GroundStrafe
			{
			public:
				static bool Active, StandUpActive;
				static bool HelperActive;

				static void SetDuckPressed ( bool DuckPressed );
				static void SetScrollDuck ( bool ScrollDuck );
				static bool GetDuckPressed ( );

				static void CL_CreateMove ( const float &frametime, usercmd_s *cmd );

			private:
				static GStrafeScrollStruct Scroll;

				static int Count, State;				

				static float Distance ( const float &frametime );
				static bool FallRun ( );

				static void ScrollEmulation ( const float &frametime, usercmd_s *cmd );
				static void NoScrollEmulation ( const float &frametime, usercmd_s *cmd );

				static void ActiveGroundStrafe ( const float &frametime, usercmd_s *cmd );
				static void StandUp ( usercmd_s *cmd );

				static void Helper ( usercmd_s *cmd );
			};
		}
	}
}