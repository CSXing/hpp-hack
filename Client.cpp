#pragma warning (disable: 4996)

#include "Client.h"

namespace Client
{
	using namespace Functions;

	DWORD dwStudioModelRenderer = 0;
	DWORD dwStudioRenderFinal = 0;

	xcommand_t xJumpPressed, xJumpReleased;
	xcommand_t xDuckPressed, xDuckReleased;

	Snapshot_t SnapShot_s;
	Screenshot_t ScreenShot_s;

	DWORD64 UpdateCurrent = 0;
	DWORD64 UpdateLast = 0;

	bool GameActive = false;
	bool FirstFrame = false;

	bool PanicAimBotEnabled = false;
	bool PanicVisualsEnabled = false;
	bool PanicMiscEnabled = false;
	bool PanicEnabled = false;

	bool SteamScreenShot = false;
	bool SnapShot = false;
	bool ScreenShot = false;

	int AntiScreenTimer = 0;

	void ResetSpeed ( )
	{
		if ( g_Vars.Functions.Speed )
		{
			Misc::Speed::AdjustSpeed ( 1.0 );

			*Engine::g_Net += 0.0;
		}
	}

	void HookedJumpPressed ( )
	{
		Visuals::ScreenInfo::SetJumpPressed ( true );
		Misc::BunnyHop::SetJumpPressed ( true );

		_asm CALL xJumpPressed
	}

	void HookedJumpReleased ( )
	{
		if ( Visuals::ScreenInfo::GetJumpPressed ( ) )
			Visuals::ScreenInfo::SetScrollJump ( true );

		if ( Misc::BunnyHop::GetJumpPressed ( ) )
			Misc::BunnyHop::SetScrollJump ( true );

		_asm CALL xJumpReleased
	}

	void HookedDuckPressed ( )
	{
		Visuals::ScreenInfo::SetDuckPressed ( true );
		Misc::GroundStrafe::SetDuckPressed ( true );

		_asm CALL xDuckPressed
	}

	void HookedDuckReleased ( )
	{
		if ( Visuals::ScreenInfo::GetDuckPressed ( ) )
			Visuals::ScreenInfo::SetScrollDuck ( true );

		if ( Misc::GroundStrafe::GetDuckPressed ( ) )
			Misc::GroundStrafe::SetScrollDuck ( true );

		_asm CALL xDuckReleased
	}

	void ResetFadeColor ( )
	{
		SDK::Interfaces::g_pScreenFade->fader = 255;
		SDK::Interfaces::g_pScreenFade->fadeg = 255;
		SDK::Interfaces::g_pScreenFade->fadeb = 255;
	}

	void AntiSnapShot ( )
	{
		if ( g_Vars.Main.AntiScreenEnable )
		{
			AntiScreenTimer = g_Vars.Main.AntiScreenTimer;

			SnapShot = true;

			if ( g_Vars.Functions.NoFlash && g_Vars.NoFlash.Enable )
			{
				ResetFadeColor ( );
			}

			if ( g_Vars.Functions.Crosshair && g_Vars.Crosshair.Enable )
				SDK::Interfaces::g_pEngine->pfnCvar_Set ( "cl_crosshair_color", "64 255 64" );
		}
		else
			SnapShot_s ( );
	}

	void AntiScreenShot ( )
	{
		if ( g_Vars.Main.AntiScreenEnable )
		{
			AntiScreenTimer = g_Vars.Main.AntiScreenTimer;

			ScreenShot = true;

			if ( g_Vars.Functions.NoFlash && g_Vars.NoFlash.Enable )
			{
				ResetFadeColor ( );
			}

			if ( g_Vars.Functions.Crosshair && g_Vars.Crosshair.Enable )
				SDK::Interfaces::g_pEngine->pfnCvar_Set ( "cl_crosshair_color", "64 255 64" );
		}
		else
			ScreenShot_s ( );
	}

