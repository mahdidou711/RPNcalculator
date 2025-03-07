#include "stack.h"
#include <stdio.h>    // pour printf si besoin
#include <stdlib.h>   // pour malloc, realloc, free

void initStack(Stack *s, int initialCapacity) {
    s->data = malloc(sizeof(double) * initialCapacity);
    if (s->data == NULL) {
        // Échec d'allocation => on peut gérer l'erreur
        s->capacity = 0;
    } else {
        s->capacity = initialCapacity;
    }
    s->top = -1;
}

bool push(Stack *s, double value) {
    // Vérifier si la pile est pleine
    if (s->top >= s->capacity - 1) {
        // Agrandir la pile
        int newCap = (s->capacity == 0) ? 1 : s->capacity * 2;
        double *tmp = realloc(s->data, sizeof(double) * newCap);
        if (tmp == NULL) {
            // Échec du realloc
            return false;
        }
        s->data = tmp;
        s->capacity = newCap;
    }
    s->data[++(s->top)] = value;
    return true;
}

double pop(Stack *s, bool *ok) {
    if (s->top < 0) {
        // Pile vide
        if (ok) *ok = false;
        return 0.0;
    }
    if (ok) *ok = true;
    return s->data[s->top--];
}

bool isEmpty(Stack *s) {
    return (s->top < 0);
}

void freeStack(Stack *s) {
    free(s->data);
    s->data = NULL;
    s->capacity = 0;
    s->top = -1;
}
