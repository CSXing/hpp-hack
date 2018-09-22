#include "Crosshair.h"

namespace Client
{
	namespace Functions
	{
		namespace Visuals
		{
			int Crosshair::Size;
			int Crosshair::Gap;
			int Crosshair::Thickness;
			BYTE Crosshair::Color[4];

			void Crosshair::SetSettings ( )
			{
				Size = ( int )g_Vars.Crosshair.Size;
				Gap = ( int )g_Vars.Crosshair.Gap;
				Thickness = ( int )g_Vars.Crosshair.Thickness;

				Color[0] = BYTE ( g_Vars.Crosshair.Color[0] );
				Color[1] = BYTE ( g_Vars.Crosshair.Color[1] );
				Color[2] = BYTE ( g_Vars.Crosshair.Color[2] );
				Color[3] = BYTE ( g_Vars.Crosshair.Color[3] );
			}

			void Crosshair::DrawCrosshair ( const int &x, const int &y, BYTE R, BYTE G, BYTE B, BYTE A )
			{
				int thickness = Thickness - 1;

				if ( g_Vars.Crosshair.Dynamic )
				{
					int Recoil = int ( g_Info->GetVectorPunchAngles ( )[0] * g_Vars.Crosshair.DynamicScale );

					Renderer::g_Drawing->FillArea ( x + Recoil - Gap - Size + 1 - thickness, y - thickness, Size, Thickness, R, G, B, A );
					Renderer::g_Drawing->FillArea ( x - Recoil + Gap, y - thickness, Size, Thickness, R, G, B, A );
					Renderer::g_Drawing->FillArea ( x - thickness, y + Recoil - Gap - Size + 1 - thickness, Thickness, Size, R, G, B, A );
					Renderer::g_Drawing->FillArea ( x - thickness, y - Recoil + Gap, Thickness, Size, R, G, B, A );
				}
				else
				{
					Renderer::g_Drawing->FillArea ( x - Gap - Size + 1 - thickness, y - thickness, Size, Thickness, R, G, B, A );
					Renderer::g_Drawing->FillArea ( x + Gap, y - thickness, Size, Thickness, R, G, B, A );
					Renderer::g_Drawing->FillArea ( x - thickness, y - Gap - Size + 1 - thickness, Thickness, Size, R, G, B, A );
					Renderer::g_Drawing->FillArea ( x - thickness, y + Gap, Thickness, Size, R, G, B, A );
				}
			}

			void Crosshair::DrawDot ( const int &x, const int &y, BYTE R, BYTE G, BYTE B, BYTE A )
			{
				int thickness = Thickness - 1;

				Renderer::g_Drawing->FillArea ( x - thickness, y - thickness, Thickness, Thickness, R, G, B, A );
			}

			void Crosshair::HUD_Redraw ( )
			{
				if ( !g_Vars.Crosshair.Snipers && g_Info->GetWeaponListSnipers ( ) ) return;
				if ( g_Info->GetFOV ( ) == 40 || g_Info->GetFOV ( ) == 10 || g_Info->GetFOV ( ) == 15 ) return;

				SetSettings ( );

				int x = SDK::Interfaces::g_Screen.iWidth / 2;
				int y = SDK::Interfaces::g_Screen.iHeight / 2;

				if ( g_Vars.Crosshair.Outline )
				{
					DrawCrosshair ( x - 1, y, 0, 0, 0, Color[3] );
					DrawCrosshair ( x, y - 1, 0, 0, 0, Color[3] );
					DrawCrosshair ( x + 1, y, 0, 0, 0, Color[3] );
					DrawCrosshair ( x, y + 1, 0, 0, 0, Color[3] );

					DrawCrosshair ( x - 1, y - 1, 0, 0, 0, Color[3] );
					DrawCrosshair ( x - 1, y + 1, 0, 0, 0, Color[3] );
					DrawCrosshair ( x + 1, y - 1, 0, 0, 0, Color[3] );
					DrawCrosshair ( x + 1, y + 1, 0, 0, 0, Color[3] );
				}

				DrawCrosshair ( x, y, Color[0], Color[1], Color[2], Color[3] );

				if ( g_Vars.Crosshair.Dot )
				{
					if ( g_Vars.Crosshair.Outline )
					{
						DrawDot ( x - 1, y, 0, 0, 0, Color[3] );
						DrawDot ( x, y - 1, 0, 0, 0, Color[3] );
						DrawDot ( x + 1, y, 0, 0, 0, Color[3] );
						DrawDot ( x, y + 1, 0, 0, 0, Color[3] );

						DrawDot ( x - 1, y - 1, 0, 0, 0, Color[3] );
						DrawDot ( x + 1, y - 1, 0, 0, 0, Color[3] );
						DrawDot ( x - 1, y + 1, 0, 0, 0, Color[3] );
						DrawDot ( x + 1, y + 1, 0, 0, 0, Color[3] );
					}

					DrawDot ( x, y, Color[0], Color[1], Color[2], Color[3] );
				}
			}
		}
	}
}