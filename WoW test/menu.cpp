#include "Header.h"

void menu(int& activeOption) {
	system("cls");
	printFrame(menu_width, menu_height);

	int options = 3;
	bool run = true;
	while (run) {
		SetColor(YELLOW, BACKGROUND_COLOR);
		centerCursor("�������� ��", 2);
		cout << "�������� ��";

		centerCursor(" � ��! ", centerOfNumInOptions(1, 3));
		isActiveButton(activeOption == 1);
		cout << " � ��! ";

		centerCursor(" ���������� ", centerOfNumInOptions(2, 3));
		isActiveButton(activeOption == 2);
		cout << " ���������� ";

		centerCursor(" ����� ", menu_height - 3);
		isActiveButton(activeOption == 3);
		cout << " ����� ";

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
		centerCursor("������������ �������", 2);
		cout << "������������ �������";

		centerCursor(" ������ ", centerOfNumInOptions(1, 3));
		isActiveButton(activeOption == 1);
		cout << " ������ ";

		centerCursor(" ����������� ", centerOfNumInOptions(2, 3));
		isActiveButton(activeOption == 2);
		cout << " ����������� ";

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

	centerCursor("���������� ", 2);
	cout << "����������" << current_player->login;

	centerCursor("ǳ�����: ", centerOfNumInOptions(1, 5));
	cout << "ǳ�����: " << current_player->stats[GAMES_PLAYED] << " ����" << endl;
	centerCursor("��������: ", centerOfNumInOptions(2, 5));
	cout << "��������: " << current_player->stats[WINS] << endl;
	centerCursor("³������ �������: ", centerOfNumInOptions(3, 5));
	cout << "³������ �������: " << current_player->stats[WINRATE] << "%" << endl;
	centerCursor("������� �������: ", centerOfNumInOptions(4, 5));
	cout << "������� �������: " << current_player->stats[SHIPS_DESTROYED] << endl;

	centerCursor(" ����� ", centerOfNumInOptions(5, 5));
	SetColor(BLACK, RED);
	cout << " ����� ";
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
