#include "Engine.h"

namespace SDK
{
	cl_clientfunc_t *Interfaces::g_pClient = nullptr;
	cl_enginefunc_t *Interfaces::g_pEngine = nullptr;
	engine_studio_api_t *Interfaces::g_pStudio = nullptr;
	playermove_t *Interfaces::g_pPlayerMove = nullptr;
	screenfade_t *Interfaces::g_pScreenFade = nullptr;

	SCREENINFO Interfaces::g_Screen;
	PUserMsg Interfaces::g_pUserMsgBase;
	PEngineMsg Interfaces::g_pEngineMsgBase;
	PColor24 Interfaces::Console_TextColor;
	cl_clientfunc_t Interfaces::g_Client;
	cl_enginefunc_t Interfaces::g_Engine;
	engine_studio_api_t Interfaces::g_Studio;

	namespace Offset
	{
		void Initialize ( HANDLE& hProcessReloadThread )
		{
			int FindCounter = 0;

		StartHook:
			if ( FindCounter >= FIND_COUNTER_VALUE )
			{
				if ( !Interfaces::g_pClient )
				{
					Files::InjectLog ( CLIENT_FIND_ERROR );
					Utils::Error ( true, CLIENT_FIND_ERROR );
				}

				if ( !Interfaces::g_pEngine )
				{
					Files::InjectLog ( ENGINE_FIND_ERROR );
					Utils::Error ( true, ENGINE_FIND_ERROR );
				}

				if ( !Interfaces::g_pStudio )
				{
					Files::InjectLog ( STUDIO_FIND_ERROR );
					Utils::Error ( true, STUDIO_FIND_ERROR );
				}

				if ( !Interfaces::g_pPlayerMove )
				{
					Files::InjectLog ( PPMOVE_PTR_ERROR );
					Utils::Error ( true, PPMOVE_PTR_ERROR );
				}
			}

			Sleep ( 100 );

			++FindCounter;

			if ( Engine::Offset::GetModuleInfo ( ) )
			{
				static bool ClientLog, EngineLog, StudioLog, PlayerMoveLog, UserMsgLog, EngineMsgLog;

				DWORD ClientTable = Engine::Offset::FindClientTable ( );

				if ( ClientTable )
				{
					Interfaces::g_pClient = ( cl_clientfunc_t* )ClientTable;

					if ( !ClientLog )
					{
						Files::InjectLog ( "	g_pClient: 0x%X", Interfaces::g_pClient );

						ClientLog = true;
					}

					Utils::native_memcpy ( &Interfaces::g_Client, Interfaces::g_pClient, sizeof ( cl_clientfunc_t ) );

					if ( Interfaces::g_Client.Initialize )
					{
						DWORD EngineTable = Engine::Offset::FindEngineTable ( );

						if ( EngineTable )
						{
							Interfaces::g_pEngine = ( cl_enginefunc_t* )EngineTable;

							if ( !EngineLog )
							{
								Files::InjectLog ( "	g_pEngine: 0x%X", Interfaces::g_pEngine );

								EngineLog = true;
							}

							Utils::native_memcpy ( &Interfaces::g_Engine, Interfaces::g_pEngine, sizeof ( cl_enginefunc_t ) );

							if ( Interfaces::g_Engine.V_CalcShake )
							{
								DWORD StudioTable = Engine::Offset::FindStudioTable ( );

								if ( StudioTable )
								{
									Interfaces::g_pStudio = ( engine_studio_api_t* )StudioTable;

									if ( !StudioLog )
									{
										Files::InjectLog ( "	g_pStudio: 0x%X", Interfaces::g_pStudio );

										StudioLog = true;
									}

									Utils::native_memcpy ( &Interfaces::g_Studio, Interfaces::g_pStudio, sizeof ( engine_studio_api_t ) );

									if ( Interfaces::g_Studio.StudioSetupSkin )
									{
										DWORD PlayerMove = Engine::Offset::FindPlayerMove ( );

										if ( PlayerMove )
										{
											Interfaces::g_pPlayerMove = ( playermove_t* )PlayerMove;

											if ( !PlayerMoveLog )
											{
												Files::InjectLog ( "	g_pPlayerMove: 0x%X", Interfaces::g_pPlayerMove );

												PlayerMoveLog = true;
											}

											DWORD UserMsg = Engine::Offset::FindUserMsgBase ( );

											if ( UserMsg )
											{
												Interfaces::g_pUserMsgBase = ( PUserMsg )UserMsg;

												if ( !UserMsgLog )
												{
													Files::InjectLog ( "	g_pUserMsgBase: 0x%X", Interfaces::g_pUserMsgBase );

													UserMsgLog = true;
												}

												DWORD EngineMsg = Engine::Offset::FindSVCMessages ( );

												if ( EngineMsg )
												{
													Interfaces::g_pEngineMsgBase = ( PEngineMsg )EngineMsg;

													if ( !EngineMsgLog )
													{
														Files::InjectLog ( "	g_pEngineMsgBase: 0x%X", Interfaces::g_pEngineMsgBase );

														EngineMsgLog = true;
													}

													Files::InjectLog ( "FindCounterValue: %d", FindCounter );

													while ( !Client::FirstFrame )
													{
														Hook::HookClient ( );
														Hook::HookStudio ( );

														Sleep ( 100 );
													}

													hProcessReloadThread = CreateThread ( 0, 0, ProcessReload, 0, 0, 0 );
												}
												else goto StartHook;
											}
											else goto StartHook;
										}
										else goto StartHook;
									}
									else goto StartHook;
								}
								else goto StartHook;
							}
							else goto StartHook;
						}
						else goto StartHook;
					}
					else goto StartHook;
				}
				else goto StartHook;
			}
			else goto StartHook;
		}
	}

