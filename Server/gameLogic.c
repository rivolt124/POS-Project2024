#include "gameLogic.h"

#include <mapGenerator.h>
#include <stdio.h>
#include <stdlib.h>

void showSnake(snake_data* snake, map_data* map)
{
    if (snake->isLive == 0)
    {

    }

    for (int i = 0; i < snake->size; i++) {
        int x = snake->bodyX[i];
        int y = snake->bodyY[i];
        map->gridData[x][y] = PLAYER;
    }
}

bool isApple(int x, int y, map_data* map) {
    return map->gridData[x][y] == 'o';
}

bool isPassable(int x, int y, map_data* map) {
    return map->gridData[x][y] == ' ' || isApple(x, y, map);
}

void moveSnake(snake_data* snake, map_data* map) {
    int newX = snake->bodyX[0];
    int newY = snake->bodyY[0];

    switch (snake->heading) {
        case 0: newY--; break;  // up
        case 90: newX++; break; // rigth
        case 180: newY++; break; // down
        case 270: newX--; break; // leftt
    }

    if (!isPassable(newX, newY, map)) {
        snake->isLive = 0; //himself or borde
        return;
    }

    if (isApple(newX, newY, map)) {
        increaseSize(snake);
        map->gridData[newX][newY] = ' ';
        map->appleExist = 0;
    } else {
        int tailX = snake->bodyX[snake->size - 1];
        int tailY = snake->bodyY[snake->size - 1];
        map->gridData[tailX][tailY] = ' ';
    }

    if (snake->size == 1) {
        int oldX = snake->bodyX[0];
        int oldY = snake->bodyY[0];

        map->gridData[oldX][oldY] = ' ';

        snake->bodyX[0] = newX;
        snake->bodyY[0] = newY;
    } else {
        for (int i = snake->size - 1; i > 0; i--) {
            snake->bodyX[i] = snake->bodyX[i - 1];
            snake->bodyY[i] = snake->bodyY[i - 1];
        }
        snake->bodyX[0] = newX;
        snake->bodyY[0] = newY;
    }

    map->gridData[newX][newY] = PLAYER;
}



// Zvýšenie veľkosti hada po zjedení jablka
void increaseSize(snake_data* snake) {
    snake->size++;
    snake->bodyX = realloc(snake->bodyX, snake->size * sizeof(int));
    snake->bodyY = realloc(snake->bodyY, snake->size * sizeof(int));

    // Nastavenie novej chvostovej pozície
    snake->bodyX[snake->size - 1] = snake->bodyX[snake->size - 2];
    snake->bodyY[snake->size - 1] = snake->bodyY[snake->size - 2];
}

void changeDirection(snake_data* snake, int newHeading) {
    snake->heading = newHeading;  // Zmena smeru pohybu hada
}

void checkCollision(snake_data* snake, map_data* map) {
    int headX = snake->bodyX[0];
    int headY = snake->bodyY[0];

    // border or wall
    if (map->gridData[headX][headY] == '#' || map->gridData[headX][headY] == '~' || map->gridData[headX][headY] == '|') {
        snake->isLive = 0;
    }

    // selfcollisiion
    for (int i = 1; i < snake->size; i++) {
        if (headX == snake->bodyX[i] && headY == snake->bodyY[i]) {
            snake->isLive = 0;
        }
    }
}

void printScore(snake_data* snake) {
    printf("\nACHIEVED SCORE: %d\n", snake->size - 1);
}
