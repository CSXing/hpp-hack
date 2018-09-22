#pragma once

#include "Main.h"

namespace Client
{
	namespace Functions
	{
		namespace Visuals
		{
			struct M_Entry
			{
				char Name[MAX_NAME_CHAR];
				bool Space, Function;
			};

			struct S_Entry
			{
				char Name[MAX_NAME_CHAR];

				float *flValue, flStep, flMin, flMax;
				int *iValue, iStep, iMin, iMax;
				bool *bValue;

				BYTE Color[3];

				bool Float, Space, Switch;
				bool Active, Sub, Auto;
			};

			struct SS_Entry
			{
				char Name[MAX_NAME_CHAR];

				float *flValue, flStep, flMin, flMax;
				int *iValue, iStep, iMin, iMax;
				BYTE *kValue;
				bool *bValue;

				bool Float, Space;
				bool Switch, Auto, String;
			};

			class Menu
			{
			public:
				static void HUD_Redraw ( );
				static void HUD_Key_Event ( bool& RetFlag, int& keynum );

			private:
				static int BoxWidth, BoxHeight;
				static BYTE BoxOutlineColor[4], BoxColor[4];
				static BYTE BoxSelectColor[4], TextColor[3];

				static void SetSettings ( );

				static void Initialize ( );	
				static void DrawFadeAnimation ( );
				static void DrawMenu ( int x, int y );

				static char String[20];

				static bool SubMenu, SubSubMenu;
				static bool Visible, InputString;
				static bool VisibleAnimation;

				static float flVisibleAnimationTimer;

				static M_Entry MenuEntry[MAX_SUBS_MENU];
				static S_Entry SubmEntry[MAX_SUBS_MENU];
				static SS_Entry SubSubmEntry[MAX_SUBS_MENU];

				static int M_EntryPos, M_EntrySize;
				static int S_EntryPos, S_EntrySize;
				static int SS_EntryPos, SS_EntrySize;

				static void SetAimBotPistolsSettings ( );
				static void SetAimBotRiflesSettings ( );
				static void SetAimBotSnipersSettings ( );

				static void SetTriggerBotPistolsSettings ( );
				static void SetTriggerBotRiflesSettings ( );
				static void SetTriggerBotSnipersSettings ( );

				static void Add ( const char* Name, bool Space, bool Function );

				static void AddSubFloat ( const char* Name, float* Value, float Min, float Max, float Step, 
					bool Float, bool Space, bool Switch, bool Active, bool Sub, bool Auto, BYTE R, BYTE G, BYTE B );

				static void AddSubInt ( const char* Name, int* Value, int Min, int Max, int Step,
					bool Float, bool Space, bool Switch, bool Active, bool Sub, bool Auto, BYTE R, BYTE G, BYTE B );

				static void AddSubBool ( const char* Name, bool* Value, bool Float, bool Space,
					bool Switch, bool Active, bool Sub, bool Auto, BYTE R, BYTE G, BYTE B );

				static void AddSubSubFloat ( const char* Name, float* Value, float Min, float Max, 
					float Step, bool Float, bool Space, bool Switch, bool Auto, bool String );

				static void AddSubSubInt ( const char* Name, int* Value, int Min, int Max, 
					int Step, bool Float, bool Space, bool Switch, bool Auto, bool String );

				static void AddSubSubKey ( const char* Name, BYTE* Value, 
					bool Float, bool Space, bool Switch, bool Auto, bool String );

				static void AddSubSubBool ( const char* Name, bool* Value, 
					bool Float, bool Space, bool Switch, bool Auto, bool String );

				static void Clear ( );
			};
		}
	}
}