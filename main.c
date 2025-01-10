#include "Server/server.h"
#include "Client/client.h"
#include "Server/gameLogic.h"

#include <sys/mman.h>

void process_menu(gameSettings *settings, ipc_resources *resources)
{
	init_menu(settings);
	if (settings->mainMenuChoose == 1)
	{
		if (settings->onlineMode == 2)
		{
			resources->pipe_ = generate_pipe_name(MULTIPLAYER);
			resources->fd_ = -1;
			server_create(resources);
		}
		else if (settings->onlineMode == 1)
		{
			resources->pipe_ = generate_pipe_name(SINGLEPLAYER);
			resources->fd_ = -1;
			server_create(resources);
		}

		sleep(10);
		server_destroy(resources); // Remember to remove this!!!
	}
	else if (settings->mainMenuChoose == 2)
	{
		char *found_server = find_available_server("/tmp", "multi");
		if (found_server)
		{
			resources->pipe_ = found_server;
			resources->fd_ = -1;

			//client_connect(resources);
			//free(found_server);
		}
		else
		{
			printf("No server found...");
			free(found_server);
			return;
		}
	}
}

int main()
{
	// Structs
	gameSettings settings;
	ipc_resources *resources = mmap(NULL, sizeof(ipc_resources),
									PROT_READ | PROT_WRITE,
									MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	Map *map 				 = mmap(NULL, sizeof(Map),
									PROT_READ | PROT_WRITE,
									MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	SnakeAtributes *snake 	 = mmap(NULL, sizeof(Map),
									  PROT_READ | PROT_WRITE,
								 	MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	init_snake(snake);

	// Menu
	process_menu(&settings, resources);
	if (settings.mainMenuChoose == 3)
		return 0;

	// Processes
	int pid = fork();
	if (pid == 0)
	{
		// Child Process: Server
		/*
		int fd;
		char buffer[1024];
		ssize_t bytesRead;

		printf("SERVER::: %s\n", resources->pipe_);

		fd = open(resources->pipe_, O_RDONLY);
		if (fd == -1) {
			perror("Failed to open pipe");
		}

		// Read from the pipe and print the contents
		while ((bytesRead = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
			buffer[bytesRead] = '\0';  // Null-terminate the buffer
			printf("%s", buffer);  // Print the data read from the pipe
		}

		// Close the pipe
		close(fd);
		 */
		exit(0);
	}
	else if (pid > 0)
	{
		// Parent Process: Client
		game(snake, map);
		/*
		int fd;
		char message[256];
		printf("Give your message to server:\n");
		scanf("%255[^\n]", message);

		printf("CLIENT::: %s\n", resources->pipe_);

		fd = pipe_open_write(resources->pipe_);
		// Send message to the server
		if (write(fd, message, strlen(message)) == -1)
			perror("Client: Failed to write to pipe");

		pipe_close(fd);
		 */
		waitpid(pid, NULL, 0);
	}
	else
	{
		printf("Error with fork...");
		return 1234;
	}

	sleep(1);
	// Release shared memory
 	munmap(resources, sizeof(ipc_resources));
	return 0;
}
