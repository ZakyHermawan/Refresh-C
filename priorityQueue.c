#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    int priority;
    struct Node* next;
} Node;

Node* insert(Node* node) {
    int data, priority;
    printf("Masukkan data: "); scanf("%d", &data);
    printf("Masukkan priority: "); scanf("%d", &priority);
    Node* new = (Node*) malloc(sizeof(Node));
    new->data = data;
    new->priority = priority;
    new->next = NULL;

    Node* first = node;

    if(node == NULL) {
        return new;
    }

    int awal = 1;
    // utilizing short circuit
    while(node->next != NULL && node->next->priority < priority) {
        awal = 0;
        node = node->next;
    }

    if(awal) {
        if(node->priority < priority) {
            node->next = new;
            return node;
        }
        new->next = node;
        return new;
    }

    if(node->next != NULL) {
        Node* save = node->next;
        node->next = new;
        new->next = save;
        return first;
    }

    node->next = new;
    return first;

    


}

Node* delete(Node* node) {
    if(node == NULL) {
        printf("Queue kosong\n");
        return node;
    }

    Node* ptr = node;
    node = node->next;
    free(ptr);
    return node;
}

Node* erase(Node* node) {
    while(node != NULL) {
        Node* ptr = node->next;
        free(node);
        node = ptr;
    }
}

Node* display(Node* node) {
    Node* first = node;

    while(node != NULL) {
        printf("%d memiliki prioritas: %d \n", node->data, node->priority);
        node = node->next;
    }

    return first;
}

int main() {
    int option;
    Node* pQueue = NULL;
    do {
        printf("\n\nMain Menu\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Masukkan pilihan Anda: "); scanf("%d", &option);

        switch(option) {
            case 1:
                pQueue = insert(pQueue);
                break;

            case 2:
                pQueue = delete(pQueue);
                break;

            case 3:
                pQueue = display(pQueue);
                break;
        }
    } while(option != 4);

    erase(pQueue);


}