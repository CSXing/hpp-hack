#include "Spread.h"

namespace Client
{
	LocalSpreadStruct Spread::LocalSpread;

	Vector2D Spread::DrawSpread;

	unsigned int glSeed = 0;

	Vector2D Spread::GetDrawSpread ( )
	{
		return DrawSpread;
	}

	unsigned int SeedTable[256] =
	{
		28985, 27138, 26457, 9451, 17764, 10909, 28790, 8716, 6361, 4853, 17798, 21977, 19643, 20662, 10834, 20103,
		27067, 28634, 18623, 25849, 8576, 26234, 23887, 18228, 32587, 4836, 3306, 1811, 3035, 24559, 18399, 315,
		26766, 907, 24102, 12370, 9674, 2972, 10472, 16492, 22683, 11529, 27968, 30406, 13213, 2319, 23620, 16823,
		10013, 23772, 21567, 1251, 19579, 20313, 18241, 30130, 8402, 20807, 27354, 7169, 21211, 17293, 5410, 19223,
		10255, 22480, 27388, 9946, 15628, 24389, 17308, 2370, 9530, 31683, 25927, 23567, 11694, 26397, 32602, 15031,
		18255, 17582, 1422, 28835, 23607, 12597, 20602, 10138, 5212, 1252, 10074, 23166, 19823, 31667, 5902, 24630,
		18948, 14330, 14950, 8939, 23540, 21311, 22428, 22391, 3583, 29004, 30498, 18714, 4278, 2437, 22430, 3439,
		28313, 23161, 25396, 13471, 19324, 15287, 2563, 18901, 13103, 16867, 9714, 14322, 15197, 26889, 19372, 26241,
		31925, 14640, 11497, 8941, 10056, 6451, 28656, 10737, 13874, 17356, 8281, 25937, 1661, 4850, 7448, 12744,
		21826, 5477, 10167, 16705, 26897, 8839, 30947, 27978, 27283, 24685, 32298, 3525, 12398, 28726, 9475, 10208,
		617, 13467, 22287, 2376, 6097, 26312, 2974, 9114, 21787, 28010, 4725, 15387, 3274, 10762, 31695, 17320,
		18324, 12441, 16801, 27376, 22464, 7500, 5666, 18144, 15314, 31914, 31627, 6495, 5226, 31203, 2331, 4668,
		12650, 18275, 351, 7268, 31319, 30119, 7600, 2905, 13826, 11343, 13053, 15583, 30055, 31093, 5067, 761,
		9685, 11070, 21369, 27155, 3663, 26542, 20169, 12161, 15411, 30401, 7580, 31784, 8985, 29367, 20989, 14203,
		29694, 21167, 10337, 1706, 28578, 887, 3373, 19477, 14382, 675, 7033, 15111, 26138, 12252, 30996, 21409,
		25678, 18555, 13256, 23316, 22407, 16727, 991, 9236, 5373, 29402, 6117, 15241, 27715, 19291, 19888, 19847
	};

	void Spread::GetSpreadOffset ( unsigned int Seed, int Future, Vector &InAngles, Vector &Velocity, Vector &OutAngles )
	{
		Vector Forward, Right, Up, VecDir, View, Dest, Spread;

		SDK::Interfaces::g_Engine.pfnAngleVectors ( InAngles, Forward, Right, Up );

		GetSpreadXY ( Seed, Future, Velocity, Spread );

		VecDir[0] = Forward[0] + Spread[0] * Right[0] + Spread[1] * Up[0];
		View[0] = 8192.0f * VecDir[0];

		VecDir[1] = Forward[1] + Spread[0] * Right[1] + Spread[1] * Up[1];
		View[1] = 8192.0f * VecDir[1];

		VecDir[2] = Forward[2] + Spread[0] * Right[2] + Spread[1] * Up[2];
		View[2] = 8192.0f * VecDir[2];

		VectorAngles ( View, Dest );
		Dest[0] *= -1.0f;

		OutAngles[0] = InAngles[0] - Dest[0];
		OutAngles[1] = InAngles[1] - Dest[1];
		OutAngles[2] = 0.0f;
	}

