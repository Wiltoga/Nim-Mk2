#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "consoleManagement.h"
#include "bool.h"
#include "help.h"

int main()
{
    srand(time(NULL));
    clearScreen();
    int index = 0; //l'index représente la position du curseur dans les menus
    while (true)//boucle du jeu
    {
        printf(FRONT_BRIGHT_CYAN BACK_BLACK);
        //http://patorjk.com/software/taag/#p=display&f=Standard&t=Nim
        printf("  _   _ _           \n | \\ | (_)_ __ ___  \n |  \\| | | '_ ` _ \\ \n | |\\  | | | | | | |\n |_| \\_|_|_| |_| |_|\n");
        printf("______________________\npar Nathan HANEN, Tom SUBLET, Husein PARIC\n\n");
        printf(FRONT_GREY BACK_BLACK "Utiliser les fleches pour se deplacer, Entree pour valider.\n\n");
        if (index == 0)//couleur "jouer"
            printf(FRONT_BLACK BACK_BRIGHT_GREEN);
        else
            printf(FRONT_GREEN BACK_BLACK);
        printf("Jouer" BACK_BLACK "\n");
        if (index == 1)//couleur "aide"
            printf(FRONT_BLACK BACK_WHITE);
        else
            printf(FRONT_WHITE BACK_BLACK);
        printf("Aide" BACK_BLACK "\n");
        if (index == 2)//couleur "quitter"
            printf(FRONT_BLACK BACK_BRIGHT_RED);
        else
            printf(FRONT_RED BACK_BLACK);
        printf("Quitter" BACK_BLACK "\n");
        switch (getArrowPressed())
        {
        case UP:
            index--;
            break;
        case DOWN:
            index++;
            break;
        case RETURN:
            switch (index)
            {
            case 0://démarrer le jeu
                startGame();
                break;
            case 1://aide
                help();
                break;
            case 2://quitter
             //reset de la couleur de la console
                printf(FRONT_WHITE BACK_BLACK);
                exit(0);
            }
            break;
        }
        index = (index + 3)%3; //pour faire une boucle (-1%5 = -1 en C, malheureusement...)
        clearScreen();
      }
    return 0;
}
