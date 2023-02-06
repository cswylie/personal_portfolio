#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include "mtrand.h"
#include "stats.h"
#include "bubble.h"
#include "heap.h"
#include "quick.h"
#include "shell.h"
#include "set.h"

#define OPTIONS "asbqhr:n:p:H"

int main(int argc, char **argv) {
    int opt = 0;
    uint64_t seed = 13371453;
    uint64_t seedtarget; 
    uint32_t size = 100;
    uint32_t sizetarget;
    int printset = 0;
    uint32_t printelements = 100;
    Set command = set_empty();
    Stats stat;
    reset(&stat);
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch(opt) {
            case 'a':
                command = set_union(set_insert(command, 0), command);
                break;
            case 's':
                command = set_union(set_insert(command, 1), command);
                break;
            case 'b':
                command = set_union(set_insert(command, 2), command);
                break;
            case 'q':
                command = set_union(set_insert(command, 3), command);
                break;
            case 'h':
                command = set_union(set_insert(command, 4), command);
                break;
            case 'r': //seed
                seedtarget = strtoul(optarg, NULL, 10);
                if (seedtarget > 0 && seedtarget < 10000000000) {
                    seed = seedtarget;
                }
                else {
                    return 1;
                }
                break;
            case 'n': //size
                sizetarget = strtoul(optarg, NULL, 10);
                if (sizetarget >= 1 && sizetarget <= 250000000) {
                    size = sizetarget;
                }
                else {
                    return 1;
                }
                break;
            case 'p': //how many elements to print
                printset = 1;
                printelements = strtoul(optarg, NULL, 10);
                break;
            case 'H':
                printf("SYNOPSIS\n");
                printf("   A collection of comparison-based sorting algorithms.\n\n");
                printf("USAGE\n");
                printf("   ./sorting [-Hasbhq] [-n length] [-p elements] [-r seed]\n\n");
                printf("OPTIONS\n");
                printf("   -H              Display program help and usage.\n");
                printf("   -a              Enable all sorts.\n");
                printf("   -b              Enable Bubble Sort.\n");
                printf("   -h              Enable Heap Sort.\n");
                printf("   -q              Enable Quick Sort.\n");
                printf("   -s              Enable Shell Sort.\n");
                printf("   -n length       Specify number of array elements (default: 100).\n");
                printf("   -p elements     Specify number of elements to print (default: 100).\n");
                printf("   -r seed         Specify random seed (default: 13371453).\n");
                return 0;
                break;
        }
    }
    mtrand_seed(seed);
    uint32_t *arr = (uint32_t *) malloc(size * sizeof(uint32_t));

    uint32_t *arr2 = (uint32_t *) malloc(size * sizeof(uint32_t));
    uint32_t *arr3 = (uint32_t *) malloc(size * sizeof(uint32_t));
    uint32_t *arr4 = (uint32_t *) malloc(size * sizeof(uint32_t));
    for (uint32_t i = 0; i < size; i += 1) {
        uint32_t generate = mtrand_rand64() & 0x3fffffff; //have to bit mask the 64 bit down to 32 bit
        arr[i] = generate; //original array

        arr2[i] = generate; //copies for the -a function
        arr3[i] = generate;
        arr4[i] = generate;
    }
    if (set_member(command, 0)) { //-a option
        bubble_sort(&stat, arr, size);
        printf("Bubble Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size, stat.moves, stat.compares);
        reset(&stat);
        if (size < printelements) {
            printelements = size;
        }
        for (uint32_t i = 0; i < size; i += 5) {
            for (uint32_t j = i; j < i + 5;j +=1) {
                if (j == printelements) {
                    break;
                }
                printf("%13" PRIu32, arr[j]);
            }
            printf("\n");
        }

        heap_sort(&stat, arr2, size);
        printf("Heap Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size, stat.moves, stat.compares);
        reset(&stat);
        if (size < printelements) {
            printelements = size;
        }
        for (uint32_t i = 0; i < size; i += 5) {
            for (uint32_t j = i; j < i + 5;j +=1) {
                if (j == printelements) {
                    break;
                }
                printf("%13" PRIu32, arr2[j]);
            }
            printf("\n");
        }

        quick_sort(&stat, arr3, size);
        printf("Quick Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size, stat.moves, stat.compares);
        reset(&stat);
        if (size < printelements) {
            printelements = size;
        }
        for (uint32_t i = 0; i < size; i += 5) {
            for (uint32_t j = i; j < i + 5;j +=1) {
                if (j == printelements) {
                    break;
                }
                printf("%13" PRIu32, arr3[j]);
            }
            printf("\n");
        }

        shell_sort(&stat, arr4, size);
        printf("Shell Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size, stat.moves, stat.compares);
        reset(&stat);
        for (uint32_t i = 0; i < size; i += 5) {
            for (uint32_t j = i; j < i + 5;j +=1) {
                if (j == printelements) {
                    break;
                }
                printf("%13" PRIu32, arr4[j]);
            }
            printf("\n");
        }
    }
    else { //every other option for sorting
        if (set_member(command, 1)) {
            shell_sort(&stat, arr, size);
            if (printset == 1) {
                printf("Shell Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size, stat.moves, stat.compares);
                reset(&stat);
                if (size < printelements) {
                    printelements = size;
                }
                for (uint32_t i = 0; i < printelements; i += 5) {
                    for (uint32_t j = i; j < i + 5;j +=1) {
                        if (j == printelements) {
                            break;
                        }
                        printf("%13" PRIu32, arr[j]);
                    }
                    printf("\n");
                }
            }
        }
        if (set_member(command, 2)) {
            bubble_sort(&stat, arr, size);
            if (printset == 1) {
                printf("Bubble Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size, stat.moves, stat.compares);
                reset(&stat);
                if (size < printelements) {
                    printelements = size;
                }
                for (uint32_t i = 0; i < printelements; i += 5) {
                    for (uint32_t j = i; j < i + 5;j +=1) {
                        if (j == printelements) {
                            break;
                        }
                        printf("%13" PRIu32, arr[j]);
                    }
                    printf("\n");
                }
            }
        }
        if (set_member(command, 3)) {
            quick_sort(&stat, arr, size);
            if (printset == 1) {
                printf("Quick Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size, stat.moves, stat.compares);
                reset(&stat);
                if (size < printelements) {
                    printelements = size;
                }
                for (uint32_t i = 0; i < printelements; i += 5) {
                    for (uint32_t j = i; j < i + 5;j +=1) {
                        if (j == printelements) {
                            break;
                        }
                        printf("%13" PRIu32, arr[j]); 
                    }
                    printf("\n");
                }
            }
        }
        if (set_member(command, 4)) {
            heap_sort(&stat, arr, size);
            if (printset == 1) {
                printf("Heap Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size, stat.moves, stat.compares);
                reset(&stat);
                if (size < printelements) {
                    printelements = size;
                }
                for (uint32_t i = 0; i < printelements; i += 5) {
                    for (uint32_t j = i; j < i + 5;j +=1) {
                        if (j == printelements) {
                            break;
                        }
                        printf("%13" PRIu32, arr[j]); 
                    }
                    printf("\n");
                }
            }
        }
    }
    free(arr);
    arr = NULL;

    free(arr2);
    free(arr3);
    free(arr4);
    arr2 = NULL;
    arr3 = NULL;
    arr4 = NULL;
}
