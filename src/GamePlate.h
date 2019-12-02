#ifndef DEF_GAME_PLATE_H
#define DEF_GAME_PLATE_H
#include "Case.h"
#include "gameOptions.h"

struct GamePlate
{
    Table cases;
    int nbColumns;
    int nbRows;
};
typedef struct GamePlate GamePlate;

//créé un tableau rempli un tableau selon certaines règles
GamePlate* createPlate(GameOptions);
//accède à une certaine case du plateau selon une position donnée
Case* accessCase(GamePlate*, Position);
//libère un plateau
void freePlate(GamePlate*);

#endif //DEF_GAME_PLATE_H