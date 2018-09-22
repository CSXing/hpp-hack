#include "EngineMsg.h"

using namespace Client::Functions;

int MSG_SavedReadCount = 0;

int* MSG_ReadCount = nullptr;
int* MSG_CurrentSize = nullptr;
int* MSG_BadRead = nullptr;

sizebuf_t* MSG_Buffer = nullptr;

HL_MSG_ReadByte MSG_ReadByte = nullptr;
HL_MSG_ReadShort MSG_ReadShort = nullptr;
HL_MSG_ReadLong MSG_ReadLong = nullptr;
HL_MSG_ReadFloat MSG_ReadFloat = nullptr;
HL_MSG_ReadString MSG_ReadString = nullptr;
HL_MSG_ReadCoord MSG_ReadCoord = nullptr;
HL_MSG_ReadBitVec3Coord MSG_ReadBitVec3Coord = nullptr;
HL_MSG_ReadBits MSG_ReadBits = nullptr;
HL_MSG_StartBitReading MSG_StartBitReading = nullptr;
HL_MSG_EndBitReading MSG_EndBitReading = nullptr;

pfnEngineMsgHook pSVC_sound;
pfnEngineMsgHook pSVC_SpawnStaticSound;
pfnEngineMsgHook pSVC_NewUserMsg;
pfnEngineMsgHook pSVC_UpdateUserInfo;
pfnEngineMsgHook pSVC_StuffText;
pfnEngineMsgHook pSVC_SendCvarValue;
pfnEngineMsgHook pSVC_SendCvarValue2;
pfnEngineMsgHook pSVC_Director;

void MSG_SaveReadCount ( )
{
	MSG_SavedReadCount = *MSG_ReadCount;
}

void MSG_RestoreReadCount ( )
{
	*MSG_ReadCount = MSG_SavedReadCount;
}

void SVC_Sound ( )
{
	MSG_SaveReadCount ( );

	Vector vOrigin;

	float flAttenuation = 0.0f;

	int FieldMask = 0;
	int Volume = 0;
	int Pitch = 0;
	int Channel = 0;
	int Index = 0;
	int SoundNum = 0;

	MSG_StartBitReading ( MSG_Buffer );

	FieldMask = MSG_ReadBits ( 9 );

	Volume = ( FieldMask & SND_FL_VOLUME ) ? MSG_ReadBits ( 8 ) / 255 : SOUND_PACKET_VOLUME;

	if ( FieldMask & SND_FL_ATTENUATION )
		flAttenuation = MSG_ReadBits ( 8 ) / 64.0f;

	Channel = MSG_ReadBits ( 3 );
	Index = MSG_ReadBits ( 11 );

	SoundNum = ( FieldMask & SND_FL_LARGE_INDEX ) ? MSG_ReadBits ( 16 ) : MSG_ReadBits ( 8 );

	MSG_ReadBitVec3Coord ( vOrigin );

	if ( FieldMask & SND_FL_PITCH )
		Pitch = MSG_ReadBits ( 8 );

	MSG_EndBitReading ( MSG_Buffer );

	if ( g_Vars.Functions.ESP && g_Vars.ESP.Enable && g_Vars.ESP.Sound )
	{
		cl_entity_s *Local = SDK::Interfaces::g_pEngine->GetLocalPlayer ( );
		cl_entity_s *Entity = SDK::Interfaces::g_pEngine->GetEntityByIndex ( Index );

		if ( Entity && Index != Local->index )
		{
			if ( Client::g_Info->GetDistanceToEntity ( vOrigin ) <= g_Vars.ESP.SoundDistance && Client::g_Info->GetDistanceToEntity ( vOrigin ) >= 50 )
			{
				if ( Entity->player )
				{
					if ( Client::g_Info->GetPlayerTeamByIndex ( Index ) == TERRORIST )
					{
						Visuals::ESP::AddSound ( GetTickCount64 ( ), vOrigin, 255, 20, 20 );
					}
					else if ( Client::g_Info->GetPlayerTeamByIndex ( Index ) == CT )
					{
						Visuals::ESP::AddSound ( GetTickCount64 ( ), vOrigin, 20, 20, 255 );
					}
					else if ( Client::g_Info->GetPlayerTeamByIndex ( Index ) == SPECTATOR )
					{
						Visuals::ESP::AddSound ( GetTickCount64 ( ), vOrigin, 255, 255, 255 );
					}
				}
				else
				{
					Visuals::ESP::AddSound ( GetTickCount64 ( ), vOrigin, 255, 180, 0 );
				}
			}
		}
	}

	MSG_RestoreReadCount ( );
	pSVC_sound ( );
}

