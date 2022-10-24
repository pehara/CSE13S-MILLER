#include <stdio.h>
#include <stdlib.h>
#include "stats.h"

uint32_t next_gap(uint32_t n) {
    uint32_t a;

    if (n > 1) {
        if (n <= 2) {
            a = 1;
        }
        else {
            a = (5 * n) / 11;
        }
    }
    else {
        a = 1;
    }

    return a;
}

void shell_sort(Stats *stats, uint32_t *arr, uint32_t n_elements) {
    uint32_t i;
    uint32_t j;
    uint32_t tempArr;
    
    uint32_t gap;

    //shell sorting
    for (gap = n_elements - 1; gap > 0; gap = next_gap(gap)) {
        for (i = gap; i < n_elements; i++) {
            j = i;
            tempArr = arr[i];
            cmp(stats, 0, 0);
            while (j >= gap && tempArr < arr[j - gap]) {
                move(stats, 0);
                arr[j] = arr[j - gap];
                j = j - gap;
            }
            arr[j] = tempArr;
        }

        if (gap == 1) {
            break;
        }
    }

}
