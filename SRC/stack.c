#include "stack.h"
#include <stdio.h> 

void initStack(Stack *s) {
    s->top = -1;
}

bool push(Stack *s, double value) {
    if (s->top >= STACK_SIZE - 1) {
        // Pile pleine
        return false;
    }
    s->data[++(s->top)] = value;
    return true;
}

double pop(Stack *s, bool *ok) {
    if (s->top < 0) {
        // Pile vide
        if (ok) *ok = false;
        return 0.0; // Valeur par défaut
    }
    if (ok) *ok = true;
    return s->data[s->top--];
}

bool isEmpty(Stack *s) {
    return (s->top < 0);
}
