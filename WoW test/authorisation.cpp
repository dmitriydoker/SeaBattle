#include "Header.h"


//float winrate(float& games, float& wins) {
//	float winrate = 100 / (games / wins);
//	int temp = int(winrate * 10);
//	winrate = temp / 10.0;
//	return winrate;
//}

//Player* authorization()
//{
//	ifstream file("players.txt");
//	file >> players_amount;
//	string buffer;
//	getline(file, buffer);
//
//	players = new Player[players_amount];
//
//	for (int i = 0; i < players_amount; ++i)
//	{
//		getline(file, buffer);
//		players[i].login = buffer;
//		getline(file, buffer);
//		players[i].password = buffer;
//		for (int j = 0; j < 5; ++j) {
//			file >> players[i].stats[j];
//		}
//		getline(file, buffer);
//	}
//	file.close();
//
//	int activeOption = 1;
//	bool run = true, valid_password = false;
//
//	system("cls");
//	printFrame(x, y);
//
//	while (run)
//	{
//		SetColor(YELLOW, BACKGROUND_COLOR);
//		SetCursorPosition(((x - sizeof("Вхід")) / 2) + Xcenter, Ycenter + 2); //центрує назву по центру вікна
//		cout << "Вхід";
//
//		for (size_t i = 0; i < players_amount; i++)
//		{
//			SetCursorPosition(Xcenter + 3, Ycenter + 4 + i);
//			if (activeOption == i + 1) {
//				SetColor(BACKGROUND_COLOR, TEXT_COLOR);
//			}
//			else {
//				SetColor(TEXT_COLOR, BACKGROUND_COLOR);
//			}
//			cout << i + 1 << ". " << players[i].login << " ";
//		}
//
//		SetCursorPosition(((x - sizeof("+ Створити нового гравця")) / 2) + Xcenter, Ycenter + 4 + players_amount + 1);
//		if (activeOption == players_amount + 1) {
//			SetColor(BACKGROUND_COLOR, TEXT_COLOR);
//		}
//		else {
//			SetColor(TEXT_COLOR, BACKGROUND_COLOR);
//		}
//		cout << " + Створити нового гравця ";
//
//		getKey(run, activeOption, players_amount + 1 /* create new user */);
//		SetColor(TEXT_COLOR, BACKGROUND_COLOR);
//	}
//
//	if (activeOption != players_amount + 1)
//	{
//		while (!valid_password)
//		{
//			system("cls");
//			printFrame(x, y);
//
//			SetCursorPosition(Xcenter + 3, (y - 3) / 2 + Ycenter);
//			cout << "Логін : " << players[activeOption - 1].login << " ";
//
//			string check_password;
//			SetCursorPosition(Xcenter + 3, (y - 3) / 2 + Ycenter + 2);
//			cout << "Пароль: ";
//			getline(cin, check_password);
//
//			if (check_password == players[activeOption - 1].password)
//			{
//				valid_password = true;
//			}
//			else
//			{
//				SetCursorPosition(Xcenter + 3, (y - 3) / 2 + Ycenter + 4);
//				cout << "Невірний пароль!";
//				_getch();
//			}
//		}
//	}
//	if (activeOption == players_amount + 1) {
//		createUser();
//		current_player = &players[players_amount - 1];
//	}
//	else {
//		current_player = &players[activeOption - 1];
//	}
//
//	return current_player;
//}

//Player* createUser()
//{
//	Player newPlayer;
//
//	while (true)
//	{
//		system("cls");
//		printFrame(x, y);
//
//		SetColor(YELLOW, BACKGROUND_COLOR);
//		SetCursorPosition(((x - sizeof("Створення нового гравця")) / 2) + Xcenter + 1, Ycenter + 2); //центрує назву по центру вікна
//		cout << "Створення нового гравця";
//
//		SetCursorPosition(Xcenter + 3, Ycenter + (y - 3) / 2);
//		cout << "Логін: ";
//		getline(cin, newPlayer.login);
//
//		bool valid_login = true;
//		for (size_t i = 0; i < players_amount; i++)
//		{
//			if (newPlayer.login == players[i].login)
//			{
//				valid_login = false;
//				SetCursorPosition(Xcenter + 3, Ycenter + (y - 3) / 2 + 2);
//				cout << "Такий гравець вже є!";
//				_getch();
//				break;
//			}
//		}
//		if (valid_login) {
//			break;
//		}
//	}
//
//	SetCursorPosition(Xcenter + 3, Ycenter + (y - 3) / 2 + 2);
//	cout << "Пароль: ";
//	getline(cin, newPlayer.password);
//
//	players_amount++;
//
//	ofstream fileOut("players.txt"); // ЗАПИСУЄ ДАНІ З НОВИМ ГРАВЦЕМ
//	fileOut << players_amount << endl;
//
//	for (int i = 0; i < players_amount - 1; ++i)
//	{
//		fileOut << players[i].login << endl;
//		fileOut << players[i].password << endl;
//		for (int j = 0; j < 5; ++j) {
//			fileOut << players[i].stats[j] << " ";
//		}
//		fileOut << endl;
//	}
//	fileOut << newPlayer.login << endl;
//	fileOut << newPlayer.password << endl;
//	for (int j = 0; j < 5; ++j) {
//		fileOut << 0 << " ";
//	}
//
//	fileOut.close();
//
//	ifstream fileIn("players.txt"); // ОНОВЛЮЄ ДАНІ В КОДІ
//	fileIn >> players_amount;
//	string buffer;
//	getline(fileIn, buffer);
//
//	players = new Player[players_amount];
//
//	for (int i = 0; i < players_amount; ++i)
//	{
//		getline(fileIn, buffer);
//		players[i].login = buffer;
//		getline(fileIn, buffer);
//		players[i].password = buffer;
//		for (int j = 0; j < 5; ++j) {
//			fileIn >> players[i].stats[j];
//		}
//		getline(fileIn, buffer);
//	}
//	fileIn.close();
//	return &newPlayer;
//}

//void savePlayers()
//{
//	ofstream file("players.txt");
//	file << players_amount << endl;
//
//	current_player->stats[3] = winrate(current_player->stats[1], current_player->stats[2]); // рахує відсоток виграшів перед записом в файл
//
//	for (int i = 0; i < players_amount; ++i)
//	{
//		if (players[i].login == current_player->login)
//		{
//			file << (*current_player).login << endl;
//			file << (*current_player).password << endl;
//			for (int j = 0; j < 5; ++j) {
//				file << (*current_player).stats[j] << " ";
//			}
//			file << endl;
//		}
//		else
//		{
//			file << players[i].login << endl;
//			file << players[i].password << endl;
//			for (int j = 0; j < 5; ++j) {
//				file << players[i].stats[j] << " ";
//			}
//			file << endl;
//		}
//	}
//
//	file.close();
//}