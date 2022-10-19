#include "Header.h"

int players_amount = 0;
Player* current_player;
Player* players;

void loadPlayers() {
	ifstream file("players.txt");
	file >> players_amount;
	string buffer;
	getline(file, buffer);

	players = new Player[players_amount];

	for (int i = 0; i < players_amount; ++i)
	{
		getline(file, buffer);
		players[i].login = buffer;
		getline(file, buffer);
		players[i].password = buffer;
		for (int j = 0; j < STATS_AMOUNT; ++j) {
			file >> players[i].stats[j];
		}
		getline(file, buffer);
	}
	file.close();
}

int selectUser() {
	int activeUser = 1;
	bool run = true;
	do
	{
		SetColor(YELLOW, BACKGROUND_COLOR);
		centerCursor("Вхід", 2);
		cout << "Вхід";

		for (size_t i = 0; i < players_amount; i++)
		{
			centerCursor(players[i].login, centerOfNumInOptions(i, players_amount));
			isActiveButton(activeUser == i + 1);
			cout << " " << players[i].login << " ";
		}

		centerCursor(" + Створити нового гравця ", menu_height - 3);
		isActiveButton(activeUser == players_amount + 1);
		cout << " + Створити нового гравця ";

		getKeyMenu(run, activeUser, players_amount + 1); // players_amount + 1 => players_amount + create new
	} while (run);
	SetColor(TEXT_COLOR, BACKGROUND_COLOR);

	return activeUser;
}

void sign_in(int active_user) {
	bool valid_password = false;

	while (!valid_password)
	{
		system("cls");
		printFrame(menu_width, menu_height);

		SetCursorPosition(Xcenter + 3, Ycenter + (menu_height - 3) / 2);
		cout << "Логін : " << players[active_user - 1].login << " ";

		string check_password;
		SetCursorPosition(Xcenter + 3, Ycenter + (menu_height - 3) / 2 + 2);
		cout << "Пароль: ";
		getline(cin, check_password);

		if (check_password == players[active_user - 1].password)
		{
			valid_password = true;
		}
		else
		{
			SetCursorPosition(Xcenter + 3, Ycenter + (menu_height - 3) / 2 + 2);
			cout << "Невірний пароль!";
			_getch();
		}
	}
}

Player* authorisation()
{
	system("cls");
	printFrame(menu_width, menu_height);
	
	loadPlayers();
	int active_user = selectUser();

	if (active_user != players_amount + 1) { // + 1 => create new user
		sign_in(active_user);
		current_player = &players[active_user - 1];
	}
	else {
		createUser();
		current_player = &players[active_user - 1];
	}

	return current_player;
}



void createMenuHead() {
	system("cls");
	printFrame(menu_width, menu_height);

	SetColor(YELLOW, BACKGROUND_COLOR);
	centerCursor("Створення нового гравця", 2);
	cout << "Створення нового гравця";

	SetColor(TEXT_COLOR, BACKGROUND_COLOR);
}

void create_valid_login(Player &newPlayer) {
	do
	{
		createMenuHead();

		SetCursorPosition(Xcenter + 3, Ycenter + (menu_height - 2) / 2);
		cout << "Логін: ";
		getline(cin, newPlayer.login);

		bool valid_login = true;
		if (newPlayer.login.length() == 0) {
			SetCursorPosition(Xcenter + 3, Ycenter + (menu_height - 2) / 2 + 2);
			cout << "Ім'я дуже коротке!";
			_getch();
			continue;
		}
		for (size_t i = 0; i < players_amount; i++)
		{
			if (newPlayer.login == players[i].login) {
				valid_login = false;
				SetCursorPosition(Xcenter + 3, Ycenter + (menu_height - 2) / 2 + 2);
				cout << "Такий гравець вже є!";
				_getch();
				break;
			}
		}
		if (valid_login) {
			break;
		}
	} while (true);
}

void create_valid_password(Player& newPlayer) {
	do
	{
		createMenuHead();

		SetCursorPosition(Xcenter + 3, Ycenter + (menu_height - 2) / 2);
		cout << "Логін: " << newPlayer.login;

		SetCursorPosition(Xcenter + 3, Ycenter + (menu_height - 2) / 2 + 2);
		cout << "Пароль: ";
		getline(cin, newPlayer.password);
		
		if (newPlayer.password.length() == 0) {
			SetCursorPosition(Xcenter + 3, Ycenter + (menu_height - 2) / 2 + 4);
			cout << "Пароль дуже короткий!";
			_getch();
			continue;
		}
		break;
	} while (true);
}

void add_player_to_list(Player& newPlayer) {
	ifstream file("players.txt");
	file >> players_amount;
	string buffer;
	getline(file, buffer);

	players_amount++;
	players = new Player[players_amount];
	
	// load players
	for (int i = 0; i < players_amount - 1; ++i)
	{
		getline(file, buffer);
		players[i].login = buffer;
		getline(file, buffer);
		players[i].password = buffer;
		for (int j = 0; j < STATS_AMOUNT; ++j) {
			file >> players[i].stats[j];
		}
		getline(file, buffer);
	}
	file.close();

	// ADD NEW PLAYER
	players[players_amount - 1] = newPlayer;
}

void createUser() {
	Player newPlayer;

	create_valid_login(newPlayer);
	create_valid_password(newPlayer);
	add_player_to_list(newPlayer);
}



void winrate(Player* player) {
	if (player->stats[WINS] == 0) {
		player->stats[WINRATE] = 0;
	}
	else {
		float winrate = 100 / (player->stats[GAMES_PLAYED] / player->stats[WINS]);

		int temp = int(winrate * 10);
		winrate = temp / 10.0;

		player->stats[WINRATE] = winrate;
	}
}

void update_current_player_stats() {
	winrate(current_player); // рахує відсоток виграшів перед записом в файл

	for (size_t i = 0; i < players_amount; i++)
	{
		if (players[i].login == current_player->login) {
			for (size_t j = 0; j < STATS_AMOUNT; j++)
			{
				players[i].stats[j] = current_player->stats[j];
			}
		}
	}
}

void savePlayers() {
	update_current_player_stats();

	ofstream file("players.txt");
	file << players_amount << endl;

	for (int i = 0; i < players_amount; ++i)
	{
		file << players[i].login << endl;
		file << players[i].password << endl;
		for (int j = 0; j < STATS_AMOUNT; ++j) {
			file << players[i].stats[j] << " ";
		}
		file << endl;
	}

	file.close();
}