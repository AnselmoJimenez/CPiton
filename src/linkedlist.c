#include "linkedlist.h"

// Create a new node
node_t *create_node(token_t *data) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t *));
    if (new_node == NULL) printf("Unable to allocate memory"); // report_err(0, NULL, "Memory unable to be allocated for new node");

    new_node->data = data;
    new_node->next = NULL;
    new_node->previous = NULL;

    return new_node;
}

// frees allocated memory for the list
void free_list(node_t *head) {
    node_t *current = head;
    node_t *next;

    // traverse the linked list forward and free each node
    while (current != NULL) {
        next = current->next;
        
        free(current);
        current = next;
    }
}

// insert a new node at the end of the list
void insert(node_t **head, token_t *data) {
    node_t *new_node = create_node(data);

    // if the list is empty, make the new node the head of the list
    if (*head == NULL) *head = new_node;
    else {
        node_t *current = *head;
        while(current->next != NULL) {
            current = current->next;
        }

        // insert the node after the last node
        current->next = new_node;
        new_node->previous = current;
    }
}

// print the contents of each node in the list
void print_list(node_t *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    node_t *current = head;

    // traverse the linked list forward
    printf("[");
    while (current != NULL) {
        if (current->next == NULL) {
            printf("%s]\n", current->data->lexeme);
            break;
        } else {
            printf("%s, ", current->data->lexeme);
            current = current->next;
        }
    }
    printf("\n");
}

// #define DEBUG
#ifdef DEBUG

int main() {
    // initialize an empty doubly linked list
    node_t *head = NULL;

    // create tokens for testing and insert elements
    token_t *token = (token_t *) malloc(sizeof(token_t *));
    token->lexeme = "mostrar";
    insert(&head, token);

    token_t *token1 = (token_t *) malloc(sizeof(token_t *));
    token1->lexeme = "(";
    insert(&head, token1);

    token_t *token2 = (token_t *) malloc(sizeof(token_t *));
    token2->lexeme = "Hola, Mundo";
    insert(&head, token2);

    token_t *token3 = (token_t *) malloc(sizeof(token_t *));
    token3->lexeme = ")";
    insert(&head, token3);

    // print the list
    printf("List: ");
    print_list(head);

    // free memory allocated
    free_list(head);

    return 0;
}

#endif