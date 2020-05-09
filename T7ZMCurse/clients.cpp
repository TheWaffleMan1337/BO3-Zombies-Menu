#include "clients.h"
Clients * clients;

void Clients::Free() {
	memset(this, 0x00, sizeof(Clients));
}

void Clients::AddTitle(int menuIndex, int topMenu, const char * title) {
	menu[ClientNumber][menuIndex][0].parentMenu = topMenu;
	menu[ClientNumber][menuIndex][0].title = title;
}
void Clients::AddOption(int menuIndex, const char * opt, void(*func)(int clientNum)) {
	menu[ClientNumber][menuIndex][MaxScroll[menuIndex]].text = opt;
	menu[ClientNumber][menuIndex][MaxScroll[menuIndex]].func0 = func;
	menu[ClientNumber][menuIndex][MaxScroll[menuIndex]].calltype = CALL_NONE;
	MaxScroll[menuIndex] += 1;
}

void Clients::AddOption(int menuIndex, const char * opt, void(*func)(int clientNum, const char * arg), const char * arg) {
	menu[ClientNumber][menuIndex][MaxScroll[menuIndex]].text = opt;
	menu[ClientNumber][menuIndex][MaxScroll[menuIndex]].func1 = func;
	menu[ClientNumber][menuIndex][MaxScroll[menuIndex]].func1arg = arg;
	menu[ClientNumber][menuIndex][MaxScroll[menuIndex]].calltype = CALL_STRING;
	MaxScroll[menuIndex] += 1;
}

void Clients::AddOption(int menuIndex, const char * opt, void(*func)(int clientNum, int arg), int arg) {
	menu[ClientNumber][menuIndex][MaxScroll[menuIndex]].text = opt;
	menu[ClientNumber][menuIndex][MaxScroll[menuIndex]].func2 = func;
	menu[ClientNumber][menuIndex][MaxScroll[menuIndex]].func2arg = arg;
	menu[ClientNumber][menuIndex][MaxScroll[menuIndex]].calltype = CALL_INT;
	MaxScroll[menuIndex] += 1;
}

void Clients::AddOption(int menuIndex, const char * opt, void(*func)(int clientNum, int targetClientNum, const char * arg), const char * arg) {
	menu[ClientNumber][menuIndex][MaxScroll[menuIndex]].text = opt;
	menu[ClientNumber][menuIndex][MaxScroll[menuIndex]].func3 = func;
	menu[ClientNumber][menuIndex][MaxScroll[menuIndex]].func3arg = arg;
	menu[ClientNumber][menuIndex][MaxScroll[menuIndex]].calltype = CALL_CLIENT_STRING;
	MaxScroll[menuIndex] += 1;
}

void Clients::Wait(int time) {
	iTick = *(uint32_t*)(0x01744A00 + 0x96C), iWait = time;
}

