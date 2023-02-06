### README

This program consists of **16** required files to run.

The first is the file **Makefile**, and this file will use shell.c, heap.c, quick.c, bubble.c, mtrand.c, sorting.c, stats.c, and set.c to create an executable file within the directory where the files are stored. It will also create *.o* files of each of these *.c* files. Makefile will delete and remake the .o files each time the executable is run. In additon, it will create the executable with the compiler clang.

There are **4** required sorting files, each with their own header, *.h*,  files, making a total of **8** files. The *4* sorting algorithm are: *shell sort*, *quick sort*, *heap sort*, and *bubble sort*. Each *.c* file for the sorting algorithm contains the base code that sorts an unsorted array. Each *.h* file contains the header for each function in the *.c* files, making them accessible in the main file, *sorting.c*.

The main file is **sorting.c**, and it assembles all of the sorting algorithms based on the inputs of the user on the command line. It will print the sorted algorithmn based on the *-p* option, printing in 5 columns, increasing from left to right in each row. After sorting using the specified commands, *sorting.c* will print a usage message telling the user how many moves and comparisons were completed within the sort. 

The following programs are all tool-based files that help do certain functions throughout the c base code for the sorting algorithms and the main file, *sorting.c*. 
- **mtrand.c** and *mtrand.h* generate the random numbers that fill the unsorted arrays based on the default values or a seed inputted by the user.
- **set.c** and *set.h* define a set that denotes which of the sorting algorithms were specified by the user on the command line.
- **stats.c** and *stats.h*  define a structure used by each sorting algorithm to track how many comparisons and moves there are during the sort.

*sorting.c* takes the following options for the command line, which can also be accessed via the -H command:
- **H**: Display program help and usage.
- **a**: Enable all sorts.
- **b**: Enable Bubble Sort.
- **h**: Enable Heap Sort.
- **q**: Enable Quick Sort.
- **s**: Enable Shell Sort.
- **n** *length*: Specify a number of array elements (default: 100).
- **p** *elements*: Specify a number of elements to print (default: 100) | Printing using *"0"* will only print the usage message.
- **r** *seed*: Specify a random seed (default: 13371453).

To run the program, simply make sure all of the required files are in one reposiroty or directory. Next, type *make* in the command line. This will create an executable called *sorting* in the repository. Type *./sorting* and the respective comman option from above. Each command is mutually exclusive, and they will not print more than once.
