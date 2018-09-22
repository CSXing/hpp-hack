#include "BunnyHop.h"

namespace Client
{
	namespace Functions
	{
		namespace Misc
		{
			BHopScrollStruct BunnyHop::Scroll;

			int BunnyHop::FramesOnGround;
			bool BunnyHop::inWater, BunnyHop::State;
			bool BunnyHop::HelperActive;

			bool BunnyHop::Active, BunnyHop::StandUpActive;

			void BunnyHop::SetJumpPressed ( bool JumpPressed )
			{
				Scroll.JumpPressed = JumpPressed;
			}

			void BunnyHop::SetScrollJump ( bool ScrollJump )
			{
				Scroll.ScrollJump = ScrollJump;
			}

			bool BunnyHop::GetJumpPressed ( )
			{
				return Scroll.JumpPressed;
			}

			void BunnyHop::CountingFramesOnGround ( )
			{
				if ( SDK::Interfaces::g_pPlayerMove->flags & FL_ONGROUND && SDK::Interfaces::g_pPlayerMove->waterlevel < 2 )
				{
					++FramesOnGround;

					if ( FramesOnGround > 4 )
						FramesOnGround = 4;
				}
				else
					FramesOnGround = 0;
			}

			float BunnyHop::Distance ( const float &frametime )
			{
				if ( g_Vars.BunnyHop.NoSlowdown )
				{
					if ( g_Info->GetGroundAngle ( g_Info->GetGroundTrace ( ) ) > 0.0f && g_Info->GetGroundAngle ( g_Info->GetGroundTrace ( ) ) <= 45.0f )
					{
						return abs ( g_Info->GetGroundAngle ( g_Info->GetGroundTrace ( ) ) / SDK::Interfaces::g_pPlayerMove->flFallVelocity / frametime * 2.0f );
					}
					else
					{
						return abs ( g_Info->GetGroundAngle ( g_Info->GetGroundTrace ( ) ) / frametime * 0.01f );
					}
				}
				else
					return abs ( g_Info->GetGroundAngle ( g_Info->GetGroundTrace ( ) ) / SDK::Interfaces::g_pPlayerMove->flFallVelocity / frametime * 2.0f );
			}

			bool BunnyHop::PerfectJumpÑondition ( const float &frametime )
			{
				float flDistance = Distance ( frametime );

				return ( flDistance >= 5.0f && flDistance <= 12.0f ) || ( SDK::Interfaces::g_pPlayerMove->flags & FL_ONGROUND || g_Info->GetHeightGround ( g_Info->GetGroundTrace ( ) ) <= 0.01f );
			}

			void BunnyHop::NoSlowdown ( const float &frametime, usercmd_s *cmd )
			{
				if ( PerfectJumpÑondition ( frametime ) )
				{
					if ( SDK::Interfaces::g_pPlayerMove->flags & FL_ONGROUND || g_Info->GetHeightGround ( g_Info->GetGroundTrace ( ) ) <= 0.01f )
					{
						if ( SDK::Interfaces::g_pPlayerMove->velocity.Length ( ) >= SDK::Interfaces::g_pPlayerMove->maxspeed * 1.2f )
						{
							if ( FramesOnGround < 2 )
							{
								cmd->buttons &= ~IN_JUMP;

								return;
							}
							else
							{
								cmd->buttons |= IN_JUMP;

								State = true;
							}
						}
						else
						{
							cmd->buttons |= IN_JUMP;

							State = true;
						}
					}
				}
				else
					cmd->buttons &= ~IN_JUMP;
			}

			void BunnyHop::ScrollEmulation ( const float &frametime, usercmd_s *cmd )
			{
				float flDistance = SDK::Interfaces::g_pEngine->pfnRandomFloat ( g_Vars.BunnyHop.ScrollDistance[0], g_Vars.BunnyHop.ScrollDistance[1] );

				if ( Distance ( frametime ) <= flDistance || SDK::Interfaces::g_pPlayerMove->flags & FL_ONGROUND )
				{
					if ( g_Vars.BunnyHop.ScrollRandFails && flDistance <= ( g_Vars.BunnyHop.ScrollDistance[0] +
						( ( g_Vars.BunnyHop.ScrollDistance[1] - g_Vars.BunnyHop.ScrollDistance[0] ) / 7.0f ) ) )
					{
						if ( FramesOnGround < 2 )
						{
							cmd->buttons &= ~IN_JUMP;

							return;
						}
					}
					else
					{
						mouse_event ( MOUSEEVENTF_WHEEL, 0, 0, g_Vars.BunnyHop.ScrollDirection > DOWN ? 120 : -120, 0 );

						State = true;
					}
				}
			}

			void BunnyHop::NoScrollEmulation ( const float &frametime, usercmd_s *cmd )
			{
				int NeedFrames = SDK::Interfaces::g_pEngine->pfnRandomLong ( 1, 2 );

				if ( PerfectJumpÑondition ( frametime ) )
				{
					if ( SDK::Interfaces::g_pPlayerMove->flags & FL_ONGROUND || g_Info->GetHeightGround ( g_Info->GetGroundTrace ( ) ) <= 0.01f )
					{
						if ( FramesOnGround < NeedFrames )
						{
							cmd->buttons &= ~IN_JUMP;

							return;
						}
						else
						{
							cmd->buttons |= IN_JUMP;

							State = true;
						}
					}
					else
					{
						cmd->buttons |= IN_JUMP;

						State = true;
					}
				}
				else
					cmd->buttons &= ~IN_JUMP;
			}

