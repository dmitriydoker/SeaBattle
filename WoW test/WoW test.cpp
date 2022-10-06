#include<math.h>
#include<string>
#include<cstdio>

#include "Header.h"

using namespace std;

int main()
{
	setlocale(LC_CTYPE, "ukr");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	system("mode con cols=80 lines=25"); // задає розмір вікна консолі
	srand(time(NULL));

	Player* current_user = {0}/*= autorisation()*/;

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
			//game(current_user);
			break;
		case 2: // statistics
			showStatistics(current_user);
			break;
		default:
			break;
		}
		//	savePlayers();
	} while (run);
}