	void Spread::HUD_PostRunCmd ( struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed )
	{
		if ( runfuncs )
		{
			LocalSpread.RandomSeed = random_seed;
			LocalSpread.GTime = float ( time );
			LocalSpread.PrcFlags = to->client.flags;

			if ( cmd->buttons & IN_ATTACK && WeaponList::CanCurWeaponAttack ( ) )
			{
				PrimaryAttack ( );
			}
			else if ( !( cmd->buttons & ( IN_ATTACK | IN_ATTACK2 ) ) )
			{
				if ( LocalSpread.Firing )
				{
					LocalSpread.Firing = false;

					if ( LocalSpread.Recoil > 15 )
						LocalSpread.Recoil = 15;

					LocalSpread.RecoilTime = float ( time + 0.4 );
				}
				if ( WeaponList::IsCurWeaponSec ( ) )
				{
					LocalSpread.Recoil = 0;
				}
				else if ( LocalSpread.Recoil > 0 )
				{
					if ( LocalSpread.RecoilTime <= time )
					{
						LocalSpread.RecoilTime = float ( LocalSpread.RecoilTime + 0.0225 );
						--LocalSpread.Recoil;
					}
				}
			}

			for ( int i = 0; i < WeaponList::WeaponListIndex; ++i )
			{
				if ( WeaponList::WeaponListData[i].ID == to->client.m_iId )
				{
					if ( !WeaponList::WeaponListData[i].CurWeapon )
					{
						LocalSpread.Recoil = 0;
						LocalSpread.PrevTime = 0.0f;

						DefaultSpread ( WeaponList::WeaponListData[i].ID );

						LocalSpread.RecoilTime = float ( time );
						LocalSpread.Firing = true;
					}

					WeaponList::WeaponListData[i].CurWeapon = true;
				}
				else
					WeaponList::WeaponListData[i].CurWeapon = false;
			}

			for ( BYTE i = 0; i < MAX_WEAPONS; ++i )
			{
				int Index = WeaponList::GetWeaponIndexByID ( i );

				if ( Index == -1 )
					continue;

				to->weapondata[i].m_iId ?
					memcpy ( &WeaponList::WeaponListData[Index].weapondata, &to->weapondata[i], sizeof ( weapon_data_t ) ) :
					memset ( &WeaponList::WeaponListData[Index].weapondata, 0, sizeof ( weapon_data_t ) );
			}

			if ( WeaponList::IsReloading ( ) )
			{
				int ID = WeaponList::GetCurWeaponId ( );

				if ( ID == -1 )
					return;

				LocalSpread.Recoil = 0;
				LocalSpread.PrevTime = 0.0f;

				DefaultSpread ( ID );

				LocalSpread.RecoilTime = float ( time );
				LocalSpread.Firing = false;
			}
		}
	}

	void Spread::CL_CreateMove ( usercmd_s *cmd )
	{
		Vector Offset;

		if ( !g_Info->GetBadWeapon ( ) && g_Info->GetAliveLocal ( ) )
			GetSpreadOffset ( LocalSpread.RandomSeed, 2, cmd->viewangles, SDK::Interfaces::g_pPlayerMove->velocity, Offset );

		g_Info->SetVectorSpreadAngles ( Offset );
	}

	void Spread::DefaultSpread ( int WeaponID )
	{
		if ( WeaponID == WEAPONLIST_DEAGLE )			LocalSpread.SpreadVar = 0.9f;
		else if ( WeaponID == WEAPONLIST_MP5 )			LocalSpread.SpreadVar = 0.35f;
		else if ( WeaponID == WEAPONLIST_AK47 )			LocalSpread.SpreadVar = 0.2f;
		else if ( WeaponID == WEAPONLIST_SG552 )		LocalSpread.SpreadVar = 0.2f;
		else if ( WeaponID == WEAPONLIST_AUG )			LocalSpread.SpreadVar = 0.3f;
		else if ( WeaponID == WEAPONLIST_M4A1 )			LocalSpread.SpreadVar = 0.2f;
		else if ( WeaponID == WEAPONLIST_M249 )			LocalSpread.SpreadVar = 0.2f;
		else if ( WeaponID == WEAPONLIST_MAC10 )		LocalSpread.SpreadVar = 0.15f;
		else if ( WeaponID == WEAPONLIST_UMP45 )		LocalSpread.SpreadVar = 0.5f;
		else if ( WeaponID == WEAPONLIST_TMP )			LocalSpread.SpreadVar = 0.2f;
		else if ( WeaponID == WEAPONLIST_P90 )			LocalSpread.SpreadVar = 0.15f;
		else if ( WeaponID == WEAPONLIST_P228 )			LocalSpread.SpreadVar = 0.9f;
		else if ( WeaponID == WEAPONLIST_FIVESEVEN )	LocalSpread.SpreadVar = 0.92f;
		else if ( WeaponID == WEAPONLIST_ELITE )		LocalSpread.SpreadVar = 0.88f;
		else if ( WeaponID == WEAPONLIST_GLOCK18 )		LocalSpread.SpreadVar = 0.9f;
		else if ( WeaponID == WEAPONLIST_USP )			LocalSpread.SpreadVar = 0.92f;
		else if ( WeaponID == WEAPONLIST_G3SG1 )		LocalSpread.SpreadVar = 0.2f;
		else if ( WeaponID == WEAPONLIST_SG550 )		LocalSpread.SpreadVar = 0.2f;
		else											LocalSpread.SpreadVar = 0.0f;
	}

