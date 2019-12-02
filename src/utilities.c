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
bool containsCase(Case* toFind, Table plate, size_t size)
{
    int i;
    //on parcours le tableau...
    for (i = 0;i<size;i++)
        //si on trouve une occurence, on renvoie true
        if (plate[i] == toFind)
            return true;
    //si rien n'a été trouvé, on renvoie false
    return false;
}
bool containsPosition(Position pos, Table plate, size_t size)
{
    int i;
    //on parcours le tableau...
    for (i = 0;i<size;i++)
        //si on trouve une occurence, on renvoie true
        if (plate[i] != NULL &&
            plate[i]->position.x == pos.x &&
            plate[i]->position.y == pos.y)
            return true;
    //si rien n'a été trouvé, on renvoie false
    return false;
}