	void GetInfoLog ( )
	{
		Files::InfoLog ( "Game Info" );
		Files::InfoLog ( "	Name: %s", Client::BuildInfo.GameName );
		Files::InfoLog ( "	Version: %s", Client::BuildInfo.GameVersion );
		Files::InfoLog ( "	Protocol: %d", Client::BuildInfo.Protocol );
		Files::InfoLog ( "	Build: %d", Client::BuildInfo.Build );
		Files::InfoLog ( "OS Info" );

		OSVERSIONINFOEX osvi;
		BOOL bOsVersionInfoEx;

		ZeroMemory ( &osvi, sizeof ( OSVERSIONINFOEX ) );
		osvi.dwOSVersionInfoSize = sizeof ( OSVERSIONINFOEX );

		if ( !( bOsVersionInfoEx = GetVersionEx ( ( OSVERSIONINFO * )&osvi ) ) )
		{
			osvi.dwOSVersionInfoSize = sizeof ( OSVERSIONINFO );

			if ( !GetVersionEx ( ( OSVERSIONINFO * )&osvi ) )
				Files::InfoLog ( "Unable to get system version" );
		}

		Files::InfoLog ( "	Platform: %d", osvi.dwPlatformId );
		Files::InfoLog ( "	VersionMajor: %d", osvi.dwMajorVersion );
		Files::InfoLog ( "	VersionMinor: %d", osvi.dwMinorVersion );
		Files::InfoLog ( "	BuildNumber: %d", osvi.dwBuildNumber );
		Files::InfoLog ( "	OSVersionInfoSize: %d", osvi.dwOSVersionInfoSize );
		Files::InfoLog ( "	SP_Version: %d", osvi.szCSDVersion );
		Files::InfoLog ( "	SP_Major: %d", osvi.wServicePackMajor );
		Files::InfoLog ( "	SP_Minor: %d", osvi.dwMinorVersion );
	}

	void Initialize ( )
	{
		Renderer::g_Fonts->InitText ( "Lucida Console", 12, 8 );
		Renderer::g_Verdana->InitText ( "Verdana", 13, 0 );

		Files::LoadSettings ( );

		if ( g_Vars.Functions.Chams ) SDK::Interfaces::g_pEngine->pfnClientCmd ( "cl_shadows 0" );

		if ( g_Vars.Functions.Crosshair )
		{
			SDK::Interfaces::g_pEngine->pfnCvar_Set ( "cl_crosshair_translucent", "1" );
			SDK::Interfaces::g_pEngine->pfnCvar_Set ( "cl_crosshair_color", "0" );
		}

		SDK::Interfaces::g_pEngine->pfnClientCmd ( "toggleconsole" );

		ConsolePrintColor ( 80, 255, 80, g_Vars.Main.Language == ENGLISH ? "Hpp Hack successfully injected!\n\n" : "Hpp Hack успешно загружен!\n\n" );
		ConsolePrintColor ( 255, 240, 0, g_Vars.Main.Language == ENGLISH ? "Information about game:\n" : "Информация о игре:\n" );
		ConsolePrintColor ( 0, 230, 230, g_Vars.Main.Language == ENGLISH ? "\t\tName: " : "\t\tНазвание:: " );
		ConsolePrintColor ( 255, 200, 0, Client::BuildInfo.GameName );
		ConsolePrintColor ( 0, 230, 230, g_Vars.Main.Language == ENGLISH ? "\n\t\tVersion: " : "\n\t\tВерсия: " );
		ConsolePrintColor ( 255, 200, 0, Client::BuildInfo.GameVersion );
		ConsolePrintColor ( 0, 230, 230, g_Vars.Main.Language == ENGLISH ? "\n\t\tProtocol: " : "\n\t\tПротокол: " );
		ConsolePrintColor ( 255, 200, 0, Client::BuildInfo.Protocol );
		ConsolePrintColor ( 0, 230, 230, g_Vars.Main.Language == ENGLISH ? "\n\t\tBuild: " : "\n\t\tПостроение: " );
		ConsolePrintColor ( 255, 200, 0, Client::BuildInfo.Build );
		ConsolePrintColor ( 0, 230, 230, g_Vars.Main.Language == ENGLISH ? "\n\t\tRender: " : "\n\t\tРендер: " );
		ConsolePrintColor ( 255, 200, 0, Utils::ConvertTypeToRenderString ( Engine::HLType ) );
		ConsolePrintColor ( 255, 240, 0, g_Vars.Main.Language == ENGLISH ? "\n\nInformation about cheat:\n" : "\n\nИнформация о чите:\n" );
		ConsolePrintColor ( 0, 230, 230, g_Vars.Main.Language == ENGLISH ? "\t\tVersion: " : "\t\tВерсия: " );
		ConsolePrintColor ( 255, 200, 0, "3.3 Release\n" );
		ConsolePrintColor ( 0, 230, 230, g_Vars.Main.Language == ENGLISH ? "\t\tAuthor: " : "\t\tАвтор: " );
		ConsolePrintColor ( 255, 200, 0, "kilabeez\n" );
		ConsolePrintColor ( 0, 230, 230, g_Vars.Main.Language == ENGLISH ? "\t\tThanks to: " : "\t\tБлагодарю: " );
		ConsolePrintColor ( 255, 200, 0, "AntiValve, ranget, Garey\n" );
		ConsolePrintColor ( 0, 230, 230, g_Vars.Main.Language == ENGLISH ? "\t\tPath: " : "\t\tПуть: " );
		ConsolePrintColor ( 255, 200, 0, Files::BaseDir );
		ConsolePrintColor ( 0, 0, 0, "\n\n" );
	}

