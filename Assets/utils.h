#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

//#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct gameSettings {
    int mainMenuChoose; // 1 New Game, 2 Connect to game
    int gameTypeMode;   // 1 Standard mode, 2 Time mode
    int timeSeconds;    // Time in seconds
    int gameWorld;      // 1 World with obstacles, 2 World without obstacles
    int onlineMode;     // 1 SinglePlayer, 2 MultiPlayer
    char * selectedMap; //
    int mapWidth;
    int mapHeight;
} gameSettings;

typedef struct {
    int width;
    int height;
    int appleExist;
    char** gridData;
} map_data;

typedef struct{
    int* bodyX;
    int* bodyY;
    int size;
    int isLive;
    char heading;
} snake_data;

#define PLAYER  'X'
#define ENEMY   'Z'

#define UP      'W'
#define DOWN    'S'
#define RIGHT   'D'
#define LEFT    'A'
#define DEFAULT_HEADING DOWN

#define APPLE               'O'
#define BARRIER             '#'
#define SPACE               ' '
#define HORIZONTAL_BORDER   '-'
#define VERTICAL_BORDER     '|'

#define RED_BG      "\033[41m"    // Red background
#define GREEN_BG    "\033[42m"    // Green background
#define YELLOW_BG   "\033[43m"    // Yellow background
#define GRAY_BG     "\x1b[100m"   // Grey background

#define RESET       "\033[0m"     // Color reset
#define RED         "\033[31m"    // Apples
#define GREEN       "\033[32m"    // Player snake
#define YELLOW      "\033[33m"    // Enemy snake

#endif
