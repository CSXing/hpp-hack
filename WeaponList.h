#pragma once

#include "Main.h"

namespace Client
{
	struct weapon_list_s
	{
		char name[MAX_WEAPON_NAME];
		int len;
		char command[MAX_WEAPON_NAME];
		int AmmoType;
		int Ammo2Type;
		int Max1;
		int Max2;
		int Slot;
		int SlotPos;
		int ID;
		int Flags;
		int ClipCap;
		int CAmmo;
		int XAmmo;
		bool Active;
		bool CurWeapon;
		int penetrate;
		weapon_data_t weapondata;
		float distance;
		int bullettype;
		float wallpierce1;
		float wallpierce2;
		int damage1;
		int damage2;
	};

	class WeaponList
	{
	public:
		static int OldWeaponBits;
		static int WeaponListIndex;

		static weapon_list_s* WeaponListData;

		static void SetWeaponData ( weapon_list_s* weapon );

		static weapon_list_s* GetCurWeapon ( );
		static weapon_list_s* GetSecWeapon ( );

		static bool IsReloading ( );
		static bool IsCurWeaponSec ( );
		static bool CanCurWeaponAttack ( );
		static bool IsCurWeaponInBurst ( );
		static bool IsCurWeaponSilenced ( );

		static int GetCurWeaponId ( );
		static int GetWeaponIndexByID ( int WeaponID );

		static void WeaponListCurWeapon ( int CurWeapon, int WeaponID, int Ammo );
		static void WeaponListAmmoX ( int ID, int Count );
		static void WeaponListUpdate ( int WeaponBits );

		static void WeaponListAdd ( char* weaponname, int ammo1type, int max1, int ammo2type, int max2, int slot, int slotpos, int id, int flags );
		static void WeaponListClear ( );
	};
}