#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cutter.h"
#include "eval.h"
#include "shunting_yard.h"  // <-- pour convertToRPN

#define MAX_TOKENS 100
#define MAX_INPUT_SIZE 256

int main(void) {

    while(1) {
        system("cls");  // Efface l'écran (Windows) ; sous Linux/macOS : "clear"

        char input[MAX_INPUT_SIZE];
        Token tokens[MAX_TOKENS];
        double xValue = 0.0;  // Valeur de la variable x

        // (1) Demander le mode d'entrée : infix ou postfix
        printf("Calculatrice RPN\n");
        printf("Choisissez le mode d'entree :\n");
        printf("1. Notation Infixee (ex: (3+4)*2 )\n");
        printf("2. Notation Postfixee (RPN) (ex: 3 4 + 2 *)\n");
        printf("Votre choix (1 ou 2) : ");

        int choix;
        if (scanf("%d", &choix) != 1) {
            // Erreur de saisie
            printf("Erreur de saisie pour le choix.\n");
            getchar(); // consommer le \n
            // On recommence la boucle
            continue;
        }
        getchar(); // consommer le \n restant

        // (2) Lire l'expression
        printf("Entrez votre expression :\n> ");
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            printf("Erreur de lecture.\n");
            // On recommence la boucle
            continue;
        }
        // Supprimer le \n en fin de chaîne
        input[strcspn(input, "\n")] = '\0';

        // (3) Si choix = 1 => Convertir en RPN via Shunting-Yard
        if (choix == 1) {
            char tempOutput[MAX_INPUT_SIZE];
            if (!convertToRPN(input, tempOutput, MAX_INPUT_SIZE)) {
                printf("Erreur lors de la conversion en RPN.\n");
                // On recommence la boucle
                continue;
            }
            printf("Expression convertie en RPN : %s\n", tempOutput);
            // On remplace input par la version postfixée
            strncpy(input, tempOutput, MAX_INPUT_SIZE);
        }

        // (4) Découper l'expression (postfixée) en tokens
        int tokenCount = tokenize(input, tokens, MAX_TOKENS);
        if (tokenCount == -1) {
            printf("Erreur lors de la tokenisation.\n");
            // On recommence la boucle
            continue;
        }

        // (5) Vérifier si l'expression contient la variable 'x'
        int hasVariable = 0;
        for (int i = 0; i < tokenCount; i++) {
            if (tokens[i].type == T_VARIABLE) {
                hasVariable = 1;
                break;
            }
        }

        // (6) Si 'x' est présent, demander un intervalle et générer un fichier
        if (hasVariable) {
            double xMin, xMax, step;
            printf("Entrez l'intervalle pour x (x_min x_max step) : ");
            if (scanf("%lf %lf %lf", &xMin, &xMax, &step) != 3) {
                printf("Erreur de saisie (x_min, x_max, step).\n");
                continue;
            }
            getchar(); // consommer le \n restant

            FILE *file = fopen("result.txt", "w");
            if (file == NULL) {
                printf("Erreur : Impossible de creer le fichier result.txt\n");
                continue;
            }

            // Ecrire un en-tête
            fprintf(file, "x\tf(x)\n");

            // Calculer f(x) pour chaque valeur dans [xMin, xMax]
            for (double xv = xMin; xv <= xMax; xv += step) {
                // On évalue l'expression postfixée avec xValue = xv
                double result = evaluateRPN(tokens, tokenCount, xv);
                fprintf(file, "%.6lf\t%.6lf\n", xv, result);
            }

            fclose(file);
            printf("Les valeurs ont ete enregistrees dans 'result.txt'.\n");
            printf("Utilisez un logiciel de trace (Gnuplot, Python, etc.) pour visualiser.\n");
        } 
        // (7) Sinon, évaluation directe sans variable
        else {
            // On met xValue = 0.0 ou n'importe quelle valeur
            // car l'expression n'utilise pas x
            double result = evaluateRPN(tokens, tokenCount, xValue);
            printf("Resultat : %lf\n", result);
        }

        // (8) Voulez-vous continuer ?
        printf("\nVoulez-vous calculer une nouvelle expression ? (o/n) ");
        char reponse;
        scanf(" %c", &reponse);
        getchar(); // consommer le \n
        if (reponse == 'n' || reponse == 'N') {
            // On sort de la boucle => fin du programme
            break;
        }
    }

    // On arrive ici si on a break
    printf("Fin du programme.\n");
    return 0;
}
