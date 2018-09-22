#include "AutoPistol.h"

namespace Client
{
	namespace Functions
	{
		namespace AimBot
		{
			DWORD64 AutoPistol::dwTime;

			bool AutoPistol::FirstBullet;

			void AutoPistol::CL_CreateMove ( usercmd_s *cmd )
			{
				if ( g_Info->GetWeaponListPistols ( ) )
				{
					if ( cmd->buttons & IN_ATTACK )
					{
						if ( FirstBullet )
						{
							cmd->buttons |= IN_ATTACK;

							FirstBullet = false;
						}

						if ( GetTickCount64 ( ) - dwTime < g_Vars.AutoPistol.Delay && cmd->buttons & IN_ATTACK )
							cmd->buttons &= ~IN_ATTACK;
						else
							dwTime = GetTickCount64 ( );
					}
					else
						FirstBullet = true;
				}
			}
		}
	}
}