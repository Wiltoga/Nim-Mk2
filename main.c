#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "game.h"
#include "consoleManagement.h"

int main()
{
    clearScreen();
    printf(FRONT_CYAN);
    //http://patorjk.com/software/taag/#p=display&f=Standard&t=Nim
    printf("  _   _ _           \n | \\ | (_)_ __ ___  \n |  \\| | | '_ ` _ \\ \n | |\\  | | | | | | |\n |_| \\_|_|_| |_| |_|\n");
    printf("______________________\n");
    printf(FRONT_WHITE);
    //reset de la couleur de la console
    
    printf(FRONT_WHITE BACK_BLACK);
    return 0;
}
