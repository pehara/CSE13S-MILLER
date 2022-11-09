//contains implementation and main() function for decrypt program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <gmp.h>
#include <time.h>
#include <stdbool.h>
#include "randstate.h"
#include "numtheory.h"
#include "rsa.h"

#define OPTIONS "i:o:n:vh"

int main(int argc, char **argv){
    int opt = 0;
    char* input_file = "in_file.txt"; // Default stdin
    char* output_file = "out_file.txt"; // Default stdout
    char* private_key = "rsa.priv";
    int verb_out = 0;

    int input_file_k = 0;
    int output_file_k = 0;
    
    FILE * input_file_f;
    FILE * out_file_f;
    FILE * private_key_f;

    mpz_t n, d;
    mpz_inits(n, d, NULL);

    // Process input
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        // Parse input
        switch (opt) {
            case 'i':
            input_file = optarg;
            input_file_k = true;
            break;

            case 'o':
            output_file = optarg; 
            output_file_k = true;

            break;

            case 'n':
            private_key = optarg; 
            break;

            case 'v':
            verb_out = true;
            break;

            case 'h':
            printf("-i:specifies the input file to decrypt(default:stdin)");
            printf("\n-o:specifies the output file to decrypt(default:stdout)");
            printf("\n-n:specifies the file containing the private key(default:rsa.priv)");
            printf("\n-v enables verbose output");
            printf("\n-h displays program synopsis and usage\n");
            return 0;
            break;
        }
    }

    //opens file and check for erros
    //in file
    if (input_file_k == true) {
        input_file_f = fopen (input_file, "r+");
    }
    else {
        input_file_f = stdin;
    }

    if (input_file_f == NULL) {
        printf("no such %s file.\n", input_file);
        return 0;
    }
    //out file
    if (output_file_k == true) {
        out_file_f = fopen (output_file, "w+");
    }
    else {
        out_file_f = stdout;
    }

    if (out_file_f == NULL) {
        printf("no such %s file.\n", output_file);
        return 0;
    }

    out_file_f = fopen (output_file, "w+");
    if (out_file_f == NULL) {
        printf("no such %s file.\n", output_file);
        return 0;
    }

    private_key_f = fopen (private_key, "r+");
    if (private_key_f == NULL) {
        printf("no such %s file.\n", private_key);
        return 0;
    }

    rsa_read_priv(n, d, private_key_f);

    //print verbose out
    if (verb_out) {
        gmp_printf("n = %Zd\n", n);
        gmp_printf("d = %Zd\n", d);
    }

    // Decrypt file
    rsa_decrypt_file(input_file_f, out_file_f, n, d);

    // Clear mpz
    mpz_clear(n);
    mpz_clear(d);

    // Close files
    fclose(input_file_f);
    fclose(out_file_f);
    fclose(private_key_f);

    return 0;
}
