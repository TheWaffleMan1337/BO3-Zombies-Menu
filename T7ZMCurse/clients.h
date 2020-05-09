#pragma once
#include "TheCurse.h"

struct game_hudelem_s;

struct Clients {
	int ClientNumber;
	int CurrentMenu;
	int CurrentOption;
	int SelectedPlayer;
	int LastOption[20];
	int MaxScroll[20];
	bool IsMenuOpen;
	bool IsVerified;
	int iTick;
	int iWait;
	bool unlockChallenges;
	int unlockChallengesTick;
	bool isFiring;
	game_hudelem_s * MainShader;
	game_hudelem_s * ScrollbarShader;
	game_hudelem_s * OptionText;
	game_hudelem_s * TitleText;
	game_hudelem_s * DiscordText;
	void Free();
	void AddTitle(int menuIndex, int topMenu, const char * title);
	void AddOption(int menuIndex, const char * opt, void(*func)(int clientNum));
	void AddOption(int menuIndex, const char * opt, void(*func)(int clientNum, const char * arg), const char * arg);
	void AddOption(int menuIndex, const char * opt, void(*func)(int clientNum, int arg), int arg);
	void AddOption(int menuIndex, const char * opt, void(*func)(int clientNum, int targetClientNum, const char * arg), const char * arg);

	void Wait(int time);
	bool IsReady();

	void CreateMenus();

	bool AttackButtonPressed();
	bool AdsButtonPressed();
	bool JumpButtonPressed();
	bool StanceButtonPressed();
	bool ChangeSeatButtonPressed();
	bool MeleeButtonPressed();
	bool FragButtonPressed();
	bool SprintButtonPressed();
	bool UseButtonPressed();
	bool ActionslotOneButtonPressed();
	bool ActionslotTwoButtonPressed();
	bool ActionslotThreeButtonPressed();
	bool ActionslotFourButtonPressed();
};

void givepoints(int clientNum, const char * points);
void giveclientpoints(int clientNum, int targetClientNum, const char * points);

void GiveWeapon(int clientNum, const char * weapon);

extern Clients * clients;