#include <stdio.h>
#include <stdlib.h>
 
typedef struct Node {
    int player_id;
    struct Node* next;
} Node;
 
Node* create(Node* node, int n) {
    Node* first;
    for(int i=1; i<=n; ++i) {
        Node* new = (Node*)malloc(sizeof(Node));
        new->player_id = i;
        new->next = NULL;
        if(i == 1) first = new;
        if(node == NULL) node = new;
        else {
            node->next = new;
            new->next = first;
        }
        node = new;
    }
    return node;
}
 
void display(Node* node) {
    Node* first = node;
    if(node == NULL) return;
    do {
        printf("%d\n", node->player_id);
        node = node->next;
    } while(node != first);
}
 
int main() {
    int n, k;
    printf("Masukkan jumlah pemain: "); scanf("%d", &n);
    printf("Masukkan nilai k: "); scanf("%d", &k);
 
    Node* node = NULL;
    node = create(node, n);
    
    for(int i=0; i<n-1; ++i) {
        for(int j=0; j<k-1; ++j) {
            node = node->next;
        }
        Node* ptr = node->next->next;
        free(node->next);
        node->next = ptr;
    }
    printf("%d\n", node->player_id);
 
    return 0;
}
