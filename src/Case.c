#include "Case.h"
#include <stdlib.h> //pour NULL

void appendCase(Table table, Case* toAppend)
{
    int i = 0;
    while (table[i] != NULL)
        i++;
    table[i] = toAppend;
    table[i+1] = NULL;
}
void removeCase(Table table, Case* toRemove)
{
    int i = findCase(table, toRemove);
    if (i != -1)
        removeCaseAt(table, i);
}
int findCase(Table table, Case* toFind)
{
    int i = 0;
    while (table[i] != NULL)
    {
        if (table[i] == toFind)
            return i;
        i++;
    }
    return -1;
}
void removeCaseAt(Table table, int index)
{
    while (table[index] != NULL)
    {
        table[index] = table[index+1];
        index++;
    }
}
int tableLength(Table table)
{
    int i = 0;
    while (table[i] != NULL)
        i++;
    return i;
}