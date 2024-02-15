#include "piton.h"

// Execute the current line 
void run(line_t *line) {
    // printf("%s\n", line->data);
    init_lexer(line);
}

// Handle input errors
void report_err(const char *loc, const char *msg) {
    if (loc != NULL)    fprintf(stderr, "Error: %s '%s'\n", msg, loc);
    else                fprintf(stderr, "Error: %s\n", msg);

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
    if (last_occurence == -1 || filepath[last_occurence + 1] != 'p' || filepath[last_occurence + 2] != 'i') report_err(filepath, "Cannot read file");

    // open file from file path
    FILE *file = fopen(filepath, "r");
    if (file == NULL) report_err(filepath, "Unable to open file");

    // Read line
    line_t *line = (line_t *) malloc(sizeof(line_t *));
    if (line == NULL) report_err(NULL, "Unable to allocate memory");
    char ch = 0;
    line->length = 0;
    
    while ((ch = fgetc(file)) != EOF) {
        // Check for the beginning of line and allocate memory
        if (line->length == 0)  line->data = (char *) malloc(1);
        else                    line->data = (char *) realloc(line->data, line->length + 1);

        // check if memory allocation was successful
        if (line->data == NULL) report_err(NULL, "Unable to allocate memory");

        // set current index at line_length to character read, then incremenet line_length
        line->data[line->length++] = ch;

        if (ch == '\n') {
            line->data[line->length] = '\0';

            // run this line
            run(line);

            // reset counters
            line->length = 0;
            free(line->data);
            line->data = NULL;
        }
    }

    // process the last line of the file
    if (line->length > 0) {
        line->data[line->length] = '\0';

        // run the last line
        run(line);

        free(line);
        line = NULL;
    }

    fclose(file);
}

// Run console interpreter
void run_prompt(void) {
    for (;;) {
        printf(">>> ");

        line_t *line = (line_t *) malloc(sizeof(line_t *));
        if (line == NULL) report_err(NULL, "Unable to allocate memory");
        char ch = 0;
        line->length = 0;
        
        while ((ch = getchar()) != '\n') {
            // Allocate memory for each new character encountered
            if (line->length == 0)  line->data = (char *) malloc(sizeof(char));
            else                    line->data = (char *) realloc(line->data, line->length + 1);

            // Check for successful memory allocation
            if (line->data == NULL) report_err(NULL, "Unable to allocate memory");

            // set index at line_length to ch, then increment
            line->data[line->length++] = ch;
        }

        // If there is a line...
        if (line->length > 0) {
            // End of the line
            line->data[line->length] = '\0';

            // Run this line
            run(line);

            free(line);
            line = NULL;
        }
    }
}

// Scan flag for command and errors
command_t scan_flag(const char *flag) {
    command_t command = INPUT_NO_CMD;
    int position = 0;
    char token = flag[position];
    
    do {
        // check token for validity
        switch (token) {
            case '-': break;
            case 'h': // Usage command
                if (flag[position + 1] != '\0') goto exit;
                if (position != 1)              goto exit;
                command = INPUT_USAGE;
                break;
            case 'f': // File command
                if (flag[position + 1] != '\0') goto exit;
                if (position != 1)              goto exit;
                command = INPUT_FILE;
                break;
            default: goto exit;
        }

        // go to next token
        position++;
        token = flag[position];
    } while (token != '\0');
    
    return command;

exit:
    report_err(flag, "Invalid flag");
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
            report_err(argv[1], "Invalid flag");
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
            printf("running interpreter...\n\n");
            run_file(argv[2]);
            break;
        case INPUT_NO_CMD:
        case INPUT_USAGE:
        case INPUT_CONSOLE:
        default:
            report_err(argv[1], "Invalid flag");
            break;
        }

    break;
    }
}


int main(int argc, char const **argv) {
    assemble_input(argc, argv);
    
    return 0;
}
