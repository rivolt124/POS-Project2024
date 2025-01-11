#include "mapGenerator.h"
#include "gameLogic.h"
#include "inputHandler.h"
#include "menuInterface.h"

void start_app(gameSettings* settings, map_data* map, snake_data* snake, communication_data* comm)
{
	init_menu(settings);
	if (settings->mainMenuChoose == 1)
	{
		loadFixedMap(map, settings->selectedMap);
	}
}

int main()
{
	// Structs
	gameSettings settings;
    map_data map;
    snake_data snake;
	communication_data comm;

	// Init necessary data


    placeSnake(&map, &snake);
    generateApple(&map);

    while (snake.isLive == 1)
    {
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
