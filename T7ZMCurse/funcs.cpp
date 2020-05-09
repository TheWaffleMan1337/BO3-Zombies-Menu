#include "funcs.h"

template<typename R, typename... Arguments> inline R Call(long long function, Arguments... args) {
	int toc_t[2] = { function, 0x00DF1E60 };
	R(*temp)(Arguments...) = (R(*)(Arguments...))&toc_t;
	return temp(args...);
}

short G_MaterialIndex(const char * shader) {
	return Call<short>(0x00389590, shader);
}

short G_LocalizedStringIndex(const char * str) {
	return Call<short>(0x003894AC, str);
}

int Scr_GetSelf(int inst, int num) {
	return Call<int>(0x001B1C18, inst, num);
}

int atoi(const char * str) {
	return Call<int>(0x0094E85C, str, 0, 10);
}

bool CL_AllLocalClientsDisconnected() {
	return Call<bool>(0x007C79F4);
}

bool isInGame() {
	if (*(char*)(0x013FE11D) == 1)
		return true;
	return false;
}

void StringTable_GetAsset(const char *filename, StringTable **tablePtr) {
	Call<void>(0x00619930, filename, tablePtr);
}

void GScr_AddWeaponStat(int entNum, const char * weapon, const char * stat, int value) {
	//Scr_AddInt(0, value); printf("addint called\n");
	//Scr_AddString(0, stat); printf("Scr_AddString called\n");
	//Scr_AddString(0, weapon); printf("Scr_AddString called\n");
	//scr_entref_t ent = { entNum, 0 };
	//*(int*)(0x01110CA0) = 3;
	//Call<void>(0x002C4DA4, 0, ent); printf("addweaponstat called\n");
	//IncInParam(0); printf("IncInParam called\n");
}

void IncInParam(int r3) {
	Call<void>(0x001BBCDC, r3);
}

void Scr_GetFunctionHandle(uint32_t * r3, int inst, const char * file, uint32_t unknown_hash, uint32_t funchash, int r8, int r9) {
	Call<void>(0x001A170C, r3, inst, file, unknown_hash, funchash, r8, r9);
}

uint32_t Scr_ExecEntThread(uint32_t ent, uint32_t func_pos, int argc) {
	return Call<uint32_t>(0x0037C7C8, ent, func_pos, argc);
}

uint32_t Scr_ExecThread(int inst, uint32_t func_pos, int argc, int r6, int r7) {
	return Call<uint32_t>(0x001BDE2C, inst, func_pos, argc, r6, r7);
}

void Scr_FreeThread(int inst, uint32_t threadHandle) {
	Call<void>(0x001BE330, inst, threadHandle);
}

void Scr_AddString(int inst, const char * value) {
	Call<void>(0x001C1318, inst, value);
}

void Scr_AddBool(int inst, bool value) {
	Call<void>(0x001C0F48, inst, value);
}

void Scr_AddInt(int inst, int value) {
	Call<void>(0x001C0FA4, inst, value);
}

bool G_GivePlayerWeapon(gentity_s * ent, gclient_t * ps, int weaponIndex, int r6, int r7) {
	return Call<bool>(0x003AFC08, ent, ps, weaponIndex, r6, r7);
}

void BG_TakePlayerWeapon(gclient_t* ps, int weaponIndex, int r5) {
	Call<void>(0x0075B694, ps, weaponIndex, r5);
}

void Add_Ammo(gentity_s*ent, int weaponIndex, int ammoCount, int fillClip, char weapModel) {
	Call<void>(0x0031BE30, ent, weaponIndex, ammoCount, fillClip, weapModel);
}

void SV_GameSendServerCommand(int clientNum, int reliable, const char * cmd) {
	Call<void>(0x005E0E44, clientNum, reliable, cmd);
}

int G_GetWeaponIndex(const char * weaponName) {
	int BG_WeaponDef_t = 0x2C6AB44;
	while (*(int*)(BG_WeaponDef_t) != 0) {
		if (!strcmp((char*)(*(int*)(*(int*)(BG_WeaponDef_t))), weaponName)) {
			return (BG_WeaponDef_t - 0x2C6AB44) / 4;
		}
		BG_WeaponDef_t += 4;
	}
}

int va_t[2] = { 0x0062D0B8, 0x00DF1E60 };
char*(*va)(const char * fmt, ...) = (char*(*)(const char *, ...))&va_t;

char *getName(int ClientNum) {
	if (!strcmp(g_clients[ClientNum].newnetname, "")){
		return "not connected";
	}
	else {
		return g_clients[ClientNum].newnetname;
	}
}

void increment_challenge_stat(uint32_t ent, const char * stat) {
	Scr_AddString(0, stat);
	Scr_FreeThread(0, Scr_ExecEntThread(ent, 822439716, 1));
}

