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

// Run file line by line
void runfile(const char *filepath) {
    // open the file for reading and check if reading was successful
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Error opening given file...");
        return;
    }

    // buffer to hold the characters of each line
    char *buffer = NULL;
    size_t buffer_size = 0;
    size_t line_length = 0;

    // Read contents of the file line by line
    while((line_length = getLine(&buffer, &buffer_size, file)) != -1) run(buffer); // TODO: run function

    // free dynamically allocated buffer
    free(buffer);
    buffer = NULL;

    // Close the file
    fclose(file);
}

void runprompt() {
    // buffer to hold all of the characters in each line
    char *buffer = NULL;
    size_t buffer_size = 0;

    for (;;) {
        printf(">>> ");

        // Dynamically allocate memory for the input buffer
        size_t characters_read = getLine(&buffer, &buffer_size, stdin);
        if (characters_read == -1) {
            free(buffer);
            buffer = NULL;
            break;
        }
        run(buffer);

        free(buffer);
        buffer = NULL;
    }
}

// Returns the position of the last occurence of a character
int searchchar(const char *str, char ch) {
    int last_occurence = -1;

    for (int i = 0; str[i] != '\0'; i++) 
        if (str[i] == ch) 
            last_occurence = i;

    return last_occurence;
}

int main(int argc, const char **argv) {
    int failure = 0;

    switch (argc) {
        case 1: // no flags
            printf("initiating console interpreter...");
            runprompt();
        break;

        case 2: // 1 flag
            failure = 1;

            // Scan command line option
            for (int i = 0; argv[1][i] != '\0'; i++) {
                // check if the first character is a flag
                if (i == 0 && argv[1][i] != '-') goto exit;

                // check for flag character
                switch (argv[1][i]) {
                    case 'h': // USAGE message
                        if (argv[1][i + 1] == '\0') printf("%s\n", USAGE);
                        else goto exit;
                    break;
                    case 'f': goto exit; // no file associated
                }
            }
        break;

        case 3: // flag and file path
            failure = 1;
            
            // check for valid flag
            for (int i = 0; argv[1][i] != '\0'; i++) {
                // check if the first character is a flag
                if (i == 0 && argv[1][i] != '-') goto exit;

                // check for flag character
                if (argv[1][i] == 'f' && argv[1][i + 1] == '\0') break;
                else goto exit;
            }

            failure = 2;

            // scan file for valid file extension
            int last_period = searchchar(argv[2], '.');

            if (last_period == -1)                  goto exit;
            if (argv[2][last_period + 1] != 'p')    goto exit;
            if (argv[2][last_period + 2] != 'i')    goto exit;

            // run the interpreter on the file
            printf("running file interpreter\n");
            runfile(argv[2]);
        break;
    }

    return 0;

exit:
    switch (failure) {
        case 1: 
            fprintf(stderr, "invalid command line option : %s\n", argv[failure]);
        break;
        case 2: 
            fprintf(stderr, "invalid file path\n");
        break;
    }
    
    return 0;
}
