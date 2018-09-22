#include "Utils.h"

namespace Utils
{
	pcmd_t CommandByName ( char* Name )
	{
		pcmd_t pCmd = SDK::Interfaces::g_pEngine->pfnGetCmdList ( );

		while ( pCmd )
		{
			if ( !lstrcmpA ( pCmd->name, Name ) ) return pCmd;

			pCmd = pCmd->next;
		}

		return 0;
	}

	PUserMsg UserMsgByName ( char* MsgName )
	{
		PUserMsg Ptr = SDK::Interfaces::g_pUserMsgBase;

		while ( Ptr->next )
		{
			if ( !lstrcmpA ( Ptr->name, MsgName ) ) return Ptr;

			Ptr = Ptr->next;
		}

		Ptr->pfn = 0;

		return Ptr;
	}

	pfnUserMsgHook HookUserMsg ( char *MsgName, pfnUserMsgHook pfn )
	{
		pfnUserMsgHook pfnOriginal = nullptr;
		PUserMsg Ptr = UserMsgByName ( MsgName );

		if ( Ptr->pfn )
		{
			pfnOriginal = Ptr->pfn;
			Ptr->pfn = pfn;
		}

		return pfnOriginal;
	}

	PEngineMsg EngineMsgByName ( char* MsgName )
	{
		PEngineMsg Ptr = SDK::Interfaces::g_pEngineMsgBase;

		while ( lstrcmpA ( Ptr->name, "End of List." ) )
		{
			if ( !lstrcmpA ( Ptr->name, MsgName ) ) return Ptr;

			++Ptr;
		}

		Ptr->pfn = 0;

		return Ptr;
	}

	pfnEngineMsgHook HookEngineMsg ( char *MsgName, pfnEngineMsgHook pfn )
	{
		pfnEngineMsgHook pfnOriginal = nullptr;
		PEngineMsg Ptr = EngineMsgByName ( MsgName );

		if ( Ptr->pfn )
		{
			pfnOriginal = Ptr->pfn;
			Ptr->pfn = pfn;
		}
		else
		{
			Files::InjectLog ( ENGINEMSG_ERROR, MsgName );
			Utils::Error ( true, ENGINEMSG_ERROR, MsgName );
		}

		return pfnOriginal;
	}

	void HookCommand ( char *CmdName, xcommand_t *CmdPointer, void ( *Function )( void ) )
	{
		pcmd_t pCmd = SDK::Interfaces::g_pEngine->pfnGetCmdList ( );

		while ( pCmd )
		{
			if ( !lstrcmpA ( pCmd->name, CmdName ) )
			{
				*CmdPointer = pCmd->function;
				pCmd->function = ( xcommand_t )( ( void * )Function );
				break;
			}

			pCmd = pCmd->next;
		}
	}

	void Error ( const bool &Exit, char *Message, ... )
	{
		char String[256];

		va_list ArgumentPtr;
		va_start ( ArgumentPtr, Message );
		vsprintf_s ( String, Message, ArgumentPtr );
		va_end ( ArgumentPtr );

		MessageBox ( 0, String, "Hpp Hack", MB_OK | MB_ICONERROR );

		if ( Exit ) ExitProcess ( 0 );
	}

	void native_memcpy ( void* dst, const void* src, size_t count )
	{
		_asm
		{
			mov	edi, [dst]
			mov	esi, [src]
			mov	ecx, [count]
			rep	movsb
		}
	}

	void native_memset ( void *szBuffer, DWORD dwLen, DWORD dwSym )
	{
		_asm
		{
			pushad
			mov edi, [szBuffer]
			mov ecx, [dwLen]
			mov eax, [dwSym]
			rep stosb
			popad
		}
	}

