#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "../Assets/utils.h"

void moveSnake(snake_data* snake, map_data* map);
void checkCollision(snake_data* snake, map_data* map);
void changeDirection(snake_data* snake,int heading);
void deleteSnake(snake_data* snake);
void increaseSize(snake_data* snake);
void showSnake(snake_data* snake,map_data* map);
void printSnakeData(snake_data* snake);
bool isApple(int x,int y,map_data* map);
bool isPassable(int x,int y, map_data* map);

#endif
