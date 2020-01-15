#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "consoleManagement.h"
#include "GamePlate.h"
#include "Position.h"
#include "utilities.h"
#include "constants.h"

GamePlate* createPlate(GameOptions options)
{
    GamePlate* plate = malloc(sizeof(GamePlate)); //on créé un plateau

    //simple assignation des tailles
    plate->nbColumns = options.ncol;
    plate->nbRows = options.nlig;
    plate->level = options.niveau;
    plate->cases = malloc((options.nlig*options.ncol+1)*sizeof(Case*)); //on créé le tableau
    plate->cases[options.nlig*options.ncol] = NULL;

    int i, j;//indexeurs
    for (i=0;i<options.nlig*options.ncol;i++)
    {
        Case* curr = malloc(sizeof(Case));
        curr->position.x = i%options.ncol;
        curr->position.y = i/options.nlig;
        curr->banned = false;
        plate->cases[i] = curr;
    }
    for (i = 0;i<options.nban;i++) //on génère options.nban cases à bannir
    {
        bool nextBan = false; //deviens true quand tous les tests sont passés

        while (!nextBan)//tant que les tests sont négatifs
        {
            //on génère les coordonnées de la prochaine case à bannir
            int x = randomNumber(0, plate->nbColumns);
            int y = randomNumber(0, plate->nbRows);

            /*
             * pour les tests suivants, on peut tout mettre dans un seul grand if
             * mais pour des raisons de lisibilité, on segmente
             */
            if (
                    //si la case se trouve dans un des deux coins autorisés
                    (x == 0 && y == plate->nbRows-1 ||
                    x == plate->nbRows-1 && y == 0)
                    ||
                    //si la case se trouve dans la "partie centrale" du plateau
                    (x > 0 && x < plate->nbColumns-1 &&
                    y > 0 && y < plate->nbRows-1)
                )
            {
                //la case se trouve à un emplacement de plateau autorisé

                //on vérifie que la case n'est pas déjà bannie
                if (!accessCase(plate, newPosition(x, y))->banned)
                {
                    //s'il s'agit de la case en bas à gauche et qu'elle n'a pas de case bannnies dans la diagonale
                    if (x == 0 && !accessCase(plate, newPosition(x+1, y-1))->banned)
                        nextBan = true;
                    //s'il s'agit de la case en haut à droite et qu'elle n'a pas de case bannnies dans la diagonale
                    else if (y == 0 && !accessCase(plate, newPosition(x-1, y+1))->banned)
                        nextBan = true;
                    else if ( //sinon si aucune des cases dans sa diagonale (cases interdites) n'est occupée
                            !accessCase(plate, newPosition(x-1, y+1))->banned &&
                            !accessCase(plate, newPosition(x+1, y-1))->banned)
                        nextBan = true;
                }
            }
            if (nextBan) //si la case a passé tous les tests, on la bannie
                accessCase(plate, newPosition(x, y))->banned = true;
        }
    }
    for (i = 0;i<plate->nbColumns;i++)
        for (j = 0;j<plate->nbRows;j++)
        {
            //on parcours tout le tableau pour désigner les cases voisines
            //curr est la case actuelle à traiter
            Case* curr = accessCase(plate, newPosition(i, j));
            /*
             * on alloue un tableau de 4 cases voisines potentielles
             * chaque case du tableau possèdera une case voisine, le tableau se finissant par NULL
             */
            curr->availableMovements = malloc(5*sizeof(Case*));
            int nbMovements = 0;
            //si on se trouve à une extremité de l'axe x
            if (i == plate->nbColumns-1);
            //si on se trouve une case avant le mur
            else if (i == plate->nbColumns-2)
            {
                Case* tmp = accessCase(plate, newPosition(i+1, j)); //on récupère la case à droite
                if (!tmp->banned)
                    curr->availableMovements[nbMovements++] = tmp; //si elle n'est pas bannie, on l'ajoute aux voisines
            }
            else
            {
                //ici on se trouve ailleurs dans le plateau
                Case* tmp = accessCase(plate, newPosition(i+1, j)); //on récupère la case à droite
                if (!tmp->banned)
                    curr->availableMovements[nbMovements++] = tmp; //si elle n'est pas bannie, on l'ajoute aux voisines

                //si cette même case n'est pas bannie, on continue de vérifier les déplacements
                if (!tmp->banned)
                {
                    //on récupère la case suivante
                    tmp = accessCase(plate, newPosition(i+2, j));
                    if (!tmp->banned)
                        curr->availableMovements[nbMovements++] = tmp; //si elle n'est pas bannie, on l'ajoute aux voisines
                }
            }
            //si on se trouve à une extremité de l'axe y
            if (j == plate->nbRows-1);
            //si on se trouve une case avant le mur
            else if (j == plate->nbRows-2)
            {
                Case* tmp = accessCase(plate, newPosition(i, j+1)); //on récupère la case en dessous
                if (!tmp->banned)
                    curr->availableMovements[nbMovements++] = tmp; //si elle n'est pas bannie, on l'ajoute aux voisines
            }
            else
            {
                //ici on se trouve ailleurs dans le plateau
                
                Case* tmp = accessCase(plate, newPosition(i, j+1));
                if (!tmp->banned)
                    curr->availableMovements[nbMovements++] = tmp; //si elle n'est pas bannie, on l'ajoute aux voisines

                //si cette même case n'est pas bannie, on continue de vérifier les déplacements
                if (!tmp->banned)
                {
                    //on récupère la case suivante
                    Case* tmp = accessCase(plate, newPosition(i, j+2));
                    if (!tmp->banned)
                        curr->availableMovements[nbMovements++] = tmp; //si elle n'est pas bannie, on l'ajoute aux voisines
                }
            }
            curr->availableMovements[nbMovements] = NULL;
        }
    //nimbers
    {
        Table open = malloc((plate->nbRows*plate->nbColumns)*sizeof(Case*));
        int openLen = 0;
        for (i = 0;i<plate->nbColumns;i++)
            for(j = 0;j<plate->nbRows;j++)
                if ((i != plate->nbColumns-1 || j != plate->nbRows-1))
                        open[openLen++] = accessCase(plate, newPosition(i, j));
        open[openLen] = NULL;
        accessCase(plate, newPosition(plate->nbColumns-1, plate->nbRows-1))->winning = true;
        while (openLen > 0)
        {
            Case* currentOpen;
            for(i = 0;i<openLen;i++)
            {
                currentOpen = open[i];
                bool hasUndefined = false;
                for(j=0;currentOpen->availableMovements[j] != NULL;j++)
                    if (findCase(open, currentOpen->availableMovements[j]) > -1)
                        hasUndefined = true;
                if (!hasUndefined)
                {
                    bool hasWinningPossibilities = false;
                    for(j=0;currentOpen->availableMovements[j] != NULL;j++)
                        if (currentOpen->availableMovements[j]->winning)
                            hasWinningPossibilities = true;
                    if (currentOpen->banned)
                        hasWinningPossibilities = true;
                    currentOpen->winning = !hasWinningPossibilities;
                    removeCase(open, currentOpen);
                    openLen--;
                }
            }
        }
        free(open);
    }
    
    return plate;
}

