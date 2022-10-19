#include "Header.h"

void menu(int& activeOption) {
	system("cls");
	printFrame(menu_width, menu_height);
	SetColor(TEXT_COLOR, BACKGROUND_COLOR);

	int options = 3;
	bool run = true;
	while (run) {
		SetColor(YELLOW, BACKGROUND_COLOR);
		centerCursor("Морський бій", 2);
		cout << "Морський бій";

		centerCursor(" В бій! ", centerOfNumInOptions(1, 2));
		isActiveButton(activeOption == 1);
		cout << " В бій! ";

		centerCursor(" Статистика ", centerOfNumInOptions(2, 2));
		isActiveButton(activeOption == 2);
		cout << " Статистика ";

		centerCursor(" Вихід ", menu_height - 3);
		isActiveButton(activeOption == 3);
		cout << " Вихід ";

		getKeyMenu(run, activeOption, options);
	}
}

void showStatistics(const Player* current_player)
{
	system("cls");
	printFrame(menu_width, menu_height);

	SetCursorPosition(Xcenter + 6, Ycenter + 2);
	cout << "Статистика " << current_player->login;

	
	SetCursorPosition(Xcenter + 6, Ycenter + (menu_height - STATS_AMOUNT) / 2);
	cout << "Зіграно: " << current_player->stats[GAMES_PLAYED] << " ігор" << endl;

	SetCursorPosition(Xcenter + 6, Ycenter + (menu_height - STATS_AMOUNT) / 2 + 1);
	cout << "Виграшів: " << current_player->stats[WINS] << endl;

	SetCursorPosition(Xcenter + 6, Ycenter + (menu_height - STATS_AMOUNT) / 2 + 2);
	cout << "Відсоток виграшу: " << current_player->stats[WINRATE] << "%" << endl;

	/*SetCursorPosition(Xcenter + 6, Ycenter + (menu_height - STATS_AMOUNT) / 2 + 3);
	cout << "Знищено кораблів: " << current_player->stats[SHIPS_DESTROYED] << endl;*/

	centerCursor(" Назад ", menu_height - 3);
	SetColor(BLACK, RED);
	cout << " Назад ";
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
		centerCursor("Режим гри", 2);
		cout << "Режим гри";

		centerCursor(" Людина vs Бот ", centerOfNumInOptions(1, 3));
		isActiveButton(activeOption == 1);
		cout << " Людина vs Бот ";

		centerCursor(" Бот vs Бот ", centerOfNumInOptions(2, 3));
		isActiveButton(activeOption == 2);
		cout << " Бот vs Бот ";

		centerCursor(" Назад ", menu_height - 3);
		isActiveButton(activeOption == 3);
		cout << " Назад ";

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
		centerCursor("Розташування кораблів", 2);
		cout << "Розташування кораблів";

		centerCursor(" Вручну ", centerOfNumInOptions(1, 3));
		isActiveButton(activeOption == 1);
		cout << " Вручну ";

		centerCursor(" Автоматично ", centerOfNumInOptions(2, 3));
		isActiveButton(activeOption == 2);
		cout << " Автоматично ";

		getKeyMenu(run, activeOption, options);
	}
	return activeOption;
}

int pregame_settings(Player* current_user) {
	int gamemode = gameMode();
	
	if (gamemode == EXIT) {
		return EXIT;
	}
	if (gamemode == PLAYER_VS_BOT) {
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
		//current_user->stats[1]++;
	}
	else if (gamemode == BOT_VS_BOT) {
		autoPosition(player_field);
		autoPosition(bot_field);
	}
	return gamemode;
}
