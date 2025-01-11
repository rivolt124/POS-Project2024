#include "mapGenerator.h"

void loadFixedMap(map_data* map, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Unable to open selected map...\n");
        exit(1);
    }

    // Dimensions
    fscanf(file, "%d, %d\n", &map->width, &map->height);

    // Alloc
    map->gridData = (char**)malloc(map->width * sizeof(char*));
    for (int x = 0; x < map->width; x++) {
        map->gridData[x] = (char*)malloc(map->height * sizeof(char));
    }

    // Initialize
    for (int x = 0; x < map->width; x++) {
        for (int y = 0; y < map->height; y++) {
            if (y == 0 || y == map->height - 1)
                map->gridData[x][y] = HORIZONTAL_BORDER;
            else if (x == 0 || x == map->width - 1)
                map->gridData[x][y] = VERTICAL_BORDER;
            else
                map->gridData[x][y] = SPACE;
        }
    }

    // Add obstacles
    int x, y;
    while (fscanf(file, "%d, %d\n", &x, &y) == 2) {
        if (x > 0 && x < map->width - 1 && y > 0 && y < map->height - 1) {
            map->gridData[x][y] = BARRIER;
        }
    }
    fclose(file);
    map->appleExist = 0;
}

/* We don't handle the accessibility for each position
void createRandomMap(map_data* map, int width, int height, int obstacleCount) {
    map->width = width;
    map->height = height;

    // Allocate
    map->gridData = (char**)malloc(width * sizeof(char*));
    for (int x = 0; x < width; x++) {
        map->gridData[x] = (char*)malloc(height * sizeof(char));
    }

    // Initialize
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (y == 0 || y == height - 1)
                map->gridData[x][y] = '-';
            else if (x == 0 || x == width - 1)
                map->gridData[x][y] = '|';
            else
                map->gridData[x][y] = ' ';
        }
    }

    srand(time(NULL));
    for (int i = 0; i < obstacleCount; i++) {
        int x, y;
        do {
            x = rand() % (width - 2) + 1;
            y = rand() % (height - 2) + 1;
        } while (map->gridData[x][y] != ' ');
        map->gridData[x][y] = '#';
    }
    map->appleExist = 0;
}
*/

static void assign_color(char symbol)
{
    switch (symbol)
    {
    case APPLE:
        printf(RED "%c" RESET, APPLE);
        break;
    case BARRIER:
        printf(YELLOW "%c" RESET, BARRIER);
        break;
    case VERTICAL_BORDER:
		printf(GRAY_BG "%c" RESET, VERTICAL_BORDER);
		break;
    case HORIZONTAL_BORDER:
        printf(GRAY_BG "%c" RESET, HORIZONTAL_BORDER);
        break;
    case PLAYER:
        printf(GREEN "%c" RESET, PLAYER);
        break;
    case ENEMY:
        printf(YELLOW "%c" RESET, ENEMY);
        break;
    default:
        printf("%c", symbol);
    }
}

void drawMap(map_data* map) {
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            //assign_color(map->gridData[x][y]); // Only on Linux/MacOs
            printf("%c", map->gridData[x][y]);
        }
        printf("\n");
    }
}

void freeMap(map_data* map) {
    for (int x = 0; x < map->width; x++) {
        free(map->gridData[x]);
    }
    free(map->gridData);
}

static int* generatePosition(map_data* map)
{
    srand(time(NULL));
    int x, y;
    int* position = malloc(2 * sizeof(int));
    if (!position) {
        fprintf(stderr, "Memory allocation failed whilst generating a position...\n");
        exit(EXIT_FAILURE);
    }

    do {
        x = rand() % map->width;   // random x position
        y = rand() % map->height; // random y position
    } while (map->gridData[x][y] != ' ');

    position[0] = x;
    position[1] = y;
    return position;
}

void generateApple(map_data* map)
{
    if (map->appleExist == 1)
        return;
    int* position = generatePosition(map);

    map->gridData[position[0]][position[1]] = APPLE;
    map->appleExist = 1;
    //free(position);
}

void placeSnake(map_data* map, snake_data* snake)
{
    int* position = generatePosition(map);
    //map->gridData[position[0]][position[1]] = PLAYER; ?!
	snake_data_init(snake, position[0], position[1]);
    //free(position);
}
