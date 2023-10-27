#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USAGE                                                                                   \
        "NAME\n"                                                                                \
        "   Piton - An interpreted and interactive programming language in Spanish\n"           \
        "\n"                                                                                    \
        "SYNOPSIS\n"                                                                            \
        "   Piton   [-h] \n"                                                                    \
        "           [-f path/to/file] \n"                                                       \
        "\n"                                                                                    \
        "   Where:\n"                                                                           \
        "       [-h]              : help mode (displays this message)\n"                        \
        "       [-f path/to/file] : specifies a source file to interpret from (ext: .pi)\n"     \
        "\n"                                                                                    \
        "DESCRIPTION\n"                                                                         \
        "   Piton mimics CPython functionality but in Spanish.\n"                               \
        "   Functionality is currenty very limited and very basic as CPython functionality is\n"\
        "   grand.\n"                                                                           \

typedef struct {
    int position;
    char token;
} scanner_t;

typedef enum {
    INPUT_NO_CMD,
    INPUT_USAGE,
    INPUT_CONSOLE,
    INPUT_FILE,
} input_command_t;

typedef enum {
    INPUT_NO_ERROR,
    INPUT_BAD_PARAMS,
    INPUT_BAD_PATH,
    INPUT_BAD_FILE,
    INPUT_BAD_OPEN,
    INPUT_BAD_ALLOC,
} input_error_t;

// Handle input errors
void handle_errors(input_error_t err, const char **argv);

// Search for the last occurence of a character in a string
int search_char(char character, const char *string);

// Run file line by line
void run_file(const char *filepath);

// Run console interpreter
void run_prompt(void);

// Scan flag for command and errors
input_command_t scan_flag(const char *flag);

// Assembles the input from command line arguments
void assemble_input(int argc, const char **argv);

#endif