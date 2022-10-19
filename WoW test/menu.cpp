#include "Header.h"

void menu(int& activeOption) {
	system("cls");
	printFrame(menu_width, menu_height);
	SetColor(TEXT_COLOR, BACKGROUND_COLOR);

	int options = 3;
	bool run = true;
	while (run) {
		SetColor(YELLOW, BACKGROUND_COLOR);
		centerCursor("�������� ��", 2);
		cout << "�������� ��";

		centerCursor(" � ��! ", centerOfNumInOptions(1, 2));
		isActiveButton(activeOption == 1);
		cout << " � ��! ";

		centerCursor(" ���������� ", centerOfNumInOptions(2, 2));
		isActiveButton(activeOption == 2);
		cout << " ���������� ";

		centerCursor(" ����� ", menu_height - 3);
		isActiveButton(activeOption == 3);
		cout << " ����� ";

		getKeyMenu(run, activeOption, options);
	}
}

void showStatistics(const Player* current_player)
{
	system("cls");
	printFrame(menu_width, menu_height);

	SetCursorPosition(Xcenter + 6, Ycenter + 2);
	cout << "���������� " << current_player->login;

	
	SetCursorPosition(Xcenter + 6, Ycenter + (menu_height - STATS_AMOUNT) / 2);
	cout << "ǳ�����: " << current_player->stats[GAMES_PLAYED] << " ����" << endl;

	SetCursorPosition(Xcenter + 6, Ycenter + (menu_height - STATS_AMOUNT) / 2 + 1);
	cout << "��������: " << current_player->stats[WINS] << endl;

	SetCursorPosition(Xcenter + 6, Ycenter + (menu_height - STATS_AMOUNT) / 2 + 2);
	cout << "³������ �������: " << current_player->stats[WINRATE] << "%" << endl;

	/*SetCursorPosition(Xcenter + 6, Ycenter + (menu_height - STATS_AMOUNT) / 2 + 3);
	cout << "������� �������: " << current_player->stats[SHIPS_DESTROYED] << endl;*/

	centerCursor(" ����� ", menu_height - 3);
	SetColor(BLACK, RED);
	cout << " ����� ";
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
		centerCursor("����� ���", 2);
		cout << "����� ���";

		centerCursor(" ������ vs ��� ", centerOfNumInOptions(1, 3));
		isActiveButton(activeOption == 1);
		cout << " ������ vs ��� ";

		centerCursor(" ��� vs ��� ", centerOfNumInOptions(2, 3));
		isActiveButton(activeOption == 2);
		cout << " ��� vs ��� ";

		centerCursor(" ����� ", menu_height - 3);
		isActiveButton(activeOption == 3);
		cout << " ����� ";

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
		centerCursor("������������ �������", 2);
		cout << "������������ �������";

		centerCursor(" ������ ", centerOfNumInOptions(1, 3));
		isActiveButton(activeOption == 1);
		cout << " ������ ";

		centerCursor(" ����������� ", centerOfNumInOptions(2, 3));
		isActiveButton(activeOption == 2);
		cout << " ����������� ";

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
