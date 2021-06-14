#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

float eval(char a, char b, char operator) {
    int operand1, operand2;
    operand1 = ((int)a)-48;
    operand2 = ((int)b)-48;

    if(operator == '+') return operand1+operand2;
    else if(operator == '-') return operand1-operand2;
    else if(operator == '/') return operand1/operand2;
    else if(operator == '*') return operand1*operand2;
    
}

int main() {
    char exp[1000];
    printf("Enter a postfix expression: ");
    gets(exp);
    puts(exp);
    exp[strlen(exp)] = ')';
    exp[strlen(exp)+1] = 0;
    Node* stack = NULL;

    float hasil = 0;
    
    int idx = 0;
    while(exp[idx] != ')') {
        char now = exp[idx++];
        if((int)now <= 57 && (int)now >=48) {
            stack = push(stack, now);
        }
        else {
            if(now == ' ') continue;
            // now adalah oeprator
            char a = stack->data;
            stack = pop(stack);
            char b = stack->data;
            stack = pop(stack);
            hasil = eval(b, a, now);
            stack = push(stack, hasil+48);
        }
    }

    printf("%.2f\n", hasil);




    return 0;
}