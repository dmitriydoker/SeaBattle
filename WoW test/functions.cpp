#include "Header.h"

void SetCursorPosition(short x, short y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
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

void getKeyMenu(bool& run, int& activeOption, const int& optionAmount)
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

	if (key == ARROW_START) { 
		key = _getch();

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
	SetColor(TEXT_COLOR, BACKGROUND_COLOR);
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

void centerCursor(string text, int yExtend) {
	int xExtend = (menu_width - text.length()) / 2;
	text.length() % 2 ? xExtend++ : 0;
	SetCursorPosition(Xcenter + xExtend, Ycenter + yExtend);
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