#pragma once
#include "TheCurse.h"

void ChangeMenu(int clientNum, int menu);

enum MenuNumbers {
	MenuBase,
	SelfMenu,
	WeaponsMenu,
	GobbleGumsMenu,
	AccountMenu,
	PointsMenu,
	PlayersMenu,
	AllPlayersMenu,
	CurrentPlayer,
	AssaultRifles,
	Shotguns,
	Snipers,
	LightMachineGuns,
	Pistols,
	SubMachineGuns,
	Launchers,
	Specials
};

enum CallType {
	CALL_NONE,
	CALL_STRING,
	CALL_INT,
	CALL_CLIENT_STRING,
};

struct Menu {
	int parentMenu;
	const char * title;
	const char * text;
	void(*func0)(int clientNum);
	void(*func1)(int clientNum, const char * arg);
	void(*func2)(int clientNum, int arg);
	void(*func3)(int clientNum, int targetClientNum, const char * arg);
	const char * func1arg;
	int func2arg;
	const char * func3arg;
	CallType calltype;
};

extern Menu menu[4][20][20];
