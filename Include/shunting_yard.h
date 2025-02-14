#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <stdbool.h>

/*
 * Convertit l’expression infixée "infix" en notation postfixée (RPN).
 * stocke le résultat dans "output", qui doit avoir une taille maxOutputSize.
 * Renvoie true si la conversion a réussi, false en cas d’erreur.
 */
bool convertToRPN(const char *infix, char *output, int maxOutputSize);

#endif
