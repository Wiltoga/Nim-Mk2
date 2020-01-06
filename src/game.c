#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "Case.h"
#include "Position.h"
#include "consoleManagement.h"
#include "bool.h"
#include "GamePlate.h"
#include "utilities.h"

void startGame()
{
    GameOptions options = parameters();      //on appelle le générateur de paramètres
    GamePlate *plate = createPlate(options); //on créé le plateau de jeu
    Position pawn = newPosition(0, 0);       //on place le pion à (0,0)
    bool playerTurn = options.next;          //on défini par rapport aux paramètres qui commence

    //tant que le pion est en dehors du puit...
    while (pawn.x != plate->nbColumns - 1 || pawn.y != plate->nbRows - 1)
    {
        //si le tour est au joueur
        if (playerTurn)
            pawn = Player(plate, pawn, plate->level == MULTIPLAYER ? ", joueur 1" : ""); //on mets à jour notre place après sélection
        else if (plate->level != MULTIPLAYER)
            pawn = IA(plate, pawn); //on mets à jour notre place après sélection de l'IA
        else
            pawn = Player(plate, pawn, ", joueur 2"); //on mets à jour notre place après sélection

        playerTurn = !playerTurn; //on échange de joueur
    }
    //si on est ici, on a un vainqueur
    clearScreen();

    if (plate->level == MULTIPLAYER)
    {
        if (!playerTurn) //si l'un ou l'autre a gagngé..
            printf("\n" BACK_BRIGHT_CYAN FRONT_BLACK "Le joueur 1 a gagne !");
        else
            printf("\n" BACK_MAGENTA FRONT_WHITE "Le joueur 2 a gagne !");
    }
    else
    {
        if (!playerTurn) //si l'un ou l'autre a gagngé..
            printf("\n" BACK_BRIGHT_CYAN FRONT_BLACK "Le joueur a gagne !");
        else
            printf("\n" BACK_RED FRONT_WHITE "Le joueur a perdu !");
    }

    //formattage du bouton Retour
    printf(BACK_BLACK "\n\n" BACK_BRIGHT_RED FRONT_BLACK "Retour" BACK_BLACK "\n");
    //on attend la touche Entrée
    while (getArrowPressed() != RETURN)
        ;
    //on libère la RAM
    freePlate(plate);
}