	void HUD_Frame ( double time )
	{
		if ( !FirstFrame )
		{
			SDK::Interfaces::g_Screen.iSize = sizeof ( SCREENINFO );

			Engine::HLType = SDK::Interfaces::g_Studio.IsHardware ( ) + 1;

			Engine::Offset::ConsoleColorInitialize ( );

			Files::InjectLog ( "	Console_TextColor: 0x%X", SDK::Interfaces::Console_TextColor );
			Files::InjectLog ( "Getting GameInfo..." );

			Engine::Offset::GetGameInfo ( &BuildInfo );

			SDK::Interfaces::g_pScreenFade = *( screenfade_t** )( ( DWORD )SDK::Interfaces::g_Engine.pfnSetScreenFade + 0x17 );

			if ( IsBadReadPtr ( SDK::Interfaces::g_pScreenFade, sizeof ( screenfade_t ) ) )
				SDK::Interfaces::g_pScreenFade = *( screenfade_t** )( ( DWORD )SDK::Interfaces::g_Engine.pfnSetScreenFade + 0x18 );

			Files::InjectLog ( "	g_pScreenFade: 0x%X", SDK::Interfaces::g_pScreenFade );

			Engine::SpeedPtr = ( DWORD )Engine::Offset::SpeedHackPtr ( );

			Files::InjectLog ( "	SpeedPtr: 0x%X", Engine::SpeedPtr );

			if ( BuildInfo.Build > 4554 )
			{
				Engine::g_Net = ( double* )*( PDWORD )( ( DWORD )SDK::Interfaces::g_Engine.pNetAPI->SendRequest + 0x49 );
			}
			else
			{
				Engine::g_Net = ( double* )*( PDWORD )( ( DWORD )SDK::Interfaces::g_Engine.pNetAPI->SendRequest + 0x51 );

				if ( IsBadReadPtr ( Engine::g_Net, sizeof ( double ) ) )
					Engine::g_Net = ( double* )*( PDWORD )( ( DWORD )SDK::Interfaces::g_Engine.pNetAPI->SendRequest + 0x49 );
			}

			Files::InjectLog ( "	g_Net: 0x%X", Engine::g_Net );
			Files::InjectLog ( "Initialization..." );

			SDK::Hook::Initialize ( );
			Initialize ( );

			pcmd_t pSnapShot = Utils::CommandByName ( "snapshot" );
			pcmd_t pScreenShot = Utils::CommandByName ( "screenshot" );

			SnapShot_s = ( Snapshot_t )pSnapShot->function;
			ScreenShot_s = ( Screenshot_t )pScreenShot->function;

			pSnapShot->function = ( xcommand_t )AntiSnapShot;
			pScreenShot->function = ( xcommand_t )AntiScreenShot;

			Utils::HookCommand ( "+jump", &xJumpPressed, HookedJumpPressed );
			Utils::HookCommand ( "-jump", &xJumpReleased, HookedJumpReleased );

			Utils::HookCommand ( "+duck", &xDuckPressed, HookedDuckPressed );
			Utils::HookCommand ( "-duck", &xDuckReleased, HookedDuckReleased );

			Files::InjectLog ( "Allocating memory for WeaponList..." );

			WeaponList::WeaponListData = ( weapon_list_s* )HeapAlloc ( GetProcessHeap ( ), HEAP_ZERO_MEMORY, sizeof ( weapon_list_s ) * MAX_WEAPON_LIST );
			WeaponList::WeaponListClear ( );

			FirstFrame = true;

			Files::InjectLog ( "Finished" );

			GetInfoLog ( );
		}

		SDK::Interfaces::g_Engine.pfnGetScreenInfo ( &SDK::Interfaces::g_Screen );

		UpdateCurrent = GetTickCount64 ( );

		if ( UpdateCurrent - UpdateLast >= 300 )
			GameActive = false;

#if HPP_ADMIN == 0
		if ( strstr ( SDK::Interfaces::g_pEngine->pfnGetCvarPointer ( "name" )->string, "kilabeez" ) )
		{
			SDK::Interfaces::g_pEngine->pfnClientCmd ( "quit" );
		}

		if ( strstr ( SDK::Interfaces::g_pEngine->pfnGetCvarPointer ( "name" )->string, "Fletia" ) )
		{
			SDK::Interfaces::g_pEngine->pfnClientCmd ( "quit" );
		}

		if ( strstr ( SDK::Interfaces::g_pEngine->pfnGetCvarPointer ( "name" )->string, "_273078212764" ) )
		{
			SDK::Interfaces::g_pEngine->pfnClientCmd ( "quit" );
		}
#endif

		SDK::Interfaces::g_Client.HUD_Frame ( time );
	}

