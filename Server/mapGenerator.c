#include "mapGenerator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void loadFixedMap(Map* map, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Unable to open file %s\n", filename);
        exit(1);
    }

    // dimensions
    fscanf(file, "%d, %d\n", &map->width, &map->height);

    // Alloc
    map->data = (char**)malloc(map->width * sizeof(char*));
    for (int x = 0; x < map->width; x++) {
        map->data[x] = (char*)malloc(map->height * sizeof(char));
    }

    // Initialize
    for (int x = 0; x < map->width; x++) {
        for (int y = 0; y < map->height; y++) {
            if (y == 0 || y == map->height - 1) {
                map->data[x][y] = '~';
            } else if (x == 0 || x == map->width - 1) {
                map->data[x][y] = '|';
            } else {
                map->data[x][y] = ' ';
            }
        }
    }

    // Add obstacles
    int x, y;
    while (fscanf(file, "%d, %d\n", &x, &y) == 2) {
        if (x > 0 && x < map->width - 1 && y > 0 && y < map->height - 1) {
            map->data[x][y] = '#';
        }
    }

    fclose(file);
}


void createRandomMap(Map* map, int width, int height, int obstacleCount) {
    map->width = width;
    map->height = height;

    // Allocate
    map->data = (char**)malloc(width * sizeof(char*));
    for (int x = 0; x < width; x++) {
        map->data[x] = (char*)malloc(height * sizeof(char));
    }

    // Initialize
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (y == 0 || y == height - 1) {
                map->data[x][y] = '~';
            } else if (x == 0 || x == width - 1) {
                map->data[x][y] = '|';
            } else {
                map->data[x][y] = ' ';
            }
        }
    }

    srand(time(NULL));
    for (int i = 0; i < obstacleCount; i++) {
        int x, y;
        do {
            x = rand() % (width - 2) + 1;
            y = rand() % (height - 2) + 1;
        } while (map->data[x][y] != ' ');
        map->data[x][y] = '#';
    }
}


void drawMap(Map* map) {
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            printf("%c", map->data[x][y]);
        }
        printf("\n");
    }
}


void freeMap(Map* map) {
    for (int x = 0; x < map->width; x++) {
        free(map->data[x]);
    }
    free(map->data);
}


