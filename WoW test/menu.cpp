#include "Header.h"

void menu(int& activeOption) {
	system("cls");
	printFrame(menu_width, menu_height);

	int options = 3;
	bool run = true;
	while (run) {
		SetColor(YELLOW, BACKGROUND_COLOR);
		centerCursor("Морський бій", 2);
		cout << "Морський бій";

		centerCursor(" В бій! ", centerOfNumInOptions(1, 3));
		isActiveButton(activeOption == 1);
		cout << " В бій! ";

		centerCursor(" Статистика ", centerOfNumInOptions(2, 3));
		isActiveButton(activeOption == 2);
		cout << " Статистика ";

		centerCursor(" Вихід ", menu_height - 3);
		isActiveButton(activeOption == 3);
		cout << " Вихід ";

		getKey(run, activeOption, options);
	}
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

		getKey(run, activeOption, options);
	}
	switch (activeOption)
	{
	case options: // exit
		return EXIT;
	case 1:
		return PLAYER_VS_BOT;
	case 2:
		return BOT_VS_BOT;
	default:
		break;
	}
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

		getKey(run, activeOption, options);
	}

	switch (activeOption)
	{
	case 1: // manual
		return false;
	case 2: // auto
		return true;
	default:
		break;
	}
}

void showStatistics(const Player* current_player)
{
	system("cls");
	printFrame(menu_width + 10, menu_height);

	centerCursor("Статистика ", 2);
	cout << "Статистика" << current_player->login;

	centerCursor("Зіграно: ", centerOfNumInOptions(1, 5));
	cout << "Зіграно: " << current_player->stats[GAMES_PLAYED] << " ігор" << endl;
	centerCursor("Виграшів: ", centerOfNumInOptions(2, 5));
	cout << "Виграшів: " << current_player->stats[WINS] << endl;
	centerCursor("Відсоток виграшу: ", centerOfNumInOptions(3, 5));
	cout << "Відсоток виграшу: " << current_player->stats[WINRATE] << "%" << endl;
	centerCursor("Знищено кораблів: ", centerOfNumInOptions(4, 5));
	cout << "Знищено кораблів: " << current_player->stats[SHIPS_DESTROYED] << endl;

	centerCursor(" Назад ", centerOfNumInOptions(5, 5));
	SetColor(BLACK, RED);
	cout << " Назад ";
	SetColor(WHITE, BLACK);
	_getch();
}

bool pregame_settings() {
	int gamemode = gameMode();
	
	if (gamemode == EXIT) {
		return false;
	}
	if (gamemode == PLAYER_VS_BOT) {
		int positioning = choosePositioning();

		if (positioning == MANUAL_POSITIONING) {
			
		}
		else if (positioning == AUTO_POSITIONING) {

		}
		//current_user->stats[1]++;
	}
	else if (gamemode == BOT_VS_BOT) {
		//autolocate x2
	}
}
