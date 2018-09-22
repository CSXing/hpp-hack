#include "TriggerBot.h"

namespace Client
{
	namespace Functions
	{
		namespace TriggerBot
		{
			PlayerStruct Trigger::Player[33];

			int Trigger::TargetID;

			bool Trigger::Active;
			bool Trigger::TriggerActive;

			bool Trigger::FriendlyFire ( const int &Index )
			{
				return g_Vars.Trigger.FriendlyFire || g_Info->GetPlayerTeamByIndex ( Index ) != g_Info->GetPlayerTeam ( );
			}

			bool Trigger::VisibleCheck ( const int &Index )
			{
				return g_Vars.Trigger.VisibleCheck ? g_Info->GetVisibilityEntityByIndex ( Index ) : true;
			}

			void Trigger::UpdateAimHitBox ( const int &Index, cl_entity_s *Entity )
			{
				Vector vAngles ( 0.0f, Entity->angles[1], 0.0f );
				Vector vForward, vRight, vUp;

				SDK::Interfaces::g_pEngine->pfnAngleVectors ( vAngles, vForward, vRight, vUp );

				float flMaxScreenDistance = FLT_MAX;

				Vector2D Screen, Trigger;

				if ( g_Vars.TriggerWeapons[g_Info->GetWeaponID ( )].ProSpread )
				{
					Screen[0] = Spread::GetDrawSpread ( )[0];
					Screen[1] = Spread::GetDrawSpread ( )[1];
				}
				else
				{
					Screen[0] = SDK::Interfaces::g_Screen.iWidth / 2.0f - Utils::GetPunchScreen ( )[1];
					Screen[1] = SDK::Interfaces::g_Screen.iHeight / 2.0f + Utils::GetPunchScreen ( )[0];
				}

				if ( g_Vars.TriggerWeapons[g_Info->GetWeaponID ( )].OnlyHead )
				{
					Player[Index].vAimHitBox = g_Info->GetHitBoxByIndex ( Index, 11 ) + vForward + vRight + vUp;

					Player[Index].vAimHitBox[1] += 0.8f;
					Player[Index].vAimHitBox[2] -= 0.8f;

					Player[Index].HitBoxNum = 11;
				}
				else
				{
					BYTE HitBoxCheck[] = { 7, 8, 9, 10, 11 };

					for ( int i = 0; i < sizeof ( HitBoxCheck ); ++i )
					{
						Vector HitBox = g_Info->GetHitBoxByIndex ( Index, ( int )HitBoxCheck[i] ) + vForward + vRight + vUp;

						if ( HitBoxCheck[i] == 11 )
						{
							HitBox[1] += 0.8f;
							HitBox[2] -= 0.8f;
						}

						if ( HitBoxCheck[i] == 7 )
						{
							HitBox[2] -= 0.8f;
						}

						if ( Utils::CalcScreen ( HitBox, Trigger ) )
						{
							float flScreenDistance = Utils::CalcDistanceScreen ( Screen, Trigger );

							if ( flScreenDistance < flMaxScreenDistance )
							{
								flMaxScreenDistance = flScreenDistance;

								Player[Index].vAimHitBox = HitBox;

								Player[Index].HitBoxNum = HitBoxCheck[i];
							}
						}
					}
				}
			}

