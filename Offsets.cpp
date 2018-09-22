#include "Offsets.h"

namespace Engine
{
	DWORD HWDLL = 0;
	DWORD SWDLL = 0;
	DWORD HLMOD = 0;

	DWORD HWBase = 0;
	DWORD HWSize = 0;
	DWORD HWEnd = 0;

	DWORD HLBase = 0;
	DWORD HLSize = 0;
	DWORD HLEnd = 0;

	DWORD CLBase = 0;
	DWORD CLSize = 0;
	DWORD CLEnd = 0;

	DWORD VGBase = 0;
	DWORD VGSize = 0;
	DWORD VGEnd = 0;

	DWORD Speed = 0;
	DWORD SpeedPtr = 0;

	int HLType = 0;

	double* g_Net = nullptr;

	namespace Offset
	{
		void GetRenderType ( )
		{
			HWDLL = ( DWORD )GetModuleHandle ( "hw.dll" );
			SWDLL = ( DWORD )GetModuleHandle ( "sw.dll" );
			HLMOD = ( DWORD )GetModuleHandle ( 0 );
		}

		DWORD GetModuleSize ( DWORD Address )
		{
			return PIMAGE_NT_HEADERS ( Address + ( DWORD )PIMAGE_DOS_HEADER ( Address )->e_lfanew )->OptionalHeader.SizeOfImage;
		}

		bool GetModuleInfo ( )
		{
			GetRenderType ( );

			if ( HWDLL )
			{
				HWBase = HWDLL;
			}
			else if ( SWDLL )
			{
				HWBase = SWDLL;
			}
			else
			{
				HWBase = HLMOD;
			}

			HWSize = GetModuleSize ( HWBase );
			HWEnd = HWBase + HWSize - 1;

			HLBase = HLMOD;
			HLSize = GetModuleSize ( HWBase );
			HLEnd = HLBase + HLSize - 1;

			CLBase = ( DWORD )GetModuleHandle ( "client.dll" );

			if ( CLBase )
			{
				CLSize = GetModuleSize ( CLBase );
				CLEnd = CLBase + CLSize - 1;
			}
			else
			{
				CLBase = HWBase;
				CLSize = HWSize;
				CLEnd = HWEnd;
			}

			VGBase = ( DWORD )GetModuleHandle ( "GameUI.dll" );

			if ( VGBase )
			{
				VGSize = GetModuleSize ( VGBase );
				VGEnd = VGBase + VGSize - 1;
			}

			return HWBase && CLBase && VGBase;
		}

		DWORD FindString ( PCHAR String, DWORD Start, DWORD End, DWORD Offset )
		{
			DWORD PtLen = lstrlen ( String );

			bool Found = false;

			for ( DWORD i = Start; i < End - PtLen; ++i )
			{
				Found = true;

				for ( DWORD idx = 0; idx < PtLen; ++idx )
				{
					if ( String[idx] != *( PCHAR )( i + idx ) )
					{
						Found = false;

						break;
					}
				}

				if ( Found )
					return i + Offset;
			}

			return 0;
		}

		DWORD FindPattern ( PCHAR Pattern, DWORD PtLen, DWORD Start, DWORD End, DWORD Offset )
		{
			bool Found = false;

			for ( DWORD i = Start; i < End - PtLen; ++i )
			{
				Found = true;

				for ( DWORD idx = 0; idx < PtLen; ++idx )
				{
					if ( Pattern[idx] != *( PCHAR )( i + idx ) )
					{
						Found = false;

						break;
					}
				}

				if ( Found )
					return i + Offset;
			}

			return 0;
		}

		DWORD FindPushString ( DWORD Start, DWORD End, DWORD Address )
		{
			char Pattern[5] = { 0x68, 0x00, 0x00, 0x00, 0x00 };

			*( PDWORD )&Pattern[1] = Address;

			return FindPattern ( Pattern, sizeof ( Pattern ), Start, End, 0 );
		}

		DWORD FarProc ( DWORD Address, DWORD LB, DWORD HB )
		{
			return ( Address < LB ) || ( Address > HB );
		}

		DWORD FindClientTable ( )
		{
			DWORD PatternAddress = FindString ( "ScreenFade", HWBase, HWEnd, 0 );

			BYTE ClientOffset[2] = { 0x10, 0x13 };

			if ( PatternAddress )
			{
				for ( int i = 0; i < sizeof ( ClientOffset ); ++i )
				{
					DWORD ClientTablePtr = *( PDWORD )( FindPushString ( HWBase, HWEnd, PatternAddress ) + ClientOffset[i] );

					if ( !FarProc ( ClientTablePtr, HWBase, HWEnd ) && !IsBadReadPtr ( ( PVOID )ClientTablePtr, sizeof ( cl_clientfunc_t ) ) )
						return ClientTablePtr;
				}
			}

			return 0;
		}

