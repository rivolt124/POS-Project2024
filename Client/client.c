//client.c

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

    snprintf(shmaddr, SHM_SIZE, "Hello from client!");

    printf("Client: Sent message to server.\n");

    while (strcmp(shmaddr, "Hello from server!") != 0) {
        sleep(1); // Wait for the server
    }

    printf("Client: Received response from server: %s\n", shmaddr);

    detach_shared_memory(shmaddr);
    #ifdef _WIN32
        // No need to destroy shared memory in Windows
    #else
        destroy_shared_memory(shmid);
    #endif
    return 0;
}
