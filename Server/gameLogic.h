#include <stdbool.h>
#include "mapGenerator.h"

typedef struct{
  int* bodyX;
  int* bodyY;
  int size;
  int isLive;
  int heading; //heading - user input (0,90,180,270)
  char name;
  int color;
  //Map* map; Maybe!!!

}SnakeAtributes;

void moveSnake(SnakeAtributes* snake, Map* map); // SURADNICU V DANOM SMERE ZMENI (HEADING = 90 => x + 1) KONTROLA CI SA MOZE POHNUT A CI ZJEDOL JABLKO

void checkCollision(SnakeAtributes* snake, Map* map); // CHECK IF SNAKE COLLISION WITH WALL OR SNAKE

void changeDirection(SnakeAtributes* snake,int heading); // CHANGE SNAKE HEADING

void deleteSnake(SnakeAtributes* snake); // ???

void increaseSize(SnakeAtributes* snake);// IF EAT APPLE ICREASE SIZE



bool isApple(int x,int y,Map* map); // IS APPLE HERE
bool isPassable(int x,int y, Map* map); //Can Move here

void showSnake(SnakeAtributes* snake,Map* map); // SHOW SNAKE ON MAP

void printSnakeData(SnakeAtributes* snake); //Testing Method