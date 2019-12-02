#ifndef DEF_GAME_PLATE_H
#define DEF_GAME_PLATE_H
#include "Case.h"
#include "gameOptions.h"

struct GamePlate
{
    Table cases;
    size_t nbColumns;
    size_t nbRows;
    Difficulty level;
};
typedef struct GamePlate GamePlate;

//créé un tableau rempli un tableau selon certaines règles
GamePlate* createPlate(GameOptions);
//accède à une certaine case du plateau selon une position donnée
Case* accessCase(GamePlate*, Position);
//libère un plateau
void freePlate(GamePlate*);
//affiche le plateau à l'écran en donnant la position du pion au début du tour et sa position temporaire choisie
void renderPlate(GamePlate*, Position, Position);

#endif //DEF_GAME_PLATE_H