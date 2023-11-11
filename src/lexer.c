#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>

static lexer_t *lex = NULL;

// initialize the lexer
void init_lexer(line_t *line) {
    lex = (lexer_t *) malloc(sizeof(lexer_t));
    lex->line = line;
    lex->start = 0;
    lex->current = 0;
    lex->line_index = 1;
}

// frees the space allocated by the init_lexer function above
void destroy_lexer() {
    free(lex);
    lex = NULL;
}

// // Scans through tokens in the line
// const char **scan_tokens();