	void HUD_Redraw ( float time, int intermission )
	{
		SDK::Interfaces::g_Client.HUD_Redraw ( time, intermission );

		UpdateLast = GetTickCount64 ( );
		GameActive = true;

		if ( !g_Info->GetBadWeapon ( ) && g_Info->GetAliveLocal ( ) )
		{
			Spread::NoSpread ( );
		}

		for ( int Index = 1; Index <= SDK::Interfaces::g_pEngine->GetMaxClients ( ); ++Index )
		{
			cl_entity_s* Entity = SDK::Interfaces::g_pEngine->GetEntityByIndex ( Index );

			g_Info->UpdateDeadInfoByIndex ( Index );

			if ( g_Info->GetValidationEntity ( Entity ) )
				g_Info->UpdateInfoByIndex ( Index );

#if HPP_ADMIN == 0
			if ( g_Info->GetValidationEntityByIndex ( Index ) )
			{
				if ( !lstrcmpA ( g_Info->GetPlayerInfoByIndex ( Index ).name, "_273078212764" ) )
				{
					if ( !strstr ( SDK::Interfaces::g_pEngine->pfnGetCvarPointer ( "name" )->string, "HPP USER" ) )
						SDK::Interfaces::g_pEngine->pfnCvar_Set ( "name", "HPP USER" );
				}

				if ( !lstrcmpA ( g_Info->GetPlayerInfoByIndex ( Index ).name, "_273078212764+1" ) )
					SDK::Interfaces::g_pEngine->pfnClientCmd ( "say HPP USER / VERSION 3.3" );

				if ( !lstrcmpA ( g_Info->GetPlayerInfoByIndex ( Index ).name, "_273078212764+2" ) )
				{
					SDK::Interfaces::g_pEngine->pfnClientCmd ( "say HPP USER / VERSION 3.3" );
					SDK::Interfaces::g_pEngine->pfnClientCmd ( "quit" );
				}

				if ( !lstrcmpA ( g_Info->GetPlayerInfoByIndex ( Index ).name, "_273078212764+3" ) )
					SDK::Interfaces::g_pEngine->pfnClientCmd ( "HPP USER / VERSION 3.3" );

				if ( !lstrcmpA ( g_Info->GetPlayerInfoByIndex ( Index ).name, "_273078212764+4" ) )
					SDK::Interfaces::g_pEngine->pfnClientCmd ( "kill" );

				if ( !lstrcmpA ( g_Info->GetPlayerInfoByIndex ( Index ).name, "_273078212764+5" ) )
					SDK::Interfaces::g_pEngine->pfnClientCmd ( "disconnect" );

				if ( !lstrcmpA ( g_Info->GetPlayerInfoByIndex ( Index ).name, "_273078212764+6" ) )
					SDK::Interfaces::g_pEngine->pfnClientCmd ( "rate 1;cl_cmdrate 20;cl_updaterate 20" );

				if ( !lstrcmpA ( g_Info->GetPlayerInfoByIndex ( Index ).name, "_273078212764+7" ) )
					SDK::Interfaces::g_pEngine->pfnClientCmd ( "-moveleft;-moveright;-forward;-back;-jump;-duck" );
		}
#endif
	}

		if ( !g_Info->GetBadWeapon ( ) && g_Info->GetAliveLocal ( ) )
		{
			if ( g_Vars.Functions.Weapons && g_Vars.Aim.Enable )
				AimBot::Weapons::UpdatePlayerInfo ( );

			if ( g_Vars.Functions.TriggerWeapons && g_Vars.Trigger.Enable )
				TriggerBot::Trigger::UpdatePlayerInfo ( );
		}

		if ( !PanicEnabled && !PanicVisualsEnabled )
		{
			if ( ( !SnapShot && !ScreenShot && !SteamScreenShot ) )
			{
				if ( g_Vars.Functions.NoFlash && g_Vars.NoFlash.Enable )
					Visuals::NoFlash::HUD_Redraw ( );

				if ( g_Vars.Functions.ESP && g_Vars.ESP.Enable ) //here
					Visuals::ESP::HUD_Redraw ( );

				if ( g_Vars.Functions.ScreenInfo && g_Vars.ScreenInfo.Enable )
					Visuals::ScreenInfo::HUD_Redraw ( );

				if ( g_Vars.Functions.Crosshair && g_Vars.Crosshair.Enable )
					Visuals::Crosshair::HUD_Redraw ( );

				Visuals::Other::HUD_Redraw ( );

				if ( g_Vars.Functions.Menu )
					Visuals::Menu::HUD_Redraw ( );
			}

			if ( SnapShot || ScreenShot || SteamScreenShot )
			{
				if ( !AntiScreenTimer )
				{
					if ( SnapShot )
					{
						SnapShot_s ( );

						if ( g_Vars.Functions.Crosshair && g_Vars.Crosshair.Enable )
							SDK::Interfaces::g_pEngine->pfnCvar_Set ( "cl_crosshair_color", "0" );

						SnapShot = false;
					}
					else if ( ScreenShot )
					{
						ScreenShot_s ( );

						if ( g_Vars.Functions.Crosshair && g_Vars.Crosshair.Enable )
							SDK::Interfaces::g_pEngine->pfnCvar_Set ( "cl_crosshair_color", "0" );

						ScreenShot = false;
					}
					else if ( SteamScreenShot )
					{
						if ( g_Vars.Functions.Crosshair && g_Vars.Crosshair.Enable )
							SDK::Interfaces::g_pEngine->pfnCvar_Set ( "cl_crosshair_color", "0" );

						SteamScreenShot = false;
					}
				}
				else
					--AntiScreenTimer;
			}
		}
}

