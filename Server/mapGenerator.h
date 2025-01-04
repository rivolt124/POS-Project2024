typedef struct {
    int width;
    int height;
    int appleExist;
    char** data;
} Map;

// na načítanie pevnej mapy zo súboru
void loadFixedMap(Map* map, const char* filename);

// na nacitanie náhodnej mapy
void createRandomMap(Map* map, int width, int height, int obstacleCount);

// na vykreslenie mapy
void drawMap(Map* map);

// na uvoľnenie pamäte
void freeMap(Map* map);

//generovanie jablka na mape
void generateApple(Map* map);