#pragma once

#include "Main.h"

namespace Client
{
	namespace Functions
	{
		namespace AimBot
		{
			class AutoPistol
			{
			public:
				static void CL_CreateMove ( usercmd_s *cmd );

			private:
				static DWORD64 dwTime;
				static bool FirstBullet;
			};
		}
	}
}