		DWORD FindEngineTable ( )
		{
			BYTE EngineOffset[4] = { 0x22, 0x1C, 0x1D, 0x37 };

			for ( int i = 0; i < sizeof ( EngineOffset ); ++i )
			{
				PVOID EnginePtr = ( cl_enginefunc_t* )*( PDWORD )( ( DWORD )SDK::Interfaces::g_pClient->Initialize + EngineOffset[i] );

				if ( FarProc ( ( DWORD )EnginePtr, HWBase, HWEnd ) && FarProc ( ( DWORD )EnginePtr, HLBase, HLEnd ) && !FarProc ( ( DWORD )EnginePtr, CLBase, CLEnd ) )
					return ( DWORD )EnginePtr;
			}

			return 0;
		}

		DWORD FindStudioTable ( )
		{
			DWORD StudioTablePtr = *( DWORD* )( ( DWORD )SDK::Interfaces::g_pClient->HUD_GetStudioModelInterface + 0x30 );

			if ( FarProc ( StudioTablePtr, HWBase, HWEnd ) && FarProc ( StudioTablePtr, HLBase, HLEnd ) && FarProc ( StudioTablePtr, CLBase, CLEnd ) )
			{
				StudioTablePtr = *( DWORD* )( ( DWORD )SDK::Interfaces::g_pClient->HUD_GetStudioModelInterface + 0x1A );

				if ( !FarProc ( StudioTablePtr, CLBase, CLEnd ) )
					return StudioTablePtr;
			}

			return 0;
		}

		BOOL CompareMemory ( const UCHAR *Buff1, const UCHAR *Buff2, UINT Size )
		{
			for ( UINT i = 0; i < Size; ++i, ++Buff1, ++Buff2 )
				if ( ( *Buff1 != *Buff2 ) && ( *Buff2 != 0xFF ) )
					return FALSE;

			return TRUE;
		}

		ULONG FindMemoryClone ( const ULONG Start, const ULONG End, const ULONG Clone, UINT Size )
		{
			for ( ULONG i = Start; ( i + Size ) < End; ++i )
				if ( CompareMemory ( ( const UCHAR* )i, ( const UCHAR* )Clone, ( UINT )Size ) )
					return i;

			return 0;
		}

		ULONG FindReference ( const ULONG Start, const ULONG End, const ULONG Address )
		{
			UCHAR Pattern[5];

			Pattern[0] = 0x68;

			*( ULONG* )&Pattern[1] = Address;

			return FindMemoryClone ( ( const ULONG )Start, ( const ULONG )End, ( const ULONG )Pattern, ( UINT )sizeof ( Pattern ) - 1 );
		}

		DWORD FindPlayerMove ( )
		{
			PCHAR String = "ScreenFade";

			DWORD Address = ( DWORD )FindMemoryClone ( ( const ULONG )HWBase, ( const ULONG )HWBase + HWSize, ( const ULONG )String, ( UINT )strlen ( String ) );

			PVOID PlayerMovePtr = ( PVOID )*( PDWORD )( FindReference ( ( const ULONG )HWBase, ( const ULONG )HWBase + HWSize, ( const ULONG )Address ) + ( UINT )0x18 );

			if ( !FarProc ( ( DWORD )PlayerMovePtr, HWBase, HWEnd ) )
				return ( DWORD )PlayerMovePtr;

			return 0;
		}

		DWORD FindUserMsgBase ( )
		{
			DWORD UserMsgPattern = FindString ( "UserMsg: Not Present on Client %d", HWBase, HWEnd, 0 );

			BYTE OffsetUserMsgBase = 0x16;

			if ( !UserMsgPattern ) return 0;

			DWORD FindAddress = FindPushString ( HWBase, HWEnd, UserMsgPattern );

			if ( FindAddress )
			{
				PBYTE MovPtr = ( PBYTE )( FindAddress - OffsetUserMsgBase );

				if ( *MovPtr == 0x8B )
				{
					DWORD dwUserMsgBase = *( PDWORD )( ( DWORD )MovPtr + 2 );

					if ( !FarProc ( dwUserMsgBase, HWBase, HWEnd ) )
						return *( PDWORD )dwUserMsgBase;
				}
			}

			return 0;
		}