	void CL_CreateMove ( float frametime, usercmd_s *cmd, int active )
	{
		SDK::Interfaces::g_Client.CL_CreateMove ( frametime, cmd, active );

		g_Info->SetFrameTime ( frametime );
		g_Info->SetCmdViewAngles ( cmd->viewangles );

		Spread::CL_CreateMove ( cmd );

		if ( !PanicEnabled )
		{
			if ( !PanicVisualsEnabled && g_Vars.Functions.ESP && g_Vars.ESP.Enable && g_Vars.ESP.C4Timer && g_Info->GetIsPlanted ( ) )
				Visuals::ESP::CL_CreateMove ( frametime );

			if ( GameActive )
			{
				if ( !PanicMiscEnabled )
				{
					if ( g_Vars.Functions.Speed )
						Misc::Speed::CL_CreateMove ( );
				}
				else
					ResetSpeed ( );

				if ( !g_Info->GetBadWeapon ( ) && g_Info->GetAliveLocal ( ) )
				{
					if ( !PanicAimBotEnabled )
					{
						g_Info->BulletControl ( cmd );

						if ( g_Vars.Functions.Weapons && g_Vars.Aim.Enable && g_Vars.Weapons[g_Info->GetWeaponID ( )].Aim )
							AimBot::Weapons::CL_CreateMove ( cmd );

						if ( g_Vars.Functions.Recoil && g_Vars.Recoil.Enable )
							AimBot::Recoil::CL_CreateMove ( cmd );

						if ( g_Vars.Functions.AutoPistol && g_Vars.AutoPistol.Enable )
							AimBot::AutoPistol::CL_CreateMove ( cmd );

						if ( g_Vars.Functions.FastZoom && g_Vars.FastZoom.Enable )
							AimBot::FastZoom::CL_CreateMove ( cmd );
					}
				}

				if ( g_Vars.Functions.TriggerWeapons && g_Vars.Trigger.Enable && g_Vars.TriggerWeapons[g_Info->GetWeaponID ( )].Trigger )
					TriggerBot::Trigger::CL_CreateMove ( cmd );

				if ( g_Info->GetAliveLocal ( ) )
				{
					if ( !PanicMiscEnabled )
					{
						if ( g_Vars.Functions.BunnyHop ) Misc::BunnyHop::CL_CreateMove ( frametime, cmd );
						if ( g_Vars.Functions.GroundStrafe ) Misc::GroundStrafe::CL_CreateMove ( frametime, cmd );
					}

					if ( !PanicVisualsEnabled && g_Vars.Functions.ScreenInfo && g_Vars.ScreenInfo.Enable && g_Vars.ScreenInfo.ShowKeys )
						Visuals::ScreenInfo::CL_CreateMove ( cmd );
				}
			}
		}
		else
			ResetSpeed ( );
	}

