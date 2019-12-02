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
            } while (pressedKey != RETURN || !(pawn.x != futurePos.x || pawn.y != futurePos.y));
            pawn = futurePos;
        }
        else
        {
            Position IAPos = IA(plate, pawn);
            renderPlate(plate, pawn, IAPos);
            printf("L'ordinateur joue... Appuyez sur Entree\n");
            while (getArrowPressed() != RETURN);
            pawn = IAPos;
        }
        playerTurn = !playerTurn;
    }
    clearScreen();
    if (!playerTurn)
        printf("\n" BACK_BRIGHT_CYAN FRONT_BLACK "Le joueur a gagne !");
    else
        printf("\n" BACK_RED FRONT_WHITE "Le joueur a perdu !");
    printf(BACK_BLACK "\n\n" BACK_BRIGHT_RED FRONT_BLACK "Retour" BACK_BLACK "\n");
    while (getArrowPressed() != RETURN);

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
Position IAPlaysRandomly(GamePlate* plate, Position currPos)
{
    Case* current = accessCase(plate, currPos);
    while(true)
    {
        int randomIndex = random(0, 4);
        if (current->availableMovements[randomIndex] != NULL)
            return current->availableMovements[randomIndex]->position;
    }
}
Position IAPlaysHard(GamePlate* plate, Position currPos)
{
    Case* current = accessCase(plate, currPos);
    int i;
    for(i = 0;i<4;i++)
    {
        if (current->availableMovements[i] != NULL &&
            current->availableMovements[i]->winning)
            return current->availableMovements[i]->position;
    }
    return IAPlaysRandomly(plate, currPos);
}
Position IAPlaysVeryHard(GamePlate* plate, Position currPos)
{
    Case* current = accessCase(plate, currPos);
    int i;
    for(i = 0;i<4;i++)
    {
        if (current->availableMovements[i] != NULL &&
            current->availableMovements[i]->winning)
            return current->availableMovements[i]->position;
    }
    for(i = 0;i<4;i++)
    {
        Case* caseToTest = current->availableMovements[i];
        if (caseToTest != NULL)
        {
            int j;
            bool hasWinningPossibilities = false;
            for(j = 0;j<4;j++)
            {
                if (caseToTest->availableMovements[j] != NULL &&
                    caseToTest->availableMovements[j]->winning)
                    hasWinningPossibilities = true;
            }
            if (!hasWinningPossibilities)
                return caseToTest->position;
        }
    }
    return IAPlaysRandomly(plate, currPos);
}
Position IA(GamePlate* plate, Position currPos)
{
    switch(plate->level)
    {
        case BEGINNER:
            return IAPlaysRandomly(plate, currPos);
        case MEDIUM:
            return rand()%3 == 0 ? IAPlaysHard(plate, currPos) : IAPlaysRandomly(plate, currPos);
        case EXPERT:
            return rand()%3 <= 1 ? IAPlaysHard(plate, currPos) : IAPlaysRandomly(plate, currPos);
        case VIRTUOSO:
            return IAPlaysHard(plate, currPos);
        case GODLIKE:
        return IAPlaysVeryHard(plate, currPos);
    }
}
