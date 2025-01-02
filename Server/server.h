//server.h
#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ipc.h>
    #include <sys/shm.h>
#endif

// Server-side shared memory structure
typedef struct {
#ifdef _WIN32
    HANDLE hMapFile;   // Handle to shared memory (Windows)
#else
    int shmid;         // Shared memory ID (Linux)
#endif
    char *shmaddr;       // Pointer to shared memory
} serverSharedMemory;

void init_server(serverSharedMemory *ssm);
void release_server(serverSharedMemory *ssm);

#endif
