#Here you can find all the functions used in the game



1) "Lire_entier" is a function which takes a number and displays it

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


2) "Parametres" is a function that will take the number of lines and columns as well as the level and the difficulty. It's task is the random selection of restricted fields.