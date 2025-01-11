#include "utils.h"

void syn_data_init(communication_data* this, void* (*function)(void*), void* arg)
{
	if (pthread_mutex_init(&this->lock, NULL) != 0) {
		fprintf(stderr, "Mutex creation failure...");
		exit(1);
	}
	if (pthread_cond_init(&this->cond_client, NULL) != 0) {
		fprintf(stderr, "Conditional variable creation failure...");
		exit(1);
	}
	if (pthread_cond_init(&this->cond_server, NULL) != 0) {
		fprintf(stderr, "Conditional variable creation failure...");
		exit(1);
	}
	if (pthread_create(&this->server, NULL, function, NULL) != 0) {
		fprintf(stderr, "Thread creation failure...");
		exit(1);
	}
}

void syn_data_destroy(communication_data* this)
{
	pthread_join(this->server, NULL);

	pthread_mutex_destroy(&this->lock);
	pthread_cond_destroy(&this->cond_client);
	pthread_cond_destroy(&this->cond_server);
}

void snake_data_init(snake_data* snake) {
	snake->bodyX = malloc(sizeof(int));
	if (snake->bodyX == NULL) {
		fprintf(stderr, "Memory allocation for bodyX failed\n");
		exit(1);
	}

	snake->bodyY = malloc(sizeof(int));
	if (snake->bodyY == NULL) {
		fprintf(stderr, "Memory allocation for bodyY failed\n");
		free(snake->bodyX);
		exit(1);
	}

	snake->size = 0;
	snake->isLive = 0;
	snake->heading = DEFAULT_HEADING;
}
