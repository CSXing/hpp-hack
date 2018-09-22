#pragma once
#pragma warning (disable: 4996)

#include "Main.h"

#define FILE_READ_INT( Variable, Section, Key ) Variable = ReadInt ( ( char* )Path.c_str ( ), Section, Key, "0" )
#define FILE_READ_FLOAT( Variable, Section, Key ) Variable = ReadFloat ( ( char* )Path.c_str ( ), Section, Key, "0" )
#define FILE_READ_STRING( Variable, Section, Key) Variable = ReadString ( ( char* )Path.c_str ( ), Section, Key, "0" )
#define FILE_READ_KEY( Variable, Section, Key ) Variable = ReadStringConvert ( ( char* )Path.c_str ( ), Section, Key, "0" )
#define FILE_READ_CONVERT( Variable, Section, Key ) Variable = ReadStringConvert ( ( char* )Path.c_str ( ), Section, Key, "0" )

#define FILE_WRITE_INT( Variable, Section, Key ) { char String[MAX_FILE_WRITE_LENGHT]; sprintf_s ( String, " %d", ( int )Variable );\
	WriteString ( ( char* )Path.c_str ( ), Section, Key, String ); }

#define FILE_WRITE_INT_2( Variable1, Variable2, Section, Key ) { char String[MAX_FILE_WRITE_LENGHT];\
	sprintf_s ( String, " %d, %d", ( int )Variable1, ( int )Variable2 );\
	WriteString ( ( char* )Path.c_str ( ), Section, Key, String ); }

#define FILE_WRITE_FLOAT( Variable, Section, Key ) { char String[MAX_FILE_WRITE_LENGHT]; sprintf_s ( String, " %g", Variable );\
	WriteString ( ( char* )Path.c_str ( ), Section, Key, String ); }

#define FILE_WRITE_FLOAT_2( Variable1, Variable2, Section, Key ) { char String[MAX_FILE_WRITE_LENGHT]; sprintf_s ( String, " %g, %g", Variable1, Variable2 );\
	WriteString ( ( char* )Path.c_str ( ), Section, Key, String ); }

#define FILE_WRITE_RGB( R, G, B, Section, Key ) { char String[MAX_FILE_WRITE_LENGHT]; sprintf_s ( String, " %d, %d, %d", ( int )R,  ( int )G, ( int )B );\
	WriteString ( ( char* )Path.c_str ( ), Section, Key, String ); }

#define FILE_WRITE_RGBA( R, G, B, A, Section, Key ) { char String[MAX_FILE_WRITE_LENGHT];\
	sprintf_s ( String, " %d, %d, %d, %d", ( int )R,  ( int )G, ( int )B, ( int )A );\
	WriteString ( ( char* )Path.c_str ( ), Section, Key, String ); }

#define FILE_WRITE_DIR( Variable, Section, Key ) { if ( Variable == 1001 ) WriteString ( ( char* )Path.c_str ( ), Section, Key, " up" );\
	else if ( Variable == 1000 ) WriteString ( ( char* )Path.c_str ( ), Section, Key, " down" ); }

#define FILE_WRITE_LANG( Variable, Section, Key ) { if ( Variable == 2001 ) WriteString ( ( char* )Path.c_str ( ), Section, Key, " russian" );\
	else if ( Variable == 2000 ) WriteString ( ( char* )Path.c_str ( ), Section, Key, " english" ); }

#define FILE_WRITE_KEY( Variable, Section, Key ) { char String[MAX_FILE_WRITE_LENGHT]; sprintf_s ( String, " %s", KeyToString ( Variable ) );\
	WriteString ( ( char* )Path.c_str ( ), Section, Key, String ); }

#define PARS_STRING( KeyToConvert, Convert ) { if ( !lstrcmpi ( Key, KeyToConvert ) ) return Convert; }

namespace Files
{
	extern char* BaseDir;

	std::string szDirFile ( const char* FileName );

	extern std::ofstream Inject, Info;

	inline void InjectLog ( const char* fmt, ... )
	{
		char DateString[9], TimeStr[9];

		_strtime_s ( TimeStr );
		_strdate_s ( DateString );

		if ( !fmt )
		{
			Inject << std::endl;

			return;
		}

		char LogBuf[256] = { 0 };

		va_list va_alist;
		va_start ( va_alist, fmt );
		_vsnprintf ( LogBuf + strlen ( LogBuf ), sizeof ( LogBuf ) - strlen ( LogBuf ), fmt, va_alist );
		va_end ( va_alist );

		Inject << "[" << DateString << " - " << TimeStr << "] " << LogBuf << std::endl;
	}

