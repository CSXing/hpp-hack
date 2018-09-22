#pragma once

#include "Main.h"

namespace SDK
{
	class Interfaces
	{
	public:
		static cl_clientfunc_t *g_pClient;
		static cl_enginefunc_t *g_pEngine;
		static engine_studio_api_t *g_pStudio;
		static playermove_t *g_pPlayerMove;
		static screenfade_t *g_pScreenFade;

		static cl_clientfunc_t g_Client;
		static cl_enginefunc_t g_Engine;
		static engine_studio_api_t g_Studio;
		static SCREENINFO g_Screen;
		static PUserMsg g_pUserMsgBase;
		static PEngineMsg g_pEngineMsgBase;
		static PColor24 Console_TextColor;
	};

	namespace Offset
	{
		void Initialize ( HANDLE& hProcessReloadThread );
	}

	namespace Hook
	{
		void Initialize ( );

		void HookClient ( );
		void HookStudio ( );
		void HookUserMessages ( );
		void HookEngineMessages ( );
		void HookOpenGL ( );
	}
}