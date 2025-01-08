#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

typedef struct {
    int width;
    int height;
    int appleExist;
    char** gridMap;
} map_data;

//#define RESET_BG "\033[0m"
#define RED_BG      "\033[41m"    // Red background
#define GREEN_BG    "\033[42m"    // Green background
#define YELLOW_BG   "\033[43m"    // Yellow background
#define GRAY_BG     "\x1b[100m"   // Grey background

#define RESET       "\033[0m"     // Color reset
#define RED         "\033[31m"    // Apples
#define GREEN       "\033[32m"    // Player snake
#define YELLOW      "\033[33m"    // Enemy snake


void loadFixedMap(map_data* map, const char* filename);
void createRandomMap(map_data* map, int width, int height, int obstacleCount);
void drawMap(map_data* map);
void freeMap(map_data* map);
void generateApple(map_data* map);

#endif