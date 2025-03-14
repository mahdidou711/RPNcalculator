#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

/**
 * Stack
 *      Représente une pile dynamique de nombres (type double).
            * data Pointeur vers le tableau dynamique contenant les éléments.
            * top Indice du sommet de la pile (dernier élément).
            * capacity Taille allouée (nombre maximal d'éléments stockables).
 */
typedef struct {
    double *data;
    int top;
    int capacity;
} Stack;

/**
 * Initialise la pile avec une capacité initiale.
        *s Pile à initialiser.
        *initialCapacity Capacité de départ (ex: 100).
 */
void initStack(Stack *s, int initialCapacity);

/**
 *Empile une valeur (agrandit la pile si nécessaire).
        *s Pile sur laquelle empiler.
        *value Valeur à empiler.
        * return true si l'empilement a réussi, false en cas d'échec d'allocation.
 */
bool push(Stack *s, double value);

/**
 *Dépile et renvoie la valeur au sommet de la pile.
        *s Pile à dépiler.
        *ok Indicateur de succès (false si la pile est vide).
        *return La valeur dépilée, ou 0.0 si la pile était vide (ok=false).
 */
double pop(Stack *s, bool *ok);

/**
 *Vérifie si la pile est vide.
        *s Pile à examiner.
        * return true si la pile est vide, false sinon.
 */
bool isEmpty(Stack *s);

/**
 *Libère la mémoire allouée pour la pile.
        *s Pile à libérer.
 */
void freeStack(Stack *s);

#endif
