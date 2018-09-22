#include "NoFlash.h"

namespace Client
{
	namespace Functions
	{
		namespace Visuals
		{
			enum FADE_COLOR
			{
				RED, LIGHT_RED, GREEN, LIGHT_GREEN, BLUE, LIGHT_BLUE, AQUAMARINE, HELIOTROPE,
				DARKPURPLEVOILET, LASERLEMON, BRIGHTGREEN, GREENLAWN, GREENYELLOWKRAYOLA, YELLOW
			};

			float NoFlash::flCurstateFlashed;
			float NoFlash::flPrevstateFlashed;

			BYTE NoFlash::FadeColor[3];
			BYTE NoFlash::ShowPecentColor[3];

			bool NoFlash::SetColor;

			void NoFlash::SetFadeColorRandom ( )
			{
				if ( flCurstateFlashed && SetColor )
				{
					int Color = SDK::Interfaces::g_pEngine->pfnRandomLong ( 0, 13 );

					switch ( Color )
					{
					case RED:
						FadeColor[0] = 255;
						FadeColor[1] = 0;
						FadeColor[2] = 0;

						break;

					case LIGHT_RED:
						FadeColor[0] = 255;
						FadeColor[1] = 100;
						FadeColor[2] = 100;

						break;

					case GREEN:
						FadeColor[0] = 0;
						FadeColor[1] = 255;
						FadeColor[2] = 0;

						break;

					case LIGHT_GREEN:
						FadeColor[0] = 100;
						FadeColor[1] = 255;
						FadeColor[2] = 100;

						break;

					case BLUE:
						FadeColor[0] = 0;
						FadeColor[1] = 0;
						FadeColor[2] = 255;

						break;

					case LIGHT_BLUE:
						FadeColor[0] = 100;
						FadeColor[1] = 100;
						FadeColor[2] = 255;

						break;

					case AQUAMARINE:
						FadeColor[0] = 127;
						FadeColor[1] = 255;
						FadeColor[2] = 212;

						break;

					case HELIOTROPE:
						FadeColor[0] = 200;
						FadeColor[1] = 90;
						FadeColor[2] = 255;

						break;

					case DARKPURPLEVOILET:
						FadeColor[0] = 102;
						FadeColor[1] = 0;
						FadeColor[2] = 153;

						break;

					case LASERLEMON:
						FadeColor[0] = 254;
						FadeColor[1] = 254;
						FadeColor[2] = 34;

						break;

					case BRIGHTGREEN:
						FadeColor[0] = 0;
						FadeColor[1] = 125;
						FadeColor[2] = 52;

						break;

					case GREENLAWN:
						FadeColor[0] = 124;
						FadeColor[1] = 252;
						FadeColor[2] = 0;

						break;

					case GREENYELLOWKRAYOLA:
						FadeColor[0] = 240;
						FadeColor[1] = 232;
						FadeColor[2] = 145;

						break;

					case YELLOW:
						FadeColor[0] = 255;
						FadeColor[1] = 255;
						FadeColor[2] = 0;

						break;
					}

					SDK::Interfaces::g_pScreenFade->fader = FadeColor[0];
					SDK::Interfaces::g_pScreenFade->fadeg = FadeColor[1];
					SDK::Interfaces::g_pScreenFade->fadeb = FadeColor[2];

					SetColor = false;
				}

				if ( flCurstateFlashed == 255.0f && flPrevstateFlashed == 255.0f )
				{
					SDK::Interfaces::g_pScreenFade->fader = FadeColor[0];
					SDK::Interfaces::g_pScreenFade->fadeg = FadeColor[1];
					SDK::Interfaces::g_pScreenFade->fadeb = FadeColor[2];
				}

				if ( !flCurstateFlashed || flPrevstateFlashed < flCurstateFlashed )
				{
					SetColor = true;
				}
			}

			void NoFlash::SetFadeColor ( )
			{
				SDK::Interfaces::g_pScreenFade->fader = g_Vars.NoFlash.FadeColor[0];
				SDK::Interfaces::g_pScreenFade->fadeg = g_Vars.NoFlash.FadeColor[1];
				SDK::Interfaces::g_pScreenFade->fadeb = g_Vars.NoFlash.FadeColor[2];
			}