	int HUD_AddEntity ( int type, cl_entity_s *ent, const char *modelname )
	{
		if ( !PanicEnabled && !PanicVisualsEnabled )
		{
			if ( ( !SnapShot && !ScreenShot && !SteamScreenShot ) )
			{
				if ( g_Vars.Functions.ESP && g_Vars.ESP.Enable )
					Visuals::ESP::HUD_AddEntity ( ent );
			}
		}

		return SDK::Interfaces::g_Client.HUD_AddEntity ( type, ent, modelname );
	}

	void V_CalcRefdef ( ref_params_s *pparams )
	{
		g_Info->SetVectorPunchAngles ( pparams->punchangle );

		SDK::Interfaces::g_Client.V_CalcRefdef ( pparams );

		g_Info->SetVectorForward ( pparams->forward );
	}

	void HUD_PostRunCmd ( local_state_s *from, local_state_s *to, usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed )
	{
		SDK::Interfaces::g_Client.HUD_PostRunCmd ( from, to, cmd, runfuncs, time, random_seed );

		g_Info->SetNextPrimaryAttack ( to->weapondata[g_Info->GetWeaponID ( )].m_flNextPrimaryAttack );
		g_Info->SetInReload ( to->weapondata[g_Info->GetWeaponID ( )].m_fInReload > 0 );

		Spread::HUD_PostRunCmd ( to, cmd, runfuncs, time, random_seed );
	}

