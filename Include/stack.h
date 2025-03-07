#ifndef STACK_H
#define STACK_H

#include <stdbool.h>


typedef struct {
    double *data;   // tableau dynamique
    int top;        // sommet
    int capacity;   // taille allouée
} Stack;


void initStack(Stack *s, int initialCapacity);


bool push(Stack *s, double value);


double pop(Stack *s, bool *ok);


bool isEmpty(Stack *s);


void freeStack(Stack *s);

#endif
