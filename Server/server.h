#ifndef SERVER_H
#define SERVER_H

#include "../Assets/ipc.h"

#include <string.h>
#include <time.h>
//#include <dirent.h>

#define MULTIPLAYER "/tmp/multi"
#define SINGLEPLAYER "/tmp/single"

void server_create(const ipc_resources* resources);
void server_open(ipc_resources* resources);
void server_close(ipc_resources* resources);
void server_destroy(const ipc_resources* resources);

char* generate_pipe_name(const char* server_name);

#endif