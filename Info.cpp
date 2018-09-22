#include "Info.h"

namespace Client
{
	Info::Info ( )
	{
		Local.flFrameTime = 0.01f;
		Local.flNextPrimaryAttack = 0.0f;
		Local.Bomb.flC4Timer = 0.0f;

		Local.WeaponID = 0;
		Local.WeaponClip = -1;
		Local.Team = 0;
		Local.FOV = 90;
		Local.InReload = 0;

		Local.Bomb.isPlanted = false;

		for ( int PlayerID = 0; PlayerID <= 32; ++PlayerID )
		{
			Player[PlayerID].Team = 0;

			Player[PlayerID].isAlive = false;
		}
	}

	Vector Info::GetVectorEyePosition ( )
	{
		return SDK::Interfaces::g_pPlayerMove->origin + SDK::Interfaces::g_pPlayerMove->view_ofs;
	}

	int Info::GetLocalIndex ( )
	{
		cl_entity_s* Local = SDK::Interfaces::g_pEngine->GetLocalPlayer ( );

		return Local->index;
	}

	bool Info::GetAliveLocal ( )
	{
		cl_entity_s* Local = SDK::Interfaces::g_pEngine->GetLocalPlayer ( );

		return Local && Local->player && Local->curstate.movetype != 6 && Local->curstate.movetype;
	}

	pmtrace_t* Info::GetGroundTrace ( )
	{
		Vector vOrigin ( SDK::Interfaces::g_pPlayerMove->origin[0], SDK::Interfaces::g_pPlayerMove->origin[1], -4096.0f );

		return SDK::Interfaces::g_pEngine->PM_TraceLine ( SDK::Interfaces::g_pPlayerMove->origin,
			vOrigin, 1, ( SDK::Interfaces::g_pPlayerMove->flags & FL_DUCKING ) ? 1 : 0, -1 );
	}

	float Info::GetGroundAngle ( pmtrace_t* pTrace )
	{
		return acosf ( pTrace->plane.normal[2] ) / M_PI_F * 180.0f;
	}

	float Info::GetHeightGround ( pmtrace_t* pTrace )
	{
		float Height = SDK::Interfaces::g_pPlayerMove->origin[2] - pTrace->endpos[2];

		for ( int Index = 0; Index < SDK::Interfaces::g_pEngine->GetMaxClients ( ); ++Index )
		{
			cl_entity_s* Entity = SDK::Interfaces::g_pEngine->GetEntityByIndex ( Index );

			if ( GetValidationEntity ( Entity ) && Index != GetLocalIndex ( ) )
			{
				bool OnPlayer = abs ( SDK::Interfaces::g_pPlayerMove->origin[0] - Entity->origin[0] ) <= 32.0f &&
					abs ( SDK::Interfaces::g_pPlayerMove->origin[1] - Entity->origin[1] ) <= 32.0f &&
					SDK::Interfaces::g_pPlayerMove->origin[2] > Entity->origin[2];

				if ( OnPlayer )
				{
					Height += GetPlayerHeight ( Entity, GetPlayerGroundTrace ( Entity ) );
					Height -= GetDuckedEntity ( Entity ) ? 49.991f : 72.031f;

					if ( SDK::Interfaces::g_pPlayerMove->flags & FL_ONGROUND || ( GetDuckedEntity ( Entity ) && Height <= 0.001f ) )
					{
						Height = 0.0f;
					}
				}
			}
		}

		return Height;
	}

	float Info::GetEdgeDistance ( )
	{
		float mind = 250.0f;

		if ( GetGroundAngle ( GetGroundTrace ( ) ) )
			return 0.0f;

		TraceEdge ( -1.0f, 0.0f );
		TraceEdge ( 1.0f, 0.0f );
		TraceEdge ( 0.0f, 1.0f );
		TraceEdge ( 0.0f, -1.0f );
		TraceEdge ( -1.0f, -1.0f );
		TraceEdge ( 1.0f, 1.0f );
		TraceEdge ( 1.0f, -1.0f );
		TraceEdge ( -1.0f, 1.0f );

		return mind;
	}

	int Info::GetFallDamage ( )
	{
		float flFallDamage1 = Utils::EndSpeed ( SDK::Interfaces::g_pPlayerMove->flFallVelocity,
			SDK::Interfaces::g_pEngine->pfnGetGravity ( ), 0.01f, GetHeightGround ( GetGroundTrace ( ) ) ) - PLAYER_MAX_SAFE_FALL_SPEED;

		float flFallDamage2 = flFallDamage1 * DAMAGE_FOR_FALL_SPEED < 0.0f ? 0.0f : flFallDamage1 * DAMAGE_FOR_FALL_SPEED;

		if ( flFallDamage2 - ( int )flFallDamage2 >= 0.01f )
		{
			++flFallDamage2;
		}

		return ( int )flFallDamage2;
	}

	bool Info::GetSlideSurface ( )
	{
		return GetGroundAngle ( GetGroundTrace ( ) ) > 45.0f && GetHeightGround ( GetGroundTrace ( ) ) < 1.0f;
	}

	bool Info::GetDuckedEntity ( cl_entity_s* Entity )
	{
		return Entity->curstate.maxs[2] - Entity->curstate.mins[2] < 54.0f;
	}

