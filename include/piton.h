#pragma once

#ifndef PITON_H
#define PITON_H

#include <stdio.h>
#include <stdlib.h>


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


typedef enum commands {
    INPUT_NO_CMD,
    INPUT_USAGE,
    INPUT_CONSOLE,
    INPUT_FILE,
} command_t;

typedef struct lines {
    char *data;
    size_t length;
} line_t;

// Execute the current line
void run(line_t *line);

// Handle input errors
void report_err(int line, const char* loc, const char *msg);

// Search for the last occurence of a character in a string
int search_char(char character, const char *string);

// Run file line by line
void run_file(const char *filepath);

// Run console interpreter
void run_prompt(void);

// Scan flag for command and errors
command_t scan_flag(const char *flag);

// Assembles the input from command line arguments
void assemble_input(int argc, const char **argv);

#endif