#ifndef MENU_INTERFACE_H
#define MENU_INTERFACE_H

#include "../Assets/utils.h"

void init_menu(gameSettings *menu);
void clearConsole();
void clearConsole2();
void clearConsole3();
char displayMenu(const char* menuTitle, const char* options[], int optionCount);
void showOnlineModeMenu(gameSettings* settings);
void showGameWorldMenu(gameSettings* settings);
void showGameTypeMenu(gameSettings* settings);
void showMainMenu(gameSettings* settings);
void printGameSettings(const gameSettings* settings);
int  menuPause();

#endif