bool Clients::IsReady() {
	return ((*(uint32_t*)(0x01744A00 + 0x96C) - iTick) > iWait);
}
void func(int clientNum){}
void Clients::CreateMenus() {
	for (int i = 0; i < 20;i++) {
		MaxScroll[i] = 0;
	}

	AddTitle(MenuBase, MenuBase, "Main Menu");
	AddOption(MenuBase, "Self Menu", ChangeMenu, SelfMenu);
	AddOption(MenuBase, "Lobby Menu", func);
	AddOption(MenuBase, "Weapons Menu", ChangeMenu, WeaponsMenu);
	AddOption(MenuBase, "GobbleGums Menu", ChangeMenu, GobbleGumsMenu);
	AddOption(MenuBase, "Account Menu", func);
	AddOption(MenuBase, "Points Menu", func);
	AddOption(MenuBase, "Round Menu", func);
	AddOption(MenuBase, "Players Menu", ChangeMenu, PlayersMenu);
	AddOption(MenuBase, "All Players Menu", func);
	
	AddTitle(SelfMenu, MenuBase, "Self Menu");
	AddOption(SelfMenu, "Give 10000 Points", givepoints, "10000");
	AddOption(SelfMenu, "Remove 10000 Points", givepoints, "-10000");
	AddOption(SelfMenu, "Option 1", func);
	AddOption(SelfMenu, "Option 1", func);
	AddOption(SelfMenu, "Option 1", func);

	AddTitle(WeaponsMenu, MenuBase, "Weapons Menu");
	AddOption(WeaponsMenu, "Assault Rifles", ChangeMenu, AssaultRifles);
	AddOption(WeaponsMenu, "Sub Machine Guns", ChangeMenu, SubMachineGuns);
	AddOption(WeaponsMenu, "Light Machine Guns", ChangeMenu, LightMachineGuns);
	AddOption(WeaponsMenu, "Shotguns", ChangeMenu, Shotguns);
	AddOption(WeaponsMenu, "Pistols", ChangeMenu, Pistols);
	AddOption(WeaponsMenu, "Snipers", ChangeMenu, Snipers);
	AddOption(WeaponsMenu, "Launchers", ChangeMenu, Launchers);
	AddOption(WeaponsMenu, "Specials", ChangeMenu, Specials);

	AddTitle(Snipers, WeaponsMenu, "");
	AddOption(Snipers, "Locus", GiveWeapon, "sniper_fastbolt_zm");
	AddOption(Snipers, "Drakon", GiveWeapon, "sniper_fastsemi_zm");
	AddOption(Snipers, "SVG-100", GiveWeapon, "sniper_powerbolt_zm");
	AddOption(Snipers, "Arrhythmic Dirge", GiveWeapon, "sniper_fastbolt_upgraded_zm");
	AddOption(Snipers, "Bahamut", GiveWeapon, "sniper_fastsemi_upgraded_zm");
	AddOption(Snipers, "Ikken Hissatsu", GiveWeapon, "sniper_powerbolt_upgraded_zm");

	AddTitle(LightMachineGuns, WeaponsMenu, "");
	AddOption(LightMachineGuns, "BRM", GiveWeapon, "lmg_light_zm");
	AddOption(LightMachineGuns, "Dingo", GiveWeapon, "lmg_cqb_zm");
	AddOption(LightMachineGuns, "48 Dredge", GiveWeapon, "lmg_heavy_zm");
	AddOption(LightMachineGuns, "Gorgon", GiveWeapon, "lmg_slowfire_zm");
	AddOption(LightMachineGuns, "Dire Wolf", GiveWeapon, "lmg_cqb_upgraded_zm");
	AddOption(LightMachineGuns, "Trapezoherdon Shard", GiveWeapon, "lmg_heavy_upgraded_zm");
	AddOption(LightMachineGuns, "Blight Oblivion", GiveWeapon, "lmg_light_upgraded_zm");
	AddOption(LightMachineGuns, "Athena's Spear", GiveWeapon, "lmg_slowfire_upgraded_zm");

	AddTitle(SubMachineGuns, WeaponsMenu, "");
	AddOption(SubMachineGuns, "Vesper", GiveWeapon, "smg_fastfire_zm");
	AddOption(SubMachineGuns, "VMP", GiveWeapon, "smg_versatile_zm");
	AddOption(SubMachineGuns, "Bootlegger", GiveWeapon, "smg_sten_zm");
	AddOption(SubMachineGuns, "Kuda", GiveWeapon, "smg_standard_zm");
	AddOption(SubMachineGuns, "Pharo", GiveWeapon, "smg_burst_zm");
	AddOption(SubMachineGuns, "Weevil", GiveWeapon, "smg_capacity_zm");
	AddOption(SubMachineGuns, "Razorback", GiveWeapon, "smg_longrange_zm");
	AddOption(SubMachineGuns, "Crocuta", GiveWeapon, "smg_standard_upgraded_zm");
	AddOption(SubMachineGuns, "Regurgitator", GiveWeapon, "smg_burst_upgraded_zm");
	AddOption(SubMachineGuns, "Infernus", GiveWeapon, "smg_fastfire_upgraded_zm");
	AddOption(SubMachineGuns, "Impaler", GiveWeapon, "smg_versatile_upgraded_zm");
	AddOption(SubMachineGuns, "Barrage", GiveWeapon, "smg_capacity_upgraded_zm");
	AddOption(SubMachineGuns, "Ein Sten", GiveWeapon, "smg_sten_upgraded_zm");

	AddTitle(Launchers, WeaponsMenu, "");
	AddOption(Launchers, "XM-53", GiveWeapon, "launcher_standard_zm");
	AddOption(Launchers, "Incandescence", GiveWeapon, "launcher_standard_upgraded_zm");

	AddTitle(Specials, WeaponsMenu, "");
	AddOption(Specials, "Combat Knife", GiveWeapon, "knife_loadout_zm");
	AddOption(Specials, "DEFAULTWEAPON", GiveWeapon, "defaultweapon");
	AddOption(Specials, "BASEWEAPON", GiveWeapon, "baseweapon");
	AddOption(Specials, "Kor-Maroth", GiveWeapon, "idgun_0_zm");
	AddOption(Specials, "Mar-Astagua", GiveWeapon, "idgun_1_zm");
	AddOption(Specials, "Nar-Ullaqua", GiveWeapon, "idgun_2_zm");
	AddOption(Specials, "Lor-Zarozzor", GiveWeapon, "idgun_3_zm");
	AddOption(Specials, "Kor-Maroth Arbgwaoth", GiveWeapon, "idgun_upgraded_0_zm");
	AddOption(Specials, "Mar-Astagua Arbgwaoth", GiveWeapon, "idgun_upgraded_1_zm");
	AddOption(Specials, "Nar-Ullaqua Arbgwaoth", GiveWeapon, "idgun_upgraded_2_zm");
	AddOption(Specials, "Lor-Zarozzor Arbgwaoth", GiveWeapon, "idgun_upgraded_3_zm");
	AddOption(Specials, "Death Machine", GiveWeapon, "minigun_zm");
	AddOption(Specials, "Porter's X2 Ray Gun", GiveWeapon, "ray_gun_upgraded_zm");
	AddOption(Specials, "Ray Gun", GiveWeapon, "ray_gun_zm");
	AddOption(Specials, "Wunderwaffe DG-3 JZ", GiveWeapon, "tesla_gun_upgraded_zm");
	AddOption(Specials, "Wunderwaffe DG-2", GiveWeapon, "tesla_gun_zm");
	AddOption(Specials, "Beast Arms", GiveWeapon, "zombie_beast_grapple_dwr_zm");

	AddTitle(Pistols, WeaponsMenu, "");
	AddOption(Pistols, "MR6", GiveWeapon, "pistol_standard_zm");
	AddOption(Pistols, "Rk5", GiveWeapon, "pistol_burst_zm");
	AddOption(Pistols, "L-CAR 9", GiveWeapon, "pistol_fullauto_zm");
	AddOption(Pistols, "Death & Taxes", GiveWeapon, "pistol_standard_upgraded_zm");
	AddOption(Pistols, "Rex-Kalibur 115", GiveWeapon, "pistol_burst_upgraded_zm");
	AddOption(Pistols, "Flux Collider 935", GiveWeapon, "pistol_fullauto_upgraded_zm");
	AddOption(Pistols, "Meat Wagon", GiveWeapon, "pistol_revolver38_upgraded_zm");

	AddTitle(AssaultRifles, WeaponsMenu, "");
	AddOption(AssaultRifles, "KN-44", GiveWeapon, "ar_standard_companion_zm");
	AddOption(AssaultRifles, "Anointed Avenger", GiveWeapon, "ar_standard_upgraded_companion_zm");
	AddOption(AssaultRifles, "ICR-1", GiveWeapon, "ar_accurate_zm");
	AddOption(AssaultRifles, "LN-44", GiveWeapon, "ar_standard_zm");
	AddOption(AssaultRifles, "M8A7", GiveWeapon, "ar_longburst_zm");
	AddOption(AssaultRifles, "Sheiva", GiveWeapon, "ar_marksman_zm");
	AddOption(AssaultRifles, "HVK-30", GiveWeapon, "ar_cqb_zm");
	AddOption(AssaultRifles, "Man-o-War", GiveWeapon, "ar_damage_zm");
	AddOption(AssaultRifles, "XR-2", GiveWeapon, "ar_fastburst_zm");
	AddOption(AssaultRifles, "Anointed Avenger", GiveWeapon, "ar_standard_upgraded_zm");
	AddOption(AssaultRifles, "Illuminated Deanimator", GiveWeapon, "ar_accurate_upgraded_zm");
	AddOption(AssaultRifles, "HVK", GiveWeapon, "ar_cqb_upgraded_zm");
	AddOption(AssaultRifles, "Dread Armada", GiveWeapon, "ar_damage_upgraded_zm");
	AddOption(AssaultRifles, "The Unspeakable", GiveWeapon, "ar_longburst_upgraded_zm");
	AddOption(AssaultRifles, "Cumulus Struggle", GiveWeapon, "ar_marksman_upgraded_zm");

	AddTitle(Shotguns, WeaponsMenu, "");
	AddOption(Shotguns, "KRM-262", GiveWeapon, "shotgun_pump_zm");
	AddOption(Shotguns, "Argus", GiveWeapon, "shotgun_precision_zm");
	AddOption(Shotguns, "Brecci 205", GiveWeapon, "shotgun_semiauto_zm");
	AddOption(Shotguns, "Haymaker 12", GiveWeapon, "shotgun_fullauto_zm");
	AddOption(Shotguns, "Shoeshining 100", GiveWeapon, "shotgun_fullauto_upgraded_zm");
	AddOption(Shotguns, "Ancient Messenger", GiveWeapon, "shotgun_precision_upgraded_zm");
	AddOption(Shotguns, "Dragon's Glare", GiveWeapon, "shotgun_pump_upgraded_zm");
	AddOption(Shotguns, "Stellar Screech", GiveWeapon, "shotgun_semiauto_upgraded_zm");

	AddTitle(GobbleGumsMenu, MenuBase, "GobbleGums Menu");
	AddOption(GobbleGumsMenu, "Perk-A-Holic", give_gobblegum, "zm_bgb_perkaholic");
	AddOption(GobbleGumsMenu, "Ephemeral Enhancement", give_gobblegum, "zm_bgb_ephemeral_enhancement");
	AddOption(GobbleGumsMenu, "Gobblegum Test", give_gobblegum, "zm_bgb_armamental_accomplishment");

	AddTitle(PlayersMenu, MenuBase, "Players Menu");
	AddOption(PlayersMenu, getName(0), ChangeMenu, CurrentPlayer);
	AddOption(PlayersMenu, getName(1), ChangeMenu, CurrentPlayer);
	AddOption(PlayersMenu, getName(2), ChangeMenu, CurrentPlayer);
	AddOption(PlayersMenu, getName(3), ChangeMenu, CurrentPlayer);

	AddTitle(CurrentPlayer, PlayersMenu, "Edit Player");
	AddOption(CurrentPlayer, "Give 10000 Points", giveclientpoints, "10000");
	AddOption(CurrentPlayer, "Take 10000 Points", giveclientpoints, "-10000");

	//AddOption(0, "Unlock All Challenges", UnlockAllChallenges);
	//AddOption(0, "Set Box Cost: 10", set_treasure_chest_cost, "10");
	//AddOption(0, "Set Zombie Vars", SetZombieVars);
	//AddOption(0, "Perk-A-Holic", give_gobblegum, "zm_bgb_perkaholic");
	//AddOption(0, "Ephemeral Enhancement", give_gobblegum, "zm_bgb_ephemeral_enhancement");
	//AddOption(0, "Gobblegum Test", give_gobblegum, "zm_bgb_armamental_accomplishment");
}