	void Spread::NoSpread ( )
	{
		Vector SpreadAngles, Forward, Screen;

		pmtrace_t Trace;

		SpreadAngles = g_Info->GetCmdViewAngles ( ) + g_Info->GetVectorSpreadAngles ( );

		SDK::Interfaces::g_Engine.pfnAngleVectors ( SpreadAngles, Forward, 0, 0 );
		SDK::Interfaces::g_Engine.pEventAPI->EV_SetTraceHull ( 2 );

		SDK::Interfaces::g_Engine.pEventAPI->EV_PlayerTrace ( g_Info->GetVectorEyePosition ( ),
			g_Info->GetVectorEyePosition ( ) + Forward * 8192.0f, PM_GLASS_IGNORE, -1, &Trace );

		if ( Utils::CalcScreen ( Trace.endpos, DrawSpread ) )
		{
			DrawSpread[0] = SDK::Interfaces::g_Screen.iWidth - DrawSpread[0];
			DrawSpread[1] = SDK::Interfaces::g_Screen.iHeight - DrawSpread[1];
		}
	}

	unsigned int Spread::U_Random ( )
	{
		glSeed *= 69069;
		glSeed += SeedTable[glSeed & 0xff];

		return ( ++glSeed & 0x0fffffff );
	}

	void Spread::U_Srand ( unsigned int seed )
	{
		glSeed = SeedTable[seed & 0xff];
	}

	int Spread::UTIL_SharedRandomLong ( unsigned int seed, int low, int high )
	{
		unsigned int Range = 0;

		U_Srand ( ( int )seed + low + high );

		Range = high - low + 1;

		if ( !( Range - 1 ) )
		{
			return low;
		}
		else
		{
			int Offset = 0;
			int rnum = 0;

			rnum = U_Random ( );
			Offset = rnum % Range;

			return low + Offset;
		}
	}

	float Spread::UTIL_SharedRandomFloat ( unsigned int seed, float low, float high )
	{
		unsigned int Range = 0;

		U_Srand ( ( int )seed + *( int * )&low + *( int * )&high );

		U_Random ( );
		U_Random ( );

		Range = unsigned int ( high - low );

		if ( !Range )
		{
			return low;
		}
		else
		{
			int TenSixRand = 0;
			float Offset = 0.0f;

			TenSixRand = U_Random ( ) & 65535;
			Offset = ( float )TenSixRand / 65536.0f;

			return low + Offset * Range;
		}
	}

