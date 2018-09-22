#pragma once

#include "Main.h"

namespace Client
{
	namespace Functions
	{
		namespace Misc
		{
			struct BHopScrollStruct
			{
				float flLastScrollTime;
				int ScrollCounter;
				int PerfectJumpsCount;
				bool ScrollJump;
				bool JumpPressed;
			};

			class BunnyHop
			{
			public:
				static bool Active, StandUpActive;
				static bool HelperActive;

				static void SetJumpPressed ( bool JumpPressed );
				static void SetScrollJump ( bool ScrollJump );
				static bool GetJumpPressed ( );

				static void CL_CreateMove ( const float &frametime, usercmd_s *cmd );

			private:
				static BHopScrollStruct Scroll;

				static int FramesOnGround;
				static bool inWater, State;				

				static void CountingFramesOnGround ( );
				static float Distance ( const float &frametime );
				static bool PerfectJump—ondition ( const float &frametime );

				static void NoSlowdown ( const float &frametime, usercmd_s *cmd );
				static void ScrollEmulation ( const float &frametime, usercmd_s *cmd );
				static void NoScrollEmulation ( const float &frametime, usercmd_s *cmd );

				static void ActiveBunnyHop ( const float &frametime, usercmd_s *cmd );
				static void StandUp ( usercmd_s *cmd );

				static void Helper ( usercmd_s *cmd );
			};
		}
	}
}