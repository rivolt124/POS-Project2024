#include "server.h"
#include "../Assets/ipc.h"

void init_server(serverSharedMemory *ssm)
{
    #ifdef _WIN32
        ssm->hMapFile = create_shared_memory();
        ssm->shmaddr = attach_shared_memory(ssm->hMapFile);
    #else
        ssm.shmid = create_shared_memory();
        ssm.shmaddr = attach_shared_memory(ssm.shmid);
    #endif

    printf("Server is up...\n");
    snprintf(ssm->shmaddr, SHM_SIZE, "Server ready! Attach to shared memory.");

    //if (ssm->shmaddr[0] != '\0')
    //    printf("Server: Received message from client: %s\n", ssm->shmaddr);

    sleep(5); // Simulate ongoing communication
}

void release_server(serverSharedMemory *ssm)
{
    detach_shared_memory(ssm->shmaddr);

    #ifdef _WIN32
        destroy_shared_memory(ssm->hMapFile);
    #else
        destroy_shared_memory(ssm->shmid);
    #endif
}
