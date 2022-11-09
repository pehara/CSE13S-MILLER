//this specfies the interface for the RSA library
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
#include <math.h>
#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"

#define EOF (-1)


void lcm(mpz_t o, mpz_t p,  mpz_t q) {
    mpz_t t, r, temp, tempp, tempq;
    mpz_inits(t, r, temp, tempp, tempq, NULL);
    mpz_set(tempp, p);
    mpz_set(tempq, q);

    gcd(r, tempp, tempq);

    mpz_mul(temp, p, q);// temp = p x q
    mpz_abs(temp, temp);// temp = abs temp
    mpz_fdiv_q(t, temp, r);// t = temp/r
    //t = abs(p * q) / r;

    mpz_set(o, t);
    mpz_clears(temp, t, r, tempp, tempq, NULL); //clear temp here or no??
}

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    mpz_t prime1, prime2, lamda, ran_num, lamda_gcd;
    mpz_inits (prime1, prime2, lamda, ran_num, lamda_gcd, NULL);
    uint64_t r_bits = (rand() % (nbits/2)) + nbits/4;

    make_prime(p, r_bits, iters);
    make_prime(q, nbits - r_bits, iters);

    // p = make_prime(prime1, nbits, iters);
    // q = make_prime(prime2, nbits, iters);
    mpz_sub_ui(prime1, p, 1);

    mpz_sub_ui(prime2, q, 1);
    lcm(lamda, prime1, prime2);
    //gmp_printf("prime 1 = %Zx, prime2 = %Zx\n", prime1, prime2);
    //gmp_printf("lcm = %Zx\n", lamda);
    while (mpz_cmp_ui(lamda_gcd, 1) != 0) {
        mpz_t temp_ran, temp_lamda;
        mpz_inits(temp_ran, temp_lamda, NULL);
        //lcm(lamda, prime1, prime2);
        //lamda = lcm(p-1, q-1);
        // Generate random number
        mpz_urandomb(ran_num, state, nbits);
        mpz_set(temp_ran, ran_num);
        mpz_set(temp_lamda, lamda);
        gcd(lamda_gcd, temp_ran, temp_lamda);
        //gmp_printf("gcd = %Zx\n", lamda_gcd);
        
        mpz_clears(temp_lamda, temp_ran, NULL);
    }

    // n = p * q;
    // e = lamda_gcd;

    mpz_mul(n, p, q);
    mpz_set(e, ran_num);

    mpz_clears(prime1, prime2, lamda, ran_num, lamda_gcd, NULL);
 
    //printf("\n check make 5\n");
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t lamda, prime1, prime2;
    mpz_inits(lamda, prime1, prime2, NULL);

    mpz_sub_ui(prime1, p, 1);
    mpz_sub_ui(prime2, q, 1);
    lcm(lamda, prime1, prime2);
    //lamda_lcm = lcm(p-1, q-1);

    mod_inverse(d, e, lamda);

    mpz_clears(lamda, prime1, prime2, NULL);
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {

    gmp_fprintf(pbfile,"%Zx\n",n);
    gmp_fprintf(pbfile,"%Zx\n",e);
    gmp_fprintf(pbfile,"%Zx\n",s);
    fprintf(pbfile,"%s\n",username);

}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {

    gmp_fscanf(pbfile, "%Zx\n", n);
    gmp_fscanf(pbfile, "%Zx\n", e);
    gmp_fscanf(pbfile, "%Zx\n", s);
    fscanf(pbfile, "%s\n", username);

}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile,"%Zx\n",n);
    gmp_fprintf(pvfile,"%Zx\n",d);
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n", n);
    gmp_fscanf(pvfile, "%Zx\n", d);
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    mpz_t a;
    mpz_init(a);

    pow_mod(a, m, e, n);
    
    mpz_set(c, a);
    
    mpz_clear(a);
    // c = a;
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    uint64_t c;
    int k = 2;
    mpz_t m, m_e, div;
    mpz_inits(m, m_e, div, NULL);

    //n_dob = mpz_get_d(n);
    if (mpz_cmp_ui(n, 1) > 0) {
        k = ((mpz_sizeinbase(n, 2) - 1) / 8);
    }

    //allocate memory
    uint8_t* array_block = (uint8_t *) malloc(k*sizeof(uint8_t));

    //set zeroth byte
    array_block[0] = 0xFF;

    //while (c != EOF) { //error 2
    while ((c = fread(array_block + 1, sizeof(uint8_t), k - 1, infile)) > 0 ) {

        // Convert
        mpz_import(m, c + 1, 1, sizeof(uint8_t), 1, 0, array_block);
        // RSA encrypt
        rsa_encrypt(m_e, m, e, n);
        // Write encrypted message to a file
        gmp_fprintf(outfile,"%Zx\n",m_e);

        for (int i = 1; i < k; i++) {
            array_block[i] = 0;
        }
    }

    free(array_block);

    mpz_clears(m, m_e, NULL);
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    mpz_t a;
    mpz_init(a);

    pow_mod(a, c, d, n);
    mpz_set(m, a);

    mpz_clear(a);
    //m = a;
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    uint64_t jj;
    int k = 2;
    mpz_t c, b;
    mpz_inits(c, b, NULL);

    if (mpz_cmp_ui(n, 1) > 0) {
        k = ((mpz_sizeinbase(n, 2) - 1) / 8);
    }

    // Allocate memory
    uint8_t* array_block = (uint8_t *) malloc(k*sizeof(uint8_t));


    // Scan file
    while ( gmp_fscanf(infile, "%Zx\n", c) != EOF) {
        jj = ((mpz_sizeinbase(c, 2)) / 8);
        // Convert
        rsa_decrypt(b, c, d, n);

        mpz_export(array_block, &jj, 1, sizeof(uint8_t), 1, 0, b);
        // Write out to the file
        fwrite(array_block + 1, sizeof(uint8_t), jj - 1, outfile);
        for (uint64_t i = 1; i < jj; i++) {
            array_block[i] = 0;
        }
    }

    free(array_block);

    // mpz_set(c, d); //returning

    mpz_clears(c, b, NULL);

}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    mpz_t a;
    mpz_init(a);

    pow_mod(a, m, d, n);
    mpz_set(s, a);
    //s = a;
    mpz_clear(a);
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {

    mpz_t a, b;
    mpz_inits(a, b, NULL);

    pow_mod(a, s, e, n);
    // pow_mod(b, m, e, n);

    //if (a == b)
    if(mpz_cmp(m, a) == 0) {
        return true;
    }
    else {
        return false;
    }
    mpz_clears(a, b, NULL);

}
//clear memory
