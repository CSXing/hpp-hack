#include "Files.h"

namespace Files
{
	char* BaseDir;

	std::string szDirFile ( const char *FileName )
	{
		std::string Path = BaseDir;

		return Path + FileName;
	}

	std::ofstream Inject, Info;

	namespace Read
	{
		void Functions ( )
		{
			std::string Path = szDirFile ( FUNCTIONS_PATH ).c_str ( );

			FILE_READ_INT ( g_Vars.Functions.Menu, "Visuals", "|Menu" );
			FILE_READ_INT ( g_Vars.Functions.ScreenInfo, "Visuals", "|ScreenInfo" );
			FILE_READ_INT ( g_Vars.Functions.ESP, "Visuals", "|ESP" );
			FILE_READ_INT ( g_Vars.Functions.Chams, "Visuals", "|Chams" );
			FILE_READ_INT ( g_Vars.Functions.NoFlash, "Visuals", "|NoFlash" );
			FILE_READ_INT ( g_Vars.Functions.Crosshair, "Visuals", "|Crosshair" );
			FILE_READ_INT ( g_Vars.Functions.Speed, "Misc", "|Speed" );
			FILE_READ_INT ( g_Vars.Functions.BunnyHop, "Misc", "|BunnyHop" );
			FILE_READ_INT ( g_Vars.Functions.GroundStrafe, "Misc", "|GroundStrafe" );
			FILE_READ_INT ( g_Vars.Functions.Weapons, "AimBot", "|Weapons" );
			FILE_READ_INT ( g_Vars.Functions.Recoil, "AimBot", "|Recoil" );
			FILE_READ_INT ( g_Vars.Functions.AutoPistol, "AimBot", "|AutoPistol" );
			FILE_READ_INT ( g_Vars.Functions.FastZoom, "AimBot", "|FastZoom" );
			FILE_READ_INT ( g_Vars.Functions.TriggerWeapons, "TriggerBot", "|Weapons" );
		}

		void Main ( )
		{
			std::string Path = szDirFile ( MAIN_PATH ).c_str ( );

			FILE_READ_CONVERT ( g_Vars.Main.Language, "Main", "|Language" );
			FILE_READ_KEY ( g_Vars.Main.ReloadKey, "Main", "|Reload.Key" );
			FILE_READ_KEY ( g_Vars.Main.SaveKey, "Main", "|Save.Key" );
			FILE_READ_KEY ( g_Vars.Main.PanicKey, "Main", "|Panic.Key" );
			FILE_READ_KEY ( g_Vars.Main.PanicAimBotKey, "Main", "|Panic.AimBot.Key" );
			FILE_READ_KEY ( g_Vars.Main.PanicVisualsKey, "Main", "|Panic.Visuals.Key" );
			FILE_READ_KEY ( g_Vars.Main.PanicMiscKey, "Main", "|Panic.Misc.Key" );
			FILE_READ_INT ( g_Vars.Main.PlayerValidCheck, "Main", "|Player.Valid.Check" );
			FILE_READ_INT ( g_Vars.Main.AntiScreenEnable, "Main", "|AntiScreen.Enable" );
			FILE_READ_INT ( g_Vars.Main.AntiScreenTimer, "Main", "|AntiScreen.Timer" );
			FILE_READ_KEY ( g_Vars.Main.AntiScreenKey, "Main", "|AntiScreen.Key" );
			FILE_READ_INT ( g_Vars.Main.FontOutlineStyle, "Main", "|Font.Outline.Style" );
		}

		void Menu ( )
		{
			std::string Path = szDirFile ( VISUALS_PATH ).c_str ( );

			FILE_READ_INT ( g_Vars.Menu.X, "Menu", "|Menu.X" );
			FILE_READ_INT ( g_Vars.Menu.Y, "Menu", "|Menu.Y" );
			FILE_READ_INT ( g_Vars.Menu.BoxHeight, "Menu", "|Menu.Box.Height" );
			FILE_READ_INT ( g_Vars.Menu.BoxWidth, "Menu", "|Menu.Box.Width" );
			FILE_READ_STRING ( g_Vars.Menu.BoxColorString, "Menu", "|Menu.Box.Color" );
			FILE_READ_STRING ( g_Vars.Menu.BoxOutlineColorString, "Menu", "|Menu.Box.Outline.Color" );
			FILE_READ_STRING ( g_Vars.Menu.BoxSelectColorString, "Menu", "|Menu.Box.Select.Color" );
			FILE_READ_STRING ( g_Vars.Menu.TextColorString, "Menu", "|Menu.Text.Color" );
			FILE_READ_KEY ( g_Vars.Menu.Key, "Menu", "|Menu.Key" );

			Parse ( g_Vars.Menu.BoxColorString, g_Vars.Menu.BoxColor, 4 );
			Parse ( g_Vars.Menu.BoxOutlineColorString, g_Vars.Menu.BoxOutlineColor, 4 );
			Parse ( g_Vars.Menu.BoxSelectColorString, g_Vars.Menu.BoxSelectColor, 4 );
			Parse ( g_Vars.Menu.TextColorString, g_Vars.Menu.TextColor, 3 );
		}

		void ScreenInfo ( )
		{
			std::string Path = szDirFile ( VISUALS_PATH ).c_str ( );

			FILE_READ_INT ( g_Vars.ScreenInfo.Enable, "ScreenInfo", "|ScreenInfo.Enable" );
			FILE_READ_INT ( g_Vars.ScreenInfo.FPS, "ScreenInfo", "|ScreenInfo.FPS" );
			FILE_READ_INT ( g_Vars.ScreenInfo.Copyright, "ScreenInfo", "|ScreenInfo.Copyright" );
			FILE_READ_INT ( g_Vars.ScreenInfo.Time, "ScreenInfo", "|ScreenInfo.Time" );
			FILE_READ_INT ( g_Vars.ScreenInfo.ShowKeys, "ScreenInfo", "|ScreenInfo.ShowKeys" );
			FILE_READ_INT ( g_Vars.ScreenInfo.KreedzInfo, "ScreenInfo", "|ScreenInfo.KreedzInfo" );
			FILE_READ_STRING ( g_Vars.ScreenInfo.FontColorString, "ScreenInfo", "|ScreenInfo.Font.Color" );
			FILE_READ_INT ( g_Vars.ScreenInfo.FontOutline, "ScreenInfo", "|ScreenInfo.Font.Outline" );

			Parse ( g_Vars.ScreenInfo.FontColorString, g_Vars.ScreenInfo.FontColor, 4 );
		}

		void ESP ( )
		{
			std::string Path = szDirFile ( VISUALS_PATH ).c_str ( );

			FILE_READ_INT ( g_Vars.ESP.Enable, "ESP", "|ESP.Enable" );
			FILE_READ_INT ( g_Vars.ESP.Player, "ESP", "|ESP.Player" );
			FILE_READ_INT ( g_Vars.ESP.PlayerVisibleOnly, "ESP", "|ESP.Player.VisibleOnly" );
			FILE_READ_INT ( g_Vars.ESP.PlayerBox, "ESP", "|ESP.Player.Box" );
			FILE_READ_INT ( g_Vars.ESP.PlayerBoxFilled, "ESP", "|ESP.Player.Box.Filled" );
			FILE_READ_STRING ( g_Vars.ESP.ColorTVisString, "ESP", "|ESP.Player.Box.T.Vis" );
			FILE_READ_STRING ( g_Vars.ESP.ColorTHideString, "ESP", "|ESP.Player.Box.T.Hide" );
			FILE_READ_STRING ( g_Vars.ESP.ColorCTVisString, "ESP", "|ESP.Player.Box.CT.Vis" );
			FILE_READ_STRING ( g_Vars.ESP.ColorCTHideString, "ESP", "|ESP.Player.Box.CT.Hide" );
			FILE_READ_INT ( g_Vars.ESP.PlayerName, "ESP", "|ESP.Player.Name" );
			FILE_READ_INT ( g_Vars.ESP.PlayerWeapon, "ESP", "|ESP.Player.Weapon" );
			FILE_READ_INT ( g_Vars.ESP.PlayerDistance, "ESP", "|ESP.Player.Distance" );
			FILE_READ_INT ( g_Vars.ESP.PlayerBarrel, "ESP", "|ESP.Player.Barrel" );
			FILE_READ_INT ( g_Vars.ESP.WorldC4, "ESP", "|ESP.World.C4" );
			FILE_READ_INT ( g_Vars.ESP.WorldItems, "ESP", "|ESP.World.Items" );
			FILE_READ_INT ( g_Vars.ESP.WorldNades, "ESP", "|ESP.World.Nades" );
			FILE_READ_INT ( g_Vars.ESP.C4Timer, "ESP", "|ESP.C4Timer" );
			FILE_READ_INT ( g_Vars.ESP.C4TimerValue, "ESP", "|ESP.C4Timer.Value" );
			FILE_READ_INT ( g_Vars.ESP.Sound, "ESP", "|ESP.Sound" );
			FILE_READ_INT ( g_Vars.ESP.SoundDistance, "ESP", "|ESP.Sound.Distance" );
			FILE_READ_INT ( g_Vars.ESP.SoundFadeTime, "ESP", "|ESP.Sound.FadeTime" );
			FILE_READ_STRING ( g_Vars.ESP.FontColorString, "ESP", "|ESP.Font.Color" );
			FILE_READ_INT ( g_Vars.ESP.FontOutline, "ESP", "|ESP.Font.Outline" );

			Parse ( g_Vars.ESP.ColorTVisString, g_Vars.ESP.ColorTVis, 3 );
			Parse ( g_Vars.ESP.ColorTHideString, g_Vars.ESP.ColorTHide, 3 );
			Parse ( g_Vars.ESP.ColorCTVisString, g_Vars.ESP.ColorCTVis, 3 );
			Parse ( g_Vars.ESP.ColorCTHideString, g_Vars.ESP.ColorCTHide, 3 );
			Parse ( g_Vars.ESP.FontColorString, g_Vars.ESP.FontColor, 4 );
		}

		void NoFlash ( )
		{
			std::string Path = szDirFile ( VISUALS_PATH ).c_str ( );

			FILE_READ_INT ( g_Vars.NoFlash.Enable, "NoFlash", "|NoFlash.Enable" );
			FILE_READ_INT ( g_Vars.NoFlash.FadeLimit, "NoFlash", "|NoFlash.Fade.Limit" );
			FILE_READ_INT ( g_Vars.NoFlash.FadeColorEnable, "NoFlash", "|NoFlash.Fade.Color.Enable" );
			FILE_READ_STRING ( g_Vars.NoFlash.FadeColorString, "NoFlash", "|NoFlash.Fade.Color" );
			FILE_READ_INT ( g_Vars.NoFlash.FadeColorRandom, "NoFlash", "|NoFlash.Fade.Color.Random" );
			FILE_READ_INT ( g_Vars.NoFlash.DrawFlashed, "NoFlash", "|NoFlash.DrawFlashed" );
			FILE_READ_INT ( g_Vars.NoFlash.FontOutline, "NoFlash", "|NoFlash.Font.Outline" );

			Parse ( g_Vars.NoFlash.FadeColorString, g_Vars.NoFlash.FadeColor, 3 );
		}

		void Speed ( )
		{
			std::string Path = szDirFile ( MISC_PATH ).c_str ( );

			FILE_READ_FLOAT ( g_Vars.Speed.Player, "Speed", "|Speed.Player" );
			FILE_READ_INT ( g_Vars.Speed.Engine, "Speed", "|Speed.Engine" );
			FILE_READ_FLOAT ( g_Vars.Speed.Boost, "Speed", "|Speed.Boost" );
			FILE_READ_KEY ( g_Vars.Speed.BoostKey, "Speed", "|Speed.Boost.Key" );
			FILE_READ_FLOAT ( g_Vars.Speed.Slowmo, "Speed", "|Speed.Slowmo" );
			FILE_READ_KEY ( g_Vars.Speed.SlowmoKey, "Speed", "|Speed.Slowmo.Key" );
			FILE_READ_INT ( g_Vars.Speed.Helper, "Speed", "|Speed.Helper" );
			FILE_READ_FLOAT ( g_Vars.Speed.HelperGround, "Speed", "|Speed.Helper.Ground" );
			FILE_READ_FLOAT ( g_Vars.Speed.HelperLadder, "Speed", "|Speed.Helper.Ladder" );
			FILE_READ_FLOAT ( g_Vars.Speed.HelperFly, "Speed", "|Speed.Helper.Fly" );
		}

		void BunnyHop ( )
		{
			std::string Path = szDirFile ( MISC_PATH ).c_str ( );

			FILE_READ_INT ( g_Vars.BunnyHop.NoSlowdown, "BunnyHop", "|BunnyHop.NoSlowdown" );
			FILE_READ_INT ( g_Vars.BunnyHop.ScrollEmulation, "BunnyHop", "|BunnyHop.Scroll.Emulation" );
			FILE_READ_CONVERT ( g_Vars.BunnyHop.ScrollDirection, "BunnyHop", "|BunnyHop.Scroll.Direction" );
			FILE_READ_STRING ( g_Vars.BunnyHop.ScrollDistanceString, "BunnyHop", "|BunnyHop.Scroll.Distance" );
			FILE_READ_INT ( g_Vars.BunnyHop.ScrollRandFails, "BunnyHop", "|BunnyHop.Scroll.RandFails" );
			FILE_READ_INT ( g_Vars.BunnyHop.OnLadder, "BunnyHop", "|BunnyHop.OnLadder" );
			FILE_READ_INT ( g_Vars.BunnyHop.Helper, "BunnyHop", "|BunnyHop.Helper" );
			FILE_READ_INT ( g_Vars.BunnyHop.HelperNoSlowdown, "BunnyHop", "|BunnyHop.Helper.NoSlowdown" );
			FILE_READ_INT ( g_Vars.BunnyHop.HelperIdealPercent, "BunnyHop", "|BunnyHop.Helper.IdealPercent" );
			FILE_READ_INT ( g_Vars.BunnyHop.StandUpAuto, "BunnyHop", "|BunnyHop.StandUp.Auto" );
			FILE_READ_INT ( g_Vars.BunnyHop.StandUpFallVelocity, "BunnyHop", "|BunnyHop.StandUp.FallVelocity" );
			FILE_READ_KEY ( g_Vars.BunnyHop.StandUpKey, "BunnyHop", "|BunnyHop.StandUp.Key" );
			FILE_READ_KEY ( g_Vars.BunnyHop.Key, "BunnyHop", "|BunnyHop.Key" );

			Parse ( g_Vars.BunnyHop.ScrollDistanceString, g_Vars.BunnyHop.ScrollDistance, 2 );
		}