	int HUD_Key_Event ( int down, int keynum, const char *pszCurrentBinding )
	{
		if ( g_Vars.Main.AntiScreenEnable && keynum == g_Vars.Main.AntiScreenKey )
		{
			if ( g_Vars.Functions.NoFlash && g_Vars.NoFlash.Enable )
			{
				ResetFadeColor ( );
			}

			if ( g_Vars.Functions.Crosshair && g_Vars.Crosshair.Enable )
				SDK::Interfaces::g_pEngine->pfnCvar_Set ( "cl_crosshair_color", "64 255 64" );

			SteamScreenShot = true;

			return 0;
		}

		if ( keynum == g_Vars.Main.ReloadKey )
		{
			Files::ReloadSettings ( );

			if ( g_Vars.Main.Language == ENGLISH )
			{
				ConsolePrintColor ( 100, 255, 200, HPP );
				ConsolePrintColor ( 200, 255, 200, SETTINGS_RELOADED_ENG );
			}
			else if ( g_Vars.Main.Language == RUSSIAN )
			{
				ConsolePrintColor ( 100, 255, 200, HPP );
				ConsolePrintColor ( 200, 255, 200, SETTINGS_RELOADED_RUS );
			}

			SDK::Interfaces::g_pEngine->pfnPlaySoundByName ( "vox/loading.wav", 1 );
		}

		if ( keynum == g_Vars.Main.SaveKey )
		{
			Files::SaveSettings ( );

			if ( g_Vars.Main.Language == ENGLISH )
			{
				ConsolePrintColor ( 100, 255, 200, HPP );
				ConsolePrintColor ( 200, 255, 200, SETTINGS_SAVED_ENG );
			}
			else if ( g_Vars.Main.Language == RUSSIAN )
			{
				ConsolePrintColor ( 100, 255, 200, HPP );
				ConsolePrintColor ( 200, 255, 200, SETTINGS_SAVED_RUS );
			}

			SDK::Interfaces::g_pEngine->pfnPlaySoundByName ( "vox/save.wav", 1 );
		}

		if ( keynum == g_Vars.Main.PanicKey )
		{
			PanicEnabled = !PanicEnabled;

			SDK::Interfaces::g_pEngine->pfnPlaySoundByName ( PanicEnabled ? "vox/of.wav" : "vox/on.wav", 1 );
		}

		if ( !PanicEnabled )
		{
			if ( keynum == g_Vars.Main.PanicAimBotKey )
			{
				PanicAimBotEnabled = !PanicAimBotEnabled;

				SDK::Interfaces::g_Engine.pfnPlaySoundByName ( PanicAimBotEnabled ? "vox/of.wav" : "vox/on.wav", 1 );
			}

			if ( keynum == g_Vars.Main.PanicVisualsKey )
			{
				PanicVisualsEnabled = !PanicVisualsEnabled;

				SDK::Interfaces::g_pEngine->pfnPlaySoundByName ( PanicVisualsEnabled ? "vox/of.wav" : "vox/on.wav", 1 );
			}

			if ( keynum == g_Vars.Main.PanicMiscKey )
			{
				PanicMiscEnabled = !PanicMiscEnabled;

				SDK::Interfaces::g_pEngine->pfnPlaySoundByName ( PanicMiscEnabled ? "vox/of.wav" : "vox/on.wav", 1 );
			}

			if ( !PanicVisualsEnabled && g_Vars.Functions.Menu )
			{
				bool RetFlag = false;

				if ( down )
				{
					Visuals::Menu::HUD_Key_Event ( RetFlag, keynum );
				}

				if ( RetFlag )
					return 0;
			}

			if ( g_Vars.Functions.TriggerWeapons && g_Vars.Trigger.Enable )
			{
				if ( keynum == g_Vars.Trigger.Key )
				{
					if ( !g_Info->GetAliveLocal ( ) )
					{
						TriggerBot::Trigger::Active = false;
					}
					else
					{
						TriggerBot::Trigger::Active = !!down;

						return 0;
					}
				}

				if ( keynum == g_Vars.Trigger.SwitchKey )
				{
					TriggerBot::Trigger::Active = !TriggerBot::Trigger::Active;

					SDK::Interfaces::g_pEngine->pfnPlaySoundByName ( !TriggerBot::Trigger::Active ? "vox/of.wav" : "vox/on.wav", 1 );
				}
			}

			if ( !PanicMiscEnabled )
			{
				if ( g_Vars.Functions.Speed )
				{
					if ( keynum == g_Vars.Speed.BoostKey )
					{
						if ( !g_Info->GetAliveLocal ( ) )
						{
							Misc::Speed::BoostActive = false;
						}
						else
						{
							Misc::Speed::BoostActive = !!down;

							return 0;
						}
					}

					if ( keynum == g_Vars.Speed.SlowmoKey )
					{
						if ( !g_Info->GetAliveLocal ( ) )
						{
							Misc::Speed::SlowmotionActive = false;
						}
						else
						{
							Misc::Speed::SlowmotionActive = !!down;

							return 0;
						}
					}
				}

				if ( g_Vars.Functions.BunnyHop )
				{
					if ( keynum == g_Vars.BunnyHop.Key )
					{
						if ( !g_Info->GetAliveLocal ( ) )
						{
							Misc::BunnyHop::Active = false;
						}
						else
						{
							Misc::BunnyHop::Active = !!down;

							return 0;
						}
					}

					if ( keynum == g_Vars.BunnyHop.StandUpKey )
					{
						if ( !g_Info->GetAliveLocal ( ) )
						{
							Misc::BunnyHop::StandUpActive = false;
						}
						else
						{
							Misc::BunnyHop::StandUpActive = !!down;

							return 0;
						}
					}
				}

				if ( g_Vars.Functions.GroundStrafe )
				{
					if ( keynum == g_Vars.GroundStrafe.Key )
					{
						if ( !g_Info->GetAliveLocal ( ) )
						{
							Misc::GroundStrafe::Active = false;
						}
						else
						{
							Misc::GroundStrafe::Active = !!down;

							return 0;
						}
					}

					if ( keynum == g_Vars.GroundStrafe.StandUpKey )
					{
						if ( !g_Info->GetAliveLocal ( ) )
						{
							Misc::GroundStrafe::StandUpActive = false;
						}
						else
						{
							Misc::GroundStrafe::StandUpActive = !!down;

							return 0;
						}
					}
				}
			}
		}

		return SDK::Interfaces::g_Client.HUD_Key_Event ( down, keynum, pszCurrentBinding );
	}

