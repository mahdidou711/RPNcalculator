#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cutter.h"
#include "eval.h"

#define MAX_TOKENS 100
#define MAX_INPUT_SIZE 256

int main(void) {
    system("cls");  // Efface l'écran sous Windows (utilise "clear" sous Linux/Mac si tu veux)

    char input[MAX_INPUT_SIZE];
    Token tokens[MAX_TOKENS];
    
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
    int hasVariable = 0;
    for (int i = 0; i < tokenCount; i++) {
        if (tokens[i].type == T_VARIABLE) {
            hasVariable = 1;
            break;
        }
    }

    if (hasVariable) {
        // Demander à l'utilisateur l'intervalle : x_min, x_max et le pas (step)
        double xMin, xMax, step;
        printf("Entrez l'intervalle pour x (x_min x_max step) : ");
        if (scanf("%lf %lf %lf", &xMin, &xMax, &step) != 3) {
            printf("Erreur de saisie (x_min, x_max, step).\n");
            return 1;
        }

        // Ouvrir un fichier pour stocker les valeurs
        FILE *file = fopen("result.txt", "w");
        if (file == NULL) {
            printf("Erreur : Impossible de créer le fichier result.txt\n");
            return 1;
        }

        // Écrire un en-tête dans le fichier
        fprintf(file, "x\tf(x)\n");

        // Calculer f(x) pour chaque x de xMin à xMax
        for (double xValue = xMin; xValue <= xMax; xValue += step) {
            double result = evaluateRPN(tokens, tokenCount, xValue);
            fprintf(file, "%.6lf\t%.6lf\n", xValue, result);
        }

        fclose(file);
        printf("Les valeurs ont ete enregistrees dans 'result.txt'.\n");
        printf("Utilisez un logiciel de trace (ex: Gnuplot, Python, etc.) pour visualiser.\n");

    } else {
        // Si aucune variable 'x' n'est présente, on évalue directement l'expression
        double result = evaluateRPN(tokens, tokenCount, 0.0);
        printf("Resultat : %lf\n", result);
    }

    return 0;
}
