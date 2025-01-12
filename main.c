#include "mapGenerator.h"
#include "menuInterface.h"
#include "gameLogic.h"
#include "inputHandler.h"
#include "../Assets/communication.h"

#include <sys/shm.h>

typedef struct {
	game_data* game;
	index_data* indexer;
} thread_data;

void client(thread_data* data)
{
	switch (init_inputHandler())
	{
		case 'a':
			pthread_mutex_lock(&data->game->comm.lock);
			changeDirection(&data->game->snakes[data->indexer->snakeIndex], LEFT);
			pthread_mutex_unlock(&data->game->comm.lock);
			break;
		case 's':
			pthread_mutex_lock(&data->game->comm.lock);
			changeDirection(&data->game->snakes[data->indexer->snakeIndex], DOWN);
			pthread_mutex_unlock(&data->game->comm.lock);
			break;
		case 'd':
			pthread_mutex_lock(&data->game->comm.lock);
			changeDirection(&data->game->snakes[data->indexer->snakeIndex], RIGHT);
			pthread_mutex_unlock(&data->game->comm.lock);
			break;
		case 'w':
			pthread_mutex_lock(&data->game->comm.lock);
			changeDirection(&data->game->snakes[data->indexer->snakeIndex], UP);
			pthread_mutex_unlock(&data->game->comm.lock);
			break;
		case 'q':
			pthread_mutex_lock(&data->game->comm.lock);
			data->game->timer = -1;
			pthread_mutex_unlock(&data->game->comm.lock);
		default:
			break;
	}
}

void* render(void* data)
{
	thread_data* t_data = (thread_data*)data;
	game_data* game = t_data->game;
	int currentPlayer = t_data->indexer->snakeIndex;

	while (game->timer >= 0 && game->snakes[currentPlayer].isLive == 1)
	{
		pthread_mutex_lock(&game->comm.lock);
		pthread_cond_wait(&game->comm.cond_client, &game->comm.lock);
		map_data map;
		map = game->map;

		for (int i = 0; i < game->numPlayers; i++) {
			if (i == currentPlayer)
				showSnake(&game->snakes[i], &map, PLAYER);
			else
				showSnake(&game->snakes[i], &map, ENEMY);
		}
		drawMap(&map);

		pthread_mutex_unlock(&game->comm.lock);
		client(data);
		sleep(1);
	}
	return NULL;
}

void* server(void* data)
{
	thread_data* t_data = (thread_data*)data;
	game_data* game = t_data->game;
	int currentPlayer = t_data->indexer->snakeIndex;

	while (game->timer >= 0 && game->snakes[currentPlayer].isLive == 1)
	{
		pthread_mutex_lock(&game->comm.lock);
		for (int i = 0; i < game->numPlayers; i++)
		{
			moveSnake(&game->snakes[i], &game->map);
		}
		if (game->map.appleExist == 0)
			generateApple(&game->map);
		game->timer--;

		pthread_mutex_unlock(&game->comm.lock);
		pthread_cond_signal(&game->comm.cond_client);

		sleep(2);
	}
	printScore(&game->snakes[currentPlayer]);
	game->snakes[currentPlayer].isLive = 0;
	memset(&game->snakes[currentPlayer], 0, sizeof (snake_data));
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
			return;
		}
		game_data* game = (game_data *)shmat(shm_id, NULL, 0);
		if (game == (void *)-1)
		{
			fprintf(stderr, "Game is not available, try again...");
			shmdt(game);
			sleep(1);
			start_app(index);
			return;
		}
		if (game->numPlayers + 1 > MAX_PLAYERS)
		{
			fprintf(stderr, "Game is full, create a new one...");
			shmdt(game);
			sleep(1);
			start_app(index);
			return;
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

int main() {
	// SHM data
	index_data index;
	pthread_t consumer;
	pthread_t producer;
	// Init necessary data
	start_app(&index);
	game_data *game = shmat(index.gameId, NULL, 0);

	thread_data t_data;
	t_data.game = game;
	t_data.indexer = &index;

	pthread_create(&consumer, NULL, &server, &t_data);
	pthread_create(&producer, NULL, &render, &t_data);

	pthread_join(consumer, NULL);
	pthread_join(producer, NULL);

	shmdt(game);
	shmctl(index.gameId, IPC_RMID, NULL);
    return 0;
}