	bool Info::GetValidationEntity ( cl_entity_s* Entity )
	{
		cl_entity_s *Local = SDK::Interfaces::g_pEngine->GetLocalPlayer ( );

		return Entity && ( g_Vars.Main.PlayerValidCheck >= 2 ? ( Entity->player && !Player[Entity->index].isDead ) : Player[Entity->index].isAlive ) &&
			!( Entity->curstate.messagenum < Local->curstate.messagenum ) && !( Local->curstate.iuser1 == 4 && Local->curstate.iuser2 == Entity->index );
	}

	float Info::GetDistanceToEntity ( const Vector& vOrigin )
	{
		return floorf ( sqrtf ( POW ( abs ( vOrigin[0] - SDK::Interfaces::g_pPlayerMove->origin[0] ) ) +
			POW ( abs ( vOrigin[1] - SDK::Interfaces::g_pPlayerMove->origin[1] ) ) +
			POW ( abs ( vOrigin[2] - SDK::Interfaces::g_pPlayerMove->origin[2] ) ) ) - 32.0f );
	}

	bool Info::GetVisibilityEntityByIndex ( const int& Index )
	{
		return Utils::PathFree ( Player[Index].vHitBox[11] );
	}

	pmtrace_t* Info::GetPlayerGroundTrace ( cl_entity_s* Entity )
	{
		Vector vOrigin ( Entity->origin[0], Entity->origin[1], -4096.0f );

		return SDK::Interfaces::g_pEngine->PM_TraceLine ( Entity->origin, vOrigin, 1, GetDuckedEntity ( Entity ) ? 1 : 0, -1 );
	}

	float Info::GetPlayerHeight ( cl_entity_s* Entity, pmtrace_t* pTrace )
	{
		float PlayerHeight = Entity->origin[2] - pTrace->endpos[2];

		if ( PlayerHeight < 0.0f )
			PlayerHeight = 0.0f;

		return PlayerHeight;
	}

	bool Info::GetPlayerOnGround ( cl_entity_s* Entity )
	{
		float PlayerHeight = GetPlayerHeight ( Entity, GetPlayerGroundTrace ( Entity ) );

		return PlayerHeight <= 1.0f;
	}

	void Info::UpdateDeadInfoByIndex ( const int& Index )
	{
		if ( Player[Index].isDead )
		{
			if ( GetTickCount64 ( ) >= Player[Index].isDeadTime + 6000 )
			{
				Player[Index].isDead = false;
			}
		}
		else
			Player[Index].isDeadTime = GetTickCount64 ( );
	}

	void Info::UpdateInfoByIndex ( const int& Index )
	{
		SDK::Interfaces::g_pEngine->pfnGetPlayerInfo ( Index, &Player[Index].Info );

		if ( g_Vars.Functions.Weapons && g_Vars.Aim.Enable && g_Vars.Weapons[GetWeaponID ( )].Aim && !GetBadWeapon ( ) && GetAliveLocal ( ) )
			Functions::AimBot::Weapons::UpdateAimInfo ( Index );

		if ( g_Vars.Functions.TriggerWeapons && g_Vars.Trigger.Enable && !GetBadWeapon ( ) && GetAliveLocal ( ) )
			Functions::TriggerBot::Trigger::UpdateAimInfo ( Index );
	}

	void Info::GetHitBoxOrigin ( cl_entity_s* Entity )
	{
		Vector vBBMin, vBBMax;

		typedef float BoneMatrix_t[MAXSTUDIOBONES][3][4];

		model_s *Model = SDK::Interfaces::g_pStudio->SetupPlayerModel ( Entity->index );
		studiohdr_t* StudioHeader = ( studiohdr_t* )SDK::Interfaces::g_pStudio->Mod_Extradata ( Model );
		BoneMatrix_t* BoneMatrix = ( BoneMatrix_t* )SDK::Interfaces::g_pStudio->StudioGetBoneTransform ( );
		mstudiobbox_t* HitBox = ( mstudiobbox_t* )( ( BYTE* )StudioHeader + StudioHeader->hitboxindex );

		for ( int i = 0; i < StudioHeader->numhitboxes; ++i )
		{
			VectorTransform ( HitBox[i].bbmin, ( *BoneMatrix )[HitBox[i].bone], vBBMin );
			VectorTransform ( HitBox[i].bbmax, ( *BoneMatrix )[HitBox[i].bone], vBBMax );

			Player[Entity->index].vHitBox[i] = ( vBBMax + vBBMin ) / 2.0f;
		}
	}

	void Info::BulletControl ( usercmd_s* cmd )
	{
		static int SaveiClip;

		if ( cmd->buttons & IN_ATTACK )
		{
			if ( !g_Info->GetWeaponClip ( ) )
			{
				Local.ShotsFired = 0;

				return;
			}

			if ( !Local.ShotsFired && ( SaveiClip - g_Info->GetWeaponClip ( ) ) < 0 )
				SaveiClip = g_Info->GetWeaponClip ( ) + 1;

			Local.ShotsFired = SaveiClip - g_Info->GetWeaponClip ( );
		}
		else
		{
			SaveiClip = g_Info->GetWeaponClip ( );
			Local.ShotsFired = 0;
		}
	}

	Info *g_Info = nullptr;
}