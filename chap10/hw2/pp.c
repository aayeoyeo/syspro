#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node *head, struct node *tail, int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;
    tail->next = new_node;
}

int delete(struct node *head, struct node *tail) {
    struct node *del_node;
    int del_data;

    if (head->next == NULL) {
        return -1;
    }

    del_node = head->next;
    del_data = del_node->data;
    head->next = del_node->next;    
    free(del_node);
    return del_data;
}

int main() {
    struct node *head = (struct node *)malloc(sizeof(struct node));
    head->next = NULL;

    struct node *tail = head; 
    int input;

    while (scanf("%d", &input) == 1) {
        if (input <= 0) break; 
        addq(head, tail, input);        
        tail = tail->next;
    }

    printf("Print queue\n");
    struct node *curr = head->next;
    while (curr != NULL) {
        printf("%d\n", curr->data);
        curr = curr->next;
    }

    return 0;
}
