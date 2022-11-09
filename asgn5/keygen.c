//contains the implementation and main() keygen program
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

#define OPTIONS "bindsvh"

int main (int argc, char **argv) {
    int opt = 0;
    int min_bits = 1024;
    int miller_r = 50;
    char* public_key = "rsa.pub";
    char* private_key = "rsa.priv";
    int ran_seed = time(NULL); //needs header file
    int verb_out = 0;
    FILE * public_key_f; //public key file
    FILE * private_key_f; //private key file

    char* username;

    //public key
    mpz_t p_pub; 
    mpz_t n_pub; 
    mpz_t e_pub;
    mpz_t d_priv;
    mpz_t user_signature;
    mpz_t user_name;
    mpz_t q_pub;

    mpz_inits(p_pub, n_pub, e_pub, d_priv, user_signature, user_name, q_pub, NULL);

    //process input
    while ((opt = getopt( argc, argv, OPTIONS)) != -1) { 
        //parse input 
        //switch case for everything below
        switch (opt) {
            case 'b':
            min_bits = atoi(optarg);
            break;

            case 'i':
            miller_r = atoi(optarg);
            break;

            case 'n':
            public_key_f = fopen(optarg, "w");
            break;

            case 'd':
            private_key_f = fopen(optarg, "w");
            break;

            case 's':
            ran_seed = atoi(optarg);
            break;

            case 'v':
            verb_out = true;
            break;

            case 'h':
            printf("Usage ./keygen [options]\n");
            printf("./keygen generates a public / private key pair, placing the keys into the public and private key files as specified below. The keys have a modulus (n) whose length is specified in the program options.\n\n");
            printf("USAGE\n");
            printf("./keygen [-h] [-v] [-n filename] [-d filename]  [-s seed] \n\n");
            printf("OPTIONS\n");
            printf("   -s specifies the random seed for the random state initialization (default: the seconds since the UNIX epoch, given by time(NULL))");
            printf("\n   -b specifies the minimum bits needed for the public modulus n");
            printf("\n   -i specifies the number of Miller-Rabin iterations for testing primes (default:50)");
            printf("\n   -n pbfile:specifies the public key file (default:rsa.pub)");
            printf("\n   -d pvfile:specifies the privatekey file (default:rsa.priv)");
            printf("\n   -v enables verbose output");
            printf("\n   -h displays program synopsis and usage\n");
            return 0;
            break;

        }
    }

    //opens file and check for errors
    public_key_f = fopen (public_key, "w+");
    if (public_key_f == NULL) {
        printf("no such %s file.\n", public_key);
        return 0;
    }

    //add fchmod and fileno
    if (fileno(public_key_f) > 0) {
        fchmod(fileno(public_key_f), S_IRUSR | S_IWUSR); /*Allow read and write by the owner/user 0600*/
    }
    else {
        printf("no such %s file.\n", public_key);
    }

    //opens file and check for erros
    private_key_f= fopen (private_key, "w+");
    if (private_key_f == NULL) {
        printf("error with %s file.\n", private_key);
        return 0;
    }

    //add fchmod and fileno
    if (fileno(private_key_f) > 0) {
        fchmod(fileno(private_key_f), S_IRUSR | S_IWUSR); // Allow read and write by the owner/user 0600
    }
    else {
        printf("error with %s file.\n", private_key);
    }
    
    //initiate theeee random state
    randstate_init(ran_seed);

    //make RSA keys
    rsa_make_pub(p_pub, q_pub, n_pub, e_pub, min_bits, miller_r);
    rsa_make_priv(d_priv, e_pub, p_pub, q_pub);

    //get the user name from the environment and convert
    username = getenv("USER");
    mpz_set_str(user_name, username, 62);

    //compute user signature
    rsa_sign(user_signature, user_name, d_priv, n_pub);

    rsa_write_pub(n_pub, e_pub, user_signature, username, public_key_f);
    rsa_write_priv(n_pub, d_priv, private_key_f);

    //print verbose out
    if (verb_out) {
        printf("username: %s\n", username);
        gmp_printf("the signature s: %Zd\n", user_signature);
        gmp_printf("the first large prime p: %Zd\n", p_pub);
        gmp_printf("the second large prime: %Zd\n", q_pub);
        gmp_printf("the public modulus n: %Zd\n", n_pub);
        gmp_printf("the public exponent e: %Zd\n", e_pub);
        gmp_printf("the private key d: %Zd\n", d_priv);
    }

    //clean up
    randstate_clear();

    //clear mpz
    mpz_clears(p_pub, q_pub, n_pub, e_pub, d_priv, user_signature, user_name, NULL);

    //close files
    fclose(public_key_f);
    fclose(private_key_f);

    return 0;

}