	float Spread::GetVecSpread ( float speed )
	{
		float Spread = 0.0f;

		int ID = g_Info->GetWeaponID ( );

		switch ( ID )
		{
		case WEAPONLIST_DEAGLE:
			if ( LocalSpread.PrcFlags & FL_ONGROUND )
			{
				if ( speed )
				{
					Spread = 0.25f * ( 1.0f - LocalSpread.SpreadVar );
				}
				else if ( LocalSpread.PrcFlags & FL_DUCKING )
				{
					Spread = 0.115f * ( 1.0f - LocalSpread.SpreadVar );
				}
				else
				{
					Spread = 0.13f * ( 1.0f - LocalSpread.SpreadVar );
				}
			}
			else
				Spread = 1.5f * ( 1.0f - LocalSpread.SpreadVar );

			break;

		case WEAPONLIST_ELITE:
			if ( LocalSpread.PrcFlags & FL_ONGROUND )
			{
				if ( speed )
				{
					Spread = 0.175f * ( 1.0f - LocalSpread.SpreadVar );
				}
				else if ( LocalSpread.PrcFlags & FL_DUCKING )
				{
					Spread = 0.08f * ( 1.0f - LocalSpread.SpreadVar );
				}
				else
				{
					Spread = 0.01f * ( 1.0f - LocalSpread.SpreadVar );
				}
			}
			else
				Spread = 1.3f * ( 1.0f - LocalSpread.SpreadVar );

			break;

		case WEAPONLIST_GALIL:
			if ( LocalSpread.PrcFlags & FL_ONGROUND )
			{
				Spread = ( speed > 140.0f ) ? LocalSpread.SpreadVar * 0.07f + 0.04f : LocalSpread.SpreadVar * 0.0375f;
			}
			else
			{
				Spread = LocalSpread.SpreadVar * 0.4f + 0.03f;
			}

			break;

		case WEAPONLIST_FAMAS:
			if ( LocalSpread.PrcFlags & FL_ONGROUND )
			{
				Spread = ( speed > 140.0f ) ? LocalSpread.SpreadVar * 0.07f + 0.03f : LocalSpread.SpreadVar * 0.020f;
			}
			else
			{
				Spread = LocalSpread.SpreadVar * 0.4f + 0.04f;
			}

			break;

		case WEAPONLIST_FIVESEVEN:
			if ( LocalSpread.PrcFlags & FL_ONGROUND )
			{
				if ( speed )
				{
					Spread = 0.255f * ( 1.0f - LocalSpread.SpreadVar );
				}
				else if ( LocalSpread.PrcFlags & FL_DUCKING )
				{
					Spread = 0.075f * ( 1.0f - LocalSpread.SpreadVar );
				}
				else
				{
					Spread = 0.15f * ( 1.0f - LocalSpread.SpreadVar );
				}
			}
			else
				Spread = 1.5f * ( 1.0f - LocalSpread.SpreadVar );

			break;

		case WEAPONLIST_GLOCK18:
			if ( !WeaponList::IsCurWeaponInBurst ( ) )
			{
				if ( LocalSpread.PrcFlags & FL_ONGROUND )
				{
					if ( speed )
					{
						Spread = 0.165f * ( 1.0f - LocalSpread.SpreadVar );
					}
					else if ( LocalSpread.PrcFlags & FL_DUCKING )
					{
						Spread = 0.075f * ( 1.0f - LocalSpread.SpreadVar );
					}
					else
					{
						Spread = 0.01f * ( 1.0f - LocalSpread.SpreadVar );
					}
				}
				else
					Spread = 1.0f - LocalSpread.SpreadVar;
			}
			else
			{
				if ( LocalSpread.PrcFlags & FL_ONGROUND )
				{
					if ( speed )
					{
						Spread = 0.185f * ( 1.0f - LocalSpread.SpreadVar );
					}
					else if ( LocalSpread.PrcFlags & FL_DUCKING )
					{
						Spread = 0.095f * ( 1.0f - LocalSpread.SpreadVar );
					}
					else
					{
						Spread = 0.3f * ( 1.0f - LocalSpread.SpreadVar );
					}
				}
				else
					Spread = 1.2f * ( 1.0f - LocalSpread.SpreadVar );
			}

			break;

		case WEAPONLIST_P228:
			if ( LocalSpread.PrcFlags & FL_ONGROUND )
			{
				if ( speed )
				{
					Spread = 0.255f * ( 1.0f - LocalSpread.SpreadVar );
				}
				else if ( LocalSpread.PrcFlags & FL_DUCKING )
				{
					Spread = 0.075f * ( 1.0f - LocalSpread.SpreadVar );
				}
				else
				{
					Spread = 0.15f * ( 1.0f - LocalSpread.SpreadVar );
				}
			}
			else
				Spread = 1.5f * ( 1.0f - LocalSpread.SpreadVar );

			break;

		case WEAPONLIST_G3SG1:
			if ( LocalSpread.PrcFlags & FL_ONGROUND )
			{
				if ( speed > 100.0f )
				{
					Spread = 0.15f;
				}
				else if ( LocalSpread.PrcFlags & FL_DUCKING )
				{
					Spread = 0.04f * ( 1.0f - LocalSpread.SpreadVar );
				}
				else
				{
					Spread = 0.06f * ( 1.0f - LocalSpread.SpreadVar );
				}
			}
			else
				Spread = 0.45f * ( 1.0f - LocalSpread.SpreadVar );

			if ( !( g_Info->GetFOV ( ) < 90 ) )
				Spread += 0.0016f;

			break;

		case WEAPONLIST_SG550:
			if ( LocalSpread.PrcFlags & FL_ONGROUND )
			{
				if ( speed )
				{
					Spread = 0.15f;
				}
				else if ( LocalSpread.PrcFlags & FL_DUCKING )
				{
					Spread = 0.04f * ( 1.0f - LocalSpread.SpreadVar );
				}
				else
				{
					Spread = 0.05f * ( 1.0f - LocalSpread.SpreadVar );
				}
			}
			else
				Spread = 0.45f * ( 1.0f - LocalSpread.SpreadVar );

			if ( !( g_Info->GetFOV ( ) < 90 ) )
				Spread += 0.025f;

			break;

		case WEAPONLIST_USP:
			if ( !WeaponList::IsCurWeaponSilenced ( ) )
			{
				if ( LocalSpread.PrcFlags & FL_ONGROUND )
				{
					if ( speed )
					{
						Spread = 0.225f * ( 1.0f - LocalSpread.SpreadVar );
					}
					else if ( LocalSpread.PrcFlags & FL_DUCKING )
					{
						Spread = 0.08f * ( 1.0f - LocalSpread.SpreadVar );
					}
					else
					{
						Spread = 0.01f * ( 1.0f - LocalSpread.SpreadVar );
					}
				}
				else
					Spread = 1.2f * ( 1.0f - LocalSpread.SpreadVar );
			}
			else
			{
				if ( LocalSpread.PrcFlags & FL_ONGROUND )
				{
					if ( speed )
					{
						Spread = 0.25f * ( 1.0f - LocalSpread.SpreadVar );
					}
					else if ( LocalSpread.PrcFlags & FL_DUCKING )
					{
						Spread = 0.125f * ( 1.0f - LocalSpread.SpreadVar );
					}
					else
					{
						Spread = 0.15f * ( 1.0f - LocalSpread.SpreadVar );
					}
				}
				else
					Spread = 1.3f * ( 1.0f - LocalSpread.SpreadVar );
			}

			break;

		case WEAPONLIST_AK47:
			if ( LocalSpread.PrcFlags & FL_ONGROUND )
			{
				Spread = ( speed > 140.0f ) ? LocalSpread.SpreadVar * 0.07f + 0.04f : LocalSpread.SpreadVar * 0.0275f;
			}
			else
			{
				Spread = LocalSpread.SpreadVar * 0.4f + 0.04f;
			}

			break;

		case WEAPONLIST_SG552:
			if ( LocalSpread.PrcFlags & FL_ONGROUND )
			{
				Spread = ( speed > 140.0f ) ? LocalSpread.SpreadVar * 0.07f + 0.035f : LocalSpread.SpreadVar * 0.02f;
			}
			else
			{
				Spread = LocalSpread.SpreadVar * 0.4f + 0.035f;
			}

			break;

		case WEAPONLIST_AUG:
			if ( LocalSpread.PrcFlags & FL_ONGROUND )
			{
				Spread = ( speed > 140.0f ) ? LocalSpread.SpreadVar * 0.07f + 0.035f : LocalSpread.SpreadVar * 0.02f;
			}
			else
			{
				Spread = LocalSpread.SpreadVar * 0.4f + 0.035f;
			}

			break;

		case WEAPONLIST_M249:
			if ( LocalSpread.PrcFlags & FL_ONGROUND )
			{
				Spread = ( speed > 140.0f ) ? LocalSpread.SpreadVar * 0.095f + 0.045f : LocalSpread.SpreadVar * 0.03f;
			}
			else
			{
				Spread = LocalSpread.SpreadVar * 0.5f + 0.045f;
			}

			break;

		case WEAPONLIST_M4A1:
			if ( LocalSpread.PrcFlags & FL_ONGROUND )
			{
				if ( !WeaponList::IsCurWeaponSilenced ( ) )
				{
					Spread = ( speed > 140.0f ) ? LocalSpread.SpreadVar * 0.07f + 0.035f : LocalSpread.SpreadVar * 0.02f;
				}
				else
				{
					Spread = ( speed > 140.0f ) ? LocalSpread.SpreadVar * 0.07f + 0.035f : LocalSpread.SpreadVar * 0.025f;
				}
			}
			else
				Spread = LocalSpread.SpreadVar * 0.4f + 0.035f;

			break;

		case WEAPONLIST_MP5:
			Spread = ( LocalSpread.PrcFlags & FL_ONGROUND ) ? 0.04f * LocalSpread.SpreadVar : 0.2f * LocalSpread.SpreadVar;

			break;

		case WEAPONLIST_MAC10:
			Spread = ( LocalSpread.PrcFlags & FL_ONGROUND ) ? 0.03f * LocalSpread.SpreadVar : 0.375f * LocalSpread.SpreadVar;

			break;

		case WEAPONLIST_P90:
			if ( LocalSpread.PrcFlags & FL_ONGROUND )
			{
				Spread = ( speed > 170.0f ) ? LocalSpread.SpreadVar * 0.115f : LocalSpread.SpreadVar * 0.045f;
			}
			else
			{
				Spread = LocalSpread.SpreadVar * 0.3f;
			}

			break;

		case WEAPONLIST_TMP:
			Spread = ( LocalSpread.PrcFlags & FL_ONGROUND ) ? 0.03f * LocalSpread.SpreadVar : 0.25f * LocalSpread.SpreadVar;

			break;

		case WEAPONLIST_UMP45:
			Spread = ( LocalSpread.PrcFlags & FL_ONGROUND ) ? 0.04f * LocalSpread.SpreadVar : 0.24f * LocalSpread.SpreadVar;

			break;

		case WEAPONLIST_AWP:
			if ( LocalSpread.PrcFlags & FL_ONGROUND )
			{
				if ( speed < 10.0f )
				{
					Spread = ( LocalSpread.PrcFlags & FL_DUCKING ) ? 0.0f : 0.001f;
				}
				else if ( speed < 140.0f )
				{
					Spread = 0.01f;
				}
				else
				{
					Spread = 0.25f;
				}
			}
			else
				Spread = 0.85f;

			if ( !( g_Info->GetFOV ( ) < 90 ) )
				Spread += 0.08f;

			break;

		case WEAPONLIST_SCOUT:
			if ( LocalSpread.PrcFlags & FL_ONGROUND )
			{
				if ( speed < 170.0f )
				{
					Spread = ( LocalSpread.PrcFlags & FL_DUCKING ) ? 0.0f : 0.007f;
				}
				else
				{
					Spread = 0.075f;
				}
			}
			else
				Spread = 0.2f;

			if ( !( g_Info->GetFOV ( ) < 90 ) )
				Spread += 0.025f;

			break;

		default:
			Spread = 0.0f;

			break;
		}

		return Spread;
	}