	namespace Hook
	{
		void Initialize ( )
		{
			HookUserMessages ( );
			HookEngineMessages ( );
			HookOpenGL ( );
		}

		void HookClient ( )
		{
			Files::InjectLog ( "HookClient..." );

			SDK::Interfaces::g_pClient->HUD_Frame = Client::HUD_Frame;
			SDK::Interfaces::g_pClient->HUD_Key_Event = Client::HUD_Key_Event;
			SDK::Interfaces::g_pClient->HUD_Redraw = Client::HUD_Redraw;
			SDK::Interfaces::g_pClient->V_CalcRefdef = Client::V_CalcRefdef;
			SDK::Interfaces::g_pClient->CL_CreateMove = Client::CL_CreateMove;
			SDK::Interfaces::g_pClient->HUD_AddEntity = Client::HUD_AddEntity;
			SDK::Interfaces::g_pClient->HUD_PostRunCmd = Client::HUD_PostRunCmd;
		}

		void HookStudio ( )
		{
			Files::InjectLog ( "HookStudio..." );

			SDK::Interfaces::g_pStudio->StudioEntityLight = Client::StudioEntityLight;
			SDK::Interfaces::g_pStudio->SetChromeOrigin = Client::SetChromeOrigin;
		}

		void HookUserMessages ( )
		{
			Files::InjectLog ( "HookUserMessages..." );

			pScoreAtrrib = Utils::HookUserMsg ( "ScoreAttrib", ScoreAtrrib );
			pResetHUD = Utils::HookUserMsg ( "ResetHUD", ResetHUD );
			pSetFOV = Utils::HookUserMsg ( "SetFOV", SetFOV );
			pTextMsg = Utils::HookUserMsg ( "TextMsg", TextMsg );
			pTeamInfo = Utils::HookUserMsg ( "TeamInfo", TeamInfo );
			pCurWeapon = Utils::HookUserMsg ( "CurWeapon", CurWeapon );
			pWeaponList = Utils::HookUserMsg ( "WeaponList", WeaponList );
			pDeathMsg = Utils::HookUserMsg ( "DeathMsg", DeathMsg );
		}

		void HookEngineMessages ( )
		{
			Files::InjectLog ( "HookEngineMessages..." );

			pSVC_sound = Utils::HookEngineMsg ( "svc_sound", SVC_Sound );
			pSVC_SpawnStaticSound = Utils::HookEngineMsg ( "svc_spawnstaticsound", SVC_SpawnStaticSound );
			pSVC_StuffText = Utils::HookEngineMsg ( "svc_stufftext", SVC_StuffText );
			pSVC_NewUserMsg = Utils::HookEngineMsg ( "svc_newusermsg", SVC_NewUserMsg );
			pSVC_UpdateUserInfo = Utils::HookEngineMsg ( "svc_updateuserinfo", SVC_UpdateUserInfo );
			pSVC_SendCvarValue = Utils::HookEngineMsg ( "svc_sendcvarvalue", SVC_SendCvarValue );
			pSVC_SendCvarValue2 = Utils::HookEngineMsg ( "svc_sendcvarvalue2", SVC_SendCvarValue2 );
			pSVC_Director = Utils::HookEngineMsg ( "svc_director", SVC_Director );
		}

		void HookOpenGL ( )
		{
			Files::InjectLog ( "HookOpenGL..." );

			HMODULE OpenGL = GetModuleHandle ( "opengl32.dll" );

			DWORD dwglBegin = ( DWORD )OpenGL::DetourFunc ( ( LPBYTE )GetProcAddress ( OpenGL, "glBegin" ), ( LPBYTE )&OpenGL::Hooked_glBegin, 6 );
			DWORD dwglVertex3fv = ( DWORD )OpenGL::DetourFunc ( ( LPBYTE )GetProcAddress ( OpenGL, "glVertex3fv" ), ( LPBYTE )&OpenGL::Hooked_glVertex3fv, 6 );
			DWORD dwglColor4f = ( DWORD )OpenGL::DetourFunc ( ( LPBYTE )GetProcAddress ( OpenGL, "glColor4f" ), ( LPBYTE )&OpenGL::Hooked_glColor4f, 6 );

			if ( dwglBegin ) OpenGL::pglBegin = ( OpenGL::glBegin_t )dwglBegin;
			if ( dwglVertex3fv ) OpenGL::pglVertex3fv = ( OpenGL::glVertex3fv_t )dwglVertex3fv;
			if ( dwglColor4f ) OpenGL::pglColor4f = ( OpenGL::glColor4f_t )dwglColor4f;
		}
	}
}