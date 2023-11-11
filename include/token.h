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
} tokenizer_t;


// token object
typedef struct token {
    tokenizer_t type;
    const char* lexeme;
    void* literal;
    int line;
} token_t;

#endif