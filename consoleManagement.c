#include<stdio.h>
#include "consoleManagement.h"

//fonction qui déplace le curseur de la console (caret) aux coordonnées données
void moveCurs(int X, int Y)
{
    char tab[20];//tableau pour stocker la chaine
    sprintf(tab, "\033[%d;%dH", X, Y);//formattage du la chaine ANSI pour déplacer le curseur
    printf(tab);//déplacement du curseur
}