			void Trigger::UpdateAimInfo ( const int &Index )
			{
				cl_entity_s *Entity = SDK::Interfaces::g_pEngine->GetEntityByIndex ( Index );

				UpdateAimHitBox ( Index, Entity );

				Vector2D Trigger;

				if ( Utils::CalcScreen ( Player[Index].vAimHitBox, Trigger ) )
				{
					Vector2D Screen;

					if ( g_Vars.TriggerWeapons[g_Info->GetWeaponID ( )].ProSpread )
					{
						Screen[0] = Spread::GetDrawSpread ( )[0];
						Screen[1] = Spread::GetDrawSpread ( )[1];
					}
					else
					{
						Screen[0] = SDK::Interfaces::g_Screen.iWidth / 2.0f - Utils::GetPunchScreen ( )[1];
						Screen[1] = SDK::Interfaces::g_Screen.iHeight / 2.0f + Utils::GetPunchScreen ( )[0];
					}

					Vector uppt = Entity->origin - g_Info->GetVectorEyePosition ( );

					float FOV = 0.0f;

					switch ( Player[Index].HitBoxNum )
					{
					case 7: FOV = 1.0f * 500.0f / uppt.Length ( ); break;
					case 8: FOV = 1.0f * 500.0f / uppt.Length ( ); break;
					case 9: FOV = 1.0f * 500.0f / uppt.Length ( ); break;
					case 10: FOV = 0.7f * 500.0f / uppt.Length ( ); break;
					case 11: FOV = 0.6f * 500.0f / uppt.Length ( ); break;
					default: FOV = 0.5f * 500.0f / uppt.Length ( );
					}

					FOV = FOV / g_Info->GetFOV ( ) * SDK::Interfaces::g_Screen.iWidth / 2.0f;

					Player[Index].isFOV = Utils::CheckFOV ( Screen, Trigger, FOV );
				}
				else
					Player[Index].isFOV = false;
			}

			void Trigger::UpdatePlayerInfo ( )
			{
				if ( TargetID && !VisibleCheck ( TargetID ) )
				{
					TargetID = 0;
				}

				UpdateTargetID ( );
			}

			void Trigger::UpdateTargetID ( )
			{
				float flMaxScreenDistance = FLT_MAX;

				Vector2D Screen;

				if ( g_Vars.TriggerWeapons[g_Info->GetWeaponID ( )].ProSpread )
				{
					Screen[0] = Spread::GetDrawSpread ( )[0];
					Screen[1] = Spread::GetDrawSpread ( )[1];
				}
				else
				{
					Screen[0] = SDK::Interfaces::g_Screen.iWidth / 2.0f - Utils::GetPunchScreen ( )[1];
					Screen[1] = SDK::Interfaces::g_Screen.iHeight / 2.0f + Utils::GetPunchScreen ( )[0];
				}

				for ( int Index = 1; Index <= SDK::Interfaces::g_pEngine->GetMaxClients ( ); ++Index )
				{
					cl_entity_s* Entity = SDK::Interfaces::g_pEngine->GetEntityByIndex ( Index );

					if ( !FriendlyFire ( Index ) || !VisibleCheck ( Index ) ||
						!g_Info->GetValidationEntity ( Entity ) || g_Info->GetLocalIndex ( ) == Index )
					{
						continue;
					}

					Vector2D Trigger;

					if ( Utils::CalcScreen ( Player[Index].vAimHitBox, Trigger ) )
					{
						float flScreenDistance = Utils::CalcDistanceScreen ( Screen, Trigger );

						if ( flScreenDistance < flMaxScreenDistance )
						{
							flMaxScreenDistance = flScreenDistance;
							TargetID = Index;
						}
					}
				}
			}

			void Trigger::CL_CreateMove ( usercmd_s *cmd )
			{
				if ( !g_Info->GetWeaponClip ( ) )
				{
					return;
				}

				cl_entity_s* Entity = SDK::Interfaces::g_pEngine->GetEntityByIndex ( TargetID );

				if ( Active && g_Info->GetValidationEntity ( Entity ) )
				{
					if ( !Player[TargetID].isFOV )
					{
						return;
					}

					if ( g_Vars.Trigger.SnipersOnlyInZoom && g_Info->GetWeaponListSnipers ( ) && g_Info->GetFOV ( ) == 90 )
					{
						return;
					}

					g_Info->GetNextPrimaryAttack ( ) > 0.0f ? cmd->buttons &= ~IN_ATTACK : cmd->buttons |= IN_ATTACK;
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