#ifndef IPC_H
#define IPC_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

typedef struct {
    const char *pipe_;
} ipc_resources;

// Function declarations
void    pipe_init(const char *path);
void    pipe_destroy(const char *path);
int     pipe_open_write(const char *path);
int     pipe_open_read(const char *path);
void    pipe_close(int fd);

#endif