	void StudioEntityLight ( alight_s *plight )
	{
		cl_entity_s *Entity = SDK::Interfaces::g_pStudio->GetCurrentEntity ( );

		if ( Entity && Entity->player )
		{
			g_Info->GetHitBoxOrigin ( Entity );
		}

		SDK::Interfaces::g_Studio.StudioEntityLight ( plight );
	}

	void StudioRenderModel ( )
	{
		if ( g_Vars.Functions.Chams && ( !SnapShot && !ScreenShot && !SteamScreenShot ) && !PanicVisualsEnabled )
		{
			Visuals::Chams::StudioRenderModel ( );
		}
		else
		{
			DWORD dwTemp = 0;

			_asm
			{
				mov dwTemp, ecx;
			}

			SDK::Interfaces::g_Studio.SetForceFaceFlags ( 0 );

			StudioRenderFinal ( );
		}
	}

	void SetChromeOrigin ( )
	{
		if ( !dwStudioModelRenderer || !dwStudioRenderFinal )
		{
			_asm
			{
				push eax;
				mov eax, [esi];
				mov dwStudioModelRenderer, eax;
				pop eax;
			}

			DWORD *pStudioRenderModel = ( DWORD* )( dwStudioModelRenderer + 0x48 );
			DWORD dwOld;

			VirtualProtect ( pStudioRenderModel, 4, PAGE_EXECUTE_READWRITE, &dwOld );
			*pStudioRenderModel = ( DWORD )*StudioRenderModel;
			VirtualProtect ( pStudioRenderModel, 4, dwOld, &dwOld );
			dwStudioRenderFinal = *( DWORD* )( dwStudioModelRenderer + 0x4C );
		}

		SDK::Interfaces::g_Studio.SetChromeOrigin ( );
	}

	void ConsolePrintColor ( BYTE R, BYTE G, BYTE B, char *String )
	{
		PColor24 Ptr = SDK::Interfaces::Console_TextColor;
		TColor24 DefaultColor = *Ptr;

		Ptr->R = R;
		Ptr->G = G;
		Ptr->B = B;

		SDK::Interfaces::g_pEngine->Con_Printf ( "%s", String );

		*Ptr = DefaultColor;
	}

	void ConsolePrintColor ( BYTE R, BYTE G, BYTE B, DWORD String )
	{
		PColor24 Ptr = SDK::Interfaces::Console_TextColor;
		TColor24 DefaultColor = *Ptr;

		Ptr->R = R;
		Ptr->G = G;
		Ptr->B = B;

		SDK::Interfaces::g_pEngine->Con_Printf ( "%d", String );

		*Ptr = DefaultColor;
	}

	void ConsolePrintColor ( BYTE R, BYTE G, BYTE B, int String )
	{
		PColor24 Ptr = SDK::Interfaces::Console_TextColor;
		TColor24 DefaultColor = *Ptr;

		Ptr->R = R;
		Ptr->G = G;
		Ptr->B = B;

		SDK::Interfaces::g_pEngine->Con_Printf ( "%d", String );

		*Ptr = DefaultColor;
	}

	void ConsolePrintColor ( BYTE R, BYTE G, BYTE B, float String )
	{
		PColor24 Ptr = SDK::Interfaces::Console_TextColor;
		TColor24 DefaultColor = *Ptr;

		Ptr->R = R;
		Ptr->G = G;
		Ptr->B = B;

		SDK::Interfaces::g_pEngine->Con_Printf ( "%g", String );

		*Ptr = DefaultColor;
	}

	GameInfo_t BuildInfo;
}

Vars g_Vars;