#include <stdbool.h>
#include "mapGenerator.h"

typedef struct{
  int x;
  int y;
  int size;
  int isLive;
  int heading; //heading - user input (0,90,180,270)
  char name;
}SnakeAtributes;

void move(SnakeAtributes); // SURADNICU V DANOM SMERE ZMENI (HEADING = 90 => x + 1) KONTROLA CI SA MOZE POHNUT A CI ZJEDOL JABLKO

void checkCollision(SnakeAtributes); // CHECK IF SNAKE COLLISION WITH WALL OR SNAKE

void changeDirection(SnakeAtributes,int heading); // CHANGE SNAKE HEADING

void deleteSnake(SnakeAtributes); // ???

void increaseSize(SnakeAtributes);// IF EAT APPLE ICREASE SIZE



bool isApple(int x,int y,Map map); // IS APPLE HERE
bool isPassable(int x,int y, Map map); //Can Move here

void showSnake(SnakeAtributes,Map map); // SHOW SNAKE ON MAP