		void Crosshair ( )
		{
			std::string Path = szDirFile ( VISUALS_PATH ).c_str ( );

			FILE_READ_INT ( g_Vars.Crosshair.Enable, "Crosshair", "|Crosshair.Enable" );
			FILE_READ_INT ( g_Vars.Crosshair.Dot, "Crosshair", "|Crosshair.Dot" );
			FILE_READ_INT ( g_Vars.Crosshair.Size, "Crosshair", "|Crosshair.Size" );
			FILE_READ_INT ( g_Vars.Crosshair.Gap, "Crosshair", "|Crosshair.Gap" );
			FILE_READ_INT ( g_Vars.Crosshair.Thickness, "Crosshair", "|Crosshair.Thickness" );
			FILE_READ_INT ( g_Vars.Crosshair.Dynamic, "Crosshair", "|Crosshair.Dynamic" );
			FILE_READ_FLOAT ( g_Vars.Crosshair.DynamicScale, "Crosshair", "|Crosshair.Dynamic.Scale" );
			FILE_READ_INT ( g_Vars.Crosshair.Outline, "Crosshair", "|Crosshair.Outline" );
			FILE_READ_INT ( g_Vars.Crosshair.Snipers, "Crosshair", "|Crosshair.Snipers" );
			FILE_READ_STRING ( g_Vars.Crosshair.ColorString, "Crosshair", "|Crosshair.Color" );

			Parse ( g_Vars.Crosshair.ColorString, g_Vars.Crosshair.Color, 4 );
		}

		void AimWeapons ( )
		{
			std::string Path = szDirFile ( AIMBOT_PATH ).c_str ( );

			FILE_READ_INT ( g_Vars.Aim.Enable, "Aim", "|Aim.Enable" );
			FILE_READ_INT ( g_Vars.Aim.Silent, "Aim", "|Aim.Silent" );
			FILE_READ_INT ( g_Vars.Aim.FriendlyFire, "Aim", "|Aim.FriendlyFire" );
			FILE_READ_INT ( g_Vars.Aim.VisibleCheck, "Aim", "|Aim.VisibleCheck" );
			FILE_READ_INT ( g_Vars.Aim.FlashCheck, "Aim", "|Aim.FlashCheck" );
			FILE_READ_INT ( g_Vars.Aim.FOVDistance, "Aim", "|Aim.FOV.Distance" );
			FILE_READ_INT ( g_Vars.Aim.KillDelay, "Aim", "|Aim.KillDelay" );

			for ( int Index = 1; Index <= 30; ++Index )
			{
				std::string Weapon;

				Utils::GetSection ( Index, Weapon );

				std::string Aim = "|" + Weapon + ".Aim";
				std::string BulletControl = "|" + Weapon + ".BulletControl";
				std::string Nearest = "|" + Weapon + ".HitBox.Nearest";
				std::string HitBox = "|" + Weapon + ".HitBox";
				std::string Prediction = "|" + Weapon + ".Prediction";
				std::string FOV = "|" + Weapon + ".FOV";
				std::string Smooth = "|" + Weapon + ".Smooth";
				std::string Delay = "|" + Weapon + ".Delay";
				std::string DelayType = "|" + Weapon + ".Delay.Type";
				std::string Recoil = "|" + Weapon + ".Recoil";
				std::string RecoilPrediction = "|" + Weapon + ".Recoil.Prediction";
				std::string FOVRecoil = "|" + Weapon + ".Recoil.FOV";
				std::string SmoothRecoil = "|" + Weapon + ".Recoil.Smooth";

				FILE_READ_INT ( g_Vars.Weapons[Index].Aim, "Weapons", ( char* )Aim.c_str ( ) );
				FILE_READ_STRING ( g_Vars.Weapons[Index].BulletControlString, "Weapons", ( char* )BulletControl.c_str ( ) );
				FILE_READ_INT ( g_Vars.Weapons[Index].HitBoxNearest, "Weapons", ( char* )Nearest.c_str ( ) );
				FILE_READ_INT ( g_Vars.Weapons[Index].HitBox, "Weapons", ( char* )HitBox.c_str ( ) );
				FILE_READ_FLOAT ( g_Vars.Weapons[Index].Prediction, "Weapons", ( char* )Prediction.c_str ( ) );
				FILE_READ_FLOAT ( g_Vars.Weapons[Index].FOV, "Weapons", ( char* )FOV.c_str ( ) );
				FILE_READ_FLOAT ( g_Vars.Weapons[Index].Smooth, "Weapons", ( char* )Smooth.c_str ( ) );
				FILE_READ_INT ( g_Vars.Weapons[Index].Delay, "Weapons", ( char* )Delay.c_str ( ) );
				FILE_READ_INT ( g_Vars.Weapons[Index].DelayType, "Weapons", ( char* )DelayType.c_str ( ) );
				FILE_READ_FLOAT ( g_Vars.Weapons[Index].Recoil, "Weapons", ( char* )Recoil.c_str ( ) );
				FILE_READ_FLOAT ( g_Vars.Weapons[Index].RecoilPrediction, "Weapons", ( char* )RecoilPrediction.c_str ( ) );
				FILE_READ_FLOAT ( g_Vars.Weapons[Index].RecoilFOV, "Weapons", ( char* )FOVRecoil.c_str ( ) );
				FILE_READ_FLOAT ( g_Vars.Weapons[Index].RecoilSmooth, "Weapons", ( char* )SmoothRecoil.c_str ( ) );

				Parse ( g_Vars.Weapons[Index].BulletControlString, g_Vars.Weapons[Index].BulletControl, 2 );
			}
		}

		void Other ( )
		{
			std::string Path = szDirFile ( VISUALS_PATH ).c_str ( );

			FILE_READ_INT ( g_Vars.Other.DrawAimSpot, "Other", "|Draw.Aim.Spot" );
			FILE_READ_INT ( g_Vars.Other.DrawAimFOV, "Other", "|Draw.Aim.FOV" );
			FILE_READ_INT ( g_Vars.Other.DrawPunch, "Other", "|Draw.Punch" );
			FILE_READ_INT ( g_Vars.Other.DrawSpread, "Other", "|Draw.Spread" );
			FILE_READ_INT ( g_Vars.Other.StatusAimBot, "Other", "|Status.AimBot" );
			FILE_READ_INT ( g_Vars.Other.StatusTriggerBot, "Other", "|Status.TriggerBot" );
			FILE_READ_INT ( g_Vars.Other.RemoveSmoke, "Other", "|Remove.Smoke" );
			FILE_READ_STRING ( g_Vars.Other.FontColorString, "Other", "|Font.Color" );
			FILE_READ_INT ( g_Vars.Other.FontOutline, "Other", "|Font.Outline" );

			Parse ( g_Vars.Other.FontColorString, g_Vars.Other.FontColor, 4 );
		}

		void Recoil ( )
		{
			std::string Path = szDirFile ( AIMBOT_PATH ).c_str ( );

			FILE_READ_INT ( g_Vars.Recoil.Enable, "Recoil", "|Recoil.Enable" );
			FILE_READ_FLOAT ( g_Vars.Recoil.X, "Recoil", "|Recoil.X" );
			FILE_READ_FLOAT ( g_Vars.Recoil.Y, "Recoil", "|Recoil.Y" );
			FILE_READ_FLOAT ( g_Vars.Recoil.Smooth, "Recoil", "|Recoil.Smooth" );
			FILE_READ_INT ( g_Vars.Recoil.BulletStart, "Recoil", "|Recoil.BulletStart" );
		}

		void AutoPistol ( )
		{
			std::string Path = szDirFile ( AIMBOT_PATH ).c_str ( );

			FILE_READ_INT ( g_Vars.AutoPistol.Enable, "AutoPistol", "|AutoPistol.Enable" );
			FILE_READ_INT ( g_Vars.AutoPistol.Delay, "AutoPistol", "|AutoPistol.Delay" );
		}

		void FastZoom ( )
		{
			std::string Path = szDirFile ( AIMBOT_PATH ).c_str ( );

			FILE_READ_INT ( g_Vars.FastZoom.Enable, "FastZoom", "|FastZoom.Enable" );
			FILE_READ_INT ( g_Vars.FastZoom.Delay, "FastZoom", "|FastZoom.Delay" );
			FILE_READ_INT ( g_Vars.FastZoom.QuickSwitch, "FastZoom", "|FastZoom.QuickSwitch" );
		}

		void Chams ( )
		{
			std::string Path = szDirFile ( VISUALS_PATH ).c_str ( );

			FILE_READ_INT ( g_Vars.Chams.Enable, "Chams", "|Chams.Enable" );
			FILE_READ_INT ( g_Vars.Chams.Player, "Chams", "|Chams.Player" );
			FILE_READ_INT ( g_Vars.Chams.PlayerVisibleOnly, "Chams", "|Chams.Player.VisibleOnly" );
			FILE_READ_INT ( g_Vars.Chams.PlayerRenderType, "Chams", "|Chams.Player.RenderType" );
			FILE_READ_STRING ( g_Vars.Chams.ColorTVisString, "Chams", "|Chams.Player.T.Vis" );
			FILE_READ_STRING ( g_Vars.Chams.ColorTHideString, "Chams", "|Chams.Player.T.Hide" );
			FILE_READ_STRING ( g_Vars.Chams.ColorCTVisString, "Chams", "|Chams.Player.CT.Vis" );
			FILE_READ_STRING ( g_Vars.Chams.ColorCTHideString, "Chams", "|Chams.Player.CT.Hide" );
			FILE_READ_INT ( g_Vars.Chams.Weapon, "Chams", "|Chams.Weapon" );
			FILE_READ_INT ( g_Vars.Chams.WeaponVisibleOnly, "Chams", "|Chams.Weapon.VisibleOnly" );
			FILE_READ_INT ( g_Vars.Chams.WeaponRenderType, "Chams", "|Chams.Weapon.RenderType" );
			FILE_READ_STRING ( g_Vars.Chams.WeaponColorVisString, "Chams", "|Chams.Weapon.Color.Vis" );
			FILE_READ_STRING ( g_Vars.Chams.WeaponColorHideString, "Chams", "|Chams.Weapon.Color.Hide" );
			FILE_READ_INT ( g_Vars.Chams.Hands, "Chams", "|Chams.Hands" );
			FILE_READ_INT ( g_Vars.Chams.HandsRenderType, "Chams", "|Chams.Hands.RenderType" );
			FILE_READ_STRING ( g_Vars.Chams.HandsColorString, "Chams", "|Chams.Hands.Color" );

			Parse ( g_Vars.Chams.ColorTVisString, g_Vars.Chams.ColorTVis, 3 );
			Parse ( g_Vars.Chams.ColorTHideString, g_Vars.Chams.ColorTHide, 3 );
			Parse ( g_Vars.Chams.ColorCTVisString, g_Vars.Chams.ColorCTVis, 3 );
			Parse ( g_Vars.Chams.ColorCTHideString, g_Vars.Chams.ColorCTHide, 3 );
			Parse ( g_Vars.Chams.WeaponColorVisString, g_Vars.Chams.WeaponColorVis, 3 );
			Parse ( g_Vars.Chams.WeaponColorHideString, g_Vars.Chams.WeaponColorHide, 3 );
			Parse ( g_Vars.Chams.HandsColorString, g_Vars.Chams.HandsColor, 3 );
		}

		void GroundStrafe ( )
		{
			std::string Path = szDirFile ( MISC_PATH ).c_str ( );

			FILE_READ_INT ( g_Vars.GroundStrafe.ScrollEmulation, "GroundStrafe", "|GroundStrafe.Scroll.Emulation" );
			FILE_READ_CONVERT ( g_Vars.GroundStrafe.ScrollDirection, "GroundStrafe", "|GroundStrafe.Scroll.Direction" );
			FILE_READ_STRING ( g_Vars.GroundStrafe.ScrollDistanceString, "GroundStrafe", "|GroundStrafe.Scroll.Distance" );
			FILE_READ_STRING ( g_Vars.GroundStrafe.ScrollCountString, "GroundStrafe", "|GroundStrafe.Scroll.Count" );
			FILE_READ_FLOAT ( g_Vars.GroundStrafe.SlowdownScale, "GroundStrafe", "|GroundStrafe.Slowdown.Scale" );
			FILE_READ_FLOAT ( g_Vars.GroundStrafe.SlowdownAngle, "GroundStrafe", "|GroundStrafe.Slowdown.Angle" );
			FILE_READ_INT ( g_Vars.GroundStrafe.FallRun, "GroundStrafe", "|GroundStrafe.FallRun" );
			FILE_READ_INT ( g_Vars.GroundStrafe.Helper, "GroundStrafe", "|GroundStrafe.Helper" );
			FILE_READ_INT ( g_Vars.GroundStrafe.StandUpFallVelocity, "GroundStrafe", "|GroundStrafe.StandUp.FallVelocity" );
			FILE_READ_KEY ( g_Vars.GroundStrafe.StandUpKey, "GroundStrafe", "|GroundStrafe.StandUp.Key" );
			FILE_READ_KEY ( g_Vars.GroundStrafe.Key, "GroundStrafe", "|GroundStrafe.Key" );

			Parse ( g_Vars.GroundStrafe.ScrollDistanceString, g_Vars.GroundStrafe.ScrollDistance, 2 );
			Parse ( g_Vars.GroundStrafe.ScrollCountString, g_Vars.GroundStrafe.ScrollCount, 2 );
		}

