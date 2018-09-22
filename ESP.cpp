#include "ESP.h"

namespace Client
{
	namespace Functions
	{
		namespace Visuals
		{
			EntityStruct ESP::Entity[MAX_ENTITY];
			SoundStruct ESP::Sound[MAX_SOUNDS];

			int ESP::EntityIndex;
			int ESP::SoundIndex;

			BYTE ESP::BoxColor[3];
			BYTE ESP::FontColor[4];

			void ESP::PlayerFilters ( const int& Index, bool& RetFlag )
			{
				RetFlag = true;

				bool OnlyEnemy = g_Vars.ESP.Player == 1.0f && g_Info->GetPlayerTeamByIndex ( Index ) == g_Info->GetPlayerTeam ( );
				bool OnlyVisible = g_Vars.ESP.PlayerVisibleOnly && !g_Info->GetVisibilityEntityByIndex ( Index );

				if ( g_Info->GetAliveLocal ( ) && ( OnlyEnemy || OnlyVisible ) )
				{
					return;
				}

				RetFlag = false;
			}

			void ESP::GetColorPlayerBox ( const int &Index )
			{
				for ( int i = 0; i < sizeof ( BoxColor ); ++i )
				{
					if ( g_Info->GetPlayerTeamByIndex ( Index ) == TERRORIST && g_Info->GetVisibilityEntityByIndex ( Index ) )
					{
						BoxColor[i] = BYTE ( g_Vars.ESP.ColorTVis[i] );
					}
					else if ( g_Info->GetPlayerTeamByIndex ( Index ) == TERRORIST )
					{
						BoxColor[i] = BYTE ( g_Vars.ESP.ColorTHide[i] );
					}
					else if ( g_Info->GetPlayerTeamByIndex ( Index ) == CT && g_Info->GetVisibilityEntityByIndex ( Index ) )
					{
						BoxColor[i] = BYTE ( g_Vars.ESP.ColorCTVis[i] );
					}
					else if ( g_Info->GetPlayerTeamByIndex ( Index ) == CT )
					{
						BoxColor[i] = BYTE ( g_Vars.ESP.ColorCTHide[i] );
					}
					else if ( g_Info->GetVisibilityEntityByIndex ( Index ) )
					{
						BoxColor[i] = 255;
					}
					else
					{
						BoxColor[i] = 180;
					}
				}
			}

			void ESP::SetFontColor ( )
			{
				FontColor[0] = g_Vars.ESP.FontColor[0];
				FontColor[1] = g_Vars.ESP.FontColor[1];
				FontColor[2] = g_Vars.ESP.FontColor[2];
				FontColor[3] = g_Vars.ESP.FontColor[3];
			}

			void ESP::GetC4TimerValue ( )
			{
				if ( g_Vars.ESP.C4Timer == 1.0f )
				{
					g_Info->SetC4Timer ( 0.0f );
				}
				else if ( g_Vars.ESP.C4Timer >= 2.0f )
				{
					g_Info->SetC4Timer ( g_Vars.ESP.C4TimerValue );
				}
			}

			void ESP::PlayerBox ( const int &Index, const int &x, const int &w, const int &PlayerBoxHeight, const Vector2D &ScreenTop )
			{
				GetColorPlayerBox ( Index );

				if ( g_Vars.ESP.PlayerBoxFilled )
				{
					Renderer::g_Drawing->FillArea ( x, ( int )ScreenTop[1], w, PlayerBoxHeight,
						BoxColor[0], BoxColor[1], BoxColor[2], BYTE ( g_Vars.ESP.PlayerBoxFilled ) );
				}

				if ( g_Vars.ESP.PlayerBox == 1.0f )
				{
					Renderer::g_Drawing->Box ( x, ( int )ScreenTop[1], w, PlayerBoxHeight, 1, BoxColor[0], BoxColor[1], BoxColor[2], 255 );
				}
				else if ( g_Vars.ESP.PlayerBox == 2.0f )
				{
					Renderer::g_Drawing->BoxOutline ( x, ( int )ScreenTop[1], w, PlayerBoxHeight, 1, BoxColor[0], BoxColor[1], BoxColor[2], 255 );
				}
				else if ( g_Vars.ESP.PlayerBox == 3.0f )
				{
					Renderer::g_Drawing->BoxCorner ( x, ( int )ScreenTop[1], w, PlayerBoxHeight, 1, BoxColor[0], BoxColor[1], BoxColor[2], 255 );
				}
				else if ( g_Vars.ESP.PlayerBox >= 4.0f )
				{
					Renderer::g_Drawing->BoxCornerOutline ( x, ( int )ScreenTop[1], w, PlayerBoxHeight, 1, BoxColor[0], BoxColor[1], BoxColor[2], 255 );
				}
			}

