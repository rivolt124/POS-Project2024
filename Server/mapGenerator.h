#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include "../Assets/utils.h"

void loadFixedMap(map_data* map, const char* filename);
//void createRandomMap(map_data* map, int width, int height, int obstacleCount); We don't handle the accessibility for each position
void drawMap(map_data* map);
void freeMap(map_data* map);
void generateApple(map_data* map);
void placeSnake(map_data* map, snake_data* snake);

#endif