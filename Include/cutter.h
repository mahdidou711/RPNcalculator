#ifndef CUTTER_H
#define CUTTER_H

#include "token.h"
#include <stdbool.h>

/**
 * Découpe une chaîne de caractères en une liste de tokens.
 *
    * input     Chaîne entrée par l'utilisateur (souvent en notation postfixée).
    * tokens    Tableau de tokens à remplir.
    * maxTokens Taille maximale du tableau tokens.
    *
    * return Le nombre de tokens extraits, ou -1 en cas d'erreur (ex: trop de tokens).
 */
int tokenize(const char *input, Token tokens[], int maxTokens);

#endif
