#include <stdlib.h>
#include "utilities.h"

inline int randomNumber(int min, int max)
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
bool containsCase(Case* toFind, Table plate)
{
    int i=0;
    //on parcours le tableau...
    while(plate[i]!=NULL)
        //si on trouve une occurence, on renvoie true
        if (plate[i] == toFind)
            return true;
        else
            i++;
    //si rien n'a été trouvé, on renvoie false
    return false;
}
bool containsPosition(Position pos, Table plate)
{
    Case* curr;
    int i = 0;
    //on parcours le tableau...
    while ((curr = plate[i]) != NULL)
        //si on trouve une occurence, on renvoie true
        if (curr->position.x == pos.x &&
            curr->position.y == pos.y)
            return true;
        else
            i++;
    //si rien n'a été trouvé, on renvoie false
    return false;
}
int TableSize(Table table)
{
    int size = 0;
    while (table[size] != NULL)
        size++;
    return size;
}