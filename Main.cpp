#include "Main.h"

namespace Renderer
{
	void Drawing::FillArea ( int x, int y, int w, int h, BYTE R, BYTE G, BYTE B, BYTE A )
	{
		SDK::Interfaces::g_pEngine->pfnTintRGBA ( x, y, w, h, R, G, B, A );
	}

	Drawing *g_Drawing = nullptr;
	Fonts *g_Fonts = nullptr;
	Fonts *g_Verdana = nullptr;
}

void Initialize ( )
{
	Renderer::g_Drawing = new Renderer::Drawing;
	Renderer::g_Fonts = new Renderer::Fonts;
	Renderer::g_Verdana = new Renderer::Fonts;
	Client::g_Info = new Client::Info;
}

void Shutdown ( )
{
	DELETE_MOD ( Renderer::g_Drawing );
	DELETE_MOD ( Renderer::g_Fonts );
	DELETE_MOD ( Renderer::g_Verdana );
	DELETE_MOD ( Client::g_Info );
}

DWORD WINAPI ProcessReload ( LPVOID lpThreadParameter )
{
	while ( true )
	{
		if ( Client::FirstFrame )
		{
			if ( !Engine::Offset::GetModuleInfo ( ) )
			{
				Client::dwStudioModelRenderer = 0;
				Client::dwStudioRenderFinal = 0;

				Client::FirstFrame = false;
			}
		}
		else
			CreateThread ( 0, 0, ( LPTHREAD_START_ROUTINE )CheatEntry, 0, 0, 0 );

		Sleep ( 100 );
	}

	return 0;
}

DWORD WINAPI CheatEntry ( LPVOID lpThreadParameter )
{
	static HANDLE hProcessReloadThread;

	if ( hProcessReloadThread )
	{
		TerminateThread ( hProcessReloadThread, 0 );
		CloseHandle ( hProcessReloadThread );
	}

	Files::InjectLog ( "Initialization..." );

	Initialize ( );
	SDK::Offset::Initialize ( hProcessReloadThread );

	return 0;
}

BOOL WINAPI DllMain ( HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved )
{
	if ( dwReason == DLL_PROCESS_ATTACH )
	{
		DisableThreadLibraryCalls ( hInstance );

		Files::GetBaseDir ( hInstance );
		Files::CreateLogDirectory ( );
		Files::CreateInjectLogFile ( );
		Files::CreateInfoLogFile ( );

		Files::InjectLog ( "CreateThread..." );

		CreateThread ( 0, 0, ( LPTHREAD_START_ROUTINE )CheatEntry, 0, 0, 0 );
	}
	else if ( dwReason == DLL_PROCESS_DETACH )
	{
		Shutdown ( );
	}

	return TRUE;
}