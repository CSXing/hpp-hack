#include "GroundStrafe.h"

namespace Client
{
	namespace Functions
	{
		namespace Misc
		{
			GStrafeScrollStruct GroundStrafe::Scroll;

			int GroundStrafe::Count, GroundStrafe::State;
			bool GroundStrafe::HelperActive;

			bool GroundStrafe::Active, GroundStrafe::StandUpActive;

			void GroundStrafe::SetDuckPressed ( bool DuckPressed )
			{
				Scroll.DuckPressed = DuckPressed;
			}

			void GroundStrafe::SetScrollDuck ( bool ScrollDuck )
			{
				Scroll.ScrollDuck = ScrollDuck;
			}

			bool GroundStrafe::GetDuckPressed ( )
			{
				return Scroll.DuckPressed;
			}

			float GroundStrafe::Distance ( const float &frametime )
			{
				return abs ( g_Info->GetHeightGround ( g_Info->GetGroundTrace ( ) ) / SDK::Interfaces::g_pPlayerMove->flFallVelocity / frametime * 2.0f );
			}

			bool GroundStrafe::FallRun ( )
			{
				return g_Info->GetGroundAngle ( g_Info->GetGroundTrace ( ) ) >= 28.5f && g_Info->GetGroundAngle ( g_Info->GetGroundTrace ( ) ) <= 45.0f;
			}

			void GroundStrafe::ScrollEmulation ( const float &frametime, usercmd_s *cmd )
			{
				float flDistance = SDK::Interfaces::g_pEngine->pfnRandomFloat ( StandUpActive ? g_Vars.GroundStrafe.ScrollDistance[0] + 2.0f :
					g_Vars.GroundStrafe.ScrollDistance[0], StandUpActive ? g_Vars.GroundStrafe.ScrollDistance[1] + 2.0f : g_Vars.GroundStrafe.ScrollDistance[1] );

				if ( Distance ( frametime ) <= flDistance || SDK::Interfaces::g_pPlayerMove->flags & FL_ONGROUND )
				{
					if ( g_Vars.GroundStrafe.SlowdownScale != 1.0f && g_Info->GetGroundAngle ( g_Info->GetGroundTrace ( ) ) <=
						g_Vars.GroundStrafe.SlowdownAngle && SDK::Interfaces::g_pPlayerMove->flags & FL_ONGROUND )
					{
						Speed::AdjustSpeed ( g_Vars.GroundStrafe.SlowdownScale <= 0.0f ? 0.000001f : g_Vars.GroundStrafe.SlowdownScale );
					}

					mouse_event ( MOUSEEVENTF_WHEEL, 0, 0, g_Vars.GroundStrafe.ScrollDirection > DOWN ? 120 : -120, 0 );

					Count = BYTE ( SDK::Interfaces::g_pEngine->pfnRandomLong ( int ( g_Vars.GroundStrafe.ScrollCount[0] ), int ( g_Vars.GroundStrafe.ScrollCount[1] ) ) );
					State = 1;
				}
			}

			void GroundStrafe::NoScrollEmulation ( const float &frametime, usercmd_s *cmd )
			{
				if ( Distance ( frametime ) <= ( StandUpActive ? 4.0f : 2.0f ) || SDK::Interfaces::g_pPlayerMove->flags & FL_ONGROUND )
				{
					if ( g_Vars.GroundStrafe.SlowdownScale != 1.0f && g_Info->GetGroundAngle ( g_Info->GetGroundTrace ( ) ) <=
						g_Vars.GroundStrafe.SlowdownAngle && SDK::Interfaces::g_pPlayerMove->flags & FL_ONGROUND )
					{
						Speed::AdjustSpeed ( g_Vars.GroundStrafe.SlowdownScale <= 0.0f ? 0.000001f : g_Vars.GroundStrafe.SlowdownScale );
					}

					cmd->buttons |= IN_DUCK;

					Count = BYTE ( SDK::Interfaces::g_pEngine->pfnRandomLong ( 1, 3 ) );
					State = 1;
				}
			}

