#include "Client/client.h"
#include "Server/server.h"
#include "Server/gameLogic.h"
#include "Client/menuInterface.h"
#include "Client/inputHandler.c"

//TODO SNAKE NAME ADD TO MENU ???
//TODO FILE NAME ADD TO MENU ???
//TODO MENU BACK DONT WORK CORRECT
//TODO HOW TO SHOW DIFERENT SNAKES??
//TODO COLOR TEXT (SNAKE)???

// Checkpre Robinka: musim spravit nejake mapy bez prekazok
// + generovanie ovocia vymysliet ako a kedy by sa malo vykonat
// + zvacsovanie na nom odskusat(metoda by uz nejaka bola)

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
        Map map;
        createRandomMap(&map, 20, 10, 3);
        SnakeAtributes snake;
        snake.bodyX = (int*)malloc(sizeof(int) * 1);
        snake.bodyY = (int*)malloc(sizeof(int) * 1);
        snake.size = 1;
        snake.bodyX[0] = 1;
        snake.bodyY[0] = 1;
        snake.name = 'x';
        snake.isLive = 1;
        snake.color = 1;
        changeDirection(&snake, 90);
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
            checkCollision(&snake, &map);
            showSnake(&snake, &map);
            drawMap(&map,&snake);


            sleep(1);

        }
    }
}

/*
//test input
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

        Map map;
        createRandomMap(&map, 20, 10, 3);
        SnakeAtributes snake;
        snake.bodyX = (int*)malloc(sizeof(int) * 1);
        snake.bodyY = (int*)malloc(sizeof(int) * 1);
        snake.size = 1;
        snake.bodyX[0] = 1;
        snake.bodyY[0] = 1;
        snake.name = 'x';
        snake.isLive = 1;
        changeDirection(&snake, 90);
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
            checkCollision(&snake, &map);
            showSnake(&snake, &map);
            drawMap(&map);


            sleep(1);

        }

        // here the client will be connecting to a server
    }
    return 0;
}

int main() {
    Map map;
    int mode;

    // Užívateľská voľba pre typ mapy
    printf("Vyberte mod hry:\n");
    printf("1. Nacitat pevnu mapu z textoveho suboru\n");
    printf("2. Generovat nahodnu mapu\n");
    printf("Vas vyber: ");
    scanf("%d", &mode);

    if (mode == 1) {
        char fileName[256];
        char fullName[512];
        printf("Zadajte nazov suboru s mapou (napr. map1.txt):");
        scanf("%s", fileName);

        snprintf(fullName, sizeof(fullName), "Maps/%s", fileName);
        loadFixedMap(&map, fullName);
    }
    if (mode == 2) {
        createRandomMap(&map, 20, 10, 0);
    }
    printf("\n");


    SnakeAtributes snake;
    snake.bodyX = (int*)malloc(sizeof(int) * 1);
    snake.bodyY = (int*)malloc(sizeof(int) * 1);
    snake.size = 1;
    snake.bodyX[0] = 1;
    snake.bodyY[0] = 1;
    snake.name = 'x';
    snake.isLive = 1;
    changeDirection(&snake, 90);


    for (int i = 0; i < 10; i++) {
        printSnakeData(&snake);
        showSnake(&snake, &map);
        drawMap(&map);

        moveSnake(&snake, &map);
        checkCollision(&snake, &map);
        //generateApple(&map, 3, 1);
        //generateApple(&map, 5, 1);
        //generateApple(&map, 6, 2);
        //generateApple(&map);
        if (i == 4) {
            changeDirection(&snake, 180);
        }


        usleep(200000);
    }

    free(snake.bodyX);
    free(snake.bodyY);
    freeMap(&map);

    return 0;
}



int main() {
    Map map;
    int mode;

    // Užívateľská voľba pre typ mapy
    printf("Vyberte mod hry:\n");
    printf("1. Nacitat pevnu mapu z textoveho suboru\n");
    printf("2. Generovat nahodnu mapu\n");
    printf("Vas vyber: ");
    scanf("%d", &mode);

    if (mode == 1) {
        char fileName[256];
        char fullName[512];
        printf("Zadajte nazov suboru s mapou (napr. map1.txt):");
        scanf("%s", fileName);

        snprintf(fullName, sizeof(fullName), "Maps/%s", fileName);
        loadFixedMap(&map, fullName);
    }
    if (mode == 2) {
        createRandomMap(&map, 20, 10, 3);
    }
    printf("\n");


    SnakeAtributes snake;
    snake.bodyX = (int*)malloc(sizeof(int) * 1);
    snake.bodyY = (int*)malloc(sizeof(int) * 1);
    snake.size = 1;
    snake.bodyX[0] = 1;
    snake.bodyY[0] = 1;
    snake.name = 'A';
    snake.isLive = 1;
    changeDirection(&snake, 90);


    for (int i = 0; i < 10; i++) {
        printSnakeData(&snake);
        showSnake(&snake, &map);
        drawMap(&map);

        moveSnake(&snake, &map);
        checkCollision(&snake, &map);

        if (i == 4) {
            changeDirection(&snake, 0);
        }
    printf("\033[33;44mŽltý text na modrom pozadí\033[0m\n");

        usleep(200000);
    }

    free(snake.bodyX);
    free(snake.bodyY);
    freeMap(&map);

    return 0;
}

int main()
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
*/