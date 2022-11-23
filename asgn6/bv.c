//Contains the implementation of the bit vector ADT.
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//#include "bf.c"
#include "bv.h"

struct BitVector {
    uint32_t length;
    uint64_t *vector;
};

BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    if (bv) {
        bv->length = length;
        bv->vector = (uint64_t *) malloc((length / 64) * sizeof(uint64_t));
    }
    else {
        free(bv);
        bv = NULL;
    }
    return bv;
}

//destructor for bit vector
void bv_delete(BitVector **bv) {
    free(*bv); //* de refrences, & gets the address of the pointer
    bv = NULL;
}

//returns length of bit vector
uint32_t bv_length(BitVector *bv) {
    return (bv->length);
}

//sets the ith bit in a bit vector
void bv_set_bit(BitVector *bv, uint32_t i) {
    bv->vector[i/64] = bv->vector[i/64] | (1 << (i%64)); //invalid operands ERROR
}

//clears the ith bit in a bit vector
void bv_clr_bit(BitVector *bv, uint32_t i) {
    bv->vector[i/64] = bv->vector[i/64] & ~(1 << (i%64)); //invalid operands ERROR
}

//returns the ith bit in a bit vetcor
uint8_t bv_get_bit(BitVector *bv, uint32_t i) {
    return (bv->vector[i/64] & (1 << (i%64))); //invalid operands ERROR
}

//debug function
void bv_print(BitVector *bv) {
    printf("length %u, vector %lu\n", bv->length, *bv->vector);
}
