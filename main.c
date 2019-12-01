#include<stdio.h>
#include "game.h"
#include "consoleColors.h"

int main()
{
    //http://patorjk.com/software/taag/#p=display&f=Standard&t=Nim
    printf("\t\t  _   _ _           \n\t\t | \\ | (_)_ __ ___  \n\t\t |  \\| | | '_ ` _ \\ \n\t\t | |\\  | | | | | | |\n\t\t |_| \\_|_|_| |_| |_|\n");
    printf("\t\t______________________");
    startGame();


    //reset the console color
    printf(FRONT_WHITE BACK_BLACK);
    return 0;
}