			void NoFlash::DrawFlashed ( const int& Percentage )
			{
				int x = SDK::Interfaces::g_Screen.iWidth / 2;
				int y = SDK::Interfaces::g_Screen.iHeight / 6;

				Renderer::g_Fonts->Print ( x, y, ShowPecentColor[0], ShowPecentColor[1], 0, 255, 
					g_Vars.NoFlash.FontOutline ? FL_CENTER | FL_OUTLINE : FL_CENTER, "Flashed: %d", Percentage );

				if ( Percentage > DONT_SEE_FLASH_PERCENT )
				{
					Renderer::g_Fonts->Print ( x, y + 13, 255, 80, 80, 255, g_Vars.NoFlash.FontOutline ? 
						FL_CENTER | FL_OUTLINE : FL_CENTER, "You are don't see." );
				}
			}

			void NoFlash::DrawFlashedBox ( const int& Percentage )
			{
				int x = SDK::Interfaces::g_Screen.iWidth / 2;
				int y = int ( SDK::Interfaces::g_Screen.iHeight / 6.2f );

				Renderer::g_Drawing->Box ( x - 101, y - 9, 202, 18, 1, 20, 20, 20, 225 );
				Renderer::g_Drawing->FillArea ( x - 100, y - 8, 200, 16, ShowPecentColor[0], ShowPecentColor[1], 0, 150 );

				Renderer::g_Fonts->Print ( x, y + 4, 255, 255, 255, 255, g_Vars.NoFlash.FontOutline ? 
					FL_CENTER | FL_OUTLINE : FL_CENTER, "Flashed: %d", Percentage );

				if ( Percentage > DONT_SEE_FLASH_PERCENT )
				{
					Renderer::g_Fonts->Print ( x, y + 23, 255, 0, 0, 255, g_Vars.NoFlash.FontOutline ? 
						FL_CENTER | FL_OUTLINE : FL_CENTER, "You are don't see." );
				}
			}

			float NoFlash::GetFlashedPercentage ( )
			{
				UpdateFlashedData ( );

				return flCurstateFlashed / 255.0f * 100.0f;
			}

			void NoFlash::UpdateFlashedData ( )
			{
				float flFadeEnd = 0.0f;

				flPrevstateFlashed = flCurstateFlashed;

				if ( SDK::Interfaces::g_pScreenFade->fadeEnd > SDK::Interfaces::g_pEngine->GetClientTime ( ) )
				{
					flFadeEnd = SDK::Interfaces::g_pScreenFade->fadeEnd;

					if ( g_Vars.Functions.NoFlash && g_Vars.NoFlash.Enable )
					{
						if ( g_Vars.NoFlash.FadeLimit > 255.0f )
						{
							SDK::Interfaces::g_pScreenFade->fadeEnd = 255.0f;
						}
						else if ( SDK::Interfaces::g_pScreenFade->fadealpha > g_Vars.NoFlash.FadeLimit )
						{
							SDK::Interfaces::g_pScreenFade->fadealpha = g_Vars.NoFlash.FadeLimit;
						}
					}
				}

				flCurstateFlashed = flFadeEnd > SDK::Interfaces::g_pEngine->GetClientTime ( ) ?
					( flFadeEnd - SDK::Interfaces::g_pEngine->GetClientTime ( ) ) * SDK::Interfaces::g_pScreenFade->fadeSpeed : 0.0f;

				if ( flCurstateFlashed > 255.0f )
					flCurstateFlashed = 255.0f;

				if ( flCurstateFlashed < 0.0f )
					flCurstateFlashed = 0.0f;
			}

			void NoFlash::InterpolatedShowPercentColor ( const int& Percentage )
			{
				ShowPecentColor[0] = Percentage >= 50 ? 255 : ( BYTE )Utils::Interp ( 0.0f, ( float )Percentage, 50.0f, 0.0f, 255.0f );
				ShowPecentColor[1] = Percentage <= 50 ? 255 : ( BYTE )Utils::Interp ( 50.0f, ( float )Percentage, 100.0f, 255.0f, 0.0f );
			}

			void NoFlash::HUD_Redraw ( )
			{
				if ( g_Vars.NoFlash.FadeColorEnable )
				{
					g_Vars.NoFlash.FadeColorRandom ? SetFadeColorRandom ( ) : SetFadeColor ( );
				}

				int Percentage = ( int )GetFlashedPercentage ( );

				if ( g_Vars.NoFlash.DrawFlashed && Percentage >= 1 )
				{
					InterpolatedShowPercentColor ( Percentage );

					g_Vars.NoFlash.DrawFlashed <= 1.0f ? DrawFlashed ( Percentage ) : DrawFlashedBox ( Percentage );
				}
			}
		}
	}
}