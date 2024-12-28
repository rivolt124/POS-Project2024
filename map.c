#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Inicializuje mapu a nastaví ju na prázdnu (s medzerami)
void vytvorMapu(char** map, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1) {
                map[i][j] = '~';
            } else if (j == 0 || j == width - 1) {
                map[i][j] = '|'; 
            } else {
                map[i][j] = ' '; // Prázdne políčko
            }
        }
    }
}

// Vykreslí mapu na konzolu
void vykresliMapu(char** map, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

// Generuje náhodné objekty na mape
void generuj(char** map, int width, int height, char object, int count) {
    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        int x, y;
        do {
            x = rand() % (height - 2) + 1; // Vyhneme sa okrajom
            y = rand() % (width - 2) + 1;
        } while (map[x][y] != ' '); // Nájdeme prázdne miesto
        map[x][y] = object;
    }
}
