#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int INTEGER;

typedef struct LinkedList {
    int data;
    struct LinkedList* next;
} list;

list* start = NULL;

int countNode(list* start) {
    list* ptr = start;
    if(start == NULL) {
        return 0;
    }
    
    int counter = 1;
    while(ptr != NULL) {
        ptr = ptr->next;
        ++counter;
    }
    return counter;
}

bool isValidNode(list* start, int urutan) {
    if(urutan > countNode(start) || urutan <= 0) {
        return false;
    }
    return true;
}

list* create_ll(list* start) {
    int num;
    list *ptr, *newNode;

    if(start != NULL) {
        printf("Data tidak kosong, hapus semua data terlebih dahulu!\n");
        return start;
    }

    printf("Masukkan -1 untuk selesai\n");
    printf("Masukkan data: "); scanf("%d", &num);

    while(num != -1) {
        newNode = (list*) malloc(sizeof(list));
        newNode->data = num;
        newNode->next = NULL;
        if(start == NULL) {
            start = newNode;
        }
        else {
            ptr = start;
            while(ptr->next != NULL) {
                ptr = ptr->next;
            }
            ptr->next = newNode;
        }
        printf("Masukkan data: "); scanf("%d", &num);
    }
    return start;
}

list* display(list* start) {
    // if(start == NULL)
    int counter=0;
    list* ptr = start;

    if(ptr == NULL) {
        printf("Tidak ada data untuk ditampilkan\n");
    }

    while(ptr != NULL) {
        printf("Data node ke-%d adalah: %d\n", counter+1, ptr->data);
        ptr = ptr->next;
        ++counter;
    }
    return start;
}

list* insert_beg(list* node) {
    int data;
    printf("Masukkan data: "); scanf("%d", &data);

    if(node == NULL) {
        list* tmp = (list*) malloc(sizeof(list));
        node = tmp;
        node->data = data;
        node->next = NULL;
        return node;
    }
    
    list* tmp = (list*) malloc(sizeof(list));
    tmp->data = data;
    tmp->next = node;
    return tmp;
}

list* insert_end(list* start) {
    int data;
    printf("Masukkan data: "); scanf("%d", &data);

    list* tmp = (list*) malloc(sizeof(list));
    tmp->data = data;
    tmp->next = NULL;

    if(start == NULL) {
        start = tmp;
        return start;
    }
    

    list* ptr = start;
    while(ptr->next != NULL) {
        ptr = ptr->next;
    }
    
    
    ptr->next = tmp;
    return start;
}

list* insert_before(list* start) {
    int data;
    printf("Masukkan data: "); scanf("%d", &data);
    list* tmp = (list*) malloc(sizeof(list));
    tmp->data = data;
    tmp->next = NULL;

    if(start == NULL) {
        printf("Karena data kosong, data terbaru akan dimasukkan ke node pertama\n");
        start = tmp;
        return start;
    }
    
    list* ptr = start;
    printf("\n");
    display(start);
    int urutan;
    printf("Masukkan data sebelum data ke berapa? "); scanf("%d", &urutan);

    if(!isValidNode(start, urutan)) {
        printf("Tidak ada node tidak valid\n");
        return start;
    }

    if(urutan == 1) {
        tmp->next = start;
        return tmp;
    }

    int counter = 1;
    while(counter != urutan-1) {
        ptr = ptr->next;
        ++counter;
    }

    // simpan node sebelum node masuk
    list* after = ptr->next;
    ptr->next = tmp;
    tmp->next = after;
    return start;
}

list* insert_after(list* start) {
    list* tmp = (list*) malloc(sizeof(list));
    int data; 
    printf("Masukkan data: "); scanf("%d", &data);
    tmp->data = data;
    tmp->next = NULL;

    if(start == NULL) {
        printf("Karena data kosong, data terbaru akan dimasukkan ke node pertama\n");
        start = tmp;
        return start;
    }
    
    list* ptr = start;
    display(start);
    int urutan;
    printf("Masukkan data setelah data ke berapa? "); scanf("%d", &urutan);

    if(!isValidNode(start, urutan)) {
        printf("Node tidak valid\n");
        return start;
    }

    int counter = 1;
    while(counter != urutan) {
        ptr = ptr->next;
        ++counter;
    }

    // simpan node sebelum node baru masuk
    list* after = ptr->next;
    ptr->next = tmp;
    tmp->next = after;
    return start;
}

