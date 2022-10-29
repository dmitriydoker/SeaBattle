#include "Header.h"

int(*empty_field)[10][10];
void getWinner(Player* current_user);

void game(Player* current_user, string game_status) {
	int coinflip;

	pregame_settings(current_user, game_status, coinflip);
	if (gmode == EXIT) return;

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
	
	getWinner(current_user);
	_getch();

	clearField(player_field);
	clearField(bot_field);
}

void getWinner(Player* current_user) {
	if (gmode == PLAYER_VS_BOT) {
		if ((*empty_field) == bot_field) {
			SetCursorPosition(30, 2);
			cout << current_user->login << " переміг!!!";
			current_user->stats[WINS]++;
		}
		else if ((*empty_field) == player_field) {
			SetCursorPosition(30, 2);
			cout << "Бот переміг!!!";
		}
	}

	if (gmode == BOT_VS_BOT) {
		if ((*empty_field) == bot_field) {
			SetCursorPosition(30, 2);
			cout << "Бот 1 переміг!!!";
		}
		else if ((*empty_field) == player_field) {
			SetCursorPosition(30, 2);
			cout << "Бот 2 переміг!!!";
		}
	}
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
			empty_field = &(*field);
			return true;
		}

		field = &bot_field;
	} 
	return false;
}
