#pragma once

#ifndef TOKEN_H
#define TOKEN_H

// tokenizer (token type) object
typedef enum tokenizer {
    // Keywords
    // Single-Character
    LPARENTHESIS,
    RPARENTHESIS,
    COLON,

    // Comments
    HASH,

    // Literals
    IDENTIFIER,
    NUMBER,
    STRING,
    BOOLEAN,

    EOF,
} tokenizer_t;


// token object
typedef struct token {
    tokenizer_t type;
    const char* lexeme;
    void* literal;
    int line;
} token_t;

// Creates a new token object
token_t *new_token(tokenizer_t *type, const char *lexeme, void *literal, int line) {
    token_t *token = (token_t *) malloc(sizeof(token_t *));
    token->type = type
    token->lexeme = lexeme;
    token->literal = literal;
    token->line = line;
}

#endif