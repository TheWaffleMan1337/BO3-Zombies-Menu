#pragma once
#include "TheCurse.h"


struct Server {
	int serverTime;
	bool bConstantDrops;
	int iConstantDropTick;

	void Free();
	void RunServerFuncs();

};

extern Server * server;