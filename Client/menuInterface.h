#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct gameSettings {
    int mainMenuChoose; // 1 New Game, 2 Connect to game
    int gameTypeMode;   // 1 Standard mode, 2 Time mode
    int timeSeconds;    // Time in seconds
    int gameWorld;      // 1 World with obstacles, 2 World without obstacles
    int onlineMode;     // 1 SinglePlayer, 2 MultiPlayer
} gameSettings;

void clearConsole();
void clearConsole2();
int displayMenu(const char* menuTitle, const char* options[], int optionCount);
void showOnlineModeMenu(gameSettings* settings);
void showGameWorldMenu(gameSettings* settings);
void showGameTypeMenu(gameSettings* settings);
void showMainMenu(gameSettings* settings);
void printGameSettings(const gameSettings* settings);