		void TriggerWeapons ( )
		{
			std::string Path = szDirFile ( TRIGGERBOT_PATH ).c_str ( );

			FILE_READ_INT ( g_Vars.Trigger.Enable, "Trigger", "|Trigger.Enable" );
			FILE_READ_INT ( g_Vars.Trigger.FriendlyFire, "Trigger", "|Trigger.FriendlyFire" );
			FILE_READ_INT ( g_Vars.Trigger.VisibleCheck, "Trigger", "|Trigger.VisibleCheck" );
			FILE_READ_INT ( g_Vars.Trigger.SnipersOnlyInZoom, "Trigger", "|Trigger.Snipers.OnlyInZoom" );
			FILE_READ_KEY ( g_Vars.Trigger.SwitchKey, "Trigger", "|Trigger.Switch.Key" );
			FILE_READ_KEY ( g_Vars.Trigger.Key, "Trigger", "|Trigger.Key" );

			for ( int Index = 1; Index <= 30; ++Index )
			{
				std::string Weapon;

				Utils::GetSection ( Index, Weapon );

				std::string Trigger = "|" + Weapon + ".Trigger";
				std::string OnlyHead = "|" + Weapon + ".OnlyHead";
				std::string ProSpread = "|" + Weapon + ".ProSpread";

				FILE_READ_INT ( g_Vars.TriggerWeapons[Index].Trigger, "Weapons", ( char* )Trigger.c_str ( ) );
				FILE_READ_INT ( g_Vars.TriggerWeapons[Index].OnlyHead, "Weapons", ( char* )OnlyHead.c_str ( ) );
				FILE_READ_INT ( g_Vars.TriggerWeapons[Index].ProSpread, "Weapons", ( char* )ProSpread.c_str ( ) );
			}
		}
	}

	namespace Write
	{
		void Main ( )
		{
			std::string Path = szDirFile ( MAIN_PATH ).c_str ( );

			FILE_WRITE_LANG ( g_Vars.Main.Language, "Main", "|Language" );
			FILE_WRITE_INT ( g_Vars.Main.PlayerValidCheck, "Main", "|Player.Valid.Check" );
			FILE_WRITE_INT ( g_Vars.Main.AntiScreenEnable, "Main", "|AntiScreen.Enable" );
			FILE_WRITE_INT ( g_Vars.Main.AntiScreenTimer, "Main", "|AntiScreen.Timer" );
			FILE_WRITE_INT ( g_Vars.Main.FontOutlineStyle, "Main", "|Font.Outline.Style" );
			FILE_WRITE_KEY ( g_Vars.Main.ReloadKey, "Main", "|Reload.Key" );
			FILE_WRITE_KEY ( g_Vars.Main.SaveKey, "Main", "|Save.Key" );
			FILE_WRITE_KEY ( g_Vars.Main.AntiScreenKey, "Main", "|AntiScreen.Key" );
			FILE_WRITE_KEY ( g_Vars.Main.PanicKey, "Main", "|Panic.Key" );
			FILE_WRITE_KEY ( g_Vars.Main.PanicAimBotKey, "Main", "|Panic.AimBot.Key" );
			FILE_WRITE_KEY ( g_Vars.Main.PanicVisualsKey, "Main", "|Panic.Visuals.Key" );
			FILE_WRITE_KEY ( g_Vars.Main.PanicMiscKey, "Main", "|Panic.Misc.Key" );
			FILE_WRITE_KEY ( g_Vars.Main.AntiScreenKey, "Main", "|AntiScreen.Key" );
		}

		void Menu ( )
		{
			std::string Path = szDirFile ( VISUALS_PATH ).c_str ( );

			FILE_WRITE_INT ( g_Vars.Menu.X, "Menu", "|Menu.x" );
			FILE_WRITE_INT ( g_Vars.Menu.Y, "Menu", "|Menu.y" );
			FILE_WRITE_INT ( g_Vars.Menu.BoxHeight, "Menu", "|Menu.Box.Height" );
			FILE_WRITE_INT ( g_Vars.Menu.BoxWidth, "Menu", "|Menu.Box.Width" );
			FILE_WRITE_RGBA ( g_Vars.Menu.BoxColor[0], g_Vars.Menu.BoxColor[1], g_Vars.Menu.BoxColor[2], g_Vars.Menu.BoxColor[3], "Menu", "|Menu.Box.Color" );

			FILE_WRITE_RGBA ( g_Vars.Menu.BoxOutlineColor[0], g_Vars.Menu.BoxOutlineColor[1],
				g_Vars.Menu.BoxOutlineColor[2], g_Vars.Menu.BoxOutlineColor[3], "Menu", "|Menu.Box.Outline.Color" );

			FILE_WRITE_RGBA ( g_Vars.Menu.BoxSelectColor[0], g_Vars.Menu.BoxSelectColor[1],
				g_Vars.Menu.BoxSelectColor[2], g_Vars.Menu.BoxSelectColor[3], "Menu", "|Menu.Box.Select.Color" );

			FILE_WRITE_RGB ( g_Vars.Menu.TextColor[0], g_Vars.Menu.TextColor[1], g_Vars.Menu.TextColor[2], "Menu", "|Menu.Text.Color" );
			FILE_WRITE_KEY ( g_Vars.Menu.Key, "Menu", "|Menu.Key" );
		}

		void ScreenInfo ( )
		{
			std::string Path = szDirFile ( VISUALS_PATH ).c_str ( );

			FILE_WRITE_INT ( g_Vars.ScreenInfo.Enable, "ScreenInfo", "|ScreenInfo.Enable" );
			FILE_WRITE_INT ( g_Vars.ScreenInfo.FPS, "ScreenInfo", "|ScreenInfo.FPS" );
			FILE_WRITE_INT ( g_Vars.ScreenInfo.Copyright, "ScreenInfo", "|ScreenInfo.Copyright" );
			FILE_WRITE_INT ( g_Vars.ScreenInfo.Time, "ScreenInfo", "|ScreenInfo.Time" );
			FILE_WRITE_INT ( g_Vars.ScreenInfo.ShowKeys, "ScreenInfo", "|ScreenInfo.ShowKeys" );
			FILE_WRITE_INT ( g_Vars.ScreenInfo.KreedzInfo, "ScreenInfo", "|ScreenInfo.KreedzInfo" );

			FILE_WRITE_RGBA ( g_Vars.ScreenInfo.FontColor[0], g_Vars.ScreenInfo.FontColor[1],
				g_Vars.ScreenInfo.FontColor[2], g_Vars.ScreenInfo.FontColor[3], "ScreenInfo", "|ScreenInfo.Font.Color" );

			FILE_WRITE_INT ( g_Vars.ScreenInfo.FontOutline, "ScreenInfo", "|ScreenInfo.Font.Outline" );
		}

		void ESP ( )
		{
			std::string Path = szDirFile ( VISUALS_PATH ).c_str ( );

			FILE_WRITE_INT ( g_Vars.ESP.Enable, "ESP", "|ESP.Enable" );
			FILE_WRITE_INT ( g_Vars.ESP.Player, "ESP", "|ESP.Player" );
			FILE_WRITE_INT ( g_Vars.ESP.PlayerVisibleOnly, "ESP", "|ESP.Player.VisibleOnly" );
			FILE_WRITE_INT ( g_Vars.ESP.PlayerBox, "ESP", "|ESP.Player.Box" );
			FILE_WRITE_INT ( g_Vars.ESP.PlayerBoxFilled, "ESP", "|ESP.Player.Box.Filled" );
			FILE_WRITE_RGB ( g_Vars.ESP.ColorTVis[0], g_Vars.ESP.ColorTVis[1], g_Vars.ESP.ColorTVis[2], "ESP", "|ESP.Player.Box.T.Vis" );
			FILE_WRITE_RGB ( g_Vars.ESP.ColorTHide[0], g_Vars.ESP.ColorTHide[1], g_Vars.ESP.ColorTHide[2], "ESP", "|ESP.Player.Box.T.Hide" );
			FILE_WRITE_RGB ( g_Vars.ESP.ColorCTVis[0], g_Vars.ESP.ColorCTVis[1], g_Vars.ESP.ColorCTVis[2], "ESP", "|ESP.Player.Box.CT.Vis" );
			FILE_WRITE_RGB ( g_Vars.ESP.ColorCTHide[0], g_Vars.ESP.ColorCTHide[1], g_Vars.ESP.ColorCTHide[2], "ESP", "|ESP.Player.Box.CT.Hide" );
			FILE_WRITE_INT ( g_Vars.ESP.PlayerName, "ESP", "|ESP.Player.Name" );
			FILE_WRITE_INT ( g_Vars.ESP.PlayerWeapon, "ESP", "|ESP.Player.Weapon" );
			FILE_WRITE_INT ( g_Vars.ESP.PlayerDistance, "ESP", "|ESP.Player.Distance" );
			FILE_WRITE_INT ( g_Vars.ESP.PlayerBarrel, "ESP", "|ESP.Player.Barrel" );
			FILE_WRITE_INT ( g_Vars.ESP.WorldC4, "ESP", "|ESP.World.C4" );
			FILE_WRITE_INT ( g_Vars.ESP.WorldItems, "ESP", "|ESP.World.Items" );
			FILE_WRITE_INT ( g_Vars.ESP.WorldNades, "ESP", "|ESP.World.Nades" );
			FILE_WRITE_INT ( g_Vars.ESP.C4Timer, "ESP", "|ESP.C4Timer" );
			FILE_WRITE_INT ( g_Vars.ESP.C4TimerValue, "ESP", "|ESP.C4Timer.Value" );
			FILE_WRITE_INT ( g_Vars.ESP.Sound, "ESP", "|ESP.Sound" );
			FILE_WRITE_INT ( g_Vars.ESP.SoundDistance, "ESP", "|ESP.Sound.Distance" );
			FILE_WRITE_INT ( g_Vars.ESP.SoundFadeTime, "ESP", "|ESP.Sound.FadeTime" );
			FILE_WRITE_RGBA ( g_Vars.ESP.FontColor[0], g_Vars.ESP.FontColor[1], g_Vars.ESP.FontColor[2], g_Vars.ESP.FontColor[3], "ESP", "|ESP.Font.Color" );
			FILE_WRITE_INT ( g_Vars.ESP.FontOutline, "ESP", "|ESP.Font.Outline" );
		}

		void NoFlash ( )
		{
			std::string Path = szDirFile ( VISUALS_PATH ).c_str ( );

			FILE_WRITE_INT ( g_Vars.NoFlash.Enable, "NoFlash", "|NoFlash.Enable" );
			FILE_WRITE_INT ( g_Vars.NoFlash.FadeLimit, "NoFlash", "|NoFlash.Fade.Limit" );
			FILE_WRITE_INT ( g_Vars.NoFlash.FadeColorEnable, "NoFlash", "|NoFlash.Fade.Color.Enable" );
			FILE_WRITE_RGB ( g_Vars.NoFlash.FadeColor[0], g_Vars.NoFlash.FadeColor[1], g_Vars.NoFlash.FadeColor[2], "NoFlash", "|NoFlash.Fade.Color" );
			FILE_WRITE_INT ( g_Vars.NoFlash.FadeColorRandom, "NoFlash", "|NoFlash.Fade.Color.Random" );
			FILE_WRITE_INT ( g_Vars.NoFlash.DrawFlashed, "NoFlash", "|NoFlash.DrawFlashed" );
			FILE_WRITE_INT ( g_Vars.NoFlash.FontOutline, "NoFlash", "|NoFlash.Font.Outline" );
		}

		void Speed ( )
		{
			std::string Path = szDirFile ( MISC_PATH ).c_str ( );

			FILE_WRITE_FLOAT ( g_Vars.Speed.Player, "Speed", "|Speed.Player" );
			FILE_WRITE_INT ( g_Vars.Speed.Engine, "Speed", "|Speed.Engine" );
			FILE_WRITE_FLOAT ( g_Vars.Speed.Boost, "Speed", "|Speed.Boost" );
			FILE_WRITE_FLOAT ( g_Vars.Speed.Slowmo, "Speed", "|Speed.Slowmo" );
			FILE_WRITE_INT ( g_Vars.Speed.Helper, "Speed", "|Speed.Helper" );
			FILE_WRITE_FLOAT ( g_Vars.Speed.HelperGround, "Speed", "|Speed.Helper.Ground" );
			FILE_WRITE_FLOAT ( g_Vars.Speed.HelperLadder, "Speed", "|Speed.Helper.Ladder" );
			FILE_WRITE_FLOAT ( g_Vars.Speed.HelperFly, "Speed", "|Speed.Helper.Fly" );
			FILE_WRITE_KEY ( g_Vars.Speed.BoostKey, "Speed", "|Speed.Boost.Key" );
			FILE_WRITE_KEY ( g_Vars.Speed.SlowmoKey, "Speed", "|Speed.Slowmo.Key" );
		}

