#pragma once

#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>

// tokenizer (token type) object
typedef enum tokenizer {
    ERROR,

    // Keywords
    LPARENTHESIS,
    RPARENTHESIS,
    COLON,
    PLUS,
    PLUS_EQUAL,
    MINUS,
    MINUS_EQUAL,
    MULTIPLY,
    MULTIPLY_EQUAL,
    DIVIDE,
    DIVIDE_EQUAL,
    DOT,
    MODULO,
    MODULO_EQUAL,

    // Operators
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    LESSTHAN,
    LESSTHAN_EQUAL,
    GREATERTHAN,
    GREATERTHAN_EQUAL,

    // Comment
    HASH,

    // Literals
    IDENTIFIER,
    NUMBER,
    STRING,
    BOOLEAN,
} tokenizer_t;


// token object
typedef struct token {
    tokenizer_t type;
    const char *lexeme;
    void *literal;
    int line;
} token_t;

// Creates a new token object
token_t *new_token(tokenizer_t type, const char *lexeme, void *literal, int line);

#endif