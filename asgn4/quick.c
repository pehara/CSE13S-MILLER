#include <stdio.h>
#include <stdlib.h>
#include "stats.h"
#include "shell.h"
#include "quick.h"

#define SMALL 8


uint32_t find_pivot(Stats *stats, uint32_t *arr, int32_t left, int32_t right) {

  // Select staring pivot
  uint32_t pivot;
  int32_t j;
  uint32_t tempArr;
  int32_t i;

  pivot = arr[right];
  //pivot = arr[left] + arr[right/2];

  i = (left-1); // Start from the lowest

  for (j=left; j<right; j++) {
    cmp(stats, 0, 0);
    if (arr[j] <= pivot) {
      move(stats, 0);
      i++;
      // Swap array
      tempArr  = arr[j]; // Store in temporary array before swap
      arr[j]   = arr[i];
      arr[i]   = tempArr;
    }
  }

  // swap with the greater element
  tempArr  = arr[i+1]; // Store in temporary array before swap
  arr[i+1] = arr[right];
  arr[right] = tempArr;

  return (i+1);

}

void q_sort(Stats *stats, uint32_t *arr, int32_t left, int32_t right) {

  uint32_t pivot_index;

  if (left < right) {
    pivot_index = find_pivot(stats, arr, left, right);

    // Recursive call of left piot
    //printf("\nq sort left [%d] pivot_index [%d]", left, pivot_index-1);
    q_sort(stats, arr, left, pivot_index-1);

    // Recursive call of left piot
    //printf("\nq sort right [%d] pivot_index [%d]", right, pivot_index+1);
    q_sort(stats, arr, pivot_index+1, right);

  }

}

void quick_sort(Stats *stats, uint32_t *arr, uint32_t n_elements) {

  //quick sorting
  if (n_elements < SMALL) {
    shell_sort(stats, arr, n_elements);
  }

  // Call q_sort
  q_sort(stats, arr, 0, n_elements - 1);

}

