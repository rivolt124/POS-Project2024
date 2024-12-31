#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "Menu.h"

int main() {

    int width = 20;
    int height = 10;

    char** map = (char**)malloc(height * sizeof(char*));
    for (int i = 0; i < height; i++) {
        map[i] = (char*)malloc(width * sizeof(char));
    }

    createMap(map, width, height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < height; i++) {
        free(map[i]);
    }
    free(map);

    printMainMenu();

    return 0;
}

