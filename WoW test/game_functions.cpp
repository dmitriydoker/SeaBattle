#include "Header.h"


void getStartCoords(int& xStart, int& yStart, int field_status) {
	if (field_status == ALLY) {
		xStart = playerFieldStartX, yStart = playerFieldStartY;
	}
	else {
		xStart = botFieldStartX, yStart = botFieldStartY;
	}
}

bool onFrame(int var, int edge) {
	if (var == 0 || var == edge) return true;
	else return false;
}

bool onPosition(int var, int edge) {
	if (var > 0 && var < edge) return true;
	else return false;
}

void frameColor(int field_status) {
	if (field_status == ALLY) {
		SetColor(BLACK, TEAL_FADE);
	}
	else {
		SetColor(BLACK, RED);
	}
}

void setFrame(int& fieldStartX, int& fieldStartY, int field_status)
{
	int width = MAP_SIZE + 2, height = MAP_SIZE + 2;
	int frameXstart = fieldStartX - 2, frameYstart = fieldStartY- 1;
	string letters = " АБВГДЕЖЗИІ ";

	frameColor(field_status);

	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			if (onFrame(x, width - 1) or onFrame(y, height - 1)) {
				// draws empty cell 
				SetCursorPosition(frameXstart + x * 2, frameYstart + y);
				cout << "  ";

				// fills empty cell if needed
				SetCursorPosition(frameXstart + x * 2, frameYstart + y);
				if (y == 0) {
					if (onPosition(x, width - 1)) {
						cout << letters[x] << " ";
					}
				}
				else if (x == 0) {
					if (onPosition(y, height- 1)) {
						cout << y - 1 << " ";
					}
				}
			}
		}
	}
	SetColor(BLACK, WHITE);
}

void chessCellColor(int x, int y) {
	bool cellStatus = (x + y) % 2;

	if (cellStatus) {
		SetColor(BLACK, WHITE);
	}
	else {
		SetColor(BLACK, WHITE_FADE);
	}
}

void printCell(int field[10][10], int x, int y) {
	switch (field[x][y])
	{
	case ALIVE:
		if (field == player_field) {
			cout << "[]";
		}
		else {
			cout << "  ";
		}
		//cout << "[]";
		break;
	case DAMAGED:
		SetColor(BLACK, RED);
		cout << "[]";
		break;
	case DROWN:
		SetColor(BLACK, RED);
		cout << "[]";
		break;
	case DUMMY:
		cout << "--";
		break;
	case EMPTY:
		cout << "  ";
		break;
	default:
		break;
	}
}

void setField(int field[10][10]) {
	int xStart, yStart;
	int field_status = field == player_field ? ALLY : ENEMY;

	getStartCoords(xStart, yStart, field_status);
	setFrame(xStart, yStart, field_status);

	// sets field
	for (size_t y = 0; y < MAP_SIZE; y++) {
		for (size_t x = 0; x < MAP_SIZE; x++) {
			SetCursorPosition(xStart + x * 2, yStart + y);
			chessCellColor(x, y);
			printCell(field, x, y);
		}
	}
}



int getRandCoord()
{
	int coord = rand() % MAP_SIZE;
	return coord;
}

bool getRandBool() {
	return rand() % 2;
}

void autoPosition(int field[MAP_SIZE][MAP_SIZE])
{
	int ships[] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 }; // Всі версії кораблів та їх кількість
	int x, y, ship_len;
	bool rotated;

	for (size_t i = 0; i < SHIP_AMOUNT; i++) {
		do {
			x = getRandCoord();
			y = getRandCoord();
			rotated = getRandBool();
			ship_len = ships[i];
		} while (!applyPosition(field, ship_len, x, y, rotated));
	}
}



void processSidesArrows(int& activeOption, int* ships, bool& run) {
	int key = _getch();

	if (key == ENTER) {
		run = false;
	}

	if (key == ARROW_START) {
		key = _getch();

		if (key == RIGHT_ARROW) {
			do {
				activeOption++;
				if (activeOption > 4) {
					activeOption = 1;
				}
			} while (!in(activeOption, ships));
		}
		if (key == LEFT_ARROW) {
			do {
				activeOption--;
				if (activeOption < 1) {
					activeOption = 4;
				}
			} while (!in(activeOption, ships));
		}
	}
}

