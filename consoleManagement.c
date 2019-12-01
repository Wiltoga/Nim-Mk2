#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "consoleManagement.h"

void moveCurs(int X, int Y)
{
    char tab[20];//tableau pour stocker la chaine
    sprintf(tab, "\033[%d;%dH", X, Y);//formattage du la chaine ANSI pour déplacer le curseur
    printf(tab);//déplacement du curseur
}
int getArrowPressed()
{
    //inspiré de https://stackoverflow.com/a/10473315
    int var = getch();//on récupère le code du caractère entré dans la console
    if (var == 0 || var == 224)//s'il s'agit d'une flèche...
    {
        switch (getch())
        {
        case 72://code fèche haut
            return UP;
        case 80://code fèche bas
            return DOWN;
        case 75://code fèche gauche
            return LEFT;
        case 77://code fèche droite
            return RIGHT;
        }
    }
    else if(var == 13) //entrée
        return RETURN;
    else
        return NONE;
    
}
void clearScreen()
{
    system(
    #ifdef WIN32
    "cls");
    #else
    "clear");
    #endif
}
