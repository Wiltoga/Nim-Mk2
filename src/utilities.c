#include "utilities.h"

inline int random(int min, int max)
{
    return min + rand()%(max - min);
}
//renvoie la plus grande valeur
inline int max(int val1, int val2)
{
    return val1 > val2 ? val1 : val2; 
}
//renvoie la plus petite valeur
inline int min(int val1, int val2)
{
    return val1 < val2 ? val1 : val2; 
}
