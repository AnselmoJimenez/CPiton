#include "lexer.h"

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

// Report errors of unrecognized lexemes
void lexer_error(int line_number, token_t *token, const char *message) {
    fprintf(stderr, "Error: Line %d, %s '%s'", line_number, message, token->lexeme);
    exit(1);
}

// Helper Functions
// Check if we are at the end of the line being scanned
bool at_end()  { return lex->current >= lex->line_data->length; }

// Go forward one character in the line
char advance() { return lex->line_data->data[lex->current++];   }

// Check if the next character matches the character we expect
bool match(char expected) {
    if (at_end()) return false;
    if (lex->line_data->data[lex->current] != expected) return false;

    lex->current++;
    return true;
}

// Lookahead function
char peek() {
    if (at_end()) return '\0';
    else return lex->line_data->data[lex->current];
}

void string(char quote_char_type); // TODO: NEED TO IMPLEMENT

// Scan each character and tokenize it
void scan() {
    // Advance to the next character
    char c = lex->line_data->data[lex->current++];

    // Check the character and assign it a token based on properties
    switch (c) {
    case '#' : while (peek() != '\n' && !at_end()) advance();                     break;
    case ')' : insert(&head, new_token(LPARENTHESIS, &c, NULL, lex->line_index)); break;
    case '(' : insert(&head, new_token(RPARENTHESIS, &c, NULL, lex->line_index)); break;
    case '.' : insert(&head, new_token(DOT, &c, NULL, lex->line_index));          break;
    case '+' : match('=') ? insert(&head, new_token(PLUS_EQUAL, "+=", NULL, lex->line_index))    : insert(&head, new_token(PLUS, &c, NULL, lex->line_index));     break;
    case '-' : match('=') ? insert(&head, new_token(MINUS_EQUAL, "-=", NULL, lex->line_index))   : insert(&head, new_token(MINUS, &c, NULL, lex->line_index));    break;
    case '*' : match('=') ? insert(&head, new_token(MULTIPLY_EQUAL, "*=", NULL, lex->line_index)): insert(&head, new_token(MULTIPLY, &c, NULL, lex->line_index)); break;
    case '/' : match('=') ? insert(&head, new_token(DIVIDE_EQUAL, "/=", NULL, lex->line_index))  : insert(&head, new_token(DIVIDE, &c, NULL, lex->line_index));   break;
    case '%' : match('=') ? insert(&head, new_token(MODULO_EQUAL, "%=", NULL, lex->line_index))  : insert(&head, new_token(MODULO, &c, NULL, lex->line_index));   break;
    case '=' : match('=') ? insert(&head, new_token(EQUAL_EQUAL, "==", NULL, lex->line_index))   : insert(&head, new_token(EQUAL, &c, NULL, lex->line_index));    break;
    case '!' : match('=') ? insert(&head, new_token(BANG_EQUAL, "!=", NULL, lex->line_index))    : insert(&head, new_token(BANG, &c, NULL, lex->line_index));     break;
    case ' ' : 
    case '\t': // FOR NOW
    case '\r': break;
    case '\n': lex->line_index++; break;
    case '\"': // string("\""); break; or multiline comment
    case '\'': string('\''); break;
    default:
        lexer_error(lex->line_index, new_token(ERROR, &c, NULL, lex->line_index), "Invalid Character");
        break;
    }
}

// Scans through tokens in the line
void scan_tokens() {
    while (!at_end()) {
        lex->start = lex->current;
        scan();
    }

    insert(&head, new_token(EOF, "", NULL, lex->line_index));
    print_list(head);
}
