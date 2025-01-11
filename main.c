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

void start_app(game_data *game, int *snakeIndex)
{
	gameSettings settings;
	init_menu(&settings);
	if (settings.mainMenuChoose == 1)
	{
		int shm_id = shmget(IPC_PRIVATE, sizeof(game_data), IPC_CREAT | 0666);
		game = (game_data *)shmat(shm_id, NULL, 0);

		loadFixedMap(&game->map, settings.selectedMap);
		generateApple(&game->map);

		placeSnake(&game->map, &game->snakes[0]);
		snakeIndex = 0;
		game->numPlayers = 1;

		// Store the new shm_id for multiplayer connection
		if (settings.onlineMode == 2)
		{
			int s_shm_id = shmget(S_SHM_ID, sizeof(shared_id), IPC_CREAT | 0666);
			shared_id *data = shmat(s_shm_id, NULL, 0);
			if (data->activeGames == 0)
				shared_id_init(data);

			pthread_mutex_lock(&data->id_lock);
			data->id[data->activeGames] = shm_id;
			data->activeGames++;
			pthread_mutex_unlock(&data->id_lock);
			shmdt(data);
			communication_data_init_multi(&game->comm);
		}
		else if (settings.onlineMode == 1)
			communication_data_init_single(&game->comm);

	}
	else if (settings.mainMenuChoose == 2)
	{
		if (settings.serverID == -1)
		{
			fprintf(stderr, "\nNo games available...\n");
			sleep(1);
			start_app(game, snakeIndex);
		}
		int s_shm_id = shmget(S_SHM_ID, sizeof(shared_id), IPC_CREAT | 0666);
		shared_id *data = shmat(s_shm_id, NULL, 0);
		game = (game_data *)shmat(data->id[settings.serverID], NULL, 0);

		if (game->numPlayers + 1 > MAX_PLAYERS)
		{
			fprintf(stderr, "Game is full...");
			shmdt(data);
			shmdt(game);
			start_app(game, snakeIndex);
		}
		else
		{
			pthread_mutex_lock(&game->comm.lock);
			placeSnake(&game->map, &game->snakes[game->numPlayers]);
			snakeIndex = &game->numPlayers;
			game->numPlayers++;
			pthread_mutex_unlock(&game->comm.lock);
			shmdt(data);
		}
	}
	else
		exit(0);
}

int main()
{
	// SHM data
	game_data game;
	int snakeIndex = 0;
	// Init necessary data
	start_app(&game, &snakeIndex);

	printf("%d", snakeIndex);

    return 0;
}
