#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct ParentChildNode {
    Node* parent;
    Node* child;
} ParentChildNode;


ParentChildNode* getLargestNode(Node* node) {
    Node* parent = node;
    Node* child = node->right;
    
    while(node->right->right != NULL) {
        parent = parent->right;
        child = child->right;
        node = node->right;
    }
    ParentChildNode *parentChild = malloc(sizeof(ParentChildNode));
    parentChild->parent = parent;
    parentChild->child = child;
    return parentChild;
}

Node* insert_element(Node* node, int val) {
    Node* new = (Node*)malloc(sizeof(Node));
    new->data = val;
    new->left = NULL;
    new->right = NULL;
    if(node == NULL) {
        node = new;
    }
    else {
        Node* prev = NULL;
        Node* ptr = node;
        while(ptr != NULL) {
            prev = ptr;
            if(val < ptr->data) {
                ptr = ptr->left;
            }
            else {
                ptr = ptr->right;
            }
        }

        if(val < prev->data) {
            prev->left = new;
        }
        else {
            prev->right = new;
        }
    }
    return node;
}

void preorder(Node* tree) {
    if(tree) {
        printf("%d ", tree->data);
        preorder(tree->left);
        preorder(tree->right);
    }
}

void inorder(Node* tree) {
    if(tree) {
        inorder(tree->left);
        printf("%d ", tree->data);
        inorder(tree->right);
    }
}

void postorder(Node* tree) {
    if(tree) {
        postorder(tree->left);
        postorder(tree->right);
        printf("%d ", tree->data);
    }
}

Node* insert(Node* node) {
    int val;
    printf("Masukkan nilai Node: "); scanf("%d", &val);
    if(node == NULL) {
        return insert_element(node, val);
    }
    Node* tmp = node;
    insert_element(node, val);
    return tmp;
}

Node* findMin(Node* node) {
    if(node == NULL) {
        printf("The tree has no node\n");
        return node;
    }

    Node* tmp = node;
    int min_val;
    while(tmp) {
        min_val = tmp->data;
        tmp = tmp->left;
    }

    printf("Element terkecil adalah: %d\n", min_val);
    return node;
}

Node* findMax(Node* node) {
    if(node == NULL) {
        printf("The tree has no node\n");
        return node;
    }

    Node* tmp = node;
    int max_val;
    while(tmp) {
        max_val = tmp->data;
        tmp = tmp->right;
    }

    printf("Element terbesar adalah: %d\n", max_val);

    return node;
}

Node* delete_node(Node* node) {
    int val; 
    printf("Masukkan nilai node yang akan dihapus: ");
    scanf("%d", &val);

    if(node == NULL) {
        printf("The tree has no node\n");
        return node;
    }

    Node* tmp = node;
    Node* parent;

    if(tmp->data == val) {
        if(tmp->left == NULL && tmp->right == NULL) {
            free(tmp);
            node = NULL;
            return node;
        }

        if(tmp->left == NULL && tmp->right != NULL) {
            node = node->right;
            free(tmp);
            return node;
        }
        if(tmp->right == NULL && tmp->left != NULL) {
            node = node->left;
            free(tmp);
            return node;
        }

        ParentChildNode* largest = getLargestNode(tmp->left);
        tmp->data = largest->child->data;
        free(largest->child);
        free(largest);

        return node;
    }

    while(tmp->data != val) {
        parent = tmp;
        if(val < tmp->data) {
            tmp = tmp->left;
        }
        else {
            tmp = tmp->right;
        }

        if(tmp == NULL) {
            printf("There is no node with value: %d\n", val);
            return node;
        }
    }

    // leaf node
    if(tmp->left == NULL && tmp->right == NULL) {
        if(parent->left == tmp) {
            free(tmp);
            parent->left = NULL;
        }
        else {
            free(tmp);
            parent->right = NULL;
        }
        return node;
    }

    if(tmp->left == NULL && tmp->right != NULL) {
        if(parent->left == tmp) {
            parent->left = parent->left->right;
            free(tmp);
        }
        else {
            parent->right = parent->right->right;
            free(tmp);
        }
        return node;
    }

    if(tmp->left != NULL && tmp->right == NULL) {
        if(parent->left == tmp) {
            parent->left = parent->left->left;
            free(tmp);
        }
        else {
            parent->right = parent->right->left;
            free(tmp);
        }
        return node;
    }

    // find largest value on the left subtree (largest always on rightmost leaf)
    ParentChildNode* largest = getLargestNode(tmp->left);
    if(parent->left == tmp) {
        parent->left->data = largest->child->data;
    }
    else {
        parent->right->data = largest->child->data;
    }

    free(largest->child);
    free(largest);
    return node;
}