			void ESP::PlayerName ( const int &Index, const int &PlayerBoxHeight, const Vector2D &ScreenTop )
			{
				int y = PlayerBoxHeight - 5 + ( int )ScreenTop[1];

				if ( strstr ( g_Info->GetPlayerInfoByIndex ( Index ).name, "kilabeez" ) )
				{
					Renderer::g_Verdana->Print ( ( int )ScreenTop[0], y, 0, 255, 0, FontColor[3],
						g_Vars.ESP.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, g_Info->GetPlayerInfoByIndex ( Index ).name );

					return;
				}

				if ( strstr ( g_Info->GetPlayerInfoByIndex ( Index ).name, "Fletia" ) )
				{
					Renderer::g_Verdana->Print ( ( int )ScreenTop[0], y, 255, 192, 203, FontColor[3],
						g_Vars.ESP.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, g_Info->GetPlayerInfoByIndex ( Index ).name );

					return;
				}

				Renderer::g_Verdana->Print ( ( int )ScreenTop[0], y, FontColor[0], FontColor[1], FontColor[2],
					FontColor[3], g_Vars.ESP.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, g_Info->GetPlayerInfoByIndex ( Index ).name );
			}

			void ESP::PlayerWeapon ( cl_entity_s *Entity, const Vector2D &ScreenBot, const Vector2D &ScreenTop )
			{
				float y = ScreenBot[1] + ( ( g_Vars.ESP.PlayerDistance ? 24.0f : 12.0f ) - ( ScreenBot[1] - ScreenTop[1] ) );

				int SequenceInfo[] =
				{
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 1, 2, 0, 1, 2, 0, 1, 2, 0,
					1, 2, 0, 1, 1, 2, 0, 1, 1, 2,
					0, 1, 2, 0, 1, 2, 0, 1, 2, 0,
					1, 2, 0, 1, 2, 0, 1, 2, 0, 1,
					2, 0, 1, 2, 0, 0, 0, 4, 0, 4,
					0, 5, 0, 5, 0, 0, 1, 1, 2, 0,
					1, 1, 2, 0, 1, 0, 1, 0, 1, 2,
					0, 1, 2, 3, 3, 3, 3, 3, 3, 3,
					3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
					3
				};

				if ( SequenceInfo[Entity->curstate.sequence] == 2 )
				{
					Renderer::g_Verdana->Print ( ( int )ScreenTop[0], ( int )y + 12, 255, 80, 80,
						255, g_Vars.ESP.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, "reloading" );
				}
				else if ( SequenceInfo[Entity->curstate.sequence] == 5 )
				{
					Renderer::g_Verdana->Print ( ( int )ScreenTop[0], ( int )y + 12, 255, 80, 80,
						255, g_Vars.ESP.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, "planting c4" );
				}

				model_s *Model = SDK::Interfaces::g_pStudio->GetModelByIndex ( Entity->curstate.weaponmodel );

				if ( Model && Model->name )
				{
					char WeaponName[64];

					int len = lstrlenA ( SDK::Interfaces::g_pStudio->GetModelByIndex ( Entity->curstate.weaponmodel )->name + 9 ) - 3;

					lstrcpynA ( WeaponName, SDK::Interfaces::g_pStudio->GetModelByIndex ( Entity->curstate.weaponmodel )->name + 9, len );

					WeaponName[len] = '\0';

					Renderer::g_Verdana->Print ( ( int )ScreenTop[0], ( int )y, FontColor[0], FontColor[1],
						FontColor[2], FontColor[3], g_Vars.ESP.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, WeaponName );
				}
			}

