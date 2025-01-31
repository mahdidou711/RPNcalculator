#ifndef CUTTER_H
#define CUTTER_H

#include "token.h"
#include <stdbool.h>

/**
 * Découpe une chaîne d'entrée en tokens.
 *
 * input      Chaîne entrée par l'utilisateur (notation postfixée).
 * tokens     Tableau de tokens à remplir.
 * maxTokens  Taille maximale du tableau de tokens.
 * Nombre de tokens extraits, ou -1 en cas d'erreur.
 */
int tokenize(const char *input, Token tokens[], int maxTokens);

#endif
