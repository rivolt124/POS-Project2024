//main.c
#include <stdio.h>
#include "Client/client.h"
#include "Server/mapGenerator.h"
#include "Client/menuInterface.h"


int main()
{
    printf("Hello World");
    return 0;
}

/*
int main()
{
    gameSettings settings;
    showMainMenu(&settings);
    printGameSettings(&settings);
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