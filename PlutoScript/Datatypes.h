#pragma once
#pragma once
#include <Windows.h>

typedef float vec3_t[3];
typedef BYTE byte;

enum EntityFlags
{
	God = 0x1,
	Demigod = 0x2,
	NoTarget = 0x4,
};

enum EntityType
{
	ENTTYPE_SCRIPTVEHICLE = 0x11,
};

struct WeaponInfo
{
	char unk1[1];
	char ForceDualWield;
	char unk2[10];
};

struct PlayerState
{
	int CommandTime;
	unsigned __int8 unk1[248];
	int PredictableEventSequence;
	int PredictableEvents[4];
	int PredictableEventParms[4];
	unsigned __int8 unk2[56];
	vec3_t Viewangles;
	char unk3[272];
	int HeldWeapons[15];
	WeaponInfo WeaponInfos[15];
	int CurrentOffhand;
	char unk4[8];
	int CurrentWeapon;
	int WeaponFlags;
	char unk5[24];
	int LastWeaponHand;
	char unk6[540];
	unsigned int Perks[2];
	char unk7[11604];
};

enum SessionState
{
	Playing = 0x0,
	Dead = 0x1,
	Spectator = 0x2,
	Intermission = 0x3,
};

enum ClientConnected
{
	CC_DISCONNECTED = 0x0,
	CC_CONNECTING = 0x1,
	CC_CONNECTED = 0x2,
};

enum Button
{
	BUTTON_ATTACK = 0x1,
	BUTTON_HOLDSPRINT = 0x2,
	BUTTON_MELEE = 0x4,
	BUTTON_ACTION = 0x8,
	BUTTON_RELOAD = 0x20,
	BUTTON_HOLDPRONE = 0x100,
	BUTTON_HOLDCROUCH = 0x200,
	BUTTON_JUMP_CHANGESTANCE = 0x400,
	BUTTON_ADS = 0x800,
	BUTTON_HOLDBREATH = 0x2000,
	BUTTON_LETHAL = 0x4000,
	BUTTON_TACTICAL = 0x8000,
	BUTTON_HOLDADS = 0x80800,
};

struct UserCommands
{
	unsigned int ServerTime;
	Button Buttons;
	unsigned int ViewAngles[3];
	int Weapon;
	int OffHandIndex;
	char Forwardmove;
	char Sidemove;
	unsigned __int16 Perks;
	char MeleeChargePitch;
	char MeleeChargeYaw;
	char MeleeChargeDist;
	char _unk2[3];
	char MissilePitch;
	char MissileYaw;
	char _unk3[4];
};

enum Team
{
	None = 0x0,
	Axis = 0x1,
	Allies = 0x2,
	Spectators = 0x3,
};

struct ClientState
{
	int ClientIndex;
	Team CurrentTeam;
	Team OldTeam;
	byte unk1[56];
	char Name[16];
	byte unk2[40];
	int UsingTag;
	int UsingTitle;
	char TitleText[24];
	int TitleBg;
	char TagText[8];
	int Level;
};

struct ClientSession
{
	SessionState SessionState;
	unsigned __int8 unk1[20];
	int Score;
	int Deaths;
	int Kills;
	int unk2;
	unsigned __int16 ScriptPersId;
	byte unk3[2];
	ClientConnected Connected;
	UserCommands Cmd;
	UserCommands OldCmd;
	int LocalClient;
	char NewNetName[16];
	unsigned __int8 unk4[36];
	ClientState Clientstate;
	unsigned __int8 unk5[336];
};


enum ClientFlags
{
	Noclip = 0x1,
	Ufo = 0x2,
	ControlsFrozen = 0x4,
};


struct Client
{
	PlayerState Playerstate;
	ClientSession Session;
	int SpectatorClient;
	ClientFlags Flags;
	char unk8[728];
};

struct SharedEntity
{
	unsigned __int8 unkFlags[3];
	unsigned __int8 InUse;
	byte unk1[24];
	int Contents;
	byte unk2[24];
	vec3_t CurrentOrigin;
	vec3_t CurrentAngles;
	int OwnerNum;
	int EventTime;
	Client *Client;
	char unk3[22];
	unsigned __int16 Classname;
	unsigned __int16 ScriptClassname;
	char unk4[14];
	EntityFlags Flags;
	char unk5[20];
	int Health;
	char unk6[212];
};

struct EntityState
{
	unsigned __int16 Number;
	unsigned __int8 unk1[2];
	EntityType Type;
	int EntityFlags;
	unsigned __int8 unk2[12];
	vec3_t Origin;
	unsigned __int8 unk3[24];
	vec3_t ViewAngles;
	unsigned __int8 unk4[184];
};

struct Entity
{
	EntityState State;
	SharedEntity Shared;
};
