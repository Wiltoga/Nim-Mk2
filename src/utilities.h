#ifndef DEF_UTILITIES_H
#define DEF_UTILITIES_H
#include <stdbool.h>
#include "Case.h"
#include "Position.h"

//génère un nombre aléatoire entre un minimum et un maximum
int randomNumber(int, int);
//renvoie la plus grande valeur
int max(int, int);
//renvoie la plus petite valeur
int min(int, int);
//renvoie true si la case passée en paramètre est dans le tableau
bool containsCase(Case*, Table, size_t);
//renvoie true si la position passée en paramètre est trouvée parmis les cases du tableau
bool containsPosition(Position, Table);
//renvoie la taille d'un plateau
int TableSize(Table);

#endif