			float ESP::GetPlayerDistance ( const BYTE &Index, const bool &Meters )
			{
				cl_entity_s *Entity = SDK::Interfaces::g_pEngine->GetEntityByIndex ( Index );

				float flDistance = g_Info->GetDistanceToEntity ( Entity->origin );

				return Meters ? flDistance < 0.0f ? 0.0f : flDistance * 0.025f : flDistance < 0.0f ? 0.0f : flDistance;
			}

			void ESP::PlayerDistance ( const int &Index, const Vector2D &ScreenBot, const Vector2D &ScreenTop )
			{
				float y = ScreenBot[1] + ( 12.0f - ( ScreenBot[1] - ScreenTop[1] ) );

				int DistanceUnits = ( int )GetPlayerDistance ( Index, false );
				int DistanceMeters = ( int )GetPlayerDistance ( Index, true );

				BYTE PlayerDistanceColor[3] = { 255, 255, 255 };

				if ( DistanceUnits >= 0 && DistanceUnits <= 1000 )
				{
					PlayerDistanceColor[0] = 255;
					PlayerDistanceColor[1] = DistanceUnits >= 50 ? ( BYTE )Utils::Interp ( 50.0f, ( float )DistanceUnits, 1000.0f, 255.0f, 80.0f ) : 255;
					PlayerDistanceColor[2] = DistanceUnits <= 50 ? ( BYTE )Utils::Interp ( 0.0f, ( float )DistanceUnits, 50.0f, 255.0f, 80.0f ) : 80;
				}
				else if ( DistanceUnits > 1000 )
				{
					PlayerDistanceColor[0] = 255;
					PlayerDistanceColor[1] = 80;
					PlayerDistanceColor[2] = 80;
				}

				if ( g_Vars.ESP.PlayerDistance == 1.0f )
				{
					Renderer::g_Verdana->Print ( ( int )ScreenTop[0], ( int )y, PlayerDistanceColor[0], PlayerDistanceColor[1],
						PlayerDistanceColor[2], 255, g_Vars.ESP.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, "%d u", DistanceUnits );
				}
				else if ( g_Vars.ESP.PlayerDistance >= 2.0f )
				{
					Renderer::g_Verdana->Print ( ( int )ScreenTop[0], ( int )y, PlayerDistanceColor[0], PlayerDistanceColor[1],
						PlayerDistanceColor[2], 255, g_Vars.ESP.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, "%d m", DistanceMeters );
				}
			}

			void ESP::WorldNades ( const int &Index, const Vector2D &EntityScreen )
			{
				Vector uppt = Entity[Index].vOrigin - g_Info->GetVectorEyePosition ( );

				float Length = uppt.Length ( );

				if ( g_Vars.ESP.WorldNades && Entity[Index].Type == 3 )
				{
					if ( strstr ( Entity[Index].Name, "hegrenade" ) )
					{
						Renderer::g_Drawing->Circle ( ( int )EntityScreen[0], ( int )EntityScreen[1], int ( 4000.0f / Length ), 100, 2, 255, 50, 50, 255 );
					}
					else if ( strstr ( Entity[Index].Name, "flash" ) )
					{
						Renderer::g_Drawing->Circle ( ( int )EntityScreen[0], ( int )EntityScreen[1], int ( 4000.0f / Length ), 100, 2, 255, 255, 255, 255 );
					}
					else if ( strstr ( Entity[Index].Name, "smoke" ) )
					{
						Renderer::g_Drawing->Circle ( ( int )EntityScreen[0], ( int )EntityScreen[1], int ( 4000.0f / Length ), 100, 2, 50, 255, 50, 255 );
					}
				}
			}

