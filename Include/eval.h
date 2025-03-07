#ifndef EVAL_H
#define EVAL_H

#include "token.h"
#include "stack.h"
#include <stdbool.h>

/**
 * Évalue une expression en notation postfixée (RPN).
 * 
 * tokens[]    Tableau de tokens à analyser.
 * tokenCount Nombre total de tokens.
 * xValue    Valeur de la variable `x` (si présente dans l'expression).
 */
double evaluateRPN(Token tokens[], int tokenCount, double xValue);
double evaluateRPN_3var(Token tokens[], int tokenCount,
    double xValue, double yValue, double zValue);


#endif
