#include "ipc.h"
#include <stdio.h>
#include <stdlib.h>

// Cross-platform includes
#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ipc.h>
    #include <sys/shm.h>
    #include <unistd.h>
#endif

#ifdef _WIN32
    // Windows-specific shared memory implementation
    HANDLE create_shared_memory() {
        HANDLE hMapFile = CreateFileMapping(
            INVALID_HANDLE_VALUE,    // Use system paging file
            NULL,                    // Default security attributes
            PAGE_READWRITE,          // Read/write access
            0,                       // Maximum object size (high-order DWORD)
            SHM_SIZE,                // Maximum object size (low-order DWORD)
            SHM_NAME);        // Name of the shared memory object

        if (hMapFile == NULL) {
            fprintf(stderr, "CreateFileMapping failed with error: %ld\n", GetLastError());
            exit(EXIT_FAILURE);
        }

        return hMapFile;
    }

    char *attach_shared_memory(HANDLE hMapFile) {
        char *shmaddr = (char *)MapViewOfFile(
            hMapFile,                // Handle to the file mapping object
            FILE_MAP_ALL_ACCESS,     // Read/write access
            0, 0, SHM_SIZE);         // Map the whole memory object

        if (shmaddr == NULL) {
            fprintf(stderr, "MapViewOfFile failed with error: %ld\n", GetLastError());
            exit(EXIT_FAILURE);
        }

        return shmaddr;
    }

    HANDLE open_shared_memory() {
        HANDLE hMapFile = OpenFileMapping(
            FILE_MAP_ALL_ACCESS,     // Read/write access
            FALSE,                   // Do not inherit the handle
            SHM_NAME);               // Name of the shared memory object

        if (hMapFile == NULL) {
            fprintf(stderr, "OpenFileMapping failed with error: %ld\n", GetLastError());
            exit(EXIT_FAILURE);
        }

        return hMapFile;
    }

    void detach_shared_memory(char *shmaddr) {
        if (!UnmapViewOfFile(shmaddr)) {
            fprintf(stderr, "UnmapViewOfFile failed with error: %ld\n", GetLastError());
        }
    }

    void destroy_shared_memory(HANDLE hMapFile) {
        if (!CloseHandle(hMapFile)) {
            fprintf(stderr, "CloseHandle failed with error: %ld\n", GetLastError());
        }
    }

#else
    // Linux-specific shared memory implementation
    int create_shared_memory() {
        int shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
        if (shmid == -1) {
            perror("shmget failed");
            exit(EXIT_FAILURE);
        }
        return shmid;
    }

    char *attach_shared_memory(int shmid) {
        char *shmaddr = (char *)shmat(shmid, NULL, 0);
        if (shmaddr == (char *)-1) {
            perror("shmat failed");
            exit(EXIT_FAILURE);
        }
        return shmaddr;
    }

    int open_shared_memory() {
        int shmid = shmget(SHM_KEY, SHM_SIZE, 0666);  // Only read/write access, not creating
        if (shmid == -1) {
            perror("shmget failed");
            exit(EXIT_FAILURE);
        }
        return shmid;
    }

    void detach_shared_memory(char *shmaddr) {
        if (shmdt(shmaddr) == -1) {
            perror("shmdt failed");
        }
    }

    void destroy_shared_memory(int shmid) {
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl failed");
        }
    }
#endif