	inline void InfoLog ( const char* fmt, ... )
	{
		char DateString[9], TimeStr[9];

		_strtime_s ( TimeStr );
		_strdate_s ( DateString );

		if ( !fmt )
		{
			Info << std::endl;

			return;
		}

		char LogBuf[256] = { 0 };

		va_list va_alist;
		va_start ( va_alist, fmt );
		_vsnprintf ( LogBuf + strlen ( LogBuf ), sizeof ( LogBuf ) - strlen ( LogBuf ), fmt, va_alist );
		va_end ( va_alist );

		Info << "[" << DateString << " - " << TimeStr << "] " << LogBuf << std::endl;
	}

	namespace Read
	{
		void Functions ( );
		void Main ( );
		void Menu ( );
		void ScreenInfo ( );
		void ESP ( );
		void NoFlash ( );
		void Speed ( );
		void BunnyHop ( );
		void Crosshair ( );
		void AimWeapons ( );
		void Other ( );
		void Recoil ( );
		void AutoPistol ( );
		void FastZoom ( );
		void Chams ( );
		void GroundStrafe ( );
		void TriggerWeapons ( );
	}

	namespace Write
	{
		void Main ( );
		void Menu ( );
		void ScreenInfo ( );
		void ESP ( );
		void NoFlash ( );
		void Speed ( );
		void BunnyHop ( );
		void Crosshair ( );
		void AimWeapons ( );
		void Other ( );
		void Recoil ( );
		void AutoPistol ( );
		void FastZoom ( );
		void Chams ( );
		void GroundStrafe ( );
		void TriggerWeapons ( );
	}

	void GetBaseDir ( const HINSTANCE& hInstance );

	void LoadSettings ( );
	void ReloadSettings ( );
	void SaveSettings ( );

	void FilesCheck ( );

	void CreateLogDirectory ( );
	void CreateInjectLogFile ( );
	void CreateInfoLogFile ( );
	void CreateSettingsDirectory ( );
	void CreateFileMain ( );
	void CreateFileFunctions ( );
	void CreateFileVisuals ( );
	void CreateFileMisc ( );
	void CreateFileAimBot ( );
	void CreateFileTriggerBot ( );

	void LoadFileMain ( );
	void LoadFileFunctions ( );
	void LoadFileVisuals ( );
	void LoadFileMisc ( );
	void LoadFileAimBot ( );
	void LoadFileTriggerBot ( );

	void SaveFileMain ( );
	void SaveFileVisuals ( );
	void SaveFileMisc ( );
	void SaveFileAimBot ( );
	void SaveFileTriggerBot ( );

	inline bool FileExists ( const char* FileName )
	{
		return _access ( FileName, 0 ) != -1;
	}

	inline char* ReadString ( const char* Path, const char* Section, const char* Key, const char* DefString )
	{
		char* String = new char[512];

		GetPrivateProfileString ( Section, Key, DefString, String, 200, Path );

		return String;
	}

	inline float ReadFloat ( const char* Path, const char* Section, const char* Key, const char* DefValue )
	{
		return ( float )atof ( ReadString ( Path, Section, Key, DefValue ) );
	}

	inline int ReadInt ( const char* Path, const char* Section, const char* Key, const char* DefValue )
	{
		return atoi ( ReadString ( Path, Section, Key, DefValue ) );
	}

	inline void WriteString ( const char* Path, const char* Section, const char* Key, const char* String )
	{
		WritePrivateProfileString ( Section, Key, String, Path );
	}

