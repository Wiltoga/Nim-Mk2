#ifndef DEF_GAME_H
#define DEF_GAME_H
#include "Position.h"
#include "gameOptions.h"
#include "GamePlate.h"

//démarre une nouvelle partie de jeu
void startGame();
//défini les paramètres de lancement
GameOptions parameters();
//donne au joueur la possibilité de jouer son tour
Position Player(GamePlate*, Position, char*);
//donne à l'IA la possibilité de jouer un tour en modifiant la position du pion
Position IA(GamePlate*, Position);

#endif //DEF_GAME_H