list* delete_beg(list* start) {
    if(start == NULL) {
        printf("Data koisong tidak ada yang akan dihapus\n");
        return start;
    }
    
    list* tmp = start;
    start = start->next;
    free(tmp);
    tmp = NULL;
    return start;

}
list* delete_end(list* start) {
    list* ptr = start;

    if(start == NULL) {
        printf("Data koisong tidak ada yang akan dihapus\n");
        return start;
    }

    while(ptr->next->next != NULL) {
        ptr = ptr->next;
    }
    free(ptr->next);
    ptr->next = NULL;

    return start;
}

list* delete_node(list* start) {

    if(start == NULL) {
        printf("Tidak ada data yang bisa dihapus\n");
        return start;
    }

    int urutan;
    printf("Data ke berapa yang ingin dihapus ? "); scanf("%d", &urutan);

    if(!isValidNode(start, urutan)) {
        printf("Node tidak valid\n");
        return start;
    }

    if(urutan == 1) {
        free(start);
        start = NULL;
        return start;
    }

    
    list* ptr = start;
    int counter = 1;
    while(counter != urutan-1) {
        ptr = ptr->next;
        ++counter;
    }

    list* tmp = ptr->next->next;
    free(ptr->next);
    ptr->next = tmp;
    return start;

}

list* delete_list(list* start) {
    list* ptr = start;
    if(ptr == NULL) {
        printf("Data koisong tidak ada yang akan dihapus\n");
        return start;
    }
    while(ptr != NULL) {
        list* tmp = ptr;
        ptr = ptr->next;
        free(tmp);
        tmp = NULL;
    }
    start = NULL;
    return start;
}

list* reverse_list(list* start) {
    list* ptr = start;
    list* tmp = NULL;
    list* new_list = NULL;

    if(ptr == NULL) {
        printf("Data koisong tidak ada yang akan dihapus\n");
        return start;
    }

    while(ptr != NULL) {
        tmp = ptr;
        ptr = ptr->next;
        tmp->next = new_list;
        new_list = tmp;
    }
    return new_list;
}

list* sort_list(list* start) {
    list* simpan = start;
    if(start == NULL) {
        printf("Data koisong tidak ada yang akan dihapus\n");
        return start;
    }
    
    while(simpan->next != NULL) {
        list* ptr = simpan->next;
        while(ptr != NULL) {
            if(simpan->data > ptr->data) {
                int tmp = ptr->data;
                ptr->data = simpan->data;
                simpan->data = tmp;
            }
            ptr = ptr->next;
        }
        simpan = simpan->next;
    }
    printf("Data berhasil diurutkan\n");
    return start;
}

int main() {
    int option;
    do {
        printf("\n\nMain Menu\n");
        printf("1. Create List\n");
        printf("2. Display List\n");
        printf("3. Add node at the beginning\n");
        printf("4. Add node at the end\n");
        printf("5. Add node before a given node\n");
        printf("6. Add node after a given node\n");
        printf("7. Delete node from the beginning\n");
        printf("8. Delete node from the end\n");
        printf("9. Delete a given node\n");
        printf("10. Delete the entire list\n");
        printf("11. Reverse list\n");
        printf("12. Sort the list\n");
        printf("13. EXIT: ");
        printf("\n\nEnter your option: ");
        scanf("%d", &option);
        printf("\n\n");
        switch (option)
        {
        case 1:
            start = create_ll(start);
            break;
        case 2:
            start = display(start);
            break;
        case 3:
            start = insert_beg(start);
            break;
        case 4:
            start = insert_end(start);
            break;
        case 5:
            start = insert_before(start);
            break;
        case 6:
            start = insert_after(start);
            break;
        case 7:
            start = delete_beg(start);
            break;
        case 8:
            start = delete_end(start);
            break;
        case 9:
            start = delete_node(start);
            break;
        case 10:
            start = delete_list(start);
            break;
        case 11:
            start = reverse_list(start);
            break;
        case 12:
            start = sort_list(start);
            break;
        }
    } while(option != 13);
    getchar();

    return 0;
}
