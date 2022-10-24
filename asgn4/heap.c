#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"
#include "heap.h"


uint32_t l_child (uint32_t n) {
    return (2 * n + 1);
}

uint32_t r_child (uint32_t n) {
    return (2 * n + 2);
}

uint32_t parent (uint32_t n) {
    return ((n - 1) / 2);
}

uint32_t up_heap(Stats *stats, uint32_t *a, uint32_t n) {
    uint32_t tmp;
    uint32_t m;

    //m = n;

    cmp(stats, 0, 0);
    while (n > 0 && a[n] > a[parent(n)]) {
        move(stats, 0);
        // Swap
        tmp = a[n];
        a[n] = a[parent(n)];
        a[parent(n)] = tmp;
        m = parent(n);
    }

    return m;
}

uint32_t down_heap(Stats *stats, uint32_t *a, uint32_t heap_size, uint32_t n) {
    uint32_t m;
    uint32_t tmp, bigger;

    m = 0;

    cmp(stats, 0, 0);
    while (l_child(m) < heap_size) {
        if (r_child(m) == heap_size) {
            bigger = l_child(m);
        }
        else {
            if (a[l_child(m)] > a[r_child(m)]) {
                bigger = l_child(m);
            }
            else {
                bigger = r_child(m);
            }
        }

        if (a[m] > a[bigger]) {
            m = n;
            break;
        }

        move(stats, 0);
        // Swap
        tmp = a[m];
        a[m] = a[bigger];
        a[bigger] = tmp;
        m = bigger;
    }

    return m;
}

void build_heap(Stats *stats, uint32_t *heap, uint32_t *a, uint32_t n_elements) {
    uint32_t n;

    memset(heap, 0, n_elements*sizeof(uint32_t)); // Init array with zero

    for (n = 0; n < n_elements; n++) {
        heap[n] = a[n];
        up_heap(stats, heap, n);
    }
}

void heap_sort(Stats *stats, uint32_t *arr, uint32_t n_elements) {
    uint32_t n;
    uint32_t *heap;
    uint32_t *sorted_list;

    // Allocate memory
    heap = (uint32_t *) malloc(n_elements*sizeof(uint32_t));
    sorted_list = (uint32_t *) malloc(n_elements*sizeof(uint32_t));

    build_heap(stats, heap, arr, n_elements);
    memset(sorted_list, 0, n_elements*sizeof(uint32_t)); // Init array with zero

    for (n = 0; n < n_elements; n++) {
        sorted_list[n] = heap[0];
        heap[0] = heap[n_elements - n - 1];
        down_heap(stats, heap, n_elements - n, n);
    }

    for (n = 0; n < n_elements; n++){
      arr[n] = sorted_list[n_elements-n-1];
    }

    // Release memory
    free(heap);
    free(sorted_list);

}
