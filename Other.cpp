#include "Other.h"

namespace Client
{
	namespace Functions
	{
		namespace Visuals
		{
			void Other::DrawAimSpot ( )
			{
				cl_entity_s* Entity = SDK::Interfaces::g_pEngine->GetEntityByIndex ( AimBot::Weapons::GetTargetID ( ) );

				if ( AimBot::Weapons::FriendlyFire ( AimBot::Weapons::GetTargetID ( ) ) &&
					AimBot::Weapons::VisibleCheck ( AimBot::Weapons::GetTargetID ( ) ) &&
					g_Info->GetValidationEntity ( Entity ) )
				{
					Vector2D vAim;

					if ( Utils::CalcScreen ( AimBot::Weapons::GetAimHitBoxByIndex ( AimBot::Weapons::GetTargetID ( ) ), vAim ) )
					{
						Vector uppt = AimBot::Weapons::GetAimHitBoxByIndex ( AimBot::Weapons::GetTargetID ( ) ) - g_Info->GetVectorEyePosition ( );

						float Length = uppt.Length ( );

						int size = int ( 3800.0f / Length );

						int x1 = ( int )vAim[0];
						int y1 = int ( vAim[1] - size / 2 );

						int x2 = int ( vAim[0] - size / 2 );
						int y2 = ( int )vAim[1];

						Renderer::g_Drawing->FillArea ( x1, y1, 1, size, 0, 255, 200, 255 );
						Renderer::g_Drawing->FillArea ( x2, y2, size, 1, 0, 255, 200, 255 );
					}
				}
			}

			void Other::DrawAimFOV ( )
			{
				float FOV = 0.0f;

				if ( g_Vars.Aim.FOVDistance && AimBot::Weapons::GetTargetID ( ) )
				{
					cl_entity_s *Entity = SDK::Interfaces::g_pEngine->GetEntityByIndex ( AimBot::Weapons::GetTargetID ( ) );

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

				int x = SDK::Interfaces::g_Screen.iWidth / 2 - ( int )Utils::GetPunchScreen ( )[1];
				int y = SDK::Interfaces::g_Screen.iHeight / 2 + ( int )Utils::GetPunchScreen ( )[0];

				Renderer::g_Drawing->Circle ( x, y, ( int )FOV, 100, 1, 255, 255, 255, 255 );
			}

			void Other::DrawPunch ( )
			{
				int x = SDK::Interfaces::g_Screen.iWidth / 2 - ( int )Utils::GetPunchScreen ( )[1] - 1;
				int y = SDK::Interfaces::g_Screen.iHeight / 2 + ( int )Utils::GetPunchScreen ( )[0] - 1;

				Renderer::g_Drawing->FillArea ( x, y, 3, 3, 255, 0, 0, 255 );
			}

			void Other::DrawSpread ( )
			{
				int x = ( int )Spread::GetDrawSpread ( )[0] - 1;
				int y = ( int )Spread::GetDrawSpread ( )[1] - 1;

				Renderer::g_Drawing->FillArea ( x, y, 3, 3, 255, 180, 0, 255 );
			}

			void Other::StatusAimBot ( )
			{
				bool AimBotActive = g_Vars.Aim.Enable && g_Vars.Weapons[g_Info->GetWeaponID ( )].Aim;

				int x = AimBotActive ? SDK::Interfaces::g_Screen.iWidth - 135 : SDK::Interfaces::g_Screen.iWidth - 143;
				int y = 220;

				Renderer::g_Fonts->Print ( x, y, ( BYTE )g_Vars.Other.FontColor[0], ( BYTE )g_Vars.Other.FontColor[1], ( BYTE )g_Vars.Other.FontColor[2], 
					( BYTE )g_Vars.Other.FontColor[3], g_Vars.Other.FontOutline ? FL_OUTLINE : FL_NONE, AimBotActive ? "AIMBOT: ENABLED" : "AIMBOT: DISABLED" );
			}

			void Other::StatusTriggerBot ( )
			{
				bool TriggerActive = g_Vars.Trigger.Enable && g_Vars.TriggerWeapons[g_Info->GetWeaponID ( )].Trigger &&TriggerBot::Trigger::Active;

				int x = TriggerActive ? SDK::Interfaces::g_Screen.iWidth - 167 : SDK::Interfaces::g_Screen.iWidth - 175;
				int y = 235;

				Renderer::g_Fonts->Print ( x, y, ( BYTE )g_Vars.Other.FontColor[0], ( BYTE )g_Vars.Other.FontColor[1], ( BYTE )g_Vars.Other.FontColor[2],
					( BYTE )g_Vars.Other.FontColor[3], g_Vars.Other.FontOutline ? FL_OUTLINE : FL_NONE, TriggerActive ? "TRIGGERBOT: ENABLED" : "TRIGGERBOT: DISABLED" );
			}

			void Other::HUD_Redraw ( )
			{
				if ( g_Info->GetAliveLocal ( ) && !g_Info->GetBadWeapon ( ) )
				{
					if ( g_Vars.Functions.Weapons && g_Vars.Aim.Enable )
					{
						if ( g_Vars.Weapons[g_Info->GetWeaponID ( )].Aim )
						{
							if ( g_Vars.Other.DrawAimSpot ) DrawAimSpot ( );
							if ( g_Vars.Other.DrawAimFOV ) DrawAimFOV ( );
						}

						if ( g_Vars.Other.StatusAimBot ) StatusAimBot ( );
					}

					if ( g_Vars.Functions.TriggerWeapons && g_Vars.Trigger.Enable )
					{
						if ( g_Vars.Other.StatusTriggerBot ) StatusTriggerBot ( );
					}

					if ( g_Vars.Other.DrawPunch ) DrawPunch ( );
					if ( g_Vars.Other.DrawSpread ) DrawSpread ( );
				}
			}
		}
	}
}