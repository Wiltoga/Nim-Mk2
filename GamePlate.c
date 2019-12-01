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
    for (i = 0;i<options.nlig;i++)
        for (j = 0;j<options.ncol;j++)
        {
            //pour chaque case du tableau, on créé un objet Case
            Case* tmpCase = malloc(sizeof(Case));
            plate->cases[j + i*plate->nbColumns] = tmpCase;
            tmpCase->position = newPosition(j, i);
        }
    //todo : fill it randomly, set the winning tiles
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
