#Here you can find all the functions used in the game



1) "Lire_entier" is a function which takes a number and displays it

------------------------------------------------------------------------------------------------
```C
#include <stdio.h>
#define VMIN 5
#define VMAX 30

    int Lire_entier(int entier1)
  {
    
      while ((entier1<=VMIN) || (entier1>=VMAX))
     {
         printf("Type a number between %d and %d:\n", VMIN, VMAX);
         scanf("%d", &entier1);
         if ((entier1>=VMAX) && (entier1<=VMIN))
         printf("The number is not part of the interval.\n");
     }
      if ((entier1<=VMAX) && (entier1>=VMIN))  
        return entier1;
  }
```
  ------------------------------------------------------------------------------------------------


2) "Parametres" is a function that will take the number of lines and columns as well as the level and the difficulty. It's task is the random selection of restricted fields.

------------------------------------------------------------------------------------------------
```C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define VMAX 30
#define VMIN 5
#define NIVMAX 4
#define NIVMIN 1


int Parametres(int nlig, int ncol, int niveau, next, int nban)
{
    while ((nlig<VMIN) || (nlig>VMAX))
    {
        printf("Type a number of lines for the platform:\n");
        scanf("%d", &nlig);                
        if ((nlig<VMIN) || (nlig>VMAX))  //reprompte l'utilisateur à saisir le nb de colonnes au cas où le nb n'est pas dans les bornes
        {
            printf("Entered number is not part of the interval, retry.\n");
        }
    }
    while ((ncol<VMIN) || (ncol>VMAX))
    {
        printf("Type a number of columns for the platform:\n");
        scanf("%d", &ncol);
        if ((ncol<VMIN) || (ncol>VMAX))            //reprompte l'utilisateur à saisir le nb de colonnes au cas où le nb n'est pas dans les bornes
        {
            printf("Entered number is not part of the interval, retry.\n");
        }
    }
    while ((niveau<1) || (niveau>4))
    {
        printf("Select a difficulty from 1 to 4:\n") 
        scanf("%d", &niveau)
        if((niveau<1) || (niveau>4))  //reprompte l'utilisateur à saisir le nb de colonnes au cas où le nb n'est pas dans les bornes
        {
            printf("The difficulty doesn't exist, retry.\n")
        }
    }
    bool next = true;
    printf("If you wish to start first press 1 and if not, press 2:\n"); //a revoir et optimiser
    scanf("%i\n", &next);
    
    int nban = rand() % max(nlig, ncol); //nombre de lignes bannies
    //inspiré par https://stackoverflow.com/questions/822323/how-to-generate-a-random-int-in-c

    return nban;
  }
```



------------------------------------------------------------------------------------------------
