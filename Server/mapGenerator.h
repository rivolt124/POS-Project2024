#pragma once
#include "gameLogic.h"

typedef struct {
    int width;
    int height;
    int appleExist;
    char** data;
} Map;

#define RESET_BG "\033[0m"       // Resetovanie farieb
#define RED_BG "\033[41m"     // Červené pozadie
#define GREEN_BG "\033[42m"   // Zelené pozadie
#define YELLOW_BG "\033[43m"  // Žlté pozadie
#define BLUE_BG "\033[44m"    // Modré pozadie
#define BLINK_RED "\033[5;31m"
#define GRAY_BG "\x1b[100m"

#define RESET        "\033[0m"      // Reset farieb
#define RED          "\033[31m"    // Červená
#define GREEN        "\033[32m"    // Zelená
#define YELLOW       "\033[33m"    // Žltá
#define BLUE         "\033[34m"    // Modrá
#define MAGENTA      "\033[35m"    // Fialová
#define CYAN         "\033[36m"    // Tyrkysová
#define WHITE        "\033[37m"    // Biela
#define ORANGE "\x1b[38;5;208m"
#define PINK "\x1b[38;5;213m"

// na načítanie pevnej mapy zo súboru
void loadFixedMap(Map* map, const char* filename);

// na nacitanie náhodnej mapy
void createRandomMap(Map* map, int width, int height, int obstacleCount);

// na vykreslenie mapy
void drawMap(Map* map,SnakeAtributes* snake);

// na uvoľnenie pamäte
void freeMap(Map* map);

//generovanie jablka na mape
void generateApple(Map* map);