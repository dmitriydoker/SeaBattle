#include "Header.h"

int players_amount = 0;
Player* current_player;
Player* players;

void SetCursorPosition(short x, short y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(ConsoleColor text, ConsoleColor background)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (short)text | ((short)background << 4));
}

void printFrame(const int& x, const int& y)
{
	SetColor(MENU_COLOR, BACKGROUND_COLOR);
	int XCenter = (CONSOLE_WIDTH - x) / 2, YCenter = (CONSOLE_HEIGHT - y) / 2;

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (j == 0 || j == x - 1 || i == 0 || i == y - 1) {
				SetCursorPosition(j + XCenter, i + YCenter);
				cout << '*';
			}
		}
	}
	SetColor(TEXT_COLOR, BACKGROUND_COLOR);
}

void getKey(bool& run, int& activeOption, const int& optionAmount)
{
	int key;
	key = _getch();


	if (key == ENTER) {
		run = false;
	}

	if (key == ESC) {
		activeOption = optionAmount;// exit
		run = false;
	}

	if (key == ARROW_START) { //первый код от клавиш стрелок
		key = _getch(); //получаем второй код


		if (key == DOWN_ARROW) {
			activeOption++;
			if (activeOption > optionAmount) {
				activeOption = 1;
			}
		}
		if (key == UP_ARROW) {
			activeOption--;
			if (activeOption < 1) {
				activeOption = optionAmount;
			}
		}
	}
}

bool in(int& ship, int* arr)
{
	for (size_t i = 0; i < SHIP_AMOUNT; i++)
	{
		if (arr[i] == ship)
		{
			return true;
		}
	}
	return false;
}

void centerCursor(string text, int option_count) {
	SetCursorPosition(Xcenter + (menu_width - text.length()) / 2 + 1, Ycenter + option_count); //центрує назву по центру вікна
}

int centerOfNumInOptions(int num, int options) {
	int start = (menu_height - options) / 2;
	int needle_center = start + (num - 1);
	return needle_center;
}

void isActiveButton(bool value) {
	if (value) {
		SetColor(BACKGROUND_COLOR, TEXT_COLOR);
	}
	else {
		SetColor(TEXT_COLOR, BACKGROUND_COLOR);
	}
}
