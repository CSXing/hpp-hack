#include "Recoil.h"

namespace Client
{
	namespace Functions
	{
		namespace AimBot
		{
			void Recoil::CL_CreateMove ( usercmd_s *cmd )
			{
				static Vector OldPunchAngle;

				if ( cmd->buttons & IN_ATTACK && g_Info->GetWeaponClip ( ) && g_Info->GetWeaponListRifles ( ) )
				{
					Vector PunchAngle, ViewAngles;

					PunchAngle[0] = g_Info->GetVectorPunchAngles ( )[0] * g_Vars.Recoil.Y;
					PunchAngle[1] = g_Info->GetVectorPunchAngles ( )[1] * g_Vars.Recoil.X;

					ViewAngles = cmd->viewangles;
					ViewAngles += OldPunchAngle;
					ViewAngles -= PunchAngle;

					Vector SmoothAngles;

					Utils::SmoothAimAngles ( cmd->viewangles, ViewAngles, SmoothAngles, g_Vars.Recoil.Smooth );

					if ( PunchAngle < OldPunchAngle )
					{
						if ( g_Info->GetShotsFired ( ) >= g_Vars.Recoil.BulletStart && !Weapons::GetIsFOVByIndex ( Weapons::GetTargetID ( ) ) )
						{
							ClampAngles ( SmoothAngles );

							cmd->viewangles = SmoothAngles;

							SDK::Interfaces::g_pEngine->SetViewAngles ( cmd->viewangles );
						}
					}

					OldPunchAngle = PunchAngle;
				}
				else
					OldPunchAngle = Vector ( 0.0f );
			}
		}
	}
}