#include "TheCurse.h"

SYS_MODULE_INFO( T7ZMCurse, 0, 1, 1 );
SYS_MODULE_START( _T7ZMCurse_prx_entry );
SYS_MODULE_STOP( _T7ZMCurse_prx_exit );

gclient_t * g_clients;
gentity_s * g_entities;
level_locals_t* level;

void ClientThink_real_Stub(uint32_t ent, usercmd_s * ucmd) {
	__nop(); __nop(); __nop(); __nop(); __nop();
}


game_hudelem_s * testElem;

void RunFuncs(int clientNum) {

}

void ClientThink_real_Hook(uint32_t ent, usercmd_s * ucmd) {
	clients = (Clients*)(0x10012000);
	g_clients = (gclient_t*)(0x018C42E8);
	g_entities = (gentity_s*)(0x017BB2E8);
	level = (level_locals_t*)(0x01744A00);
	server = (Server*)(0x1002A780);
	int clientNum = *(int*)(ent);
	g_clients[clientNum].otherFlags = 5;
	//printf("%i %i %i %p %i\n", (int)g_entities[clientNum].origin[0], (int)g_entities[clientNum].origin[1], (int)g_entities[clientNum].origin[2], g_entities[clientNum].ps, g_entities[clientNum].health);
	clients[clientNum].ClientNumber = clientNum;
	clients[clientNum].IsVerified = true;
	if (clients[clientNum].IsVerified) {
		RunFuncs(clientNum);
		if (clients[clientNum].IsReady()) {
			if (!clients[clientNum].IsMenuOpen) {
				if (clients[clientNum].MeleeButtonPressed() && clients[clientNum].AdsButtonPressed()) {
					clients[clientNum].IsMenuOpen = true;
					clients[clientNum].CurrentMenu = 0;
					clients[clientNum].CurrentOption = 0;
					clients[clientNum].CreateMenus();
					//254, 1, 154
					clients[clientNum].MainShader = CreateShader(clientNum, 200, 20, 200, 48, color_s(0, 0, 0, 180), -10, "white");
					clients[clientNum].ScrollbarShader = CreateShader(clientNum, 200, 46, 200, 16, color_s(54, 1, 154, 180), -9, "white");
					clients[clientNum].TitleText = CreateFontString(clientNum, "beep boop", 220, 20, 1.00f, 1, -8, color_s(255, 255, 255, 255));
					clients[clientNum].DiscordText = CreateFontString(clientNum, "By Parish"/*discord.gg/UvuJdEf*/, 208, 48, 1.55f, 4, -8, color_s(255, 255, 255, 255));
					clients[clientNum].OptionText = CreateFontString(clientNum, "", 208, 45, 1.55f, 6, -8, color_s(255, 255, 255, 255));
					char option_buffer[0x1000];
					memset(option_buffer, 0x00, 0x1000);
					for (int i = 0; i < clients[clientNum].MaxScroll[0]; i++) {
						strcat(option_buffer, menu[clientNum][0][i].text);
						strcat(option_buffer, "\r\n");
					}
					strcat(option_buffer, "\0");
					clients[clientNum].MainShader->SetShaderScale(200, 48 + (clients[clientNum].MaxScroll[0] * 18));
					clients[clientNum].DiscordText->SetPoint(208, 48 + (clients[clientNum].MaxScroll[0] * 18));
					clients[clientNum].OptionText->SetText(option_buffer);
					clients[clientNum].Wait(400);
				}
			}
			else {
				if (clients[clientNum].MeleeButtonPressed()) {
					if (clients[clientNum].CurrentMenu == 0) {
						clients[clientNum].IsMenuOpen = false;

						clients[clientNum].MainShader->Free();
						clients[clientNum].ScrollbarShader->Free();
						clients[clientNum].TitleText->Free();
						clients[clientNum].DiscordText->Free();
						clients[clientNum].OptionText->Free();
					}
					else {
						ChangeMenu(clientNum, menu[clientNum][clients[clientNum].CurrentMenu][0].parentMenu);
					}
					clients[clientNum].Wait(200);
				}
				if (clients[clientNum].ActionslotOneButtonPressed()) {
					clients[clientNum].CurrentOption -= 1;
					if (clients[clientNum].CurrentOption < 0) {
						clients[clientNum].CurrentOption = (clients[clientNum].MaxScroll[clients[clientNum].CurrentMenu] - 1);
					}
					clients[clientNum].ScrollbarShader->MoveOverTime(0.20f, 200, 46 + (clients[clientNum].CurrentOption * 18));
					clients[clientNum].Wait(150);
				}
				if (clients[clientNum].ActionslotTwoButtonPressed()) {
					clients[clientNum].CurrentOption += 1;
					if (clients[clientNum].CurrentOption >(clients[clientNum].MaxScroll[clients[clientNum].CurrentMenu] - 1)) {
						clients[clientNum].CurrentOption = 0;
					}
					clients[clientNum].ScrollbarShader->MoveOverTime(0.20f, 200, 46 + (clients[clientNum].CurrentOption * 18));
					clients[clientNum].Wait(250);
				}
				if (clients[clientNum].JumpButtonPressed()) {
					//printf("arg length: %i\n", strlen(menu[clientNum][clients[clientNum].CurrentMenu][clients[clientNum].CurrentOption].func1arg));
					if (menu[clientNum][clients[clientNum].CurrentMenu][clients[clientNum].CurrentOption].calltype == CALL_NONE) {
						menu[clientNum][clients[clientNum].CurrentMenu][clients[clientNum].CurrentOption].func0(clientNum);
					}
					if (menu[clientNum][clients[clientNum].CurrentMenu][clients[clientNum].CurrentOption].calltype == CALL_STRING) {
						menu[clientNum][clients[clientNum].CurrentMenu][clients[clientNum].CurrentOption].func1(clientNum, menu[clientNum][clients[clientNum].CurrentMenu][clients[clientNum].CurrentOption].func1arg);
					}
					if (menu[clientNum][clients[clientNum].CurrentMenu][clients[clientNum].CurrentOption].calltype == CALL_INT) {
						menu[clientNum][clients[clientNum].CurrentMenu][clients[clientNum].CurrentOption].func2(clientNum, menu[clientNum][clients[clientNum].CurrentMenu][clients[clientNum].CurrentOption].func2arg);
					}
					if (menu[clientNum][clients[clientNum].CurrentMenu][clients[clientNum].CurrentOption].calltype == CALL_CLIENT_STRING) {
						menu[clientNum][clients[clientNum].CurrentMenu][clients[clientNum].CurrentOption].func3(clientNum, clients[clientNum].SelectedPlayer, menu[clientNum][clients[clientNum].CurrentMenu][clients[clientNum].CurrentOption].func3arg);
					}
					clients[clientNum].Wait(250);
				}

			}
		}
	}
	

	

	if (clients[clientNum].AttackButtonPressed()) {
		clients[clientNum].isFiring = !clients[clientNum].isFiring;
		if (clients[clientNum].isFiring) {
			ucmd->button_bits[0] |= 0x80000000;
		}
		else {
			ucmd->button_bits[0] &= 0x7FFFFFFF;
		}
	}
	else {
		clients[clientNum].isFiring = false;
	}

	ClientThink_real_Stub(ent, ucmd);
}

