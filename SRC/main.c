#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cutter.h"
#include "eval.h"           
#include "shunting_yard.h"  // Pour convertToRPN

#define MAX_TOKENS 100
#define MAX_INPUT_SIZE 256

int main(void) {
    while (1) {
        system("cls"); // Efface l'écran (Windows) ou "clear" sous Linux/macOS

        char input[MAX_INPUT_SIZE];
        Token tokens[MAX_TOKENS];

        // (1) Choix : Infixe ou Postfixe
        printf("Calculatrice RPN (x, y)\n");
        printf("1. Notation Infixee (ex: (x^2 + y^2) )\n");
        printf("2. Notation Postfixee (ex: x 2 ^ y 2 ^ + )\n");
        printf("Votre choix (1 ou 2) : ");

        int choix;
        if (scanf("%d", &choix) != 1) {
            printf("Erreur de saisie.\n");
            getchar();
            continue;
        }
        getchar(); // consomme le \n

        // (2) Lecture de l'expression
        printf("Entrez votre expression :\n> ");
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            printf("Erreur de lecture.\n");
            continue;
        }
        input[strcspn(input, "\n")] = '\0'; // Retire le '\n' final

        // (3) Conversion Infix -> Postfix si choix = 1
        if (choix == 1) {
            char tempOutput[MAX_INPUT_SIZE];
            if (!convertToRPN(input, tempOutput, MAX_INPUT_SIZE)) {
                printf("Erreur : Echec de conversion en RPN.\n");
                continue;
            }
            printf("Expression RPN : %s\n", tempOutput);
            strncpy(input, tempOutput, MAX_INPUT_SIZE);
        }

        // (4) Découpage en tokens
        int tokenCount = tokenize(input, tokens, MAX_TOKENS);
        if (tokenCount == -1) {
            printf("Erreur : Echec de tokenisation.\n");
            continue;
        }

        // (5) Détection de 'x' ou 'y'
        int hasX = 0, hasY = 0;
        for (int i = 0; i < tokenCount; i++) {
            if (tokens[i].type == T_VARIABLE) {
                if (tokens[i].variableName == 'x') hasX = 1;
                if (tokens[i].variableName == 'y') hasY = 1;
            }
        }

        /*
         * (6) Distinction 1D / 2D / pas de variable.
         * - Si x ET y -> on demande x_min, x_max, y_min, y_max, step (2D).
         * - Si x SEULEMENT -> x_min, x_max, step (1D).
         * - Sinon -> evaluation directe (pas de variable).
         */

        if (hasX && !hasY) {
            // CAS 1D : variable x uniquement
            double xMin, xMax, step;
            printf("Entrez x_min, x_max, step : ");
            if (scanf("%lf %lf %lf", &xMin, &xMax, &step) != 3) {
                printf("Erreur de saisie.\n");
                continue;
            }
            getchar();

            FILE *file = fopen("result.txt", "w");
            if (!file) {
                printf("Erreur : Impossible de creer result.txt\n");
                continue;
            }
            fprintf(file, "x\tf(x)\n");

            for (double xv = xMin; xv <= xMax; xv += step) {
                double result = evaluateRPN(tokens, tokenCount, xv, 0.0);
                fprintf(file, "%.6lf\t%.6lf\n", xv, result);
            }
            fclose(file);

            printf("Resultats enregistres dans 'result.txt'.\n");
            // Proposer un tracé 1D (plot 2 colonnes)
            printf("Tracer en 2 colonnes (Gnuplot) ? (o/n) ");
            char rep;
            scanf(" %c", &rep);
            getchar();
            if (rep == 'o' || rep == 'O') {
                system("gnuplot -p -e \"plot 'result.txt' using 1:2 with lines title 'f(x)'\"");
            }

        } else if (hasX && hasY) {
            // CAS 2D : x et y
            double xMin, xMax, yMin, yMax, step;
            printf("Entrez x_min, x_max, y_min, y_max, step : ");
            if (scanf("%lf %lf %lf %lf %lf", &xMin, &xMax, &yMin, &yMax, &step) != 5) {
                printf("Erreur de saisie.\n");
                continue;
            }
            getchar();

            FILE *file = fopen("result.txt", "w");
            if (!file) {
                printf("Erreur : Impossible de creer result.txt\n");
                continue;
            }
            fprintf(file, "x\ty\tf\n");

            for (double xv = xMin; xv <= xMax; xv += step) {
                for (double yv = yMin; yv <= yMax; yv += step) {
                    double result = evaluateRPN(tokens, tokenCount, xv, yv);
                    fprintf(file, "%.6lf\t%.6lf\t%.6lf\n", xv, yv, result);
                }
            }
            fclose(file);
            printf("Resultats enregistres dans 'result.txt'.\n");

            // Tracé 3D via Gnuplot
            printf("Tracer via Gnuplot en 3D ? (o/n) ");
            char rep;
            scanf(" %c", &rep);
            getchar();
            if (rep == 'o' || rep == 'O') {
                system("gnuplot -p -e \"set dgrid3d 30,30; set pm3d; splot 'result.txt' using 1:2:3 with lines title 'f(x,y)'\"");
            }

        } else {
            // Aucune variable : eval direct
            double result = evaluateRPN(tokens, tokenCount, 0.0, 0.0);
            printf("Resultat : %lf\n", result);
        }

        // (7) Recommencer ?
        printf("\nVoulez-vous calculer une nouvelle expression ? (o/n) ");
        char cont;
        scanf(" %c", &cont);
        getchar();
        if (cont == 'n' || cont == 'N') {
            break;
        }
    }

    printf("Fin du programme.\n");
    return 0;
}
