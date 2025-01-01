//ipc.h
#ifndef IPC_H
#define IPC_H

#define SHM_SIZE 1024

#ifdef _WIN32
#include <windows.h>
#define SHM_NAME "Local\\SharedMemory"

// Windows-specific functions
HANDLE create_shared_memory();
char *attach_shared_memory(HANDLE hMapFile);
void detach_shared_memory(char *shmaddr);
void destroy_shared_memory(HANDLE hMapFile);

#else
#include <sys/types.h>
#define SHM_KEY 0x1234

// Linux-specific functions
int create_shared_memory();
char *attach_shared_memory(int shmid);
void detach_shared_memory(char *shmaddr);
void destroy_shared_memory(int shmid);

#endif

#endif
