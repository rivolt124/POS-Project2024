#include "server.h"

void server_create(const ipc_resources* resources) {
	// Inicializácia názvovej rúrky
	pipe_init(resources->pipe_);
	printf("Server: Initialized at %s\n", resources->pipe_);
}

void server_open(ipc_resources* resources)
{
	int fd = pipe_open_read(resources->pipe_);
	resources->fd_ = fd;
	printf("Server: Opened...\n");
}

void server_close(ipc_resources* resources)
{
	pipe_close(resources->fd_);
	resources->fd_ = -1;
	printf("Server: Closed...\n");
}

void server_destroy(const ipc_resources* resources)
{
	pipe_destroy(resources->pipe_);
}

char* generate_pipe_name(const char* server_name) {
	char* pipe_name = malloc(64);
	return pipe_name ? snprintf(pipe_name, 64, "%s_%ld", server_name, time(NULL)), pipe_name : NULL;
	//return pipe_name ? snprintf(pipe_name, 64, "%s_1", server_name), pipe_name : NULL;
}
