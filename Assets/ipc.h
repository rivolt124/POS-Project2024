#ifndef IPC_H
#define IPC_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	const char *pipe_;
	int fd_;
} ipc_resources;

// Function declarations
void    pipe_init(const char *path);
void    pipe_destroy(const char *path);
int     pipe_open_write(const char *path);
int     pipe_open_read(const char *path);
void    pipe_close(int fd);

#endif

// Interfaces
/*
int open(const char *pathname, int flags);   // mode_t mode is optional -> sets access rights
int mkfifo(const char *pathname, mode_t mode);
int unlink(const char *pathname);
int close(int fd);
*/