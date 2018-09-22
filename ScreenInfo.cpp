#include "ScreenInfo.h"

namespace Client
{
	namespace Functions
	{
		namespace Visuals
		{
			KeysStruct ScreenInfo::Keys;
			ScrollStruct ScreenInfo::Scroll;

			BYTE ScreenInfo::FontColor[4];

			void ScreenInfo::SetJumpPressed ( bool JumpPressed )
			{
				Scroll.JumpPressed = JumpPressed;
			}

			void ScreenInfo::SetDuckPressed ( bool DuckPressed )
			{
				Scroll.DuckPressed = DuckPressed;
			}

			void ScreenInfo::SetScrollJump ( bool ScrollJump )
			{
				Scroll.ScrollJump = ScrollJump;
			}

			void ScreenInfo::SetScrollDuck ( bool ScrollDuck )
			{
				Scroll.ScrollDuck = ScrollDuck;
			}

			bool ScreenInfo::GetJumpPressed ( )
			{
				return Scroll.JumpPressed;
			}

			bool ScreenInfo::GetDuckPressed ( )
			{
				return Scroll.DuckPressed;
			}

			void ScreenInfo::SetColor ( )
			{
				FontColor[0] = BYTE ( g_Vars.ScreenInfo.FontColor[0] );
				FontColor[1] = BYTE ( g_Vars.ScreenInfo.FontColor[1] );
				FontColor[2] = BYTE ( g_Vars.ScreenInfo.FontColor[2] );
				FontColor[3] = BYTE ( g_Vars.ScreenInfo.FontColor[3] );
			}

			void ScreenInfo::DrawFPS ( )
			{
				Renderer::g_Fonts->Print ( 8, 15, FontColor[0], FontColor[1], FontColor[2], FontColor[3], g_Vars.ScreenInfo.FontOutline ?
					FL_OUTLINE : FL_NONE, g_Vars.ScreenInfo.FPS >= 2.0f ? "%.1f fps" : "%.0f fps", 1.0f / g_Info->GetFrameTime ( ) );
			}

			void ScreenInfo::DrawCopyright ( )
			{
				if ( g_Vars.ScreenInfo.Copyright == 1.0f )
				{
					Renderer::g_Fonts->Print ( SDK::Interfaces::g_Screen.iWidth - 118, 15, FontColor[0], FontColor[1],
						FontColor[2], FontColor[3], g_Vars.ScreenInfo.FontOutline ? FL_OUTLINE : FL_NONE, "Hpp Hack v3.3" );
				}
				else if ( g_Vars.ScreenInfo.Copyright >= 2.0f )
				{
					Renderer::g_Fonts->Print ( SDK::Interfaces::g_Screen.iWidth / 2, 15, FontColor[0], FontColor[1], FontColor[2],
						FontColor[3], g_Vars.ScreenInfo.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, "Hpp Hack v3.3" );
				}
			}

			void ScreenInfo::DrawTime ( )
			{
				if ( g_Vars.ScreenInfo.Time == 1.0f )
				{
					char TimeString[9];

					_strtime_s ( TimeString );

					Renderer::g_Fonts->Print ( SDK::Interfaces::g_Screen.iWidth - 78, g_Vars.ScreenInfo.Copyright != 1.0f ? 15 : 35, FontColor[0],
						FontColor[1], FontColor[2], FontColor[3], g_Vars.ScreenInfo.FontOutline ? FL_OUTLINE : FL_NONE, "%s", TimeString );
				}
				else if ( g_Vars.ScreenInfo.Time >= 2.0f )
				{
					char DateString[9], TimeString[9];

					_strdate_s ( DateString );
					_strtime_s ( TimeString );

					Renderer::g_Fonts->Print ( SDK::Interfaces::g_Screen.iWidth - 118, g_Vars.ScreenInfo.Copyright != 1.0f ? 15 : 35, FontColor[0],
						FontColor[1], FontColor[2], FontColor[3], g_Vars.ScreenInfo.FontOutline ? FL_OUTLINE : FL_NONE, "Time: %s", TimeString );

					Renderer::g_Fonts->Print ( SDK::Interfaces::g_Screen.iWidth - 118, g_Vars.ScreenInfo.Copyright != 1.0f ? 30 : 50, FontColor[0],
						FontColor[1], FontColor[2], FontColor[3], g_Vars.ScreenInfo.FontOutline ? FL_OUTLINE : FL_NONE, "Date: %s", DateString );
				}
			}

