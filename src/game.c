#include <stdio.h>
#include "game.h"
#include "Case.h"
#include "Position.h"
#include "consoleManagement.h"
#include "bool.h"
#include "GamePlate.h"
#include "utilities.h"

void startGame()
{
    //on appelle le générateur de paramètres
    GameOptions options = parameters();
    //on créé le plateau de jeu
    GamePlate* plate = createPlate(options);
    //on place le pion à (0,0)
    Position pawn = newPosition(0, 0);
    //on défini par rapport aux paramètres qui commence
    bool playerTurn = options.next;
    //tant que le pion est en dehors du puit...
    while (pawn.x != plate->nbColumns-1 || pawn.y != plate->nbRows-1)
    {
        //on récupère la case actuelle
        Case* currentCase = accessCase(plate, pawn);
        //si le tour est au joueur
        if (playerTurn)
        {
            //on stocke la position voulue du joueur dans cette variable
            Position futurePos = pawn;
            //on stocke la touche pressée ici
            int pressedKey;
            do
            {
                //boucle du tour
                //on affiche le plateau
                renderPlate(plate, pawn, futurePos);
                printf("Votre tour !\n");
                //on récupère la touche pressée
                pressedKey = getArrowPressed();
                switch (pressedKey)
                {
                case UP://si on a appuyé sur haut
                    if (futurePos.y > pawn.y)//si on s'est déplacé vers le bas précédemment
                        futurePos.y--;//on remonte
                    break;
                case DOWN://si on a appuyé sur bas
                    {
                        //on stocke l'éventuelle position future
                        Position tmpPos = futurePos;
                        //on mets à jour cette éventuelle position
                        tmpPos.y++;
                        tmpPos.x = pawn.x;
                        //on vérifie qu'elle est valide
                        if (containsPosition(tmpPos, currentCase->availableMovements, 4))
                        {
                            //si elle l'est, on mets à jour la position voulue
                            futurePos.y++;
                            futurePos.x = pawn.x;
                        }
                    }
                    break;
                case LEFT://si on a appuyé sur gauche
                    if (futurePos.x > pawn.x)//si on s'est déplacé vers la droite précédemment
                        futurePos.x--;//on va à gauche
                    break;
                case RIGHT://si on a appuyé sur droite
                    {
                        //on stocke l'éventuelle position future
                        Position tmpPos = futurePos;
                        //on mets à jour cette éventuelle position
                        tmpPos.x++;
                        tmpPos.y = pawn.y;
                        //on vérifie qu'elle est valide
                        if (containsPosition(tmpPos, currentCase->availableMovements, 4))
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
            //on mets à jour notre place après sélection
            pawn = futurePos;
        }
        else
        {
            //on récupère les mouvements de l'IA
            Position IAPos = IA(plate, pawn);
            //on affiche...
            renderPlate(plate, pawn, IAPos);
            printf("L'ordinateur joue... Appuyez sur Entree\n");
            //on attend d'appuyer sur Entrée
            while (getArrowPressed() != RETURN);
            //on mets à jour notre place après sélection de l'IA
            pawn = IAPos;
        }
        //on échange de joueur
        playerTurn = !playerTurn;
    }
    //si on est ici, on a un vainqueur
    clearScreen();
    //si l'un ou l'autre a gagngé..
    if (!playerTurn)
        printf("\n" BACK_BRIGHT_CYAN FRONT_BLACK "Le joueur a gagne !");
    else
        printf("\n" BACK_RED FRONT_WHITE "Le joueur a perdu !");
    //formattage du bouton Retour
    printf(BACK_BLACK "\n\n" BACK_BRIGHT_RED FRONT_BLACK "Retour" BACK_BLACK "\n");
    //on attend la touche Entrée
    while (getArrowPressed() != RETURN);
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
    } while (options.nlig > VMAX || options.nlig < VMIN);
    clearScreen();
    do
    {
        //boucle qui demande le nombre de colonnes tant que le nombre ne respecte pas les limites
        printf("Nombre de colonnes du plateau :");
        scanf("%d", &options.ncol);
    } while (options.ncol > VMAX || options.ncol < VMIN);
    clearScreen();
    options.niveau = -1;
    int index = 0;//selecteur
    while (options.niveau == -1)
    {
        printf(FRONT_WHITE BACK_BLACK "difficulte de l'ordinateur :\n");
        if (index == 0)//couleur "debutant"
            printf(FRONT_BLACK BACK_BRIGHT_CYAN);
        else
            printf(FRONT_CYAN BACK_BLACK);
        printf("debutant" BACK_BLACK "\n");
        if (index == 1)//couleur "moyen"
            printf(FRONT_BLACK BACK_BRIGHT_GREEN);
        else
            printf(FRONT_GREEN BACK_BLACK);
        printf("moyen" BACK_BLACK "\n");
        if (index == 2)//couleur "expert"
            printf(FRONT_BLACK BACK_BRIGHT_YELLOW);
        else
            printf(FRONT_YELLOW BACK_BLACK);
        printf("expert" BACK_BLACK "\n");
        if (index == 3)//couleur "virtuose"
            printf(FRONT_BLACK BACK_BRIGHT_RED);
        else
            printf(FRONT_RED BACK_BLACK);
        printf("virtuose" BACK_BLACK "\n");
        if (index == 4)//couleur "divin"
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
        index = (index + 5)%5; //pour faire une boucle (-1%5 = -1 en C, malheureusement...)
        clearScreen();
    }
    options.next = -1;
    index = 0;
    while (options.next == -1)
    {
        printf(FRONT_WHITE BACK_BLACK "qui commence ?\n");
        if (index == 0)//couleur "debutant"
            printf(FRONT_BLACK BACK_BRIGHT_CYAN);
        else
            printf(FRONT_CYAN BACK_BLACK);
        printf("le joueur" BACK_BLACK "\n");
        if (index == 1)//couleur "moyen"
            printf(FRONT_BLACK BACK_BRIGHT_MAGENTA);
        else
            printf(FRONT_MAGENTA BACK_BLACK);
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
        index = (index + 2)%2; //pour faire une boucle (-1%5 = -1 en C, malheureusement...)
        clearScreen();
    }
    options.nban = random(0, max(options.ncol, options.nlig)+1);//on prend un nombre aléatoire de cases bannies
    return options;
}
//l'IA va jouer aléatoirement
Position IAPlaysRandomly(GamePlate* plate, Position currPos)
{
    //case sur laquelle se trouve le pion
    Case* current = accessCase(plate, currPos);
    while(true)
    {
        //tant qu'on a pas trouvé une position valide, on test...
        int randomIndex = random(0, 4);
        if (current->availableMovements[randomIndex] != NULL)//si notre position est valide,
            //on renvoie cette sélection
            return current->availableMovements[randomIndex]->position;
    }
}
//l'IA applique la stratégie gagnante
Position IAPlaysHard(GamePlate* plate, Position currPos)
{
    //case sur laquelle se trouve le pion
    Case* current = accessCase(plate, currPos);
    int i;
    for(i = 0;i<4;i++)
    {
        //on cherche une case gagnante parmis celles disponibles
        if (current->availableMovements[i] != NULL &&
            current->availableMovements[i]->winning)
            //on l'a trouvé, on renvoie notre sélection
            return current->availableMovements[i]->position;
    }
    //sinon on joue aléatoirement
    return IAPlaysRandomly(plate, currPos);
}
//l'IA applique la stratégie gagnante et en tente de gagner en cas de position perdante
Position IAPlaysVeryHard(GamePlate* plate, Position currPos)
{
    //case sur laquelle se trouve le pion
    Case* current = accessCase(plate, currPos);
    int i;
    for(i = 0;i<4;i++)
    {
        //on cherche une case gagnante parmis celles disponibles
        if (current->availableMovements[i] != NULL &&
            current->availableMovements[i]->winning)
            //on l'a trouvé, on renvoie notre sélection
            return current->availableMovements[i]->position;
    }
    //on a pas trouvé de case gagnante, on cherche à contrer le joueur
    for(i = 0;i<4;i++)
    {
        //on test chaque case possible
        Case* caseToTest = current->availableMovements[i];
        if (caseToTest != NULL)
        {
            int j;
            //on vérifie si chaque mouvement possible donne lieu à un mouvement gagnant
            bool hasWinningPossibilities = false;
            for(j = 0;j<4;j++)
            {
                if (caseToTest->availableMovements[j] != NULL &&
                    caseToTest->availableMovements[j]->winning)
                    //si la case à tester possède une option de se trouver sur une case gagnante, on la marque
                    hasWinningPossibilities = true;
            }
            /*
             * si un déplacement propose une case qui elle ne propose aucun mouvement gagnant (apparait dans 
             * de rares cas selon la configuration des cases bannies)
             */
            if (!hasWinningPossibilities)
                //on renvoie ce mouvement qui va piéger le joueur
                return caseToTest->position;
        }
    }
    //sinon on joue aléatoirement
    return IAPlaysRandomly(plate, currPos);
}
//on fait jouer l'IA
Position IA(GamePlate* plate, Position currPos)
{
    switch(plate->level)
    {
        case BEGINNER://si on est en mode débutant
            //on joue aléatoirement
            return IAPlaysRandomly(plate, currPos);
        case MEDIUM://si on est en mode moyen
            //on joue 1/3 gagnant, 2/3 aléatoirement
            return rand()%3 == 0 ? IAPlaysHard(plate, currPos) : IAPlaysRandomly(plate, currPos);
        case EXPERT://si on est en expert
            //on joue 2/3 gagnant, 1/3 aléatoirement
            return rand()%3 <= 1 ? IAPlaysHard(plate, currPos) : IAPlaysRandomly(plate, currPos);
        case VIRTUOSO://si on est en virtuose
            //on joue toujours avec la stratégie gagnante
            return IAPlaysHard(plate, currPos);
        case GODLIKE://si on est en mode divin
            //on joue toujours avec la stratégie gagnante ET en essayant de piéger le joueur
            return IAPlaysVeryHard(plate, currPos);
    }
}
