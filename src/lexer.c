#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>

static lexer_t *lex = NULL;
static node_t *head = NULL;

// initialize the lexer
void init_lexer(line_t *line_data) {
    lex = (lexer_t *) malloc(sizeof(lexer_t *));
    lex->line_data = line_data;
    lex->start = 0;
    lex->current = 0;
    lex->line_index = 1;
}

// frees the space allocated by the init_lexer function above
void destroy_lexer() {
    free(lex);
    lex = NULL;
}

void scan() {
    char c = lex->line_data->data[lex->current++];
    switch (c) {
    case ')':
        insert(&head, new_token(LPARENTHESIS, c, NULL, lex->line_index));
        break;
    
    default:
        break;
    }

}

// Scans through tokens in the line
void scan_tokens() {
    while (lex->current <= lex->line_data->length) {
        lex->start = lex->current;
        scan();
    }

    insert(&head, new_token(EOF, "", NULL, lex->line_index));
}
