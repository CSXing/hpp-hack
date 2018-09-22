#include "Weapons.h"

namespace Client
{
	namespace Functions
	{
		namespace AimBot
		{
			PlayerStruct Weapons::Player[33];

			int Weapons::TargetID;
			bool Weapons::AimActive;

			bool Weapons::FriendlyFire ( const int &Index )
			{
				return g_Vars.Aim.FriendlyFire || g_Info->GetPlayerTeamByIndex ( Index ) != g_Info->GetPlayerTeam ( );
			}

			bool Weapons::VisibleCheck ( const int &Index )
			{
				return g_Vars.Aim.VisibleCheck ? g_Info->GetVisibilityEntityByIndex ( Index ) : true;
			}

			Vector Weapons::GetPrediction ( cl_entity_s *Entity )
			{
				Vector vVelocity = Entity->curstate.origin - Entity->prevstate.origin;

				float flFrameTime = Entity->curstate.animtime - Entity->prevstate.animtime;

				if ( !flFrameTime )
				{
					flFrameTime = g_Info->GetFrameTime ( );
				}

				return vVelocity * flFrameTime * ( g_Info->GetShotsFired ( ) >= g_Vars.Weapons[g_Info->GetWeaponID ( )].BulletControl[0] ?
					g_Vars.Weapons[g_Info->GetWeaponID ( )].RecoilPrediction : g_Vars.Weapons[g_Info->GetWeaponID ( )].Prediction ) * 100.0f;
			}

			void Weapons::UpdateAimHitBox ( const int &Index, cl_entity_s *Entity )
			{
				Vector vAngles ( 0.0f, Entity->angles[1], 0.0f );
				Vector vForward, vRight, vUp;

				SDK::Interfaces::g_pEngine->pfnAngleVectors ( vAngles, vForward, vRight, vUp );

				if ( g_Vars.Weapons[g_Info->GetWeaponID ( )].HitBoxNearest )
				{
					float flMaxScreenDistance = FLT_MAX;

					Vector2D Screen = Utils::GetScreen ( );

					Screen[1] = g_Info->GetShotsFired ( ) >= g_Vars.Weapons[g_Info->GetWeaponID ( )].BulletControl[0] ?
						Screen[1] + Utils::GetPunchScreen ( )[0] : Screen[1] - Utils::GetPunchScreen ( )[0];

					Vector2D Aim;

					BYTE HitBoxCheck[] = { 7, 8, 9, 11 };

					for ( int i = 0; i < sizeof ( HitBoxCheck ); ++i )
					{
						Vector HitBox = g_Info->GetHitBoxByIndex ( Index, ( int )HitBoxCheck[i] ) + GetPrediction ( Entity ) + vForward + vRight + vUp;

						if ( Utils::CalcScreen ( HitBox, Aim ) )
						{
							float flScreenDistance = Utils::CalcDistanceScreen ( Screen, Aim );

							if ( flScreenDistance < flMaxScreenDistance )
							{
								flMaxScreenDistance = flScreenDistance;

								Player[Index].vAimHitBox = HitBox;

								if ( HitBoxCheck[i] == 11 )
								{
									Player[Index].vAimHitBox[1] += 0.8f;
									Player[Index].vAimHitBox[2] -= 0.8f;
								}
							}
						}
					}
				}
				else
				{
					Player[Index].vAimHitBox = g_Info->GetHitBoxByIndex ( Index, g_Vars.Weapons[g_Info->GetWeaponID ( )].HitBox ) + 
						GetPrediction ( Entity ) + vForward + vRight + vUp;

					if ( g_Vars.Weapons[g_Info->GetWeaponID ( )].HitBox == 11 )
					{
						Player[Index].vAimHitBox[1] += 0.8f;
						Player[Index].vAimHitBox[2] -= 0.8f;
					}
				}
			}

