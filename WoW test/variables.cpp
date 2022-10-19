#include "variables.h"

int player_field[MAP_SIZE][MAP_SIZE] = { 0 };
int bot_field[MAP_SIZE][MAP_SIZE] = { 0 };

extern int gmode = NULL; 

extern int playerFieldStartX = (CONSOLE_WIDTH - 24 * 2.5) / 2 + (1 * 2);
extern int playerFieldStartY = (CONSOLE_HEIGHT - 12) / 2 + 1;

extern int botFieldStartX = ((CONSOLE_WIDTH - 24 * 2.5) / 2) * 2 + 24 + (1 * 2);
extern int botFieldStartY = (CONSOLE_HEIGHT - 12) / 2 + 1;

extern AI bot1_AI = { 0 };
extern AI bot2_AI = { 0 };