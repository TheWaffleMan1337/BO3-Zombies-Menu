#pragma once
#include "TheCurse.h"


enum eStatsList_t {
	LIQUID_DIVINIUM = 0x4B258,
	RANKXP = 0x4AA78,
	TIME_PLAYED = 0x4AC58,

};

enum KeyState_t {
	//button_bits[1];
	BUTTON_B = 0x02,
	BUTTON_X_DOUBLE_TAP = 0x2000,
	BUTTON_STATE_SLIDE = 0x1000000,
	DPAD_UP = 0x40000,
	DPAD_DOWN = 0x20000,
	DPAD_LEFT = 0x10000,
	DPAD_RIGHT = 0x8000,

	//button_bits[0];
	BUTTON_LSHLDR = 0x100080,
	BUTTON_RSHLDR = 0x80000000,
	BUTTON_LTRIG = 0x10000,
	BUTTON_RTRIG = 0x20000,
	BUTTON_LSTICK = 0x40040000,
	BUTTON_RSTICK = 0x20000000,

	BUTTON_A = 0x200000,
	BUTTON_X = 0x4000000,
	BUTTON_Y = 0x08,
	STANCE_CROUCH = 0x400000,
	STANCE_PRONE = 0x800000,

};

struct usercmd_s {
	int serverTime;
	int button_bits[2];
	char __padding000[0x004];
	int angles[3];
	int currentWeapon;
	int currentOffhand;
	char __padding001[0x004];
	short bodymovement;
	char __padding002;
	short viewmovement;
	char __padding003[0x00F];
};

struct gclient_t {
	int clientNum;
	int commandTime;
	int pm_type;
	int bobCycle;
	int pm_flags;
	int weapFlags;
	char __padding001[0x0008];
	int otherFlags;
	char __padding002[0x000C];
	float origin[3];
	float velocity[3];
	char __padding003[0x0068];
	int gravity;
	float leanf;
	int speed;
	float delta_angles[3];
	char __padding004[0x002C];
	int jumpTime;
	float jumpOriginZ;
	char __padding005[0x015C];
	int currentWeapon;
	char __padding006[0x04C4];
	int doubleJumpState;
	int doubleJumpBoostUpDirection;
	int doubleJumpPitchOffset;
	int doubleJumpRollOffset;
	float playerEnergyRatio;
	int playerEnergyTime;
	char __padding007[0x55EC];
	int connected;
	usercmd_s curCmd;
	usercmd_s oldCmd;
	int localClient;
	int predictItemPickup;
	char newnetname[52];
	int maxHealth;
	char __padding008[0x0010];
	float moveSpeedScale;
	char __padding009[0x0018];
	char namewrite[52];
	char __padding010[0x006C];
	int score;
	int kills_actual;
	char __padding011[0x000C];
	int kills_view;
	char __padding012[0x02A0];
	int currentWeapon1;
	char __padding013[0x0002];
	bool isSwitching;
	bool isSprinting;
	char __padding014[0x0002];
	bool isSliding;
	char __padding015[0x0002];
	bool isAirborn;
	char __padding016[0x0022];
	int inLastStand;
	char __padding017[0x0040];
};

struct gentity_s {
	char __padding000[0x0018];
	float origin[3];
	char __padding001[0x01B0];
	gclient_t* ps;
	char __padding002[0x0044];
	short health;
	char __padding003[0x0130];
};

struct level_locals_t {
	gclient_t * clients;
	gentity_s * gentities;
	char __padding000[0x004];
	int entity_count;
	gentity_s * firstFreeEntity;
	gentity_s * lastFreeEntity;
	gentity_s * firstFreeActor;
	gentity_s * lastFreeActor;
	int actor_count;

	//int logFile;//0x48
	//int initializing; //0x4C
	//int maxclients; //0x54
	//int currentEntityThink; //0x153C

	//int scriptPrintChannel; //0x2EC4

};

struct StringTableCell {
	const char * string;
	int hash;
};

struct StringTable {
	const char * name;
	int columnCount;
	int rowCount;
	StringTableCell* values;
	int cellIndex;
};

struct scoreInfo_t {
	int nameHash;
	float value;
	uint32_t addPlayerStat : 1;
	uint32_t isMedal : 1;
	uint32_t isDoubleXP : 1;
	uint32_t isGunXP : 1;
	uint32_t demoBookmarkPriority : 7;
	uint32_t tableIndex : 9;
};

struct scoreInfoTable_t {
	scoreInfo_t scoreInfos[512];
	int numScoreInfos;
};

struct scr_entref_t {
	int entnum;
	int classnum;
};

extern gclient_t * g_clients;
extern gentity_s * g_entities;
extern level_locals_t* level;
