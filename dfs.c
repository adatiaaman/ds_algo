// Aman Pankaj Adatia
// 2020CSB1154
// problem 1
// DFS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int time=0; // time variable
int pos_edge=0; // variable used as index to store edge details

struct gnode{ // Graph Vertex
    // doubly linked list
    int data;
    struct gnode* next;
    struct gnode* prev;
};

struct grpbfs{ // characteristics
    int d; // discovery time
    int f; // finishing time
    int pi; // predecessor
    int color; // color: 0-white, 1-Gray, 2-Black
};

struct edges{
    // vertices
    int e1;
    int e2;
    int ed_t; // 0-tree, 1-back, 2-forward, 3-cross
};

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

// DFS
void DFS_VISIT(struct gnode** arr, int m, struct grpbfs **grp, int u, struct edges **edge){
    time=time+1;
    grp[u]->d=time;
    grp[u]->color=1;

    struct gnode *temp;
    temp=arr[u];
    while(temp!=NULL){
        int v=temp->data;
        // edges based on color of visited vertex
        if(grp[v]->color==0){
            grp[v]->pi=u;
            edge[pos_edge]=(struct edges *)malloc(sizeof(struct edges));
            edge[pos_edge]->e1=u;
            edge[pos_edge]->e2=v;
            edge[pos_edge]->ed_t=0; // tree
            pos_edge++;
            // explore the visited vertices (depth)
            DFS_VISIT(arr, m, grp, v, edge);
        }
        else if(grp[v]->color==1){
            edge[pos_edge]=(struct edges *)malloc(sizeof(struct edges));
            edge[pos_edge]->e1=u;
            edge[pos_edge]->e2=v;
            edge[pos_edge]->ed_t=1; // back
            pos_edge++;
        }
        else if(grp[v]->color==2){
            edge[pos_edge]=(struct edges *)malloc(sizeof(struct edges));
            edge[pos_edge]->e1=u;
            edge[pos_edge]->e2=v;
            edge[pos_edge]->ed_t=3;
            /*if(grp[u]->d<grp[v]->d && grp[u]->f>grp[v]->f){
                edge[pos_edge]->ed_t=2; // forward
            }
            else{
                edge[pos_edge]->ed_t=3; // cross
            }*/
            pos_edge++;
        }
        temp=temp->next;
    }
    // after finishing exploring the entire vertex
    grp[u]->color=2; // black
    time=time+1;
    grp[u]->f=time;
}

void DFS(struct gnode** arr, int m, struct grpbfs **grp, struct edges **edge){
    int i;
    for(i=0; i<m; i++){
        grp[i]=(struct grpbfs *)malloc(sizeof(struct grpbfs));
        // initializing characteristics for all vertices
        grp[i]->color=0;
        grp[i]->pi=-1;
        grp[i]->d=0;
        grp[i]->f=100000000; // inf
    }
    time=0;
    for(i=0; i<m; i++){
        if(grp[i]->color==0){ // DFS_VISIT only if unvisited i.e. white color
            DFS_VISIT(arr, m, grp, i, edge);
        }
    }
}

void DFS_time(struct gnode** arr, int m, struct grpbfs **grp){ // printing discovery and finishing time for all vertices in graph
    int i;
    for(i=0; i<m; i++){
        printf("Vertex %d: discovery time %d, finishing time %d\n", i, grp[i]->d, grp[i]->f);
    }
}

void DFS_edge_d(struct edges **edge, int ed_size, struct grpbfs **grp){ // printing type of edges
    int i;
    for(i=0; i<ed_size && edge[i]!=NULL; i++){
        if(edge[i]->ed_t==3){
            // grp[edge[i]->e1]->d<grp[edge[i]->e2]->d && grp[edge[i]->e1]->f>grp[edge[i]->e2]->f
            if(grp[edge[i]->e1]->d<grp[edge[i]->e2]->d && grp[edge[i]->e1]->f>grp[edge[i]->e2]->f){
               edge[i]->ed_t=2;
            }
        }
        printf("Edge (%d, %d): ", edge[i]->e1, edge[i]->e2);
        if(edge[i]->ed_t==0){
            printf("Tree\n");
        }
        if(edge[i]->ed_t==1){
            printf("Back\n");
        }
        if(edge[i]->ed_t==2){
            printf("Forward\n");
        }
        if(edge[i]->ed_t==3){
            printf("Cross\n");
        }
    }
}

void DFS_edge_u(struct edges **edge, int ed_size, int ver, struct grpbfs **grp){
    int v_arr[ver+1][ver+1]; // visited array - storing if AB edge is already printed, then BA edge will not be printed
    int i, j;
    for(i=0; i<ver+1; i++){
        for(j=0; j<ver+1; j++){
            v_arr[i][j]=-1; // matrix storing -1 for all edges
        }
    }
    for(i=0; i<ed_size; i++){
        if(v_arr[edge[i]->e1][edge[i]->e2]!=-1 || v_arr[edge[i]->e2][edge[i]->e1]!=-1){
            continue; // skip printing if already printed before
        }
        v_arr[edge[i]->e1][edge[i]->e2]=1; // if explored first time
        if(edge[i]->ed_t==3){
            // grp[edge[i]->e1]->d<grp[edge[i]->e2]->d && grp[edge[i]->e1]->f>grp[edge[i]->e2]->f
            if(grp[edge[i]->e1]->d<grp[edge[i]->e2]->d && grp[edge[i]->e1]->f>grp[edge[i]->e2]->f){
               edge[i]->ed_t=2;
            }
        }
        printf("Edge (%d, %d): ", edge[i]->e1, edge[i]->e2);
        if(edge[i]->ed_t==0){
            printf("Tree\n");
        }
        if(edge[i]->ed_t==1){
            printf("Back\n");
        }
        if(edge[i]->ed_t==2){
            printf("Forward\n");
        }
        if(edge[i]->ed_t==3){
            printf("Cross\n");
        }
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
    int ed_size=0; // total edges count
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
                ed_size+=2;
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
                ed_size++;
                insert_graph(b, a, gg);
            }
        }
        printf("Your directed graph is as follows: \n");
        display_graph(gg, ver);
    }

    struct edges** edge=(struct edges**)malloc(ed_size*sizeof(struct edges*)); // edge type
    for(i=0; i<ed_size; i++){
        edge[i]=NULL;
    }

    // DFS
    printf("The program runs the DFS algorithm on the graph entered.\n");
    DFS(gg, ver, grp, edge); // Depth First Search
    printf("The discovery time and the finishing time for the vertices of the directed graph are as follows: \n");
    DFS_time(gg, ver, grp); // Printing discovery and finishing time
    printf("The classification of edges are as follows: \n");
    // Printing edge details
    if(dug=='D'){
        DFS_edge_d(edge, ed_size, grp); // directed
    }
    else if(dug=='U'){
        DFS_edge_u(edge, ed_size, ver, grp); // undirected
    }

    return 0;
}
