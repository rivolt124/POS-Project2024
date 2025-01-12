#include "mapGenerator.h"
#include "menuInterface.h"
#include "gameLogic.h"
#include "../Assets/communication.h"

#include <sys/shm.h>

void render(game_data* game, int currentPlayer)
{
	pthread_mutex_lock(&game->comm.lock);
	pthread_cond_wait(&game->comm.cond_client, &game->comm.lock);
	for (int i = 0; i < game->numPlayers; i++)
	{
		if (i == currentPlayer)
			showSnake(&game->snakes[i], &game->map, PLAYER);
		else
			showSnake(&game->snakes[i], &game->map, ENEMY);
	}
	pthread_mutex_unlock(&game->comm.lock);
	drawMap(&game->map);
}

void client()
{
}

void* server(void* data)
{
	game_data *game = (game_data *)data;
	while (game->timer >= 0)
	{
		pthread_mutex_lock(&game->comm.lock);
		for (int i = 0; i < game->numPlayers; i++)
		{
			moveSnake(&game->snakes[i], &game->map);
		}
		game->timer--;
		pthread_mutex_unlock(&game->comm.lock);

		sleep(3);

		pthread_cond_signal(&game->comm.cond_client);
	}
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

		if (settings.timeSeconds > 0)
			game->timer = settings.timeSeconds;
		else
			game->timer = 600;

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
		sleep(1);
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
	pthread_t consumer;
	// Init necessary data
	start_app(&index);

	game_data *game = shmat(index.gameId, NULL, 0);
	pthread_create(&consumer, NULL, &server, game);

	while (game->timer >= 0)
	{
		//pthread_mutex_lock(&game->comm.lock);
		//pthread_cond_wait(&game->comm.cond_client, &game->comm.lock);
		//pthread_mutex_unlock(&game->comm.lock);

		render(game, index.snakeIndex);
		printf("\n");
	}

	pthread_join(consumer, NULL);
	shmdt(game);
	shmctl(index.gameId, IPC_RMID, NULL);
    return 0;
}
