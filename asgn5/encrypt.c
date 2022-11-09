//contains the implementation and main() function for the encrypt program
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

//doesnt make a pub key
//returns 0 for all the options 

#define OPTIONS "i:o:n:vh"

int main(int argc, char **argv){
    int opt = 0;
    char* input_file = "in_file_e.txt"; // Default stdin
    char* output_file = "out_file_e.txt"; // Default stdout
    char* public_key = "rsa.pub";
    int verb_out = 0;
    int input_file_k = 0;
    int output_file_k = 0;

    FILE * input_file_f;
    FILE * out_file_f;
    FILE * public_key_f; //public key file

    mpz_t n, e, s;
    mpz_t user_name;
    mpz_inits(n, e, s, user_name, NULL);

    char* username;
    username = (char*) malloc(32*sizeof(char));
    memset(username, '0', 32);
    //arrayToSort_b = (uint32_t *) malloc(n_elements*sizeof(uint32_t));

    // Process input
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        // Parse input
        
        switch (opt) {
            case 'i':
            input_file = (optarg);
            input_file_k = true;
            break;

            case 'o':
            output_file = (optarg);
            output_file_k = true;
            break;

            case 'n':
            public_key = (optarg);
            break;

            case 'v':
            verb_out = true;
            break;

            case 'h':
            printf("SYNOPSIS\n");
            printf("Encrypts data using RSA encryption.\n");
            printf("Encrypted data is decrypted by the decrypt program.\n\n");
            printf("USAGE\n");
            printf("./encrypt [-h] [-v] [-i input file name] [-o output file name]\n\n");
            printf("OPTIONS\n");
            printf("   -i specifies the input file to encrypt (default: stdin).");
            printf("\n   -o specifies the out put file to encrypt (default:stdout).");
            printf("\n   -n specifies the file containing the public key (default:rsa.pub)");
            printf("\n   -v enables verbose output");
            printf("\n   -h displays program synopsis and usage\n");
            return 0;
            break;
        }
    }

    //opens file and check for errors
    //input file
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

    //output file
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

    public_key_f = fopen (public_key, "r+");
    if (public_key_f == NULL) {
        printf("no such %s file.\n", public_key);
        return 0;
    }

    //read public key from the file
    rsa_read_pub(n, e, s, username, public_key_f); 

    //print verbose out
    if (verb_out) {
        printf("username = %s\n", username);
        gmp_printf("s = %Zd\n", s);
        gmp_printf("n = %Zd\n", n);
        gmp_printf("e = %Zd\n", e);
    }

    //convert user name
    mpz_set_str(user_name, username, 62);

    if (!rsa_verify(user_name, s, e, n)) {
        printf("signature couldn’t be verified\n");
    }

    rsa_encrypt_file(input_file_f, out_file_f, n, e);

    //clear mpz
    mpz_clear(n);
    mpz_clear(e);
    mpz_clear(s);
    mpz_clear(user_name);

    free(username);
    //close files
    fclose(input_file_f);
    fclose(out_file_f);
    fclose(public_key_f);

    return 0;
}
