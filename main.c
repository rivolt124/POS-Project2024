#include "Client/client.h"
#include "Server/server.h"

int main()
{
    gameSettings menu;
    init_client(&menu);
    if (menu.mainMenuChoose == 1)
    {

    }
    else if (menu.mainMenuChoose == 2) {
        Map map;
        createRandomMap(&map, 20, 10, 3);
        SnakeAtributes snake;
        SnakeAtributes snake1;
        snake.bodyX = (int*)malloc(sizeof(int) * 1);
        snake.bodyY = (int*)malloc(sizeof(int) * 1);
        snake.size = 1;
        snake.bodyX[0] = 1;
        snake.bodyY[0] = 1;
        snake.name = '1';
        snake.isLive = 1;
        snake.color = 1;

        snake1.bodyX = (int*)malloc(sizeof(int) * 1);
        snake1.bodyY = (int*)malloc(sizeof(int) * 1);
        snake1.size = 1;
        snake1.bodyX[0] = 5;
        snake1.bodyY[0] = 1;
        snake1.name = '2';
        snake1.isLive = 1;
        snake1.color = 1;
        changeDirection(&snake1, 90);
        generateApple(&map);
        generateApple(&map);


        while (1) {
            clearConsole3();
            char ch;
            ch = init_inputHandler();

            switch (ch) {
                case 'a':
                    changeDirection(&snake, 270);
                break;
                case 'd':
                    changeDirection(&snake, 90);
                break;
                case 'w':
                    changeDirection(&snake, 0);
                break;
                case 's':
                    changeDirection(&snake, 180);
                break;
                case 'h':
                    break;
                case 'q':
                    break;
            }

            moveSnake(&snake, &map);
            moveSnake(&snake1, &map);
            checkCollision(&snake, &map);
            showSnake(&snake, &map);
            drawMap(&map);


            sleep(1);

        }
    }
}