void dispNimbers(GamePlate* plate)
{
    #ifndef NO_COLORS
    printf(FRONT_WHITE);
    int i, j;
    for (i=0;i<plate->nbRows;i++)
    {
        for (j=0;j<plate->nbColumns;j++)
        {
            Case* current = accessCase(plate, newPosition(j, i));
            if (current->banned)
                printf(BACK_BRIGHT_RED);
            else
                printf(BACK_BLACK);
            printf("%d", current->winning?0:1);
        }
        printf("\n");
    }
    #else
    int i, j;
    for (i=0;i<plate->nbRows;i++)
    {
        for (j=0;j<plate->nbColumns;j++)
        {
            Case* current = accessCase(plate, newPosition(j, i));
            if (current->banned)
                printf("X");
            else
                printf("%d", current->winning?0:1);
        }
        printf("\n");
    }
    #endif
}

Case* accessCase(GamePlate* plate, Position pos)
{
    return plate->cases[pos.x + pos.y*plate->nbColumns]; //on cherche l'endroit de la case demandée
}

void freePlate(GamePlate* plate)
{
    int i; //indexeur
    for (i = 0;i<plate->nbRows*plate->nbColumns;i++)
    //pour chaque element du tableau, on supprime la case
    {
        free(plate->cases[i]->availableMovements);
        free(plate->cases[i]);
    }
    
    free(plate->cases); //on supprime le tableau
    free(plate); //on supprime le plateau
}

void renderPlate(GamePlate* plate, Position pawnPos, Position currentSelection)
{
    clearScreen(); //on efface l'écran
    #ifndef NO_COLORS
    printf(FRONT_WHITE); //sélection de la couleur d'écriture
    #endif
    
    //indexes
    int i, j;
    
    Case* pawnCase = accessCase(plate, newPosition(pawnPos.x, pawnPos.y)); //la case sur laquelle se trouve le pion
    
    for (j = 0;j<plate->nbRows;j++)
    {
        for (i = 0;i<plate->nbColumns;i++)
        {
           //pour chaque case du plateau
           //on en récupère la case 
            Case* currentCase = accessCase(plate, newPosition(i, j));
            #ifndef NO_COLORS
            if (currentCase == pawnCase)
                //si la case est celle du pion, on mets en jaune
                printf(BACK_YELLOW);
            else if (containsCase(currentCase, pawnCase->availableMovements, 4) &&
                    i == plate->nbColumns-1 && j == plate->nbRows-1)
                //si la case est le puit et qu'il est disponible, on le mets en doré
                printf(BACK_BRIGHT_YELLOW);
            else if (i == plate->nbColumns-1 && j == plate->nbRows-1)
                //si la case est juste le puit, on mets en vert
                printf(BACK_GREEN);
            else if (containsCase(currentCase, pawnCase->availableMovements, 4))
                //si la case correspond à un mouvement autorisé, on mets en bleu
                printf(BACK_BLUE);
            else if (currentCase->banned)
                //si la case est bannie, on mets en rouge
                printf(BACK_RED);
            else
                //sinon, on colore le fond du plateau en gris
                printf(BACK_GREY);
            if (currentSelection.x == i && currentSelection.y == j)
                //si on se trouve sur la selection de position du pion, on mets un triangle
                printf("/\\");
            else
                //sinon on mets rien
                printf("  ");
            #else
            if (currentSelection.x == i && currentSelection.y == j)
                //si on se trouve sur la selection de position du pion, on mets un triangle
                printf("/\\");
            else if (containsCase(currentCase, pawnCase->availableMovements, 4))
                //si la case correspond à un mouvement autorisé, on mets une marque
                printf("__");
            else if (currentCase->banned)
                //si la case est bannie, on mets en rouge
                printf("XX");
            else
                //sinon, on colore le fond du plateau en gris
                printf("--");
            #endif
        }
        #ifndef NO_COLORS
        //chaque ligne doit se finir par du noir, sinon toute la ligne de la console sera de la couleur précédente
        printf(BACK_BLACK);
        #endif
        printf("\n");
    }
}
