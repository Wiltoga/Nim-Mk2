#ifndef DEF_GAME_PLATE_H
#define DEF_GAME_PLATE_H
#include "Case.h"
#include "gameOptions.h"

//class représentant le plateau de jeu
struct GamePlate
{
    Table cases; //les cases du tableau
    size_t nbColumns; //le nombre de colonnes
    size_t nbRows; //le nombre de lignes
    Difficulty level; //la difficulté de l'IA
};
typedef struct GamePlate GamePlate;

GamePlate* createPlate(GameOptions); //créé un tableau rempli un tableau selon certaines règles
Case* accessCase(GamePlate*, Position); //accède à une certaine case du plateau selon une position donnée
void freePlate(GamePlate*); //libère un plateau

//affiche le plateau à l'écran en donnant la position du pion au début du tour et sa position temporaire choisie
void renderPlate(GamePlate*, Position, Position);

#endif //DEF_GAME_PLATE_H
