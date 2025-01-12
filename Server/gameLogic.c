#include "gameLogic.h"

void showSnake(snake_data* snake, map_data* map, char symbol)
{
    if (snake->isLive == 0)
        return;

    for (int i = 0; i < snake->size; i++) {
        map->gridData[snake->bodyX[i]][snake->bodyY[i]] = symbol;
    }
}

void deleteSnake(snake_data* snake, map_data* map)
{
    if (snake->isLive == 1)
        return;

    for (int i = 0; i < snake->size; i++)
        map->gridData[snake->bodyX[i]][snake->bodyY[i]] = SPACE;
}

static void increaseSize(snake_data* snake) {
    snake->size++;

    // Nastavenie novej chvostovej pozície
    snake->bodyX[snake->size - 1] = snake->bodyX[snake->size - 2];
    snake->bodyY[snake->size - 1] = snake->bodyY[snake->size - 2];
}

static bool isApple(int x, int y, map_data* map) {
    return map->gridData[x][y] == APPLE;
}

static bool checkCollision(int x, int y, map_data* map) {
    const char target = map->gridData[x][y];
    return (target == BARRIER || target == HORIZONTAL_BORDER || target == VERTICAL_BORDER || target == ENEMY || target == PLAYER);
}

void moveSnake(snake_data* snake, map_data* map)
{
    if (snake->isLive == 0)
        return;

    int targetX = snake->bodyX[0];
    int targetY = snake->bodyY[0];

    switch (snake->heading) {
        case UP:
            targetY--;
            break;
        case DOWN:
            targetY++;
            break;
        case RIGHT:
            targetX++;
            break;
        case LEFT:
            targetX--;
            break;
        default:
            break;
    }

    if (checkCollision(targetX, targetY, map))
    {
        snake->isLive = 0;
        deleteSnake(snake, map);
        return;
    }

    if (isApple(targetX, targetY, map))
    {
        increaseSize(snake);
        map->gridData[targetX][targetY] = SPACE;
        map->appleExist = 0;
    }
    else
    {
        int tailX = snake->bodyX[snake->size - 1];
        int tailY = snake->bodyY[snake->size - 1];
        map->gridData[tailX][tailY] = SPACE;
    }

    if (snake->size == 1) {
        int oldX = snake->bodyX[0];
        int oldY = snake->bodyY[0];

        map->gridData[oldX][oldY] = SPACE;

        snake->bodyX[0] = targetX;
        snake->bodyY[0] = targetY;
    } else {
        for (int i = snake->size - 1; i > 0; i--) {
            snake->bodyX[i] = snake->bodyX[i - 1];
            snake->bodyY[i] = snake->bodyY[i - 1];
        }
        snake->bodyX[0] = targetX;
        snake->bodyY[0] = targetY;
    }

    map->gridData[targetX][targetY] = PLAYER;
}

void changeDirection(snake_data* snake, char heading) {
    snake->heading = heading;
}

void printScore(snake_data* snake) {
    printf("\nACHIEVED SCORE: %d\n", snake->size - 1);
}

void cycle(snake_data* snake,map_data* map) // This will have to be modified based on the implementation of Processes
{
    if (snake->isLive == 1)
    {
        moveSnake(snake, map);
        drawMap(map);
        if (map->appleExist == 0)
            generateApple(map);

    }
}