	void Spread::PrimaryAttack ( )
	{
		int ID = WeaponList::GetCurWeaponId ( );

		switch ( ID )
		{
		case WEAPONLIST_DEAGLE:
			if ( LocalSpread.PrevTime )
			{
				LocalSpread.SpreadVar = LocalSpread.SpreadVar - ( 0.35f * ( 0.4f - ( LocalSpread.GTime - LocalSpread.PrevTime ) ) );

				if ( LocalSpread.SpreadVar > 0.9f )
				{
					LocalSpread.SpreadVar = 0.9f;
				}
				else if ( LocalSpread.SpreadVar < 0.55f )
				{
					LocalSpread.SpreadVar = 0.55f;
				}
			}

			++LocalSpread.Recoil;

			LocalSpread.PrevTime = LocalSpread.GTime;

			break;

		case WEAPONLIST_ELITE:
			if ( LocalSpread.PrevTime )
			{
				LocalSpread.SpreadVar = LocalSpread.SpreadVar - ( 0.275f * ( 0.325f - ( LocalSpread.GTime - LocalSpread.PrevTime ) ) );

				if ( LocalSpread.SpreadVar > 0.88f )
				{
					LocalSpread.SpreadVar = 0.88f;
				}
				else if ( LocalSpread.SpreadVar < 0.55f )
				{
					LocalSpread.SpreadVar = 0.55f;
				}
			}

			++LocalSpread.Recoil;

			LocalSpread.PrevTime = LocalSpread.GTime;

			break;

		case WEAPONLIST_GALIL:
			++LocalSpread.Recoil;

			LocalSpread.Firing = true;

			LocalSpread.SpreadVar = ( LocalSpread.Recoil * LocalSpread.Recoil * LocalSpread.Recoil ) / 200.0f + 0.35f;

			if ( LocalSpread.SpreadVar > 1.25f )
				LocalSpread.SpreadVar = 1.25f;

			LocalSpread.PrevTime = LocalSpread.GTime;

			break;

		case WEAPONLIST_FAMAS:
			++LocalSpread.Recoil;

			LocalSpread.Firing = true;

			LocalSpread.SpreadVar = ( LocalSpread.Recoil * LocalSpread.Recoil * LocalSpread.Recoil ) / 215.0f + 0.3f;

			if ( LocalSpread.SpreadVar > 1.0f )
				LocalSpread.SpreadVar = 1.0f;

			LocalSpread.PrevTime = LocalSpread.GTime;

			break;

		case WEAPONLIST_FIVESEVEN:
			if ( LocalSpread.PrevTime )
			{
				LocalSpread.SpreadVar = LocalSpread.SpreadVar - ( 0.25f * ( 0.275f - ( LocalSpread.GTime - LocalSpread.PrevTime ) ) );

				if ( LocalSpread.SpreadVar > 0.92f )
				{
					LocalSpread.SpreadVar = 0.92f;
				}
				else if ( LocalSpread.SpreadVar < 0.725f )
				{
					LocalSpread.SpreadVar = 0.725f;
				}
			}

			++LocalSpread.Recoil;

			LocalSpread.PrevTime = LocalSpread.GTime;

			break;

		case WEAPONLIST_GLOCK18:
			if ( !WeaponList::IsCurWeaponInBurst ( ) )
				++LocalSpread.Recoil;

			if ( LocalSpread.PrevTime )
			{
				LocalSpread.SpreadVar = LocalSpread.SpreadVar - ( 0.275f * ( 0.325f - ( LocalSpread.GTime - LocalSpread.PrevTime ) ) );

				if ( LocalSpread.SpreadVar > 0.9f )
				{
					LocalSpread.SpreadVar = 0.9f;
				}
				else if ( LocalSpread.SpreadVar < 0.6f )
				{
					LocalSpread.SpreadVar = 0.6f;
				}
			}

			LocalSpread.PrevTime = LocalSpread.GTime;

			break;

		case WEAPONLIST_P228:
			if ( LocalSpread.PrevTime )
			{
				LocalSpread.SpreadVar = LocalSpread.SpreadVar - ( 0.3f * ( 0.325f - ( LocalSpread.GTime - LocalSpread.PrevTime ) ) );

				if ( LocalSpread.SpreadVar > 0.9f )
				{
					LocalSpread.SpreadVar = 0.9f;
				}
				else if ( LocalSpread.SpreadVar < 0.6f )
				{
					LocalSpread.SpreadVar = 0.6f;
				}
			}

			++LocalSpread.Recoil;

			LocalSpread.PrevTime = LocalSpread.GTime;

			break;

		case WEAPONLIST_G3SG1:
			if ( LocalSpread.BrokenTime )
			{
				LocalSpread.SpreadVar = 0.55f + ( 0.3f * ( LocalSpread.GTime - LocalSpread.BrokenTime ) );

				if ( LocalSpread.SpreadVar > 0.98f )
					LocalSpread.SpreadVar = 0.98f;
			}

			++LocalSpread.Recoil;

			LocalSpread.BrokenTime = LocalSpread.GTime;

			LocalSpread.Firing = true;

			break;

		case WEAPONLIST_SG550:
			if ( LocalSpread.BrokenTime )
			{
				LocalSpread.SpreadVar = 0.65f + ( 0.35f * ( LocalSpread.GTime - LocalSpread.BrokenTime ) );

				if ( LocalSpread.SpreadVar > 0.98f )
					LocalSpread.SpreadVar = 0.98f;
			}

			++LocalSpread.Recoil;

			LocalSpread.BrokenTime = LocalSpread.GTime;

			LocalSpread.Firing = true;

			break;

		case WEAPONLIST_USP:
			if ( LocalSpread.PrevTime )
			{
				LocalSpread.SpreadVar = LocalSpread.SpreadVar - ( 0.275f * ( 0.3f - ( LocalSpread.GTime - LocalSpread.PrevTime ) ) );

				if ( LocalSpread.SpreadVar > 0.92f )
				{
					LocalSpread.SpreadVar = 0.92f;
				}
				else if ( LocalSpread.SpreadVar < 0.6f )
				{
					LocalSpread.SpreadVar = 0.6f;
				}
			}

			++LocalSpread.Recoil;

			LocalSpread.PrevTime = LocalSpread.GTime;

			break;

		case WEAPONLIST_AK47:
			++LocalSpread.Recoil;

			LocalSpread.Firing = true;

			LocalSpread.SpreadVar = LocalSpread.Recoil * LocalSpread.Recoil * LocalSpread.Recoil / 200.0f + 0.35f;

			if ( LocalSpread.SpreadVar > 1.25f )
				LocalSpread.SpreadVar = 1.25f;

			LocalSpread.PrevTime = LocalSpread.GTime;

			break;

		case WEAPONLIST_SG552:
			++LocalSpread.Recoil;

			LocalSpread.Firing = true;

			LocalSpread.SpreadVar = LocalSpread.Recoil * LocalSpread.Recoil * LocalSpread.Recoil / 220.0f + 0.3f;

			if ( LocalSpread.SpreadVar > 1.0f )
				LocalSpread.SpreadVar = 1.0f;

			LocalSpread.PrevTime = LocalSpread.GTime;

			break;

		case WEAPONLIST_AUG:
			++LocalSpread.Recoil;

			LocalSpread.Firing = true;

			LocalSpread.SpreadVar = LocalSpread.Recoil * LocalSpread.Recoil * LocalSpread.Recoil / 215.0f + 0.3f;

			if ( LocalSpread.SpreadVar > 1.0f )
				LocalSpread.SpreadVar = 1.0f;

			LocalSpread.PrevTime = LocalSpread.GTime;

			break;

		case WEAPONLIST_M249:
			++LocalSpread.Recoil;

			LocalSpread.Firing = true;

			LocalSpread.SpreadVar = LocalSpread.Recoil * LocalSpread.Recoil * LocalSpread.Recoil / 175.0f + 0.4f;

			if ( LocalSpread.SpreadVar > 0.9f )
				LocalSpread.SpreadVar = 0.9f;

			LocalSpread.PrevTime = LocalSpread.GTime;

			break;

		case WEAPONLIST_M4A1:
			++LocalSpread.Recoil;

			LocalSpread.Firing = true;

			LocalSpread.SpreadVar = LocalSpread.Recoil * LocalSpread.Recoil * LocalSpread.Recoil / 220.0f + 0.3f;

			if ( LocalSpread.SpreadVar > 1.0f )
				LocalSpread.SpreadVar = 1.0f;

			LocalSpread.PrevTime = LocalSpread.GTime;

			break;

		case WEAPONLIST_MP5:
			++LocalSpread.Recoil;

			LocalSpread.SpreadVar = LocalSpread.Recoil * LocalSpread.Recoil * LocalSpread.Recoil / 220.01f + 0.45f;

			if ( LocalSpread.SpreadVar > 0.75f )
				LocalSpread.SpreadVar = 0.75f;

			LocalSpread.PrevTime = LocalSpread.GTime;

			LocalSpread.Firing = true;

			break;

		case WEAPONLIST_MAC10:
			++LocalSpread.Recoil;

			LocalSpread.Firing = true;

			LocalSpread.SpreadVar = LocalSpread.Recoil * LocalSpread.Recoil * LocalSpread.Recoil / 200.0f + 0.6f;

			if ( LocalSpread.SpreadVar > 1.65f )
				LocalSpread.SpreadVar = 1.65f;

			LocalSpread.PrevTime = LocalSpread.GTime;

			break;

		case WEAPONLIST_P90:
			++LocalSpread.Recoil;

			LocalSpread.Firing = true;

			LocalSpread.SpreadVar = LocalSpread.Recoil * LocalSpread.Recoil / 175.0f + 0.45f;

			if ( LocalSpread.SpreadVar > 1.0f )
				LocalSpread.SpreadVar = 1.0f;

			LocalSpread.PrevTime = LocalSpread.GTime;

			break;

		case WEAPONLIST_TMP:
			++LocalSpread.Recoil;

			LocalSpread.Firing = true;

			LocalSpread.SpreadVar = LocalSpread.Recoil * LocalSpread.Recoil * LocalSpread.Recoil / 200.0f + 0.55f;

			if ( LocalSpread.SpreadVar > 1.4f )
				LocalSpread.SpreadVar = 1.4f;

			LocalSpread.PrevTime = LocalSpread.GTime;

			break;

		case WEAPONLIST_UMP45:
			++LocalSpread.Recoil;

			LocalSpread.Firing = true;

			LocalSpread.SpreadVar = LocalSpread.Recoil * LocalSpread.Recoil / 210.0f + 0.5f;

			if ( LocalSpread.SpreadVar > 1.0f )
				LocalSpread.SpreadVar = 1.0f;

			LocalSpread.PrevTime = LocalSpread.GTime;

			break;

		case WEAPONLIST_AWP:
			++LocalSpread.Recoil;

			LocalSpread.PrevTime = LocalSpread.GTime;

			LocalSpread.Firing = true;

			break;

		case WEAPONLIST_SCOUT:
			++LocalSpread.Recoil;

			LocalSpread.PrevTime = LocalSpread.GTime;

			LocalSpread.Firing = true;

			break;

		default:

			break;
		}

		return;
	}