bool canChoose(int* ships)
{
	for (size_t i = 0; i < SHIP_AMOUNT; i++)
	{
		if (ships[i] > 0) {
			return true;
		}
	}
	return false;
}

int chooseShip(int * availableShips) {
	int activeShip = 1;
	bool run = true;
	do {
		system("cls");
		SetColor(WHITE, BLACK);
		setField(player_field);

		SetCursorPosition(botFieldStartX, CONSOLE_HEIGHT / 2 - 2);
		cout << "Виберіть корабeль";
		SetCursorPosition(botFieldStartX, CONSOLE_HEIGHT / 2);

		if (in(activeShip, availableShips)) {
			cout << "< ";
			for (size_t i = 0; i < activeShip; i++) {
				cout << "[]";
			}
			cout << " >";
		}
		else {
			activeShip++;
			continue;
		}
		processSidesArrows(activeShip, availableShips, run);

	} while (run);

	return activeShip;
}

void deleteShip(int& activeOption, int* ships) {
	for (size_t i = 0; i < SHIP_AMOUNT; i++)
	{
		if (ships[i] == activeOption) {
			ships[i] = 0;
			break;
		}
	}
}

void manualPosition() {
	int ships[] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 }; // Всі версії кораблів та їх кількість 
	int activeShip;
	
	while (canChoose(ships)) {
		activeShip  = chooseShip(ships);
		setShip(activeShip, ships);
	}
}



bool inField(int coord) {
	return coord >= 0 and coord < MAP_SIZE;
}

void colorHint(int x, int y) {
	SetColor(BLACK, GREEN);

	for (int xx = x - 1; xx <= x + 1; xx++) {
		for (int yy = y - 1; yy <= y + 1; yy++) {
			if (!inField(xx) or !inField(yy)) {
				continue;
			}
			if (player_field[xx][yy] != 0) {
				SetColor(BLACK, RED);
				return;
			}
		}
	}
}



void stayInField(int &x, int &y, bool rotated, int ship_len) {
	if (rotated) {
		if (y > MAP_SIZE - ship_len) {
			y = MAP_SIZE - ship_len;
		}
		if (x > MAP_SIZE - 1) {
			x = MAP_SIZE - 1;
		}
	}
	if (!rotated) {
		if (x > MAP_SIZE - ship_len) {
			x = MAP_SIZE - ship_len;
		}
		if (y > MAP_SIZE - 1) {
			y = MAP_SIZE - 1;
		}
	}
}

void validRotate(int& x, int& y, int ship_len) {
	if (x > MAP_SIZE - ship_len) {
		x = MAP_SIZE - ship_len;
	}
	if (y > MAP_SIZE - ship_len) {
		y = MAP_SIZE - ship_len;
	}
}

void moveButtons(int ship, int & x, int & y, int & rotated, bool &set) {
	int key = _getch();

	if (key == ENTER) {
		set = true;
	}

	if (key == ROTATE_BUTTON) {
		rotated++;
		validRotate(x, y, ship);
	}

	if (key == ARROW_START) {
		key = _getch();

		if (key == UP_ARROW) {
			y--;
			if (y < 0) {
				y = 0;
			}
		}
		if (key == DOWN_ARROW) {
			y++;
			stayInField(x, y, (rotated % 2), ship);
		}
		if (key == LEFT_ARROW) {
			x--;
			if (x < 0) {
				x = 0;
			}
		}
		if (key == RIGHT_ARROW) {
			x++;
			stayInField(x, y, (rotated % 2), ship);
		}
	}
	
}

void controlHint() {
	SetCursorPosition(botFieldStartX, CONSOLE_HEIGHT / 2 - 2);
	cout << "Повернути корабель - Пробіл";
	SetCursorPosition(botFieldStartX, CONSOLE_HEIGHT / 2);
	cout << "Поставити корабель - Enter";
}

