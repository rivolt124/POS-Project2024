#ifndef IPC_H
#define IPC_H

#define SHM_SIZE 1024

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ipc.h>
    #include <sys/shm.h>
#endif

// Function prototypes for shared memory operations
#ifdef _WIN32
    #define SHM_NAME "game_shared_memory"
    HANDLE create_shared_memory();
    char *attach_shared_memory(HANDLE hMapFile);
    HANDLE open_shared_memory();
    void detach_shared_memory(char *shmaddr);
    void destroy_shared_memory(HANDLE hMapFile);
#else
    #define SHM_KEY 0x1234
    int create_shared_memory();
    char *attach_shared_memory(int shmid);
    int open_shared_memory();
    void detach_shared_memory(char *shmaddr);
    void destroy_shared_memory(int shmid);
#endif

#endif // IPC_H
