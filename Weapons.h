#pragma once

#include "Main.h"

namespace Client
{
	namespace Functions
	{
		namespace AimBot
		{
			struct PlayerStruct
			{
				Vector vAimHitBox;
				bool isFOV;
			};

			class Weapons
			{
			public:
				inline static int GetTargetID ( )
				{
					return TargetID;
				}

				inline static Vector GetAimHitBoxByIndex ( const int &Index )
				{
					return Player[Index].vAimHitBox;
				}

				inline static bool GetIsFOVByIndex ( const int &Index )
				{
					return Player[Index].isFOV;
				}

				static bool FriendlyFire ( const int &Index );
				static bool VisibleCheck ( const int &Index );

				static void UpdateAimInfo ( const int &Index );
				static void UpdatePlayerInfo ( );

				static void CL_CreateMove ( usercmd_s *cmd );

			private:
				static PlayerStruct Player[33];

				static int TargetID;			
				static bool AimActive;

				static Vector GetPrediction ( cl_entity_s *Entity );

				static void UpdateAimHitBox ( const int &Index, cl_entity_s *Entity );
				static void UpdateTargetID ( );
			};
		}
	}
}