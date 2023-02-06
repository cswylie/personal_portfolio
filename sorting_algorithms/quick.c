#include <stdlib.h>
#include <stdio.h>
#include "stats.h"
#include "shell.h"

void quick_sort(Stats *stats, uint32_t *arr, uint32_t n_elements) {
    if (n_elements < 8) {
        shell_sort(stats, arr, n_elements);
        return;
    }
    uint32_t pivot = (arr[0] + arr[n_elements/2] + arr[n_elements-1])/3;
    uint32_t count = 0; //First segment the initial array into stuff greater than the pivot and stuff less than it
    for (uint32_t i = 0; i < n_elements; i +=1) {
        if (cmp(stats, arr[i], pivot) == -1) {
            swap(stats, &arr[count], &arr[i]);
            count += 1;
        }
    }
    quick_sort(stats, arr, count);
    quick_sort(stats, &arr[count], n_elements - count);
}
