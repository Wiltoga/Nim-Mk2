#include <stdlib.h>
#include <stdio.h>
#include "consoleManagement.h"
#include "GamePlate.h"
#include "Position.h"
#include "utilities.h"

GamePlate* createPlate(GameOptions options)
{
    GamePlate* plate = malloc(sizeof(GamePlate)); //on créé un plateau

    //simple assignation des tailles
    plate->nbColumns = options.ncol;
    plate->nbRows = options.nlig;
    plate->level = options.niveau;
    plate->cases = malloc(options.nlig*options.ncol*sizeof(Case*)); //on créé le tableau

    int i, j;//indexeurs

    //l'indice de victoire est une valeur qui permet de savoir si une case est gagnante ou pas,
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
            tmpCase->winning = (i + j*2)%3 == winningHint; //test de case gagnante
        }
        
    for (i = 0;i<options.nban;i++) //on génère options.nban cases à bannir
    {
        bool nextBan = false; //deviens true quand tous les tests sont passés

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
                Case* tmp = accessCase(plate, newPosition(i+1, j)); //on récupère la case à droite
                curr->availableMovements[0] = tmp->banned ? NULL : tmp; //si elle n'est pas bannie, on l'ajoute aux voisines
                curr->availableMovements[1] = NULL; //la case suivante est le mur -> on n'en ajoute pas
            }
            else
            {
                //ici on se trouve ailleurs dans le plateau
                
                Case* tmp = accessCase(plate, newPosition(i+1, j)); //on récupère la case à droite
                curr->availableMovements[0] = tmp->banned ? NULL : tmp; //si elle n'est pas bannie, on l'ajoute aux voisines

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
                Case* tmp = accessCase(plate, newPosition(i, j+1)); //on récupère la case en dessous
                curr->availableMovements[2] = tmp->banned ? NULL : tmp; //si elle n'est pas bannie, on l'ajoute aux voisines
                curr->availableMovements[3] = NULL; //la case suivante est le mur -> on n'en ajoute pas
            }
            else
            {
                //ici on se trouve ailleurs dans le plateau
                
                Case* tmp = accessCase(plate, newPosition(i, j+1)); //on récupère la case en dessous
                curr->availableMovements[2] = tmp->banned ? NULL : tmp; //si elle n'est pas bannie, on l'ajoute aux voisines

                //si cette même case n'est pas bannie, on continue de vérifier les déplacements
                if (!tmp->banned)
                {
                    tmp = accessCase(plate, newPosition(i, j+2)); //on récupère la case suivante
                    curr->availableMovements[3] = tmp->banned ? NULL : tmp; //si elle n'est pas bannie, on l'ajoute aux voisines
                }
                else
                    curr->availableMovements[3] = NULL; //sinon, on n'ajoute rien au delà de la case bannie
            }
        }


    return plate;
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
    printf(FRONT_WHITE); //sélection de la couleur d'écriture
    
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
        }
        //chaque ligne doit se finir par du noir, sinon toute la ligne de la console sera de la couleur précédente
        printf(BACK_BLACK "\n");
    }
}