int countNode(Node* node) {
    if(node == NULL) {
        return 0;
    }
    return countNode(node->left) + countNode(node->right) + 1;
}

int countInternal(Node* node) {
    if(node == NULL || (node->left == NULL & node->right == NULL)) {
        return 0;
    }
    return (countInternal(node->left) + countInternal(node->right) + 1);
}

int countEksternal(Node* node) {
    if(node == NULL) {
        return 1;
    }
    if(node->left == NULL && node->right == NULL) {
        return 1;
    }
    int left = 0;
    int right = 0;
    if(node->left != NULL) {
        left = countEksternal(node->left);
    }
    if(node->right != NULL) {
        right = countEksternal(node->right);
    }
    return left + right;
}

int countHeight(Node* node) {
    if(node == NULL) {
        return 0;
    }
    int left = countHeight(node->left);
    int right = countHeight(node->right);
    return (left <= right) ? right+1 : left+1;
}

Node* convertMirror(Node* node) {
    if(node == NULL) {
        return 0;
    }
    convertMirror(node->left);
    convertMirror(node->right);
    Node* tmp;
    tmp = node->left;
    node->left = node->right;
    node->right = tmp;

    return node;
}

Node* deleteTree(Node* node) {
    if(node == NULL) {
        return 0;
    }

    deleteTree(node->left);
    deleteTree(node->right);
    node->left = NULL;
    node->right = NULL;
    free(node);
    node = NULL;
    return node;
}

void jumlahNode(Node* node) {
    int jumlah = countNode(node);
    printf("Jumlah node: %d", jumlah);
}

void jumlahIntenal(Node* node) {
    int jumlah = countInternal(node);
    printf("Jumlah node internal: %d", jumlah);
}

void jumlahEksternal(Node* node) {
    int jumlah = countEksternal(node);
    printf("Jumlah node eksternal: %d", jumlah);
}

void tinggiTree(Node* node) {
    int tinggi = countHeight(node);
    printf("Tinggi dari tree adalah: %d", tinggi);
}

Node* ubahMirror(Node* node) {
    node = convertMirror(node);
    printf("Tree berhasil diubah ke mirror nya");
    return node;
}

Node* hapusTree(Node* node) {
    node = deleteTree(node);
    printf("Tree berhasil dihapus");
    return node;
}

int main() {
    Node* tree = NULL;
    int option;
    do {
        printf("\nMain menu\n\n");
        printf("1. Insert Element\n");
        printf("2. Preorder Traversal\n");
        printf("3. Inorder Traversal\n");
        printf("4. Postorder Traversal\n");
        printf("5. Find the smallest element\n");
        printf("6. Find the largest element\n");
        printf("7. Delete an element\n");
        printf("8. Count the total number of nodes\n");
        printf("9. Count the total number of internal nodes\n");
        printf("10. Count the total number of external nodes\n");
        printf("11. Determine the height of the tree\n");
        printf("12. Convert to mirror tree\n");
        printf("13. Delete the tree\n");
        printf("14. Exit\n");
        printf("\n\nMasukkan pilihan Anda: "); scanf("%d", &option);

        switch(option) {
            case 1:
                tree = insert(tree);
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorder(tree);
                printf("\n");
                break;
            case 3:
                printf("Inorder Traversal: ");
                inorder(tree);
                printf("\n");
                break;
            case 4:
                printf("Postorder Traversal: ");
                postorder(tree);
                printf("\n");
                break;
            case 5:
                tree = findMin(tree);
                break;
            case 6:
                tree = findMax(tree);
                break;
            case 7:
                tree = delete_node(tree);
                break;
            case 8:
                jumlahNode(tree);
                break;
            case 9:
                jumlahIntenal(tree);
                break;
            case 10:
                jumlahEksternal(tree);
                break;
            case 11:
                tinggiTree(tree);
                break;
            case 12:
                tree = ubahMirror(tree);
                break;
            case 13:
                tree = hapusTree(tree);
                break;
            case 14:
                tree = hapusTree(tree);
                return 0;
            default:
                printf("Wrong command\n");
                getchar();
        }

    } while(option != 14);

    return 0;
}