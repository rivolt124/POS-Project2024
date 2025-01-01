//main.c
#include "Client/menuInterface.h"

int main()
{
    gameSettings settings;
    showMainMenu(&settings);
    printGameSettings(&settings);
    return 0;
}