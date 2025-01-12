#include "menuInterface.h"

void clearConsole() {
    system("clear"); // Linux/macOS
}

void clearConsole2() {
    printf("\033[H\033[2J");
}

void clearConsole3() {
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}

char displayMenu(const char* menuTitle, const char* options[], int optionCount) {

    printf("\n----- %s -----\n", menuTitle);
    for (int i = 0; i < optionCount; i++) {
        printf("%d. %s\n", i + 1, options[i]);
    }
    printf("--------------------------\n");
    printf("Enter your choice: ");

    char choice;
    scanf(" %c", &choice);
    return choice;
}

void showOnlineModeMenu(gameSettings* settings) {
    const char* options[] = {"SinglePlayer", "MultiPlayer", "Back"};
    while (1) {
        char choice = displayMenu("Online Mode", options, 3);
        switch (choice) {
            case '1':
                printf("SinglePlayer selected\n");
                settings->onlineMode = 1;
                return;
            case '2':
                printf("MultiPlayer selected\n");
                settings->onlineMode = 2;
                return;
            case '3':
                //showMapSelectionMenu(settings);
                return;
            default:
                printf("Invalid choice\n");
        }
    }
}

void showMapSelectionMenu(gameSettings* settings) {
    const char* options[] = {"Choose map (1-3)", "Back"};
    while (1) {
        char choice = displayMenu("Map Selection", options, 2);
        switch (choice) {
            case '1': {
                const char* mapSizeOptions[] = {"Map (1)", "Map (2)", "Map (3)", "Map without obstacles (4)", "Back"};
                while (1) {
                    char sizeChoice = displayMenu("Choose Map", mapSizeOptions, 4);
                    if (sizeChoice >= '1' && sizeChoice <= '4') {


                        if (sizeChoice == '1') {
                            settings->gameWorld = 1;
                            strcpy(settings->selectedMap, "../Maps/mapFour.txt");
                        }
                        else if (sizeChoice == '2') {
                            settings->gameWorld = 1;
                            strcpy(settings->selectedMap, "../Maps/mapFive.txt");
                        }
                        else if(sizeChoice == '3') {
                            settings->gameWorld = 1;
                             strcpy(settings->selectedMap, "../Maps/mapSix.txt");
                        }
                        else if (sizeChoice == '4') {
                            settings->gameWorld = 2;
                            strcpy(settings->selectedMap, "../Maps/mapOne.txt");
                        }


                        printf("Map selected: %s\n", settings->selectedMap);
						showOnlineModeMenu(settings);
                        return;
                    } else if (sizeChoice == 4) {
                        break; // Návrat do hlavného menu výberu mapy
                    } else {
                        printf("Invalid choice. Please try again.\n");
                    }
                }
                break;
            }
            case '2':
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void showGameTypeMenu(gameSettings* settings) {
    const char* options[] = {"Standard mode", "Time mode", "Back"};
    while (1) {
        char choice = displayMenu("Choose game type", options, 3);
        switch (choice) {
            case '1':
                printf("Standard mode selected\n");
                settings->gameTypeMode = 1;
                settings->timeSeconds = 0;
                showMapSelectionMenu(settings);
                return;
            case '2':
                printf("Time mode selected\n");
                settings->gameTypeMode = 2;
                printf("Enter time in seconds: ");
                scanf(" %d", &(settings->timeSeconds));
                showMapSelectionMenu(settings);
                return;
            case '3':
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
        char choice = displayMenu("Main Menu", options, 3);
        switch (choice) {
            case '1':
                printf("Starting new game...\n");
                settings->mainMenuChoose = 1;
                showGameTypeMenu(settings);
                return;
            case '2':
                settings->mainMenuChoose = 2;
                return;
            case '3':
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
    scanf(" %d", &choice);
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

