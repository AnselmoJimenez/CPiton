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



void assemble_input(int argc, const char **argv);

#endif