		DWORD Absolute ( DWORD Address )
		{
			if ( !Address )
			{
				Files::InjectLog ( ABSOLUTE_ERROR );

				Utils::Error ( true, ABSOLUTE_ERROR );
			}

			return Address + *( PDWORD )Address + 4;
		}

		DWORD FindSVCMessages ( )
		{
			DWORD SVCMsgPattern = FindString ( "-------- Message Load ---------", HWBase, HWEnd, 0 );

			if ( !SVCMsgPattern )
			{
				Files::InjectLog ( SVC_MSG_ERROR );
				Utils::Error ( true, SVC_MSG_ERROR );
			}

			DWORD FindAddress = *( PDWORD )( FindPushString ( HWBase, HWEnd, SVCMsgPattern ) + 0x12 );

			if ( FarProc ( FindAddress, HWBase, HWEnd ) )
			{
				Files::InjectLog ( SVC_MSG_ERROR );
				Utils::Error ( true, SVC_MSG_ERROR );
			}

			PEngineMsg EngineMsgBase = ( PEngineMsg )( FindAddress - sizeof ( DWORD ) );

			BYTE OffsetReadCoord[5] = { 0x13, 0x15, 0x17, 0x0E, 0x0B };
			BYTE OffsetSVC_SoundBase[3] = { 0x0E, 0x0C, 0x16 };

			if ( EngineMsgBase )
			{
				MSG_ReadByte = ( HL_MSG_ReadByte )Absolute ( ( ( DWORD )EngineMsgBase[SVC_CDTRACK].pfn ) + 1 );
				MSG_ReadShort = ( HL_MSG_ReadShort )Absolute ( ( ( DWORD )EngineMsgBase[SVC_STOPSOUND].pfn ) + 1 );
				MSG_ReadLong = ( HL_MSG_ReadLong )Absolute ( ( ( DWORD )EngineMsgBase[SVC_VERSION].pfn ) + 1 );
				MSG_ReadFloat = ( HL_MSG_ReadFloat )Absolute ( ( ( DWORD )EngineMsgBase[SVC_TIMESCALE].pfn ) + 1 );
				MSG_ReadString = ( HL_MSG_ReadString )Absolute ( ( ( DWORD )EngineMsgBase[SVC_PRINT].pfn ) + 1 );

				DWORD CallMSG_ReadCoord = Absolute ( ( DWORD )( EngineMsgBase[SVC_PARTICLE].pfn ) + 1 );

				for ( int i = 0; i < sizeof ( OffsetReadCoord ); ++i )
				{
					if ( *( PBYTE )( CallMSG_ReadCoord + OffsetReadCoord[i] ) == 0xE8 )
					{
						MSG_ReadCoord = ( HL_MSG_ReadCoord )Absolute ( ( CallMSG_ReadCoord + OffsetReadCoord[i] + 1 ) );

						goto NextFind1;
					}
				}

				Files::InjectLog ( MSG_READ_CORD );
				Utils::Error ( true, MSG_READ_CORD );

			NextFind1:
				MSG_ReadCount = *( PINT* )( ( INT )( MSG_ReadByte )+1 );
				MSG_CurrentSize = *( PINT* )( ( INT )( MSG_ReadByte )+7 );
				MSG_BadRead = *( PINT* )( ( INT )( MSG_ReadByte )+20 );

				DWORD SVC_SoundBase = ( DWORD )EngineMsgBase[SVC_SOUND].pfn;

				for ( int i = 0; i < sizeof ( OffsetSVC_SoundBase ); ++i )
				{
					if ( *( PBYTE )( SVC_SoundBase + OffsetSVC_SoundBase[i] ) == 0xE8 )
					{
						MSG_Buffer = ( sizebuf_t * )( *( PDWORD )( SVC_SoundBase + OffsetSVC_SoundBase[i] - 4 ) );
						MSG_StartBitReading = ( HL_MSG_StartBitReading )Absolute ( SVC_SoundBase + OffsetSVC_SoundBase[i] + 1 );
						MSG_ReadBits = ( HL_MSG_ReadBits )Absolute ( SVC_SoundBase + OffsetSVC_SoundBase[i] + 8 );

						goto NextFind2;
					}
				}

				Files::InjectLog ( MSG_STR_READING );
				Utils::Error ( true, MSG_STR_READING );

			NextFind2:
				if ( *( PBYTE )( SVC_SoundBase + 0xD6 ) == 0xE8 )
				{
					MSG_EndBitReading = ( HL_MSG_EndBitReading )Absolute ( SVC_SoundBase + 0xD7 );
					MSG_ReadBitVec3Coord = ( HL_MSG_ReadBitVec3Coord )Absolute ( SVC_SoundBase + 0xAF );
				}
				else if ( *( PBYTE )( SVC_SoundBase + 0xE2 ) == 0xE8 )
				{
					MSG_EndBitReading = ( HL_MSG_EndBitReading )Absolute ( SVC_SoundBase + 0xE3 );
					MSG_ReadBitVec3Coord = ( HL_MSG_ReadBitVec3Coord )Absolute ( SVC_SoundBase + 0xBE );
				}
				else if ( *( PBYTE )( SVC_SoundBase + 0xDD ) == 0xE8 )
				{
					MSG_EndBitReading = ( HL_MSG_EndBitReading )Absolute ( SVC_SoundBase + 0xDE );
					MSG_ReadBitVec3Coord = ( HL_MSG_ReadBitVec3Coord )Absolute ( SVC_SoundBase + 0xB9 );
				}
				else
				{
					Files::InjectLog ( MSG_END_READING );
					Utils::Error ( true, MSG_END_READING );
				}
			}
			else
				return 0;

			return ( DWORD )EngineMsgBase;
		}