			void GroundStrafe::ActiveGroundStrafe ( const float &frametime, usercmd_s *cmd )
			{
				if ( Count )
				{
					if ( State == 1 )
					{
						if ( !g_Vars.GroundStrafe.ScrollEmulation && !FallRun ( ) )
							cmd->buttons &= ~IN_DUCK;

						if ( g_Vars.GroundStrafe.SlowdownScale != 1.0f && g_Info->GetGroundAngle ( g_Info->GetGroundTrace ( ) ) <=
							g_Vars.GroundStrafe.SlowdownAngle && SDK::Interfaces::g_pPlayerMove->flags & FL_ONGROUND )
						{
							Speed::AdjustSpeed ( g_Vars.GroundStrafe.SlowdownScale <= 0.0f ? 0.000001f : g_Vars.GroundStrafe.SlowdownScale );
						}

						--Count;

						State = 2;

						return;
					}
					else if ( State == 2 )
					{
						if ( !g_Vars.GroundStrafe.ScrollEmulation && g_Vars.GroundStrafe.FallRun && FallRun ( ) )
						{
							mouse_event ( MOUSEEVENTF_WHEEL, 0, 0, g_Vars.GroundStrafe.ScrollDirection > DOWN ? 120 : -120, 0 );

							State = 1;

							return;
						}

						if ( g_Vars.GroundStrafe.SlowdownScale != 1.0f && g_Info->GetGroundAngle ( g_Info->GetGroundTrace ( ) ) <=
							g_Vars.GroundStrafe.SlowdownAngle && SDK::Interfaces::g_pPlayerMove->flags & FL_ONGROUND )
						{
							Speed::AdjustSpeed ( g_Vars.GroundStrafe.SlowdownScale <= 0.0f ? 0.000001f : g_Vars.GroundStrafe.SlowdownScale );
						}

						g_Vars.GroundStrafe.ScrollEmulation ?
							mouse_event ( MOUSEEVENTF_WHEEL, 0, 0, g_Vars.GroundStrafe.ScrollDirection > DOWN ? 120 : -120, 0 ) : cmd->buttons |= IN_DUCK;

						State = 1;

						return;
					}
				}
				else
					State = 0;

				if ( SDK::Interfaces::g_pPlayerMove->movetype == 5 || SDK::Interfaces::g_pPlayerMove->waterlevel >= 2 )
				{
					return;
				}

				if ( g_Vars.GroundStrafe.FallRun && FallRun ( ) )
				{
					if ( SDK::Interfaces::g_pPlayerMove->flFallVelocity > 0.0f )
					{
						cmd->buttons |= IN_DUCK;

						return;
					}
					else
					{
						Count = SDK::Interfaces::g_pEngine->pfnRandomLong ( 2, 3 );
						State = 1;

						return;
					}
				}

				if ( g_Info->GetGroundAngle ( g_Info->GetGroundTrace ( ) ) > 45.0f && g_Info->GetGroundAngle ( g_Info->GetGroundTrace ( ) ) < 90.0f )
				{
					if ( SDK::Interfaces::g_pPlayerMove->flags & FL_ONGROUND )
					{
						g_Vars.GroundStrafe.ScrollEmulation ?
							mouse_event ( MOUSEEVENTF_WHEEL, 0, 0, g_Vars.GroundStrafe.ScrollDirection > DOWN ? 120 : -120, 0 ) : cmd->buttons |= IN_DUCK;
					}
					else
						cmd->buttons &= ~IN_DUCK;

					return;
				}

				g_Vars.GroundStrafe.ScrollEmulation ? ScrollEmulation ( frametime, cmd ) : NoScrollEmulation ( frametime, cmd );
			}

			void GroundStrafe::StandUp ( usercmd_s *cmd )
			{
				if ( SDK::Interfaces::g_pPlayerMove->flFallVelocity >= g_Vars.GroundStrafe.StandUpFallVelocity &&
					SDK::Interfaces::g_pPlayerMove->movetype != 5 && SDK::Interfaces::g_pPlayerMove->waterlevel < 2 )
				{
					if ( !g_Info->GetGroundAngle ( g_Info->GetGroundTrace ( ) ) && SDK::Interfaces::g_pPlayerMove->flFallVelocity >= 210.0f )
						return;

					if ( g_Info->GetGroundAngle ( g_Info->GetGroundTrace ( ) ) > 45.0f && g_Info->GetGroundAngle ( g_Info->GetGroundTrace ( ) ) < 90.0f )
					{
						cmd->buttons &= ~IN_DUCK;

						return;
					}

					cmd->buttons |= IN_DUCK;
				}
			}

			void GroundStrafe::Helper ( usercmd_s *cmd )
			{
				float flClientTime = SDK::Interfaces::g_pEngine->GetClientTime ( );

				if ( Scroll.ScrollDuck )
				{
					++Scroll.ScrollCounter;

					Scroll.flLastScrollTime = flClientTime + 0.15f;
				}

				if ( Scroll.flLastScrollTime - flClientTime > 1.0f )
					Scroll.flLastScrollTime = 0.0f;

				if ( Scroll.flLastScrollTime > flClientTime )
				{
					if ( !HelperActive )
					{
						if ( Scroll.ScrollCounter > 0 && SDK::Interfaces::g_pPlayerMove->flFallVelocity > 0.0f &&
							g_Info->GetHeightGround ( g_Info->GetGroundTrace ( ) ) <= 4.2f && Scroll.flLastScrollTime - flClientTime >= 0.13f )
						{
							HelperActive = true;
						}
					}
				}
				else
				{
					if ( Scroll.ScrollCounter > 0 )
						Scroll.ScrollCounter = 0;

					HelperActive = false;
				}

				if ( HelperActive )
				{
					if ( SDK::Interfaces::g_pPlayerMove->movetype == 5 )
					{
						HelperActive = false;

						return;
					}

					if ( SDK::Interfaces::g_pPlayerMove->flags & FL_ONGROUND )
					{
						cmd->buttons |= IN_DUCK;

						HelperActive = false;
					}
					else
						cmd->buttons &= ~IN_DUCK;
				}

				Scroll.ScrollDuck = false;
				Scroll.DuckPressed = false;
			}

			void GroundStrafe::CL_CreateMove ( const float &frametime, usercmd_s *cmd )
			{
				if ( Active || StandUpActive )
				{
					cmd->buttons &= ~IN_JUMP;

					ActiveGroundStrafe ( frametime, cmd );

					if ( StandUpActive )
					{
						StandUp ( cmd );
					}
				}
				else
					Helper ( cmd );
			}
		}
	}
}