#pragma once

#include "Main.h"

namespace Client
{
	extern DWORD dwStudioModelRenderer;
	extern DWORD dwStudioRenderFinal;

	extern bool FirstFrame;

	extern bool SnapShot;
	extern bool ScreenShot;
	extern bool SteamScreenShot;

	void HUD_Frame ( double time );
	void HUD_Redraw ( float time, int intermission );
	void HUD_PostRunCmd ( local_state_s *from, local_state_s *to, usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed );

	int HUD_AddEntity ( int type, cl_entity_s *ent, const char *modelname );
	int HUD_Key_Event ( int down, int keynum, const char *pszCurrentBinding );

	void CL_CreateMove ( float frametime, usercmd_s *cmd, int active );

	void V_CalcRefdef ( ref_params_s *pparams );

	void StudioEntityLight ( alight_s *plight );
	void StudioRenderModel ( );
	void SetChromeOrigin ( );

	void ConsolePrintColor ( BYTE R, BYTE G, BYTE B, char *String );
	void ConsolePrintColor ( BYTE R, BYTE G, BYTE B, DWORD String );
	void ConsolePrintColor ( BYTE R, BYTE G, BYTE B, int String );
	void ConsolePrintColor ( BYTE R, BYTE G, BYTE B, float String );

	extern GameInfo_t BuildInfo;
}