// client.c
#include "client.h"

void client_connect(const ipc_resources* resources)
{

}

char* find_available_server(char* directory, char* available)
{
	struct dirent *entry;
	char* full_name = malloc(64);
	DIR *dir = opendir(directory);
	if (!dir) {
		perror("opendir failed...");
		return NULL;
	}

	while ((entry = readdir(dir)) != NULL)
	{
		printf("%s\n", entry->d_name);
		if (strstr(entry->d_name, available) != NULL)
			snprintf(full_name, 64, "%s/%s", directory, entry->d_name);
	}

	closedir(dir);
	if (full_name[0] == '\0')
	{
		free(full_name);
		return NULL;
	}
	return full_name;
}
