#include <stdio.h>
#include <stdlib.h>
#include "stats.h"
#include "bubble.h"

void bubble_sort(Stats *stats, uint32_t *arr, uint32_t n_elements) {
    uint32_t i;
    uint32_t j;
    uint32_t tempArr;
    int swapped;

    //bubble sorting
    for (i = 0; i < n_elements; i++) {
        swapped = 0;
        for (j = n_elements - 1; j > i; j--) {
            cmp(stats, 0, 0);
            if (arr[j] < arr[j - 1]) {
                move(stats, 0);
                tempArr = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = tempArr;
                swapped = 1;
            }
        }
        if (!swapped){
            break;
        }
    }

}