			void ESP::WorldWeapons ( const int& Index, const Vector2D& EntityScreen, const char* Weapon )
			{
				if ( strstr ( Entity[Index].Name, Weapon ) )
				{
					Renderer::g_Drawing->Box ( ( int )EntityScreen[0] - 2, ( int )EntityScreen[1], 6, 6, 1, 0, 0, 0, 255 );
					Renderer::g_Drawing->FillArea ( ( int )EntityScreen[0] - 1, ( int )EntityScreen[1] + 1, 4, 4, 255, 120, 50, 255 );

					Renderer::g_Verdana->Print ( ( int )EntityScreen[0], ( int )EntityScreen[1] + 15, FontColor[0],
						FontColor[1], FontColor[2], FontColor[3], g_Vars.ESP.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, Weapon );
				}
			}

			void ESP::WorldC4 ( const int& Index, const Vector2D& EntityScreen )
			{
				if ( strstr ( Entity[Index].Name, "backpack" ) )
				{
					Renderer::g_Drawing->Box ( ( int )EntityScreen[0] - 2, ( int )EntityScreen[1], 6, 6, 1, 0, 0, 0, 255 );
					Renderer::g_Drawing->FillArea ( ( int )EntityScreen[0] - 1, ( int )EntityScreen[1] + 1, 4, 4, 255, 0, 0, 255 );

					Renderer::g_Verdana->Print ( ( int )EntityScreen[0], ( int )EntityScreen[1] + 15, FontColor[0],
						FontColor[1], FontColor[2], FontColor[3], g_Vars.ESP.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, "c4" );
				}
			}

			void ESP::WorldC4Planted ( const int& Index, const Vector2D& EntityScreen )
			{
				if ( strstr ( Entity[Index].Name, "c4" ) )
				{
					Renderer::g_Drawing->Box ( ( int )EntityScreen[0] - 2, ( int )EntityScreen[1], 6, 6, 1, 0, 0, 0, 255 );
					Renderer::g_Drawing->FillArea ( ( int )EntityScreen[0] - 1, ( int )EntityScreen[1] + 1, 4, 4, 255, 0, 0, 255 );

					Renderer::g_Verdana->Print ( ( int )EntityScreen[0], ( int )EntityScreen[1] + 15, FontColor[0],
						FontColor[1], FontColor[2], FontColor[3], g_Vars.ESP.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, "bomb" );

					if ( g_Vars.ESP.C4Timer && g_Info->GetIsPlanted ( ) )
					{
						Renderer::g_Verdana->Print ( ( int )EntityScreen[0], ( int )EntityScreen[1] + 27, FontColor[0], FontColor[1], FontColor[2],
							FontColor[3], g_Vars.ESP.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, "time: %.2f", g_Info->GetC4Timer ( ) );
					}
				}
			}

			void ESP::AddEntity ( const char *Name, const Vector &vOrigin, const int &Type )
			{
				if ( EntityIndex < MAX_ENTITY )
				{
					lstrcpy ( Entity[EntityIndex].Name, Name );

					Entity[EntityIndex].vOrigin = vOrigin;
					Entity[EntityIndex].Type = Type;

					++EntityIndex;
				}
				else
					ClearEntity ( );
			}

			void ESP::ClearEntity ( )
			{
				for ( int Index = 0; Index < EntityIndex; ++Index )
				{
					memset ( &Entity[Index].Name, 64, 0 );

					Entity[Index].vOrigin = Vector ( 0.0f );
					Entity[Index].Type = 0;
				}

				EntityIndex = 0;
			}

			void ESP::AddSound ( DWORD64 dwTime, Vector vOrigin, BYTE R, BYTE G, BYTE B )
			{
				if ( SoundIndex < MAX_SOUNDS )
				{
					Sound[SoundIndex].dwTime = dwTime;
					Sound[SoundIndex].vOrigin = vOrigin;
					Sound[SoundIndex].R = R;
					Sound[SoundIndex].G = G;
					Sound[SoundIndex].B = B;

					++SoundIndex;
				}
				else
					ClearSound ( );
			}