void increment_challenge_stat(uint32_t ent, const char * stat, int amount) {
	Scr_AddInt(0, amount);
	Scr_AddString(0, stat);
	Scr_FreeThread(0, Scr_ExecEntThread(ent, 822439716, 2));
}

void add_global_stat(uint32_t ent, const char * stat, int amount) {
	Scr_AddInt(0, amount);
	Scr_AddString(0, stat);
	Scr_FreeThread(0, Scr_ExecEntThread(ent, 822438744, 2));
}

void set_global_stat(uint32_t ent, const char * stat, int value) {
	Scr_AddInt(0, value);
	Scr_AddString(0, stat);
	Scr_FreeThread(0, Scr_ExecEntThread(ent, 822438672, 2));
}

void set_treasure_chest_cost(int clientNum, const char * value) {
	Scr_AddInt(0, atoi(value));
	Scr_FreeThread(0, Scr_ExecThread(0, 822229956, 1, 0, 1));
}

void set_zombie_var(const char * zombie_var, int value) {
	Scr_AddInt(0, value);
	Scr_AddString(0, zombie_var);
	Scr_FreeThread(0, Scr_ExecThread(0, 822504208, 2, 0, 1));
}

void UnlockAllChallenges(int clientNum) {
	set_global_stat(0x017BB2E8 + (0x350 * clientNum), "BGB_TOKENS_GAINED", 1333337);

	set_global_stat(0x017BB2E8 + (0x350 * clientNum), "RANKXP", 2200000);
	set_global_stat(0x017BB2E8 + (0x350 * clientNum), "RANK", 34);
	set_global_stat(0x017BB2E8 + (0x350 * clientNum), "PLEVEL", 10);

	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "DARKOPS_GENESIS_SUPER_EE", 1);

	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "DARKOPS_ZOD_EE", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "DARKOPS_MAX_RANK", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "ZOMBIE_HUNTER_KILL_HEADSHOT", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "ZOMBIE_HUNTER_KILL_MELEE", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "ZOMBIE_HUNTER_KILL_CRAWLER", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "ZOMBIE_HUNTER_KILL_PACKAPUNCH", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "ZOMBIE_HUNTER_KILL_TRAP", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "ZOMBIE_HUNTER_KILL_EXPLOSIVES", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "ZOMBIE_HUNTER_EXPLOSION_MULTIKILL", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "ZOMBIE_HUNTER_BLAST_FURNACE", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "ZOMBIE_HUNTER_DEAD_WIRE", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "ZOMBIE_HUNTER_FIRE_WORKS", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "ZOMBIE_HUNTER_THUNDER_WALL", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "ZOMBIE_HUNTER_TURNED", 10000);

	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "SURVIVALIST_BUY_MAGIC_BOX", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "SURVIVALIST_BUY_PERK", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "SURVIVALIST_BUY_WALLBUY", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "SURVIVALIST_BUY_DOOR", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "SURVIVALIST_REVIVE", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "SURVIVALIST_SURVIVE_ROUNDS", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "SURVIVALIST_CRAFTABLE", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "SURVIVALIST_BOARD", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "SURVIVALIST_POWERUP", 10000);

	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "GUM_GOBBLER_CONSUME", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "GUM_GOBBLER_POWERUPS", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "GUM_GOBBLER_ALCHEMICAL_ANTITHESIS", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "GUM_GOBBLER_ANYWHERE_BUT_HERE", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "GUM_GOBBLER_BURNED_OUT", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "GUM_GOBBLER_EPHEMERAL_ENHANCEMENT", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "GUM_GOBBLER_PHOENIX_UP", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "GUM_GOBBLER_SWORD_FLAY", 10000);
	increment_challenge_stat(0x017BB2E8 + (0x350 * clientNum), "GUM_GOBBLER_WALL_POWER", 10000);
}

void SetZombieVars(int clientNum) {
	set_zombie_var("zombie_point_scalar", 5);
	set_zombie_var("zombie_powerup_bonfire_sale_on", 1);
	set_zombie_var("zombie_powerup_bonfire_sale_time", 1000);
	set_zombie_var("zombie_score_bonus_torso", 500);
	set_zombie_var("zombie_move_speed_multiplier", 20);
	set_zombie_var("rebuild_barrier_cap_per_round", 10000);
}

void spectator_respawn_player(int clientNum) {
	Scr_FreeThread(0, Scr_ExecEntThread(0x017BB2E8 + (0x350 * clientNum), 821937916, 0));
}

void give_gobblegum(int clientNum, const char * gum) {
	Scr_AddString(0, gum);
	Scr_FreeThread(0, Scr_ExecEntThread(0x017BB2E8 + (0x350 * clientNum), 822073288, 1));
}
