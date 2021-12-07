// Aman Pankaj Adatia
// 2020CSB1154
// problem 1
// AVL Tree

#include <stdio.h>
#include <stdlib.h>

struct node{
    int key; // key value
    struct node* left; // pointer to left child
    struct node* right; // pointer to right child
    int height; // height of the node
};

// root node
struct node *root=NULL;

int max(int a, int b){ // returns maximum of two numbers
    if(a>b){
        return a;
    }
    return b;
}

// creating a new node
struct node *new_node(int k){
    struct node* temp=(struct node*)malloc(sizeof(struct node)); // assigning memory
    temp->key=k;
    temp->left=NULL;
    temp->right=NULL;
    temp->height=1; // added at leaf initially
    return temp;
}

int height(struct node *N){ // returns the height of node
    if(N==NULL){ // if the node has no children, height will be zero
        return 0;
    }
    return N->height;
}

int balance(struct node *n){ // calculating balance factor
    if(n==NULL){
        return 0;
    }
    else{
        // difference between height of left and right subtree
        return height(n->left)-height(n->right);
    }
}

// Right Rotation
struct node* right_rotate(struct node* p){
    struct node* q=p->left;
    struct node* t=q->right;

    q->right=p;
    p->left=t;
    // adjusting heights
    p->height=max(height(p->left), height(p->right))+1;
    q->height=max(height(q->left), height(q->right))+1;
    return q;
}

// Left Rotation
struct node* left_rotate(struct node* p){
    struct node* q=p->right;
    struct node* t=q->left;

    q->left=p;
    p->right=t;
    // adjusting heights
    p->height=max(height(p->left), height(p->right))+1;
    q->height=max(height(q->left), height(q->right))+1;
    return q;
}

// inserting key
struct node* insert_node(struct node* N, int k){
    // N=root
    if(N==NULL){
        return new_node(k);
    }
    else{
        if(k<N->key){ // if key is smaller than node key, insert at left subtree
            N->left=insert_node(N->left, k);
        }
        else if(k>N->key){ // if key is greater than node key, insert at right subtree
            N->right=insert_node(N->right, k);
        }
        else{
            return N;
        }
    }
    N->height=1+max(height(N->left), height(N->right)); // height adjustment

    int b=balance(N); // checking balance factor, if rotation is needed or not
    if(b>1){
        if(k<N->left->key){
            // Left Left
            return right_rotate(N);
        }
        if(k>N->left->key){
            // Left Right
            N->left=left_rotate(N->left);
            return right_rotate(N);
        }
    }
    if(b<-1){
        if(k>N->right->key){
            // Right Right
            return left_rotate(N);
        }
        if(k<N->right->key){
            // Right Left
            N->right=right_rotate(N->right);
            return left_rotate(N);
        }
    }
    return N;
}

void search_node(struct node* ptr, int k){
    // ptr=root;
    if(ptr==NULL){ // Not Found
        printf("Not Present\n");
    }
    else if(ptr->key==k){ // Found
        printf("Present\n");
        printf("Balance factor of %d is %d\n", k, balance(ptr));
        printf("Height of %d in the AVL tree is %d\n", k, height(ptr)-1); // 0th indexing
    }
    else{
        // Search like BST (binary search tree)
        if(ptr->key<k){ // if key to be found is greater than the key of the node, then search at the right subtree of the current node
            search_node(ptr->right, k);
        }
        else{ // if key to be found is less than the key of the node, then search at the left subtree of the current node
            search_node(ptr->left, k);
        }
    }
}

void preorder(struct node* ptr){ // Preorder traversal
    // ptr=root;
    if(ptr!=NULL){
        printf("%d ", ptr->key);
        preorder(ptr->left);
        preorder(ptr->right);
    }
}

void inorder(struct node* ptr){ // Inorder traversal (sorted)
    // ptr=root;
    if(ptr!=NULL){
        inorder(ptr->left);
        printf("%d ", ptr->key);
        inorder(ptr->right);
    }
}

int main()
{
    for(int i=0; i<=24; i++){
        root=insert_node(root, i);
    }
    // insert 0 to 24 elements
    printf("AVL tree constructed by inserting 0 to 24 elements\n\n");

    while(1){
        char c;
        printf("i) Insert: \ns) Search: \np) Print Preorder and Inorder in Separate lines: \nq) Quit: \n");
        printf("\n");
        printf("Enter your choice: ");
        scanf(" %c", &c);

        if(c=='q'){ //Quit
            break;
        }
        else if(c=='i'){
            int n;
            printf("Enter data to insert: ");
            scanf("%d", &n);
            // insert n
            root=insert_node(root, n);
        }
        else if(c=='s'){
            int m;
            printf("Enter data you want to search: ");
            scanf("%d", &m);
            // search m
            struct node* ptrs=(struct node*)malloc(sizeof(struct node));
            ptrs=root;
            search_node(ptrs, m);
        }
        else if(c=='p'){
            // Preorder Traversal
            printf("Preorder sequence: \n");
            struct node* ptr1=(struct node*)malloc(sizeof(struct node));
            ptr1=root;
            preorder(ptr1);
            printf("\n");

            // Inorder Traversal
            printf("Inorder sequence: \n");
            struct node* ptr2=(struct node*)malloc(sizeof(struct node));
            ptr2=root;
            inorder(ptr2);
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}
