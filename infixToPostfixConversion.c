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

int precedence(char c) {
    if(c == '+' || c == '-') return 1;
    else if(c == '*' || c == '/' || c == '%') return 2;
    else return 0;
}

int main() {
    char exp[1000];
    char hasil[1000];
    for(int i=0; i<1000; ++i) hasil[i] = 0;
    printf("Enter an expression: ");
    scanf("%s", exp);
    size_t len = strlen(exp);
    exp[len] = ')';
    exp[len+1] = 0;
    int idx = 0;
    int i_hasil = 0;
    Node* stack = NULL;
    stack = push(stack, '(');

    while(idx != len+1) {
        char now = exp[idx++];
        printf("%s\n", hasil);
        if(now == '(') {
            stack = push(stack, now);
        }
        else if(now == '+' || now == '-' || now == '*' || now == '/' || now == '%') {
            while(1) {
                int now_pres = precedence(now);
                int stack_pres = precedence(stack->data);
                if(stack_pres >= now_pres) {
                    hasil[i_hasil++] = stack->data;
                    stack = pop(stack);
                }
                else {
                    
                    stack = push(stack, now);
                    break;
                }
            }
            
        }
        else if(now == ')') {
            char operator = stack->data;
            while(operator != '(') {
                hasil[i_hasil++] = operator;
                stack = pop(stack);
                operator = stack->data;
            }
            stack = pop(stack);
        }
        else {
            hasil[i_hasil++] = now;
        }
    }
    while(stack != NULL) {
        char now = stack->data;
        if(now == '(') break;
        hasil[i_hasil++] = stack->data;
        stack = pop(stack);
    }
    printf("%s\n", hasil);
}