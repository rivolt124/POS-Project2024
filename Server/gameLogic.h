#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "../Assets/utils.h"
#include "mapGenerator.h" // This could be removed in the future!

void showPlayerSnake(snake_data* snake, map_data* map);
void deleteSnake(snake_data* snake, map_data* map);
void moveSnake(snake_data* snake, map_data* map);
void changeDirection(snake_data* snake, char heading);
void printScore(snake_data* snake);
void cycle(snake_data* snake,map_data* map);

#endif
