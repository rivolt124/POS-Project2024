#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include <pthread.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/types.h>

typedef struct {
	pthread_t server;
	pthread_mutex_t lock;
	pthread_cond_t cond_client;
	pthread_cond_t cond_server;
} communication_data;

typedef struct gameSettings {
    int mainMenuChoose; // 1 New Game, 2 Connect to game
    int gameTypeMode;   // 1 Standard mode, 2 Time mode
    int timeSeconds;    // Time in seconds
    int gameWorld;      // 1 World with obstacles, 2 World without obstacles
    int onlineMode;     // 1 SinglePlayer, 2 MultiPlayer
    char * selectedMap; //
	int serverID;
    int mapWidth;
    int mapHeight;
} gameSettings;

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
    char heading;
} snake_data;

#define MAX_PLAYERS 4

typedef struct {
	map_data map;
	snake_data snakes[MAX_PLAYERS];
	int numPlayers;
} shared_game_data;

#define S_SHM_ID 4231

typedef struct {
	int* id;
	int activeGames;
} shared_shm_id;

#define PLAYER  'X'
#define ENEMY   'Z'

#define UP      'W'
#define DOWN    'S'
#define RIGHT   'D'
#define LEFT    'A'
#define DEFAULT_HEADING DOWN

#define APPLE               'O'
#define BARRIER             '#'
#define SPACE               ' '
#define HORIZONTAL_BORDER   '-'
#define VERTICAL_BORDER     '|'

#define GRAY_BG     "\x1b[100m"   // Grey background
#define RESET       "\033[0m"     // Color reset
#define RED         "\033[31m"    // Apples
#define GREEN       "\033[32m"    // Player snake
#define YELLOW      "\033[33m"    // Enemy snake

void syn_data_init(communication_data* this, void* (*function)(void*), void* arg);
void syn_data_destroy(communication_data* this);
void snake_data_init(snake_data* snake, int x, int y);

#endif
