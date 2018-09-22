#pragma once

#include "Main.h"

namespace Client
{
	namespace Functions
	{
		namespace Visuals
		{
			struct KeysStruct
			{
				bool Forward, Backward;
				bool MoveLeft, MoveRight;
				bool Duck, Jump;
			};

			struct ScrollStruct
			{
				float flLastScrollTime[2];
				BYTE ScrollCounter[2];
				bool ScrollJump, JumpPressed;
				bool ScrollDuck, DuckPressed;
			};

			class ScreenInfo
			{
			public:
				static void SetJumpPressed ( bool JumpPressed );
				static void SetDuckPressed ( bool DuckPressed );
				static void SetScrollJump ( bool ScrollJump );
				static void SetScrollDuck ( bool ScrollDuck );

				static bool GetJumpPressed ( );
				static bool GetDuckPressed ( );

				static void HUD_Redraw ( );
				static void CL_CreateMove ( usercmd_s *cmd );

			private:
				static KeysStruct Keys;
				static ScrollStruct Scroll;

				static BYTE FontColor[4];

				static void SetColor ( );
				static void DrawFPS ( );
				static void DrawCopyright ( );
				static void DrawTime ( );
				static void DrawShowKeys ( );
				static void DrawKreedzInfo ( );
			};
		}
	}
}