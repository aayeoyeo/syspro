#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node *top, int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = top->next;
    top->next = new_node;
}

int pop(struct node *top) {
    if (top->next == NULL) {
        return -1;
    }
    struct node *del_node = top->next;
    int pop_data = del_node->data;
    top->next = del_node->next;
    free(del_node);
    return pop_data;
}

int main() {
    struct node *head = (struct node *)malloc(sizeof(struct node));
    head->next = NULL;

    int input;

    while (scanf("%d", &input) == 1) {
        push(head, input);
    }

    printf("Print stack\n");
    struct node *curr = head->next;
    while (curr != NULL) {
        printf("%d\n", curr->data);
        curr = curr->next;
    }
    return 0;
}
