#pragma once
#pragma warning (disable: 4996)

#include "Main.h"

namespace Utils
{
	pcmd_t CommandByName ( char* Name );
	PUserMsg UserMsgByName ( char* MsgName );
	pfnUserMsgHook HookUserMsg ( char *MsgName, pfnUserMsgHook pfn );
	PEngineMsg EngineMsgByName ( char* MsgName );
	pfnEngineMsgHook HookEngineMsg ( char *MsgName, pfnEngineMsgHook pfn );

	inline char* ConvertTypeToRenderString ( int Type )
	{
		switch ( Type )
		{
		case 1: return "Software";
		case 2: return "OpenGL";
		case 3: return "D3D";
		default: return "Unknown";
		}
	}

	inline float EndSpeed ( float flStartSpeed, float flGravity, float flFrameTime, float flDistance )
	{
		while ( flDistance > 2.0f )
		{
			flStartSpeed += flGravity * flFrameTime;
			flDistance -= flStartSpeed * flFrameTime;
		}

		return flStartSpeed;
	}

	inline float Interp ( float s1, float s2, float s3, float f1, float f3 )
	{
		if ( s2 == s1 ) return f1;
		if ( s2 == s3 ) return f3;
		if ( s3 == s1 ) return f1;

		return f1 + ( ( s2 - s1 ) / ( s3 - s1 ) ) * ( f3 - f1 );
	}

	void HookCommand ( char *CmdName, xcommand_t *CmdPointer, void ( *Function )( void ) );
	void Error ( const bool &Exit, char *Message, ... );
	void native_memcpy ( void* dst, const void* src, size_t count );
	void native_memset ( void *szBuffer, DWORD dwLen, DWORD dwSym );

	bool PathFree ( Vector& vInput );
	bool CalcScreen ( Vector& pflOrigin, Vector2D& pflVecScreen );

	inline void VectorAngles ( const Vector &Forward, Vector &Angles )
	{
		Vector vAngles;

		if ( !Forward[1] && !Forward[0] )
		{
			vAngles[0] = ( Forward[2] > 0.0f ) ? 270.0f : 90.0f;
			vAngles[1] = 0.0f;
		}
		else
		{
			vAngles[1] = atan2f ( Forward[1], Forward[0] ) * 180.0f / M_PI_F;

			if ( vAngles[1] < 0.0f )
				vAngles[1] += 360.0f;

			vAngles[2] = sqrtf ( POW ( Forward[0] ) + POW ( Forward[1] ) );
			vAngles[0] = atan2f ( -Forward[2], vAngles[2] ) * 180.0f / M_PI_F;

			if ( vAngles[0] < 0.0f )
				vAngles[0] += 360.0f;
		}

		Angles[0] = vAngles[0];
		Angles[1] = vAngles[1];
		Angles[2] = 0.0f;

		while ( Angles[0] < -89.0f )
		{
			Angles[0] += 180.0f;
			Angles[1] += 180.0f;
		}

		while ( Angles[0] > 89.0f )
		{
			Angles[0] -= 180.0f;
			Angles[1] += 180.0f;
		}

		while ( Angles[1] < -180.0f )
			Angles[1] += 360.0f;

		while ( Angles[1] > 180.0f )
			Angles[1] -= 360.0f;
	}

	Vector2D GetPunchScreen ( );
	Vector2D GetScreen ( );

	inline float CalcDistanceScreen ( const Vector2D &flScreenCenter, const Vector2D &flPlayerPosScreen )
	{
		return sqrtf ( POW ( flPlayerPosScreen[0] - flScreenCenter[0] ) + POW ( flPlayerPosScreen[1] - flScreenCenter[1] ) );
	}

	inline float AngleBetvenVectors ( const Vector &a, const Vector &b )
	{
		float l1 = a.Length ( );
		float l2 = b.Length ( );
		float sc = a.x * b.x + a.y * b.y + a.z * b.z;

		return acosf ( sc / ( l1 * l2 ) ) * ( 180.0f / M_PI_F );
	}

	inline void GetSection ( const int& Index, std::string& Weapon )
	{
		switch ( Index )
		{
		case WEAPONLIST_USP:		Weapon = "USP";			break;
		case WEAPONLIST_DEAGLE:		Weapon = "DEagle";		break;
		case WEAPONLIST_P228:		Weapon = "P228";		break;
		case WEAPONLIST_FIVESEVEN:	Weapon = "Five-Seven";	break;
		case WEAPONLIST_ELITE:		Weapon = "Elite";		break;
		case WEAPONLIST_M3:			Weapon = "M3";			break;
		case WEAPONLIST_MP5:		Weapon = "MP5";			break;
		case WEAPONLIST_TMP:		Weapon = "TMP";			break;
		case WEAPONLIST_MAC10:		Weapon = "MAC10";		break;
		case WEAPONLIST_UMP45:		Weapon = "UMP45";		break;
		case WEAPONLIST_P90:		Weapon = "P90";			break;
		case WEAPONLIST_AK47:		Weapon = "AK47";		break;
		case WEAPONLIST_M4A1:		Weapon = "M4A1";		break;
		case WEAPONLIST_FAMAS:		Weapon = "FAMAS";		break;
		case WEAPONLIST_GALIL:		Weapon = "Galil";		break;
		case WEAPONLIST_AUG:		Weapon = "AUG";			break;
		case WEAPONLIST_SG552:		Weapon = "SG552";		break;
		case WEAPONLIST_SG550:		Weapon = "SG550";		break;
		case WEAPONLIST_SCOUT:		Weapon = "Scout";		break;
		case WEAPONLIST_AWP:		Weapon = "AWP";			break;
		case WEAPONLIST_G3SG1:		Weapon = "G3SG1";		break;
		case WEAPONLIST_M249:		Weapon = "M249";		break;
		case WEAPONLIST_XM1014:		Weapon = "XM1014";		break;
		case WEAPONLIST_GLOCK18:	Weapon = "Glock18";		break;
		default:					Weapon = "Glock18";
		}
	}

	void MakeAngle ( const Vector &Angles, usercmd_s *cmd );

	inline void* native_memcpy2 ( void * dst, const void * src, size_t count )
	{
		void *ret = dst;

		while ( --count )
		{
			*( char * )dst = *( char * )src;
			dst = ( char * )dst + 1;
			src = ( char * )src + 1;
		}

		return( ret );
	}

	inline bool CheckFOV ( const Vector2D &dest, const Vector2D &Screen, const float &FOV )
	{
		Vector2D ScreenPos;

		ScreenPos[0] = abs ( dest[0] - Screen[0] );
		ScreenPos[1] = abs ( dest[1] - Screen[1] );

		return ScreenPos[0] <= FOV && ScreenPos[1] <= FOV;
	}

	inline void SmoothAimAngles ( const Vector &MyViewAngles, const Vector &AimAngles, Vector &OutAngles, const float &Smoothing )
	{
		OutAngles = AimAngles - MyViewAngles;

		ClampAngles ( OutAngles );

		OutAngles[0] = OutAngles[0] / Smoothing + MyViewAngles[0];
		OutAngles[1] = OutAngles[1] / Smoothing + MyViewAngles[1];

		ClampAngles ( OutAngles );
	}
}