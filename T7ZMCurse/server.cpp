#include "server.h"
Server * server;

void Server::Free() {
	memset(this, 0x00, sizeof(Server));
}

void Server::RunServerFuncs() {
	if (isInGame()) {
		if (bConstantDrops) {
			set_zombie_var("zombie_powerup_drop_max_per_round", 99999);
			set_zombie_var("zombie_drop_item", 1);
		}
	}
}

