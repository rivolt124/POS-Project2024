#include "utils.h"

void communication_data_init_multi(communication_data* this)
{
	pthread_mutexattr_t mutex_attr;
	pthread_condattr_t cond_attr;

	pthread_mutexattr_init(&mutex_attr);
	pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED);
	pthread_condattr_init(&cond_attr);
	pthread_condattr_setpshared(&cond_attr, PTHREAD_PROCESS_SHARED);

	if (pthread_mutex_init(&this->lock, &mutex_attr) != 0) {
		fprintf(stderr, "Mutex creation failure...\n");
		exit(1);
	}
	if (pthread_cond_init(&this->cond_client, &cond_attr) != 0) {
		fprintf(stderr, "Conditional variable creation failure...\n");
		exit(1);
	}
	if (pthread_cond_init(&this->cond_server, &cond_attr) != 0) {
		fprintf(stderr, "Conditional variable creation failure...\n");
		exit(1);
	}
	pthread_mutexattr_destroy(&mutex_attr);
	pthread_condattr_destroy(&cond_attr);
}

void communication_data_init_single(communication_data* this)
{
	if (pthread_mutex_init(&this->lock, NULL) != 0) {
		fprintf(stderr, "Mutex creation failure...\n");
		exit(1);
	}
	if (pthread_cond_init(&this->cond_client, NULL) != 0) {
		fprintf(stderr, "Conditional variable creation failure...\n");
		exit(1);
	}
	if (pthread_cond_init(&this->cond_server, NULL) != 0) {
		fprintf(stderr, "Conditional variable creation failure...\n");
		exit(1);
	}
}

void communication_data_destroy(communication_data* this)
{
	pthread_mutex_destroy(&this->lock);
	pthread_cond_destroy(&this->cond_client);
	pthread_cond_destroy(&this->cond_server);

	// free SHM...
}

void snake_data_init(snake_data* snake, int x, int y) {
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
	snake->bodyX[0] = x;
	snake->bodyY[0] = y;
	snake->size = 1;
	snake->isLive = 1;
	snake->heading = DEFAULT_HEADING;
}
