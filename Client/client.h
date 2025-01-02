#ifndef CLIENT_H
#define CLIENT_H

#include "../Server/server.h" // Include the server header to access the shared memory structure
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Function declarations
void init_client();
int shared_memory_ready(serverSharedMemory *ssm); // Pass serverSharedMemory struct
void release_client(serverSharedMemory *ssm);

#endif // CLIENT_H