			void BunnyHop::ActiveBunnyHop ( const float &frametime, usercmd_s *cmd )
			{
				if ( inWater )
				{
					cmd->buttons |= IN_JUMP;

					return;
				}

				if ( State )
				{
					if ( g_Vars.BunnyHop.NoSlowdown || !g_Vars.BunnyHop.ScrollEmulation )
						cmd->buttons &= ~IN_JUMP;

					State = false;

					return;
				}

				if ( SDK::Interfaces::g_pPlayerMove->waterlevel >= 2 )
				{
					cmd->buttons |= IN_JUMP;

					inWater = true;

					return;
				}

				if ( g_Vars.BunnyHop.OnLadder && SDK::Interfaces::g_pPlayerMove->movetype == 5 && SDK::Interfaces::g_pPlayerMove->flFallVelocity >= 0.0f )
				{
					g_Vars.BunnyHop.ScrollEmulation ?
						mouse_event ( MOUSEEVENTF_WHEEL, 0, 0, g_Vars.BunnyHop.ScrollDirection > DOWN ? 120 : -120, 0 ) : cmd->buttons |= IN_JUMP;

					return;
				}

				g_Vars.BunnyHop.NoSlowdown ? NoSlowdown ( frametime, cmd ) :
					g_Vars.BunnyHop.ScrollEmulation ? ScrollEmulation ( frametime, cmd ) : NoScrollEmulation ( frametime, cmd );
			}

			void BunnyHop::StandUp ( usercmd_s *cmd )
			{
				if ( SDK::Interfaces::g_pPlayerMove->flFallVelocity >= g_Vars.BunnyHop.StandUpFallVelocity &&
					g_Info->GetGroundAngle ( g_Info->GetGroundTrace ( ) ) < 28.0f && !g_Info->GetFallDamage ( ) && SDK::Interfaces::g_pPlayerMove->movetype != 5 )
				{
					cmd->buttons |= IN_DUCK;
				}
			}

			void BunnyHop::Helper ( usercmd_s *cmd )
			{
				float flClientTime = SDK::Interfaces::g_pEngine->GetClientTime ( );

				if ( Scroll.ScrollJump )
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

					if ( SDK::Interfaces::g_pPlayerMove->flags & FL_ONGROUND || g_Info->GetHeightGround ( g_Info->GetGroundTrace ( ) ) <= 0.01f )
					{
						if ( g_Vars.BunnyHop.HelperNoSlowdown )
						{
							if ( SDK::Interfaces::g_pPlayerMove->velocity.Length ( ) >= SDK::Interfaces::g_pPlayerMove->maxspeed * 1.2f )
							{
								if ( FramesOnGround >= 2 )
								{
									cmd->buttons |= IN_JUMP;

									HelperActive = false;
								}
								else
								{
									cmd->buttons &= ~IN_JUMP;

									return;
								}
							}
							else
							{
								cmd->buttons |= IN_JUMP;

								HelperActive = false;
							}
						}
						else
						{
							if ( Scroll.PerfectJumpsCount >= 6 )
							{
								Scroll.PerfectJumpsCount = 0;

								if ( FramesOnGround >= 2 )
								{
									cmd->buttons |= IN_JUMP;

									HelperActive = false;
								}
								else
								{
									cmd->buttons &= ~IN_JUMP;

									return;
								}

							}

							if ( SDK::Interfaces::g_pEngine->pfnRandomLong ( 0, 100 ) <= g_Vars.BunnyHop.HelperIdealPercent )
							{
								cmd->buttons |= IN_JUMP;

								HelperActive = false;
							}
							else
							{
								if ( FramesOnGround >= 2 )
								{
									cmd->buttons |= IN_JUMP;

									HelperActive = false;
								}
								else
									cmd->buttons &= ~IN_JUMP;
							}

							if ( FramesOnGround >= 2 )
							{
								Scroll.PerfectJumpsCount = 0;
							}
							else
							{
								++Scroll.PerfectJumpsCount;
							}
						}
					}
					else
						cmd->buttons &= ~IN_JUMP;
				}

				Scroll.ScrollJump = false;
				Scroll.JumpPressed = false;
			}

			void BunnyHop::CL_CreateMove ( const float &frametime, usercmd_s *cmd )
			{
				CountingFramesOnGround ( );

				if ( Active )
				{
					ActiveBunnyHop ( frametime, cmd );

					if ( g_Vars.BunnyHop.StandUpAuto || StandUpActive )
					{
						StandUp ( cmd );
					}
				}
				else
				{
					inWater = false;

					if ( g_Vars.BunnyHop.Helper )
					{
						Helper ( cmd );
					}
				}
			}
		}
	}
}