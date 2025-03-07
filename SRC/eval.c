#include "eval.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

double evaluateRPN_3var(Token tokens[], int tokenCount, 
                        double xVal, double yVal, double zVal) 
{
    // On suppose que Stack s'est défini dans stack.h (pile dynamique).
    // initStack(&s, 100) = par ex. capacité initiale 100.
    Stack s;
    initStack(&s, 100);

    for (int i = 0; i < tokenCount; i++) {
        Token tk = tokens[i];

        switch (tk.type) {
            case T_NUMBER: {
                // On empile directement la valeur numérique
                push(&s, tk.numberValue);
            } break;

            case T_VARIABLE: {
                // On gère x, y, z
                double val = 0.0;
                switch (tk.variableName) {
                    case 'x': val = xVal; break;
                    case 'y': val = yVal; break;
                    case 'z': val = zVal; break;
                    default:
                        printf("Erreur : Variable '%c' inconnue\n", tk.variableName);
                        freeStack(&s);
                        return 0.0;
                }
                push(&s, val);
            } break;

            case T_OPERATOR: {
                bool ok;
                // On dépile 2 valeurs (b, puis a)
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
                push(&s, result);
            } break;

            case T_FUNCTION: {
                // On dépile 1 valeur
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
                push(&s, result);
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
