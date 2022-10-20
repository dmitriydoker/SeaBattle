#pragma once

#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<string>
#include<cstdio>
#include<fstream>
#include<vector>
#include "variables.h"
#include "enums.h"

using namespace std;


void SetCursorPosition(short x, short y);

void ShowConsoleCursor(bool showFlag);

void SetColor(ConsoleColor text, ConsoleColor background);

void printFrame(const int& x, const int& y);

void getKeyMenu(bool& run, int& activeOption, const int& optionAmount);

bool in(int& ship, int* arr);

void centerCursor(string text, int option_count);

int centerOfNumInOptions(int num, int options);

void isActiveButton(bool value);



void menu(int& activeOption);

void showStatistics(const Player* current_player);

int gameMode();

int choosePositioning();



Player* authorisation();

void createUser();

void savePlayers();



bool saveExist();

void deleteSaving();

int pregame_settings(Player* current_user);

void loadGame();

void game(Player* current_user, string game_status);

void pauseGame();

bool end();

void clearField(int field[10][10]);



void setField(int field[10][10]);

bool inField(int coord);

int getRandCoord();

bool getRandBool();

void setShip(int ship, int* availableShips);

void shotComment(int x, int y, int field[10][10], string text);



void manualPosition();

void autoPosition(int field[MAP_SIZE][MAP_SIZE]);

bool applyPosition(int field[MAP_SIZE][MAP_SIZE], int ship, int x, int y, bool rotated);



void shoot();

void bot_shot(AI& bot_AI, int enemy_field[10][10]);



int inverseDir(int dir);

void processOnDirection(int& x, int& y, int dir);

bool isDrown(int x, int y, int field[10][10]);

void makeDrown(int x, int y, int field[10][10], int direction);