#include <stdlib.h>
#include <stdio.h>
#include "consoleManagement.h"
#include "GamePlate.h"
#include "Position.h"
#include "utilities.h"

GamePlate* createPlate(GameOptions options)
{
    GamePlate* plate = malloc(sizeof(GamePlate));//on créé un plateau
    //simple assignation des tailles
    plate->nbColumns = options.ncol;
    plate->nbRows = options.nlig;
    plate->level = options.niveau;
    plate->cases = malloc(options.nlig*options.ncol*sizeof(Case*));//on créé le tableau
    int i, j;//indexeurs
    //l'indice de victoire est une valeur qui permet de savoir si une case est gagnante ou pas
    //étant donné que le plateau suit un shéma particulier (une diagonale de case perdante puis 2 diagonales de cases gagnantes)
    int winningHint = ((options.nlig - 1) + (options.ncol - 1)*2)%3;
    for (i = 0;i<options.nlig;i++)
        for (j = 0;j<options.ncol;j++)
        {
            //pour chaque case du tableau, on créé un objet Case
            Case* tmpCase = malloc(sizeof(Case));
            tmpCase->banned = false;
            plate->cases[j + i*options.ncol] = tmpCase;
            tmpCase->position = newPosition(j, i);
            tmpCase->winning = (i + j*2)%3 == winningHint;//test de case gagnante
        }
        //on génère options.nban cases à bannir
    for (i = 0;i<options.nban;i++)
    {
        //deviens true quand tous les tests sont passés
        bool nextBan = false;
        while (!nextBan)//tant que les tests sont négatifs
        {
            //on génère les coordonnées de la prochaine case à bannir
            int x = random(0, plate->nbColumns);
            int y = random(0, plate->nbRows);
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
                    else if (//sinon si aucune des cases dans sa diagonale (cases interdites) n'est occupée
                            !accessCase(plate, newPosition(x-1, y+1))->banned &&
                            !accessCase(plate, newPosition(x+1, y-1))->banned)
                        nextBan = true;
                }
            }
            if (nextBan)//si la case a passé tous les tests, on la bannie
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
             * chaque case du tableau possèdera la case voisine en question, ou NULL si
             * elle est indisponible (bloquée par un mur, case bannie)
             */
            curr->availableMovements = malloc(4*sizeof(Case*));
            //si on se trouve à une extremité de l'axe x
            if (i == plate->nbColumns-1)
            {
                //on mets les deux à NULL puisqu'on se trouve collé à un mur
                curr->availableMovements[0] = NULL;
                curr->availableMovements[1] = NULL;
            }
            //si on se trouve une case avant le mur
            else if (i == plate->nbColumns-2)
            {
                //on récupère la case à droite
                Case* tmp = accessCase(plate, newPosition(i+1, j));
                //si elle n'est pas bannie, on l'ajoute aux voisines
                curr->availableMovements[0] = tmp->banned ? NULL : tmp;
                //la case suivante est le mur -> on n'en ajoute pas
                curr->availableMovements[1] = NULL;
            }
            else
            {
                //ici on se trouve ailleurs dans le plateau
                //on récupère la case à droite
                Case* tmp = accessCase(plate, newPosition(i+1, j));
                //si elle n'est pas bannie, on l'ajoute aux voisines
                curr->availableMovements[0] = tmp->banned ? NULL : tmp;
                //si cette même case n'est pas bannie, on continue de vérifier les déplacements
                if (!tmp->banned)
                {
                    //on récupère la case suivante
                    tmp = accessCase(plate, newPosition(i+2, j));
                    //si elle n'est pas bannie, on l'ajoute aux voisines
                    curr->availableMovements[1] = tmp->banned ? NULL : tmp;
                }
                else
                    //sinon, on n'ajoute rien au delà de la case bannie
                    curr->availableMovements[1] = NULL;
            }
            //si on se trouve à une extremité de l'axe y
            if (j == plate->nbRows-1)
            {
                //on mets les deux à NULL puisqu'on se trouve collé à un mur
                curr->availableMovements[2] = NULL;
                curr->availableMovements[3] = NULL;
            }
            //si on se trouve une case avant le mur
            else if (j == plate->nbRows-2)
            {
                //on récupère la case en dessous
                Case* tmp = accessCase(plate, newPosition(i, j+1));
                //si elle n'est pas bannie, on l'ajoute aux voisines
                curr->availableMovements[2] = tmp->banned ? NULL : tmp;
                //la case suivante est le mur -> on n'en ajoute pas
                curr->availableMovements[3] = NULL;
            }
            else
            {
                //ici on se trouve ailleurs dans le plateau
                //on récupère la case en dessous
                Case* tmp = accessCase(plate, newPosition(i, j+1));
                //si elle n'est pas bannie, on l'ajoute aux voisines
                curr->availableMovements[2] = tmp->banned ? NULL : tmp;
                //si cette même case n'est pas bannie, on continue de vérifier les déplacements
                if (!tmp->banned)
                {
                    //on récupère la case suivante
                    tmp = accessCase(plate, newPosition(i, j+2));
                    //si elle n'est pas bannie, on l'ajoute aux voisines
                    curr->availableMovements[3] = tmp->banned ? NULL : tmp;
                }
                else
                    //sinon, on n'ajoute rien au delà de la case bannie
                    curr->availableMovements[3] = NULL;
            }
        }


    return plate;
}
Case* accessCase(GamePlate* plate, Position pos)
{
    //on cherche l'endroit de la case demandée
    return plate->cases[pos.x + pos.y*plate->nbColumns];
}
void freePlate(GamePlate* plate)
{
    int i;//indexeur
    for (i = 0;i<plate->nbRows*plate->nbColumns;i++)
    //pour chaque element du tableau, on supprime la case
    {
        free(plate->cases[i]->availableMovements);
        free(plate->cases[i]);
    }
    //on supprime le tableau
    free(plate->cases);
    //on supprime le plateau
    free(plate);
}
void renderPlate(GamePlate* plate, Position pawnPos, Position currentSelection)
{
    clearScreen();
    printf(FRONT_WHITE);
    int i, j;
    Case* pawnCase = accessCase(plate, newPosition(pawnPos.x, pawnPos.y));
    for (j = 0;j<plate->nbRows;j++)
    {
        for (i = 0;i<plate->nbColumns;i++)
        {
            Case* currentCase = accessCase(plate, newPosition(i, j));
            if (currentCase == pawnCase)
                printf(BACK_YELLOW);
            else if (containsCase(currentCase, pawnCase->availableMovements, 4) &&
                    i == plate->nbColumns-1 && j == plate->nbRows-1)
                printf(BACK_BRIGHT_YELLOW);
            else if (i == plate->nbColumns-1 && j == plate->nbRows-1)
                printf(BACK_GREEN);
            else if (containsCase(currentCase, pawnCase->availableMovements, 4))
                printf(BACK_BLUE);
            else if (currentCase->banned)
                printf(BACK_RED);
            else
                printf(BACK_GREY);
            if (currentSelection.x == i && currentSelection.y == j)
                printf("/\\");
            else
                printf("  ");
        }
        printf(BACK_BLACK "\n");
    }
}