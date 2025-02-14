#include "shunting_yard.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

// Pile locale pour l'algorithme Shunting-Yard (contient des opérateurs)
typedef struct {
    char data[MAX_STACK_SIZE];
    int top;
} OperatorStack;

static void initOpStack(OperatorStack *s) {
    s->top = -1;
}

static bool pushOp(OperatorStack *s, char c) {
    if (s->top >= MAX_STACK_SIZE - 1) return false;
    s->data[++(s->top)] = c;
    return true;
}

static char popOp(OperatorStack *s, bool *ok) {
    if (s->top < 0) {
        *ok = false;
        return '\0';
    }
    *ok = true;
    return s->data[s->top--];
}

static char peekOp(OperatorStack *s) {
    if (s->top < 0) return '\0';
    return s->data[s->top];
}

static bool isOpStackEmpty(OperatorStack *s) {
    return (s->top < 0);
}

// Renvoie la priorité d’un opérateur
static int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default:  return 0; // cas inconnu
    }
}

// Vérifie si c’est un opérateur reconnu
static bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

bool convertToRPN(const char *infix, char *output, int maxOutputSize) {
    OperatorStack opStack;
    initOpStack(&opStack);

    int outIndex = 0;  // position dans output
    int len = strlen(infix);

    for (int i = 0; i < len; i++) {
        char c = infix[i];

        // Ignorer les espaces
        if (c == ' ') continue;

        // Si c’est un nombre ou une variable (lettre)
        if (isdigit(c) || isalpha(c)) {
            // On l’ajoute directement dans la sortie
            // + un espace pour séparer (optionnel)
            if (outIndex < maxOutputSize - 1) {
                output[outIndex++] = c;
                output[outIndex++] = ' ';
            }
            else {
                return false; // pas assez de place
            }
        }
        else if (c == '(') {
            // Empiler '('
            if (!pushOp(&opStack, c)) return false;
        }
        else if (c == ')') {
            // Dépiler jusqu’à '('
            bool ok = true;
            while (!isOpStackEmpty(&opStack) && peekOp(&opStack) != '(') {
                output[outIndex++] = popOp(&opStack, &ok);
                output[outIndex++] = ' ';
            }
            // Enlever '(' de la pile
            bool ok2;
            popOp(&opStack, &ok2); // supprime '('
        }
        else if (isOperator(c)) {
            // Comparer la priorité avec le sommet de la pile
            bool ok = true;
            while (!isOpStackEmpty(&opStack)) {
                char topOp = peekOp(&opStack);
                // si le sommet est un opérateur + prioritaire, on le dépile
                if (isOperator(topOp) && precedence(topOp) >= precedence(c)) {
                    output[outIndex++] = popOp(&opStack, &ok);
                    output[outIndex++] = ' ';
                } else {
                    break;
                }
            }
            // puis on empile l’opérateur actuel
            if (!pushOp(&opStack, c)) return false;
        }
        else {
            // Caractère inconnu
            // on pourrait gérer ici l'erreur
            return false;
        }
    }

    // A la fin, on vide la pile
    bool ok = true;
    while (!isOpStackEmpty(&opStack)) {
        char topOp = popOp(&opStack, &ok);
        if (topOp == '(') {
            // Parenthèse mal placée
            return false;
        }
        output[outIndex++] = topOp;
        output[outIndex++] = ' ';
    }

    // Terminer la chaîne
    output[outIndex] = '\0';
    return true;
}
