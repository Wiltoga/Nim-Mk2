#ifndef DEF_CASE_H
#define DEF_CASE_H
#include "bool.h"


typedef struct Case Case;
//Structure contenant l'ensemble des informations utiles d'une case du plateau
struct Case
{
    //vrai si la case est gagnante, sinon faux
    bool winning;
    //tableau de 4 cases, contenant les cases valides pour un déplacement (NULL si un déplacement est impossible)
    Case** availableMovements;
};

#endif //DEF_CASE_H