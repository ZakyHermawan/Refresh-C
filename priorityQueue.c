#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    int priority;
    struct Node* next;
} Node;

// lowest priority in the first node
// if some nodes have the same priority with new node, the new node is on the last of the same priority node
Node* insert(Node* node) {
    int data, priority;
    printf("Masukkan data: "); scanf("%d", &data);
    printf("Masukkan priority: "); scanf("%d", &priority);
    Node* new = (Node*) malloc(sizeof(Node));
    new->data = data;
    new->priority = priority;
    new->next = NULL;

    Node* ptr = node;

    if(node == NULL || node->priority > priority) {
        new->next = node;
        return new;
    }

    while(ptr->next != NULL && ptr->next <= priority) {
        ptr = ptr->next;
    }

    new->next = ptr->next;
    ptr->next = new;
    
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