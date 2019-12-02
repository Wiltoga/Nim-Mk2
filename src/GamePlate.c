#include <stdlib.h>
#include "GamePlate.h"
#include "Position.h"
#include "utilities.h"

GamePlate* createPlate(GameOptions options)
{
    GamePlate* plate = malloc(sizeof(GamePlate));//on créé un plateau
    //simple assignation des tailles
    plate->nbColumns = options.ncol;
    plate->nbRows = options.nlig;
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
        free(plate->cases[i]);
    //on supprime le tableau
    free(plate->cases);
    //on supprime le plateau
    free(plate);
}
