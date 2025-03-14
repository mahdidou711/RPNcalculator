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
        system("cls"); // Efface l'écran sous Windows (ou "clear" sous Linux/macOS).

        char input[MAX_INPUT_SIZE];
        Token tokens[MAX_TOKENS];

        // (1) Choix infix ou postfix
        printf("Calculatrice RPN (x, y)\n");
        printf("1. Notation Infixee (ex: (x^2 + y^2) )\n");
        printf("2. Notation Postfixee (RPN) (ex: x 2 ^ y 2 ^ + )\n");
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
        // Retirer \n final
        input[strcspn(input, "\n")] = '\0';

        // (3) Conversion infix -> postfix si choix = 1
        if (choix == 1) {
            char tempOutput[MAX_INPUT_SIZE];
            if (!convertToRPN(input, tempOutput, MAX_INPUT_SIZE)) {
                printf("Erreur : Echec de conversion en RPN.\n");
                continue;
            }
            printf("Expression convertie en RPN : %s\n", tempOutput);
            strncpy(input, tempOutput, MAX_INPUT_SIZE);
        }

        // (4) Tokenisation
        int tokenCount = tokenize(input, tokens, MAX_TOKENS);
        if (tokenCount == -1) {
            printf("Erreur : Echec de tokenisation.\n");
            continue;
        }

        // (5) Détecter si l'expression contient x ou y
        int hasX = 0, hasY = 0;
        for (int i = 0; i < tokenCount; i++) {
            if (tokens[i].type == T_VARIABLE) {
                if (tokens[i].variableName == 'x') hasX = 1;
                if (tokens[i].variableName == 'y') hasY = 1;
            }
        }

        // (6) Si x ou y est présent, on demande un intervalle
        if (hasX || hasY) {
            // On propose un intervalle en 2D : x_min, x_max, y_min, y_max, step
            double xMin, xMax, yMin, yMax, step;
            printf("Entrez x_min, x_max, y_min, y_max, step : ");
            if (scanf("%lf %lf %lf %lf %lf", &xMin, &xMax, &yMin, &yMax, &step) != 5) {
                printf("Erreur de saisie.\n");
                continue;
            }
            getchar(); // consomme \n

            FILE *file = fopen("result.txt", "w");
            if (!file) {
                printf("Erreur : Impossible de creer result.txt\n");
                continue;
            }

            // On écrit un en-tête
            fprintf(file, "x\ty\tf\n");

            // (7) Double boucle pour x et y
            for (double xv = xMin; xv <= xMax; xv += step) {
                for (double yv = yMin; yv <= yMax; yv += step) {
                    // On évalue l'expression postfixée
                    // Suppose que evaluateRPN(...) existe
                    double result = evaluateRPN(tokens, tokenCount, xv, yv);
                    fprintf(file, "%.6lf\t%.6lf\t%.6lf\n", xv, yv, result);
                }
            }
            fclose(file);

            printf("Resultats enregistres dans 'result.txt'.\n");

            // Proposer le tracé via Gnuplot (surface 3D)
            printf("Tracer via Gnuplot en 3D ? (o/n) ");
            char rep;
            scanf(" %c", &rep);
            getchar();
            if (rep == 'o' || rep == 'O') {
                // Commande Gnuplot pour un splot 3D
                // set dgrid3d 30,30 -> interpolation
                // set pm3d -> palette
                // splot 'result.txt' using 1:2:3 with lines
                system("gnuplot -p -e \"set dgrid3d 30,30; set pm3d; splot 'result.txt' using 1:2:3 with lines title 'f(x,y)'\"");
            }

        } else {
            // (8) Si ni x ni y, on fait un calcul direct
            // Ex. expression RPN pour 3 4 + ...
            // On peut appeller evaluateRPN(...) avec x=0, y=0
            double result = evaluateRPN(tokens, tokenCount, 0.0, 0.0);
            printf("Resultat : %lf\n", result);
        }

        // (9) Recommencer ?
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
