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

int start_app(index_data *index)
{
	gameSettings settings;
	int id = -1;
	settings.selectedMap = malloc(sizeof (char*));
	init_menu(&settings);

	if (settings.mainMenuChoose == 1)
	{
		int shm_id = shmget(IPC_PRIVATE, sizeof(game_data), IPC_CREAT | 0666);
		game_data* game = (game_data *)shmat(shm_id, NULL, 0);
		if (game == (void *)-1) {
			perror("shmat failed");
			exit(EXIT_FAILURE);
		}
		id = shm_id;

		loadFixedMap(&game->map, settings.selectedMap);
		generateApple(&game->map);

		placeSnake(&game->map, &game->snakes[0]);
		printf("snake size after init: %d\n", game->snakes[0].size);
		index->snakeIndex = 0;
		game->numPlayers = 1;

		// Store the new shm_id for multiplayer connection
		if (settings.onlineMode == 2)
		{
			int s_shm_id = shmget(S_SHM_ID, sizeof(shared_id), IPC_CREAT | 0666);
			shared_id *data = shmat(s_shm_id, NULL, 0);
			if (data->activeGames == 0)
				shared_id_init(data);

			pthread_mutex_lock(&data->id_lock);
			data->id = malloc(MAX_SERVERS * sizeof (int));
			data->id[data->activeGames] = shm_id;
			printf("data id____%d", data->id[data->activeGames]);
			data->activeGames++;
			pthread_mutex_unlock(&data->id_lock);
			shmdt(data);
			communication_data_init_multi(&game->comm);
		}
		else if (settings.onlineMode == 1)
			communication_data_init_single(&game->comm);
		shmdt(game);
	}
	else if (settings.mainMenuChoose == 2)
	{
		if (settings.serverID == -1)
		{
			fprintf(stderr, "\nNo games available...\n");
			sleep(1);
			start_app(index);
		}
		int s_shm_id = shmget(S_SHM_ID, sizeof(shared_id), IPC_CREAT | 0666);
		shared_id *data = shmat(s_shm_id, NULL, 0);
		game_data* game = (game_data *)shmat(data->id[settings.serverID], NULL, 0);
		if (game->numPlayers + 1 > MAX_PLAYERS)
		{
			fprintf(stderr, "Game is full...");
			shmdt(data);
			shmdt(game);
			start_app(index);
		}
		else
		{
			index->gameIndex = settings.serverID;
			id = data->id[settings.serverID];
			pthread_mutex_lock(&game->comm.lock);
			placeSnake(&game->map, &game->snakes[game->numPlayers]);
			game->snakes[game->numPlayers].size = 3;
			index->snakeIndex = game->numPlayers;
			game->numPlayers++;
			pthread_mutex_unlock(&game->comm.lock);
			shmdt(data);
			shmdt(game);
		}
	}
	else
		exit(0);
	free(settings.selectedMap);
	return id;
}

int main()
{

	// SHM data
	index_data index;
	// Init necessary data
	int current_id = start_app(&index);

	game_data *game = shmat(current_id, NULL, 0);

	printf("snakeIndex: %d\n", index.snakeIndex);
	printf("snake size: %d\n", game->snakes[index.snakeIndex].size);
	printf("game ID: %d\n", current_id);


	int s_shm_id = shmget(S_SHM_ID, sizeof(shared_id), IPC_CREAT | 0666);
	shared_id *data = shmat(s_shm_id, NULL, 0);
	shared_id_destroy(data, S_SHM_ID);

	/*
	int s_shm_id = shmget(S_SHM_ID, sizeof(shared_id), IPC_CREAT | 0666);
	shared_id *data = shmat(s_shm_id, NULL, 0);
	shmctl(data->id[0], IPC_RMID, NULL);
	shmdt(data);
	shmctl(S_SHM_ID, IPC_RMID, NULL); */

    return 0;
}