			void Weapons::UpdateAimInfo ( const int &Index )
			{
				cl_entity_s *Entity = SDK::Interfaces::g_pEngine->GetEntityByIndex ( Index );

				UpdateAimHitBox ( Index, Entity );

				Vector2D vAim;

				if ( Utils::CalcScreen ( Player[Index].vAimHitBox, vAim ) )
				{
					float FOV = 0.0f;

					Vector2D Screen = Utils::GetScreen ( );

					Screen[0] -= Utils::GetPunchScreen ( )[1];
					Screen[1] += Utils::GetPunchScreen ( )[0];

					if ( g_Vars.Aim.FOVDistance )
					{
						Vector uppt = Entity->origin - g_Info->GetVectorEyePosition ( );

						FOV = g_Info->GetShotsFired ( ) >= g_Vars.Weapons[g_Info->GetWeaponID ( )].BulletControl[0] ?
							g_Vars.Weapons[g_Info->GetWeaponID ( )].RecoilFOV : g_Vars.Weapons[g_Info->GetWeaponID ( )].FOV * 500.0f / uppt.Length ( );

						if ( g_Info->GetShotsFired ( ) < g_Vars.Weapons[g_Info->GetWeaponID ( )].BulletControl[0] )
						{
							if ( FOV > g_Vars.Weapons[g_Info->GetWeaponID ( )].FOV * 3.0f )
								FOV = g_Vars.Weapons[g_Info->GetWeaponID ( )].FOV * 3.0f;

							if ( FOV < g_Vars.Weapons[g_Info->GetWeaponID ( )].FOV / 2.0f )
								FOV = g_Vars.Weapons[g_Info->GetWeaponID ( )].FOV / 2.0f;
						}
					}
					else
					{
						FOV = g_Info->GetShotsFired ( ) >= g_Vars.Weapons[g_Info->GetWeaponID ( )].BulletControl[0] ?
							g_Vars.Weapons[g_Info->GetWeaponID ( )].RecoilFOV : g_Vars.Weapons[g_Info->GetWeaponID ( )].FOV;
					}

					FOV = FOV / g_Info->GetFOV ( ) * SDK::Interfaces::g_Screen.iWidth / 2.0f;

					Player[Index].isFOV = Utils::CheckFOV ( Screen, vAim, FOV );
				}
				else
					Player[Index].isFOV = false;
			}

			void Weapons::UpdateTargetID ( )
			{
				float flMaxScreenDistance = FLT_MAX;

				Vector2D Screen = Utils::GetScreen ( );

				Screen[0] -= Utils::GetPunchScreen ( )[1] / 2.0f;
				Screen[1] += Utils::GetPunchScreen ( )[0] / 2.0f;

				for ( int Index = 1; Index <= SDK::Interfaces::g_pEngine->GetMaxClients ( ); ++Index )
				{
					cl_entity_s* Entity = SDK::Interfaces::g_pEngine->GetEntityByIndex ( Index );

					if ( !FriendlyFire ( Index ) || !VisibleCheck ( Index ) ||
						!g_Info->GetValidationEntity ( Entity ) || g_Info->GetLocalIndex ( ) == Index )
					{
						continue;
					}

					Vector2D Aim;

					if ( Utils::CalcScreen ( Player[Index].vAimHitBox, Aim ) )
					{
						float flScreenDistance = Utils::CalcDistanceScreen ( Screen, Aim );

						if ( flScreenDistance < flMaxScreenDistance )
						{
							flMaxScreenDistance = flScreenDistance;
							TargetID = Index;
						}
					}
				}
			}

			void Weapons::UpdatePlayerInfo ( )
			{
				static DWORD64 dwKillDelay;

				if ( TargetID && !VisibleCheck ( TargetID ) )
				{
					TargetID = 0;
				}

				if ( g_Vars.Aim.KillDelay <= 0 || ( ( dwKillDelay + g_Vars.Aim.KillDelay ) <= GetTickCount64 ( ) && !AimActive ) )
				{
					dwKillDelay = 0;

					AimActive = true;
				}

				if ( TargetID && AimActive )
				{
					cl_entity_s* Entity = SDK::Interfaces::g_pEngine->GetEntityByIndex ( TargetID );

					if ( !g_Info->GetValidationEntity ( Entity ) && AimActive && g_Vars.Aim.KillDelay )
					{
						if ( !dwKillDelay )
						{
							dwKillDelay = GetTickCount64 ( );

							AimActive = false;
						}
					}

					UpdateTargetID ( );
				}
				else
					UpdateTargetID ( );
			}

