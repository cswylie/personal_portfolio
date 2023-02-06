### README
### Files Included
- **List.h** - Header file for the List.c source code
- **List.c** -  Source code for the List ADT
- **Graph.c** - Source code for the Graph ADT
- **Graph.h** - Header file for the Graph.c source code
- **FindPath.c** - Source code for the FindPath executable
- **Makefile** - Makefile for executables and other make statements
- **README.md** - Table of contents for all files

### Here are all of the make commands:
- **FindPath** - Makes FindPath executable to find the path in an input file
- **clean** - Removes all *.o files and executables.
- **checkFind** - runs valgrind on FindPath

The program needs an input file and an output file to work properly.

The text formatting for the input file should look something like this:
 6
 1 2
 1 3
 2 4
 2 5
 2 6
 3 4
 4 5
 5 6
 0 0
 1 5
 3 6
 2 3
 4 4
 0 0 

The first number signifies how many vertices will be in the graph.
The first set of double 0s signify where to stop when creating the graph. Each number pair before then signifies an edge on the graph.
The second set of double 0s signify where to stop when running BFS in number pairs. The number pairs above it signify where to start in the graph, the left vertex, and where to get to in the graph, the right vertex.
The program will print out the distances from each source vertex to its destination.

The program will also use the command line to properly use the input and output file.
- Make the program.
- Type ./FindPath *input_file* *output_file*