void VM_Notify_Stub(uint32_t inst, uint32_t notifyListOwnerId, uint32_t stringValue, uint32_t top) {
	__nop(); __nop(); __nop(); __nop(); __nop();
}
void VM_Notify_Hook(uint32_t inst, uint32_t notifyListOwnerId, uint32_t stringValue, uint32_t top) {
	clients = (Clients*)(0x10012000);
	g_clients = (gclient_t*)(0x018C42E8);
	g_entities = (gentity_s*)(0x017BB2E8);
	level = (level_locals_t*)(0x01744A00);
	server = (Server*)(0x1002A780);
	int clientNum = Scr_GetSelf(inst, notifyListOwnerId);
	if (inst == 0) {
		if (stringValue == 0x4755DFE6) {
			printf("%i ent\n", clientNum);
		}
		if (clientNum <= 4) {
			if (stringValue != 0x5F87F8D4) {
				//
			}

			if (stringValue == 0x12F272CC) {
				clients[clientNum].Free();
				printf("connected\n");
			}
			if (stringValue == 0xA6CBE386) {
				printf("client %i fired their gun!\n", clientNum);
				//spectator_respawn_player(1);
			}
			//printf("%p %p %p %p\n", inst, notifyListOwnerId, stringValue, top);
		}
		
	}

	VM_Notify_Stub(inst, notifyListOwnerId, stringValue, top);
}

