#include "Client/client.h"
#include "Server/server.h"
#include "Server/gameLogic.h"


//TODO SNAKE NAME ADD TO MENU ???
//TODO FILE NAME ADD TO MENU ???
//TODO MENU BACK DONT WORK CORRECT
//TODO HOW TO SHOW DIFERENT SNAKES??
//TODO COLOR TEXT (SNAKE)??? printf("\033[33;44mŽltý text na modrom pozadí\033[0m\n");

int main()
{
    Map map;
    int mode;

    createRandomMap(&map, 20, 10, 3);

    SnakeAtributes snake;
    drawMap(&map);
    snake.x = 1;
    snake.y = 1;
    snake.name = 'A';
    snake.isLive = 1;
    changeDirection(&snake, 90);
    showSnake(&snake,&map);
    drawMap(&map);



    //printSnakeData(&snake);

    for (int i = 0; i < 10; i++) {
        //clearConsole3();
        moveSnake(&snake, &map);
        checkCollision(&snake,&map);
        showSnake(&snake,&map);
        drawMap(&map);
        if (i == 4) {
            changeDirection(&snake, 180);
        }
        //printSnakeData(&snake);
        sleep(1);
    }
    freeMap(&map);

    return 0;
}

/*int main()
{
    int choice = init_client();
    if (choice == 1)
    {
        serverSharedMemory ssm;
        init_server(&ssm);
        shared_memory_ready(&ssm);
    }
    else if (choice == 2) {
        // here the client will be connecting to a server
    }
    return 0;
}

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
    } else if (mode == 2) {
        int width, height, obstacleCount;
        printf("Zadajte sirku a vysku mapy: ");
        scanf("%d %d", &width, &height);
        printf("Zadajte pocet prekazok: ");
        scanf("%d", &obstacleCount);

        // Vytvorenie náhodnej mapy
        createRandomMap(&map, width, height, obstacleCount);
    } else {
        printf("Neplatny vyber.\n");
        return 1;
    }

    drawMap(&map);

    freeMap(&map);

    return 0;
}
*/