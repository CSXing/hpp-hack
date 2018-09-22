#pragma once

#include "Main.h"

namespace Client
{
	struct BombStruct
	{
		float flC4Timer;
		bool isPlanted;
	};

	struct LocalStruct
	{
		BombStruct Bomb;
		Vector vForward, vPunchAngles;
		Vector vCmdViewAngles, vSpreadAngles;
		float flFrameTime, flNextPrimaryAttack;
		int WeaponID, WeaponClip;
		int Team, FOV, InReload;
		int ShotsFired;
	};

	struct PlayerStruct
	{
		hud_player_info_t Info;

		Vector vHitBox[21];
		DWORD64 isDeadTime;
		int Team;
		bool isAlive, isDead;
	};

	class Info
	{
	public:
		Info ( );

		inline void SetVectorSpreadAngles ( const Vector& vSpreadAngles ) { Local.vSpreadAngles = vSpreadAngles; }
		inline void SetVectorPunchAngles ( const Vector& vPunchAngles ) { Local.vPunchAngles = vPunchAngles; }
		inline void SetVectorForward ( const Vector& vForward ) { Local.vForward = vForward; }
		inline void SetCmdViewAngles ( const Vector& vCmdViewAngles ) { Local.vCmdViewAngles = vCmdViewAngles; }
		inline void SetPlayerIsDeadByIndex ( const int& Index, const bool& isDead ) { Player[Index].isDead = isDead; }
		inline void SetPlayerIsAliveByIndex ( const int& Index, const bool& isAlive ) { Player[Index].isAlive = isAlive; }
		inline void SetPlayerTeamByIndex ( const int& Index, const int &Team ) { Player[Index].Team = Team; }
		inline void SetNextPrimaryAttack ( const float& flNextPrimaryAttack ) { Local.flNextPrimaryAttack = flNextPrimaryAttack; }
		inline void SetInReload ( const int& InReload ) { Local.InReload = InReload; }
		inline void SetFrameTime ( const float& flFrameTime ) { Local.flFrameTime = flFrameTime; }
		inline void SetC4Timer ( const float& flC4Timer ) { Local.Bomb.flC4Timer = flC4Timer; }
		inline void SetFOV ( const int& FOV ) { Local.FOV = FOV; }
		inline void SetWeaponID ( const int& WeaponID ) { Local.WeaponID = WeaponID; }
		inline void SetWeaponClip ( const int& WeaponClip ) { Local.WeaponClip = WeaponClip; }
		inline void SetPlayerTeam ( const int& Team ) { Local.Team = Team; }
		inline void SetIsPlanted ( const bool& isPlanted ) { Local.Bomb.isPlanted = isPlanted; }

		inline hud_player_info_t GetPlayerInfoByIndex ( const int& Index ) { return Player[Index].Info; }
		inline Vector GetVectorSpreadAngles ( ) { return Local.vSpreadAngles; }
		inline Vector GetVectorPunchAngles ( ) { return Local.vPunchAngles; }
		inline Vector GetVectorForward ( ) { return Local.vForward; }
		inline Vector GetCmdViewAngles ( ) { return Local.vCmdViewAngles; }
		inline Vector GetHitBoxByIndex ( const int& Index, const int HitBoxNum ) { return Player[Index].vHitBox[HitBoxNum]; }
		inline int GetPlayerTeamByIndex ( const int& Index ) { return Player[Index].Team; }
		inline float GetNextPrimaryAttack ( ) { return Local.flNextPrimaryAttack; }
		inline int GetInReload ( ) { return Local.InReload; }
		inline float GetFrameTime ( ) { return Local.flFrameTime; }
		inline float GetC4Timer ( ) { return Local.Bomb.flC4Timer; }
		inline int GetFOV ( ) { return Local.FOV; }
		inline int GetWeaponID ( ) { return Local.WeaponID; }
		inline int GetWeaponClip ( ) { return Local.WeaponClip; }
		inline int GetPlayerTeam ( ) { return Local.Team; }
		inline int GetShotsFired ( ) { return Local.ShotsFired; }
		inline bool GetIsPlanted ( ) { return Local.Bomb.isPlanted; }

		/*locals*/
		pmtrace_t* GetGroundTrace ( );
		Vector GetVectorEyePosition ( );
		int GetLocalIndex ( );
		float GetGroundAngle ( pmtrace_t* pTrace );
		float GetHeightGround ( pmtrace_t* pTrace );
		float GetEdgeDistance ( );
		float GetDistanceToEntity ( const Vector& vOrigin );
		int GetFallDamage ( );
		bool GetAliveLocal ( );
		bool GetSlideSurface ( );
		bool GetDuckedEntity ( cl_entity_s* Entity );
		bool GetValidationEntity ( cl_entity_s* Entity );
		bool GetVisibilityEntityByIndex ( const int& Index );

		/*players*/
		pmtrace_t* GetPlayerGroundTrace ( cl_entity_s* Entity );
		float GetPlayerHeight ( cl_entity_s* Entity, pmtrace_t* pTrace );
		bool GetPlayerOnGround ( cl_entity_s* Entity );

		inline bool GetBadWeapon ( )
		{
			return GetWeaponID ( ) == WEAPONLIST_C4 || GetWeaponID ( ) == WEAPONLIST_FLASHBANG ||
				GetWeaponID ( ) == WEAPONLIST_HEGRENADE || GetWeaponID ( ) == WEAPONLIST_KNIFE || GetWeaponID ( ) == WEAPONLIST_SMOKEGRENADE;
		}

		inline bool GetWeaponListSnipers ( )
		{
			return GetWeaponID ( ) == 3 || GetWeaponID ( ) == 18 || GetWeaponID ( ) == 24 || GetWeaponID ( ) == 13;
		}

		inline bool GetWeaponListPistols ( )
		{
			return GetWeaponID ( ) == 1 || GetWeaponID ( ) == 10 || GetWeaponID ( ) == 11 ||
				GetWeaponID ( ) == 16 || GetWeaponID ( ) == 17 || GetWeaponID ( ) == 26;
		}

		inline bool GetWeaponListRifles ( )
		{
			return GetWeaponID ( ) == 7 || GetWeaponID ( ) == 8 || GetWeaponID ( ) == 12 || GetWeaponID ( ) == 14 || GetWeaponID ( ) == 15 ||
				GetWeaponID ( ) == 19 || GetWeaponID ( ) == 20 || GetWeaponID ( ) == 21 || GetWeaponID ( ) == 22 || GetWeaponID ( ) == 23 ||
				GetWeaponID ( ) == 27 || GetWeaponID ( ) == 28 || GetWeaponID ( ) == 30;
		}

		void GetHitBoxOrigin ( cl_entity_s* Entity );

		void BulletControl ( usercmd_s* cmd );

		void UpdateDeadInfoByIndex ( const int& Index );
		void UpdateInfoByIndex ( const int& Index );

	private:
		LocalStruct Local;
		PlayerStruct Player[33];
	};

	extern Info *g_Info;
}