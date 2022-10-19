#include<iostream>
#include<Windows.h>
#include "Header.h"

using namespace std;

void projectSettings();

int main() {
	projectSettings();
	Player *current_user = authorisation();

	bool run = true;
	do {
		int activeOption = 1;
		menu(activeOption);

		switch (activeOption) {
		case 3: // exit
			system("cls");
			run = false;
			break;
		case 1: // game
			game(current_user);
			break;
		case 2: // statistics
			showStatistics(current_user);
			break;
		default:
			break;
		}
		savePlayers();
	} while (run);
}

void projectSettings() {
	setlocale(LC_CTYPE, "ukr");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	ShowConsoleCursor(false);
	system("mode con cols=80 lines=25"); // задає розмір вікна консолі
	srand(time(NULL));
}