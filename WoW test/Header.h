#pragma once

#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<math.h>
#include<string>
#include<cstdio>
#include<fstream>
#include<vector>
#include "enums.h"
#include "variables.h"

using namespace std;

struct Player {
    string login;
    string password;
    float stats[5] = { 0, 0, 0, 0, 0 };
};

void SetCursorPosition(short x, short y);

void SetColor(ConsoleColor text, ConsoleColor background);

void printFrame(const int& x, const int& y);

void getKey(bool& run, int& activeOption, const int& optionAmount);

bool in(int& ship, int* arr);

void centerCursor(string text, int option_count);

int centerOfNumInOptions(int num, int options);

void isActiveButton(bool value);

void menu(int& activeOption);

void showStatistics(const Player* current_player);

int gameMode();

int choosePositioning();