		void BunnyHop ( )
		{
			std::string Path = szDirFile ( MISC_PATH ).c_str ( );

			FILE_WRITE_INT ( g_Vars.BunnyHop.NoSlowdown, "BunnyHop", "|BunnyHop.NoSlowdown" );
			FILE_WRITE_INT ( g_Vars.BunnyHop.ScrollEmulation, "BunnyHop", "|BunnyHop.Scroll.Emulation" );
			FILE_WRITE_DIR ( g_Vars.BunnyHop.ScrollDirection, "BunnyHop", "|BunnyHop.Scroll.Direction" );
			FILE_WRITE_FLOAT_2 ( g_Vars.BunnyHop.ScrollDistance[0], g_Vars.BunnyHop.ScrollDistance[1], "BunnyHop", "|BunnyHop.Scroll.Distance" );
			FILE_WRITE_INT ( g_Vars.BunnyHop.ScrollRandFails, "BunnyHop", "|BunnyHop.Scroll.RandFails" );
			FILE_WRITE_INT ( g_Vars.BunnyHop.OnLadder, "BunnyHop", "|BunnyHop.OnLadder" );
			FILE_WRITE_INT ( g_Vars.BunnyHop.Helper, "BunnyHop", "|BunnyHop.Helper" );
			FILE_WRITE_INT ( g_Vars.BunnyHop.HelperNoSlowdown, "BunnyHop", "|BunnyHop.Helper.NoSlowdown" );
			FILE_WRITE_INT ( g_Vars.BunnyHop.HelperIdealPercent, "BunnyHop", "|BunnyHop.Helper.IdealPercent" );
			FILE_WRITE_INT ( g_Vars.BunnyHop.StandUpAuto, "BunnyHop", "|BunnyHop.StandUp.Auto" );
			FILE_WRITE_INT ( g_Vars.BunnyHop.StandUpFallVelocity, "BunnyHop", "|BunnyHop.StandUp.FallVelocity" );
			FILE_WRITE_KEY ( g_Vars.BunnyHop.StandUpKey, "BunnyHop", "|BunnyHop.StandUp.Key" );
			FILE_WRITE_KEY ( g_Vars.BunnyHop.Key, "BunnyHop", "|BunnyHop.Key" );
		}

		void Crosshair ( )
		{
			std::string Path = szDirFile ( VISUALS_PATH ).c_str ( );

			FILE_WRITE_INT ( g_Vars.Crosshair.Enable, "Crosshair", "|Crosshair.Enable" );
			FILE_WRITE_INT ( g_Vars.Crosshair.Dot, "Crosshair", "|Crosshair.Dot" );
			FILE_WRITE_INT ( g_Vars.Crosshair.Size, "Crosshair", "|Crosshair.Size" );
			FILE_WRITE_INT ( g_Vars.Crosshair.Gap, "Crosshair", "|Crosshair.Gap" );
			FILE_WRITE_INT ( g_Vars.Crosshair.Thickness, "Crosshair", "|Crosshair.Thickness" );
			FILE_WRITE_INT ( g_Vars.Crosshair.Dynamic, "Crosshair", "|Crosshair.Dynamic" );
			FILE_WRITE_FLOAT ( g_Vars.Crosshair.DynamicScale, "Crosshair", "|Crosshair.Dynamic.Scale" );
			FILE_WRITE_INT ( g_Vars.Crosshair.Outline, "Crosshair", "|Crosshair.Outline" );
			FILE_WRITE_INT ( g_Vars.Crosshair.Snipers, "Crosshair", "|Crosshair.Snipers" );

			FILE_WRITE_RGBA ( g_Vars.Crosshair.Color[0], g_Vars.Crosshair.Color[1], g_Vars.Crosshair.Color[2],
				g_Vars.Crosshair.Color[3], "Crosshair", "|Crosshair.Color" );
		}

		void AimWeapons ( )
		{
			std::string Path = szDirFile ( AIMBOT_PATH ).c_str ( );

			FILE_WRITE_INT ( g_Vars.Aim.Enable, "Aim", "|Aim.Enable" );
			FILE_WRITE_INT ( g_Vars.Aim.Silent, "Aim", "|Aim.Silent" );
			FILE_WRITE_INT ( g_Vars.Aim.FriendlyFire, "Aim", "|Aim.FriendlyFire" );
			FILE_WRITE_INT ( g_Vars.Aim.VisibleCheck, "Aim", "|Aim.VisibleCheck" );
			FILE_WRITE_INT ( g_Vars.Aim.FlashCheck, "Aim", "|Aim.FlashCheck" );
			FILE_WRITE_INT ( g_Vars.Aim.FOVDistance, "Aim", "|Aim.FOV.Distance" );
			FILE_WRITE_INT ( g_Vars.Aim.KillDelay, "Aim", "|Aim.KillDelay" );

			for ( int Index = 1; Index <= 30; ++Index )
			{
				std::string Weapon;

				Utils::GetSection ( Index, Weapon );

				std::string Aim = "|" + Weapon + ".Aim";
				std::string BulletControl = "|" + Weapon + ".BulletControl";
				std::string Nearest = "|" + Weapon + ".HitBox.Nearest";
				std::string HitBox = "|" + Weapon + ".HitBox";
				std::string Prediction = "|" + Weapon + ".Prediction";
				std::string FOV = "|" + Weapon + ".FOV";
				std::string Smooth = "|" + Weapon + ".Smooth";
				std::string Delay = "|" + Weapon + ".Delay";
				std::string DelayType = "|" + Weapon + ".Delay.Type";
				std::string Recoil = "|" + Weapon + ".Recoil";
				std::string RecoilPrediction = "|" + Weapon + ".Recoil.Prediction";
				std::string FOVRecoil = "|" + Weapon + ".Recoil.FOV";
				std::string SmoothRecoil = "|" + Weapon + ".Recoil.Smooth";

				FILE_WRITE_INT ( g_Vars.Weapons[Index].Aim, "Weapons", ( char* )Aim.c_str ( ) );
				FILE_WRITE_INT_2 ( g_Vars.Weapons[Index].BulletControl[0], g_Vars.Weapons[Index].BulletControl[1], "Weapons", ( char* )BulletControl.c_str ( ) );
				FILE_WRITE_INT ( g_Vars.Weapons[Index].HitBoxNearest, "Weapons", ( char* )Nearest.c_str ( ) );
				FILE_WRITE_INT ( g_Vars.Weapons[Index].HitBox, "Weapons", ( char* )HitBox.c_str ( ) );
				FILE_WRITE_FLOAT ( g_Vars.Weapons[Index].Prediction, "Weapons", ( char* )Prediction.c_str ( ) );
				FILE_WRITE_FLOAT ( g_Vars.Weapons[Index].FOV, "Weapons", ( char* )FOV.c_str ( ) );
				FILE_WRITE_FLOAT ( g_Vars.Weapons[Index].Smooth, "Weapons", ( char* )Smooth.c_str ( ) );
				FILE_WRITE_INT ( g_Vars.Weapons[Index].Delay, "Weapons", ( char* )Delay.c_str ( ) );
				FILE_WRITE_INT ( g_Vars.Weapons[Index].DelayType, "Weapons", ( char* )DelayType.c_str ( ) );
				FILE_WRITE_FLOAT ( g_Vars.Weapons[Index].Recoil, "Weapons", ( char* )Recoil.c_str ( ) );
				FILE_WRITE_FLOAT ( g_Vars.Weapons[Index].RecoilPrediction, "Weapons", ( char* )RecoilPrediction.c_str ( ) );
				FILE_WRITE_FLOAT ( g_Vars.Weapons[Index].RecoilFOV, "Weapons", ( char* )FOVRecoil.c_str ( ) );
				FILE_WRITE_FLOAT ( g_Vars.Weapons[Index].RecoilSmooth, "Weapons", ( char* )SmoothRecoil.c_str ( ) );
			}
		}

		void Other ( )
		{
			std::string Path = szDirFile ( VISUALS_PATH ).c_str ( );

			FILE_WRITE_INT ( g_Vars.Other.DrawAimSpot, "Other", "|Draw.Aim.Spot" );
			FILE_WRITE_INT ( g_Vars.Other.DrawAimFOV, "Other", "|Draw.Aim.FOV" );
			FILE_WRITE_INT ( g_Vars.Other.DrawPunch, "Other", "|Draw.Punch" );
			FILE_WRITE_INT ( g_Vars.Other.DrawSpread, "Other", "|Draw.Spread" );
			FILE_WRITE_INT ( g_Vars.Other.StatusAimBot, "Other", "|Status.AimBot" );
			FILE_WRITE_INT ( g_Vars.Other.StatusTriggerBot, "Other", "|Status.TriggerBot" );
			FILE_WRITE_INT ( g_Vars.Other.RemoveSmoke, "Other", "|Remove.Smoke" );

			FILE_WRITE_RGBA ( g_Vars.Other.FontColor[0], g_Vars.Other.FontColor[1],
				g_Vars.Other.FontColor[2], g_Vars.Other.FontColor[3], "Other", "|Font.Color" );

			FILE_WRITE_INT ( g_Vars.Other.FontOutline, "Other", "|Font.Outline" );
		}

		void Recoil ( )
		{
			std::string Path = szDirFile ( AIMBOT_PATH ).c_str ( );

			FILE_WRITE_INT ( g_Vars.Recoil.Enable, "Recoil", "|Recoil.Enable" );
			FILE_WRITE_FLOAT ( g_Vars.Recoil.X, "Recoil", "|Recoil.X" );
			FILE_WRITE_FLOAT ( g_Vars.Recoil.Y, "Recoil", "|Recoil.Y" );
			FILE_WRITE_FLOAT ( g_Vars.Recoil.Smooth, "Recoil", "|Recoil.Smooth" );
			FILE_WRITE_INT ( g_Vars.Recoil.BulletStart, "Recoil", "|Recoil.BulletStart" );
		}

		void AutoPistol ( )
		{
			std::string Path = szDirFile ( AIMBOT_PATH ).c_str ( );

			FILE_WRITE_INT ( g_Vars.AutoPistol.Enable, "AutoPistol", "|AutoPistol.Enable" );
			FILE_WRITE_INT ( g_Vars.AutoPistol.Delay, "AutoPistol", "|AutoPistol.Delay" );
		}

		void FastZoom ( )
		{
			std::string Path = szDirFile ( AIMBOT_PATH ).c_str ( );

			FILE_WRITE_INT ( g_Vars.FastZoom.Enable, "FastZoom", "|FastZoom.Enable" );
			FILE_WRITE_INT ( g_Vars.FastZoom.Delay, "FastZoom", "|FastZoom.Delay" );
			FILE_WRITE_INT ( g_Vars.FastZoom.QuickSwitch, "FastZoom", "|FastZoom.QuickSwitch" );
		}

		void Chams ( )
		{
			std::string Path = szDirFile ( VISUALS_PATH ).c_str ( );

			FILE_WRITE_INT ( g_Vars.Chams.Enable, "Chams", "|Chams.Enable" );
			FILE_WRITE_INT ( g_Vars.Chams.Player, "Chams", "|Chams.Player" );
			FILE_WRITE_INT ( g_Vars.Chams.PlayerVisibleOnly, "Chams", "|Chams.Player.VisibleOnly" );
			FILE_WRITE_INT ( g_Vars.Chams.PlayerRenderType, "Chams", "|Chams.Player.RenderType" );
			FILE_WRITE_RGB ( g_Vars.Chams.ColorTVis[0], g_Vars.Chams.ColorTVis[1], g_Vars.Chams.ColorTVis[2], "Chams", "|Chams.Player.T.Vis" );
			FILE_WRITE_RGB ( g_Vars.Chams.ColorTHide[0], g_Vars.Chams.ColorTHide[1], g_Vars.Chams.ColorTHide[2], "Chams", "|Chams.Player.T.Hide" );
			FILE_WRITE_RGB ( g_Vars.Chams.ColorCTVis[0], g_Vars.Chams.ColorCTVis[1], g_Vars.Chams.ColorCTVis[2], "Chams", "|Chams.Player.CT.Vis" );
			FILE_WRITE_RGB ( g_Vars.Chams.ColorCTHide[0], g_Vars.Chams.ColorCTHide[1], g_Vars.Chams.ColorCTHide[2], "Chams", "|Chams.Player.CT.Hide" );
			FILE_WRITE_INT ( g_Vars.Chams.Weapon, "Chams", "|Chams.Weapon" );
			FILE_WRITE_INT ( g_Vars.Chams.WeaponVisibleOnly, "Chams", "|Chams.Weapon.VisibleOnly" );
			FILE_WRITE_INT ( g_Vars.Chams.WeaponRenderType, "Chams", "|Chams.Weapon.RenderType" );
			FILE_WRITE_RGB ( g_Vars.Chams.WeaponColorVis[0], g_Vars.Chams.WeaponColorVis[1], g_Vars.Chams.WeaponColorVis[2], "Chams", "|Chams.Weapon.Color.Vis" );
			FILE_WRITE_RGB ( g_Vars.Chams.WeaponColorHide[0], g_Vars.Chams.WeaponColorHide[1], g_Vars.Chams.WeaponColorHide[2], "Chams", "|Chams.Weapon.Color.Hide" );
			FILE_WRITE_INT ( g_Vars.Chams.Hands, "Chams", "|Chams.Hands" );
			FILE_WRITE_INT ( g_Vars.Chams.HandsRenderType, "Chams", "|Chams.Hands.RenderType" );
			FILE_WRITE_RGB ( g_Vars.Chams.HandsColor[0], g_Vars.Chams.HandsColor[1], g_Vars.Chams.HandsColor[2], "Chams", "|Chams.Hands.Color" );
		}

