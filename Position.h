#ifndef DEF_POSITION_H
#define DEF_POSITION_H


//Structure contenant un axe x et y, par rapport au point en haut à gauche (démarre à 1,1)
struct Position
{
    //composante des abscisses de la position
    unsigned int x;
    //composante des ordonnées de la position
    unsigned int y;
};
typedef struct Position Position;
//créé un nouvel objet Position selon les arguments donnés (x, y)
Position newPosition(unsigned int, unsigned int);

#endif //DEF_POSITION_H