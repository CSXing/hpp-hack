#include "Chams.h"

namespace Client
{
	namespace Functions
	{
		namespace Visuals
		{
			float Chams::PlayerR, Chams::PlayerG, Chams::PlayerB;
			float Chams::WeaponsR, Chams::WeaponsG, Chams::WeaponsB;

			void Chams::StudioRenderModel ( )
			{
				DWORD dwTemp = 0;

				_asm
				{
					mov dwTemp, ecx;
				}

				SDK::Interfaces::g_pStudio->SetForceFaceFlags ( 0 );

				cl_entity_s *Entity = SDK::Interfaces::g_pStudio->GetCurrentEntity ( );

				Entity->curstate.renderamt = 0;

				bool isPlayer = Entity && Entity->player && g_Info->GetValidationEntity ( Entity ) && Entity->index != g_Info->GetLocalIndex ( );
				bool isWeapons = Entity && Entity->model && strstr ( Entity->model->name, "w_" );
				bool isHands = Entity && Entity->model && Entity->model->name && strstr ( Entity->model->name, "v_" );

				if ( g_Vars.Chams.Enable )
				{
					if ( g_Vars.Chams.Hands && isHands )
					{
						if ( g_Vars.Chams.HandsRenderType == 2.0f || g_Vars.Chams.HandsRenderType == 3.0f )
						{
							glDisable ( GL_TEXTURE_2D );
						}
						else if ( g_Vars.Chams.HandsRenderType == 4.0f )
						{
							glDisable ( GL_TEXTURE_2D );
							glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
							glLineWidth ( 1.0f );
						}
						else if ( g_Vars.Chams.HandsRenderType == 5.0f )
						{
							glDisable ( GL_TEXTURE_2D );
							glPolygonMode ( GL_FRONT_AND_BACK, GL_POINT );
							glPointSize ( 1.0f );
						}

						glDepthFunc ( GL_LESS );

						OpenGL::Hands = true;

						StudioRenderFinal ( );

						OpenGL::Hands = false;

						glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
						glEnable ( GL_TEXTURE_2D );
					}

					if ( g_Vars.Chams.Weapon && isWeapons )
					{
						if ( g_Vars.Chams.WeaponRenderType == 2.0f || g_Vars.Chams.WeaponRenderType == 3.0f )
						{
							glDisable ( GL_TEXTURE_2D );
						}
						else if ( g_Vars.Chams.WeaponRenderType == 4.0f )
						{
							glDisable ( GL_TEXTURE_2D );
							glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
							glLineWidth ( 1.0f );
						}
						else if ( g_Vars.Chams.WeaponRenderType == 5.0f )
						{
							glDisable ( GL_TEXTURE_2D );
							glPolygonMode ( GL_FRONT_AND_BACK, GL_POINT );
							glPointSize ( 1.0f );
						}

						glBindTexture ( GL_TEXTURE_2D, 0 );

						if ( !g_Vars.Chams.WeaponVisibleOnly )
						{
							glDepthFunc ( GL_GREATER );
							glDisable ( GL_DEPTH_TEST );

							WeaponsR = g_Vars.Chams.WeaponColorHide[0] / 255.0f;
							WeaponsG = g_Vars.Chams.WeaponColorHide[1] / 255.0f;
							WeaponsB = g_Vars.Chams.WeaponColorHide[2] / 255.0f;

							StudioRenderFinal ( );
						}

						glEnable ( GL_DEPTH_TEST );
						glDepthFunc ( GL_LESS );

						WeaponsR = g_Vars.Chams.WeaponColorVis[0] / 255.0f;
						WeaponsG = g_Vars.Chams.WeaponColorVis[1] / 255.0f;
						WeaponsB = g_Vars.Chams.WeaponColorVis[2] / 255.0f;

						StudioRenderFinal ( );

						glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
						glEnable ( GL_TEXTURE_2D );
					}

					if ( g_Vars.Chams.Player && isPlayer )
					{
						if ( g_Info->GetAliveLocal ( ) )
						{
							if ( g_Vars.Chams.Player == 1.0f && g_Info->GetPlayerTeamByIndex ( Entity->index ) == g_Info->GetPlayerTeam ( ) )
							{
								StudioRenderFinal ( );

								return;
							}
						}

						if ( g_Vars.Chams.PlayerRenderType == 2.0f || g_Vars.Chams.PlayerRenderType == 3.0f )
						{
							glDisable ( GL_TEXTURE_2D );
						}
						else if ( g_Vars.Chams.PlayerRenderType == 4.0f )
						{
							glDisable ( GL_TEXTURE_2D );
							glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
							glLineWidth ( 1.0f );
						}
						else if ( g_Vars.Chams.PlayerRenderType == 5.0f )
						{
							glDisable ( GL_TEXTURE_2D );
							glPolygonMode ( GL_FRONT_AND_BACK, GL_POINT );
							glPointSize ( 1.0f );
						}

						glBindTexture ( GL_TEXTURE_2D, 0 );

						if ( !g_Info->GetAliveLocal ( ) || !g_Vars.Chams.PlayerVisibleOnly )
						{
							glDepthFunc ( GL_GREATER );
							glDisable ( GL_DEPTH_TEST );

							if ( g_Info->GetPlayerTeamByIndex ( Entity->index ) == TERRORIST )
							{
								PlayerR = g_Vars.Chams.ColorTHide[0] / 255.0f;
								PlayerG = g_Vars.Chams.ColorTHide[1] / 255.0f;
								PlayerB = g_Vars.Chams.ColorTHide[2] / 255.0f;
							}
							else if ( g_Info->GetPlayerTeamByIndex ( Entity->index ) == CT )
							{
								PlayerR = g_Vars.Chams.ColorCTHide[0] / 255.0f;
								PlayerG = g_Vars.Chams.ColorCTHide[1] / 255.0f;
								PlayerB = g_Vars.Chams.ColorCTHide[2] / 255.0f;
							}
							else if ( g_Info->GetPlayerTeamByIndex ( Entity->index ) == SPECTATOR )
							{
								PlayerR = 0.7f;
								PlayerG = 0.7f;
								PlayerB = 0.7f;
							}

							StudioRenderFinal ( );
						}

						glEnable ( GL_DEPTH_TEST );
						glDepthFunc ( GL_LESS );

						if ( g_Info->GetPlayerTeamByIndex ( Entity->index ) == TERRORIST )
						{
							PlayerR = g_Vars.Chams.ColorTVis[0] / 255.0f;
							PlayerG = g_Vars.Chams.ColorTVis[1] / 255.0f;
							PlayerB = g_Vars.Chams.ColorTVis[2] / 255.0f;
						}
						else if ( g_Info->GetPlayerTeamByIndex ( Entity->index ) == CT )
						{
							PlayerR = g_Vars.Chams.ColorCTVis[0] / 255.0f;
							PlayerG = g_Vars.Chams.ColorCTVis[1] / 255.0f;
							PlayerB = g_Vars.Chams.ColorCTVis[2] / 255.0f;
						}
						else if ( g_Info->GetPlayerTeamByIndex ( Entity->index ) == SPECTATOR )
						{
							PlayerR = 1.0f;
							PlayerG = 1.0f;
							PlayerB = 1.0f;
						}

						StudioRenderFinal ( );

						glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
						glEnable ( GL_TEXTURE_2D );
					}

					if ( ( !g_Vars.Chams.Player || ( g_Vars.Chams.Player && !isPlayer ) ) &&
						( !g_Vars.Chams.Weapon || ( g_Vars.Chams.Weapon && !isWeapons ) ) &&
						( !g_Vars.Chams.Hands || ( g_Vars.Chams.Hands && !isHands ) ) )
					{
						StudioRenderFinal ( );
					}
				}
				else
				{
					StudioRenderFinal ( );
				}
			}
		}
	}
}