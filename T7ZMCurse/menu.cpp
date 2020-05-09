#include "menu.h"

Menu menu[4][20][20];

void ChangeMenu(int clientNum, int menuId) {
	if (menuId == CurrentPlayer) {
		clients[clientNum].SelectedPlayer = clients[clientNum].CurrentOption;
	}
	clients[clientNum].LastOption[clients[clientNum].CurrentMenu] = clients[clientNum].CurrentOption;
	clients[clientNum].CurrentMenu = menuId;
	clients[clientNum].CurrentOption = clients[clientNum].LastOption[menuId];
	char option_buffer[0x1000];
	memset(option_buffer, 0x00, 0x1000);
	for (int i = 0; i < clients[clientNum].MaxScroll[menuId]; i++) {
		strcat(option_buffer, menu[clientNum][menuId][i].text);
		strcat(option_buffer, "\r\n");
	}
	strcat(option_buffer, "\0");
	clients[clientNum].OptionText->SetText(option_buffer);
	clients[clientNum].MainShader->ScaleOverTime(0.18f, 200, 48 + (clients[clientNum].MaxScroll[menuId] * 18));
	clients[clientNum].DiscordText->MoveOverTime(0.18f, 208, 48 + (clients[clientNum].MaxScroll[menuId] * 18));
	clients[clientNum].ScrollbarShader->MoveOverTime(0.20f, 200, 46 + (clients[clientNum].CurrentOption * 18));

}
