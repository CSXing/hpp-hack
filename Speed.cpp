#include "Speed.h"

namespace Client
{
	namespace Functions
	{
		namespace Misc
		{
			bool Speed::BoostActive;
			bool Speed::SlowmotionActive;

			void Speed::AdjustSpeed ( double Speed )
			{
				static double LastSpeed = 1.0;

				if ( !Engine::Speed )
					Engine::Speed = Engine::SpeedPtr;

				if ( Speed != LastSpeed )
				{
					*( double* )Engine::Speed = Speed * 1000.0;

					LastSpeed = Speed;
				}
			}

			void Speed::Helper ( )
			{
				if ( SDK::Interfaces::g_pPlayerMove->flags & FL_ONGROUND )
				{
					AdjustSpeed ( g_Vars.Speed.HelperGround );
				}
				else if ( SDK::Interfaces::g_pPlayerMove->movetype == 5 )
				{
					AdjustSpeed ( g_Vars.Speed.HelperLadder );
				}
				else
				{
					AdjustSpeed ( g_Vars.Speed.HelperFly );
				}
			}

			void Speed::Boost ( )
			{
				if ( g_Vars.Speed.Boost > 1.0f )
					AdjustSpeed ( g_Vars.Speed.Boost );
				else
					AdjustSpeed ( 1.0 );
			}

			void Speed::Slowmo ( )
			{
				if ( g_Vars.Speed.Slowmo < 1.0f )
					AdjustSpeed ( g_Vars.Speed.Slowmo );
				else
					AdjustSpeed ( 1.0 );
			}

			void Speed::CL_CreateMove ( )
			{
				if ( g_Vars.Functions.Speed )
				{
					g_Vars.Speed.Helper ? Helper ( ) : AdjustSpeed ( g_Vars.Speed.Player );

					if ( g_Vars.Speed.Engine )
						*Engine::g_Net += g_Vars.Speed.Engine / 1000.0;

					if ( BoostActive ) Boost ( );
					if ( SlowmotionActive ) Slowmo ( );
				}
				else
				{
					AdjustSpeed ( 1.0 );

					*Engine::g_Net += 0.0;
				}
			}
		}
	}
}