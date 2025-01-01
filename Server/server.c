//server.c

#include "../Assets/ipc.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    #ifdef _WIN32
        HANDLE hMapFile = create_shared_memory();
        char *shmaddr = attach_shared_memory(hMapFile);
    #else
        int shmid = create_shared_memory();
        char *shmaddr = attach_shared_memory(shmid);
    #endif

    printf("Server: Waiting for client message...\n");

    while (shmaddr[0] == '\0') {
        sleep(1); // Wait for the client
    }

    printf("Server: Received message from client: %s\n", shmaddr);

    snprintf(shmaddr, SHM_SIZE, "Hello from server!");

    sleep(5); // Simulate ongoing communication

    detach_shared_memory(shmaddr);
    #ifdef _WIN32
        destroy_shared_memory(hMapFile);
    #else
        destroy_shared_memory(shmid);
    #endif

    return 0;
}
