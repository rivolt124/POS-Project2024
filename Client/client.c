#include "client.h"
#include "menuInterface.h"
#include "../Assets/ipc.h"

int init_client()
{
    // Initialize the client without attaching to shared memory yet
    return init_menu();
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

int init_menu()
{
    gameSettings settings;
    showMainMenu(&settings);
    printGameSettings(&settings);
    return settings.mainMenuChoose;
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
