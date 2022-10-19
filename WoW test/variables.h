#pragma once
#include <string>

#define MAP_SIZE 10
#define SHIP_AMOUNT 10

#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 25

#define MENU_COLOR TEAL
#define TEXT_COLOR WHITE
#define BACKGROUND_COLOR BLACK

using namespace std;

struct Player {
	string login;
	string password;
	float stats[3] = { 0,0,0 };
};

struct Field {
	int field[10][10];
	bool permission;
};

struct AI {
	bool hit = false;
	int startX = NULL;
	int startY = NULL;

	int hitX = NULL;
	int hitY = NULL;

	bool found_dir = false;
	int direction;
};

const int menu_width = 30, menu_height = 15;
const int Xcenter = (CONSOLE_WIDTH - menu_width) / 2;
const int Ycenter = (CONSOLE_HEIGHT - menu_height) / 2;

extern int gmode;

extern int player_field[MAP_SIZE][MAP_SIZE];
extern int bot_field[MAP_SIZE][MAP_SIZE];

extern int playerFieldStartX;
extern int botFieldStartX;

extern int playerFieldStartY;
extern int botFieldStartY;

extern AI bot1_AI;
extern AI bot2_AI;