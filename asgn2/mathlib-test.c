#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "mathlib.h"

#define OPTIONS "hascSCTl :"

int main(int argc, char **argv){
	int opt = 0;
	double mfv = 0;
	double test_input = 0;
	double mat_res = 0;
	while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
		switch (opt) {
		case 'a':
	// Run all test
   		// Check results and print
			printf("  x           sin              Library       Difference\n");
			printf("  -           ------           -------       ----------\n");

      for (test_input = 0 ; test_input <= 2*M_PI ; test_input = test_input + 0.05*M_PI) {
   		  mfv = my_sin(test_input);
			  mat_res = sin(test_input);
        printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", test_input, mfv, mat_res, (mfv - mat_res));
      }

      		// Check results and print
			printf("  x           cos              Library       Difference\n");
			printf("  -           ------           -------       ----------\n");

      for (test_input = 0 ; test_input <= 2*M_PI ; test_input = test_input + 0.05*M_PI) {
   		  mfv = my_cos(test_input);
			  mat_res = cos(test_input);
        printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", test_input, mfv, mat_res, (mfv - mat_res));
      }

		// Check results and print
			printf("  x           arcsin           Library       Difference\n");
			printf("  -           ------           -------       ----------\n");

      for (test_input = -1 ; test_input <= 1 ; test_input = test_input + 0.05) {
   		  mfv = my_arcsin(test_input);
			  mat_res = asin(test_input);
        printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", test_input, mfv, mat_res, (mfv - mat_res));
      }

   		// Check results and print
			printf("  x           arccos           Library       Difference\n");
			printf("  -           ------           -------       ----------\n");

      for (test_input = -1 ; test_input <= 1 ; test_input = test_input + 0.05) {
   		  mfv = my_arccos(test_input);
			  mat_res = acos(test_input);
        printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", test_input, mfv, mat_res, (mfv - mat_res));
      }

   		// Check results and print
			printf("  x           arctan           Library       Difference\n");
			printf("  -           ------           -------       ----------\n");

      for (test_input = 1 ; test_input <= 10 ; test_input = test_input + 0.05) {
   		  mfv = my_arctan(test_input);
			  mat_res = atan(test_input);
        printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", test_input, mfv, mat_res, (mfv - mat_res));
      }

		// Check results and print
			printf("  x           log              Library       Difference\n");
			printf("  -           ------           -------       ----------\n");

      for (test_input = 1 ; test_input <= 10 ; test_input = test_input + 0.05) {
   		  mfv = my_log(test_input);
			  mat_res = log(test_input);
        printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", test_input, mfv, mat_res, (mfv - mat_res));
      }

			break;

		case 's':
		// Check results and print
			printf("  x           sin              Library       Difference\n");
			printf("  -           ------           -------       ----------\n");

      for (test_input = 0 ; test_input <= 2*M_PI ; test_input = test_input + 0.05*M_PI) {
   		  mfv = my_sin(test_input);
			  mat_res = sin(test_input);
        printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", test_input, mfv, mat_res, (mfv - mat_res));
      }
			break;

		case 'c':
		// Check results and print
			printf("  x           cos              Library       Difference\n");
			printf("  -           ------           -------       ----------\n");

      for (test_input = 0 ; test_input <= 2*M_PI ; test_input = test_input + 0.05*M_PI) {
   		  mfv = my_cos(test_input);
			  mat_res = cos(test_input);
        printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", test_input, mfv, mat_res, (mfv - mat_res));
      }
			break;

		case 'S':
  		// Check results and print
			printf("  x           arcsin           Library       Difference\n");
			printf("  -           ------           -------       ----------\n");

      for (test_input = -1 ; test_input <= 1 ; test_input = test_input + 0.05) {
   		  mfv = my_arcsin(test_input);
			  mat_res = asin(test_input);
        printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", test_input, mfv, mat_res, (mfv - mat_res));
      }
			break;

		case 'C':
  		// Check results and print
			printf("  x           arccos           Library       Difference\n");
			printf("  -           ------           -------       ----------\n");

      for (test_input = -1 ; test_input <= 1 ; test_input = test_input + 0.05) {
   		  mfv = my_arccos(test_input);
			  mat_res = acos(test_input);
        printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", test_input, mfv, mat_res, (mfv - mat_res));
      }
			break;

		case 'T':
  		// Check results and print
			printf("  x           arctan           Library       Difference\n");
			printf("  -           ------           -------       ----------\n");

      for (test_input = 1 ; test_input <= 10 ; test_input = test_input + 0.05) {
   		  mfv = my_arctan(test_input);
			  mat_res = atan(test_input);
        printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", test_input, mfv, mat_res, (mfv - mat_res));
      }
			break;

		case 'l':
 		// Check results and print
			printf("  x           log              Library       Difference\n");
			printf("  -           ------           -------       ----------\n");
      for (test_input = 1 ; test_input <= 10 ; test_input = test_input + 0.05) {
   		  mfv = my_log(test_input);
			  mat_res = log(test_input);
        printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", test_input, mfv, mat_res, (mfv - mat_res));
      }
			break;

		case 'h':
	      printf("-a to run all tests. \n");
        printf("-s to run sin tests. \n");
        printf("-c to run cos tets. \n");
        printf("-S to run arcsin tests. \n");
        printf("-C to run arccos tests. \n");
        printf("-T to run arctan tests. \n");
        printf("-l to run log tests. \n");
			break;

		}
	}
	return 0;
}