void printShip(int ship_len, int x ,int y, bool rotated) {
	for (size_t i = 0; i < ship_len; i++) {
		if (rotated) {
			SetCursorPosition(playerFieldStartX + (x) * 2, playerFieldStartY + y + i);
			colorHint(x, y + i);
		}
		else if (!rotated) {
			SetCursorPosition(playerFieldStartX + (x + i) * 2, playerFieldStartY + y);
			colorHint(x + i, y);
		}

		cout << "[]";
	}

}

void setShip(int ship, int * availableShips) {
	system("cls");
	int x = 0, y = 0;
	bool set = false;
	int rotated = 0;

	do {
		setField(player_field);
		controlHint();
	    printShip(ship, x, y, rotated % 2);
		moveButtons(ship, x, y, rotated, set);
		
		if (set) {
			if (applyPosition(player_field, ship, x, y, rotated % 2)) {
				deleteShip(ship, availableShips);
			}
		}
	} while (!set);
	SetColor(WHITE, BLACK);
}



bool canPlace(int x, int y, int field[MAP_SIZE][MAP_SIZE]) {
	for (int xx = x - 1; xx <= x + 1; ++xx) {
		for (int yy = y - 1; yy <= y + 1; ++yy) {
			if (inField(xx) and inField(yy)) {
				if (field[xx][yy] != EMPTY) {
					return false;
				}
			}
		}
	}
	return true;
}

bool applyPosition(int field[MAP_SIZE][MAP_SIZE], int ship_len, int x, int y, bool rotated) {
	bool apply = true;
	int xx = x, yy = y;

	for (int i = 0; i < ship_len; ++i) {
		if (!inField(xx) or !inField(yy)) {
			apply = false;
			break;
		}
		apply = apply && canPlace(xx, yy, field);
		rotated ? yy++ : xx++;
	}

	if (!apply) {
		return false;
	}

	// Відмітити корабель на полі
	xx = x, yy = y;
	for (int i = 0; i < ship_len; ++i) {
		field[xx][yy] = ALIVE; // = ship
		rotated ? yy++ : xx++;
	}
	return true;
}

void clearField(int field[10][10]) {
	for (size_t x = 0; x < MAP_SIZE; x++)
	{
		for (size_t y = 0; y < MAP_SIZE; y++)
		{
			field[x][y] = 0;
		}
	}
}



void shotComment(int x, int y, int field[10][10], string text) {
	string comment = "><";
	comment.append(text);

	int xStart, yStart;
	if (field == player_field) {
		xStart = playerFieldStartX;
		yStart = playerFieldStartY;
	}
	else {
		xStart = botFieldStartX;
		yStart = botFieldStartY;
	}

	for (size_t i = 0; i < comment.length(); i++) {
		SetCursorPosition(xStart + (x * 2) + i, yStart + y);
		cout << comment[i];
		Sleep(25);
	}
	Sleep(555);

	setField(field);
}

bool shotStatus(int field[10][10], int x, int y) {
	switch (field[x][y])
	{
	case EMPTY:
		field[x][y] = 4;
		shotComment(x, y, field, "Промах");
		return false;
	case ALIVE:
		field[x][y] = DAMAGED;
		if (isDrown(x, y, field)) {
			shotComment(x, y, field, "Вбив!!!");
		}
		else {
			shotComment(x, y, field, "Влучив!");
		}
		return true;
	case DAMAGED:
		shotComment(x, y, field, "Палуба вже підбита");
		return true;
	case DROWN:
		shotComment(x, y, field, "Корабель вже потоплено");
		return true;
	case DUMMY:
		shotComment(x, y, field, "Тут пусто!");
		return true;
	default:
		break;
	}
}



int xShot = 5, yShot = 6;

void cursorColorHint() {
	if (bot_field[xShot][yShot] == EMPTY or
		bot_field[xShot][yShot] == ALIVE)
	{
		SetColor(BLACK, GREEN);
	}
	else {
		SetColor(BLACK, RED);
	}
}

void setCursor() {
	SetCursorPosition(botFieldStartX + (xShot * 2), botFieldStartY + yShot);
	cursorColorHint();
	cout << "><";

}

