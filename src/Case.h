#ifndef DEF_CASE_H
#define DEF_CASE_H
#include "bool.h"
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
    //vrai si la case est gagnante, sinon faux
    bool winning;
    //tableau de 4 cases, contenant les cases valides pour un déplacement (NULL si un déplacement est impossible)
    Table availableMovements;
};

#endif //DEF_CASE_H