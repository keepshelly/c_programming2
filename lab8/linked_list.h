#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

struct node* createNode(int data);
void append(struct node** head_ref, int data);
void freeList(struct node* head);
void printList(struct node* node);

#endif