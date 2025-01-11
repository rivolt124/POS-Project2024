#include "menuInterface.h"

void clearConsole() {
#ifdef _WIN32
    system("cls");   // Windows
#else
    system("clear"); // Linux/macOS
#endif
}
//TODO TEST ON FRIOS
void clearConsole2() {
    printf("\033[H\033[2J");
}

void clearConsole3() {
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}

int displayMenu(const char* menuTitle, const char* options[], int optionCount) {
    printf("\n----- %s -----\n", menuTitle);
    for (int i = 0; i < optionCount; i++) {
        printf("%d. %s\n", i + 1, options[i]);
    }
    printf("--------------------------\n");
    printf("Enter your choice: ");

    int choice;
    scanf("%d", &choice);
    return choice;
}

void showOnlineModeMenu(gameSettings* settings) {
    const char* options[] = {"SinglePlayer", "MultiPlayer", "Back"};
    while (1) {
        int choice = displayMenu("Online Mode", options, 3);
        switch (choice) {
            case 1:
                printf("SinglePlayer selected\n");
                settings->onlineMode = 1;
                return;
            case 2:
                printf("MultiPlayer selected\n");
                settings->onlineMode = 2;
                return;
            case 3:
                showGameWorldMenu(settings);
                return;
            default:
                printf("Invalid choice\n");
        }
    }
}

void showMapSelectionMenu(gameSettings* settings) {
    const char* options[] = {"Generate map", "Choose map (1-3)", "Back"};
    while (1) {
        int choice = displayMenu("Map Selection", options, 3);
        switch (choice) {
            case 1: {
                printf("Generating map...\n");
                printf("Width: \n");
                scanf("%d", &(settings->mapWidth));
                printf("Height: \n");
                scanf("%d", &(settings->mapHeight));
                strcpy(settings->selectedMap, "Generated");
                return;
            }
            case 2: {
                const char* mapSizeOptions[] = {"Small (1)", "Medium (2)", "Large (3)", "Back"};
                while (1) {
                    int sizeChoice = displayMenu("Choose Map Size", mapSizeOptions, 4);
                    if (sizeChoice >= 1 && sizeChoice <= 3) {

                        if (settings->gameWorld == 1) {
                            if (sizeChoice == 1) strcpy(settings->selectedMap, "../Maps/mapFour.txt");
                            else if (sizeChoice == 2) strcpy(settings->selectedMap, "../Maps/mapFive.txt");
                            else if (sizeChoice == 3) strcpy(settings->selectedMap, "../Maps/mapSix.txt");
                        } else if (settings->gameWorld == 2) {
                            if (sizeChoice == 1) strcpy(settings->selectedMap, "../Maps/mapOne.txt");
                            else if (sizeChoice == 2) strcpy(settings->selectedMap, "../Maps/mapTwo.txt");
                            else if (sizeChoice == 3) strcpy(settings->selectedMap, "../Maps/mapThree.txt");
                        }
                        printf("Map selected: %s\n", settings->selectedMap);
                        return;
                    } else if (sizeChoice == 4) {
                        break; // Návrat do hlavného menu výberu mapy
                    } else {
                        printf("Invalid choice. Please try again.\n");
                    }
                }
                break;
            }
            case 3:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}


void showGameWorldMenu(gameSettings* settings) {
    const char* options[] = {"World with obstacles", "World without obstacles", "Back"};
    while (1) {
        int choice = displayMenu("Choose world type", options, 3);
        switch (choice) {
            case 1:
                printf("World with obstacles selected\n");
            settings->gameWorld = 1;
            showMapSelectionMenu(settings);
            return;
            case 2:
                printf("World without obstacles selected\n");
            settings->gameWorld = 2;
            showMapSelectionMenu(settings);
            return;
            case 3:
                showGameTypeMenu(settings);
            return;
            default:
                printf("Invalid choice\n");
        }
    }
}

void showGameTypeMenu(gameSettings* settings) {
    const char* options[] = {"Standard mode", "Time mode", "Back"};
    while (1) {
        int choice = displayMenu("Choose game type", options, 3);
        switch (choice) {
            case 1:
                printf("Standard mode selected\n");
                settings->gameTypeMode = 1;
                settings->timeSeconds = 0;
                showGameWorldMenu(settings);
                return;
            case 2:
                printf("Time mode selected\n");
                settings->gameTypeMode = 2;
                printf("Enter time in seconds: ");
                scanf("%d", &(settings->timeSeconds));
                showGameWorldMenu(settings);
                return;
            case 3:
                showMainMenu(settings);
                return;
            default:
                printf("Invalid choice\n");
        }
    }
}

void showMainMenu(gameSettings* settings) {
    const char* options[] = {"New Game", "Connect to game", "Exit"};
    while (1) {
        int choice = displayMenu("Main Menu", options, 3);
        switch (choice) {
            case 1:
                printf("Starting new game...\n");
                settings->mainMenuChoose = 1;
                showGameTypeMenu(settings);
                return;
            case 2:
                printf("Connecting to the game...\n");
                settings->mainMenuChoose = 2;
                return;
            case 3:
                clearConsole();
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid choice\n");
        }
    }
}

void init_menu(gameSettings *menu)
{
    showMainMenu(menu);
    if (menu->mainMenuChoose == 1)
        printGameSettings(menu);
}

void printGameSettings(const gameSettings* settings)
{
    printf("\nGame Settings:\n");
    printf("Main Menu Choice: %d (1 = New Game, 2 = Connect to Game)\n", settings->mainMenuChoose);
    printf("Game Type Mode: %d (1 = Standard Mode, 2 = Time Mode)\n", settings->gameTypeMode);
    printf("Time Duration: %d seconds\n", settings->timeSeconds);
    printf("Game World: %d (1 = World with Obstacles, 2 = World without Obstacles)\n", settings->gameWorld);
    printf("Online Mode: %d (1 = SinglePlayer, 2 = MultiPlayer)\n", settings->onlineMode);
}

int menuPause() {
    int choice;
    printf("-----PAUSE-----\n");
    printf("1.Back to Game\n");
    printf("2.Back to Main Menu\n");
    printf("--------------------------\n");
    printf("Enter your choice: ");
    scanf("%c", choice);
    while (1) {
        switch (choice) {
            case '1':
                return 1;
            case '2':
                return 2;
            default:
                printf("Invalid choice\n");
        }
    }
}