#pragma once

#include "Main.h"

namespace Client
{
	namespace Functions
	{
		namespace TriggerBot
		{
			struct PlayerStruct
			{
				Vector vAimHitBox;
				int HitBoxNum;
				bool isFOV;
			};

			class Trigger
			{
			public:
				static bool Active;

				inline static Vector GetAimHitBoxByIndex ( const int &Index )
				{
					return Player[Index].vAimHitBox;
				}

				inline static int GetHitBoxNumByIndex ( const int &Index )
				{
					return Player[Index].HitBoxNum;
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
				static bool TriggerActive;

				static void UpdateAimHitBox ( const int &Index, cl_entity_s *Entity );
				static void UpdateTargetID ( );
			};
		}
	}
}