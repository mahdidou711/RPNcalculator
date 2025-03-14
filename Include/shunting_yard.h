#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <stdbool.h>

/**
 * Convertit une expression infixée en notation postfixée (RPN) en utilisant l'algorithme du Shunting-Yard.

        * infix         Chaîne représentant l'expression infixée (ex: "(3+4)*2").
        * output        Buffer où sera stockée la notation postfixée résultante.
        * maxOutputSize Taille maximale du buffer output.
        *
        * return true si la conversion a réussi, false en cas d'erreur (ex: parenthèses mal placées, dépassement de capacité, etc.).

 * note L'expression postfixée générée est généralement terminée par un espace et un '\0'.
 */
bool convertToRPN(const char *infix, char *output, int maxOutputSize);

#endif
