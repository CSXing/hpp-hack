#pragma once

#include "Main.h"

namespace Client
{
	struct LocalSpreadStruct
	{
		float GTime, PrevTime, BrokenTime;
		float SpreadVar, RecoilTime;
	
		unsigned int RandomSeed;

		int WeaponState;
		int PrcFlags, Recoil;

		bool Firing;
	};

	class Spread
	{
	public:
		static Vector2D GetDrawSpread ( );

		static void DefaultSpread ( int iWeaponID );
		static void NoSpread ( );
		static void GetSpreadOffset ( unsigned int Seed, int Future, Vector &InAngles, Vector &Velocity, Vector &OutAngles );

		static void HUD_PostRunCmd ( struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed );
		static void CL_CreateMove ( usercmd_s *cmd );	

	private:
		static LocalSpreadStruct LocalSpread;

		static Vector2D DrawSpread;

		static unsigned int U_Random ( );
		static void U_Srand ( unsigned int seed );
		static int UTIL_SharedRandomLong ( unsigned int seed, int low, int high );
		static float UTIL_SharedRandomFloat ( unsigned int seed, float low, float high );

		static float GetVecSpread ( float speed );
		static void PrimaryAttack ( );
		static void VectorAngles ( const Vector &Forward, Vector &Angles );
		static void GetSpreadXY ( unsigned int Seed, int Future, Vector &Velocity, Vector &Vec );
	};
}