void SVC_SpawnStaticSound ( )
{
	MSG_SaveReadCount ( );

	Vector vPosition;

	float flVolume = 0.0f;
	float flAttenuation = 0.0f;

	int SoundNum = 0;
	int Flags = 0;
	int Index = 0;
	int Pitch = 0;

	MSG_StartBitReading ( MSG_Buffer );

	vPosition.x = MSG_ReadCoord ( );
	vPosition.y = MSG_ReadCoord ( );
	vPosition.z = MSG_ReadCoord ( );

	SoundNum = MSG_ReadShort ( );
	flVolume = MSG_ReadByte ( ) / 255.0f;
	flAttenuation = MSG_ReadByte ( ) / 64.0f;
	Index = MSG_ReadShort ( );
	Pitch = MSG_ReadByte ( );
	Flags = MSG_ReadByte ( );

	MSG_EndBitReading ( MSG_Buffer );

	if ( g_Vars.Functions.ESP && g_Vars.ESP.Enable && g_Vars.ESP.Sound )
	{
		cl_entity_s *Local = SDK::Interfaces::g_pEngine->GetLocalPlayer ( );
		cl_entity_s *Entity = SDK::Interfaces::g_pEngine->GetEntityByIndex ( Index );

		if ( Entity && Index != Local->index )
		{
			if ( Client::g_Info->GetDistanceToEntity ( vPosition ) <= g_Vars.ESP.SoundDistance && Client::g_Info->GetDistanceToEntity ( vPosition ) >= 50 )
			{
				if ( Entity->player )
				{
					if ( Client::g_Info->GetPlayerTeamByIndex ( Index ) == TERRORIST )
					{
						Visuals::ESP::AddSound ( GetTickCount64 ( ), vPosition, 255, 20, 20 );
					}
					else if ( Client::g_Info->GetPlayerTeamByIndex ( Index ) == CT )
					{
						Visuals::ESP::AddSound ( GetTickCount64 ( ), vPosition, 20, 20, 255 );
					}
					else if ( Client::g_Info->GetPlayerTeamByIndex ( Index ) == SPECTATOR )
					{
						Visuals::ESP::AddSound ( GetTickCount64 ( ), vPosition, 255, 255, 255 );
					}
				}
				else
				{
					Visuals::ESP::AddSound ( GetTickCount64 ( ), vPosition, 255, 180, 0 );
				}
			}
		}
	}

	MSG_RestoreReadCount ( );
	pSVC_SpawnStaticSound ( );
}

void SVC_NewUserMsg ( )
{
	MSG_SaveReadCount ( );
	MSG_RestoreReadCount ( );
	pSVC_NewUserMsg ( );
}

void SVC_UpdateUserInfo ( )
{
	MSG_SaveReadCount ( );

	int ClientCDKeyHash[16] = { 0 };

	for ( int i = 0; i < 16; ++i )
		ClientCDKeyHash[i] = MSG_ReadByte ( );

	MSG_RestoreReadCount ( );
	pSVC_UpdateUserInfo ( );
}

void SVC_StuffText ( )
{
	MSG_SaveReadCount ( );
	MSG_RestoreReadCount ( );
	pSVC_StuffText ( );
}

void SVC_SendCvarValue ( )
{
	MSG_SaveReadCount ( );
	MSG_RestoreReadCount ( );
	pSVC_SendCvarValue ( );
}

void SVC_SendCvarValue2 ( )
{
	MSG_SaveReadCount ( );
	MSG_RestoreReadCount ( );
	pSVC_SendCvarValue2 ( );
}

void SVC_Director ( )
{
	MSG_SaveReadCount ( );
	MSG_RestoreReadCount ( );
	pSVC_Director ( );
}