	void Spread::VectorAngles ( const Vector &Forward, Vector &Angles )
	{
		Vector vAngles;

		if ( !Forward[1] && !Forward[0] )
		{
			vAngles[0] = 0.0f;
			vAngles[1] = 0.0f;
		}
		else
		{
			vAngles[1] = atan2f ( Forward[1], Forward[0] ) * 180.0f / M_PI_F;

			if ( vAngles[1] < 0.0f )
				vAngles[1] += 360.0f;

			vAngles[2] = sqrtf ( Forward[0] * Forward[0] + Forward[1] * Forward[1] );

			vAngles[0] = atan2f ( Forward[2], vAngles[2] ) * 180.0f / M_PI_F;
		}

		Angles[0] = vAngles[0];
		Angles[1] = vAngles[1];
		Angles[2] = 0.0f;
	}

	void Spread::GetSpreadXY ( unsigned int Seed, int Future, Vector &Velocity, Vector &Vec )
	{
		float VecSpread = 0.0f;

		Vec[0] = UTIL_SharedRandomFloat ( Seed + Future, -0.5f, 0.5f ) + UTIL_SharedRandomFloat ( Seed + 1 + Future, -0.5f, 0.5f );
		Vec[1] = UTIL_SharedRandomFloat ( Seed + 2 + Future, -0.5f, 0.5f ) + UTIL_SharedRandomFloat ( Seed + 3 + Future, -0.5f, 0.5f );

		VecSpread = GetVecSpread ( Velocity.Length ( ) );

		Vec[0] *= VecSpread;
		Vec[1] *= VecSpread;
	}
}