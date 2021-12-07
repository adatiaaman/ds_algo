// Aman Pankaj Adatia
// 2020CSB1154
// problem 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct gnode{ // Graph Vertex
    // doubly linked list
    int data;
    struct gnode* next;
    struct gnode* prev;
};

struct grpbfs{ // characteristics
    int d; // distance
    int pi; // predecessor
    int color; // color: 0-white, 1-Gray, 2-Black
};

struct gqueue{ // Queue (FIFO) (used for BFS)
    // linked list
    int s;
    struct gqueue* next;
};

// Queue front and rare nodes
struct gqueue *f=NULL;
struct gqueue *r=NULL;

void enqueue(int val){ // adding element in the queue (first in)
    struct gqueue *n=(struct gqueue *)malloc(sizeof(struct gqueue));
    n->s=val;
    n->next=NULL;
    if(r==NULL){
        f=n;
        r=n;
    }
    else{
        r->next=n;
        r=n;
    }
}

int dequeue(){ // removing element from the queue (first out)
    int val;
    struct gqueue *ptr=f;
    if(f==NULL){
        return 0;
    }
    val=f->s;
    f=f->next;
    if(f==NULL){
        r=NULL;
    }
    return val;
}

void insert_graph(int a, int b, struct gnode** arr){ // inserting in graph
    // An edge is created from b to a
    struct gnode *temp;
    temp=(struct gnode*)malloc(sizeof(struct gnode));
    temp->data=a;
    temp->prev=NULL;
    if(arr[b]==NULL){
        temp->next=NULL;
        temp->prev=NULL;
        arr[b]=temp;
    }
    else{
        temp->next=arr[b];
        arr[b]->prev=temp;
        arr[b]=temp;
    }
}

void display_graph(struct gnode** arr, int m){ // display
    // Adjacency List representation
    int i;
    for(i=0; i<m; i++){ // for all vertices
        printf("Vertex %d: ", i);
        if(arr[i]==NULL){
            printf("NULL\n");
        }
        else{
            struct gnode *temp;
            temp=(struct gnode*)malloc(sizeof(struct gnode));
            temp=arr[i];
            while(temp!=NULL){
                printf("%d ", temp->data);
                temp=temp->next;
            }
            printf("\n");
        }
    }
}

void BFS(struct gnode** arr, int m, int s, struct grpbfs **grp){ // Breadth-First Search
    int i;
    // Initializing values
    for(i=0; i<m; i++){
        grp[i]=(struct grpbfs *)malloc(sizeof(struct grpbfs));
        if(i==s){
            continue;
        }
        grp[i]->color=0; // white
        grp[i]->d=1000000;
        grp[i]->pi=-1;
    }
    grp[s]->d=0;
    grp[s]->color=1; // gray
    grp[s]->pi=-1;
    enqueue(s);

    while(f!=NULL){ // discover all vertex reachable from s
        int u=dequeue();
        struct gnode *temp;
        temp=arr[u];
        while(temp!=NULL){
            int v=temp->data;
            if(grp[v]->color==0){
                grp[v]->color=1; // white - discovered (successor)
                grp[v]->d=(grp[u]->d)+1;
                grp[v]->pi=u;
                enqueue(v);
            }
            temp=temp->next;
        }
        grp[u]->color=2; // black
    }
}


int main()
{
    int ver=0, i;
    printf("Enter the number of vertices: ");
    scanf("%d", &ver); // Total vertices
    if(ver<=0){
        printf("Invalid Input\n");
        return 0;
    }
    struct gnode** gg=(struct gnode**)malloc(ver*sizeof(struct gnode*)); // Graph
    struct grpbfs** grp=(struct grpbfs**)malloc(ver*sizeof(struct grpbfs*)); // characteristics for all vertices
    for(i=0; i<ver; i++){
        gg[i]=NULL;
        grp[i]=NULL;
    }

    char dug; // Directed or Undirected
    printf("Enter D for directed or U for undirected graphs: ");
    scanf(" %c", &dug);

    if(dug=='U'){
        printf("Enter '-1 -1' to Quit (Q)\n");
        while(1){
            int a, b;
            // Quit Q: a=-1, b=-1
            scanf("%d %d", &a, &b);
            if(a==-1 || b==-1){
                break;
            }
            else{
                // As it is undirected, both the vertices face each other
                insert_graph(a, b, gg);
                insert_graph(b, a, gg);
            }
        }
        printf("Your undirected graph is as follows: \n");
        display_graph(gg, ver);
    }
    else if(dug=='D'){
        printf("Enter '-1 -1' to Quit (Q)\n");
        while(1){
            int a, b;
            // Quit Q: a=-1, b=-1
            scanf("%d %d", &a, &b);
            if(a==-1 && b==-1){
                break;
            }
            else{
                // An edge created from a to b
                insert_graph(b, a, gg);
            }
        }
        printf("Your directed graph is as follows: \n");
        display_graph(gg, ver);
    }

    int s;
    printf("Enter a source vertex s from where you wants to run the BFS algorithm: \n");
    printf("Your options are 0, 1, ..., %d: ", ver-1);
    scanf("%d", &s);
    if(s<0 || s>=ver){
        printf("Invalid Input\n");
    }
    else{
        BFS(gg, ver, s, grp);
        for(i=0; i<ver; i++){
            if(grp[i]->d==1000000){ // If there does not exist a path from source to the vertex
                printf("The distance of the vertex %d from source vertex %d is: INF\n", i, s);
            }
            else{ // Printing shortest path from the source to the vertex
                printf("The distance of the vertex %d from source vertex %d is: %d\n", i, s, grp[i]->d);
            }
        }
    }
    return 0;
}
