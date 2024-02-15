#include "token.h"

void token_err(const char *lexeme, int line) {
    fprintf(stderr, "Unable to allocate memory for token '%s' on line %d\n.", lexeme, line);

    exit(1);
}

// Creates a new token object
token_t *new_token(tokenizer_t type, const char *lexeme, void *literal, int line) {
    token_t *token = (token_t *) malloc(sizeof(token_t *));
    if (token == NULL) token_err(lexeme, line);

    token->type = type;
    token->lexeme = lexeme;
    token->literal = literal;
    token->line = line;
}