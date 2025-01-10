#include "ipc.h"

void pipe_init(const char *path) {
	// Access rights: rw-rw----
	if (mkfifo(path, 0777) == -1) { //S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP
		perror("Failed to create named pipe");
		exit(EXIT_FAILURE);
	}
}

void pipe_destroy(const char *path) {
	if (unlink(path) == -1) {
		perror("Failed to unlink named pipe");
		exit(EXIT_FAILURE);
	}
}

static int open_pipe(const char *path, int flags) {
	const int fd = open(path, flags);
	if (fd == -1) {
		fprintf(stderr, "Failed to open named pipe %s: ", path);
		perror("");
		//exit(EXIT_FAILURE);
	}
	return fd;
}

int pipe_open_write(const char *path) {
	return open_pipe(path, O_WRONLY);
}

int pipe_open_read(const char *path) {
	return open_pipe(path, O_RDONLY);
}

void pipe_close(const int fd) {
	if (close(fd) == -1) {
		perror("Failed to close pipe");
		exit(EXIT_FAILURE);
	}
}
