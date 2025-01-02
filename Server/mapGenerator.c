#include "mapGenerator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// pevna mapa
void loadFixedMap(Map* map, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Unable to open file %s\n", filename);
        exit(1);
    }

    // rozmery
    fscanf(file, "%d, %d\n", &map->width, &map->height);
    //
    map->data = (char**)malloc(map->height * sizeof(char*));
    for (int i = 0; i < map->height; i++) {
        map->data[i] = (char*)malloc(map->width * sizeof(char));
    }

    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            if (i == 0 || i == map->height - 1) {
                map->data[i][j] = '~';
            } else if (j == 0 || j == map->width - 1) {
                map->data[i][j] = '|';
            } else {
                map->data[i][j] = ' ';
            }
        }
    }

    // Načítanie pozícií prekážok
    int x, y;
    while (fscanf(file, "%d, %d\n", &x, &y) == 2) {
        if (x > 0 && x < map->height - 1 && y > 0 && y < map->width - 1) {
            map->data[x][y] = '#'; // Prekážka
        }
    }

    fclose(file);
}

// random mapa
void createRandomMap(Map* map, int width, int height, int obstacleCount) {
    map->width = width;
    map->height = height;

    // Alokácia pamate
    map->data = (char**)malloc(height * sizeof(char*));
    for (int i = 0; i < height; i++) {
        map->data[i] = (char*)malloc(width * sizeof(char));
    }


    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1) {
                map->data[i][j] = '~';
            } else if (j == 0 || j == width - 1) {
                map->data[i][j] = '|';
            } else {
                map->data[i][j] = ' ';
            }
        }
    }

    // prekazky
    srand(time(NULL));
    for (int i = 0; i < obstacleCount; i++) {
        int x, y;
        do {
            x = rand() % (height - 2) + 1;
            y = rand() % (width - 2) + 1;
        } while (map->data[x][y] != ' ');
        map->data[x][y] = '#';
    }
}

// vykreslenie mapy
void drawMap(Map* map) {
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            printf("%c", map->data[i][j]);
        }
        printf("\n");
    }
}

// dealokovanie pamate
void freeMap(Map* map) {
    for (int i = 0; i < map->height; i++) {
        free(map->data[i]);
    }
    free(map->data);
}