		void GroundStrafe ( )
		{
			std::string Path = szDirFile ( MISC_PATH ).c_str ( );

			FILE_WRITE_INT ( g_Vars.GroundStrafe.ScrollEmulation, "GroundStrafe", "|GroundStrafe.Scroll.Emulation" );
			FILE_WRITE_DIR ( g_Vars.GroundStrafe.ScrollDirection, "GroundStrafe", "|GroundStrafe.Scroll.Direction" );
			FILE_WRITE_FLOAT_2 ( g_Vars.GroundStrafe.ScrollDistance[0], g_Vars.GroundStrafe.ScrollDistance[1], "GroundStrafe", "|GroundStrafe.Scroll.Distance" );
			FILE_WRITE_INT_2 ( g_Vars.GroundStrafe.ScrollCount[0], g_Vars.GroundStrafe.ScrollCount[1], "GroundStrafe", "|GroundStrafe.Scroll.Count" );
			FILE_WRITE_FLOAT ( g_Vars.GroundStrafe.SlowdownScale, "GroundStrafe", "|GroundStrafe.Slowdown.Scale" );
			FILE_WRITE_FLOAT ( g_Vars.GroundStrafe.SlowdownAngle, "GroundStrafe", "|GroundStrafe.Slowdown.Angle" );
			FILE_WRITE_INT ( g_Vars.GroundStrafe.FallRun, "GroundStrafe", "|GroundStrafe.FallRun" );
			FILE_WRITE_INT ( g_Vars.GroundStrafe.Helper, "GroundStrafe", "|GroundStrafe.Helper" );
			FILE_WRITE_INT ( g_Vars.GroundStrafe.StandUpFallVelocity, "GroundStrafe", "|GroundStrafe.StandUp.FallVelocity" );
			FILE_WRITE_KEY ( g_Vars.GroundStrafe.StandUpKey, "GroundStrafe", "|GroundStrafe.StandUp.Key" );
			FILE_WRITE_KEY ( g_Vars.GroundStrafe.Key, "GroundStrafe", "|GroundStrafe.Key" );
		}

		void TriggerWeapons ( )
		{
			std::string Path = szDirFile ( TRIGGERBOT_PATH ).c_str ( );

			FILE_WRITE_INT ( g_Vars.Trigger.Enable, "Trigger", "|Trigger.Enable" );
			FILE_WRITE_INT ( g_Vars.Trigger.FriendlyFire, "Trigger", "|Trigger.FriendlyFire" );
			FILE_WRITE_INT ( g_Vars.Trigger.VisibleCheck, "Trigger", "|Trigger.VisibleCheck" );
			FILE_WRITE_INT ( g_Vars.Trigger.SnipersOnlyInZoom, "Trigger", "|Trigger.Snipers.OnlyInZoom" );

			for ( int Index = 1; Index <= 30; ++Index )
			{
				std::string Weapon;

				Utils::GetSection ( Index, Weapon );

				std::string Trigger = "|" + Weapon + ".Trigger";
				std::string OnlyHead = "|" + Weapon + ".OnlyHead";
				std::string ProSpread = "|" + Weapon + ".ProSpread";

				FILE_WRITE_INT ( g_Vars.TriggerWeapons[Index].Trigger, "Weapons", ( char* )Trigger.c_str ( ) );
				FILE_WRITE_INT ( g_Vars.TriggerWeapons[Index].OnlyHead, "Weapons", ( char* )OnlyHead.c_str ( ) );
				FILE_WRITE_INT ( g_Vars.TriggerWeapons[Index].ProSpread, "Weapons", ( char* )ProSpread.c_str ( ) );
			}
		}
	}

	void GetBaseDir ( const HINSTANCE& hInstance )
	{
		Files::BaseDir = ( char* )HeapAlloc ( GetProcessHeap ( ), HEAP_ZERO_MEMORY, MAX_PATH );

		GetModuleFileName ( hInstance, Files::BaseDir, MAX_PATH );

		char* Position = Files::BaseDir + lstrlen ( Files::BaseDir );

		while ( Position >= Files::BaseDir && *Position != '\\' )
		{
			--Position;
		}

		Position[1] = 0;
	}

	void LoadSettings ( )
	{
		FilesCheck ( );

		LoadFileMain ( );
		LoadFileFunctions ( );
		LoadFileVisuals ( );
		LoadFileMisc ( );
		LoadFileAimBot ( );
		LoadFileTriggerBot ( );
	}

	void ReloadSettings ( )
	{
		FilesCheck ( );

		LoadFileMain ( );
		LoadFileVisuals ( );
		LoadFileMisc ( );
		LoadFileAimBot ( );
		LoadFileTriggerBot ( );
	}

	void SaveSettings ( )
	{
		FilesCheck ( );

		SaveFileMain ( );
		SaveFileVisuals ( );
		SaveFileMisc ( );
		SaveFileAimBot ( );
		SaveFileTriggerBot ( );
	}

	void FilesCheck ( )
	{
		if ( !FileExists ( szDirFile ( MAIN_PATH ).c_str ( ) ) )
		{
			CreateSettingsDirectory ( );
			CreateFileMain ( );
		}

		if ( !FileExists ( szDirFile ( FUNCTIONS_PATH ).c_str ( ) ) )
		{
			CreateSettingsDirectory ( );
			CreateFileFunctions ( );
		}

		if ( !FileExists ( szDirFile ( VISUALS_PATH ).c_str ( ) ) )
		{
			CreateSettingsDirectory ( );
			CreateFileVisuals ( );
		}

		if ( !FileExists ( szDirFile ( MISC_PATH ).c_str ( ) ) )
		{
			CreateSettingsDirectory ( );
			CreateFileMisc ( );
		}

		if ( !FileExists ( szDirFile ( AIMBOT_PATH ).c_str ( ) ) )
		{
			CreateSettingsDirectory ( );
			CreateFileAimBot ( );
		}

		if ( !FileExists ( szDirFile ( TRIGGERBOT_PATH ).c_str ( ) ) )
		{
			CreateSettingsDirectory ( );
			CreateFileTriggerBot ( );
		}
	}

	void LoadFileMain ( )
	{
		if ( FileExists ( szDirFile ( MAIN_PATH ).c_str ( ) ) )
			Read::Main ( );
	}

	void LoadFileFunctions ( )
	{
		if ( FileExists ( szDirFile ( FUNCTIONS_PATH ).c_str ( ) ) )
			Read::Functions ( );
	}

	void LoadFileVisuals ( )
	{
		if ( FileExists ( szDirFile ( VISUALS_PATH ).c_str ( ) ) )
		{
			if ( g_Vars.Functions.Menu )
				Read::Menu ( );

			if ( g_Vars.Functions.ScreenInfo )
				Read::ScreenInfo ( );

			if ( g_Vars.Functions.ESP )
				Read::ESP ( );

			if ( g_Vars.Functions.Chams )
				Read::Chams ( );

			if ( g_Vars.Functions.NoFlash )
				Read::NoFlash ( );

			if ( g_Vars.Functions.Crosshair )
				Read::Crosshair ( );

			Read::Other ( );
		}
	}

	void LoadFileMisc ( )
	{
		if ( FileExists ( szDirFile ( MISC_PATH ).c_str ( ) ) )
		{
			if ( g_Vars.Functions.Speed )
				Read::Speed ( );

			if ( g_Vars.Functions.BunnyHop )
				Read::BunnyHop ( );

			if ( g_Vars.Functions.GroundStrafe )
				Read::GroundStrafe ( );
		}
	}

	void LoadFileAimBot ( )
	{
		if ( FileExists ( szDirFile ( AIMBOT_PATH ).c_str ( ) ) )
		{
			if ( g_Vars.Functions.Weapons )
				Read::AimWeapons ( );

			if ( g_Vars.Functions.Recoil )
				Read::Recoil ( );

			if ( g_Vars.Functions.AutoPistol )
				Read::AutoPistol ( );

			if ( g_Vars.Functions.FastZoom )
				Read::FastZoom ( );
		}
	}

	void LoadFileTriggerBot ( )
	{
		if ( FileExists ( szDirFile ( TRIGGERBOT_PATH ).c_str ( ) ) )
		{
			if ( g_Vars.Functions.TriggerWeapons )
				Read::TriggerWeapons ( );
		}
	}

	void SaveFileMain ( )
	{
		if ( FileExists ( szDirFile ( MAIN_PATH ).c_str ( ) ) )
			Write::Main ( );
	}

	void SaveFileVisuals ( )
	{
		if ( FileExists ( szDirFile ( VISUALS_PATH ).c_str ( ) ) )
		{
			if ( g_Vars.Functions.Menu )
				Write::Menu ( );

			if ( g_Vars.Functions.ScreenInfo )
				Write::ScreenInfo ( );

			if ( g_Vars.Functions.ESP )
				Write::ESP ( );

			if ( g_Vars.Functions.Chams )
				Write::Chams ( );

			if ( g_Vars.Functions.NoFlash )
				Write::NoFlash ( );

			if ( g_Vars.Functions.Crosshair )
				Write::Crosshair ( );

			Write::Other ( );
		}
	}

	void SaveFileMisc ( )
	{
		if ( FileExists ( szDirFile ( MISC_PATH ).c_str ( ) ) )
		{
			if ( g_Vars.Functions.Speed )
				Write::Speed ( );

			if ( g_Vars.Functions.BunnyHop )
				Write::BunnyHop ( );

			if ( g_Vars.Functions.GroundStrafe )
				Write::GroundStrafe ( );
		}
	}

	void SaveFileAimBot ( )
	{
		if ( FileExists ( szDirFile ( AIMBOT_PATH ).c_str ( ) ) )
		{
			if ( g_Vars.Functions.Weapons )
				Write::AimWeapons ( );

			if ( g_Vars.Functions.Recoil )
				Write::Recoil ( );

			if ( g_Vars.Functions.AutoPistol )
				Write::AutoPistol ( );

			if ( g_Vars.Functions.FastZoom )
				Write::FastZoom ( );
		}
	}

	void SaveFileTriggerBot ( )
	{
		if ( FileExists ( szDirFile ( TRIGGERBOT_PATH ).c_str ( ) ) )
		{
			if ( g_Vars.Functions.TriggerWeapons )
				Write::TriggerWeapons ( );
		}
	}

	void CreateLogDirectory ( )
	{
		char* LogDirectiory = new char[256];

		lstrcpy ( LogDirectiory, BaseDir );
		lstrcat ( LogDirectiory, LOG_DIR_PATH );
		CreateDirectory ( LogDirectiory, 0 );
	}

	void CreateInjectLogFile ( )
	{
		char InjectLogFile[1024];

		strcpy_s ( InjectLogFile, BaseDir );
		strcat_s ( InjectLogFile, LOG_INJECT_PATH );

		if ( !FileExists ( szDirFile ( LOG_INJECT_PATH ).c_str ( ) ) )
		{
			Inject.open ( InjectLogFile, std::ios::app );
		}
		else
		{
			Inject.open ( InjectLogFile, std::ios::app );

			Inject << std::endl;
		}
	}

	void CreateInfoLogFile ( )
	{
		char InfoLogFile[1024];

		strcpy_s ( InfoLogFile, BaseDir );
		strcat_s ( InfoLogFile, "\\Logs\\Info.log" );

		if ( !FileExists ( szDirFile ( LOG_INJECT_PATH ).c_str ( ) ) )
		{
			Info.open ( InfoLogFile, std::ios::app );
		}
		else
		{
			Info.open ( InfoLogFile, std::ios::app );

			Info << std::endl;
		}
	}

	void CreateSettingsDirectory ( )
	{
		char* SettingsPath = new char[256];

		lstrcpy ( SettingsPath, BaseDir );
		lstrcat ( SettingsPath, SETTINGS_DIR_PATH );

		CreateDirectory ( SettingsPath, 0 );
	}

	void CreateFileMain ( )
	{
		std::ofstream Main;

		char* MainPath = new char[256];

		lstrcpy ( MainPath, BaseDir );
		lstrcat ( MainPath, MAIN_PATH );

		Main.open ( MainPath, std::ios::app );

		Main << "[Main]" << std::endl;
		Main << "|Language = english" << std::endl << std::endl;

		Main << "|Reload.Key = F5" << std::endl;
		Main << "|Save.Key = F6" << std::endl << std::endl;

		Main << "|Panic.Key = F7" << std::endl;
		Main << "|Panic.AimBot.Key = F8" << std::endl;
		Main << "|Panic.Visuals.Key = F9" << std::endl;
		Main << "|Panic.Misc.Key = F10" << std::endl << std::endl;

		Main << "|Player.Valid.Check = 1" << std::endl << std::endl;

		Main << "|AntiScreen.Enable = 1" << std::endl;
		Main << "|AntiScreen.Timer = 6" << std::endl;
		Main << "|AntiScreen.Key = F12" << std::endl << std::endl;

		Main << "|Font.Outline.Style = 1" << std::endl;

		Main.close ( );
	}

	void CreateFileFunctions ( )
	{
		std::ofstream Functions;

		char* FunctionsPath = new char[256];

		lstrcpy ( FunctionsPath, BaseDir );
		lstrcat ( FunctionsPath, FUNCTIONS_PATH );

		Functions.open ( FunctionsPath, std::ios::app );

		Functions << "[Visuals]" << std::endl;
		Functions << "|Menu = 1" << std::endl;
		Functions << "|ScreenInfo = 1" << std::endl;
		Functions << "|ESP = 1" << std::endl;
		Functions << "|Chams = 1" << std::endl;
		Functions << "|NoFlash = 1" << std::endl;
		Functions << "|Crosshair = 1" << std::endl << std::endl;

		Functions << "[Misc]" << std::endl;
		Functions << "|Speed = 1" << std::endl;
		Functions << "|BunnyHop = 1" << std::endl;
		Functions << "|GroundStrafe = 1" << std::endl << std::endl;

		Functions << "[AimBot]" << std::endl;
		Functions << "|Weapons = 1" << std::endl;
		Functions << "|Recoil = 1" << std::endl;
		Functions << "|AutoPistol = 1" << std::endl;
		Functions << "|FastZoom = 1" << std::endl << std::endl;

		Functions << "[TriggerBot]" << std::endl;
		Functions << "|Weapons = 1" << std::endl;

		Functions.close ( );
	}

