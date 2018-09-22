#define HPP_ADMIN					1
#define CHECK_ADMIN					0


#define MAX_FILE_WRITE_LENGHT		28
#define FIND_COUNTER_VALUE			100
#define MAX_SUBS_MENU				25
#define MAX_NAME_CHAR				32			

#define CLIENT_FIND_ERROR			"Error #0000. Couldn't find g_pClient pointer."
#define ENGINE_FIND_ERROR			"Error #0001. Couldn't find g_pEngine pointer."
#define STUDIO_FIND_ERROR			"Error #0002. Couldn't find g_pStudio pointer."
#define PPMOVE_PTR_ERROR			"Error #0003. Couldn't find g_pPlayerMove pointer."
#define SVC_MSG_ERROR				"Error #0004. Couldn't find SVCBase pointer."
#define ABSOLUTE_ERROR				"Error #0005. Absolute address error."
#define MSG_READ_CORD				"Error #0006. MSG_ReadCoord."
#define MSG_STR_READING				"Error #0007. MSG_StartBitReading."
#define MSG_END_READING				"Error #0008. MSG_EndBitReading."
#define CONSOLE_ERROR				"Error #0009. Couldn't find GameConsole pointer."
#define GAMEINFO_ERROR				"Error #0010. Couldn't find GameInfo pointer."
#define SPEEDPTR_ERROR				"Error #0011. Couldn't find SpeedPtr pointer."
#define ENGINEMSG_ERROR				"Error #0012. Couldn't find %s."

#define LOG_DIR_PATH				"\\Logs"
#define SETTINGS_DIR_PATH			"\\Settings"

#define LOG_INJECT_PATH				"\\Logs\\Inject.log"
#define MAIN_PATH					"\\Settings\\Main.ini"
#define FUNCTIONS_PATH				"\\Settings\\Functions.ini"
#define VISUALS_PATH				"\\Settings\\Visuals.ini"
#define MISC_PATH					"\\Settings\\Misc.ini"
#define AIMBOT_PATH					"\\Settings\\AimBot.ini"
#define TRIGGERBOT_PATH				"\\Settings\\TriggerBot.ini"

#define HPP							"[Hpp] "
#define SETTINGS_RELOADED_ENG		"Settings successfully reloaded.\n"
#define SETTINGS_RELOADED_RUS		"Настройки успешно перезагружены.\n"
#define SETTINGS_SAVED_ENG			"Settings successfully saved.\n"
#define SETTINGS_SAVED_RUS			"Настройки успешно сохранены.\n"

#define DELETE_MOD(name)			delete name; name = nullptr

#define GLOCK18_BURST				(1 << 1)
#define M4A1_SILENCER				(1 << 2)
#define USP_SILENCER				(1 << 0)
#define ELITE_LEFT					(1 << 4)

#define WALL_PEN0					0
#define WALL_PEN1					1
#define WALL_PEN2					2
	
#define MAX_WEAPON_LIST				29
#define MAX_WEAPON_NAME				32

#define MAX_ENTITY					1024
#define MAX_SOUNDS					1024

#define TERRORIST					1
#define CT							2
#define SPECTATOR					0

#define WEAPONLIST_P228				1
#define	WEAPONLIST_UNKNOWN1			2
#define	WEAPONLIST_SCOUT			3
#define	WEAPONLIST_HEGRENADE		4
#define	WEAPONLIST_XM1014			5
#define	WEAPONLIST_C4				6
#define	WEAPONLIST_MAC10			7
#define	WEAPONLIST_AUG				8
#define	WEAPONLIST_SMOKEGRENADE		9
#define	WEAPONLIST_ELITE			10
#define	WEAPONLIST_FIVESEVEN		11
#define	WEAPONLIST_UMP45			12
#define	WEAPONLIST_SG550			13
#define	WEAPONLIST_GALIL			14
#define	WEAPONLIST_FAMAS			15
#define	WEAPONLIST_USP				16
#define	WEAPONLIST_GLOCK18			17
#define	WEAPONLIST_AWP				18
#define	WEAPONLIST_MP5				19
#define	WEAPONLIST_M249				20
#define	WEAPONLIST_M3				21
#define	WEAPONLIST_M4A1				22
#define	WEAPONLIST_TMP				23
#define	WEAPONLIST_G3SG1			24
#define	WEAPONLIST_FLASHBANG		25
#define	WEAPONLIST_DEAGLE			26
#define	WEAPONLIST_SG552			27
#define	WEAPONLIST_AK47				28
#define	WEAPONLIST_KNIFE			29
#define	WEAPONLIST_P90				30