void shotButtons(bool & run) {
	int key = _getch();

	if (key == ESC) {
		pauseGame();
	}

	if (key == ENTER) {
		run = shotStatus(bot_field, xShot, yShot);
	}

	if (key == ARROW_START) {
		key = _getch();

		if (key == UP_ARROW) {
			yShot--;
			if (!inField(yShot)) {
				yShot = 0;
			}
		}
		if (key == DOWN_ARROW) {
			yShot++;
			if (!inField(yShot)) {
				yShot = MAP_SIZE - 1;
			}
		}
		if (key == RIGHT_ARROW) {
			xShot++;
			if (!inField(xShot)) {
				xShot = MAP_SIZE - 1;
			}
		}
		if (key == LEFT_ARROW) {
			xShot--;
			if (!inField(xShot)) {
				xShot = 0;
			}
		}
	}
}

void shoot() {
	bool run = true;
	do {
		if (end()) break; 

		setField(bot_field);
		setCursor();
		shotButtons(run);
	} while (run);
}



int findDirection(int x, int y, int field[10][10]) {
	int dirX = NO_DIRECTION, dirY = NO_DIRECTION;

	for (int  xx = x - 1; xx <= x + 1; xx++) {
		for (int yy = y - 1; yy <= y + 1; yy++) {
			if (!inField(xx) or !inField(yy))  continue; 

			if (field[xx][yy] == ALIVE)  return FOUND_ALIVE; 

			if (field[xx][yy] == DAMAGED) {
				if (xx != x or yy != y) {
					dirX = xx;
					dirY = yy;
				} 
			}
		}
	}
	if (dirX == NO_DIRECTION and dirY == NO_DIRECTION)  return DROWN_ALREADY; 

	if (dirX > x)  return RIGHT; 
	if (dirX < x)  return LEFT;
	if (dirY > y)  return DOWN; 
	if (dirY < y)  return UP; 
}

int inverseDir(int dir) {
	if (dir == UP)    return DOWN; 
	if (dir == DOWN)  return UP;
	if (dir == RIGHT) return LEFT; 
	if (dir == LEFT)  return RIGHT; 
}

void processOnDirection(int& x, int& y, int dir) { 
	if (dir == UP)	  { y--; }
	if (dir == DOWN)  { y++; }
	if (dir == LEFT)  { x--; }
	if (dir == RIGHT) { x++; }
}

bool checkOnDirection(int x, int y, int field[10][10], int dir) {
	while (true) {
		if (!inField(x) or !inField(y))  return true;

		if (field[x][y] == EMPTY or field[x][y] == DUMMY)  return true;

		if (field[x][y] == ALIVE)  return false;

		processOnDirection(x, y, dir);
	}
}

bool isDrown(int x, int y, int field[10][10]) {
	int dir = findDirection(x, y, field);

	if (dir == FOUND_ALIVE) return false; 

	if (dir == DROWN_ALREADY) {
		makeDrown(x, y, field, dir);
		return true;
	}

	bool drown = checkOnDirection(x, y, field, dir) and checkOnDirection(x, y, field, inverseDir(dir));

	if (drown) makeDrown(x, y, field, dir);	

	return drown;
}



void setDummies(int x, int y, int field[10][10]) {
	for (int xx = x - 1; xx <= x + 1; xx++) {
		for (int yy = y - 1; yy <= y + 1; yy++) {
			if (inField(xx) and inField(yy)) {
				if (field[xx][yy] == EMPTY) {
					field[xx][yy] = DUMMY;
				}
			}
		}
	}
}

void drownOnDirection(int x, int y, int field[10][10], int direction) {
	do {
		if (!inField(x) or !inField(y)) { break; }

		if (field[x][y] == DUMMY) { break; }

		field[x][y] = DROWN;
		setDummies(x, y, field);

		if (direction == DROWN_ALREADY) { break; }

		processOnDirection(x, y, direction);
	} while (true);
}

void makeDrown(int x, int y, int field[10][10], int direction) {
	drownOnDirection(x, y, field, direction);
	drownOnDirection(x, y, field, inverseDir(direction));
}
