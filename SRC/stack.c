#include "stack.h"
#include <stdio.h>
#include <stdlib.h>  // pour malloc, realloc, free

void initStack(Stack *s, int initialCapacity) {
    s->data = malloc(sizeof(double) * initialCapacity);
    if (!s->data) {
        // si l'allocation échoue, on peut gérer l'erreur
        // ex. mettre capacity = 0
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
        int newCapacity = s->capacity * 2;  // par ex. on double
        double *newData = realloc(s->data, sizeof(double) * newCapacity);
        if (!newData) {
            // Échec du realloc
            return false;
        }
        // sinon on met à jour
        s->data = newData;
        s->capacity = newCapacity;
    }
    // Maintenant on a assez de place
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
    // Libère le tableau dynamique
    free(s->data);
    s->data = NULL;
    s->top = -1;
    s->capacity = 0;
}