			void ESP::ClearSound ( )
			{
				for ( int Index = 0; Index < SoundIndex; ++Index )
				{
					Sound[Index].dwTime = 0;
					Sound[Index].vOrigin = Vector ( 0.0f );
				}

				SoundIndex = 0;
			}

			void ESP::DrawPlayer ( cl_entity_s* Entity )
			{
				bool RetFlag;

				PlayerFilters ( Entity->index, RetFlag );

				if ( RetFlag ) return;

				/*Vector vTop ( Entity->origin[0], Entity->origin[1], Entity->origin[2] + Entity->curstate.mins[2] );
				Vector vBot ( Entity->origin[0], Entity->origin[1], Entity->origin[2] + Entity->curstate.maxs[2] );

				Vector2D ScreenTop, ScreenBot;

				if ( Utils::CalcScreen ( vTop, ScreenTop ) && Utils::CalcScreen ( vBot, ScreenBot ) )
				{
					float Height = ScreenBot[1] - ScreenTop[1];
					float PlayerBoxHeight = g_Info->GetDuckedEntity ( Entity ) ? Height : Height * 0.9f;
					float x = ScreenTop[0] - ( PlayerBoxHeight * 0.25f );
					float w = PlayerBoxHeight * 0.5f;

					if ( g_Vars.ESP.PlayerBox ) PlayerBox ( Entity->index, ( int )x, ( int )w, ( int )PlayerBoxHeight, ScreenTop );
					if ( g_Vars.ESP.PlayerName ) PlayerName ( Entity->index, ( int )PlayerBoxHeight, ScreenTop );
					if ( g_Vars.ESP.PlayerWeapon ) PlayerWeapon ( Entity, ScreenBot, ScreenTop );
					if ( g_Vars.ESP.PlayerDistance ) PlayerDistance ( Entity->index, ScreenBot, ScreenTop );
				}*/

				Vector vOrigin = Entity->origin;
				Vector vHead = g_Info->GetHitBoxByIndex ( Entity->index, 11 );
				
				vOrigin[2] -= 42.0f;
				vHead[2] += 10.0f;

				Vector2D vScreenOrigin, vScreenHead;

				if ( Utils::CalcScreen ( vOrigin, vScreenOrigin ) && Utils::CalcScreen ( vHead, vScreenHead ) )
				{
					float Height = vScreenOrigin[1] - vScreenHead[1];
					float Width = Height * 0.5f;
					float x = vScreenOrigin[0] - Width / 2.0f;

					Renderer::g_Drawing->BoxCorner ( ( int )x, ( int )vScreenHead[1], ( int )Width, ( int )Height, 1, 0, 100, 255, 255 );
				}
			}

			void ESP::DrawWorld ( )
			{
				for ( int Index = 0; Index < EntityIndex; ++Index )
				{
					Vector2D EntityScreen;

					if ( Utils::CalcScreen ( Entity[Index].vOrigin, EntityScreen ) && !Entity[Index].vOrigin.IsZero ( ) )
					{
						if ( g_Vars.ESP.WorldItems && Entity[Index].Type == 1 )
						{
							WorldWeapons ( Index, EntityScreen, "usp" );
							WorldWeapons ( Index, EntityScreen, "glock18" );
							WorldWeapons ( Index, EntityScreen, "deagle" );
							WorldWeapons ( Index, EntityScreen, "p228" );
							WorldWeapons ( Index, EntityScreen, "elite" );
							WorldWeapons ( Index, EntityScreen, "fiveseven" );
							WorldWeapons ( Index, EntityScreen, "m3" );
							WorldWeapons ( Index, EntityScreen, "xm1014" );
							WorldWeapons ( Index, EntityScreen, "mp5" );
							WorldWeapons ( Index, EntityScreen, "tmp" );
							WorldWeapons ( Index, EntityScreen, "p90" );
							WorldWeapons ( Index, EntityScreen, "mac10" );
							WorldWeapons ( Index, EntityScreen, "ump45" );
							WorldWeapons ( Index, EntityScreen, "famas" );
							WorldWeapons ( Index, EntityScreen, "sg552" );
							WorldWeapons ( Index, EntityScreen, "ak47" );
							WorldWeapons ( Index, EntityScreen, "m4a1" );
							WorldWeapons ( Index, EntityScreen, "aug" );
							WorldWeapons ( Index, EntityScreen, "scout" );
							WorldWeapons ( Index, EntityScreen, "awp" );
							WorldWeapons ( Index, EntityScreen, "g3sg1" );
							WorldWeapons ( Index, EntityScreen, "sg550" );
							WorldWeapons ( Index, EntityScreen, "galil" );
							WorldWeapons ( Index, EntityScreen, "m249" );
							WorldWeapons ( Index, EntityScreen, "shield" );
							WorldWeapons ( Index, EntityScreen, "thighpack" );
						}

						if ( g_Vars.ESP.WorldC4 && Entity[Index].Type == 1 )
						{
							WorldC4 ( Index, EntityScreen );
							WorldC4Planted ( Index, EntityScreen );
						}

						WorldNades ( Index, EntityScreen );
					}
				}

				ClearEntity ( );
			}

