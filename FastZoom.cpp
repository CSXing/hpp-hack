#include "FastZoom.h"

namespace Client
{
	namespace Functions
	{
		namespace AimBot
		{
			DWORD64 FastZoom::dwTime;

			bool FastZoom::QuickSwitch;

			void FastZoom::CL_CreateMove ( usercmd_s *cmd )
			{
				if ( g_Info->GetWeaponListSnipers ( ) )
				{
					if ( cmd->buttons & IN_ATTACK && g_Info->GetWeaponClip ( ) )
					{
						g_Info->GetFOV ( ) == 90 ? cmd->buttons |= IN_ATTACK2 : QuickSwitch = true;

						if ( GetTickCount64 ( ) - dwTime < g_Vars.FastZoom.Delay )
						{
							cmd->buttons &= ~IN_ATTACK;
						}
						else
						{
							dwTime = GetTickCount64 ( );

							if ( g_Vars.FastZoom.QuickSwitch && ( g_Info->GetWeaponID ( ) == WEAPONLIST_AWP || g_Info->GetWeaponID ( ) == WEAPONLIST_SCOUT ) )
							{
								if ( QuickSwitch && g_Info->GetShotsFired ( ) >= 1 && g_Info->GetNextPrimaryAttack ( ) > 0.0f )
								{
									SDK::Interfaces::g_pEngine->pfnClientCmd ( "slot3;wait;slot1" );

									QuickSwitch = false;
								}
							}
						}
					}
				}
			}
		}
	}
}