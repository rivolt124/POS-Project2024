#include "gameLogic.h"

#include <stdlib.h>


void showSnake(SnakeAtributes* snake, Map* map) {
    if (!snake->isLive) return;

    // Show player name(character)
    map->data[snake->x][snake->y] = snake->name;
}

bool isApple(int x, int y, Map* map) {
    return map->data[x][y] == 'o'; // Jablko bude ako o
}

bool isPassable(int x, int y, Map* map) {
    return map->data[x][y] == ' ' || isApple(x, y, map); // if its empty ' ' and its not an apple, then its passable
}

void moveSnake(SnakeAtributes* snake,Map* map) {
    if (!snake->isLive) {
        return;
    }

    if (snake->heading == 90) {
        snake->x++;
    }

    if (snake->heading == 270) {
        snake->x--;
    }

    if (snake->heading == 0) {
        snake->y--;
    }

    if (snake->heading == 180) {
        snake->y++;

    }
}

void increaseSize(SnakeAtributes* snake) {
    snake->size += 1;
}

void changeDirection(SnakeAtributes* snake, int newHeading) {
    if (abs(newHeading - snake->heading) != 180) {          //only if its not going backwards
        snake->heading = newHeading;
    }
}

void checkCollision(SnakeAtributes* snake, Map* map) {
    if (map->data[snake->x][snake->y] == '#' ||
        map->data[snake->x][snake->y] == '~' ||
        map->data[snake->x][snake->y] == '|') {
        snake->isLive = 0;
        }
}
