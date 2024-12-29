// main.c
#include <stdbool.h>
#include "render_text.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}

	if (TTF_Init() != 0) {
		printf("TTF_Init Error: %s\n", TTF_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Game Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		TTF_Quit();
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		TTF_Quit();
		SDL_Quit();
		return 1;
	}

	TTF_Font *font = TTF_OpenFont("arial.ttf", 24);
	if (!font) {
		printf("TTF_OpenFont Error: %s\n", TTF_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		TTF_Quit();
		SDL_Quit();
		return 1;
	}

	SDL_Color white = {255, 255, 255, 255};
	SDL_Color yellow = {255, 255, 0, 255};

	const char *menuItems[] = {"Start Game", "Options", "Exit"};
	int selectedItem = 0;
	int menuItemCount = sizeof(menuItems) / sizeof(menuItems[0]);

	bool running = true;
	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_UP:
						selectedItem = (selectedItem - 1 + menuItemCount) % menuItemCount;
						break;
					case SDLK_DOWN:
						selectedItem = (selectedItem + 1) % menuItemCount;
						break;
					case SDLK_RETURN:
						if (selectedItem == 2) {
							running = false; // Exit
						}
						// Handle other menu item actions here
						break;
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		for (int i = 0; i < menuItemCount; i++) {
			SDL_Color color = (i == selectedItem) ? yellow : white;
			renderText(renderer, font, menuItems[i], SCREEN_WIDTH / 2 - 100, 200 + i * 50, color);
		}

		SDL_RenderPresent(renderer);
	}

	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

	return 0;
}