	bool PathFree ( Vector& vInput )
	{
		if ( !vInput ) return false;

		pmtrace_t pTrace;

		SDK::Interfaces::g_pEngine->pEventAPI->EV_SetTraceHull ( 2 );

		SDK::Interfaces::g_pEngine->pEventAPI->EV_PlayerTrace ( Client::g_Info->GetVectorEyePosition ( ),
			vInput, PM_GLASS_IGNORE | PM_STUDIO_BOX, Client::g_Info->GetLocalIndex ( ), &pTrace );

		int Index = SDK::Interfaces::g_pEngine->pEventAPI->EV_IndexFromTrace ( &pTrace );

		if ( Index )
		{
			return true;
		}

		return pTrace.fraction == 1.0f;
	}

	bool CalcScreen ( Vector& pflOrigin, Vector2D& pflVecScreen )
	{
		int Result = SDK::Interfaces::g_pEngine->pTriAPI->WorldToScreen ( pflOrigin, pflVecScreen );

		if ( !Result )
		{
			pflVecScreen[0] = pflVecScreen[0] * ( SDK::Interfaces::g_Screen.iWidth / 2 ) + ( SDK::Interfaces::g_Screen.iWidth / 2 );
			pflVecScreen[1] = -pflVecScreen[1] * ( SDK::Interfaces::g_Screen.iHeight / 2 ) + ( SDK::Interfaces::g_Screen.iHeight / 2 );

			return true;
		}

		return false;
	}

	Vector2D GetPunchScreen ( )
	{
		return Client::g_Info->GetVectorPunchAngles ( ).Make2D ( ) / ( float )Client::g_Info->GetFOV ( ) * ( float )SDK::Interfaces::g_Screen.iWidth / 1.2f;
	}

	Vector2D GetScreen ( )
	{
		Vector2D Screen;

		Screen[0] = SDK::Interfaces::g_Screen.iWidth / 2.0f;
		Screen[1] = SDK::Interfaces::g_Screen.iHeight / 2.0f;

		return Screen;
	}

	void MakeAngle ( const Vector &Angles, usercmd_s *cmd )
	{
		Vector ViewForward, ViewRight, ViewUp, AimForward, AimRight, AimUp, vTemp;

		float NewForward = 0.0f;
		float NewRight = 0.0f;
		float NewUp = 0.0f;

		float Forward = cmd->forwardmove;
		float Right = cmd->sidemove;
		float Up = cmd->upmove;

		cl_entity_s *Local = SDK::Interfaces::g_pEngine->GetLocalPlayer ( );

		SDK::Interfaces::g_pEngine->pfnAngleVectors ( Local->curstate.movetype == MOVETYPE_WALK ?
			Vector ( 0.0f, cmd->viewangles.y, 0.0f ) : cmd->viewangles, ViewForward, ViewRight, ViewUp );

		if ( Local->curstate.movetype == MOVETYPE_WALK && !( SDK::Interfaces::g_pPlayerMove->movetype == 5 ) )
		{
			cmd->viewangles.x = Angles[0];
			cmd->viewangles.y = Angles[1];
		}

		SDK::Interfaces::g_pEngine->pfnAngleVectors ( Local->curstate.movetype == MOVETYPE_WALK ?
			Vector ( 0.0f, cmd->viewangles.y, 0.0f ) : cmd->viewangles, AimForward, AimRight, AimUp );

		NewForward =
			DotProduct ( Forward * ViewForward.Normalize ( ), AimForward ) +
			DotProduct ( Right * ViewRight.Normalize ( ), AimForward ) +
			DotProduct ( Up * ViewUp.Normalize ( ), AimForward );

		NewRight =
			DotProduct ( Forward * ViewForward.Normalize ( ), AimRight ) +
			DotProduct ( Right * ViewRight.Normalize ( ), AimRight ) +
			DotProduct ( Up * ViewUp.Normalize ( ), AimRight );

		NewUp =
			DotProduct ( Forward * ViewForward.Normalize ( ), AimUp ) +
			DotProduct ( Right * ViewRight.Normalize ( ), AimUp ) +
			DotProduct ( Up * ViewUp.Normalize ( ), AimUp );

		cmd->forwardmove = ( Angles[0] > 81.0f ) ? -NewForward : NewForward;
		cmd->sidemove = NewRight;
		cmd->upmove = NewUp;
	}
}