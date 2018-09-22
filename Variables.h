#pragma once

#include "Main.h"

struct TWeaponsStruct
{
	bool Trigger;
	bool OnlyHead;
	bool ProSpread;
};

struct TriggerStruct
{
	bool Enable, FriendlyFire;
	bool VisibleCheck;
	bool SnipersOnlyInZoom;
	BYTE Key, SwitchKey;
};

struct GroundStrafeStruct
{
	char* ScrollDistanceString;
	char* ScrollCountString;
	float ScrollDistance[2];
	float SlowdownScale;
	float SlowdownAngle;
	int ScrollDirection;
	int ScrollCount[2];
	int StandUpFallVelocity;
	bool ScrollEmulation;
	bool FallRun, Helper;
	BYTE Key, StandUpKey;
};

struct ChamsStruct
{
	char* ColorTVisString;
	char* ColorTHideString;
	char* ColorCTVisString;
	char* ColorCTHideString;
	char* WeaponColorVisString;
	char* WeaponColorHideString;
	char* HandsColorString;
	int Player, HandsRenderType;
	int WeaponRenderType;
	int PlayerRenderType;
	int WeaponColorVis[3];
	int WeaponColorHide[3];
	int ColorTVis[3], ColorTHide[3];
	int ColorCTVis[3], ColorCTHide[3];
	int HandsColor[3];
	bool Enable, Weapon, Hands;
	bool WeaponVisibleOnly;
	bool PlayerVisibleOnly;
};

struct FastZoomStruct
{
	int Delay;
	bool Enable;
	bool QuickSwitch;
};

struct AutoPistolStruct
{
	int Delay;
	bool Enable;
};

struct RecoilStruct
{
	float X, Y;
	float Smooth;
	int BulletStart;
	bool Enable;
};

struct OtherStruct
{
	char* FontColorString;
	int FontColor[4];
	bool DrawAimSpot, DrawAimFOV;
	bool DrawPunch, RemoveSmoke;
	bool DrawSpread, StatusAimBot;
	bool StatusTriggerBot, FontOutline;
};

struct WeaponsStruct
{
	char* BulletControlString;
	float FOV, Smooth;
	float Recoil, RecoilFOV;
	float RecoilSmooth;
	float Prediction;
	float RecoilPrediction;
	int BulletControl[2];
	int HitBox, Delay;
	int DelayType;
	bool Aim, HitBoxNearest;
};

struct AimStruct
{
	int KillDelay;
	bool Enable, Silent;
	bool FriendlyFire;
	bool VisibleCheck;
	bool FlashCheck;
	bool FOVDistance;
};

struct CrosshairStruct
{
	char* ColorString;
	float DynamicScale;
	int Gap, Thickness;
	int Size, Color[4];
	bool Enable, Dot;
	bool Outline, Dynamic;
	bool Snipers;
};

struct BunnyHopStruct
{
	char* ScrollDistanceString;
	float ScrollDistance[2];
	int StandUpFallVelocity;
	int HelperIdealPercent;
	int ScrollDirection;
	bool NoSlowdown, OnLadder;
	bool ScrollEmulation;
	bool ScrollRandFails;
	bool Helper, StandUpAuto;
	bool HelperNoSlowdown;
	BYTE Key, StandUpKey;
};

struct SpeedStruct
{
	float Player;
	float Boost;
	float Slowmo;
	float HelperGround;
	float HelperLadder;
	float HelperFly;
	int Engine;
	bool Helper;
	BYTE BoostKey;
	BYTE SlowmoKey;
};

struct NoFlashStruct
{
	char* FadeColorString;
	int FadeLimit, DrawFlashed;
	int FadeColor[3];
	bool Enable, FontOutline;
	bool FadeColorEnable;
	bool FadeColorRandom;
};

struct ESPStruct
{
	char *ColorTVisString, *ColorTHideString;
	char *ColorCTVisString, *ColorCTHideString;
	char *FontColorString;
	int Player, PlayerBox, PlayerBoxFilled;
	int PlayerDistance, C4TimerValue;
	int SoundDistance, SoundFadeTime;
	int ColorTVis[3], ColorTHide[3];
	int ColorCTVis[3], ColorCTHide[3];
	int FontColor[4], C4Timer;
	bool Enable, PlayerVisibleOnly;
	bool PlayerName, PlayerWeapon;
	bool PlayerBarrel, WorldC4;
	bool WorldItems, WorldNades;
	bool Sound, FontOutline;
};

struct ScreenInfoStruct
{
	char* FontColorString;
	int FPS, Time;
	int Copyright;
	int KreedzInfo;
	int ShowKeys;
	int FontColor[4];
	bool Enable;
	bool FontOutline;
};

struct MenuStruct
{
	char* BoxColorString;
	char* BoxOutlineColorString;
	char* BoxSelectColorString;
	char* TextColorString;
	int X, Y;
	int BoxWidth;
	int BoxHeight;
	int BoxColor[4];
	int BoxOutlineColor[4];
	int BoxSelectColor[4];
	int TextColor[3];
	BYTE Key;
};

struct FunctionsStruct
{
	bool Menu, ScreenInfo, ESP;
	bool Chams, NoFlash, Crosshair;
	bool Speed, BunnyHop;
	bool Weapons, Recoil;
	bool AutoPistol, FastZoom;
	bool GroundStrafe, TriggerWeapons;
};

struct MainStruct
{
	int Language;
	int PlayerValidCheck;
	int FontOutlineStyle;
	int AntiScreenTimer;
	bool AntiScreenEnable;
	BYTE ReloadKey, SaveKey;
	BYTE PanicAimBotKey;
	BYTE PanicVisualsKey;
	BYTE PanicMiscKey;
	BYTE PanicKey;
	BYTE AntiScreenKey;
};

class Vars
{
public:
	TWeaponsStruct TriggerWeapons[31];
	TriggerStruct Trigger;
	GroundStrafeStruct GroundStrafe;
	ChamsStruct Chams;
	FastZoomStruct FastZoom;
	AutoPistolStruct AutoPistol;
	RecoilStruct Recoil;
	OtherStruct Other;
	WeaponsStruct Weapons[31];
	AimStruct Aim;
	CrosshairStruct Crosshair;
	BunnyHopStruct BunnyHop;
	SpeedStruct Speed;
	NoFlashStruct NoFlash;
	ESPStruct ESP;
	ScreenInfoStruct ScreenInfo;
	MenuStruct Menu;
	FunctionsStruct Functions;
	MainStruct Main;
};

extern Vars g_Vars;