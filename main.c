#include "Client/client.h"
#include "Client/menuInterface.h"
#include "Server/server.h"
#include "Server/gameLogic.h"


//TODO SNAKE NAME AD TO MENU ???
//TODO MENU BACK DONT WORK CORRECT
//TODO HOW TO SHOW DIFERENT SNAKES??

int main()
{
    gameSettings menu;
    init_client(&menu);
    if (menu.mainMenuChoose == 1)
    {
        serverSharedMemory ssm;
        init_server(&ssm);
        shared_memory_ready(&ssm);
    }
    else if (menu.mainMenuChoose == 2) {
        // here the client will be connecting to a server
    }
    return 0;
}
/*
int init_map() {
    Map map;
    int mode;

    printf("Vyberte mod hry:\n");
    printf("1. Nacitat pevnu mapu z textoveho suboru\n");
    printf("2. Generovat nahodnu mapu\n");
    printf("Vas vyber: ");
    scanf("%d", &mode);

    if (mode == 1) {
        char filename[256];
        printf("Zadajte nazov suboru s mapou (napr. map1.txt):");
        scanf("%s", filename);


        loadFixedMap(&map, filename);
    }

    drawMap(&map);
    SnakeAtributes snake;
    snake.x = 1;
    snake.y = 1;
    changeDirection(&snake, 90);
    for (int i = 0; i < 10; i++) {
        moveSnake(&snake, &map);
        checkCollision(&snake,&map);
        showSnake(&snake,&map);
        drawMap(&map);
        if (i == 4) {
            changeDirection(&snake, 180);
        }
        sleep(1);
    }

    freeMap(&map);

    return 0;
}
*/