#define CLIPCAP_AK47				30
#define CLIPCAP_AUG					30
#define CLIPCAP_AWP					10
#define CLIPCAP_DEAGLE				7
#define CLIPCAP_ELITE				15
#define CLIPCAP_FIVESEVEN			20
#define CLIPCAP_G3SG1				20
#define CLIPCAP_GLOCK18				20
#define CLIPCAP_M249				100
#define CLIPCAP_M3					8
#define CLIPCAP_M4A1				30
#define CLIPCAP_MAC10				30
#define CLIPCAP_MP5					30
#define CLIPCAP_P228				13
#define CLIPCAP_P90					50
#define CLIPCAP_SCOUT				10
#define CLIPCAP_SG550				30
#define CLIPCAP_SG552				30
#define CLIPCAP_TMP					30
#define CLIPCAP_UMP45				25
#define CLIPCAP_USP					12
#define CLIPCAP_XM1014				7
#define CLIPCAP_GALIL				35
#define CLIPCAP_FAMAS				25

#define BULLET_NONE					0
#define BULLET_AK47					11
#define BULLET_AUG					12
#define BULLET_AWP					10
#define BULLET_DEAGLE				13
#define BULLET_ELITE				1
#define BULLET_FIVESEVEN			15
#define BULLET_G3SG1				11
#define BULLET_GLOCK18				1
#define BULLET_M249					12
#define BULLET_M4A1					12
#define BULLET_MAC10				9
#define BULLET_MP5					1
#define BULLET_P228					15
#define BULLET_P90					14
#define BULLET_SCOUT				11
#define BULLET_SG550				12
#define BULLET_SG552				12
#define BULLET_TMP					1
#define BULLET_UMP45				9
#define BULLET_USP					9
#define BULLET_M3					0
#define BULLET_XM1014				0
#define BULLET_GALIL				12
#define BULLET_FAMAS				12

#define SOUND_PACKET_VOLUME			255
#define SOUND_PACKET_ATTENUATION	1.0f
#define SOUND_PACKET_PITCH			100

#define M_PI_F						3.14159265358979323846f
#define M_PI						3.14159265358979323846

#define VectorSubtract(a, b, c)\
{\
	(c)[0] = (a)[0] - (b)[0];\
	(c)[1] = (a)[1] - (b)[1];\
	(c)[2] = (a)[2] - (b)[2];\
}

#define VectorTransform(a, b, c)\
{\
	(c)[0] = DotProduct((a), (b)[0]) + (b)[0][3];\
	(c)[1] = DotProduct((a), (b)[1]) + (b)[1][3];\
	(c)[2] = DotProduct((a), (b)[2]) + (b)[2][3];\
}

#define VectorLengthSquared(v)		((v)[0] * (v)[0] + (v)[1] * (v)[1] + (v)[2] * (v)[2])

#define POW(x)						((x) * (x))
#define BIT(n)						(1 << (n))

#define MENU_ENTRY_KEY				0x5B15E
#define SUBM_ENTRY_KEY				0x1DC42

#define SND_FL_VOLUME				BIT(0)
#define SND_FL_ATTENUATION			BIT(1)
#define SND_FL_LARGE_INDEX			BIT(2)
#define SND_FL_PITCH				BIT(3)
#define SND_FL_SENTENCE				BIT(4)
#define SND_FL_STOP					BIT(5)
#define SND_FL_CHANGE_VOL			BIT(6)
#define SND_FL_CHANGE_PITCH			BIT(7)
#define SND_FL_SPAWNING				BIT(8)

#define FL_NONE						0
#define FL_OUTLINE					1
#define FL_CENTER					2

#define PLAYER_FATAL_FALL_SPEED		980.0f
#define PLAYER_MAX_SAFE_FALL_SPEED	504.8f

#define DAMAGE_FOR_FALL_SPEED		100.0f / ( PLAYER_FATAL_FALL_SPEED - PLAYER_MAX_SAFE_FALL_SPEED )

#define DOWN						1000
#define UP							1001

#define ENGLISH						2000
#define RUSSIAN						2001

