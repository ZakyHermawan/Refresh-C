#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* rear;
    Node* front;
} Queue;


Queue* insert(Queue* q) {
    int data;
    Node* new = (Node*)malloc(sizeof(Node));
    printf("Masukkan data: "); scanf("%d", &data);
    new->data = data;
    new->next = NULL;

    if(q->front == NULL) {
        q->rear = q->front = new;
    }
    else {
        q->rear->next = new;
        q->rear = new;
    }

    return q;
}

Queue* delete(Queue* q) {
    if(q->front == NULL) {
        printf("Tidak ada data\n");
        return q;
    }
    Node* ptr = q->front;

    q->front = q->front->next;
    free(ptr);
    return q;
}

Queue* display(Queue* q) {
    if(q->front == NULL) {
        printf("Tidak ada data\n");
        return q;
    }

    int counter = 1;
    Node* ptr = q->front;
    while(ptr != q->rear) {
        printf("%d. %d\n", counter++, ptr->data);
        ptr = ptr->next;
    }
    printf("%d. %d\n", counter++, ptr->data);
    return q;

}
int peek(Queue* q) {
    return q->front->data;
}

int main() {
    Queue* q;
    q->rear = q->front = NULL;
    int opt;
    do {
        printf("\n\nMain Menu\n");
        printf("1. insert Queue\n");
        printf("2. Pop Queue\n");
        printf("3. Peek Queue\n");
        printf("4. Display Queue\n");
        printf("5. Exit\n");

        scanf("%d", &opt);
        int temp;
        switch(opt) {
            case 1:
                q = insert(q);
                break;
            case 2:
                q = delete(q);
                break;
            case 3:
                temp = peek(q);
                printf("Data: %d\n", temp);
                break;
            case 4:
                q = display(q);
                break;
        }
    } while(opt != 5);

    return 0;
}