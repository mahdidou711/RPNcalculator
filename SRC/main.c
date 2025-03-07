#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cutter.h"
#include "eval.h"
#include "shunting_yard.h"  // Pour convertToRPN

#define MAX_TOKENS 100
#define MAX_INPUT_SIZE 256

// Pour simplifier, on déclare 3 variables globales
double xVal = 0.0;
double yVal = 0.0;
double zVal = 0.0;

int main(void) {
    while(1) {
        system("cls");  // Efface l'écran (Windows). Sous Linux/macOS : "clear"

        // (1) Demander la valeur de x, y, et z
        printf("Entrez la valeur de x : ");
        scanf("%lf", &xVal);
        getchar(); // consomme le \n

        printf("Entrez la valeur de y : ");
        scanf("%lf", &yVal);
        getchar();

        printf("Entrez la valeur de z : ");
        scanf("%lf", &zVal);
        getchar();

        // (2) Choix infix/postfix
        printf("Calculatrice RPN\n");
        printf("1. Notation Infixee (ex: (3+4)*2)\n");
        printf("2. Notation Postfixee (RPN) (ex: 3 4 + 2 *)\n");
        printf("Votre choix (1 ou 2) : ");
        int choix;
        if (scanf("%d", &choix) != 1) {
            printf("Erreur de saisie.\n");
            getchar();
            continue;
        }
        getchar(); // consomme le \n

        // (3) Lire l'expression
        char input[MAX_INPUT_SIZE];
        printf("Entrez votre expression :\n> ");
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            printf("Erreur de lecture.\n");
            continue;
        }
        // Supprimer le \n en fin de chaîne
        input[strcspn(input, "\n")] = '\0';

        // (4) Convertir en RPN si infix
        if (choix == 1) {
            char tempOutput[MAX_INPUT_SIZE];
            if (!convertToRPN(input, tempOutput, MAX_INPUT_SIZE)) {
                printf("Erreur de conversion en RPN.\n");
                continue;
            }
            printf("Expression convertie en RPN : %s\n", tempOutput);
            strncpy(input, tempOutput, MAX_INPUT_SIZE);
        }

        // (5) Tokenize
        Token tokens[MAX_TOKENS];
        int tokenCount = tokenize(input, tokens, MAX_TOKENS);
        if (tokenCount == -1) {
            printf("Erreur de tokenisation.\n");
            continue;
        }

        // (6) Évaluer en gérant x, y, z
        // On appelle la fonction déclarée dans eval.h et définie dans eval.c
        double result = evaluateRPN_3var(tokens, tokenCount, xVal, yVal, zVal);

        printf("Resultat : %lf\n", result);

        // (7) Voulez-vous continuer ?
        printf("\nVoulez-vous calculer une nouvelle expression ? (o/n) ");
        char rep;
        scanf(" %c", &rep);
        getchar();
        if (rep == 'n' || rep == 'N') {
            break;
        }
    }

    printf("Fin du programme.\n");
    return 0;
}
