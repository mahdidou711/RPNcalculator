#include "token.h"
#include <stdio.h>    // pour printf
#include <string.h>   // pour strcpy si nécessaire

void printToken(const Token *tk) {
    switch (tk->type) {
        case T_NUMBER:
            printf("NUMBER(%.6g)\n", tk->numberValue);
            break;
        case T_VARIABLE:
            printf("VARIABLE(%c)\n", tk->variableName);
            break;
        case T_OPERATOR:
            printf("OPERATOR(%c)\n", tk->operatorSymbol);
            break;
        case T_FUNCTION:
            printf("FUNCTION(%s)\n", tk->functionName);
            break;
        default:
            printf("UNKNOWN TOKEN\n");
            break;
    }
}