	inline int StringToKey ( const char* Key )
	{
		PARS_STRING ( "ru", RUSSIAN );
		PARS_STRING ( "en", RUSSIAN );
		PARS_STRING ( "rus", RUSSIAN );
		PARS_STRING ( "eng", ENGLISH );
		PARS_STRING ( "russian", RUSSIAN );
		PARS_STRING ( "english", ENGLISH );

		PARS_STRING ( "up", UP );
		PARS_STRING ( "down", DOWN );

		PARS_STRING ( "tab", K_TAB );
		PARS_STRING ( "enter", K_ENTER );
		PARS_STRING ( "escape", K_ESCAPE );
		PARS_STRING ( "backspace", K_BACKSPACE );
		PARS_STRING ( "uparrow", K_UPARROW );
		PARS_STRING ( "downarrow", K_DOWNARROW );
		PARS_STRING ( "leftarrow", K_LEFTARROW );
		PARS_STRING ( "rightarrow", K_RIGHTARROW );

		PARS_STRING ( "[", K_BRACKET_LEFT );
		PARS_STRING ( "]", K_BRACKET_RIGHT );
		PARS_STRING ( "0", K_0 );
		PARS_STRING ( "1", K_1 );
		PARS_STRING ( "2", K_2 );
		PARS_STRING ( "3", K_3 );
		PARS_STRING ( "4", K_4 );
		PARS_STRING ( "5", K_5 );
		PARS_STRING ( "6", K_6 );
		PARS_STRING ( "7", K_7 );
		PARS_STRING ( "8", K_8 );
		PARS_STRING ( "9", K_9 );
		PARS_STRING ( ".", K_POINT );
		PARS_STRING ( ",", K_COMMA );

		PARS_STRING ( "a", K_A );
		PARS_STRING ( "b", K_B );
		PARS_STRING ( "c", K_C );
		PARS_STRING ( "d", K_D );
		PARS_STRING ( "e", K_E );
		PARS_STRING ( "f", K_F );
		PARS_STRING ( "g", K_G );
		PARS_STRING ( "h", K_H );
		PARS_STRING ( "i", K_I );
		PARS_STRING ( "j", K_J );
		PARS_STRING ( "k", K_K );
		PARS_STRING ( "l", K_L );
		PARS_STRING ( "m", K_M );
		PARS_STRING ( "n", K_N );
		PARS_STRING ( "o", K_O );
		PARS_STRING ( "p", K_P );
		PARS_STRING ( "q", K_Q );
		PARS_STRING ( "r", K_R );
		PARS_STRING ( "s", K_S );
		PARS_STRING ( "t", K_T );
		PARS_STRING ( "u", K_U );
		PARS_STRING ( "v", K_V );
		PARS_STRING ( "w", K_W );
		PARS_STRING ( "x", K_X );
		PARS_STRING ( "z", K_Z );

		PARS_STRING ( "f1", K_F1 );
		PARS_STRING ( "f2", K_F2 );
		PARS_STRING ( "f3", K_F3 );
		PARS_STRING ( "f4", K_F4 );
		PARS_STRING ( "f5", K_F5 );
		PARS_STRING ( "f6", K_F6 );
		PARS_STRING ( "f7", K_F7 );
		PARS_STRING ( "f8", K_F8 );
		PARS_STRING ( "f9", K_F9 );
		PARS_STRING ( "f10", K_F10 );
		PARS_STRING ( "f11", K_F11 );
		PARS_STRING ( "f12", K_F12 );

		PARS_STRING ( "insert", K_INS );
		PARS_STRING ( "ins", K_INS );
		PARS_STRING ( "delete", K_DEL );
		PARS_STRING ( "del", K_DEL );
		PARS_STRING ( "pgdn", K_PGDN );
		PARS_STRING ( "pgup", K_PGUP );
		PARS_STRING ( "home", K_HOME );
		PARS_STRING ( "end", K_END );
		PARS_STRING ( "space", K_SPACE );
		PARS_STRING ( "alt", K_ALT );
		PARS_STRING ( "shift", K_SHIFT );
		PARS_STRING ( "ctrl", K_CTRL );
		PARS_STRING ( "mwheeldown", K_MWHEELDOWN );
		PARS_STRING ( "mwheelup", K_MWHEELUP );
		PARS_STRING ( "mwdown", K_MWHEELDOWN );
		PARS_STRING ( "mwup", K_MWHEELUP );
		PARS_STRING ( "mouse1", K_MOUSE1 );
		PARS_STRING ( "mouse2", K_MOUSE2 );
		PARS_STRING ( "mouse3", K_MOUSE3 );
		PARS_STRING ( "mouse4", K_MOUSE4 );
		PARS_STRING ( "mouse5", K_MOUSE5 );

		PARS_STRING ( "true", TRUE );
		PARS_STRING ( "false", FALSE );
		PARS_STRING ( "on", TRUE );
		PARS_STRING ( "off", FALSE );
		PARS_STRING ( "none", NULL );

		return 0;
	}