bool Clients::AttackButtonPressed() {
	if (g_clients[ClientNumber].curCmd.button_bits[0] & BUTTON_RSHLDR) {
		return true;
	}
	return false;
}
bool Clients::AdsButtonPressed() {
	if (g_clients[ClientNumber].curCmd.button_bits[0] & BUTTON_LSHLDR) {
		return true;
	}
	return false;
}
bool Clients::JumpButtonPressed() {
	if (g_clients[ClientNumber].curCmd.button_bits[0] & BUTTON_A) {
		return true;
	}
	return false;
}
bool Clients::StanceButtonPressed() {
	if (g_clients[ClientNumber].curCmd.button_bits[1] & BUTTON_B) {
		return true;
	}
	return false;
}
bool Clients::ChangeSeatButtonPressed() {
	if (g_clients[ClientNumber].curCmd.button_bits[0] & BUTTON_Y) {
		return true;
	}
	return false;
}
bool Clients::MeleeButtonPressed() {
	if (g_clients[ClientNumber].curCmd.button_bits[0] & BUTTON_RSTICK) {
		return true;
	}
	return false;
}
bool Clients::FragButtonPressed() {
	if (g_clients[ClientNumber].curCmd.button_bits[0] & BUTTON_RTRIG) {
		return true;
	}
	return false;
}
bool Clients::SprintButtonPressed() {
	if (g_clients[ClientNumber].curCmd.button_bits[0] & BUTTON_LSTICK) {
		return true;
	}
	return false;
}
bool Clients::UseButtonPressed() {
	if (g_clients[ClientNumber].curCmd.button_bits[0] & BUTTON_X) {
		return true;
	}
	return false;
}
bool Clients::ActionslotOneButtonPressed() {
	if (g_clients[ClientNumber].curCmd.button_bits[1] & DPAD_UP) {
		return true;
	}
	return false;
}
bool Clients::ActionslotTwoButtonPressed() {
	if (g_clients[ClientNumber].curCmd.button_bits[1] & DPAD_DOWN) {
		return true;
	}
	return false;
}
bool Clients::ActionslotThreeButtonPressed() {
	if (g_clients[ClientNumber].curCmd.button_bits[1] & DPAD_LEFT) {
		return true;
	}
	return false;
}
bool Clients::ActionslotFourButtonPressed() {
	if (g_clients[ClientNumber].curCmd.button_bits[1] & DPAD_RIGHT) {
		return true;
	}
	return false;
}

void givepoints(int clientNum, const char * points) {
	g_clients[clientNum].score += atoi(points);
}
void giveclientpoints(int clientNum, int targetClientNum, const char * points) {
	g_clients[targetClientNum].score += atoi(points);
}

void GiveWeapon(int clientNum, const char * weapon) {
	int weapIndex = G_GetWeaponIndex(weapon);
	BG_TakePlayerWeapon(g_entities[clientNum].ps, g_entities[clientNum].ps->currentWeapon, 0);
	if (G_GivePlayerWeapon(&g_entities[clientNum], g_entities[clientNum].ps, weapIndex, 1, 0)) {
		Add_Ammo(&g_entities[clientNum], weapIndex, 999, 1, 0);
		SV_GameSendServerCommand(clientNum, 0, va("h %i", weapIndex));
	}
}
