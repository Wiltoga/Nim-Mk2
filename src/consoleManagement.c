#include <stdio.h>
#include <stdlib.h>
#ifdef WIN32
#include <conio.h>
#else
#include <termios.h>
#endif
#include "consoleManagement.h"
#ifndef WIN32
//https://www.includehelp.com/c-programs/gotoxy-clrscr-getch-getche-for-gcc-linux.aspx
static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
  tcgetattr(0, &old); //grab old terminal i/o settings
  new = old; //make new settings same as old settings
  new.c_lflag &= ~ICANON; //disable buffered i/o
  new.c_lflag &= echo ? ECHO : ~ECHO; //set echo mode
  tcsetattr(0, TCSANOW, &new); //apply terminal io settings
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/*
Read 1 character without echo
getch() function definition.
*/
char getch(void)
{
  return getch_(0);
}

/*
Read 1 character with echo
getche() function definition.
*/
char getche(void)
{
  return getch_(1);
}
int getArrowPressed()
{
    //inspiré de https://stackoverflow.com/a/10473315
    int var = getch();//code de la touche pressée
    if (var == 27) //s'il s'agit d'une flèche part1...
    {
        if (getch() == 91) //s'il s'agit d'une flèche part2...
        {
            switch (getch())
            {
            case 65: //code fèche haut
                return UP;
            case 66: //code fèche bas
                return DOWN;
            case 68: //code fèche gauche
                return LEFT;
            case 67: //code fèche droite
                return RIGHT;
            }
        }
    }
    else if (var == 10) //entrée
        return RETURN;
    else
        return NONE;

}

#else
int getArrowPressed()
{
    //inspiré de https://stackoverflow.com/a/10473315
    int var = getch(); //on récupère le code du caractère entré dans la console
    if (var == 0 || var == 224) //s'il s'agit d'une flèche...
    {
        switch (getch())
        {
        case 72: //code fèche haut
            return UP;
        case 80: //code fèche bas
            return DOWN;
        case 75: //code fèche gauche
            return LEFT;
        case 77: //code fèche droite
            return RIGHT;
        }
    }
    else if(var == 13) //entrée
        return RETURN;
    else
        return NONE;

}
#endif

void clearScreen()
{
    system(
    #ifdef WIN32 //si on est sur Windows
    "cls");
    #else //si on est sur Unix
    "clear");
    #endif
}
