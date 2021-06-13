#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* before;
} Node;

Node* push(Node* node) {
    int data;
    printf("Data yang ini dimasukkan: "); scanf("%d", &data);
    
    Node* new = (Node*)malloc(sizeof(Node));
    new->data = data;
    new->before = node;
    
    return new;
}

Node* peek(Node* node) {
    if(node == NULL) {
        printf("Stack kosong\n\n");
        return node;
    }
    printf("Data paling atas pada stack: %d\n", node->data);
    return node;
}

Node* pop(Node* node) {
    if(node == NULL) {
        printf("Stack kosong\n\n");
        return node;
    }
    Node* ptr = node;
    node = node->before;
    free(ptr);
    printf("Data paling di stack paling atas telah dibuang\n");
    return node;
}

Node* erase(Node* node) {
    if(node == NULL) {
        printf("Stack kosong\n\n");
        return node;
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

Node* display(Node* node) {
    if(node == NULL) {
        printf("Tidak ada data\n");
        return node;
    }
    Node* ptr = node;
    int counter = 1;
    while(node != NULL) {
        printf("%d. %d\n", counter++, node->data);
        node = node->before;
    }
    return ptr;
}

int main() {
    Node* node = NULL;
    int option;
    do {
        printf("Program stack\n");
        printf("0. Display all stack data\n");
        printf("1. Push operation\n");
        printf("2. Peek operation\n");
        printf("3. Pop operation\n");
        printf("4. Delete all data\n");
        printf("5. Keluar\n\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &option);
        switch (option)
        {
        case 0:
            node = display(node);
            break;
        case 1:
            node = push(node);
            break;
        case 2:
            node = peek(node);
            break;
        case 3:
            node = pop(node);
            break;
        case 4:
            node = erase(node);
            break;
        }
    } while(option != 5);

    return 0;
}