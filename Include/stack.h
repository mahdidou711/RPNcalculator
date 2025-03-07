#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

// Pile dynamique : un tableau de doubles, un indice de sommet, et une capacité.
typedef struct {
    double *data;    // tableau dynamique
    int top;         // sommet (dernier élément)
    int capacity;    // taille allouée
} Stack;

// Initialise la pile avec une capacité initiale
void initStack(Stack *s, int initialCapacity);

// Empile une valeur (agrandit si nécessaire)
bool push(Stack *s, double value);

// Dépile et renvoie la valeur
double pop(Stack *s, bool *ok);

// Vérifie si la pile est vide
bool isEmpty(Stack *s);

// Libère la mémoire allouée
void freeStack(Stack *s);

#endif
