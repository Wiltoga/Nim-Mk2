#include <stdio.h>
#include "game.h"
#include "Case.h"
#include "Position.h"
#include "consoleManagement.h"
#include "bool.h"
#include "GamePlate.h"
#include "utilities.h"

void startGame()
{
    GameOptions options = parameters();
    GamePlate* plate = createPlate(options);




    freePlate(plate);
}
GameOptions parameters()
{
    printf(FRONT_WHITE BACK_BLACK);
    clearScreen();
    GameOptions options;
    do
    {
        //boucle qui demande le nombre de lignes tant que le nombre ne respecte pas les limites
        printf("Nombre de lignes du plateau :");
        scanf("%d", &options.nlig);
    } while (options.nlig > VMAX || options.nlig < VMIN);
    clearScreen();
    do
    {
        //boucle qui demande le nombre de colonnes tant que le nombre ne respecte pas les limites
        printf("Nombre de colonnes du plateau :");
        scanf("%d", &options.ncol);
    } while (options.ncol > VMAX || options.ncol < VMIN);
    clearScreen();
    options.niveau = -1;
    int index = 0;//selecteur
    while (options.niveau == -1)
    {
        printf(FRONT_WHITE BACK_BLACK "difficulte de l'ordinateur :\n");
        if (index == 0)//couleur "debutant"
            printf(FRONT_BLACK BACK_BRIGHT_CYAN);
        else
            printf(FRONT_CYAN BACK_BLACK);
        printf("debutant" BACK_BLACK "\n");
        if (index == 1)//couleur "moyen"
            printf(FRONT_BLACK BACK_BRIGHT_GREEN);
        else
            printf(FRONT_GREEN BACK_BLACK);
        printf("moyen" BACK_BLACK "\n");
        if (index == 2)//couleur "expert"
            printf(FRONT_BLACK BACK_BRIGHT_YELLOW);
        else
            printf(FRONT_YELLOW BACK_BLACK);
        printf("expert" BACK_BLACK "\n");
        if (index == 3)//couleur "virtuose"
            printf(FRONT_BLACK BACK_BRIGHT_RED);
        else
            printf(FRONT_RED BACK_BLACK);
        printf("virtuose" BACK_BLACK "\n");
        if (index == 4)//couleur "divin"
            printf(FRONT_MAGENTA BACK_RED "D I V I N");
        else
            printf(FRONT_BRIGHT_MAGENTA BACK_BLACK "divin");
        printf(BACK_BLACK "\n");
        switch (getArrowPressed())
        {
        case UP:
            index--;
            break;
        case DOWN:
            index++;
            break;
        case RETURN:
            options.niveau = index;
            break;
        }
        index = (index + 5)%5; //pour faire une boucle (-1%5 = -1 en C, malheureusement...)
        clearScreen();
    }
    options.next = -1;
    index = 0;
    while (options.next == -1)
    {
        printf(FRONT_WHITE BACK_BLACK "qui commence ?\n");
        if (index == 0)//couleur "debutant"
            printf(FRONT_BLACK BACK_BRIGHT_CYAN);
        else
            printf(FRONT_CYAN BACK_BLACK);
        printf("le joueur" BACK_BLACK "\n");
        if (index == 1)//couleur "moyen"
            printf(FRONT_BLACK BACK_BRIGHT_MAGENTA);
        else
            printf(FRONT_MAGENTA BACK_BLACK);
        printf("l'ordinateur" BACK_BLACK "\n");
        switch (getArrowPressed())
        {
        case UP:
            index--;
            break;
        case DOWN:
            index++;
            break;
        case RETURN:
            options.next = !index;
            break;
        }
        index = (index + 2)%2; //pour faire une boucle (-1%5 = -1 en C, malheureusement...)
        clearScreen();
    }
    options.nban = random(0, max(options.ncol, options.nlig)+1);//on prend un nombre aléatoire de cases bannies
    return options;
}