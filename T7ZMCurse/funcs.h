#pragma once
#include "TheCurse.h"

template<typename R, typename... Arguments> inline R Call(long long function, Arguments... args);

short G_MaterialIndex(const char * shader);
short G_LocalizedStringIndex(const char * str);

int Scr_GetSelf(int inst, int num);
int atoi(const char * str);

bool CL_AllLocalClientsDisconnected();
bool isInGame();

void StringTable_GetAsset(const char *filename, StringTable **tablePtr);

void GScr_AddWeaponStat(int entNum, const char * weapon, const char * stat, int value);
void IncInParam(int r3);

void Scr_GetFunctionHandle(uint32_t * r3, int inst, const char * file, uint32_t unknown_hash, uint32_t funchash, int r8, int r9);
uint32_t Scr_ExecEntThread(uint32_t ent, uint32_t func_pos, int argc);
uint32_t Scr_ExecThread(int inst, uint32_t func_pos, int argc, int r6, int r7);
void Scr_FreeThread(int inst, uint32_t threadHandle);
void Scr_AddString(int inst, const char * value);
void Scr_AddBool(int inst, bool value);
void Scr_AddInt(int inst, int value);

bool G_GivePlayerWeapon(gentity_s * ent, gclient_t * ps, int weaponIndex, int r6, int r7);
void BG_TakePlayerWeapon(gclient_t* ps, int weaponIndex, int r5);
int G_GetWeaponIndex(const char * weaponName);
void Add_Ammo(gentity_s*ent, int weaponIndex, int ammoCount, int fillClip, char weapModel);
void SV_GameSendServerCommand(int clientNum, int reliable, const char * cmd);

extern int va_t[2];
extern char*(*va)(const char * fmt, ...);
char * getName(int ClientNum);

void increment_challenge_stat(uint32_t ent, const char * stat);
void increment_challenge_stat(uint32_t ent, const char * stat, int amount);
void add_global_stat(uint32_t ent, const char * stat, int amount);
void set_global_stat(uint32_t ent, const char * stat, int value);

void set_treasure_chest_cost(int clientNum, const char * value);
void set_zombie_var(const char * zombie_var, int value);

void UnlockAllChallenges(int clientNum);

void SetZombieVars(int clientNum);

void spectator_respawn_player(int clientNum);

void give_gobblegum(int clientNum, const char * gum);
