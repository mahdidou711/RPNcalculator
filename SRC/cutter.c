#include "cutter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Fonction qui découpe une expression RPN en tokens.
 */
int tokenize(const char *input, Token tokens[], int maxTokens) {
    char buffer[256];  // Copie locale pour éviter de modifier `input`
    strncpy(buffer, input, 255);
    buffer[255] = '\0';  // Sécurisation

    int tokenCount = 0;
    char *token = strtok(buffer, " ");  // Découpage par espace

    while (token != NULL) {
        if (tokenCount >= maxTokens) {
            printf("Erreur : Trop de tokens\n");
            return -1;
        }

        // Vérification si c'est un nombre
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            tokens[tokenCount].type = T_NUMBER;
            tokens[tokenCount].numberValue = atof(token);
        }
        // Vérification si c'est une variable (ex. "x")
        else if (strlen(token) == 1 && isalpha(token[0])) {
            // On accepte uniquement 'x', 'y', 'z'
            if (token[0] == 'x' || token[0] == 'y' || token[0] == 'z') {
                tokens[tokenCount].type = T_VARIABLE;
                tokens[tokenCount].variableName = token[0];
            } else {
                printf("Erreur : Variable '%c' non reconnue (seules x, y, z)\n", token[0]);
                return -1;
            }
        }
        
        // Vérification si c'est un opérateur (ex. "+", "-", "*", "/")
        else if (strlen(token) == 1 && strchr("+-*/^", token[0])) {
            tokens[tokenCount].type = T_OPERATOR;
            tokens[tokenCount].operatorSymbol = token[0];
        }
        // Vérification si c'est une fonction mathématique (ex. "sin", "cos", "exp")
        else if (strlen(token) < FUNCTION_NAME_SIZE) {
            tokens[tokenCount].type = T_FUNCTION;
            strncpy(tokens[tokenCount].functionName, token, FUNCTION_NAME_SIZE - 1);
            tokens[tokenCount].functionName[FUNCTION_NAME_SIZE - 1] = '\0'; // Sécurisation
        }
        else {
            printf("Erreur : Token inconnu '%s'\n", token);
            return -1;
        }

        tokenCount++;
        token = strtok(NULL, " ");  // Prochain token
    }

    return tokenCount;
}
