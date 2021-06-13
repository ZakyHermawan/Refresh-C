#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* before;
} Node;

Node* push(Node* node, char data) {
    Node* new = (Node*)malloc(sizeof(Node));
    new->data = data;
    new->before = node;
    
    return new;
}

Node* pop(Node* node) {
    if(node == NULL) {
        return node;
    }
    Node* ptr = node;
    node = node->before;
    free(ptr);
    return node;
}

Node* erase(Node* node) {
    if(node == NULL) {
        return NULL;
    }
    while(node->before != NULL) {
        Node* ptr = node;
        node = node->before;
        free(ptr);
    }

    free(node);
    node = NULL;
    return node;
}

int main() {
    printf("Welcome to parenthesis checker!\n\nenter an expression: ");
    char expression[1000];
    scanf("%s", expression);

    int idx = 0;
    int len = (int)strlen(expression);

    Node* stack = NULL;
    int valid = 1;
    
    while(valid && idx != len) {
        char now = expression[idx];
        if(now == '{' || now == '(') {
            stack = push(stack, now);
        }
        else {
            if(stack == NULL) {
                valid = 0;
                continue;
            }
            if(now == '}') {
                if(stack->data == '{') stack = pop(stack);
                else valid = 0;
            }
            else if(now == ')') {
                if(stack->data == '(') stack = pop(stack);
                else valid = 0;
            }
        }
        ++idx;
    }

    if(valid && stack==NULL) {
        printf("Expression valid\n");
    }
    else {
        if(stack != NULL) {
            stack = erase(stack);
        }
        printf("Expression invalid\n");
    }

    return 0;
}