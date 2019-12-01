#Here you can find the functions used in the game

#Lire_entier is a function that enables you to enter a number which will then be read by the game 

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
      printf("%d is a part of the interval.", entier1);
    
  }
