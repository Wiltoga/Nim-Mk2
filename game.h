#ifndef DEF_GAME_H
#define DEF_GAME_H
#define VMIN 5
#define VMAX 30
#include "Position.h"
#include "gameOptions.h"
#include "GamePlate.h"

//démarre une nouvelle partie de jeu
void startGame();
//défini les paramètres de lancement
GameOptions parameters();
//donne à l'IA la possibilité de jouer un tour en modifiant la position du pion
Position IA(GamePlate*, Position);

#endif //DEF_GAME_H