	inline char* KeyToString ( BYTE Key )
	{
		switch ( Key )
		{
		case K_TAB:				return "TAB";
		case K_ENTER:			return "ENTER";
		case K_ESCAPE:			return "ESCAPE";
		case K_BACKSPACE:		return "BACKSPACE";
		case K_UPARROW:			return "UPARROW";
		case K_DOWNARROW:		return "DOWNARROW";
		case K_LEFTARROW:		return "LEFTARROW";
		case K_RIGHTARROW:		return "RIGHTARROW";
		case K_BRACKET_LEFT:	return "[";
		case K_BRACKET_RIGHT:	return "]";
		case K_0:				return "0";
		case K_1:				return "1";
		case K_2:				return "2";
		case K_3:				return "3";
		case K_4:				return "4";
		case K_5:				return "5";
		case K_6:				return "6";
		case K_7:				return "7";
		case K_8:				return "8";
		case K_9:				return "9";
		case K_POINT:			return ".";
		case K_COMMA:			return ",";
		case K_A:				return "A";
		case K_B:				return "B";
		case K_C:				return "C";
		case K_D:				return "D";
		case K_E:				return "E";
		case K_F:				return "F";
		case K_G:				return "G";
		case K_H:				return "H";
		case K_I:				return "I";
		case K_J:				return "J";
		case K_K:				return "K";
		case K_L:				return "L";
		case K_M:				return "M";
		case K_N:				return "N";
		case K_O:				return "O";
		case K_P:				return "P";
		case K_Q:				return "Q";
		case K_R:				return "R";
		case K_S:				return "S";
		case K_T:				return "T";
		case K_U:				return "U";
		case K_V:				return "V";
		case K_W:				return "W";
		case K_X:				return "X";
		case K_Y:				return "Y";
		case K_Z:				return "Z";
		case K_F1:				return "F1";
		case K_F2:				return "F2";
		case K_F3:				return "F3";
		case K_F4:				return "F4";
		case K_F5:				return "F5";
		case K_F6:				return "F6";
		case K_F7:				return "F7";
		case K_F8:				return "F8";
		case K_F9:				return "F9";
		case K_F10:				return "F10";
		case K_F11:				return "F11";
		case K_F12:				return "F12";
		case K_INS:				return "INSERT";
		case K_DEL:				return "DELETE";
		case K_PGDN:			return "PGDN";
		case K_PGUP:			return "PGUP";
		case K_HOME:			return "HOME";
		case K_END:				return "END";
		case K_SPACE:			return "SPACE";
		case K_ALT:				return "ALT";
		case K_SHIFT:			return "SHIFT";
		case K_CTRL:			return "CTRL";
		case K_MWHEELDOWN:		return "MWDOWN";
		case K_MWHEELUP:		return "MWUP";
		case K_MOUSE1:			return "MOUSE1";
		case K_MOUSE2:			return "MOUSE2";
		case K_MOUSE3:			return "MOUSE3";
		case K_MOUSE4:			return "MOUSE4";
		case K_MOUSE5:			return "MOUSE5";
		default:				return "none";
		}

		return 0;
	}

	inline int ReadStringConvert ( const char* Path, const char* Section, const char* Key, const char* DefValue )
	{
		char String[19];

		GetPrivateProfileString ( Section, Key, DefValue, String, 16, Path );

		return StringToKey ( String );
	}

	inline void Parse ( char* String, float* Variable, int MaxArray )
	{
		char* Parsing = strtok ( String, "," );

		for ( int i = 0; i <= MaxArray; ++i )
		{
			if ( !Parsing ) return;

			Variable[i] = ( float )atof ( Parsing );

			Parsing = strtok ( 0, "," );
		}
	}

	inline void Parse ( char* String, int* Variable, int MaxArray )
	{
		char* Parsing = strtok ( String, "," );

		for ( int i = 0; i <= MaxArray; ++i )
		{
			if ( !Parsing ) return;

			Variable[i] = atoi ( Parsing );

			Parsing = strtok ( 0, "," );
		}
	}
}