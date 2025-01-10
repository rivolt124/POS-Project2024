#ifndef CLIENT_H
#define CLIENT_H

#include "../Assets/ipc.h"
#include "menuInterface.h"

#include <string.h>
#include <dirent.h>

void client_connect(const ipc_resources* resources);
char* find_available_server(char* directory, char* available);

#endif