#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct CircularLinkedList {
    int data;
    struct CircularLinkedList* next;
} Circular;

Circular* start = NULL;

Circular* create_cll(Circular* start) {

    int data; 
    printf("Masukkan data: "); scanf("%d", &data);

    Circular* ptr;

    while(data != -1) {
        Circular* new = (Circular*) malloc(sizeof(Circular));

        new->data = data;
        new->next = start;

        if(start == NULL) {
            
            start = new;
            start->next = start;
            ptr = start;
        }
        else {
            ptr->next = new;
            ptr = ptr->next;
        }

        printf("Masukkan data: "); scanf("%d", &data);
    }

    return start;
}

Circular* display(Circular* start) {
    
    Circular* ptr = start;
    if(ptr == NULL) {
        printf("Tidak ada data yang dapat ditampilkan\n");
        return start;
    }

    bool first = true;
    int counter = 1;
    while(ptr != start || first == true) {
        first = false;
        printf("Data ke-%d adalah: %d\n", counter, ptr->data);
        ++counter;
        first = false;
        ptr = ptr->next;
    }

    return start;
}

Circular* insert_beg(Circular* start) {
    Circular* new = (Circular*) malloc(sizeof(Circular));
    int data;
    printf("Masukkan data: "); scanf("%d", &data);
    new->data = data;
    new->next = start;
    
    // bila tidak ada data
    if(start == NULL) {
        printf("Data kosong, data terbaru akan dimasukkan ke node pertama\n");
        start = new;
        start->next = start;
        return start;
    }

    
    Circular* ptr = start;

    // bila hanya ada satu data
    if(ptr->next == start) {
        ptr->next = new;
        return start;
    }

    while(ptr->next != start) {
        ptr = ptr->next;
    }

    ptr->next = new;
    start = new;
    return start;
}

Circular* insert_end(Circular* start) {
    int data;
    printf("Masukkan data: "); scanf("%d", &data);
    
    Circular* new = (Circular*) malloc(sizeof(Circular));
    new->data = data;
    new->next = start;

    // jika tidak ada data
    if(start == NULL) {
        printf("Data kosong, data terbaru akan dimasukkan ke node pertama\n");
        start = new;
        start->next = start;
        return start;
    }

    Circular* ptr = start;

    while(ptr->next != start) {
        ptr = ptr->next;
    }
    ptr->next = new;
    return start;
}

Circular* delete_beg(Circular* start) {
    
    // jika tidak ada data
    if(start == NULL) {
        printf("Tidak ada data untuk dihapus\n");
        return start;
    }

    // jika hanya ada satu data
    if(start->next == start) {
        free(start);
        start = NULL;
        return start;
    }

    Circular* ptr = start;
    
    while(ptr->next != start) {
        ptr = ptr->next;
    }
    
    start = start->next;
    free(ptr->next);
    ptr->next = start;
    return start;
}

Circular* delete_end(Circular* start) {
    
    // jika tidak ada data
    if(start == NULL) {
        printf("Tidak ada data untuk dihapus\n");
        return start;
    }

    // jika hanya ada satu data
    if(start->next == start) {
        free(start);
        start = NULL;
        return start;
    }

    Circular* ptr = start;
    while(ptr->next->next != start) {
        ptr= ptr->next;
    }

    free(ptr->next);
    ptr->next = start;

}

Circular* delete_node(Circular* start) {

    // jika tidak ada data
    if(start == NULL) {
        printf("Tidak ada data untuk dihapus\n");
        return start;
    }

    display(start);
    printf("Delete node ke berapa ? ");
    int urutan; scanf("%d", &urutan);

    // hanya ada satu
    if(urutan == 1 && start->next == start) {
        free(start);
        start = NULL;
        return start;
    }

    Circular* ptr = start;
    int counter = 1;

    if(urutan == 1) {
        while(ptr->next != start) {
            ptr = ptr->next;
        }
        start = start->next;

        free(ptr->next);
        ptr->next = start;
        return start;
    }

    while(counter < urutan-1) {
        ptr = ptr->next;
        ++counter;
    }
    
    Circular* tmp = ptr->next->next;
    free(ptr->next);
    ptr->next = tmp;

    return start;
}

Circular* delete_list(Circular* start) {
    if(start == NULL) {
        printf("Tidak ada data yang dapat dihapus\n");
        return start;
    }

    Circular* ptr = start->next;
    Circular* pre_ptr = NULL;
    while(ptr != start) {
        pre_ptr = ptr;
        ptr = ptr->next;
        free(pre_ptr);
    }

    free(start);
    start = NULL;

    return start;
}

int main() {
    int option;
    do {
        printf("\nMain Menu\n");
        printf("1. Create data\n");
        printf("2. Display data\n");
        printf("3. Add Data at the beginning\n");
        printf("4. Add Data data at the end\n");
        printf("5. Delete data at the beginning\n");
        printf("6. Delete data at the end\n");
        printf("7. Delete a data\n");
        printf("8. Delete all data\n");
        printf("9. Exit\n");
        printf("Enter your option: "); scanf("%d", &option);

        switch(option) {
            case 1:
                start = create_cll(start);
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
                start = delete_beg(start);
                break;

            case 6:
                start = delete_end(start);
                break;

            case 7:
                start = delete_node(start);
                break;

            case 8:
                start = delete_list(start);
                break;
        }
    } while( option !=9 );

    printf("Program selesai\n");


    return 0;
}