#define	K_POINT						46
#define K_COMMA						44
#define K_0							48
#define K_1							49
#define K_2							50
#define K_3							51
#define K_4							52
#define K_5							53
#define K_6							54
#define K_7							55
#define K_8							56
#define K_9							57
#define K_BRACKET_LEFT				91
#define K_BRACKET_RIGHT				93
#define K_A							97
#define K_B							98
#define K_C							99
#define K_D							100
#define K_E							101
#define K_F							102
#define K_G							103
#define K_H							104
#define K_I							105
#define K_J							106
#define K_K							107
#define K_L							108
#define K_M							109
#define K_N							110
#define K_O							111
#define K_P							112
#define K_Q							113
#define K_R							114
#define K_S							115
#define K_T							116
#define K_U							117
#define K_V							118
#define K_W							119
#define K_X							120
#define K_Y							121
#define K_Z							122

#define	SVC_BAD						0
#define	SVC_NOP						1
#define	SVC_DISCONNECT				2
#define	SVC_EVENT					3
#define	SVC_VERSION					4
#define	SVC_SETVIEW					5
#define	SVC_SOUND					6
#define	SVC_TIME					7
#define	SVC_PRINT					8
#define	SVC_STUFFTEXT				9
#define	SVC_SETANGLE				10
#define	SVC_SERVERINFO				11
#define	SVC_LIGHTSTYLE				12
#define	SVC_UPDATEUSERINFO			13
#define	SVC_DELTADESCRIPTION		14
#define	SVC_CLIENTDATA				15
#define	SVC_STOPSOUND				16
#define	SVC_PINGS					17
#define	SVC_PARTICLE				18
#define	SVC_DAMAGE					19
#define	SVC_SPAWNSTATIC				20
#define	SVC_EVENT_RELIABLE			21
#define	SVC_SPAWNBASELINE			22
#define	SVC_TEMPENTITY				23
#define	SVC_SETPAUSE				24
#define	SVC_SIGNONNUM				25
#define	SVC_CENTERPRINT				26
#define	SVC_KILLEDMONSTER			27
#define	SVC_FOUNDSECRET				28
#define	SVC_SPAWNSTATICSOUND		29
#define	SVC_INTERMISSION			30
#define	SVC_FINALE					31
#define	SVC_CDTRACK					32
#define	SVC_RESTORE					33
#define	SVC_CUTSCENE				34
#define	SVC_WEAPONANIM				35
#define	SVC_DECALNAME				36
#define	SVC_ROOMTYPE				37
#define	SVC_ADDANGLE				38
#define	SVC_NEWUSERMSG				39
#define	SVC_PACKETENTITIES			40
#define	SVC_DELTAPACKETENTITIES		41
#define	SVC_CHOKE					42
#define	SVC_RESOURCELIST			43
#define	SVC_NEWMOVEVARS				44
#define	SVC_RESOURCEREQUEST			45
#define	SVC_CUSTOMIZATION			46
#define	SVC_CROSSHAIRANGLE			47
#define	SVC_SOUNDFADE				48
#define	SVC_FILETXFERFAILED			49
#define	SVC_HLTV					50
#define	SVC_DIRECTOR				51
#define	SVC_VOICEINIT				52
#define	SVC_VOICEDATA				53
#define	SVC_SENDEXTRAINFO			54
#define	SVC_TIMESCALE				55
#define	SVC_RESOURCELOCATION		56
#define	SVC_SENDCVARVALUE			57
#define	SVC_SENDCVARVALUE2			58

#define DONT_SEE_FLASH_PERCENT		80
#define NORMAL_FOV					90

#define TraceEdge( x, y ){\
	Vector Start = SDK::Interfaces::g_pPlayerMove->origin;\
	Vector AirTemp = SDK::Interfaces::g_pPlayerMove->origin;\
	AirTemp[2] = -4096.0f;\
	pmtrace_t *pTrace = SDK::Interfaces::g_pEngine->PM_TraceLine ( Start, AirTemp, 1, ( SDK::Interfaces::g_pPlayerMove->flags & FL_DUCKING ) ? 1 : 0, -1 );\
	vec3_t vDis = ( AirTemp - SDK::Interfaces::g_pPlayerMove->origin ) * pTrace->fraction;\
	Start[2] -= 0.1f;\
	Start[2] -= -vDis[2];\
	Vector End = Start;\
	End[1] +=x * mind;\
	End[0] +=y * mind;\
	pmtrace_s* pTrace_s = SDK::Interfaces::g_pEngine->PM_TraceLine ( End, Start, 1, ( SDK::Interfaces::g_pPlayerMove->flags & FL_DUCKING ) ? 1 : 0, -1 );\
	if( !( pTrace_s->startsolid ) ) mind = ( pTrace_s->endpos - Start ).LengthXY ( ); }

#define StudioRenderFinal() _asm { mov ecx, dwTemp } _asm { call [dwStudioRenderFinal] }
