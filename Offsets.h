#pragma once

#include "Main.h"

namespace Engine
{
	extern DWORD SpeedPtr, Speed;

	extern DWORD HWDLL, SWDLL, HLMOD;
	extern DWORD HWBase, HWSize, HWEnd;
	extern DWORD HLBase, HLSize, HLEnd;
	extern DWORD CLBase, CLSize, CLEnd;
	extern DWORD VGBase, VGSize, VGEnd;

	extern double *g_Net;

	extern int HLType;

	namespace Offset
	{
		void ConsoleColorInitialize ( );

		void GetGameInfo ( pGameInfo_s GameInfo );
		void GetRenderType ( );

		void* SpeedHackPtr ( );

		bool GetModuleInfo ( );

		DWORD FindClientTable ( );
		DWORD FindEngineTable ( );
		DWORD FindStudioTable ( );
		DWORD FindPlayerMove ( );
		DWORD FindUserMsgBase ( );
		DWORD FindSVCMessages ( );

		DWORD GetModuleSize ( DWORD dwAddress );

		DWORD FindString ( PCHAR String, DWORD Start, DWORD End, DWORD Offset );
		DWORD FindPattern ( PCHAR Pattern, DWORD PtLen, DWORD Start, DWORD End, DWORD Offset );
		DWORD FindPushString ( DWORD Start, DWORD End, DWORD Address );
		ULONG FindMemoryClone ( const ULONG Start, const ULONG End, const ULONG Clone, UINT Size );
		ULONG FindReference ( const ULONG Start, const ULONG End, const ULONG Address );
		DWORD FindGameConsole ( );

		DWORD FarProc ( DWORD Address, DWORD LB, DWORD HB );
		BOOL CompareMemory ( const UCHAR *Buff1, const UCHAR *Buff2, UINT Size );
		DWORD Absolute ( DWORD Address );
	}
}