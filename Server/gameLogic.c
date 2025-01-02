#include "gameLogic.h"


void showSnake(SnakeAtributes* snake, Map* map) {
    if (!snake->isLive) return;

    // Show player name(character)
    map->data[snake->x][snake->y] = snake->name;
}

bool isApple(int x, int y, Map map) {
    return map.data[x][y] == 'o'; // Jablko bude ako o
}

bool isPassable(int x, int y, Map map) {
    return map.data[x][y] == ' ' || isApple(x, y, map); // if its empty ' ' and its not an apple, then its passable
}
