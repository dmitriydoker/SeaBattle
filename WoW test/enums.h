#pragma once

enum Keys {
    ESC = 27, ARROW_START = 224, ENTER = 13,
    UP_ARROW = 72, DOWN_ARROW = 80, LEFT_ARROW = 75, RIGHT_ARROW = 77,
    ROTATE_BUTTON = 32
};

enum ConsoleColor {
    // Standard text colors
    GRAY = 8, BLUE, GREEN,
    TEAL, RED, PINK,
    YELLOW, WHITE,
    // Faded text colors
    BLACK = 0, BLUE_FADE, GREEN_FADE,
    TEAL_FADE, RED_FADE, PINK_FADE,
    YELLOW_FADE, WHITE_FADE,
};

enum Stats {
    GAMES_PLAYED = 0, WINS = 1,
    WINRATE = 2, SHIPS_DESTROYED = 3
};

enum CeilStatus {
    EMPTY = 0, ALIVE = 1, DAMAGED = 2,
    DROWN = 3, DUMMY = 4
};

enum PreGame {
    PLAYER_VS_BOT = 1, BOT_VS_BOT= 2,
    MANUAL_POSITIONING = 1, AUTO_POSITIONING = 2,
    EXIT = 3
};