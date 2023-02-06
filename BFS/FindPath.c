//Christian Wylie, cwylie
//2023 Winter CSE 101 PA2
//Graph.c
//Main source code for FindPath Executable

#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

int main(int argc, char * argv[]) {
    FILE *in_file, *out_file;

    //check for 2 command line arguments
    if( argc != 3 ){ //because it's counting the call of Lex as 0, in and out as 1 and 2
       fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
       exit(EXIT_FAILURE);
    }

    in_file = fopen(argv[1], "r"); //open in_file for reading
    if (in_file == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        fclose(in_file);
        exit(EXIT_FAILURE);
    }

    out_file = fopen(argv[2], "w"); //open out_file for writing
    if (out_file == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[2]);
        fclose(out_file);
        exit(EXIT_FAILURE);
    }

    int vertices = 0;
    int startvert = 0;
    int endvert = 0;
    fscanf(in_file, "%d\n", &vertices);
    Graph G = newGraph(vertices);
    while (!feof(in_file)) { //build the graph
        fscanf(in_file, "%d %d\n", &startvert, &endvert);
        if (startvert == 0 && endvert == 0) {
            break;
        }
        addEdge(G, startvert, endvert);
    }
    printGraph(out_file, G); //print the graph to the outfile
    fprintf(out_file, "\n");

    while (!feof(in_file)) {
        fscanf(in_file, "%d %d\n", &startvert, &endvert);
        if (startvert == 0 && endvert == 0) {
            break;
        }
        List Path = newList();
        BFS(G, startvert);
        getPath(Path, G, endvert);
        if (front(Path) != NIL) {
            fprintf(out_file, "The distance from %d to %d is %d\n", startvert, endvert, length(Path)-1);
            fprintf(out_file, "A shortest %d-%d path is: ", startvert, endvert);
            printList(out_file, Path);
            fprintf(out_file, "\n\n");
        }
        else if (front(Path) == NIL) {
            fprintf(out_file, "The distance from %d to %d is infinity\n", startvert, endvert);
            fprintf(out_file, "No %d-%d path exists\n", startvert, endvert);
            fprintf(out_file, "\n");
        }
        freeList(&Path);
    }

    freeGraph(&G);
    fclose(in_file);
    fclose(out_file);
    return 0;
}