#ifndef STACK_H
#define STACK_H

#include <stdbool.h>  

#define STACK_SIZE 100 

typedef struct {
    double data[STACK_SIZE]; // Tableau pour stocker les valeurs
    int top;                 // Indice du sommet de pile
} Stack;


void initStack(Stack *s); //Initialise la pile : top = -1

/*
 Empile une valeur sur la pile.
 Renvoie true si succès, false si la pile est pleine.
*/
bool push(Stack *s, double value);

/*
 * Dépile et renvoie la valeur en sommet de pile.
 * Si la pile est vide, *ok sera mis à false et la fonction renvoie 0.0 (ou toute valeur par défaut).
*/
double pop(Stack *s, bool *ok);

/*
 * Renvoie true si la pile est vide, false sinon.
*/
bool isEmpty(Stack *s);

#endif