	void CreateFileVisuals ( )
	{
		std::ofstream Visuals;

		char* VisualsPath = new char[256];

		lstrcpy ( VisualsPath, BaseDir );
		lstrcat ( VisualsPath, VISUALS_PATH );

		Visuals.open ( VisualsPath, std::ios::app );

		Visuals << "[Menu]" << std::endl;
		Visuals << "|Menu.X = 200" << std::endl;
		Visuals << "|Menu.Y = 138" << std::endl;
		Visuals << "|Menu.Box.Height = 21" << std::endl;
		Visuals << "|Menu.Box.Width = 174" << std::endl;
		Visuals << "|Menu.Box.Color = 20, 20, 20, 130" << std::endl;
		Visuals << "|Menu.Box.Outline.Color = 30, 30, 80, 80" << std::endl;
		Visuals << "|Menu.Box.Select.Color = 0, 100, 255, 80" << std::endl;
		Visuals << "|Menu.Text.Color = 255, 255, 255" << std::endl;
		Visuals << "|Menu.Key = INSERT" << std::endl << std::endl;

		Visuals << "[ScreenInfo]" << std::endl;
		Visuals << "|ScreenInfo.Enable = 1" << std::endl;
		Visuals << "|ScreenInfo.FPS = 0" << std::endl;
		Visuals << "|ScreenInfo.Copyright = 1" << std::endl;
		Visuals << "|ScreenInfo.Time = 1" << std::endl;
		Visuals << "|ScreenInfo.ShowKeys = 0" << std::endl;
		Visuals << "|ScreenInfo.KreedzInfo = 0" << std::endl;
		Visuals << "|ScreenInfo.Font.Color = 255, 255, 255, 255" << std::endl;
		Visuals << "|ScreenInfo.Font.Outline = 1" << std::endl << std::endl;

		Visuals << "[ESP]" << std::endl;
		Visuals << "|ESP.Enable = 1" << std::endl;
		Visuals << "|ESP.Player = 1" << std::endl;
		Visuals << "|ESP.Player.VisibleOnly = 0" << std::endl;
		Visuals << "|ESP.Player.Box = 1" << std::endl;
		Visuals << "|ESP.Player.Box.Filled = 0" << std::endl;
		Visuals << "|ESP.Player.Box.T.Vis = 255, 255, 0" << std::endl;
		Visuals << "|ESP.Player.Box.T.Hide = 255, 30, 0" << std::endl;
		Visuals << "|ESP.Player.Box.CT.Vis = 0, 255, 0" << std::endl;
		Visuals << "|ESP.Player.Box.CT.Hide = 0, 30, 255" << std::endl;
		Visuals << "|ESP.Player.Name = 0" << std::endl;
		Visuals << "|ESP.Player.Weapon = 0" << std::endl;
		Visuals << "|ESP.Player.Distance = 0" << std::endl;
		Visuals << "|ESP.Player.Barrel = 0" << std::endl;
		Visuals << "|ESP.World.C4 = 1" << std::endl;
		Visuals << "|ESP.World.Items = 0" << std::endl;
		Visuals << "|ESP.World.Nades = 1" << std::endl;
		Visuals << "|ESP.C4Timer = 2" << std::endl;
		Visuals << "|ESP.C4Timer.Value = 35" << std::endl;
		Visuals << "|ESP.Sound = 0" << std::endl;
		Visuals << "|ESP.Sound.Distance = 1000" << std::endl;
		Visuals << "|ESP.Sound.FadeTime = 1000" << std::endl;
		Visuals << "|ESP.Font.Color = 255, 255, 255, 255" << std::endl;
		Visuals << "|ESP.Font.Outline = 1" << std::endl << std::endl;

		Visuals << "[Chams]" << std::endl;
		Visuals << "|Chams.Enable = 0" << std::endl;
		Visuals << "|Chams.Player = 1" << std::endl;
		Visuals << "|Chams.Player.VisibleOnly = 0" << std::endl;
		Visuals << "|Chams.Player.RenderType = 2" << std::endl;
		Visuals << "|Chams.Player.T.Vis = 255, 140, 0" << std::endl;
		Visuals << "|Chams.Player.T.Hide = 255, 30, 0" << std::endl;
		Visuals << "|Chams.Player.CT.Vis = 0, 140, 255" << std::endl;
		Visuals << "|Chams.Player.CT.Hide = 0, 30, 255" << std::endl;
		Visuals << "|Chams.Weapon = 0" << std::endl;
		Visuals << "|Chams.Weapon.VisibleOnly = 1" << std::endl;
		Visuals << "|Chams.Weapon.RenderType = 2" << std::endl;
		Visuals << "|Chams.Weapon.Color.Vis = 0, 140, 0" << std::endl;
		Visuals << "|Chams.Weapon.Color.Hide = 80, 80, 80" << std::endl;
		Visuals << "|Chams.Hands = 0" << std::endl;
		Visuals << "|Chams.Hands.RenderType = 2" << std::endl;
		Visuals << "|Chams.Hands.Color = 0, 140, 255" << std::endl << std::endl;

		Visuals << "[NoFlash]" << std::endl;
		Visuals << "|NoFlash.Enable = 0" << std::endl;
		Visuals << "|NoFlash.Fade.Limit = 100" << std::endl;
		Visuals << "|NoFlash.Fade.Color.Enable = 0" << std::endl;
		Visuals << "|NoFlash.Fade.Color = 255, 255, 255" << std::endl;
		Visuals << "|NoFlash.Fade.Color.Random = 0" << std::endl;
		Visuals << "|NoFlash.DrawFlashed = 1" << std::endl;
		Visuals << "|NoFlash.Font.Outline = 0" << std::endl << std::endl;

		Visuals << "[Crosshair]" << std::endl;
		Visuals << "|Crosshair.Enable = 1" << std::endl;
		Visuals << "|Crosshair.Dot = 0" << std::endl;
		Visuals << "|Crosshair.Size = 6" << std::endl;
		Visuals << "|Crosshair.Gap = 5" << std::endl;
		Visuals << "|Crosshair.Thickness = 1" << std::endl;
		Visuals << "|Crosshair.Dynamic = 1" << std::endl;
		Visuals << "|Crosshair.Dynamic.Scale = 4.0" << std::endl;
		Visuals << "|Crosshair.Outline = 0" << std::endl;
		Visuals << "|Crosshaie.Snipers = 1" << std::endl;
		Visuals << "|Crosshair.Color = 64, 255, 64, 255" << std::endl << std::endl;

		Visuals << "[Other]" << std::endl;
		Visuals << "|Draw.Aim.Spot = 0" << std::endl;
		Visuals << "|Draw.Aim.FOV = 0" << std::endl;
		Visuals << "|Draw.Punch = 0" << std::endl;
		Visuals << "|Draw.Spread = 0" << std::endl;
		Visuals << "|Status.AimBot = 0" << std::endl;
		Visuals << "|Status.TriggerBot = 1" << std::endl;
		Visuals << "|Remove.Smoke = 0" << std::endl;
		Visuals << "|Font.Color = 255, 255, 255, 255" << std::endl;
		Visuals << "|Font.Outline = 1" << std::endl;

		Visuals.close ( );
	}

	void CreateFileMisc ( )
	{
		std::ofstream Misc;

		char* MiscPath = new char[256];

		lstrcpy ( MiscPath, BaseDir );
		lstrcat ( MiscPath, MISC_PATH );

		Misc.open ( MiscPath, std::ios::app );

		Misc << "[Speed]" << std::endl;
		Misc << "|Speed.Player = 1.0" << std::endl;
		Misc << "|Speed.Engine = 0" << std::endl;
		Misc << "|Speed.Boost = 5.0" << std::endl;
		Misc << "|Speed.Boost.Key = none" << std::endl;
		Misc << "|Speed.Slowmo = 0.3" << std::endl;
		Misc << "|Speed.Slowmo.Key = none" << std::endl;
		Misc << "|Speed.Helper = 0" << std::endl;
		Misc << "|Speed.Helper.Ground = 1.1" << std::endl;
		Misc << "|Speed.Helper.Ladder = 1.1" << std::endl;
		Misc << "|Speed.Helper.Fly = 1.0" << std::endl << std::endl;

		Misc << "[BunnyHop]" << std::endl;
		Misc << "|BunnyHop.NoSlowdown = 1" << std::endl;
		Misc << "|BunnyHop.Scroll.Emulation = 0" << std::endl;
		Misc << "|BunnyHop.Scroll.Direction = up" << std::endl;
		Misc << "|BunnyHop.Scroll.Distance = 0.0, 11.5" << std::endl;
		Misc << "|BunnyHop.Scroll.RandFails = 0" << std::endl;
		Misc << "|BunnyHop.OnLadder = 1" << std::endl;
		Misc << "|BunnyHop.Helper = 1" << std::endl;
		Misc << "|BunnyHop.Helper.NoSlowdown = 1" << std::endl;
		Misc << "|BunnyHop.Helper.IdealPercent = 50" << std::endl;
		Misc << "|BunnyHop.StandUp.Auto = 0" << std::endl;
		Misc << "|BunnyHop.StandUp.FallVelocity = 180.0" << std::endl;
		Misc << "|BunnyHop.StandUp.Key = none" << std::endl;
		Misc << "|BunnyHop.Key = SPACE" << std::endl << std::endl;

		Misc << "[GroundStrafe]" << std::endl;
		Misc << "|GroundStrafe.Scroll.Emulation = 0" << std::endl;
		Misc << "|GroundStrafe.Scroll.Direction = down" << std::endl;
		Misc << "|GroundStrafe.Scroll.Distance = 0.0, 5.0" << std::endl;
		Misc << "|GroundStrafe.Scroll.Count = 1, 3" << std::endl;
		Misc << "|GroundStrafe.Slowdown.Scale = 1.0" << std::endl;
		Misc << "|GroundStrafe.Slowdown.Angle = 5.0" << std::endl;
		Misc << "|GroundStrafe.FallRun = 1" << std::endl;
		Misc << "|GroundStrafe.Helper = 1" << std::endl;
		Misc << "|GroundStrafe.StandUp.FallVelocity = 100" << std::endl;
		Misc << "|GroundStrafe.StandUp.Key = none" << std::endl;
		Misc << "|GroundStrafe.Key = none" << std::endl;

		Misc.close ( );
	}

