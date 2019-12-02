#include <stdio.h>
#include "help.h"
#include "bool.h"
#include "consoleManagement.h"

void help()
{
    //simple menu d'aide
    clearScreen();
    printf(FRONT_BRIGHT_CYAN BACK_BLACK "AIDE :" FRONT_WHITE BACK_BLACK "\n\n");
    printf("Le jeu se deroule sur un plateau de x colonnes et de x lignes.\n"
           "Il y a un pion dans le coin en haut a gauche, une arrivee dans le coin en bas a droite.\n"
           "Il y a des obstacles infranchissables sur le plateau.\n"
           "A tour de role, le joueur et l'ordinateur realisent des mouvements au pion pour attiendre l'objectif.\n"
           "Les mouvements peuvent se faire vers le bas ou vers la droite, jusqu'a deux cases maximum\n"
           "et il est impossible d'aller sur un obstacle, ni de le traverser.\n"
           "Celui qui mettra le pion au point d'arrivee gagne la partie.\n\n");
    printf(FRONT_BLACK BACK_BRIGHT_RED "Retour" BACK_BLACK "\n");
    while (getArrowPressed() != RETURN);
}
