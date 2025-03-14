#ifndef TOKEN_H
#define TOKEN_H

/**
 * TokenType
    * Définit les différents types de token possibles.
    *
        * T_NUMBER   : représente un nombre (ex: 3.14).
        * T_VARIABLE : représente une variable (ex: x).
        * T_OPERATOR : représente un opérateur (+, -, *, /, ^).
        * T_FUNCTION : représente une fonction mathématique (ex: sin, cos).
 */
typedef enum {
    T_NUMBER,
    T_VARIABLE,
    T_OPERATOR,
    T_FUNCTION
} TokenType;

/** Taille maximale du nom de fonction (ex: "sin", "cos", etc.). */
#define FUNCTION_NAME_SIZE 20

/**
 * Token
 *      Structure décrivant un token (un élément lexical de l'expression).
 *
            * \var type          Type du token (nombre, variable, opérateur ou fonction).
            * \var numberValue   Valeur si c'est un nombre (T_NUMBER).
            * \var operatorSymbol Caractère de l'opérateur (T_OPERATOR).
            * \var variableName   Nom de la variable (souvent 'x' ou 'y').
            * \var functionName   Nom de la fonction (ex: "sin", "exp"), si T_FUNCTION.
 */
typedef struct {
    TokenType type;
    double numberValue;            
    char   operatorSymbol;         
    char   variableName;           
    char   functionName[FUNCTION_NAME_SIZE];
} Token;

/**
 * Affiche un token pour le débogage (type et valeur/symbole).
 *
    *tk Pointeur vers le token à afficher.
 */
void printToken(const Token *tk);

#endif