	void CreateFileAimBot ( )
	{
		std::ofstream AimBot;

		char* AimBotPath = new char[256];

		lstrcpy ( AimBotPath, BaseDir );
		lstrcat ( AimBotPath, AIMBOT_PATH );

		AimBot.open ( AimBotPath, std::ios::app );

		AimBot << "[Aim]" << std::endl;
		AimBot << "|Aim.Enable = 1" << std::endl;
		AimBot << "|Aim.Silent = 0" << std::endl;
		AimBot << "|Aim.FriendlyFire = 0" << std::endl;
		AimBot << "|Aim.VisibleCheck = 1" << std::endl;
		AimBot << "|Aim.FlashCheck = 1" << std::endl;
		AimBot << "|Aim.FOV.Distance = 1" << std::endl;
		AimBot << "|Aim.KillDelay = 250" << std::endl << std::endl;

		AimBot << "[Recoil]" << std::endl;
		AimBot << "|Recoil.Enable = 0" << std::endl;
		AimBot << "|Recoil.X = 2.0" << std::endl;
		AimBot << "|Recoil.Y = 2.0" << std::endl;
		AimBot << "|Recoil.Smooth = 1.2" << std::endl;
		AimBot << "|Recoil.BulletStart = 2" << std::endl << std::endl;

		AimBot << "[AutoPistol]" << std::endl;
		AimBot << "|AutoPistol.Enable = 0" << std::endl;
		AimBot << "|AutoPistol.Delay = 25" << std::endl << std::endl;

		AimBot << "[FastZoom]" << std::endl;
		AimBot << "|FastZoom.Enable = 0" << std::endl;
		AimBot << "|FastZoom.Delay = 10" << std::endl;
		AimBot << "|FastZoom.QuickSwitch = 0" << std::endl << std::endl;

		AimBot << "[Weapons]" << std::endl;
		AimBot << "|USP.Aim = 1" << std::endl;
		AimBot << "|USP.BulletControl = 2, 1" << std::endl;
		AimBot << "|USP.HitBox = 11" << std::endl;
		AimBot << "|USP.HitBox.Nearest = 0" << std::endl;
		AimBot << "|USP.Prediction = 0.10" << std::endl;
		AimBot << "|USP.FOV = 2.5" << std::endl;
		AimBot << "|USP.Smooth = 4.0" << std::endl;
		AimBot << "|USP.Delay = 50" << std::endl;
		AimBot << "|USP.Delay.Type = 2" << std::endl;
		AimBot << "|USP.Recoil = 2.0" << std::endl;
		AimBot << "|USP.Recoil.Prediction = 0.20" << std::endl;
		AimBot << "|USP.Recoil.FOV = 5" << std::endl;
		AimBot << "|USP.Recoil.Smooth = 5.0" << std::endl << std::endl;

		AimBot << "|Glock18.Aim = 1" << std::endl;
		AimBot << "|Glock18.BulletControl = 2, 1" << std::endl;
		AimBot << "|Glock18.HitBox = 11" << std::endl;
		AimBot << "|Glock18.HitBox.Nearest = 0" << std::endl;
		AimBot << "|Glock18.Prediction = 0.10" << std::endl;
		AimBot << "|Glock18.FOV = 2.5" << std::endl;
		AimBot << "|Glock18.Smooth = 4.0" << std::endl;
		AimBot << "|Glock18.Delay = 50" << std::endl;
		AimBot << "|Glock18.Delay.Type = 2" << std::endl;
		AimBot << "|Glock18.Recoil = 2.0" << std::endl;
		AimBot << "|Glock18.Recoil.Prediction = 0.20" << std::endl;
		AimBot << "|Glock18.Recoil.FOV = 5" << std::endl;
		AimBot << "|Glock18.Recoil.Smooth = 5.0" << std::endl << std::endl;

		AimBot << "|DEagle.Aim = 1" << std::endl;
		AimBot << "|DEagle.BulletControl = 2, 1" << std::endl;
		AimBot << "|DEagle.HitBox = 11" << std::endl;
		AimBot << "|DEagle.HitBox.Nearest = 0" << std::endl;
		AimBot << "|DEagle.Prediction = 0.10" << std::endl;
		AimBot << "|DEagle.FOV = 2.5" << std::endl;
		AimBot << "|DEagle.Smooth = 4.0" << std::endl;
		AimBot << "|DEagle.Delay = 50" << std::endl;
		AimBot << "|DEagle.Delay.Type = 2" << std::endl;
		AimBot << "|DEagle.Recoil = 2.0" << std::endl;
		AimBot << "|DEagle.Recoil.Prediction = 0.20" << std::endl;
		AimBot << "|DEagle.Recoil.FOV = 5" << std::endl;
		AimBot << "|DEagle.Recoil.Smooth = 5.0" << std::endl << std::endl;

		AimBot << "|Five-Seven.Aim = 1" << std::endl;
		AimBot << "|Five-Seven.BulletControl = 2, 1" << std::endl;
		AimBot << "|Five-Seven.HitBox = 11" << std::endl;
		AimBot << "|Five-Seven.HitBox.Nearest = 0" << std::endl;
		AimBot << "|Five-Seven.Prediction = 0.10" << std::endl;
		AimBot << "|Five-Seven.FOV = 2.5" << std::endl;
		AimBot << "|Five-Seven.Smooth = 4.0" << std::endl;
		AimBot << "|Five-Seven.Delay = 50" << std::endl;
		AimBot << "|Five-Seven.Delay.Type = 2" << std::endl;
		AimBot << "|Five-Seven.Recoil = 2.0" << std::endl;
		AimBot << "|Five-Seven.Recoil.Prediction = 0.20" << std::endl;
		AimBot << "|Five-Seven.Recoil.FOV = 5" << std::endl;
		AimBot << "|Five-Seven.Recoil.Smooth = 5.0" << std::endl << std::endl;

		AimBot << "|Elite.Aim = 1" << std::endl;
		AimBot << "|Elite.BulletControl = 2, 1" << std::endl;
		AimBot << "|Elite.HitBox = 11" << std::endl;
		AimBot << "|Elite.HitBox.Nearest = 0" << std::endl;
		AimBot << "|Elite.Prediction = 0.10" << std::endl;
		AimBot << "|Elite.FOV = 2.5" << std::endl;
		AimBot << "|Elite.Smooth = 4.0" << std::endl;
		AimBot << "|Elite.Delay = 50" << std::endl;
		AimBot << "|Elite.Delay.Type = 2" << std::endl;
		AimBot << "|Elite.Recoil = 2.0" << std::endl;
		AimBot << "|Elite.Recoil.Prediction = 0.20" << std::endl;
		AimBot << "|Elite.Recoil.FOV = 5" << std::endl;
		AimBot << "|Elite.Recoil.Smooth = 5.0" << std::endl << std::endl;

		AimBot << "|P228.Aim = 1" << std::endl;
		AimBot << "|P228.BulletControl = 2, 1" << std::endl;
		AimBot << "|P228.HitBox = 11" << std::endl;
		AimBot << "|P228.HitBox.Nearest = 0" << std::endl;
		AimBot << "|P228.Prediction = 0.10" << std::endl;
		AimBot << "|P228.FOV = 2.5" << std::endl;
		AimBot << "|P228.Smooth = 4.0" << std::endl;
		AimBot << "|P228.Delay = 50" << std::endl;
		AimBot << "|P228.Delay.Type = 2" << std::endl;
		AimBot << "|P228.Recoil = 2.0" << std::endl;
		AimBot << "|P228.Recoil.Prediction = 0.20" << std::endl;
		AimBot << "|P228.Recoil.FOV = 5" << std::endl;
		AimBot << "|P228.Recoil.Smooth = 5.0" << std::endl << std::endl;

		AimBot << "|AK47.Aim = 1" << std::endl;
		AimBot << "|AK47.BulletControl = 2, 1000" << std::endl;
		AimBot << "|AK47.HitBox = 11" << std::endl;
		AimBot << "|AK47.HitBox.Nearest = 1" << std::endl;
		AimBot << "|AK47.Prediction = 0.10" << std::endl;
		AimBot << "|AK47.FOV = 2.5" << std::endl;
		AimBot << "|AK47.Smooth = 4.0" << std::endl;
		AimBot << "|AK47.Delay = 50" << std::endl;
		AimBot << "|AK47.Delay.Type = 2" << std::endl;
		AimBot << "|AK47.Recoil = 2.0" << std::endl;
		AimBot << "|AK47.Recoil.Prediction = 1.10" << std::endl;
		AimBot << "|AK47.Recoil.FOV = 8.0" << std::endl;
		AimBot << "|AK47.Recoil.Smooth = 14.0" << std::endl << std::endl;

		AimBot << "|M4A1.Aim = 1" << std::endl;
		AimBot << "|M4A1.BulletControl = 2, 1000" << std::endl;
		AimBot << "|M4A1.HitBox = 11" << std::endl;
		AimBot << "|M4A1.HitBox.Nearest = 1" << std::endl;
		AimBot << "|M4A1.Prediction = 0.10" << std::endl;
		AimBot << "|M4A1.FOV = 2.5" << std::endl;
		AimBot << "|M4A1.Smooth = 4.0" << std::endl;
		AimBot << "|M4A1.Delay = 50" << std::endl;
		AimBot << "|M4A1.Delay.Type = 2" << std::endl;
		AimBot << "|M4A1.Recoil = 2.0" << std::endl;
		AimBot << "|M4A1.Recoil.Prediction = 1.10" << std::endl;
		AimBot << "|M4A1.Recoil.FOV = 8" << std::endl;
		AimBot << "|M4A1.Recoil.Smooth = 14.0" << std::endl << std::endl;

		AimBot << "|AUG.Aim = 1" << std::endl;
		AimBot << "|AUG.BulletControl = 2, 1000" << std::endl;
		AimBot << "|AUG.HitBox = 11" << std::endl;
		AimBot << "|AUG.HitBox.Nearest = 1" << std::endl;
		AimBot << "|AUG.Prediction = 0.10" << std::endl;
		AimBot << "|AUG.FOV = 2.5" << std::endl;
		AimBot << "|AUG.Smooth = 4.0" << std::endl;
		AimBot << "|AUG.Delay = 50" << std::endl;
		AimBot << "|AUG.Delay.Type = 2" << std::endl;
		AimBot << "|AUG.Recoil = 2.0" << std::endl;
		AimBot << "|AUG.Recoil.Prediction = 1.10" << std::endl;
		AimBot << "|AUG.Recoil.FOV = 8" << std::endl;
		AimBot << "|AUG.Recoil.Smooth = 14.0" << std::endl << std::endl;

		AimBot << "|Galil.Aim = 1" << std::endl;
		AimBot << "|Galil.BulletControl = 2, 1000" << std::endl;
		AimBot << "|Galil.HitBox = 11" << std::endl;
		AimBot << "|Galil.HitBox.Nearest = 1" << std::endl;
		AimBot << "|Galil.Prediction = 0.10" << std::endl;
		AimBot << "|Galil.FOV = 2.5" << std::endl;
		AimBot << "|Galil.Smooth = 4.0" << std::endl;
		AimBot << "|Galil.Delay = 50" << std::endl;
		AimBot << "|Galil.Delay.Type = 2" << std::endl;
		AimBot << "|Galil.Recoil = 2.0" << std::endl;
		AimBot << "|Galil.Recoil.Prediction = 1.10" << std::endl;
		AimBot << "|Galil.Recoil.FOV = 8" << std::endl;
		AimBot << "|Galil.Recoil.Smooth = 14.0" << std::endl << std::endl;

		AimBot << "|FAMAS.Aim = 1" << std::endl;
		AimBot << "|FAMAS.BulletControl = 2, 1000" << std::endl;
		AimBot << "|FAMAS.HitBox = 11" << std::endl;
		AimBot << "|FAMAS.HitBox.Nearest = 1" << std::endl;
		AimBot << "|FAMAS.Prediction = 0.10" << std::endl;
		AimBot << "|FAMAS.FOV = 2.5" << std::endl;
		AimBot << "|FAMAS.Smooth = 4.0" << std::endl;
		AimBot << "|FAMAS.Delay = 50" << std::endl;
		AimBot << "|FAMAS.Delay.Type = 2" << std::endl;
		AimBot << "|FAMAS.Recoil = 2.0" << std::endl;
		AimBot << "|FAMAS.Recoil.Prediction = 1.10" << std::endl;
		AimBot << "|FAMAS.Recoil.FOV = 8" << std::endl;
		AimBot << "|FAMAS.Recoil.Smooth = 14.0" << std::endl << std::endl;

		AimBot << "|SG550.Aim = 1" << std::endl;
		AimBot << "|SG550.BulletControl = 2, 1000" << std::endl;
		AimBot << "|SG550.HitBox = 11" << std::endl;
		AimBot << "|SG550.HitBox.Nearest = 1" << std::endl;
		AimBot << "|SG550.Prediction = 0.10" << std::endl;
		AimBot << "|SG550.FOV = 2.5" << std::endl;
		AimBot << "|SG550.Smooth = 4.0" << std::endl;
		AimBot << "|SG550.Delay = 50" << std::endl;
		AimBot << "|SG550.Delay.Type = 2" << std::endl;
		AimBot << "|SG550.Recoil = 2.0" << std::endl;
		AimBot << "|SG550.Recoil.Prediction = 1.10" << std::endl;
		AimBot << "|SG550.Recoil.FOV = 8" << std::endl;
		AimBot << "|SG550.Recoil.Smooth = 14.0" << std::endl << std::endl;

		AimBot << "|XM1014.Aim = 1" << std::endl;
		AimBot << "|XM1014.BulletControl = 2, 1000" << std::endl;
		AimBot << "|XM1014.HitBox = 11" << std::endl;
		AimBot << "|XM1014.HitBox.Nearest = 1" << std::endl;
		AimBot << "|XM1014.Prediction = 0.10" << std::endl;
		AimBot << "|XM1014.FOV = 2.5" << std::endl;
		AimBot << "|XM1014.Smooth = 4.0" << std::endl;
		AimBot << "|XM1014.Delay = 50" << std::endl;
		AimBot << "|XM1014.Delay.Type = 2" << std::endl;
		AimBot << "|XM1014.Recoil = 2.0" << std::endl;
		AimBot << "|XM1014.Recoil.Prediction = 1.10" << std::endl;
		AimBot << "|XM1014.Recoil.FOV = 8" << std::endl;
		AimBot << "|XM1014.Recoil.Smooth = 14.0" << std::endl << std::endl;

		AimBot << "|MAC10.Aim = 1" << std::endl;
		AimBot << "|MAC10.BulletControl = 2, 1000" << std::endl;
		AimBot << "|MAC10.HitBox = 11" << std::endl;
		AimBot << "|MAC10.HitBox.Nearest = 1" << std::endl;
		AimBot << "|MAC10.Prediction = 0.10" << std::endl;
		AimBot << "|MAC10.FOV = 2.5" << std::endl;
		AimBot << "|MAC10.Smooth = 4.0" << std::endl;
		AimBot << "|MAC10.Delay = 50" << std::endl;
		AimBot << "|MAC10.Delay.Type = 2" << std::endl;
		AimBot << "|MAC10.Recoil = 2.0" << std::endl;
		AimBot << "|MAC10.Recoil.Prediction = 1.10" << std::endl;
		AimBot << "|MAC10.Recoil.FOV = 8" << std::endl;
		AimBot << "|MAC10.Recoil.Smooth = 14.0" << std::endl << std::endl;

		AimBot << "|UMP45.Aim = 1" << std::endl;
		AimBot << "|UMP45.BulletControl = 2, 1000" << std::endl;
		AimBot << "|UMP45.HitBox = 11" << std::endl;
		AimBot << "|UMP45.HitBox.Nearest = 1" << std::endl;
		AimBot << "|UMP45.Prediction = 0.10" << std::endl;
		AimBot << "|UMP45.FOV = 2.5" << std::endl;
		AimBot << "|UMP45.Smooth = 4.0" << std::endl;
		AimBot << "|UMP45.Delay = 50" << std::endl;
		AimBot << "|UMP45.Delay.Type = 2" << std::endl;
		AimBot << "|UMP45.Recoil = 2.0" << std::endl;
		AimBot << "|UMP45.Recoil.Prediction = 1.10" << std::endl;
		AimBot << "|UMP45.Recoil.FOV = 8" << std::endl;
		AimBot << "|UMP45.Recoil.Smooth = 14.0" << std::endl << std::endl;

		AimBot << "|MP5.Aim = 1" << std::endl;
		AimBot << "|MP5.BulletControl = 2, 1000" << std::endl;
		AimBot << "|MP5.HitBox = 11" << std::endl;
		AimBot << "|MP5.HitBox.Nearest = 1" << std::endl;
		AimBot << "|MP5.Prediction = 0.10" << std::endl;
		AimBot << "|MP5.FOV = 2.5" << std::endl;
		AimBot << "|MP5.Smooth = 4.0" << std::endl;
		AimBot << "|MP5.Delay = 50" << std::endl;
		AimBot << "|MP5.Delay.Type = 2" << std::endl;
		AimBot << "|MP5.Recoil = 2.0" << std::endl;
		AimBot << "|MP5.Recoil.Prediction = 1.10" << std::endl;
		AimBot << "|MP5.Recoil.FOV = 8" << std::endl;
		AimBot << "|MP5.Recoil.Smooth = 14.0" << std::endl << std::endl;

		AimBot << "|M249.Aim = 1" << std::endl;
		AimBot << "|M249.BulletControl = 2, 1000" << std::endl;
		AimBot << "|M249.HitBox = 11" << std::endl;
		AimBot << "|M249.HitBox.Nearest = 1" << std::endl;
		AimBot << "|M249.Prediction = 0.10" << std::endl;
		AimBot << "|M249.FOV = 2.5" << std::endl;
		AimBot << "|M249.Smooth = 4.0" << std::endl;
		AimBot << "|M249.Delay = 50" << std::endl;
		AimBot << "|M249.Delay.Type = 2" << std::endl;
		AimBot << "|M249.Recoil = 2.0" << std::endl;
		AimBot << "|M249.Recoil.Prediction = 1.10" << std::endl;
		AimBot << "|M249.Recoil.FOV = 8" << std::endl;
		AimBot << "|M249.Recoil.Smooth = 14.0" << std::endl << std::endl;

		AimBot << "|M3.Aim = 1" << std::endl;
		AimBot << "|M3.BulletControl = 2, 1000" << std::endl;
		AimBot << "|M3.HitBox = 11" << std::endl;
		AimBot << "|M3.HitBox.Nearest = 1" << std::endl;
		AimBot << "|M3.Prediction = 0.10" << std::endl;
		AimBot << "|M3.FOV = 2.5" << std::endl;
		AimBot << "|M3.Smooth = 4.0" << std::endl;
		AimBot << "|M3.Delay = 50" << std::endl;
		AimBot << "|M3.Delay.Type = 2" << std::endl;
		AimBot << "|M3.Recoil = 2.0" << std::endl;
		AimBot << "|M3.Recoil.Prediction = 1.10" << std::endl;
		AimBot << "|M3.Recoil.FOV = 8" << std::endl;
		AimBot << "|M3.Recoil.Smooth = 14.0" << std::endl << std::endl;

		AimBot << "|TMP.Aim = 1" << std::endl;
		AimBot << "|TMP.BulletControl = 2, 1000" << std::endl;
		AimBot << "|TMP.HitBox = 11" << std::endl;
		AimBot << "|TMP.HitBox.Nearest = 1" << std::endl;
		AimBot << "|TMP.Prediction = 0.10" << std::endl;
		AimBot << "|TMP.FOV = 2.5" << std::endl;
		AimBot << "|TMP.Smooth = 4.0" << std::endl;
		AimBot << "|TMP.Delay = 50" << std::endl;
		AimBot << "|TMP.Delay.Type = 2" << std::endl;
		AimBot << "|TMP.Recoil = 2.0" << std::endl;
		AimBot << "|TMP.Recoil.Prediction = 1.10" << std::endl;
		AimBot << "|TMP.Recoil.FOV = 8" << std::endl;
		AimBot << "|TMP.Recoil.Smooth = 14.0" << std::endl << std::endl;

		AimBot << "|G3SG1.Aim = 1" << std::endl;
		AimBot << "|G3SG1.BulletControl = 2, 1000" << std::endl;
		AimBot << "|G3SG1.HitBox = 11" << std::endl;
		AimBot << "|G3SG1.HitBox.Nearest = 1" << std::endl;
		AimBot << "|G3SG1.Prediction = 0.10" << std::endl;
		AimBot << "|G3SG1.FOV = 2.5" << std::endl;
		AimBot << "|G3SG1.Smooth = 4.0" << std::endl;
		AimBot << "|G3SG1.Delay = 50" << std::endl;
		AimBot << "|G3SG1.Delay.Type = 2" << std::endl;
		AimBot << "|G3SG1.Recoil = 2.0" << std::endl;
		AimBot << "|G3SG1.Recoil.Prediction = 1.10" << std::endl;
		AimBot << "|G3SG1.Recoil.FOV = 8" << std::endl;
		AimBot << "|G3SG1.Recoil.Smooth = 14.0" << std::endl << std::endl;

		AimBot << "|SG552.Aim = 1" << std::endl;
		AimBot << "|SG552.BulletControl = 2, 1000" << std::endl;
		AimBot << "|SG552.HitBox = 11" << std::endl;
		AimBot << "|SG552.HitBox.Nearest = 1" << std::endl;
		AimBot << "|SG552.Prediction = 0.10" << std::endl;
		AimBot << "|SG552.FOV = 2.5" << std::endl;
		AimBot << "|SG552.Smooth = 4.0" << std::endl;
		AimBot << "|SG552.Delay = 50" << std::endl;
		AimBot << "|SG552.Delay.Type = 2" << std::endl;
		AimBot << "|SG552.Recoil = 2.0" << std::endl;
		AimBot << "|SG552.Recoil.Prediction = 1.10" << std::endl;
		AimBot << "|SG552.Recoil.FOV = 8" << std::endl;
		AimBot << "|SG552.Recoil.Smooth = 14.0" << std::endl << std::endl;

		AimBot << "|P90.Aim = 1" << std::endl;
		AimBot << "|P90.BulletControl = 2, 1000" << std::endl;
		AimBot << "|P90.HitBox = 11" << std::endl;
		AimBot << "|P90.HitBox.Nearest = 1" << std::endl;
		AimBot << "|P90.Prediction = 0.10" << std::endl;
		AimBot << "|P90.FOV = 2.5" << std::endl;
		AimBot << "|P90.Smooth = 4.0" << std::endl;
		AimBot << "|P90.Delay = 50" << std::endl;
		AimBot << "|P90.Delay.Type = 2" << std::endl;
		AimBot << "|P90.Recoil = 2.0" << std::endl;
		AimBot << "|P90.Recoil.Prediction = 1.10" << std::endl;
		AimBot << "|P90.Recoil.FOV = 8" << std::endl;
		AimBot << "|P90.Recoil.Smooth = 14.0" << std::endl << std::endl;

		AimBot << "|AWP.Aim = 1" << std::endl;
		AimBot << "|AWP.BulletControl = 2, 1" << std::endl;
		AimBot << "|AWP.HitBox = 11" << std::endl;
		AimBot << "|AWP.HitBox.Nearest = 1" << std::endl;
		AimBot << "|AWP.Prediction = 0.10" << std::endl;
		AimBot << "|AWP.FOV = 5.0" << std::endl;
		AimBot << "|AWP.Smooth = 1.0" << std::endl;
		AimBot << "|AWP.Delay = 10" << std::endl;
		AimBot << "|AWP.Delay.Type = 2" << std::endl;
		AimBot << "|AWP.Recoil = 2.0" << std::endl;
		AimBot << "|AWP.Recoil.Prediction = 1.10" << std::endl;
		AimBot << "|AWP.Recoil.FOV = 8" << std::endl;
		AimBot << "|AWP.Recoil.Smooth = 14.0" << std::endl << std::endl;

		AimBot << "|Scout.Aim = 1" << std::endl;
		AimBot << "|Scout.BulletControl = 2, 1" << std::endl;
		AimBot << "|Scout.HitBox = 11" << std::endl;
		AimBot << "|Scout.HitBox.Nearest = 1" << std::endl;
		AimBot << "|Scout.Prediction = 0.10" << std::endl;
		AimBot << "|Scout.FOV = 5.0" << std::endl;
		AimBot << "|Scout.Smooth = 1.0" << std::endl;
		AimBot << "|Scout.Delay = 10" << std::endl;
		AimBot << "|Scout.Delay.Type = 2" << std::endl;
		AimBot << "|Scout.Recoil = 2.0" << std::endl;
		AimBot << "|Scout.Recoil.Prediction = 1.10" << std::endl;
		AimBot << "|Scout.Recoil.FOV = 8" << std::endl;
		AimBot << "|Scout.Recoil.Smooth = 14.0" << std::endl;

		AimBot.close ( );
	}

