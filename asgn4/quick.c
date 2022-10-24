#include <stdio.h>
#include <stdlib.h>
#include "stats.h"
#include "shell.h"
#include "quick.h"

#define SMALL 8


uint32_t find_pivot(Stats *stats, uint32_t *arr, int32_t left, int32_t right) {

  uint32_t pivot;
  int32_t j;
  uint32_t tempArr;
  int32_t i;

  pivot = arr[right];


  i = (left-1); 

  for (j=left; j<right; j++) {
    cmp(stats, 0, 0);
    if (arr[j] <= pivot) {
      move(stats, 0);
      i++;
      // Swap array
      tempArr  = arr[j];
      arr[j]   = arr[i];
      arr[i]   = tempArr;
    }
  }

  tempArr  = arr[i+1];
  arr[i+1] = arr[right];
  arr[right] = tempArr;

  return (i+1);

}

void q_sort(Stats *stats, uint32_t *arr, int32_t left, int32_t right) {

  uint32_t pivot_index;

  if (left < right) {
    pivot_index = find_pivot(stats, arr, left, right);

    q_sort(stats, arr, left, pivot_index-1);

    q_sort(stats, arr, pivot_index+1, right);

  }

}

void quick_sort(Stats *stats, uint32_t *arr, uint32_t n_elements) {

  //quick sorting
  if (n_elements < SMALL) {
    shell_sort(stats, arr, n_elements);
  }
  else {
    // Call q_sort
    q_sort(stats, arr, 0, n_elements - 1);
  }

}

