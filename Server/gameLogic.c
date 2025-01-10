#include "gameLogic.h"
#include "../Client/inputHandler.c"
#include <stdio.h>
#include <stdlib.h>

void game(SnakeAtributes *snake, Map* map)
{
	while (1) {
		char ch;
		//clearConsole3();
		ch = init_inputHandler();

		switch (ch) {
			case 'a':
				changeDirection(snake, 270);
				break;
			case 'd':
				changeDirection(snake, 90);
				break;
			case 'w':
				changeDirection(snake, 0);
				break;
			case 's':
				changeDirection(snake, 180);
				break;
			case 'h':
				break;
			case 'q':
				return;
			default:
				break;
		}

		moveSnake(snake, map);
		checkCollision(snake, map);
		showSnake(snake, map);
		drawMap(map);
	}

}

void showSnake(SnakeAtributes* snake, Map* map) {
	if (snake->isLive == 0) return;

	for (int i = 0; i < snake->size; i++) {
		int x = snake->bodyX[i];
		int y = snake->bodyY[i];
		map->data[x][y] = snake->name;
	}
}

bool isApple(int x, int y, Map* map) {
	return map->data[x][y] == 'o';
}

bool isPassable(int x, int y, Map* map) {
	return map->data[x][y] == ' ' || isApple(x, y, map);
}

void moveSnake(SnakeAtributes* snake, Map* map) {
	int newX = snake->bodyX[0];
	int newY = snake->bodyY[0];

	switch (snake->heading) {
		case 0: newY--; break;  // up
		case 90: newX++; break; // rigth
		case 180: newY++; break; // down
		case 270: newX--; break; // leftt
	}

	if (!isPassable(newX, newY, map)) {
		snake->isLive = 0; //himself or borde
		return;
	}

	if (isApple(newX, newY, map)) {
		increaseSize(snake);
		map->data[newX][newY] = ' ';
		map->appleExist = 0;
	} else {
		int tailX = snake->bodyX[snake->size - 1];
		int tailY = snake->bodyY[snake->size - 1];
		map->data[tailX][tailY] = ' ';
	}

	if (snake->size == 1) {
		int oldX = snake->bodyX[0];
		int oldY = snake->bodyY[0];

		map->data[oldX][oldY] = ' ';

		snake->bodyX[0] = newX;
		snake->bodyY[0] = newY;
	} else {
		for (int i = snake->size - 1; i > 0; i--) {
			snake->bodyX[i] = snake->bodyX[i - 1];
			snake->bodyY[i] = snake->bodyY[i - 1];
		}
		snake->bodyX[0] = newX;
		snake->bodyY[0] = newY;
	}

	map->data[newX][newY] = snake->name;
}



// Zvýšenie veľkosti hada po zjedení jablka
void increaseSize(SnakeAtributes* snake) {
	snake->size++;
	snake->bodyX = realloc(snake->bodyX, snake->size * sizeof(int));
	snake->bodyY = realloc(snake->bodyY, snake->size * sizeof(int));

	// Nastavenie novej chvostovej pozície
	snake->bodyX[snake->size - 1] = snake->bodyX[snake->size - 2];
	snake->bodyY[snake->size - 1] = snake->bodyY[snake->size - 2];
}

void changeDirection(SnakeAtributes* snake, int newHeading) {
	snake->heading = newHeading;  // Zmena smeru pohybu hada
}

void checkCollision(SnakeAtributes* snake, Map* map) {
	int headX = snake->bodyX[0];
	int headY = snake->bodyY[0];

	// border or wall
	if (map->data[headX][headY] == '#' || map->data[headX][headY] == '~' || map->data[headX][headY] == '|') {
		snake->isLive = 0;
	}

	// selfcollisiion
	for (int i = 1; i < snake->size; i++) {
		if (headX == snake->bodyX[i] && headY == snake->bodyY[i]) {
			snake->isLive = 0;
		}
	}
}

void printSnakeData(SnakeAtributes* snake) {
	printf("Snake Data:\n");
	printf("Size: %d\n", snake->size);
	printf("Heading: %d\n", snake->heading);
	printf("Is Live: %d\n", snake->isLive);
	printf("Body Positions (X, Y):\n");

	for (int i = 0; i < snake->size; i++) {
		printf("  Segment %d: (%d, %d)\n", i, snake->bodyX[i], snake->bodyY[i]);
	}
}

void init_snake(SnakeAtributes *snake)
{
	snake->bodyX = (int*)malloc(sizeof(int) * 1);
	snake->bodyY = (int*)malloc(sizeof(int) * 1);
	snake->size = 1;
	snake->bodyX[0] = 1;
	snake->bodyY[0] = 1;
	snake->name = '1';
	snake->isLive = 1;
	snake->color = 1;
}