			void Weapons::CL_CreateMove ( usercmd_s *cmd )
			{
				Vector vAimAngles, vSmoothAngles;

				static DWORD64 dwDelay;

				Utils::VectorAngles ( Player[TargetID].vAimHitBox - g_Info->GetVectorEyePosition ( ), vAimAngles );

				cl_entity_s* Entity = SDK::Interfaces::g_pEngine->GetEntityByIndex ( TargetID );

				if ( g_Vars.Aim.FlashCheck && Visuals::NoFlash::GetFlashedPercentage ( ) > 80 )
				{
					return;
				}

				if ( g_Info->GetShotsFired ( ) >= g_Vars.Weapons[g_Info->GetWeaponID ( )].BulletControl[1] ||
					!g_Info->GetWeaponClip ( ) || g_Info->GetInReload ( ) )
				{
					return;
				}

				if ( !( cmd->buttons & IN_ATTACK ) )
				{
					dwDelay = GetTickCount64 ( );
				}

				if ( cmd->buttons & IN_ATTACK && g_Info->GetValidationEntity ( Entity ) && AimActive )
				{
					if ( !Player[TargetID].isFOV )
					{
						return;
					}

					if ( g_Info->GetShotsFired ( ) >= g_Vars.Weapons[g_Info->GetWeaponID ( )].BulletControl[0] )
					{
						Vector vPunchAngles = g_Info->GetVectorPunchAngles ( ) * g_Vars.Weapons[g_Info->GetWeaponID ( )].Recoil;

						vPunchAngles[2] = 0.0f;
						vAimAngles -= vPunchAngles;

						ClampAngles ( vAimAngles );
					}

					if ( g_Vars.Aim.Silent )
					{
						ClampAngles ( vAimAngles );

						Utils::MakeAngle ( vAimAngles, cmd );
					}
					else
					{
						if ( g_Vars.Weapons[g_Info->GetWeaponID ( )].DelayType <= 1 )
						{
							if ( GetTickCount64 ( ) - dwDelay <= g_Vars.Weapons[g_Info->GetWeaponID ( )].Delay )
							{
								cmd->buttons &= ~IN_ATTACK;
							}
						}
						else if ( g_Vars.Weapons[g_Info->GetWeaponID ( )].DelayType == 2 )
						{
							if ( ( GetTickCount64 ( ) - dwDelay <= g_Vars.Weapons[g_Info->GetWeaponID ( )].Delay ) &&
								!TriggerBot::Trigger::GetIsFOVByIndex ( TargetID ) )
							{
								cmd->buttons &= ~IN_ATTACK;
							}
						}
						else if ( g_Vars.Weapons[g_Info->GetWeaponID ( )].DelayType >= 3 )
						{
							if ( !TriggerBot::Trigger::GetIsFOVByIndex ( TargetID ) )
							{
								cmd->buttons &= ~IN_ATTACK;
							}
						}

						if ( g_Info->GetShotsFired ( ) >= g_Vars.Weapons[g_Info->GetWeaponID ( )].BulletControl[0] )
						{
							if ( g_Vars.Weapons[g_Info->GetWeaponID ( )].RecoilSmooth >= 1.0f )
							{
								Utils::SmoothAimAngles ( cmd->viewangles, vAimAngles, vSmoothAngles, g_Vars.Weapons[g_Info->GetWeaponID ( )].RecoilSmooth );
							}
							else
							{
								vSmoothAngles = vAimAngles;
							}
						}
						else
						{
							if ( g_Vars.Weapons[g_Info->GetWeaponID ( )].Smooth >= 1.0f )
							{
								Utils::SmoothAimAngles ( cmd->viewangles, vAimAngles, vSmoothAngles, g_Vars.Weapons[g_Info->GetWeaponID ( )].Smooth );
							}
							else
							{
								vSmoothAngles = vAimAngles;
							}
						}

						ClampAngles ( vSmoothAngles );

						cmd->viewangles = vSmoothAngles;

						SDK::Interfaces::g_pEngine->SetViewAngles ( cmd->viewangles );
					}
				}
				else
				{
					Player[TargetID].isFOV = false;

					TargetID = 0;
				}
			}
		}
	}
}