#include "UserMsg.h"

using namespace Client::Functions;

pfnUserMsgHook pScoreAtrrib = nullptr;
pfnUserMsgHook pResetHUD = nullptr;
pfnUserMsgHook pSetFOV = nullptr;
pfnUserMsgHook pTeamInfo = nullptr;
pfnUserMsgHook pCurWeapon = nullptr;
pfnUserMsgHook pWeaponList = nullptr;
pfnUserMsgHook pDeathMsg = nullptr;
pfnUserMsgHook pTextMsg = nullptr;

int ScoreAtrrib ( const char *pszName, int iSize, void *pbuf )
{
	int PlayerID = *( uint8_t* )pbuf;
	int Flags = *( uint8_t* )( ( uintptr_t )pbuf + sizeof ( uint8_t ) );

	Client::g_Info->SetPlayerIsAliveByIndex ( PlayerID, !( Flags & ( 1 << 0 ) ) );

	return pScoreAtrrib ( pszName, iSize, pbuf );
}

void AtRoundStart ( )
{
	if ( g_Vars.Functions.BunnyHop )
	{
		Misc::BunnyHop::Active = false;
		Misc::BunnyHop::HelperActive = false;
		Misc::BunnyHop::StandUpActive = false;
	}

	if ( g_Vars.Functions.GroundStrafe )
	{
		Misc::GroundStrafe::Active = false;
		Misc::GroundStrafe::HelperActive = false;
		Misc::GroundStrafe::StandUpActive = false;
	}

	Visuals::ESP::ClearEntity ( );
	Visuals::ESP::ClearSound ( );

	Client::g_Info->SetIsPlanted ( false );

	for ( int Index = 0; Index <= SDK::Interfaces::g_pEngine->GetMaxClients ( ); ++Index )
	{
		if ( Index != Client::g_Info->GetLocalIndex ( ) )
			Client::g_Info->SetPlayerIsDeadByIndex ( Index, false );
	}
}

int ResetHUD ( const char *pszName, int iSize, void *pbuf )
{
	AtRoundStart ( );

	return pResetHUD ( pszName, iSize, pbuf );
}

int SetFOV ( const char *pszName, int iSize, void *pbuf )
{
	BEGIN_READ ( pbuf, iSize );

	Client::g_Info->SetFOV ( READ_BYTE ( ) );

	if ( !Client::g_Info->GetFOV ( ) )
		Client::g_Info->SetFOV ( 90 );

	return pSetFOV ( pszName, iSize, pbuf );
}

int TextMsg ( const char *pszName, int iSize, void *pbuf )
{
	BEGIN_READ ( pbuf, iSize );

	int ID = READ_BYTE ( );

	char *Message = READ_STRING ( );

	if ( *Message )
	{
		if ( !lstrcmpiA ( Message, "#Bomb_Planted" ) )
		{
			Client::g_Info->SetIsPlanted ( true );
		}
		else if ( !lstrcmpiA ( Message, "#Target_Bombed" ) || !lstrcmpiA ( Message, "#Bomb_Defused" ) )
		{
			Client::g_Info->SetIsPlanted ( false );
		}
	}

	return pTextMsg ( pszName, iSize, pbuf );
}

int TeamInfo ( const char *pszName, int iSize, void *pbuf )
{
	BEGIN_READ ( pbuf, iSize );

	cl_entity_s *Entity = SDK::Interfaces::g_Engine.GetLocalPlayer ( );

	int Index = READ_BYTE ( );

	char *Team = READ_STRING ( );

	if ( !lstrcmpiA ( Team, "TERRORIST" ) )
	{
		Client::g_Info->SetPlayerTeamByIndex ( Index, TERRORIST );

		if ( Index == Entity->index )
			Client::g_Info->SetPlayerTeam ( TERRORIST );
	}
	else if ( !lstrcmpiA ( Team, "CT" ) )
	{
		Client::g_Info->SetPlayerTeamByIndex ( Index, CT );

		if ( Index == Entity->index )
			Client::g_Info->SetPlayerTeam ( CT );
	}
	else
	{
		Client::g_Info->SetPlayerTeamByIndex ( Index, SPECTATOR );

		if ( Index == Entity->index )
			Client::g_Info->SetPlayerTeam ( SPECTATOR );
	}

	return pTeamInfo ( pszName, iSize, pbuf );
}

int CurWeapon ( const char *pszName, int iSize, void *pbuf )
{
	BEGIN_READ ( pbuf, iSize );

	int iState = READ_BYTE ( );
	int iWeaponID = READ_CHAR ( );
	int iClip = READ_CHAR ( );

	if ( iState && iWeaponID )
	{
		Client::g_Info->SetWeaponID ( iWeaponID );
		Client::g_Info->SetWeaponClip ( iClip );
	}

	return pCurWeapon ( pszName, iSize, pbuf );
}

int WeaponList ( const char *pszName, int iSize, void *pbuf )
{
	BEGIN_READ ( pbuf, iSize );

	char* WeaponName = READ_STRING ( );

	int Ammo1Type = READ_BYTE ( );
	int Max1 = READ_BYTE ( );

	int Ammo2Type = READ_BYTE ( );
	int Max2 = READ_BYTE ( );

	int Slot = READ_BYTE ( );
	int SlotPos = READ_BYTE ( );

	int ID = READ_BYTE ( );
	int Flags = READ_BYTE ( );

	Client::WeaponList::WeaponListAdd ( WeaponName, Ammo1Type, Max1, Ammo2Type, Max2, Slot, SlotPos, ID, Flags );

	return pWeaponList ( pszName, iSize, pbuf );
}

int DeathMsg ( const char *pszName, int iSize, void *pbuf )
{
	BEGIN_READ ( pbuf, iSize );

	int Killer = READ_BYTE ( );
	int Victim = READ_BYTE ( );
	int HS = READ_BYTE ( );

	char *Weapon = READ_STRING ( );

	Client::g_Info->SetPlayerIsDeadByIndex ( Victim, true );

	return pDeathMsg ( pszName, iSize, pbuf );
}