			void ScreenInfo::DrawShowKeys ( )
			{
				float flClientTime = SDK::Interfaces::g_pEngine->GetClientTime ( );

				if ( g_Vars.ScreenInfo.ShowKeys >= 2.0f )
				{
					if ( Scroll.ScrollJump )
					{
						++Scroll.ScrollCounter[0];

						Scroll.flLastScrollTime[0] = flClientTime + 0.15f;
					}

					if ( Scroll.ScrollDuck )
					{
						++Scroll.ScrollCounter[1];

						Scroll.flLastScrollTime[1] = flClientTime + 0.15f;
					}
				}

				int ShowKeysForwardX = Keys.Forward ? ( SDK::Interfaces::g_Screen.iWidth / 2 ) - 1 : SDK::Interfaces::g_Screen.iWidth / 2;
				int ShowKeysForwardY = int ( SDK::Interfaces::g_Screen.iHeight / 2.35f );

				Renderer::g_Fonts->Print ( ShowKeysForwardX, ShowKeysForwardY, FontColor[0], FontColor[1], FontColor[2], Keys.Forward ? 
					255 : 200, g_Vars.ScreenInfo.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, "  %s  ", Keys.Forward ? "W" : "." );

				int ShowKeysMoveRightX = Keys.MoveRight ? ( SDK::Interfaces::g_Screen.iWidth / 2 ) + 15 : ( SDK::Interfaces::g_Screen.iWidth / 2 ) + 16;
				int ShowKeysMoveRightY = ShowKeysForwardY + 18;

				Renderer::g_Fonts->Print ( ShowKeysMoveRightX, ShowKeysMoveRightY, FontColor[0], FontColor[1], FontColor[2], Keys.MoveRight ? 
					255 : 200, g_Vars.ScreenInfo.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, "%s", Keys.MoveRight ? "D" : "." );

				int ShowKeysMoveLeftX = Keys.MoveLeft ? ( SDK::Interfaces::g_Screen.iWidth / 2 ) - 15 : ( SDK::Interfaces::g_Screen.iWidth / 2 ) - 16;
				int ShowKeysMoveLeftY = ShowKeysMoveRightY;

				Renderer::g_Fonts->Print ( ShowKeysMoveLeftX, ShowKeysMoveLeftY, FontColor[0], FontColor[1], FontColor[2], Keys.MoveLeft ? 
					255 : 200, g_Vars.ScreenInfo.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, "%s", Keys.MoveLeft ? "A" : "." );

				int ShowKeysBackwardX = Keys.Backward ? ( SDK::Interfaces::g_Screen.iWidth / 2 ) - 1 : SDK::Interfaces::g_Screen.iWidth / 2;
				int ShowKeysBackwardY = ShowKeysMoveRightY;

				Renderer::g_Fonts->Print ( ShowKeysBackwardX, ShowKeysBackwardY, FontColor[0], FontColor[1], FontColor[2], Keys.Backward ? 
					255 : 200, g_Vars.ScreenInfo.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, "%s", Keys.Backward ? "S" : "." );

				int ShowKeysJumpX = SDK::Interfaces::g_Screen.iWidth / 2 + 45;
				int ShowKeysJumpY = Keys.Jump ? ShowKeysForwardY : ShowKeysForwardY + 2;

				Renderer::g_Fonts->Print ( ShowKeysJumpX, ShowKeysJumpY, FontColor[0], FontColor[1], FontColor[2], Keys.Jump ? 
					255 : 200, g_Vars.ScreenInfo.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, "%s", Keys.Jump ? "jump" : "-" );

				if ( g_Vars.ScreenInfo.ShowKeys >= 2.0f )
				{
					if ( Scroll.flLastScrollTime[0] - flClientTime > 1.0f )
						Scroll.flLastScrollTime[0] = 0.0f;

					if ( Scroll.flLastScrollTime[0] > flClientTime )
					{
						Renderer::g_Fonts->Print ( ShowKeysJumpX + 60, ShowKeysForwardY, FontColor[0], FontColor[1], FontColor[2],
							255, g_Vars.ScreenInfo.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, "scroll: %d", Scroll.ScrollCounter[0] );
					}
					else
					{
						if ( Scroll.ScrollCounter[0] > 0 )
							Scroll.ScrollCounter[0] = 0;
					}

					Scroll.ScrollJump = false;
					Scroll.JumpPressed = false;
				}

				int ShowKeysDuckX = ShowKeysJumpX;
				int ShowKeysDuckY = Keys.Duck ? ShowKeysMoveRightY : ShowKeysMoveRightY + 2;

				Renderer::g_Fonts->Print ( ShowKeysDuckX, ShowKeysDuckY, FontColor[0], FontColor[1], FontColor[2], Keys.Duck ? 
					255 : 200, g_Vars.ScreenInfo.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, "%s", Keys.Duck ? "duck" : "-" );

				if ( g_Vars.ScreenInfo.ShowKeys >= 2.0f )
				{
					if ( Scroll.flLastScrollTime[1] - flClientTime > 1.0f )
						Scroll.flLastScrollTime[1] = 0.0f;

					if ( Scroll.flLastScrollTime[1] > flClientTime )
					{
						Renderer::g_Fonts->Print ( ShowKeysDuckX + 60, ShowKeysMoveRightY, FontColor[0], FontColor[1], FontColor[2],
							255, g_Vars.ScreenInfo.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, "scroll: %d", Scroll.ScrollCounter[1] );
					}
					else
					{
						if ( Scroll.ScrollCounter[1] > 0 )
							Scroll.ScrollCounter[1] = 0;
					}

					Scroll.ScrollDuck = false;
					Scroll.DuckPressed = false;
				}
			}

