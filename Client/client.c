#include "client.h"
#include "menuInterface.h"
#include "../Assets/ipc.h"

void init_client(gameSettings* menu)
{
    // Initialize the client menu
    init_menu(menu);
}

// This function checks the server's readiness via shared memory
int shared_memory_ready(serverSharedMemory *ssm)
{
    #ifdef _WIN32
        ssm->hMapFile = open_shared_memory();  // Attach to existing shared memory (Windows)
        ssm->shmaddr = attach_shared_memory(ssm->hMapFile);  // Attach to shared memory
    #else
        ssm->shmid = open_shared_memory();  // Attach to existing shared memory (Linux)
        ssm->shmaddr = attach_shared_memory(ssm->shmid);  // Attach to shared memory
    #endif

    if (strcmp(ssm->shmaddr, "Server ready! Attach to shared memory.") == 0) {
        printf("client connected to the server");
        return 1;  // Server is ready
    }
    return 0;  // Server is not ready
}

void release_client(serverSharedMemory *ssm)
{
    detach_shared_memory(ssm->shmaddr);
    #ifdef _WIN32
        // No need to destroy shared memory in Windows
    #else
        destroy_shared_memory(ssm->shmid);
    #endif
}