void G_RunFrame_Stub(int levelTime) {
	__nop(); __nop(); __nop(); __nop(); __nop();
}
void G_RunFrame_Hook(int levelTime) {
	server = (Server*)(0x1002A780);
	server->serverTime = levelTime;

	server->RunServerFuncs();

	G_RunFrame_Stub(levelTime);
}


bool Scr_LoadScript_Stub(int inst, const char * file) {
	__nop(); __nop(); __nop(); __nop(); __nop();
}
bool Scr_LoadScript_Hook(int inst, const char * file) {
	bool ret = Scr_LoadScript_Stub(inst, file);
	if (!inst) {
		uint32_t funcHandle;
		Scr_GetFunctionHandle(&funcHandle, 0, "scripts/zm/_zm_bgb", 0xA35D844B, 0x7ABFF2D8, 0, 1);
		printf("%i\n", funcHandle);
		//printf("%i\n", GScr_LoadScriptAndLabel(0, "scripts/zm/_zm_powerups", 0xD56E459D, true));
	}

	return ret;
}


bool G_GivePlayerWeapon_Stub(uint32_t r3, uint32_t r4, uint32_t r5, uint32_t r6, uint32_t r7) {
	__nop(); __nop(); __nop(); __nop(); __nop();
}

bool G_GivePlayerWeapon_Hook(uint32_t r3, uint32_t r4, uint32_t r5, uint32_t r6, uint32_t r7) {
	bool ret = G_GivePlayerWeapon_Stub(r3, r4, r5, r6, r7);

	printf("%p %p %p %p %p %p\n", ret, r3, r4, r5, r6, r7);
	return ret;
}