			void ScreenInfo::DrawKreedzInfo ( )
			{
				if ( g_Vars.ScreenInfo.KreedzInfo == 1.0f )
				{
					int x = SDK::Interfaces::g_Screen.iWidth / 2;
					int y = int ( SDK::Interfaces::g_Screen.iHeight / 1.75f + 100 );

					Renderer::g_Fonts->Print ( x, y, FontColor[0], FontColor[1], FontColor[2], FontColor[3],  g_Vars.ScreenInfo.FontOutline ? 
						FL_CENTER | FL_OUTLINE : FL_CENTER, "%.0f units/sec", SDK::Interfaces::g_pPlayerMove->velocity.LengthXY ( ) );
				}
				else if ( g_Vars.ScreenInfo.KreedzInfo >= 2.0f )
				{
					int x = SDK::Interfaces::g_Screen.iWidth / 2;
					int y = int ( SDK::Interfaces::g_Screen.iHeight / 1.75f );

					Renderer::g_Fonts->Print ( x, y, FontColor[0], FontColor[1], FontColor[2], FontColor[3], g_Vars.ScreenInfo.FontOutline ? 
						FL_CENTER | FL_OUTLINE : FL_CENTER, "HSpeed: %.3f", SDK::Interfaces::g_pPlayerMove->velocity.LengthXY ( ) );

					y += 15;

					Renderer::g_Fonts->Print ( x, y, FontColor[0], FontColor[1], FontColor[2], FontColor[3], g_Vars.ScreenInfo.FontOutline ? 
						FL_CENTER | FL_OUTLINE : FL_CENTER, "VSpeed: %.3f", abs ( SDK::Interfaces::g_pPlayerMove->flFallVelocity ) );

					y += 15;

					Renderer::g_Fonts->Print ( x, y, FontColor[0], FontColor[1], FontColor[2], FontColor[3], g_Vars.ScreenInfo.FontOutline ? 
						FL_CENTER | FL_OUTLINE : FL_CENTER, "Height: %.3f", g_Info->GetHeightGround ( g_Info->GetGroundTrace ( ) ) );

					y += 15;

					Renderer::g_Fonts->Print ( x, y, FontColor[0], FontColor[1], FontColor[2], FontColor[3], g_Vars.ScreenInfo.FontOutline ?
						FL_CENTER | FL_OUTLINE : FL_CENTER, "EdgeDistance: %.3f", g_Info->GetEdgeDistance ( ) );

					y += 15;

					Renderer::g_Fonts->Print ( x, y, FontColor[0], FontColor[1], FontColor[2], FontColor[3], g_Vars.ScreenInfo.FontOutline ? 
						FL_CENTER | FL_OUTLINE : FL_CENTER, "GroundAngle: %.3f", g_Info->GetGroundAngle ( g_Info->GetGroundTrace ( ) ) );

					y += 15;

					Renderer::g_Fonts->Print ( x, y, FontColor[0], FontColor[1], FontColor[2], FontColor[3], g_Vars.ScreenInfo.FontOutline ? 
						FL_CENTER | FL_OUTLINE : FL_CENTER, "FallDamage: %d", g_Info->GetFallDamage ( ) );
				}
			}

			void ScreenInfo::HUD_Redraw ( )
			{
				SetColor ( );

				if ( g_Vars.ScreenInfo.FPS ) DrawFPS ( );
				if ( g_Vars.ScreenInfo.Copyright ) DrawCopyright ( );
				if ( g_Vars.ScreenInfo.Time ) DrawTime ( );

				if ( g_Info->GetAliveLocal ( ) )
				{
					if ( g_Vars.ScreenInfo.KreedzInfo ) DrawKreedzInfo ( );
					if ( g_Vars.ScreenInfo.ShowKeys ) DrawShowKeys ( );
				}
			}

			void ScreenInfo::CL_CreateMove ( usercmd_s *cmd )
			{
				Keys.Forward = cmd->buttons & IN_FORWARD;
				Keys.Backward = cmd->buttons & IN_BACK;
				Keys.MoveLeft = cmd->buttons & IN_MOVELEFT;
				Keys.MoveRight = cmd->buttons & IN_MOVERIGHT;
				Keys.Duck = cmd->buttons & IN_DUCK;
				Keys.Jump = cmd->buttons & IN_JUMP;
			}
		}
	}
}