		DWORD FindGameConsole ( )
		{
			DWORD GameConsolePattern = FindPattern ( "GameConsole003", lstrlenA ( "GameConsole003" ), VGBase, VGEnd, 0 );

			if ( !GameConsolePattern )
			{
				Files::InjectLog ( CONSOLE_ERROR );
				Utils::Error ( true, CONSOLE_ERROR );
			}

			DWORD FindAddress = *( PDWORD )( FindPushString ( VGBase, VGEnd, GameConsolePattern ) + 0x21 );

			if ( FarProc ( FindAddress, VGBase, VGEnd ) )
			{
				Files::InjectLog ( CONSOLE_ERROR );
				Utils::Error ( true, CONSOLE_ERROR );
			}

			return FindAddress;
		}

		void ConsoleColorInitialize ( )
		{
			DWORD GameConsole = FindGameConsole ( );

			if ( !GameConsole )
			{
				Files::InjectLog ( CONSOLE_ERROR );
				Utils::Error ( true, CONSOLE_ERROR );
			}

			DWORD Panel = ( *( PDWORD )( GameConsole + 8 ) - GameConsole );

			SDK::Interfaces::Console_TextColor = PColor24 ( Panel + GameConsole + 288 + sizeof ( DWORD ) );

			if ( *( PDWORD )( DWORD ( SDK::Interfaces::Console_TextColor ) + 8 ) )
				SDK::Interfaces::Console_TextColor = PColor24 ( Panel + GameConsole + 288 + ( sizeof ( DWORD ) * 2 ) );
		}

		void GetGameInfo ( pGameInfo_s GameInfo )
		{
			typedef int ( *function )( );

			pcmd_t pCmd = Utils::CommandByName ( "version" );

			DWORD Address = ( DWORD )pCmd->function;

			GameInfo->GameName = *( PCHAR* )( UINT ( Address ) + 1 );
			GameInfo->GameVersion = *( PCHAR* )( UINT ( Address ) + 6 );
			GameInfo->Protocol = *( PBYTE )( UINT ( Address ) + 11 );

			Address = Absolute ( UINT ( Address ) + 23 );

			if ( FarProc ( Address, HWBase, HWEnd ) )
			{
				Files::InjectLog ( GAMEINFO_ERROR );
				Utils::Error ( true, GAMEINFO_ERROR );
			}

			function GetBuild = ( function )Address;

			GameInfo->Build = GetBuild ( );
		}

		void* SpeedHackPtr ( )
		{
			DWORD Old = 0;
			PCHAR String = "Texture load: %6.1fms";
			DWORD Address = ( DWORD )FindMemoryClone ( ( const ULONG )HWBase, ( const ULONG )( HWBase + HWSize ), ( const ULONG )String, ( UINT )strlen ( String ) );
			PVOID SpeedPtr = ( PVOID )*( DWORD* )( FindReference ( ( const ULONG )HWBase, ( const ULONG )( HWBase + HWSize ), ( const ULONG )Address ) - 7 );

			if ( FarProc ( ( DWORD )SpeedPtr, HWBase, HWEnd ) )
			{
				Files::InjectLog ( SPEEDPTR_ERROR );
				Utils::Error ( true, SPEEDPTR_ERROR );
			}
			else
				VirtualProtect ( SpeedPtr, sizeof ( double ), PAGE_READWRITE, &Old );

			return SpeedPtr;
		}
	}
}