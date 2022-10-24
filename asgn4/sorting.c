#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <inttypes.h>
#include "mtrand.h"
#include "stats.h"
#include "bubble.h"
#include "shell.h"
#include "quick.h"
#include "heap.h"

#define MAX_RANDOM_NUM 0x3FFFFFFF // Mask for 30 bits

#define OPTIONS "r:n:p:asbqhH"

void print_results(char *sortType, Stats *stats, uint32_t *arr, uint32_t n_elements, int printArr) {
  int i;

  printf("%s, %d elements, %lu moves, %lu compares", sortType, n_elements, stats->moves, stats->compares);

  if (printArr) {
    for (i = 0; i < printArr; i++) {
      if (!(i % 5)) {
        printf("\n");
      }
      printf("%13"PRIu32"", arr[i]);
    }
  }
  printf("\n");
}

int main(int argc, char **argv){
	  int opt = 0;
    int i;
    int n_elements = 12; //100
    int randSeed = 13371453;
    int printArr = 100;
    int err_in = 0;
    int en_s_sort, en_b_sort, en_q_sort, en_h_sort = 0;
    Stats *stats;
    Stats sortstats;
    uint32_t *arrayToSort_b;
    uint32_t *arrayToSort_s;
    uint32_t *arrayToSort_q;
    uint32_t *arrayToSort_h;

    en_s_sort = en_b_sort = en_q_sort = en_h_sort = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
      // Parse input
      for(optind = 1; optind < argc; optind++){
        if (!strncmp(argv[optind], "-r", 2)) {
          randSeed = strtoul(argv[optind+1], NULL, 0);
        }
        else if (!strncmp(argv[optind], "-n", 2)) {
          n_elements = strtoul(argv[optind+1], NULL, 0);
        }
        else if (!strncmp(argv[optind], "-p", 2)) {
          printArr = strtoul(argv[optind+1], NULL, 0);
        }
        else if (!strncmp(argv[optind], "-a", 2)) {
          en_s_sort = en_b_sort = en_q_sort = en_h_sort = 1;
        }
        else if (!strncmp(argv[optind], "-H", 2)) {
          printf("SYNOPSIS\n");
          printf("   A collection of comparison-based sorting algorithms.\n");
          printf("\nUSAGE\n");
          printf("   ./sorting [-Hasbhq] [-n length] [-p elements] [-r seed]\n");
          printf("\nOPTIONS\n");
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
        } else {
          //printf("\nargc %s len %lu\n",argv[optind], strlen(argv[optind]));
        }

        if (!strncmp(argv[optind], "-", 1) && (
                argv[optind][strlen(argv[optind])-1] == 's' || argv[optind][strlen(argv[optind])-2] == 's' ||
                argv[optind][strlen(argv[optind])-3] == 's' || argv[optind][strlen(argv[optind])-4] == 's' )) {
          //printf("\nargc %s\n",argv[optind]);
          en_s_sort = 1;
        }

        if (!strncmp(argv[optind], "-", 1) && (
                argv[optind][strlen(argv[optind])-1] == 'b' || argv[optind][strlen(argv[optind])-2] == 'b' ||
                argv[optind][strlen(argv[optind])-3] == 'b' || argv[optind][strlen(argv[optind])-4] == 'b' )) {
          //printf("\nargc %s\n",argv[optind]);
          en_b_sort = 1;
        }

        if (!strncmp(argv[optind], "-", 1) && (
                argv[optind][strlen(argv[optind])-1] == 'q' || argv[optind][strlen(argv[optind])-2] == 'q' ||
                argv[optind][strlen(argv[optind])-3] == 'q' || argv[optind][strlen(argv[optind])-4] == 'q' )) {
          //printf("\nargc %s\n",argv[optind]);
          en_q_sort = 1;
        }

        if (!strncmp(argv[optind], "-", 1) && (
                argv[optind][strlen(argv[optind])-1] == 'h' || argv[optind][strlen(argv[optind])-2] == 'h' ||
                argv[optind][strlen(argv[optind])-3] == 'h' || argv[optind][strlen(argv[optind])-4] == 'h' )) {
           //printf("\nargc %s\n",argv[optind]);
          en_h_sort = 1;
        }

      }

      if (opt == '?') {
        //printf("\n opt %c\n", opt);
        err_in = 1;
      }

    }

   // Check boundary
   if (n_elements > 250000000 || n_elements < 1 || randSeed < 0 || err_in) {
    printf("\nError\n");
      return 1;
    }
    else {
      // Limit to max number of element
      if (printArr > n_elements) {
        printArr = n_elements;
      }

      stats = &sortstats;

      mtrand_seed(randSeed);

      // Allocate memory
      arrayToSort_b = (uint32_t *) malloc(n_elements*sizeof(uint32_t));
      arrayToSort_s = (uint32_t *) malloc(n_elements*sizeof(uint32_t));
      arrayToSort_q = (uint32_t *) malloc(n_elements*sizeof(uint32_t));
      arrayToSort_h = (uint32_t *) malloc(n_elements*sizeof(uint32_t));

      // Generate random array
      for (i = 0; i < n_elements; i++) {
        arrayToSort_b[i] = mtrand_rand64() & MAX_RANDOM_NUM;
        arrayToSort_s[i] = arrayToSort_q[i] = arrayToSort_h[i] = arrayToSort_b[i];
      }
      //print_results("Array to sort", stats, arrayToSort_b, n_elements, printArr);

      // Sort
      if (en_b_sort) {
        reset(stats);
        bubble_sort(stats, arrayToSort_b, n_elements);
        print_results("Bubble Sort", stats, arrayToSort_b, n_elements, printArr);
      }

      if (en_h_sort) {
        reset(stats);
        heap_sort(stats, arrayToSort_h, n_elements);
        print_results("Heap Sort", stats, arrayToSort_h, n_elements, printArr);
      }

      if (en_q_sort) {
        reset(stats);
        quick_sort(stats, arrayToSort_q, n_elements);
        print_results("Quick Sort", stats, arrayToSort_q, n_elements, printArr);
      }

      if (en_s_sort) {
        reset(stats);
        shell_sort(stats, arrayToSort_s, n_elements);
        print_results("Shell Sort", stats, arrayToSort_s, n_elements, printArr);
      }

      // Release memory
      free(arrayToSort_b);
      free(arrayToSort_s);
      free(arrayToSort_q);
      free(arrayToSort_h);

      return 0;
    }


}
