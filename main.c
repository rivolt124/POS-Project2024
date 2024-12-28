#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include <locale.h>         //na UTF-8

int main() {
    int sirka = 20;
    int vyska = 10;

    // Alokácia pamäte pre 2D mapu
    char** map = (char**)malloc(vyska * sizeof(char*));
    for (int i = 0; i < vyska; i++) {
        map[i] = (char*)malloc(sirka * sizeof(char));
    }

    // Vytvorenie a vykreslenie mapy
    vytvorMapu(map, sirka, vyska);

    for (int i = 0; i < vyska; i++) {
        for (int j = 0; j < sirka; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }

    // Uvoľnenie pamäte
    for (int i = 0; i < vyska; i++) {
        free(map[i]);
    }
    free(map);

    return 0;
}

