#include "eval.h"
#include "stack.h"     // Pour initStack, push, pop, freeStack
#include <stdio.h>
#include <math.h>
#include <string.h>

double evaluateRPN(Token tokens[], int tokenCount, double xValue) {
    // Pile dynamique, capacité initiale = 100
    Stack s;
    initStack(&s, 100);

    for (int i = 0; i < tokenCount; i++) {
        Token tk = tokens[i];

        switch (tk.type) {
            case T_NUMBER: {
                // Empiler la valeur numérique
                if (!push(&s, tk.numberValue)) {
                    printf("Erreur : Echec push (allocation?)\n");
                    freeStack(&s);
                    return 0.0;
                }
            } break;

            case T_VARIABLE: {
                // Empiler la valeur de x
                if (!push(&s, xValue)) {
                    printf("Erreur : Echec push (allocation?)\n");
                    freeStack(&s);
                    return 0.0;
                }
            } break;

            case T_OPERATOR: {
                // On doit dépiler 2 valeurs
                bool ok;
                double b = pop(&s, &ok);
                double a = pop(&s, &ok);
                if (!ok) {
                    printf("Erreur : Pile vide avant un opérateur\n");
                    freeStack(&s);
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
                            freeStack(&s);
                            return 0.0;
                        }
                        result = a / b;
                        break;
                    case '^': result = pow(a, b); break;
                    default:
                        printf("Erreur : Opérateur inconnu '%c'\n", tk.operatorSymbol);
                        freeStack(&s);
                        return 0.0;
                }

                if (!push(&s, result)) {
                    printf("Erreur : Echec push (allocation?)\n");
                    freeStack(&s);
                    return 0.0;
                }
            } break;

            case T_FUNCTION: {
                // On doit dépiler 1 valeur
                bool ok;
                double val = pop(&s, &ok);
                if (!ok) {
                    printf("Erreur : Pile vide avant application d'une fonction\n");
                    freeStack(&s);
                    return 0.0;
                }

                double result = 0.0;
                // Ajout de nouvelles fonctions math :
                if (strcmp(tk.functionName, "sin") == 0) {
                    result = sin(val);
                } else if (strcmp(tk.functionName, "cos") == 0) {
                    result = cos(val);
                } else if (strcmp(tk.functionName, "exp") == 0) {
                    result = exp(val);
                } else if (strcmp(tk.functionName, "sqrt") == 0) {
                    if (val < 0.0) {
                        printf("Erreur : Racine carrée d'un nombre négatif\n");
                        freeStack(&s);
                        return 0.0;
                    }
                    result = sqrt(val);
                } else if (strcmp(tk.functionName, "tan") == 0) {
                    result = tan(val);
                } else if (strcmp(tk.functionName, "log") == 0) {
                    result = log(val);     // log base e
                } else if (strcmp(tk.functionName, "log10") == 0) {
                    result = log10(val);   // log base 10
                } else if (strcmp(tk.functionName, "fabs") == 0) {
                    result = fabs(val);
                } else if (strcmp(tk.functionName, "ceil") == 0) {
                    result = ceil(val);
                } else if (strcmp(tk.functionName, "floor") == 0) {
                    result = floor(val);
                } else {
                    printf("Erreur : Fonction inconnue '%s'\n", tk.functionName);
                    freeStack(&s);
                    return 0.0;
                }

                if (!push(&s, result)) {
                    printf("Erreur : Echec push (allocation?)\n");
                    freeStack(&s);
                    return 0.0;
                }
            } break;

            default:
                printf("Erreur : Token non reconnu\n");
                freeStack(&s);
                return 0.0;
        }
    }

    // Récupérer le résultat final
    bool ok;
    double finalResult = pop(&s, &ok);
    if (!ok || !isEmpty(&s)) {
        printf("Erreur : Expression invalide (pile incorrecte)\n");
        freeStack(&s);
        return 0.0;
    }

    freeStack(&s);
    return finalResult;
}
