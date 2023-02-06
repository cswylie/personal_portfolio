#include <stdlib.h>
#include "stats.h"

int next_gap(int a) {
        if (a == 1) { //means we are are done with generating the gaps
            return 0;
        }
        if (a <=2) {
            return 1;
        }
        else{
            return (5*a)/11;
        }
        return 0;
    }

void shell_sort(Stats *stats, uint32_t *arr, uint32_t n_elements) {
    int start= (5*n_elements)/11;
    for (uint32_t gap = start; gap > 0; gap=next_gap(gap)) {
        for (uint32_t i = gap; i < n_elements; i += 1) {
            uint32_t j = i; 
            uint32_t temp = move(stats, arr[i]);
            while (j >= gap && cmp(stats, temp, arr[j-gap]) == -1) {
                arr[j] = move(stats, arr[j-gap]);
                move(stats, arr[j]);
                j-=gap;
            }
            arr[j] = move(stats, temp);
            move(stats, arr[j]);
        }
    }
}