			void ESP::DrawC4Timer ( )
			{
				Renderer::g_Fonts->Print ( int ( SDK::Interfaces::g_Screen.iWidth / 1.5f ), 15, FontColor[0], FontColor[1],
					FontColor[2], FontColor[3], FL_OUTLINE, "C4Timer: %d", ( int )g_Info->GetC4Timer ( ) );
			}

			void ESP::DrawSound ( )
			{
				for ( int Index = 0; Index < SoundIndex; ++Index )
				{
					Vector uppt = Sound[Index].vOrigin - g_Info->GetVectorEyePosition ( );

					float SoundSize = 10000.0f / uppt.Length ( );

					DWORD64 SoundTime = Sound[Index].dwTime + ( DWORD64 )g_Vars.ESP.SoundFadeTime;

					if ( SoundTime <= GetTickCount64 ( ) )
					{
						Sound[Index].dwTime = 0;
						Sound[Index].vOrigin = Vector ( 0.0f );
					}
					else
					{
						Vector2D SoundScreen;

						float size = Utils::Interp ( ( float )Sound[Index].dwTime, ( float )GetTickCount64 ( ), ( float )SoundTime, SoundSize, 0.0f );

						if ( Utils::CalcScreen ( Sound[Index].vOrigin, SoundScreen ) && !Sound[Index].vOrigin.IsZero ( ) )
						{
							Renderer::g_Drawing->Box ( int ( SoundScreen[0] - ( size / 2.0f ) ), int ( SoundScreen[1] - ( size / 2.0f ) ),
								( int )size, ( int )size, 1, Sound[Index].R, Sound[Index].G, Sound[Index].B,
								BYTE ( Utils::Interp ( float ( Sound[Index].dwTime ), float ( GetTickCount64 ( ) ), ( float )SoundTime, 255.0f, 0.0f ) ) );
						}
					}
				}
			}

