#pragma once

#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include "piton.h"

typedef struct lexer {
    line_t *line;
    token_t *tokens;
    int start;
    int current;
    int line_index;
} lexer_t;

// initialize the lexer
void init_lexer(line_t *line);

// frees the space allocated by the init_lexer function above
void destroy_lexer();

// Scans through tokens in the line
const char **scan_tokens();



#endif