#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct {
    int width;
    int height;
    int appleExist;
    char** gridData;
} map_data;

typedef struct{
    int* bodyX;
    int* bodyY;
    int size;
    int isLive;
    int heading; // Up, Down, Left, Right
} snake_data;

#define PLAYER 'X'
#define ENEMY  'Z'

#define RED_BG      "\033[41m"    // Red background
#define GREEN_BG    "\033[42m"    // Green background
#define YELLOW_BG   "\033[43m"    // Yellow background
#define GRAY_BG     "\x1b[100m"   // Grey background

#define RESET       "\033[0m"     // Color reset
#define RED         "\033[31m"    // Apples
#define GREEN       "\033[32m"    // Player snake
#define YELLOW      "\033[33m"    // Enemy snake

#endif
