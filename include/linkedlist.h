#pragma once

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "piton.h"
#include "token.h"

typedef struct node {
    token_t *data;
    struct node *next;
    struct node *previous;
} node_t;

// Create a new node
node_t *create_node(token_t *data);

// frees allocated memory for the list
void free_list(node_t *head);

// insert a new node at the end of the list
void insert(node_t **head, token_t *data);

// print the contents of each node in the list
void print_list(node_t *head);

#endif