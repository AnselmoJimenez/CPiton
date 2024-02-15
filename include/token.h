#pragma once

#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <stdio.h>

// tokenizer (token type) object
typedef enum tokenizer {
    ERROR,

    // One or two character tokens
    LPARENTHESIS, RPARENTHESIS,
    PLUS, PLUS_EQUAL,
    MINUS, MINUS_EQUAL,
    MULTIPLY, MULTIPLY_EQUAL,
    DIVIDE, DIVIDE_EQUAL,
    MODULO, MODULO_EQUAL,
    DOT, COLON,

    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    LESSTHAN, LESSTHAN_EQUAL,
    GREATERTHAN, GREATERTHAN_EQUAL,

    // keywords
    AND, OR,
    IF, ELSE, ELIF,
    NONE,
    FOR, WHILE,
    RETURN,
    DEFINE,
    TRUE, FALSE,

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

// Handles memory allocation errors for tokens
void token_err(const char *lexeme, int line);

// Creates a new token object
token_t *new_token(tokenizer_t type, const char *lexeme, void *literal, int line);

#endif