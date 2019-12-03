#ifndef DEF_BOOL_H
#define DEF_BOOL_H
//j'aime bien les booléens
//le matin je mange du booléen
//en cours je réfléchis en booléens
//je rêve de booléens
// je VIS le booléen
#ifdef WIN32

enum bool
{
    true = 1,
    false = 0
};
typedef enum bool bool;

#else

#define bool int
#define true 1
#define false 0

#endif
#endif //DEF_BOOL_H
