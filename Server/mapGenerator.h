typedef struct {
    int width;
    int height;
    int appleExist;
    char** data;
} Map;

#define RESET_BG "\033[0m"       // Resetovanie farieb
#define RED_BG "\033[41m"     // Červené pozadie
#define GREEN_BG "\033[42m"   // Zelené pozadie
#define YELLOW_BG "\033[43m"  // Žlté pozadie
#define BLUE_BG "\033[44m"    // Modré pozadie

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