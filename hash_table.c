// Aman Pankaj Adatia
// 2020CSB1154

#include <stdio.h>
#include <stdlib.h>

// Hash Table where collisions are resolved via chaining with doubly linked lists

struct hnode{ // Doubly Linked list
    int data;
    struct hnode* next; // pointer to next node
    struct hnode* prev; // pointer to previous node
};

int hash_funcn(int k, int m){ // Hash function
    int hf=k%m;
    if(hf<0){ // modulo for negative number
        hf+=m;
    }
    return hf;
}

void insert_hash(int k, struct hnode** arr, int m){ // insert into hash table
    int index=hash_funcn(k, m); // index
    struct hnode *temp;
    temp=(struct hnode*)malloc(sizeof(struct hnode));
    temp->data=k;
    temp->prev=NULL;
    if(arr[index]==NULL){ // if initially no element is present in the (index) doubly linked list
        temp->next=NULL;
        temp->prev=NULL;
        arr[index]=temp; // head
    }
    else{ // insert at head
        temp->next=arr[index];
        arr[index]->prev=temp;
        arr[index]=temp;
    }
}

void delete_hash(int k, struct hnode** arr, int m){
    int index=hash_funcn(k, m); // index
    struct hnode *temp;
    temp=(struct hnode*)malloc(sizeof(struct hnode));
    temp=arr[index];
    int f=0;
    while(temp!=NULL){
        if(temp->data==k){ // element found
            f=1;
            // Deleting cases
            if(temp->next==NULL && temp->prev==NULL){ // single element case
                arr[index]=NULL;
            }
            else if(temp->next==NULL && temp->prev!=NULL){ // element at last position
                temp=temp->prev;
                temp->next=NULL;

            }
            else if(temp->next!=NULL && temp->prev==NULL){ // element at first position
                temp=temp->next;
                temp->prev=NULL;
                arr[index]=temp;
            }
            else{ // general case for deleting (in between two elements)
                temp->prev->next=temp->next;
                temp->next->prev=temp->prev;
            }
        }
        temp=temp->next;
    }
    if(f==0){ // element not found
        printf("Element not found\n");
    }
}

void search_hash(int k, struct hnode** arr, int m){ // searching element in hash table
    int index=hash_funcn(k, m); // index
    struct hnode *temp;
    temp=(struct hnode*)malloc(sizeof(struct hnode));
    temp=arr[index];
    int f=0;
    while(temp!=NULL){
        if(temp->data==k){ // element found in linked list at the index, based on hash function
            f=1;
        }
        temp=temp->next;
    }
    if(f){ // index is the slot number
        printf("Searched element %d is found in slot number %d\n", k, index);
    }
    else{
        printf("Searched element %d is NOT found\n", k);
    }
}

void display_hash(struct hnode** arr, int m){ // display entire hash table
    int i;
    for(i=0; i<m; i++){ // all indexes/slots
        printf("index %d: ", i);
        if(arr[i]==NULL){ // if no element present in the linked list
            printf("NULL\n");
        }
        else{
            struct hnode *temp;
            temp=(struct hnode*)malloc(sizeof(struct hnode));
            temp=arr[i];
            while(temp!=NULL){ // traversing and printing entire linked list
                printf("%d ", temp->data);
                temp=temp->next;
            }
            printf("\n");
        }
    }
}

int main()
{
    // m = hash table size
    int m, i;
    printf("Enter hash table size m: ");
    scanf("%d", &m);

    if(m<=0){
        printf("Invalid Input\n");
        return 0;
    }

    // struct hnode* a[m]; // alternate
    struct hnode** a=(struct hnode**)malloc(m*sizeof(struct hnode*));
    for(i=0; i<m; i++){
        a[i]=NULL;
    }

    while(1){
        int x;
        printf("1. Insert\n2. Delete\n3. Search\n4. Display\n5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &x);

        if(x==5){ // Quit
            break;
        }
        else if(x==1){ // Insert
            int key;
            printf("Enter value to insert: ");
            scanf("%d", &key);
            insert_hash(key, a, m);
        }
        else if(x==2){ // Delete
            int del;
            printf("Enter value to be deleted: ");
            scanf("%d", &del);
            delete_hash(del, a, m);
        }
        else if(x==3){ // Search
            int s;
            printf("Enter the element to be searched: ");
            scanf("%d", &s);
            search_hash(s, a, m);
        }
        else if(x==4){ // Display
            display_hash(a, m);
        }
        else{ // Invalid input
            printf("Enter a valid number (from 1 to 5)\n");
        }
        printf("\n");
    }

    return 0;
}
