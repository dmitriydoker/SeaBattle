#include"Header.h"

bool valid_bot_shot(int x, int y, int field[10][10]) {
	if (!inField(x) or !inField(y)) {
		return false;
	}
	if (field[x][y] != EMPTY and field[x][y] != ALIVE) {
		return false; 
	}
	return true;
}

void getValidCoords(int field[10][10], int& x, int& y) {
	do {
		x = getRandCoord();
		y = getRandCoord();
	} while (!valid_bot_shot(x, y, field));
}

int getValidDir(int field[10][10], int& x, int& y) {
	int xx, yy;
	int dir; 

	while (true) {
		xx = x, yy = y;
		dir = rand() % 4 + 1; // check enum Directions
		processOnDirection(xx, yy, dir);

		if (valid_bot_shot(xx, yy, field)) {
			break;
		}
	}
	return dir;
}



void fillAI(AI& bot_AI, int &x, int &y, int &dir, int field[10][10]) {
	if (bot_AI.hit) {
		// списує координати попадання
		x = bot_AI.hitX;
		y = bot_AI.hitY;

		// списує правильний напрямок
		if (bot_AI.found_dir) {
			dir = bot_AI.direction;
		}
		else {
			dir = getValidDir(field, x, y);
		}
	}
	else {
		getValidCoords(field, x, y);
		dir = NO_DIRECTION;
	}
}

void resetAI(AI& AI) {
	AI.hit = false;
	AI.startX = NULL;
	AI.startY = NULL;
	
	AI.found_dir = false;
	AI.direction = NO_DIRECTION;
}



bool secureDirProcession(int &x, int &y, int dir, int field[10][10]) {
	int xx = x, yy = y;
	processOnDirection(xx, yy, dir);

	if (valid_bot_shot(xx, yy, field)) {
		return true;
	}
	return false;
}

void setupShot(int field[10][10], int &x, int &y, int &direction, AI& bot_AI) {
	if (secureDirProcession(x, y, direction, field)) {
		processOnDirection(x, y, direction);
	}
	else {
		x = bot_AI.startX;
		y = bot_AI.startY;

		direction = inverseDir(direction);

		if (secureDirProcession(x, y, direction, field)) {
			processOnDirection(x, y, direction);
		}
		else {
			resetAI(bot_AI);
			fillAI(bot_AI, x, y, direction, field);
		}
	}
}

bool processShot(AI& bot_AI, int field[10][10], int x, int y, int& direction) {
	switch (field[x][y])
	{
	case EMPTY:
		field[x][y] = DUMMY;
		shotComment(x, y, field, "Промах");

		//якщо корабель ще не потолено і треба добити з іншої сторони
		if (bot_AI.hit and bot_AI.found_dir) { 
			bot_AI.hitX = bot_AI.startX;
			bot_AI.hitY = bot_AI.startY;

			bot_AI.direction = inverseDir(bot_AI.direction);
		}

		return false;
	case ALIVE:
		field[x][y] = DAMAGED;

		if (bot_AI.hit) { // якщо вже було попадання
			bot_AI.hitX = x;
			bot_AI.hitY = y;

			bot_AI.found_dir = true;
			bot_AI.direction = direction;
		}
		else if (!bot_AI.hit) { // якщо це перше попадання
			bot_AI.hit = true;

			bot_AI.startX = x;
			bot_AI.startY = y;

			bot_AI.hitX = x;
			bot_AI.hitY = y;
		}

		if (isDrown(x, y, field)) {
			shotComment(x, y, field, "Вбив");
			resetAI(bot_AI);
		}
		else {
			shotComment(x, y, field, "Влучив");
		}
		return true;
	default:
		return false;
	}
}



void bot_shot(AI &bot_AI, int enemy_field[10][10]) {
	int x, y, direction;
	bool run = true;

	do {
		if (end()) { break; }

		fillAI(bot_AI, x, y, direction, enemy_field);
		setupShot(enemy_field, x, y, direction, bot_AI); 
		run = processShot(bot_AI, enemy_field, x, y, direction);
	} while (run);
}