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
    Position pawn = newPosition(0, 0);
    bool playerTurn = options.next;
    while (pawn.x != plate->nbColumns-1 || pawn.y != plate->nbRows-1)
    {
        Case* currentCase = accessCase(plate, pawn);
        if (playerTurn)
        {
            Position futurePos = pawn;
            int pressedKey;
            do
            {
                renderPlate(plate, pawn, futurePos);
                printf("Votre tour !\n");
                pressedKey = getArrowPressed();
                switch (pressedKey)
                {
                case UP:
                    if (futurePos.y == pawn.y + 2)
                        if (containsPosition(newPosition(futurePos.x, futurePos.y-1), currentCase->availableMovements, 4))
                            futurePos.y--;
                    break;
                case DOWN:
                    {
                        Position tmpPos = futurePos;
                        tmpPos.y++;
                        tmpPos.x = pawn.x;
                        if (containsPosition(tmpPos, currentCase->availableMovements, 4))
                        {
                            futurePos.y++;
                            futurePos.x = pawn.x;
                        }
                    }
                    break;
                case LEFT:
                    if (futurePos.x == pawn.x + 2)
                        if (containsPosition(newPosition(futurePos.x-1, futurePos.y), currentCase->availableMovements, 4))
                            futurePos.x--;
                    break;
                case RIGHT:
                    {
                        Position tmpPos = futurePos;
                        tmpPos.x++;
                        tmpPos.y = pawn.y;
                        if (containsPosition(tmpPos, currentCase->availableMovements, 4))
                        {
                            futurePos.x++;
                            futurePos.y = pawn.y;
                        }
                    }
                    break;
                }
            } while (pressedKey != RETURN || pawn.x != futurePos.x && pawn.y != futurePos.y);
            pawn = futurePos;
        }
        else
        {

        }
        playerTurn = !playerTurn;
    }


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

Position IA(GamePlate* plate, Position curPos)
{
    Position newPos;
    GameOptions options;
    bool isWinCaseFounded = false;

    switch(options.niveau)
    {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            // On met les distances au maximum pour être sûr de trouver la case gagnante la plus proche
            int i, distanceX = options.ncol, distanceY = options.nlig;
            for(i = 0; i < 4; i++) //4 directions
            {
                Position nextPos;
                switch(i)
                {
                    case 0:
                        // 1 case à droite
                        nextPos = newPosition(curPos.x+1, curPos.y);
                        break;
                    case 1:
                        // 2 cases à droite
                        nextPos = newPosition(curPos.x+2, curPos.y);
                        break;
                    case 2:
                        // 1 case en bas
                        nextPos = newPosition(curPos.x, curPos.y+1);
                        break;
                    case 3:
                        // 2 cases en bas
                        nextPos = newPosition(curPos.x, curPos.y+2);
                        break;
                }

                Case* nextCase = accessCase(&plate, nextPos);
                int nextDistanceX, nextDistanceY;
                if(nextCase->winning)
                {
                    // cherche la case gagnante la plus proche
                    if(!(nextCase->banned))
                    {
                        isWinCaseFounded = true;
                        nextDistanceX = nextCase->position.x - curPos.x;
                        nextDistanceY = nextCase->position.y - curPos.y;
                        if(distanceX < nextDistanceX || distanceY < nextDistanceY)
                            newPos = nextCase->position;
                    }
                    else if(i == 0 || i == 2)
                    {
                        /* 
                            si une case adjacente est bloqué, on ne peux acceder à
                            celles qui se trouve dans la même direction, donc on saute
                            une étape pour regarder dans une autre direction.
                        */
                        i++;
                    }
                }
                else if(!isWinCaseFounded)
                {
                    // prépare un coup au hasard
                    Position rndPos;
                    do
                    {
                        int rndPosX;
                        int rndPosY;
                        rndPosX = random(curPos.x, curPos.x+2);
                        rndPosY = random(curPos.y, curPos.y+2);

                        if(
                            (rndPosX == curPos.x && rndPosY > curPos.y)
                            || (rndPosX > curPos.x && rndPosY == curPos.y)
                        )
                        {
                            nextPos = newPosition(rndPosX, rndPosY);
                            nextCase = accessCase(&plate, rndPos);
                            if(!(nextCase->banned))
                                break;
                        }      
                    } 
                    while (true);
                }
            }
            break;
        case 5:
            break;
    }
    return newPos;
}
