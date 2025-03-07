#include "eval.h"
#include "stack.h"     // IMPORTANT : pour initStack, push, pop, freeStack
#include <stdio.h>
#include <math.h>
#include <string.h>

double evaluateRPN(Token tokens[], int tokenCount, double xValue) {
    // On initialise la pile avec une capacité initiale de 100 (par exemple).
    Stack s;
    initStack(&s, 100);

    for (int i = 0; i < tokenCount; i++) {
        Token tk = tokens[i];

        switch (tk.type) {
            case T_NUMBER: {
                // Empile la valeur numérique
                // (on pourrait vérifier si push() renvoie false => échec d'alloc)
                if (!push(&s, tk.numberValue)) {
                    printf("Erreur : Echec push (allocation?)\n");
                    freeStack(&s);
                    return 0.0;
                }
            } break;

            case T_VARIABLE: {
                // Empile la valeur de x
                if (!push(&s, xValue)) {
                    printf("Erreur : Echec push (allocation?)\n");
                    freeStack(&s);
                    return 0.0;
                }
            } break;

            case T_OPERATOR: {
                // Vérifier : il faut 2 valeurs dans la pile
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
                // Il faut 1 valeur
                bool ok;
                double val = pop(&s, &ok);
                if (!ok) {
                    printf("Erreur : Pile vide avant application d'une fonction\n");
                    freeStack(&s);
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
                        freeStack(&s);
                        return 0.0;
                    }
                    result = sqrt(val);
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

    // Récupération du résultat final
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
