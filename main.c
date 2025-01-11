#include "mapGenerator.h"
#include "gameLogic.h"
#include "inputHandler.h"
#include "menuInterface.h"

#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/types.h>

void client()
{}

void* server(void* data)
{
	// Server thread

	return NULL;
}

void start_app(communication_data* comm, shared_game_data *game)
{
	gameSettings settings;
	init_menu(&settings);
	if (settings.mainMenuChoose == 1)
	{
		int shm_id = shmget(IPC_PRIVATE, sizeof(shared_game_data), IPC_CREAT | 0666);
		game = (shared_game_data *)shmat(shm_id, NULL, 0);

		loadFixedMap(&game->map, settings.selectedMap);
		generateApple(&game->map);

		placeSnake(&game->map, &game->snakes[0]);
		game->numPlayers = 1;

		// Store the new shm_id
		int s_shm_id = shmget(S_SHM_ID, sizeof(shared_shm_id), IPC_CREAT | 0666);
		shared_shm_id *data = shmat(s_shm_id, NULL, 0);
		if (data->activeGames == 0)
			data->activeGames = 0;
		data->id[data->activeGames] = shm_id;
		data->activeGames++;
	}
	else if (settings.mainMenuChoose == 2)
	{
		int s_shm_id = shmget(S_SHM_ID, sizeof(shared_shm_id), IPC_CREAT | 0666);
		shared_shm_id *data = shmat(s_shm_id, NULL, 0);

		// Choose which game to connect to from the available ones
		// int shm_id = -return which game-

		game = (shared_game_data *)shmat(shm_id, NULL, 0);
		if (game->numPlayers + 1 > MAX_PLAYERS)
		{
			fprintf(stderr, "Game is full...");
			start_app(comm, game);
		}
		else
		{
			placeSnake(&game->map, &game->snakes[game->numPlayers]);
			game->numPlayers++;
		}
	}
	else if (settings.mainMenuChoose == 3)
		exit(0);

	// Init game
	syn_data_init(comm, &server, NULL);
}

int main()
{
	// Structs
	communication_data comm;
	shared_game_data game;
	// Init necessary data
	start_app(&comm, &game);


    return 0;
}
