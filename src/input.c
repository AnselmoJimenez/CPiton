#include "input.h"

// Handle input errors
void err(enum input_errors err, const char *information) {
    switch (err) {
        case INPUT_NO_ERROR: break;
        case INPUT_BAD_PARAMS:
            fprintf(stderr, "Invalid Parameters: %s\n", information);
            break;
        case INPUT_BAD_PATH:
            fprintf(stderr, "Invalid file path: %s\n", information);
            break;
        case INPUT_BAD_FILE:
            fprintf(stderr, "Invalid file. please check file \"%s\"\n", information);
            break;
        case INPUT_BAD_OPEN:
            fprintf(stderr, "Unable to open file \"%s\". Please check permissions.", information);
            break;
        case INPUT_BAD_ALLOC:
            fprintf(stderr, "Failure allocating memory.\n");
            break;
    }
    printf("\n");


    exit(1);
}

// search for the last occurence of a character in a string
int search_char(char character, const char *string) {
    int last_occurence = -1;
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == character) last_occurence = i;
    }
    return last_occurence;
}

// Run file line by line
void run_file(const char *filepath) {
    // check for valid filepath extension (.pi)
    int last_occurence = search_char('.', filepath);
    if (last_occurence == -1 || filepath[last_occurence + 1] != 'p' || filepath[last_occurence + 2] != 'i') err(INPUT_BAD_PATH, filepath);

    // open file from file path
    FILE *file = fopen(filepath, "r");
    if (file == NULL) err(INPUT_BAD_OPEN, filepath);

    // Read line
    char *line = NULL;
    char ch = 0;
    size_t line_length = 0;
    while ((ch = fgetc(file)) != EOF) {
        // Check for the beginning of line and allocate memory
        if (line_length == 0) line = (char *) malloc(1);
        else line = (char *) realloc(line, line_length + 1);

        // check if memory allocation was successful
        if (line == NULL) err(INPUT_BAD_ALLOC, NULL);

        // set current index at line_length to character read, then incremenet line_length
        line[line_length++] = ch;

        if (ch == '\n') {
            line[line_length] = '\0';

            // run this line
            // run(line);
            printf("%s", line);

            // reset counters
            line_length = 0;
            free(line);
            line = NULL;
        }
    }

    // process the last line of the file
    if (line_length > 0) {
        line[line_length] = '\0';

        // run the last line
        // run(line);
        printf("%s", line);

        free(line);
        line = NULL;
    }

    fclose(file);
}

// Run console interpreter
void run_prompt(void) {
    for (;;) {
        printf(">>> ");

        char *line = NULL;
        char ch = 0;
        size_t line_length = 0;
        
        while ((ch = getchar()) != '\n') {
            // Allocate memory for each new character encountered
            if (line_length == 0) line = (char *) malloc(sizeof(char));
            else line = (char *) realloc(line, line_length + 1);

            // Check for successful memory allocation
            if (line == NULL) err(INPUT_BAD_ALLOC, NULL);

            // set index at line_length to ch, then increment
            line[line_length++] = ch;
        }

        // If there is a line...
        if (line_length > 0) {
            // End of the line
            line[line_length] = '\0';

            // Run this line
            printf("%s\n", line);

            free(line);
            line = NULL;
        }
    }
}

// Scan flag for command and errors
input_command_t scan_flag(const char *flag) {
    input_command_t command = INPUT_NO_CMD;
    scanner_t *scanner = (scanner_t *) calloc(1, sizeof(scanner_t));
    scanner->token = flag[scanner->position];

    do {
        // check token for validity
        switch (scanner->token) {
            case '-': break;
            case 'h': // Usage command
                if (flag[scanner->position + 1] != '\0') goto exit;
                command = INPUT_USAGE;
                break;
            case 'f': // File command
                if (flag[scanner->position + 1] != '\0') goto exit;
                command = INPUT_FILE;
                break;
            default: goto exit;
        }

        // go to next token
        scanner->position++;
        scanner->token = flag[scanner->position];
    } while (scanner->token != '\0');
    
    // free memory
    free(scanner);
    scanner = NULL;

    return command;

exit:
    err(INPUT_BAD_PARAMS, flag);
    return command;
}

// Assembles the input from command line arguments
void assemble_input(int argc, const char **argv) {
    switch (argc) {

    // 0 Flags
    case 1:
        printf("running console interpreter...\n");
        run_prompt();
    break;

    // 1 Flag
    case 2:
        switch (scan_flag(argv[1])) {
        case INPUT_USAGE: 
            printf("%s\n", USAGE);
            break;
        case INPUT_FILE:
            printf("Please provide a file.\n");
            break;
        case INPUT_NO_CMD:
            err(INPUT_BAD_PARAMS, argv[1]);
            break;
        case INPUT_CONSOLE:
        default: break;
        }
    break;

    // 2 Flags (flag and filepath)
    case 3:
        // check for valid flag
        switch (scan_flag(argv[1])) {
        case INPUT_FILE:
            // run the interpreter on the file
            printf("running interpreter...\n");
            run_file(argv[2]);
            break;
        case INPUT_NO_CMD:
        case INPUT_USAGE:
        case INPUT_CONSOLE:
        default:
            err(INPUT_BAD_PARAMS, argv[1]);
            break;
        }

    break;
    }
}


int main(int argc, char const **argv) {
    assemble_input(argc, argv);
    
    return 0;
}
