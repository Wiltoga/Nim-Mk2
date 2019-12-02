#include <stdlib.h>
#include "GamePlate.h"
#include "Position.h"

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
            plate->cases[j + i*options.ncol] = tmpCase;
            tmpCase->position = newPosition(j, i);
            tmpCase->winning = (i + j*2)%3 == winningHint;//test de case gagnante
        }
    //todo : fill it randomly with banned cases


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
