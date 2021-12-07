// AMAN PANKAJ ADATIA
// 2020CSB1154
// problem 1
// B Tree

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct bnode{
    int n; // number of keys
    int *key; // array of keys
    bool leaf; // leaf boolean - true/false
    struct bnode **child; // pointing to child (maximum 2t)
};

struct bnode *root=NULL; // root of B tree

// creating empty node
struct bnode *btree_create(int t){
    struct bnode *temp=(struct bnode*)malloc(sizeof(struct bnode));
    temp->n=0; // initially no keys as an empty node
    temp->key=(int*)malloc((2*t-1)*sizeof(int)); // assigning memory for maximum 2t-1 keys
    temp->leaf=1;
    temp->child=(struct bnode**)malloc((2*t)*sizeof(struct bnode*)); // assigning memory for maximum 2t child nodes
    for(int i=0; i<2*t; i++){
        temp->child[i]=NULL; // assigning all child to null as empty node
    }
    return temp;
}

// Split child if keys exceed 2t-1
void btree_spilt_child(struct bnode *x, int i, int t){
    struct bnode *z=btree_create(t); // making new node to store last t-1 keys
    struct bnode *y=x->child[i]; // making new node to store first t-1 keys
    z->leaf=y->leaf;
    z->n=t-1;
    for(int j=0; j<t-1; j++){
        z->key[j]=y->key[j+t];
    }
    if(!y->leaf){
        // if not leaf then assigning last t child of y to z
        for(int j=0; j<t; j++){
            z->child[j]=y->child[j+t];
        }
    }
    y->n=t-1;
    for(int j=(x->n); j>=i+1; j--){
        x->child[j+1]=x->child[j];
    }
    x->child[i+1]=z; // right child of x is now z
    for(int j=(x->n)-1; j>=i; j--){
        x->key[j+1]=x->key[j];
    }
    // center element is moved up to x from y
    x->key[i]=y->key[t-1];
    x->n=x->n+1; // total keys increase by 1
}

// inserting in a node which is not full, i.e. (keys<2t-1)
void btree_insert_nonfull(struct bnode *x, int k, int t){
    int i=x->n;
    i--;
    if(x->leaf){ // leaf
        while(i>=0 && k<x->key[i]){ // obtaining the position to insert
            x->key[i+1]=x->key[i]; // shifting all elements greater than k
            i--;
        }
        x->key[i+1]=k; // assigning the key to the position where keys remain sorted
        x->n=x->n+1; // as we are inserting total keys will now be equal to n+1
    }
    else{
        while(i>=0 && k<x->key[i]){ // obtaining the position so remains sorted (B tree condition)
            i--;
        }
        i++;
        if(x->child[i]->n==2*t-1){ // if elements are already max in child then split child
            btree_spilt_child(x, i, t);
            if(k>x->key[i]){
                i++;
            }
        }
        btree_insert_nonfull(x->child[i], k, t); // insert at child
    }
}

void btree_insert(int k, int t){
    if(root==NULL){ // if root is null then it is an empty tree
        root=btree_create(t);
        root->n=1;
        root->key[0]=k; // inserting 1st element at root
    }
    else{
        struct bnode *r=root;
        if(r->n==2*t-1){ // if root is full
            struct bnode *s=btree_create(t);
            root=s;
            s->leaf=0;
            s->n=0;
            s->child[0]=r;
            btree_spilt_child(s, 0, t);
            btree_insert_nonfull(s, k, t);
        }
        else{ // if root is not full, just insert (should remain sorted)
            btree_insert_nonfull(r, k, t);
        }
    }
}

void btree_search(struct bnode *ptr, int k, int t){
    int i=0;
    // struct bnode *ptr=root;
    while(i<ptr->n && k>ptr->key[i]){ // traversing to find the closest key to k (as keys are sorted)
        i++;
    }
    if(i<ptr->n && k==ptr->key[i]){ // if equal then present
        printf("Present \n");
    }
    else if(ptr->leaf){ // if not equal and at the leaf then not present
        printf("Not Present \n");
    }
    else{
        btree_search(ptr->child[i], k, t); // continue search at the child
    }
}

int btree_min(){ // going to the left most child (like binary search)
    struct bnode *pt=root;
    int minm=pt->key[0];
    while(pt->leaf==0){
        pt=pt->child[0];
    }
    minm=pt->key[0]; // first (0th) element of the left most child
    printf("Minimum element is: %d\n", minm);
    return minm;
}

void btree_inorder(struct bnode *pt, int t){
    if(pt->leaf){ // if leaf then print all keys in the node
        for(int j=0; j<pt->n; j++){
            printf("%d ", pt->key[j]);
        }
    }
    else{
        int j=0;
        for(j=0; j<pt->n; j++){
            btree_inorder(pt->child[j], t); // calling inorder for left child
            printf("%d ", pt->key[j]); // printing key
        }
        btree_inorder(pt->child[j], t); // the right most child (last position)
    }
}


int main()
{
    int t; // minimum degree
    char c; // A or B
    printf("Enter the minimum degree of the B-tree t: ");
    scanf("%d", &t);
    printf("Enter A or B: ");
    scanf(" %c", &c);

    if(c=='A'){
        for(int y=100; y>=1; y--){
            btree_insert(y, t); // inserting 100 to 1
        }
        struct bnode *pr=root;
        btree_inorder(pr, t); // printing inorder traversal
        printf("\n");
        int srch;
        printf("Enter an element to search: ");
        scanf("%d", &srch);
        struct bnode *spr=root;
        btree_search(spr, srch, t); // element search operation
    }
    else if(c=='B'){
        while(1){
            char ch;
            printf("options: I for insertion, S for search, M for finding minimum, T for traversing the B-tree, E for exit: ");
            scanf(" %c", &ch);
            if(ch=='E'){ // Exit
                break;
            }
            else if(ch=='M'){ // minimum element
                int minm=btree_min();
            }
            else if(ch=='S'){ // search operation
                int srch;
                printf("Enter an element to search: ");
                scanf("%d", &srch);
                struct bnode *spr=root;
                btree_search(spr, srch, t);
            }
            else if(ch=='T'){ // inorder traversal
                struct bnode *pr=root;
                btree_inorder(pr, t);
                printf("\n");
            }
            else if(ch=='I'){ // inserting elements
                int no;
                printf("Enter number of elements you wanted to enter: ");
                scanf("%d", &no);
                printf("Enter %d numbers to insert: ", no);
                for(int y=1; y<=no; y++){
                    int ins;
                    scanf("%d", &ins);
                    btree_insert(ins, t);
                }
            }
        }
    }
    return 0;
}
