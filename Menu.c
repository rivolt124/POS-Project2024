#include "Menu.h"

void printOnlineModeMenu() {

    printf("\n-----Online Mode-----");
    printf("\n1. SinglePlayer");
    printf("\n2. MultiPlayer");
    printf("\n3. Back");
    printf("\n--------------");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("SinglePlayer \n");

        break;
        case 2:
            printf("MultiPlayer \n");
        break;
        default:
            printf("Invalid choice\n");
        printOnlineModeMenu();
    }
}

void printGameWorldMenu() {

    printf("\n-----Choose world type-----");
    printf("\n1. World with obstacles");
    printf("\n2. World without obstacles");
    printf("\n3. Back");
    printf("\n--------------------------");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("World with obstacles \n");
            printOnlineModeMenu();
        break;
        case 2:
            printf("World with obstacles");
            printOnlineModeMenu();
        break;
        default:
            printf("Invalid choice\n");
        printGameWorldMenu();
    }

}

void printGameTypeMenu() {


    printf("\n-----Choose game type-----");
    printf("\n1. Standard mode");
    printf("\n2. Time mode");
    printf("\n3. Back");
    printf("\n--------------------------");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Standard mode\n");
            printGameWorldMenu();
        break;
        case 2:
            printf("Time mode\n");
            printGameWorldMenu();
        break;
        default:
            printf("Invalid choice\n");
        printGameTypeMenu();
    }

}

void printMainMenu() {
    bool end = false;

    while (!end) {
        printf("\n-----Menu-----");
        printf("\n1. New Game");
        printf("\n2. Connect to game");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        printf("\n--------------");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("SinglePlayer\n");
                end = true;
                printGameTypeMenu();
            break;
            case 2:
                printf("Multilayer\n");
                end = true;
            break;
            case 3:
                printf("Exit");
                end = true;
            break;
            default:
                printf("Invalid choice\n");
        }
    }
}