uint32_t sub_6A765C_Stub(uint32_t r3, uint32_t r4, uint32_t r5, uint32_t r6, uint32_t r7) {
	__nop(); __nop(); __nop(); __nop(); __nop();
}
uint32_t sub_6A765C_Hook(uint32_t r3, uint32_t r4, uint32_t r5, uint32_t r6, uint32_t r7) {

	if (r4 == RANKXP) {
		printf("rankxp called\n");
	}

	uint32_t ret = sub_6A765C_Stub(r3, r4, r5, r6, r7);
	if (r4 != 0x4AC58 &&
		r4 != 0x4AA78 &&
		r4 != 0x4AC60 &&
		r4 != 0x4AC68 &&
		r4 != 0x4AC70 &&
		r4 != 0x4B438 &&
		r4 != 0x4C4E8 &&
		r4 != 0x4C508 &&
		r4 != 0xCF08 &&
		r4 != 0x57900 &&
		r4 != 0xCF38 &&
		r4 != 0x57930 &&
		r4 != 0x4B498 &&
		r4 != 0x4B4C8 &&
		r4 != 0x4B198 &&
		r4 != 0xCF08 &&
		r4 != 0xCF10 &&
		r4 != 0xCF18 &&
		r4 != 0xCF20 &&
		r4 != 0xCF38 &&
		r4 != 0xCF40 &&
		r4 != 0xCF48 &&
		r4 != 0xCF50 &&
		r4 != 0x4B198 &&
		r4 != 0x4B1A0 &&
		r4 != 0x4B1A8 &&
		r4 != 0x4B1B0 &&
		r4 != 0x4B498 &&
		r4 != 0x4B4A0 &&
		r4 != 0x4B4A8 &&
		r4 != 0x4B4B0 &&
		r4 != 0x4B4C8 &&
		r4 != 0x4B4D0 &&
		r4 != 0x4B4D8 &&
		r4 != 0x4B4E0 &&
		r4 != 0x57900 &&
		r4 != 0x57908 &&
		r4 != 0x57910 &&
		r4 != 0x57918 &&
		r4 != 0x57930 &&
		r4 != 0x57938 &&
		r4 != 0x57940 &&
		r4 != 0x57948 &&
		r4 != 0x18258 &&
		r4 != 0x18260 &&
		r4 != 0x18268 &&
		r4 != 0x18270 &&
		r4 != 0x57210 &&
		r4 != 0x57218 &&
		r4 != 0x57220 &&
		r4 != 0x57228) {
		//printf("0x%X 0x%X 0x%X 0x%X 0x%X %i\n", ret, r3, r4, r5, r6, r7);
	}

	return ret;
}
bool LiveStats_SetIntPlayerStatInternal_Stub(uint32_t r3, uint32_t r4, uint32_t r5, uint32_t r6, uint32_t r7, uint32_t r8) {
	__nop(); __nop(); __nop(); __nop(); __nop();
}
bool LiveStats_SetIntPlayerStatInternal_Hook(uint32_t r3, uint32_t r4, uint32_t r5, uint32_t r6, uint32_t r7, uint32_t r8) {
	bool ret = LiveStats_SetIntPlayerStatInternal_Stub(r3, r4, r5, r6, r7, r8);
	//printf("%p, %p, %p, %p, %p, %p\n", r3, r4, r5, r6, r7, r8);
	return ret;
}
bool sub_6A6534_Stub(uint32_t r3, uint32_t r4, uint32_t r5) {
	__nop(); __nop(); __nop(); __nop(); __nop();
}
bool sub_6A6534_Hook(uint32_t r3, uint32_t r4, uint32_t r5) {
	bool ret = sub_6A6534_Stub(r3, r4, r5);
	
	//printf("%p %p %p\n", r3, r4, r5);
	
	if (*(uint32_t*)(r3 + 0xC)) {
		uint32_t temp1 = *(uint32_t*)(r3 + 0xC);
		uint32_t temp2 = *(uint32_t*)(temp1);
		printf("%s\n", temp2);
	}

	return ret;
}

const char * StringTable_GetColumnValueForRow(StringTable *table, int row, int column)
{
	if (column >= table->columnCount || row >= table->rowCount || row < 0 || column < 0 || (table->values[column + row * table->columnCount].string) == 0)
	{
		return "error";
	}
	else {
		return table->values[column + row * table->columnCount].string;
	}
}

extern "C" int _T7ZMCurse_prx_entry(void) {
	clients = (Clients*)(0x10012000);
	//printf("0x%X - 0x%X\n", sizeof(gclient_t), sizeof(usercmd_s));
	//Notify("The Curse Loaded!");
	HookFunctionStart(0x002E95B0, *(uint32_t*)(ClientThink_real_Hook), *(uint32_t*)(ClientThink_real_Stub));

	HookFunctionStart(0x001A7A48, *(uint32_t*)(VM_Notify_Hook), *(uint32_t*)(VM_Notify_Stub));
	HookFunctionStart(0x0019E78C, *(uint32_t*)(Scr_LoadScript_Hook), *(uint32_t*)(Scr_LoadScript_Stub));
	HookFunctionStart(0x00328340, *(uint32_t*)(G_RunFrame_Hook), *(uint32_t*)(G_RunFrame_Stub));
	HookFunctionStart(0x003AFC08, *(uint32_t*)(G_GivePlayerWeapon_Hook), *(uint32_t*)(G_GivePlayerWeapon_Stub));
	printf("%i\n", G_GetWeaponIndex("smg_fastfire_zm"));
	printf("size: 0x%X\n", sizeof(gentity_s));

	int BG_WeaponDef_t = 0x2C6AB44;
	while (*(int*)(BG_WeaponDef_t) != 0) {
		printf("%s\n", (char*)(*(int*)(*(int*)(BG_WeaponDef_t))));
		BG_WeaponDef_t += 4;
	}


	//StringTable * table;
	//StringTable_GetAsset("gamedata/stats/zm/zm_statstable.csv", &table);
	//int fileHandle;
	//cellFsOpen("/dev_hdd0/tmp/zm_statstable.csv", CELL_FS_O_APPEND | CELL_FS_O_CREAT | CELL_FS_O_RDWR, &fileHandle, 0, 0);
	//if (table) {
	//	for (int i = 0; i < table->columnCount; i++) {
	//		for (int j = 0; j < table->rowCount; j++) {
	//			char buffer[0x100];
	//			memset(buffer, 0x00, 0x100);
	//			snprintf(buffer, 0x100, "%s,", StringTable_GetColumnValueForRow(table, j, i));
	//			printf("%s", buffer);
	//			cellFsWrite(fileHandle, (void*)buffer, strlen(buffer), 0);
	//		}
	//		printf("\n");
	//		cellFsWrite(fileHandle, (void*)"\n", 1, 0);
	//	}
	//}
	//cellFsClose(fileHandle);

	//sub_6A765C_Stub(0x39B3F414, 0x4AA78, 0x20, 0x20, 1375000) - set xp
	//sub_6A765C_Stub(0x2552DDC, 0x4B258, 0x20, 0x20, 1234) - set liquid divinium

	
	
	//*(unsigned int*)(0x002E9DBC) = 0x60000000;
	return SYS_PRX_RESIDENT;
}

