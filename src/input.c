#include "input.h"

static input_error_t error = INPUT_NO_ERROR;

// Handle input errors
// void handle_errors(input_error_t err, const char **argv);

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
    int last_occurence = searchchar('.', filepath);
    if (last_occurence == -1 || filepath[last_occurence + 1] != 'p' || filepath[last_occurence + 2] != 'i') {
        printf("invalid file. Given file is not a .pi file. '%s'\n", filepath);
        return;
    }

    // open file from file path
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        printf("unable to open file '%s'\n", filepath);
        return;
    }

    printf("\n");
    // run interpreter on line
    // run(line);
}

// Run console interpreter
void run_prompt(void) {
    // buffer to hold all of the characters in each line

    for (;;) {
        printf(">>> ");
    
        break;
    }
    printf("\n");
}

// Scan flag for command and errors
input_command_t scan_flag(const char *flag) {
    input_command_t command = INPUT_NO_CMD;
    scanner_t *scanner = (scanner_t *) calloc(1, sizeof(scanner_t));
    scanner->token = flag[scanner->position];

    do {
        scanner->token = flag[scanner->position];

        switch (scanner->token) {
            case '-':   // Check for flag
                if (flag[scanner->position + 1] == '\0') goto exit;
                break;
            case 'h':
                if (flag[scanner->position + 1] != '\0') goto exit;
                command = INPUT_USAGE;
                break;
            case 'f':
                if (flag[scanner->position + 1] != '\0') goto exit;
                command = INPUT_FILE;
                break;
            default: goto exit;
        }

        scanner->position++;

    } while (scanner->token != '\0');

    free(scanner);
    scanner = NULL;

    return command;

exit:
    error = INPUT_BAD_PARAMS;
    return command;
}

// Assembles the input from command line arguments
void assemble_input(int argc, const char **argv) {
    switch (argc) {

    // 0 Flags
    case 1:
        printf("running console interpreter...\n");
        runprompt();
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
            printf("running interpreter\n");
            runfile(argv[2]);
        break;
        case INPUT_NO_CMD:
        case INPUT_USAGE:
        case INPUT_CONSOLE:
        default:
            error = INPUT_BAD_PARAMS;
        break;
        }

    break;
    }

    // Handle Errors
    if (error = INPUT_NO_ERROR) return;


}


int main(int argc, char const **argv) {
    assemble_input(argc, argv);
    
    return 0;
}
