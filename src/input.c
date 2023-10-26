#include "input.h"

// Run file line by line
void runfile(const char *filepath) {
    // check for valid filepath extension (.pi)
    int last_occurence = -1;
    for (int i = 0; filepath[i] != '\0'; i++) {
        if (filepath[i] == '.') last_occurence = i;
    }

    // invalid file extension handling
    if (last_occurence == -1 || filepath[last_occurence + 1] != 'p' || filepath[last_occurence + 2] != 'i') {
        printf("invalid file");
        return;
    }

    // open file from file path
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        printf("unable to open file '%s'\n", filepath);
        return;
    }

    // Read one line of the file and run the interpreter on that line
    int max_buffer_length = 128;
    char *line_buffer = (char *) malloc(sizeof(char) * max_buffer_length);
    if (line_buffer == NULL) {
        printf("Error allocating memory.\n");
        return;
    }

    // Read character
    char ch = getc(file);
    int count = 0;
    while(ch != '\n' && ch != EOF) {
        // if we surpass the amount of characters in the buffer reallocate more memory to the buffer
        if (count == max_buffer_length) {
            // increase maximum buffer length and reallocate to the line_buffer
            max_buffer_length += max_buffer_length;
            line_buffer = realloc(line_buffer, max_buffer_length);

            // Check if allocation is successful
            if (line_buffer == NULL) {
                printf("Error reallocating memory.\n");
                return;
            }
        }
        // add character to line buffer
        line_buffer[count] = ch;
        count++;

        // Get next character
        ch = getc(file);
    }

    line_buffer[count] = '\0';
    count++;

    char line[count];
    strncpy(line, line_buffer, count);

    free(line_buffer);
    line_buffer = NULL;

    run(line);
}

void runprompt() {
    // buffer to hold all of the characters in each line

    for (;;) {
        printf(">>> ");

    }
}


void assemble_input(int argc, const char **argv) {
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

            // run the interpreter on the file
            printf("running file interpreter\n");
            runfile(argv[2]);
        break;
    }

    return;

exit:
    switch (failure) {
        case 1: 
            fprintf(stderr, "invalid command line option : %s\n", argv[failure]);
        break;
        case 2: 
            fprintf(stderr, "invalid file path\n");
        break;
    }
    
    return;
}
