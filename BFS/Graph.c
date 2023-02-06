//Christian Wylie, cwylie
//2023 Winter CSE 101 PA2
//Graph.c
//Main source code for Graph ADT
#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct GraphObj {
    List *ngbr; //pointer to an array of lists
    char *clr; //pointer to a char array for colors
    int *parent; //pointer to an int array of parents
    int *distance; //pointer to an array of distance to source vertex
    int vertices; //number of vertices
    int edges;
    int sourcevert; //most recent vertex for source
} GraphObj;

/*** Constructors-Destructors ***/

Graph newGraph(int n) { //each array has length of n+1 to match vertices with correct indices--DON'T USE INDEX 0
    Graph G = malloc(sizeof(GraphObj));
    assert(G != NULL);
    G->ngbr = calloc(n + 1, sizeof(List)); //an array of List Objects
    for (int i = 0; i < n + 1; i += 1) {
        G->ngbr[i] = newList(); //initialize the List for each element in the array
    }
    G->clr = calloc(n + 1, sizeof(char)); //an array of chars
    G->parent = calloc(n + 1, sizeof(int)); //an array of ints
    G->distance = calloc(n + 1, sizeof(int)); //an array of ints
    G->vertices = n;
    G->edges = 0; //no edges to start with
    G->sourcevert = NIL;
    return G;
}

void freeGraph(Graph *pG) {
    if (*pG != NULL) {
        for (int i = 0; i < (*pG)->vertices + 1; i += 1) { //go for as long as the arrays are, and free everything in each array
            freeList(&(*pG)->ngbr[i]);
        }
        free((*pG)->ngbr);
        free((*pG)->clr);
        free((*pG)->parent);
        free((*pG)->distance);
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/
int getOrder(Graph G) { //how many vertices are in the graph
    if (G == NULL) {
        fprintf(stderr, "Calling getOrder on NULL graph reference.\n");
        exit(EXIT_FAILURE);
    }
    return G->vertices;
}

int getSize(Graph G) { //how many edges are in the graph
    if (G == NULL) {
        fprintf(stderr, "Calling getSize on NULL graph reference.\n");
        exit(EXIT_FAILURE);
    }
    return G->edges;
}

int getSource(Graph G) { //NIL signifies that BFS() has not been declared yet
    if (G == NULL) {
        fprintf(stderr, "Calling getSource on NULL graph reference.\n");
        exit(EXIT_FAILURE);
    }
    if (G->sourcevert != NIL) {
        return G->sourcevert;
    }
    return NIL;
}

int getParent(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Calling getParent on NULL graph reference.\n");
        exit(EXIT_FAILURE);
    }
    if (!(1 <= u && u <= getOrder(G))) {
        fprintf(stderr, "Calling getParent on invalid vertex.\n");
        exit(EXIT_FAILURE);
    }
    if (G->sourcevert != NIL) {
        return G->parent[u];
    }
    return NIL;
}

int getDist(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Calling getDist on NULL graph reference.\n");
        exit(EXIT_FAILURE);
    }
    if (!(1 <= u && u <= getOrder(G))) {
        fprintf(stderr, "Calling getPath on invalid vertex.\n");
        exit(EXIT_FAILURE);
    }
    if (G->sourcevert != NIL) {
        return G->distance[u];
    }
    return INF;
}

void getPath(List L, Graph G, int u) { //appends the vertices that lead to the shortest path from the source to u
    if (G == NULL || L == NULL) {
        fprintf(stderr, "Calling getPath on NULL Graph or List reference.\n");
        exit(EXIT_FAILURE);
    }
    if (!(1 <= u && u <= getOrder(G))) {
        fprintf(stderr, "Calling getPath on invalid vertex.\n");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) != NIL) {
        if (u == getSource(G)) {
            append(L, u);
        }
        else if(G->parent[u] == NIL) { //if there is no connection, add NIL to the list
            append(L, NIL);
        }
        else {
            getPath(L, G, G->parent[u]); //basically recursivley call the function until you hit the parent as the source or nothing
            append(L, u);
        }
    }
}

/*** Manipulation procedures ***/
void makeNull(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Calling makeNull on NULL graph reference.\n");
        exit(EXIT_FAILURE);
    }
    /*
    if (G != NULL) {
           G->edges = 0;
           for (int i = 0; i < G->vertices + 1; i += 1) {
                clear(G->ngbr[i]);
           }
    }
    */
    int n = G->vertices;
    freeGraph(&G);
    G = newGraph(n);
}

void addEdge(Graph G, int u, int v) {//everything is meant to be kept in increasing order
    if (G == NULL) {
        fprintf(stderr, "Calling addEdge on NULL graph reference.\n");
        exit(EXIT_FAILURE);
    }
    List U = G->ngbr[u]; //to make it easier to call the lists
    List V = G->ngbr[v];
    bool check = false;
    if (length(U) == 0) {
        append(U, v);
    }
    else {
        for(moveFront(U); index(U) >=0; moveNext(U)) {
            if (v <= get(U)) {
                insertBefore(U, v);
                check = true;
                break;
            }
        }
        if (check == false) {
            append(U, v);
        }
    }
    check = false;
    if (length(V) == 0) {
        append(V, u);
    }
    else {
        for(moveFront(V); index(V) >=0; moveNext(V)) {
            if (u <= get(V)) {
                insertBefore(V, u);
                check = true;
                break;
            }
        }
        if (check == false) {
            append(V, u);
        }
    }
    G->edges += 1; //makes sure to increment the edge count by 1
}

void addArc(Graph G, int u, int v) {//adding a directed egde, meaning there is only one addition to the adj list.
    if (G == NULL) {
        fprintf(stderr, "Calling addEdge on NULL graph reference.\n");
        exit(EXIT_FAILURE);
    }
    List U = G->ngbr[u]; //to make it easier to call the lists
    bool check = false;
    if (length(U) == 0) {
        append(U, v);
    }
    else {
        for(moveFront(U); index(U) >=0; moveNext(U)) {
            if (v <= get(U)) {
                insertBefore(U, v);
                check = true;
                break;
            }
        }
        if (check == false) {
            append(U, v);
        }
    }
    G->edges += 1;
}

void BFS(Graph G, int s) {
    if (G == NULL) {
        fprintf(stderr, "Calling BFS on NULL graph reference.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < G->vertices+1; i += 1) { //start at 1 because we aren't using the 0th vertex; Initalize them all
        G->clr[i] = 'w';
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->sourcevert = s;
    G->clr[s] = 'g';
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List Queue = newList(); //create a queue out of a list
    prepend(Queue, s);
    while (length(Queue) != 0) { //while the queue isn't empty
        int x = front(Queue); //Dequeue is basically just get the front and delete it after
        deleteFront(Queue);
        List X = G->ngbr[x]; //adj list of x
        for (moveFront(X); index(X) >=0; moveNext(X)) {
            int y = get(X);
            if (G->clr[y] == 'w') {
                G->clr[y] = 'g';
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                append(Queue, y); //add it on to the end of the queue, so we take them out sequentially
            }
        }
        G->clr[x] = 'b';
    }
    freeList(&Queue); //make sure to free the queue after we finish with it
}

/*** Other operations ***/
void printGraph(FILE *out, Graph G) { //prints out the list to out, will end on an endline
    if (G == NULL) {
        fprintf(stderr, "Calling printGraph on NULL graph reference.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < G->vertices + 1; i += 1) {
        fprintf(out, "%d: ", i);
        List curr = G->ngbr[i];
        printList(out, curr); //print the things in the list
        fprintf(out, "\n");
    }
}
