#include "mapGenerator.h"
#include "gameLogic.h"
#include "inputHandler.h"


int main()
{
    map_data map;
    snake_data snake;
    snake.bodyX = malloc(sizeof(int));  // Allocate memory for bodyX
    snake.bodyY = malloc(sizeof(int));
    loadFixedMap(&map, "../Maps/mapOne.txt");

    //game(&snake, &map);
    placeSnake(&map, &snake);
    generateApple(&map);

    while (snake.isLive == 1)
    {
        //clearConsole3();
        switch (init_inputHandler()) {
        case 'a':
            changeDirection(&snake, LEFT);
            break;
        case 'd':
            changeDirection(&snake, RIGHT);
            break;
        case 'w':
            changeDirection(&snake, UP);
            break;
        case 's':
            changeDirection(&snake, DOWN);
            break;
        case 'p':
            break;
        case 'q':
            snake.isLive = 0;
            deleteSnake(&snake, &map);
            printScore(&snake);
            return 0;
        default:
            break;
        }

        cycle(&snake, &map);
    }


    free(snake.bodyX);
    free(snake.bodyY);
    freeMap(&map);
    return 0;
}
