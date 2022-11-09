//contains implementation of numbver theory functions
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <stdint.h>
#include <stdbool.h>
#include "randstate.h"
#include "numtheory.h"

//gmp_randstate_t state;


void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    mpz_rrandomb(p, state, bits + 1);

    while(!is_prime(p, iters)) {
        mpz_rrandomb(p, state, bits + 1);
    }

}


// p = base, d = exponent, n = modulus, out is return
void pow_mod(mpz_t o, mpz_t a, mpz_t d, mpz_t n) {
    mpz_t v, p, temp;
    mpz_inits(v, p, temp, NULL);
    mpz_set_ui(v, 1); // v = 1
    mpz_set(p, a); //p = a
    mpz_set(temp, d);

    while(mpz_cmp_ui(temp, 0) > 0) { //while d > 0
        if(mpz_odd_p(temp)) { //if d is odd
            mpz_mul(v, v, p); //v = v x p
            mpz_mod(v, v, n); //v = v mod n
        }
        mpz_mul(p, p, p); //p = p x p
        mpz_mod(p, p, n); //p = p mod n
        mpz_fdiv_q_ui(temp, temp, 2); //d = [d/2]
    }
    mpz_set(o, v);
    mpz_clears(v, p, temp, NULL); //make clean
    // mpz_clear(v);
    // mpz_clear(p);
    // mpz_clear(temp);

} 

//miller rabin (n,k)
bool is_prime(mpz_t n, uint64_t iters) {
    if(mpz_cmp_ui(n, 2) == 0 || mpz_cmp_ui(n, 3) == 0) {
        return true;
    }
    else if (mpz_even_p(n)|| mpz_cmp_ui(n, 3) < 0) { //elif n is even or n < 3
        return false; //means it is even, a negative num, or 1 which arent primes
    }

    mpz_t s, r, mf, temp; //mf is n - 1
    mpz_inits(s, r, mf, temp, NULL);
    mpz_sub_ui(mf, n, 1); //mf = n - 1

    mpz_set(r, mf);

    mpz_fdiv_q_ui(r, r, 2); // r = r/2
    mpz_mod_ui(temp, r, 2); //temp = r mod 2

    while(mpz_sgn(temp) == 0) { //sgn i sign, while its same as 0
        mpz_fdiv_q_ui(r, r, 2);
        mpz_mod_ui(temp, r, 2);
        mpz_add_ui(s, s, 1);
    } 

    //EVERYTHING above is for making sure s is at the right point and r is odd

    for(uint64_t i = 1; i < iters; i++) {
        mpz_t rv, y, nf; //random variable, n - 4
        mpz_inits(rv, y, nf, NULL);
        mpz_sub_ui(nf, n, 3);

        mpz_urandomm(rv, state, nf); //goes from 0 to size limit - 1
        mpz_add_ui(rv, rv, 2); //rv = rv - 2
        pow_mod(y, rv, r, n);

        if(mpz_cmp_ui(y, 1) != 0 && mpz_cmp(y, mf) != 0) {
            mpz_t j, sj;
            mpz_inits(j, sj, NULL);
            mpz_sub_ui(sj, s, 1);

            while(mpz_cmp(j, sj) <= 0 && mpz_cmp(y, mf) != 0) {
                mpz_t base;
                mpz_init(base);
                mpz_set_ui(base, 2);

                pow_mod(y, y, base, n); // y = powmod(y,2,n)

                if(mpz_cmp_ui(y, 1) == 0) {
                    mpz_clears(s, r, mf, temp, rv, nf, j, base, sj, NULL);
                    return false;
                }
                mpz_add_ui(j, j, 1); //j = j + 1
                mpz_clear(base);
            }

            if(mpz_cmp(y, mf) != 0) {
                mpz_clears(s, r, mf, temp, rv, nf, j, sj, NULL);
                return false;
            }
            mpz_clears(j, sj, NULL);
        }
        mpz_clears(rv, nf, y, NULL);
    }
    mpz_clears(s, r, mf, temp, NULL);
    return true;
}

//GCD (a,b)
void gcd(mpz_t d, mpz_t a, mpz_t b) {
    while (mpz_cmp_ui(b, 0) != 0) {
        mpz_t t;
        mpz_init(t); //intializing a variable t
        mpz_set(t, b); //t = b
        mpz_mod(b, a, b); // b <- a mod b
        mpz_set(a, t); //a = t
        
        mpz_clear(t);
    }
    mpz_set(d, a); //returning 
}

//Mod inverse (a,n)
void mod_inverse(mpz_t o, mpz_t a, mpz_t n) {
    mpz_t r, r_, t, t_; //
    mpz_inits(r, r_, t, t_, NULL); //intializing i and q, NULL exits the intialized functio
    mpz_set(r, n); // r = n
    mpz_set(r_, a); //r prime = a
    //inorder to set to int use set_ui
    mpz_set_ui(t, 0);
    mpz_set_ui(t_, 1);

    while(mpz_cmp_ui(r_, 0) != 0) {
        mpz_t q, temp;
        mpz_inits(q, temp, NULL);
        mpz_fdiv_q(q, r , r_);// q = (r / r prime) (floor div)

        mpz_set(temp, r_); //temp = r prime
        mpz_mul(r_, q, r_); //r prime = q x r rpime
        mpz_sub(r_, r, r_); //r prime = r - r_prime
        mpz_set(r, temp); //r = temp

        mpz_set(temp, t_); //temp = t prime
        mpz_mul(t_, q, t_); //t prime = q x t rpime
        mpz_sub(t_, t, t_); //t prime = t - t prime
        mpz_set(t, temp); //t = temp

        mpz_clear(q); //clearing memory
        mpz_clear(temp); //clearing memory
    }

    if(mpz_cmp_ui(r, 1) > 0) { //r > 1
        mpz_set_ui(o, 0); //return no inverse
        mpz_clears(r, r_, t, t_, NULL); //clears memory
        // mpz_clear(r);
        // mpz_clear(r_);
        // mpz_clear(t);
        // mpz_clear(t_); 
        return;
    }

    if(mpz_cmp_ui(t, 0) < 0) { //t < 1
        mpz_add(t, t , n); //t = t + n
    }

    mpz_set(o, t); //RETURN

    mpz_clears(r, r_, t, t_, NULL); //clear memory
    // mpz_clear(r);
    // mpz_clear(r_);
    // mpz_clear(t);
    // mpz_clear(t_); 
}