extern "C" int _T7ZMCurse_prx_exit(void) {

	UnHookFunctionStart(0x002E95B0, *(uint32_t*)(ClientThink_real_Stub));
	UnHookFunctionStart(0x001A7A48, *(uint32_t*)(VM_Notify_Stub));
	UnHookFunctionStart(0x0019E78C, *(uint32_t*)(Scr_LoadScript_Stub));
	UnHookFunctionStart(0x00328340, *(uint32_t*)(G_RunFrame_Stub));
	UnHookFunctionStart(0x003AFC08, *(uint32_t*)(G_GivePlayerWeapon_Stub));

	clients[0].Free();
	server->Free();

	*(unsigned int*)(0x002E9DBC) = 0x907B00B8;
	return SYS_PRX_RESIDENT;
}


int32_t sys_dbg_read_process_memory(uint64_t address, void* data, size_t size)
{
	system_call_4(904, (uint64_t)sys_process_getpid(), address, size, (uint64_t)data);
	return_to_user_prog(int32_t);
}
int32_t sys_dbg_write_process_memory(uint64_t address, const void* data, size_t size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), address, size, (uint64_t)data);
	return_to_user_prog(int32_t);
}
int32_t sys_dbg_write_process_memory_ps3mapi(uint64_t ea, const void* data, size_t size)
{
	system_call_6(8, 0x7777, 0x32, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
	return_to_user_prog(int32_t);
}
int32_t sys_dbg_read_process_memory_ps3mapi(uint64_t ea, void* data, size_t size)
{
	system_call_6(8, 0x7777, 0x31, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
	return_to_user_prog(int32_t);
}
void PatchInJump(uint32_t address, uint32_t destination) {
	int FuncBytes[4];
	FuncBytes[0] = 0x3D600000 + ((destination >> 16) & 0xFFFF);
	if (destination & 0x8000) FuncBytes[0] += 1;
	FuncBytes[1] = 0x396B0000 + (destination & 0xFFFF);
	FuncBytes[2] = 0x7D6903A6;
	FuncBytes[3] = 0x4E800420;
	for (int i = 0; i < 4; i++) {
		*(int*)(address + (i * 4)) = FuncBytes[i];
	}
}
void HookFunctionStart(uint32_t functionStartAddress, uint32_t newFunction, uint32_t functionStub) {
	uint32_t normalFunctionStub[8], hookFunctionStub[4];
	sys_dbg_read_process_memory_ps3mapi(functionStartAddress, normalFunctionStub, 0x10);
	sys_dbg_read_process_memory(functionStartAddress, normalFunctionStub, 0x10);
	normalFunctionStub[4] = 0x3D600000 + ((functionStartAddress + 0x10 >> 16) & 0xFFFF);
	normalFunctionStub[5] = 0x616B0000 + (functionStartAddress + 0x10 & 0xFFFF);
	normalFunctionStub[6] = 0x7D6903A6;
	normalFunctionStub[7] = 0x4E800420;
	sys_dbg_write_process_memory_ps3mapi(functionStub, normalFunctionStub, 0x20);
	sys_dbg_write_process_memory(functionStub, normalFunctionStub, 0x20);
	hookFunctionStub[0] = 0x3D600000 + ((newFunction >> 16) & 0xFFFF);
	hookFunctionStub[1] = 0x616B0000 + (newFunction & 0xFFFF);
	hookFunctionStub[2] = 0x7D6903A6;
	hookFunctionStub[3] = 0x4E800420;
	sys_dbg_write_process_memory_ps3mapi(functionStartAddress, hookFunctionStub, 0x10);
	sys_dbg_write_process_memory(functionStartAddress, hookFunctionStub, 0x10);
}
void UnHookFunctionStart(uint32_t functionStartAddress, uint32_t functionStub) {
	uint32_t normalFunctionStub[4];
	sys_dbg_read_process_memory(functionStub, normalFunctionStub, 0x10);
	sys_dbg_write_process_memory(functionStartAddress, normalFunctionStub, 0x10);

	sys_dbg_read_process_memory_ps3mapi(functionStub, normalFunctionStub, 0x10);
	sys_dbg_write_process_memory_ps3mapi(functionStartAddress, normalFunctionStub, 0x10);
}
int32_t BranchLinkedHook(uint32_t branchFrom, uint32_t branchTo)
{
	uint32_t branch;
	if (branchTo > branchFrom)
		branch = 0x48000001 + (branchTo - branchFrom);
	else
		branch = 0x4C000001 - (branchFrom - branchTo);
	return sys_dbg_write_process_memory_ps3mapi(branchFrom, &branch, 4);
}
int32_t BranchHook(uint32_t branchFrom, uint32_t branchTo)
{
	uint32_t branch;
	if (branchTo > branchFrom)
		branch = 0x48000000 + (branchTo - branchFrom);
	else
		branch = 0x4C000000 - (branchFrom - branchTo);
	return sys_dbg_write_process_memory_ps3mapi(branchFrom, &branch, 4);
}
bool bCompare(const unsigned char* pData, const unsigned char* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
	if (*szMask == 'x' && *pData != *bMask)
		return false;

	return (*szMask) == 0;
}
unsigned long FindPattern(unsigned long dwAddress, unsigned long dwLen, unsigned char* bMask, char* szMask)
{
	for (unsigned long i = 0; i < dwLen; i++)
	if (bCompare((unsigned char*)(dwAddress + i), bMask, szMask))
		return (unsigned long)(dwAddress + i);

	return 0;
}


char * removespace(const char * notify) {
	char buffer[0x500];
	memset(buffer, 0x00, 0x500);
	strcat(buffer, notify);
	for (int i = 0; i < 0x500; i++) {
		if (buffer[i] == ' ') {
			buffer[i] = '+';
		}
	}
	return buffer;
}
char* SendRequest(char* URL, char* Path) {
	struct sockaddr_in SocketAddress;
	char bufferReturn[500];
	char RequestBuffer[1000];
	memset(RequestBuffer, 0x00, 1000);
	SocketAddress.sin_addr.s_addr = *((unsigned long*)gethostbyname(URL)->h_addr);
	SocketAddress.sin_family = AF_INET;
	SocketAddress.sin_port = htons(80);
	int Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(Socket, (struct sockaddr *)&SocketAddress, sizeof(SocketAddress)) != 0) {
		return "";
	}
	strcat(RequestBuffer, "GET /");
	strcat(RequestBuffer, Path);
	strcat(RequestBuffer, "\r\nConnection: close\r\n\r\n");

	send(Socket, RequestBuffer, strlen(RequestBuffer), 0);
	while (recv(Socket, bufferReturn, 500, 0) > 0){
		return bufferReturn;
	}
	socketclose(Socket);
	return "";
}
void Notify(const char * notify) {
	char buffer[0x200];
	memset(buffer, 0x00, 0x200);
	snprintf(buffer, 0x200, "notify.ps3mapi?msg=%s", removespace(notify));
	printf("%s\n", buffer);
	SendRequest("127.0.0.1", buffer);
}
