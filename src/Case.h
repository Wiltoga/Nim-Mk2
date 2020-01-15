#ifndef DEF_CASE_H
#define DEF_CASE_H
#include <stdbool.h>
#include "Position.h"

struct Case;
typedef struct Case Case;

typedef Case** Table;

//Structure contenant l'ensemble des informations utiles d'une case du plateau
struct Case
{
    //position de la case dans le plateau
    Position position;
    //vrai si cette case est bannie
    bool banned;
    //vrai si la case est gagnante (nimber = 0), sinon faux (nimber != 0)
    bool winning;
    //tableau contenant les cases valides pour un déplacement (finissant par NULL)
    Table availableMovements;
};
//ajoute une case au tableau
void appendCase(Table, Case*);
//trouve une case spécifique du tableau, ou -1 si aucune case n'est trouvée
int findCase(Table, Case*);
//retire une case spécifique du tableau
void removeCase(Table, Case*);
//retire une case à un index spécifique du tableau
void removeCaseAt(Table, int);
//renvoie la taille du tableau
int tableLength(Table);

#endif //DEF_CASE_H