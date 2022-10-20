#include "Header.h"

Player* user;

void getWinner(int empty_field[10][10]);

void game(Player* current_user, string game_status) {
	user = current_user;
	int coinflip = rand() % 2;
	
	if (game_status == "new game") {
		gmode = pregame_settings(current_user);
		if (gmode == EXIT) return;
	}
	else if (game_status == "load game") {
		loadGame();
		gmode = PLAYER_VS_BOT;
		coinflip = 1;
	}

	do {
		system("cls");
		
		setField(player_field);
		setField(bot_field);

		if (gmode == PLAYER_VS_BOT) {
			if (coinflip) {
				shoot();
				bot_shot(bot1_AI, player_field);
			}
			else {
				bot_shot(bot1_AI, player_field);
				shoot();
			}
		}
		else if (gmode == BOT_VS_BOT) {
			bot_shot(bot1_AI, player_field);
			bot_shot(bot2_AI, bot_field);
		}
	} while (!end());
	_getch();

	clearField(player_field);
	clearField(bot_field);
}

bool end() {
	int(*field)[10][10] = &player_field;
	bool end;
	for (size_t fields = 0; fields < 2; fields++) {
		end = true;
		
		for (size_t x = 0; x < MAP_SIZE; x++) {
			for (size_t y = 0; y < MAP_SIZE; y++) {
				if ((*field)[x][y] == ALIVE) {
					end = false;
				}
			}
		}

		if (end == true) {
			getWinner(*field);
			return true;
		}

		field = &bot_field;
	} 
	return false;
}

void getWinner(int empty_field[10][10]) {
	if (gmode == PLAYER_VS_BOT) {
		if (empty_field == bot_field) {
			SetCursorPosition(30, 2);
			cout << user->login << " переміг!!!";
			user->stats[WINS]++;
		}
		else if (empty_field == player_field) {
			SetCursorPosition(30, 2);
			cout << "Бот переміг!!!";
		}
	}

	if (gmode == BOT_VS_BOT) {
		if (empty_field == bot_field) {
			SetCursorPosition(30, 2);
			cout << "Бот 1 переміг!!!";
		}
		else if (empty_field == player_field) {
			SetCursorPosition(30, 2);
			cout << "Бот 2 переміг!!!";
		}
	}
}