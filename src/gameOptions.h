#ifndef DEF_GAME_OPTIONS_H
#define DEF_GAME_OPTIONS_H
#include "bool.h"

//Enumeration des modes de difficulté
enum Difficulty
{
    BEGINNER = 0,
    MEDIUM,
    EXPERT,
    VIRTUOSO,
    GODLIKE
};
typedef enum Difficulty Difficulty;
//Structure contenant l'ensemble des informations utiles à la création d'une partie de jeu
struct GameOptions
{
    //le nombre de lignes du plateau
    int nlig;
    //le nombre de colonnes du plateau
    int ncol;
    //le niveau de difficulté
    Difficulty niveau;
    //faux si l'ordi commence, vrai si le joueur commence
    bool next;
    //le nombre de cases bannies
    int nban;
};
typedef struct GameOptions GameOptions;

#endif //DEF_GAME_OPTIONS_H