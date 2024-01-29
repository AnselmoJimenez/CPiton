#pragma once

#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "linkedlist.h"

typedef struct lines {
    char *data;
    size_t length;
} line_t;

typedef struct lexer {
    line_t *line_data;
    node_t *tokens;
    int start;
    int current;
    int line_index;
} lexer_t;

// initialize the lexer
void init_lexer(line_t *line_data);

// frees the space allocated by the init_lexer function above
void destroy_lexer();

// Scans through tokens in the line
node_t* scan_tokens();

void scan();


#endif