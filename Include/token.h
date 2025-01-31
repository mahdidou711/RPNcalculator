#ifndef TOKEN_H
#define TOKEN_H

// Différents types de token
typedef enum {
    T_NUMBER,    // ex. 3.14
    T_VARIABLE,  // ex. x
    T_OPERATOR,  // +, -, *, /, ^
    T_FUNCTION   // exp, sin, cos, etc.
} TokenType;

#define FUNCTION_NAME_SIZE 20

typedef struct {
    TokenType type;
    double numberValue;            // si T_NUMBER
    char   operatorSymbol;         // si T_OPERATOR
    char   variableName;           // si T_VARIABLE (souvent 'x')
    char   functionName[FUNCTION_NAME_SIZE]; // si T_FUNCTION
} Token;

//Affiche un token (pour débogage)

void printToken(const Token *tk);

#endif
