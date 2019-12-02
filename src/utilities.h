#ifndef DEF_UTILITIES_H
#define DEF_UTILITIES_H
#include <stdlib.h>
#include "bool.h"
#include "Case.h"

//génère un nombre aléatoire entre un minimum et un maximum
int random(int, int);
//renvoie la plus grande valeur
int max(int, int);
//renvoie la plus petite valeur
int min(int, int);
//renvoie true si la case passée en paramètre est dans le tableau
bool containsCase(Case*, Table, size_t);

#endif