GameOptions parameters()
{
    printf(FRONT_WHITE BACK_BLACK);
    clearScreen();
    GameOptions options;

    do
    {
        //boucle qui demande le nombre de lignes tant que le nombre ne respecte pas les limites
        printf("Nombre de lignes du plateau :");
        scanf("%d", &options.nlig);
        getchar();
 } while (options.nlig > VMAX || options.nlig < VMIN);

    clearScreen();

    do
    {
        //boucle qui demande le nombre de colonnes tant que le nombre ne respecte pas les limites
        printf("Nombre de colonnes du plateau :");
        scanf("%d", &options.ncol);
        getchar();
    } while (options.ncol > VMAX || options.ncol < VMIN);

    clearScreen();

    options.niveau = -1;
    int index = 1; //selecteur
    while (options.niveau == -1)
    {
        printf(FRONT_WHITE BACK_BLACK "Multijoueur ?\n");
        if (index == 0) //couleur "oui"
            printf(FRONT_BLACK BACK_BRIGHT_CYAN);
        else
            printf(FRONT_CYAN BACK_BLACK);
        printf("Oui" BACK_BLACK "\n");
        if (index == 1) //couleur "non"
            printf(FRONT_BLACK BACK_BRIGHT_MAGENTA);
        else
            printf(FRONT_MAGENTA BACK_BLACK);
        printf("Non" BACK_BLACK "\n");
        switch (getArrowPressed())
        {
        case UP:
            index--;
            break;
        case DOWN:
            index++;
            break;
        case RETURN:
            options.niveau = index;
            break;
        }
        index = (index + 2) % 2; //pour faire une boucle (-1%5 = -1 en C, malheureusement...)
        clearScreen();
    }
    if (options.niveau)
        options.niveau = -1;
    else
        options.niveau = MULTIPLAYER;
    index = 0; //selecteur
    while (options.niveau == -1)
    {
        printf(FRONT_WHITE BACK_BLACK "difficulte de l'ordinateur :\n");
        if (index == 0) //couleur "debutant"
            printf(FRONT_BLACK BACK_BRIGHT_CYAN);
        else
            printf(FRONT_CYAN BACK_BLACK);
        printf("debutant" BACK_BLACK "\n");
        if (index == 1) //couleur "moyen"
            printf(FRONT_BLACK BACK_BRIGHT_GREEN);
        else
            printf(FRONT_GREEN BACK_BLACK);
        printf("moyen" BACK_BLACK "\n");
        if (index == 2) //couleur "expert"
            printf(FRONT_BLACK BACK_BRIGHT_YELLOW);
        else
            printf(FRONT_YELLOW BACK_BLACK);
        printf("expert" BACK_BLACK "\n");
        if (index == 3) //couleur "virtuose"
            printf(FRONT_BLACK BACK_BRIGHT_RED);
        else
            printf(FRONT_RED BACK_BLACK);
        printf("virtuose" BACK_BLACK "\n");
        if (index == 4) //couleur "divin"
            printf(FRONT_MAGENTA BACK_RED "D I V I N");
        else
            printf(FRONT_BRIGHT_MAGENTA BACK_BLACK "divin");
        printf(BACK_BLACK "\n");
        switch (getArrowPressed())
        {
        case UP:
            index--;
            break;
        case DOWN:
            index++;
            break;
        case RETURN:
            options.niveau = index;
            break;
        }
        index = (index + 5) % 5; //pour faire une boucle (-1%5 = -1 en C, malheureusement...)
        clearScreen();
    }
    options.next = -1;
    index = 0;

    while (options.next == -1)
    {
        printf(FRONT_WHITE BACK_BLACK "qui commence ?\n");
        if (index == 0) //couleur "debutant"
            printf(FRONT_BLACK BACK_BRIGHT_CYAN);
        else
            printf(FRONT_CYAN BACK_BLACK);
        if (options.niveau == MULTIPLAYER)
            printf("le joueur 1" BACK_BLACK "\n");
        else
            printf("le joueur" BACK_BLACK "\n");
        if (index == 1) //couleur "moyen"
            printf(FRONT_BLACK BACK_BRIGHT_MAGENTA);
        else
            printf(FRONT_MAGENTA BACK_BLACK);
        if (options.niveau == MULTIPLAYER)
            printf("le joueur 2" BACK_BLACK "\n");
        else
            printf("l'ordinateur" BACK_BLACK "\n");
        switch (getArrowPressed())
        {
        case UP:
            index--;
            break;
        case DOWN:
            index++;
            break;
        case RETURN:
            options.next = !index;
            break;
        }
        index = (index + 2) % 2; //pour faire une boucle (-1%5 = -1 en C, malheureusement...)
        clearScreen();
    }
    options.nban = randomNumber(0, max(options.ncol, options.nlig) + 1); //on prend un nombre aléatoire de cases bannies
    return options;
}

Position Player(GamePlate *plate, Position pawn, char* playerName)
{
    Case *currentCase = accessCase(plate, pawn); //on récupère la case actuelle
    Position futurePos = pawn;                   //on stocke la position voulue du joueur dans cette variable
    int pressedKey;                              //on stocke la touche pressée ici
    do
    {
        //boucle du tour
        renderPlate(plate, pawn, futurePos); //on affiche le plateau
        printf("Votre tour%s !\n", playerName);

        pressedKey = getArrowPressed(); //on récupère la touche pressée
        switch (pressedKey)
        {
        case UP:                      //si on a appuyé sur haut
            if (futurePos.y > pawn.y) //et qu'on s'est déplacé vers le bas précédemment
                futurePos.y--;        //on remonte
            break;
        case DOWN: //si on a appuyé sur bas
        {
            Position tmpPos = futurePos; //on stocke l'éventuelle position future
            tmpPos.y++;                  //on mets à jour cette éventuelle position
            tmpPos.x = pawn.x;

            //on vérifie qu'elle est valide
            if (containsPosition(tmpPos, currentCase->availableMovements))
            {
                //si elle l'est, on mets à jour la position voulue
                futurePos.y++;
                futurePos.x = pawn.x;
            }
        }
        break;
        case LEFT:                    //si on a appuyé sur gauche
            if (futurePos.x > pawn.x) //et qu'on s'est déplacé vers la droite précédemment
                futurePos.x--;        //on va à gauche
            break;
        case RIGHT: //si on a appuyé sur droite
        {
            Position tmpPos = futurePos; //on stocke l'éventuelle position future
            tmpPos.x++;                  //on mets à jour cette éventuelle position
            tmpPos.y = pawn.y;

            //on vérifie qu'elle est valide
            if (containsPosition(tmpPos, currentCase->availableMovements))
            {
                //si elle l'est, on mets à jour la position voulue
                futurePos.x++;
                futurePos.y = pawn.y;
            }
        }
        break;
        }
        //tant que la touche Entrée n'a pas été pressée et que le pion est à une position différente de l'origine
    } while (pressedKey != RETURN || !(pawn.x != futurePos.x || pawn.y != futurePos.y));
    return futurePos;
}

