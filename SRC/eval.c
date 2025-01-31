#include "eval.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

/**
 * Fonction principale d'évaluation RPN.
 */
double evaluateRPN(Token tokens[], int tokenCount, double xValue) {
    Stack s;
    initStack(&s);

    for (int i = 0; i < tokenCount; i++) {
        Token tk = tokens[i];

        switch (tk.type) {
            case T_NUMBER:
                // Si le token est un nombre, on l'empile.
                push(&s, tk.numberValue);
                break;

            case T_VARIABLE:
                // Si le token est une variable 'x', on empile sa valeur actuelle.
                push(&s, xValue);
                break;

            case T_OPERATOR: {
                // Vérification : il faut au moins 2 valeurs pour un opérateur binaire
                bool ok;
                double b = pop(&s, &ok);
                double a = pop(&s, &ok);
                if (!ok) {
                    printf("Erreur : Pile vide avant un opérateur\n");
                    return 0.0;
                }

                double result = 0.0;
                switch (tk.operatorSymbol) {
                    case '+': result = a + b; break;
                    case '-': result = a - b; break;
                    case '*': result = a * b; break;
                    case '/':
                        if (b == 0) {
                            printf("Erreur : Division par zéro\n");
                            return 0.0;
                        }
                        result = a / b;
                        break;
                    case '^': result = pow(a, b); break;
                    default:
                        printf("Erreur : Opérateur inconnu '%c'\n", tk.operatorSymbol);
                        return 0.0;
                }
                push(&s, result);
            } break;

            case T_FUNCTION: {
                // Vérification : il faut au moins 1 valeur pour une fonction
                bool ok;
                double val = pop(&s, &ok);
                if (!ok) {
                    printf("Erreur : Pile vide avant application d'une fonction\n");
                    return 0.0;
                }

                double result = 0.0;
                if (strcmp(tk.functionName, "sin") == 0) {
                    result = sin(val);
                } else if (strcmp(tk.functionName, "cos") == 0) {
                    result = cos(val);
                } else if (strcmp(tk.functionName, "exp") == 0) {
                    result = exp(val);
                } else if (strcmp(tk.functionName, "sqrt") == 0) {
                    if (val < 0.0) {
                        printf("Erreur : Racine carrée d'un nombre négatif\n");
                        return 0.0;
                    }
                    result = sqrt(val);
                } else {
                    printf("Erreur : Fonction inconnue '%s'\n", tk.functionName);
                    return 0.0;
                }
                push(&s, result);
            } break;

            default:
                printf("Erreur : Token non reconnu\n");
                return 0.0;
        }
    }

    // Récupération du résultat final
    bool ok;
    double finalResult = pop(&s, &ok);
    if (!ok || !isEmpty(&s)) {
        printf("Erreur : Expression invalide (pile incorrecte)\n");
        return 0.0;
    }

    return finalResult;
}
