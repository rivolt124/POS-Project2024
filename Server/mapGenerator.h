#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include "../Assets/utils.h"

void loadFixedMap(map_data* map, const char* filename);
void drawMap(map_data* map);
void generateApple(map_data* map);
void placeSnake(map_data* map, snake_data* snake);

#endif