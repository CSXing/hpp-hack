#include "OpenGL.h"

namespace OpenGL
{
	using namespace Client::Functions;

	glBegin_t pglBegin = 0;
	glVertex3fv_t pglVertex3fv = 0;
	glColor4f_t pglColor4f = 0;

	bool Smoke = false;
	bool Hands = false;

	void APIENTRY Hooked_glBegin ( GLenum mode )
	{
		if ( !Client::FirstFrame )
			return;

		if ( Client::SnapShot || Client::ScreenShot || Client::SteamScreenShot )
			goto go;

		cl_entity_s *Entity = SDK::Interfaces::g_pStudio->GetCurrentEntity ( );

		if ( g_Vars.Other.RemoveSmoke && mode == GL_QUADS )
		{
			if ( Entity && Entity->model && strstr ( Entity->model->name, "black_smoke" ) )
			{
				GLfloat SmokeCol[4];

				glGetFloatv ( GL_CURRENT_COLOR, SmokeCol );

				if ( ( SmokeCol[0] == SmokeCol[1] ) && ( SmokeCol[0] == SmokeCol[2] ) &&
					( SmokeCol[0] != 0.0f ) && ( SmokeCol[0] != 1.0f ) )
				{
					Smoke = true;
				}
			}
		}
		else
			Smoke = false;

	go:
		pglBegin ( mode );
	}

	void APIENTRY Hooked_glVertex3fv ( GLfloat *v )
	{
		if ( !Client::FirstFrame )
			return;

		if ( Smoke )
			return;

		pglVertex3fv ( v );
	}

	void APIENTRY Hooked_glColor4f ( float r, float g, float b, float a )
	{
		if ( !Client::FirstFrame )
			return;

		if ( Client::SnapShot || Client::ScreenShot || Client::SteamScreenShot )
			goto go;

		cl_entity_s *Entity = SDK::Interfaces::g_pStudio->GetCurrentEntity ( );

		bool isPlayer = Entity && Entity->player && Client::g_Info->GetValidationEntity ( Entity ) && Entity->index != Client::g_Info->GetLocalIndex ( );
		bool isWeapons = Entity && Entity->model && strstr ( Entity->model->name, "w_" );
		bool isHands = Entity && Entity->model && Entity->model->name && strstr ( Entity->model->name, "v_" );

		if ( g_Vars.Chams.Enable )
		{
			if ( g_Vars.Chams.Weapon && isWeapons )
			{
				if ( g_Vars.Chams.WeaponRenderType == 3 )
				{
					r = Visuals::Chams::GetWeaponsColorR ( ) * r;
					g = Visuals::Chams::GetWeaponsColorG ( ) * g;
					b = Visuals::Chams::GetWeaponsColorB ( ) * b;
				}
				else
				{
					r = Visuals::Chams::GetWeaponsColorR ( );
					g = Visuals::Chams::GetWeaponsColorG ( );
					b = Visuals::Chams::GetWeaponsColorB ( );
				}
			}

			if ( g_Vars.Chams.Player && isPlayer )
			{
				if ( Client::g_Info->GetAliveLocal ( ) )
				{
					if ( g_Vars.Chams.Player == 1.0f && Client::g_Info->GetPlayerTeamByIndex ( Entity->index ) == Client::g_Info->GetPlayerTeam ( ) )
					{
						goto go;
					}
				}

				if ( g_Vars.Chams.PlayerRenderType == 3 )
				{
					r = Visuals::Chams::GetPlayerColorR ( ) * r;
					g = Visuals::Chams::GetPlayerColorG ( ) * g;
					b = Visuals::Chams::GetPlayerColorB ( ) * b;
				}
				else
				{
					r = Visuals::Chams::GetPlayerColorR ( );
					g = Visuals::Chams::GetPlayerColorG ( );
					b = Visuals::Chams::GetPlayerColorB ( );
				}
			}
		}

		if ( g_Vars.Chams.Hands && isHands && Hands )
		{
			if ( g_Vars.Chams.HandsRenderType == 3 )
			{
				r = g_Vars.Chams.HandsColor[0] / 255.0f * r;
				g = g_Vars.Chams.HandsColor[1] / 255.0f * g;
				b = g_Vars.Chams.HandsColor[2] / 255.0f * b;
			}
			else
			{
				r = g_Vars.Chams.HandsColor[0] / 255.0f;
				g = g_Vars.Chams.HandsColor[1] / 255.0f;
				b = g_Vars.Chams.HandsColor[2] / 255.0f;
			}
		}

	go:
		pglColor4f ( r, g, b, a );
	}

	void* DetourFunc ( BYTE *src, const BYTE *dst, const int len )
	{
		BYTE *jmp = ( BYTE* )HeapAlloc ( GetProcessHeap ( ), HEAP_ZERO_MEMORY, len + 5 );

		if ( src[0] != 0xE9 )
		{
			DWORD dwBack;

			VirtualProtect ( src, len, PAGE_READWRITE, &dwBack );

			memcpy ( jmp, src, len );

			jmp += len;
			jmp[0] = 0xE9;
			*( DWORD* )( jmp + 1 ) = ( DWORD )( src + len - jmp ) - 5;
			src[0] = 0xE9;
			*( DWORD* )( src + 1 ) = ( DWORD )( dst - src ) - 5;

			VirtualProtect ( src, len, dwBack, &dwBack );

			return ( jmp - len );
		}

		return 0;
	}
}