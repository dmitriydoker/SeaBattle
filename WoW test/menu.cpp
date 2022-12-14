#include "Header.h"

Player* player;
string fileName;


void menu(int& activeOption) {
	system("cls");
	printFrame(menu_width, menu_height);
	SetColor(TEXT_COLOR, BACKGROUND_COLOR);

	int options = 4;
	bool run = true;
	while (run) {
		SetColor(YELLOW, BACKGROUND_COLOR);
		centerCursor("???????? ???", 2);
		cout << "???????? ???";

		centerCursor(" ?????????? ", centerOfNumInOptions(1, 3));
		isActiveButton(activeOption == 1);
		cout << " ?????????? ";

		centerCursor(" ???? ??? ", centerOfNumInOptions(2, 3));
		isActiveButton(activeOption == 2);
		cout << " ???? ??? ";

		centerCursor(" ?????????? ", centerOfNumInOptions(3, 3));
		isActiveButton(activeOption == 3);
		cout << " ?????????? ";

		centerCursor(" ????? ", menu_height - 3);
		isActiveButton(activeOption == 4);
		cout << " ????? ";

		getKeyMenu(run, activeOption, options);
	}
}

void showStatistics(const Player* current_player)
{
	system("cls");
	printFrame(menu_width, menu_height);

	SetCursorPosition(Xcenter + 6, Ycenter + 2);
	cout << "?????????? " << current_player->login;
	
	SetCursorPosition(Xcenter + 6, Ycenter + (menu_height - STATS_AMOUNT) / 2);
	cout << "ǳ?????: " << current_player->stats[GAMES_PLAYED] << " ????" << endl;

	SetCursorPosition(Xcenter + 6, Ycenter + (menu_height - STATS_AMOUNT) / 2 + 1);
	cout << "????????: " << current_player->stats[WINS] << endl;

	SetCursorPosition(Xcenter + 6, Ycenter + (menu_height - STATS_AMOUNT) / 2 + 2);
	cout << "³?????? ???????: " << current_player->stats[WINRATE] << "%" << endl;

	centerCursor(" ????? ", menu_height - 3);
	SetColor(BLACK, RED);
	cout << " ????? ";

	SetColor(WHITE, BLACK);
	_getch();
}

int gameMode() {
	system("cls");
	printFrame(menu_width, menu_height);

	int activeOption = 1;
	const int options = 3;
	bool run = true;
	while (run) {
		SetColor(YELLOW, BACKGROUND_COLOR);
		centerCursor("????? ???", 2);
		cout << "????? ???";

		centerCursor(" ?????? vs ??? ", centerOfNumInOptions(1, 3));
		isActiveButton(activeOption == 1);
		cout << " ?????? vs ??? ";

		centerCursor(" ??? vs ??? ", centerOfNumInOptions(2, 3));
		isActiveButton(activeOption == 2);
		cout << " ??? vs ??? ";

		centerCursor(" ????? ", menu_height - 3);
		isActiveButton(activeOption == 3);
		cout << " ????? ";

		getKeyMenu(run, activeOption, options);
	}
	return activeOption;
}

int choosePositioning()
{
	system("cls");	
	printFrame(menu_width, menu_height);

	int activeOption = 1;
	int options = 2;
	bool run = true;
	while (run) {
		SetColor(YELLOW, BACKGROUND_COLOR);
		centerCursor("???????????? ????????", 2);
		cout << "???????????? ????????";

		centerCursor(" ?????? ", centerOfNumInOptions(1, 3));
		isActiveButton(activeOption == 1);
		cout << " ?????? ";

		centerCursor(" ??????????? ", centerOfNumInOptions(2, 3));
		isActiveButton(activeOption == 2);
		cout << " ??????????? ";

		getKeyMenu(run, activeOption, options);
	}
	return activeOption;
}

void pregame_settings(Player* current_user, string game_status, int & coinflip) {
	player = current_user;
	fileName = player->login + "_save.txt";

	if (game_status == "load game") {
		loadGame();
		gmode = PLAYER_VS_BOT;
		coinflip = 1; // game starts with player`s turn

	}
	else {
		gmode = gameMode();
		coinflip = rand() % 2;

		if (gmode == EXIT) return;
	
		if (gmode == PLAYER_VS_BOT) {
			current_user->stats[GAMES_PLAYED]++;

			int positioning = choosePositioning();

			if (positioning == MANUAL_POSITIONING) {
				manualPosition();
				autoPosition(bot_field);
			}
			else if (positioning == AUTO_POSITIONING) {
				autoPosition(player_field);
				autoPosition(bot_field);
			}
			deleteSaving();
		}
		else if (gmode == BOT_VS_BOT) {
			autoPosition(player_field);
			autoPosition(bot_field);
		}
	}
}



bool saveExists(Player* current_player) {
	player = current_player;
	fileName = player->login + "_save.txt";

	ifstream file(fileName);

	string buffer;
	getline(file, buffer);

	if (buffer == "true") {
		return true;
	}
	return false;
}

void saveGame() {
	ofstream file(fileName);
	file << "true" << endl;

	for (size_t x = 0; x < MAP_SIZE; x++) {
		for (size_t y = 0; y < MAP_SIZE; y++) {
			file << player_field[x][y] << "  ";
		}
		file << endl;
	}

	file << endl;

	for (size_t x = 0; x < MAP_SIZE; x++) {
		for (size_t y = 0; y < MAP_SIZE; y++) {
			file << bot_field[x][y] << "  ";
		}
		file << endl;
	}
	file.close();

	savePlayers();
}

void deleteSaving() {
	ofstream file(fileName);
	file << "false";
	file.close();
}

void loadGame() {
	ifstream file(fileName);
	string buffer;
	getline(file, buffer);

	for (size_t x = 0; x < MAP_SIZE; x++) {
		for (size_t y = 0; y < MAP_SIZE; y++) {
			file >> player_field[x][y];
		}
		getline(file, buffer);
	}
	getline(file, buffer);

	for (size_t x = 0; x < MAP_SIZE; x++) {
		for (size_t y = 0; y < MAP_SIZE; y++) {
			file >> bot_field[x][y];
		}
		getline(file, buffer);
	}

	file.close();
	deleteSaving();
}

void pauseGame() {
	SetColor(TEXT_COLOR, BACKGROUND_COLOR);
	system("cls");
	printFrame(menu_width, menu_height);

	int activeOption = 1;
	int options = 2;
	bool run = true;
	while (run) {
		SetColor(YELLOW, BACKGROUND_COLOR);
		centerCursor("?????", 2);
		cout << "?????";

		centerCursor(" ?????????? ", centerOfNumInOptions(1, 2));
		isActiveButton(activeOption == 1);
		cout << " ?????????? ";

		centerCursor(" ???????? ? ?????", centerOfNumInOptions(2, 2));
		isActiveButton(activeOption == 2);
		cout << " ???????? ? ????? ";

		getKeyMenu(run, activeOption, options);
	}

	system("cls");

	if (activeOption == 2) {
		saveGame();
		exit(0);
	}
	else if (activeOption == 1) {
		setField(player_field);
		setField(bot_field);
	}
}