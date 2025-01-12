#include "mapGenerator.h"
#include "menuInterface.h"
#include "../Assets/communication.h"

#include <sys/shm.h>

void client()
{}

void* server(void* data)
{
	// Server thread

	return NULL;
}

void start_app(index_data *index)
{
	gameSettings settings;
	settings.selectedMap = malloc(sizeof (char*));
	init_menu(&settings);

	if (settings.mainMenuChoose == 1)
	{
		int shm_id = shmget(IPC_PRIVATE, sizeof(game_data), IPC_CREAT | 0666);
		game_data* game = (game_data *)shmat(shm_id, NULL, 0);

		loadFixedMap(&game->map, settings.selectedMap);
		generateApple(&game->map);

		placeSnake(&game->map, &game->snakes[0]);
		game->numPlayers = 1;

		if (settings.onlineMode == 2)
		{
			// Send msg
			send_msg(shm_id);
			communication_data_init_multi(&game->comm);
		}
		else if (settings.onlineMode == 1)
			communication_data_init_single(&game->comm);
		index->snakeIndex = 0;
		index->gameId = shm_id;
		shmdt(game);
	}
	else if (settings.mainMenuChoose == 2)
	{
		// Read msg
		int shm_id = receive_msg();
		if (shm_id == -1)
		{
			sleep(1);
			start_app(index);
		}
		game_data* game = (game_data *)shmat(shm_id, NULL, 0);
		if (game->numPlayers + 1 > MAX_PLAYERS)
		{
			fprintf(stderr, "Game is full, create a new one...");
			shmdt(game);
			sleep(1);
			start_app(index);
		}
		else
		{
			pthread_mutex_lock(&game->comm.lock);
			placeSnake(&game->map, &game->snakes[game->numPlayers]);
			index->snakeIndex = game->numPlayers;
			index->gameId = shm_id;
			game->numPlayers++;
			pthread_mutex_unlock(&game->comm.lock);
			send_msg(shm_id);
			shmdt(game);
		}
	}
	else
		exit(0);
	free(settings.selectedMap);
}

int main()
{
	// SHM data
	index_data index;
	// Init necessary data
	start_app(&index);

	printf("1\n");

	game_data *game = shmat(index.gameId, NULL, 0);

	printf("2\n");

	drawMap(&game->map);

	printf("3\n");


	//sleep(20);
	printf("4\n");

	//shmdt(game);
    return 0;
}
