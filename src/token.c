#include "token.h"

// Creates a new token object
token_t *new_token(tokenizer_t type, const char *lexeme, void *literal, int line) {
    token_t *token = (token_t *) malloc(sizeof(token_t *));
    token->type = type;
    token->lexeme = lexeme;
    token->literal = literal;
    token->line = line;
}