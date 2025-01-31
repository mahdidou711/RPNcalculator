#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cutter.h"
#include "eval.h"

#define MAX_TOKENS 100
#define MAX_INPUT_SIZE 256

int main(void) {
    system("cls");
    char input[MAX_INPUT_SIZE];
    Token tokens[MAX_TOKENS];
    double xValue = 0.0;
    
    printf("Calculatrice RPN\n");
    printf("Entrez une expression en notation postfixee :\n> ");
    
    if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
        printf("Erreur de lecture.\n");
        return 1;
    }
    
    // Supprimer le \n en fin de chaîne
    input[strcspn(input, "\n")] = '\0';

    // Découper l'expression en tokens
    int tokenCount = tokenize(input, tokens, MAX_TOKENS);
    if (tokenCount == -1) {
        printf("Erreur lors de la tokenisation.\n");
        return 1;
    }

    // Vérifier si l'expression contient la variable 'x'
    for (int i = 0; i < tokenCount; i++) {
        if (tokens[i].type == T_VARIABLE) {
            printf("Entrez la valeur de x : ");
            if (scanf("%lf", &xValue) != 1) {
                printf("Erreur de saisie.\n");
                return 1;
            }
            break;
        }
    }

    // Évaluer l'expression
    double result = evaluateRPN(tokens, tokenCount, xValue);

    // Afficher le résultat
    printf("Resultat : %lf\n", result);

    return 0;
}