//l'IA va jouer aléatoirement
Position IAPlaysRandomly(GamePlate *plate, Position currPos)
{
    Case *current = accessCase(plate, currPos); //case sur laquelle se trouve le pion
    int randomIndex = randomNumber(0, TableSize(current->availableMovements)); //on prend une position au hasard dedans
    return current->availableMovements[randomIndex]->position; //on renvoie cette sélection
}

//l'IA applique la stratégie gagnante
Position IAPlaysHard(GamePlate *plate, Position currPos)
{
    Case *current = accessCase(plate, currPos); //case sur laquelle se trouve le pion
    int i;
    Case *available;
    //on cherche une case gagnante parmis celles disponibles
    while ((available = current->availableMovements[i]) != NULL)
        if (available->winning)
            return available->position; //on l'a trouvé, on renvoie notre sélection
        else
            i++;
    //sinon on joue aléatoirement
    return IAPlaysRandomly(plate, currPos);
}

//l'IA applique la stratégie gagnante et en tente de gagner en cas de position perdante
Position IAPlaysVeryHard(GamePlate *plate, Position currPos)
{
    Case *current = accessCase(plate, currPos); //case sur laquelle se trouve le pion
    int i;
    Case *available;
    //on cherche une case gagnante parmis celles disponibles
    while ((available = current->availableMovements[i]) != NULL)
        if (available->winning)
            return available->position; //on l'a trouvé, on renvoie notre sélection
        else
            i++;

    //on a pas trouvé de case gagnante, on cherche à contrer le joueur
    i = 0;
    while ((available = current->availableMovements[i]) != NULL)
    {
        int j;
        bool hasWinningPossibilities = false;
        //on vérifie si chaque mouvement possible donne lieu à un mouvement gagnant
        Case *futureMovement;
        while ((futureMovement = current->availableMovements[j]) != NULL)
            if (futureMovement->winning)
                //si la case à tester possède une option de se trouver sur une case gagnante, on la marque
                hasWinningPossibilities = true;
            else
                j++;
        /*
         * si un déplacement propose une case qui elle ne propose aucun mouvement gagnant (apparait dans 
         * de rares cas selon la configuration des cases bannies)
        */
        if (!hasWinningPossibilities)
            //on renvoie ce mouvement qui va piéger le joueur
            return available->position;
    }
    //sinon on joue aléatoirement
    return IAPlaysRandomly(plate, currPos);
}

Position IA(GamePlate *plate, Position currPos)
{
    Position newPos;
    switch (plate->level)
    {
    case BEGINNER: //si on est en mode débutant
        //on joue aléatoirement
        newPos =  IAPlaysRandomly(plate, currPos);
        break;
    case MEDIUM: //si on est en mode moyen
        //on joue 1/3 gagnant, 2/3 aléatoirement
        newPos =  rand() % 3 == 0 ? IAPlaysHard(plate, currPos) : IAPlaysRandomly(plate, currPos);
        break;
    case EXPERT: //si on est en expert
        //on joue 2/3 gagnant, 1/3 aléatoirement
        newPos =  rand() % 3 <= 1 ? IAPlaysHard(plate, currPos) : IAPlaysRandomly(plate, currPos);
        break;
    case VIRTUOSO: //si on est en virtuose
        //on joue toujours avec la stratégie gagnante
        newPos =  IAPlaysHard(plate, currPos);
        break;
    case GODLIKE: //si on est en mode divin
        //on joue toujours avec la stratégie gagnante ET en essayant de piéger le joueur
        newPos =  IAPlaysVeryHard(plate, currPos);
        break;
    }
    renderPlate(plate, currPos, newPos);  //on affiche...
    printf("L'ordinateur joue... Appuyez sur Entree\n");
    while (getArrowPressed() != RETURN);         //on attend d'appuyer sur Entrée
    return newPos;
}