			void ESP::HUD_AddEntity ( cl_entity_s *Entity )
			{
				if ( ( g_Vars.ESP.WorldItems || g_Vars.ESP.WorldNades || g_Vars.ESP.WorldC4 ) && Entity->model->name && Entity->model && Entity )
				{
					if ( strstr ( Entity->model->name, "w_" ) )
					{
						char Name[64];

						int len = lstrlenA ( Entity->model->name + 7 ) - 3;

						lstrcpynA ( Name, Entity->model->name + 7, len );

						Name[len] = '\0';

						if ( strstr ( Entity->model->name, "hegrenade" ) )
						{
							AddEntity ( Name, Entity->origin, 3 );
						}
						else if ( strstr ( Entity->model->name, "flash" ) )
						{
							AddEntity ( Name, Entity->origin, 3 );
						}
						else if ( strstr ( Entity->model->name, "smoke" ) )
						{
							AddEntity ( Name, Entity->origin, 3 );
						}
						else
						{
							if ( g_Vars.ESP.WorldItems || g_Vars.ESP.WorldC4 )
								AddEntity ( Name, Entity->origin, 1 );
						}
					}
				}

				if ( g_Vars.ESP.Player && g_Vars.ESP.PlayerBarrel && g_Info->GetValidationEntity ( Entity ) &&
					Entity && Entity->player && Entity->index != g_Info->GetLocalIndex ( ) )
				{
					bool RetFlag;

					PlayerFilters ( Entity->index, RetFlag );

					if ( RetFlag ) return;

					int BeamIndex = SDK::Interfaces::g_pEngine->pEventAPI->EV_FindModelIndex ( "sprites/laserbeam.spr" );

					Vector vEnd, vUp, vRight, vForward;
					Vector vEntityViewOrg = Entity->origin;

					if ( !Entity->curstate.usehull )
					{
						vEntityViewOrg[2] += 17.0f;
					}
					else if ( Entity->curstate.usehull == 1 )
					{
						vEntityViewOrg[2] += 12.0f;
					}

					SDK::Interfaces::g_pEngine->pfnAngleVectors ( Entity->angles, vForward, vRight, vUp );

					vForward[2] = -vForward[2];

					float PlayerBarrelColor[3] =
					{
						0.0f, 0.0f, 0.0f
					};

					if ( g_Info->GetPlayerTeamByIndex ( Entity->index ) == TERRORIST )
					{
						PlayerBarrelColor[0] = 255.0f;
						PlayerBarrelColor[1] = 0.0f;
						PlayerBarrelColor[2] = 0.0f;
					}
					else if ( g_Info->GetPlayerTeamByIndex ( Entity->index ) == CT )
					{
						PlayerBarrelColor[0] = 0.0f;
						PlayerBarrelColor[1] = 0.0f;
						PlayerBarrelColor[2] = 255.0f;
					}
					else
					{
						PlayerBarrelColor[0] = 255.0f;
						PlayerBarrelColor[1] = 255.0f;
						PlayerBarrelColor[2] = 255.0f;
					}

					vEnd = vEntityViewOrg + vForward * 8000.0f;

					SDK::Interfaces::g_pEngine->pEfxAPI->R_BeamPoints ( vEntityViewOrg, vEnd, BeamIndex, 0.001f, 0.9f, 0.0f,
						32.0f, 2.0f, 0, 0.0f, PlayerBarrelColor[0], PlayerBarrelColor[1], PlayerBarrelColor[2] );
				}
			}

			void ESP::HUD_Redraw ( )
			{
				SetFontColor ( );

				if ( g_Vars.ESP.WorldItems || g_Vars.ESP.WorldNades || g_Vars.ESP.WorldC4 )
				{
					DrawWorld ( );
				}

				if ( g_Vars.ESP.Player )
				{
					for ( int Index = 1; Index <= SDK::Interfaces::g_pEngine->GetMaxClients ( ); ++Index )
					{
						cl_entity_s* Entity = SDK::Interfaces::g_pEngine->GetEntityByIndex ( Index );

						if ( g_Info->GetValidationEntity ( Entity ) && Index != g_Info->GetLocalIndex ( ) )
						{
							DrawPlayer ( Entity );
						}
					}
				}

				if ( g_Vars.ESP.C4Timer )
				{
					g_Info->GetIsPlanted ( ) ? DrawC4Timer ( ) : GetC4TimerValue ( );
				}

				if ( g_Vars.ESP.Sound )
				{
					DrawSound ( );
				}
			}

			void ESP::CL_CreateMove ( const float &frametime )
			{
				if ( g_Vars.ESP.C4Timer == 1.0f )
				{
					g_Info->SetC4Timer ( g_Info->GetC4Timer ( ) + frametime );
				}
				else if ( g_Vars.ESP.C4Timer >= 2.0f )
				{
					g_Info->SetC4Timer ( g_Info->GetC4Timer ( ) - frametime );

					if ( g_Info->GetC4Timer ( ) < 0.0f )
						g_Info->SetC4Timer ( 0.0f );
				}
			}
		}
	}
}