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
		case 4: // exit
			system("cls");
			run = false;
			break;
		case 1: // continue game
			if (saveExists(current_user)) {
				game(current_user, "load game");
			}
			break;
		case 2: // new game
			game(current_user, "new game");
			break;
		case 3: // statistics
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