	void CreateFileTriggerBot ( )
	{
		std::ofstream TriggerBot;

		char* TriggerBotPath = new char[256];

		lstrcpy ( TriggerBotPath, BaseDir );
		lstrcat ( TriggerBotPath, TRIGGERBOT_PATH );

		TriggerBot.open ( TriggerBotPath, std::ios::app );

		TriggerBot << "[Trigger]" << std::endl;
		TriggerBot << "|Trigger.Enable = 1" << std::endl;
		TriggerBot << "|Trigger.FriendlyFire = 0" << std::endl;
		TriggerBot << "|Trigger.VisibleCheck = 1" << std::endl;
		TriggerBot << "|Trigger.Snipers.OnlyInZoom = 1" << std::endl;
		TriggerBot << "|Trigger.Switch.Key = none" << std::endl;
		TriggerBot << "|Trigger.Key = none" << std::endl << std::endl;

		TriggerBot << "[Weapons]" << std::endl;
		TriggerBot << "|P228.Trigger = 1" << std::endl;
		TriggerBot << "|P228.OnlyHead = 1" << std::endl;
		TriggerBot << "|P228.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|Glock18.Trigger = 1" << std::endl;
		TriggerBot << "|Glock18.OnlyHead = 1" << std::endl;
		TriggerBot << "|Glock18.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|Scout.Trigger = 1" << std::endl;
		TriggerBot << "|Scout.OnlyHead = 1" << std::endl;
		TriggerBot << "|Scout.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|XM1014.Trigger = 1" << std::endl;
		TriggerBot << "|XM1014.OnlyHead = 1" << std::endl;
		TriggerBot << "|XM1014.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|MAC10.Trigger = 1" << std::endl;
		TriggerBot << "|MAC10.OnlyHead = 1" << std::endl;
		TriggerBot << "|MAC10.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|AUG.Trigger = 1" << std::endl;
		TriggerBot << "|AUG.OnlyHead = 1" << std::endl;
		TriggerBot << "|AUG.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|Elite.Trigger = 1" << std::endl;
		TriggerBot << "|Elite.OnlyHead = 1" << std::endl;
		TriggerBot << "|Elite.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|Five-Seven.Trigger = 1" << std::endl;
		TriggerBot << "|Five-Seven.OnlyHead = 1" << std::endl;
		TriggerBot << "|Five-Seven.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|UMP32.Trigger = 1" << std::endl;
		TriggerBot << "|UMP32.OnlyHead = 1" << std::endl;
		TriggerBot << "|UMP32.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|SG550.Trigger = 1" << std::endl;
		TriggerBot << "|SG550.OnlyHead = 1" << std::endl;
		TriggerBot << "|SG550.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|Galil.Trigger = 1" << std::endl;
		TriggerBot << "|Galil.OnlyHead = 1" << std::endl;
		TriggerBot << "|Galil.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|FAMAS.Trigger = 1" << std::endl;
		TriggerBot << "|FAMAS.OnlyHead = 1" << std::endl;
		TriggerBot << "|FAMAS.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|USP.Trigger = 1" << std::endl;
		TriggerBot << "|USP.OnlyHead = 1" << std::endl;
		TriggerBot << "|USP.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|AWP.Trigger = 1" << std::endl;
		TriggerBot << "|AWP.OnlyHead = 1" << std::endl;
		TriggerBot << "|AWP.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|MP5.Trigger = 1" << std::endl;
		TriggerBot << "|MP5.OnlyHead = 1" << std::endl;
		TriggerBot << "|MP5.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|M249.Trigger = 1" << std::endl;
		TriggerBot << "|M249.OnlyHead = 1" << std::endl;
		TriggerBot << "|M249.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|M3.Trigger = 1" << std::endl;
		TriggerBot << "|M3.OnlyHead = 1" << std::endl;
		TriggerBot << "|M3.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|M4A1.Trigger = 1" << std::endl;
		TriggerBot << "|M4A1.OnlyHead = 1" << std::endl;
		TriggerBot << "|M4A1.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|TMP.Trigger = 1" << std::endl;
		TriggerBot << "|TMP.OnlyHead = 1" << std::endl;
		TriggerBot << "|TMP.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|G3SG1.Trigger = 1" << std::endl;
		TriggerBot << "|G3SG1.OnlyHead = 1" << std::endl;
		TriggerBot << "|G3SG1.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|DEagle.Trigger = 1" << std::endl;
		TriggerBot << "|DEagle.OnlyHead = 1" << std::endl;
		TriggerBot << "|DEagle.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|SG552.Trigger = 1" << std::endl;
		TriggerBot << "|SG552.OnlyHead = 1" << std::endl;
		TriggerBot << "|SG552.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|AK47.Trigger = 1" << std::endl;
		TriggerBot << "|AK47.OnlyHead = 1" << std::endl;
		TriggerBot << "|AK47.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|P90.Trigger = 1" << std::endl;
		TriggerBot << "|P90.OnlyHead = 1" << std::endl;
		TriggerBot << "|P90.ProSpread = 1" << std::endl << std::endl;

		TriggerBot << "|UMP45.Trigger = 1" << std::endl;
		TriggerBot << "|UMP45.OnlyHead = 1" << std::endl;
		TriggerBot << "|UMP45.ProSpread = 1" << std::endl;

		TriggerBot.close ( );
	}
}