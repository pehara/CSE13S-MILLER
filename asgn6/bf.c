//Contains the implementation of the Bloom filter ADT.
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bv.h"
#include "bf.h"
#include "city.h"

//extern struct BitVector;

#define N_HASHES 5
struct BloomFilter {
    uint64_t salts[N_HASHES]; //salts for five hash functions
    uint32_t n_keys;
    uint32_t n_hits;
    uint32_t n_misses;
    uint32_t n_bits_examined;
    BitVector *filter;
};

static uint64_t default_salts [] = {
    0x5adf08ae86d36f21 ,
    0x419d292ea2ffd49e ,
    0x50d8bb08de3818df ,
    0x272347aea4045dd5 ,
    0x7c8e16f768811a21
};

BloomFilter *bf_create(uint32_t size) {

    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        bf->n_keys = bf->n_hits = 0;
        bf->n_misses = bf->n_bits_examined = 0;
        for (int i = 0; i < N_HASHES; i++) {
            bf->salts[i] = default_salts[i];
        }
        bf->filter = bv_create(size);
        if (bf->filter == NULL) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

//seg dump here
void bf_delete(BloomFilter **bf) {
    bv_delete(&(*bf)->filter);
    free(*bf);
    *bf = NULL;
}

uint32_t bf_size(BloomFilter *bf) {
    return (bv_length(bf->filter));
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    for (int i = 0; i < N_HASHES; i++) {
        bf->salts[i] = hash(bf->salts[i], oldspeak); // default salts maybe
        uint64_t p = hash(bf->salts[i], oldspeak) % bv_length(bf->filter); // default salts maybe
        bv_set_bit(bf->filter, p);
        //uint64_t p = hash(bf->salts[i], oldspeak); // default salts maybe
        //bf->salts[i] = p;
    }
    bf->n_keys++;
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
	bf->n_bits_examined++;
	
    for (int i = 0; i < N_HASHES; i++) {
        uint64_t p = hash(bf->salts[i], oldspeak) % bv_length(bf->filter);
        if (bv_get_bit(bf->filter, p) == 0) {
        	bf->n_misses++;
            return false;
        }
    }
    bf->n_hits++;
    return true;
}

//returns num of set bits in filter
uint32_t bf_count(BloomFilter *bf) {
    uint32_t i;
    uint32_t count = 0;
    for (i = 0; i < bf_size(bf); i++) {
        if (bv_get_bit(bf->filter, i)) {
            count = count + 1;
        }
    }
    return count;
}

void bf_print(BloomFilter *bf) {
    ///a debug function to print out a bloom filter
    printf("\ndebug statement for bloom filter\n");
    for (int i = 0; i < N_HASHES; i++) {
        printf("salts %d value: %lu \n", i, bf->salts[i]);
    }
    printf("n_keys %u, n_hits %u, n_misses %u, n_bits_examined %u\n", bf->n_keys, bf->n_hits, bf->n_misses, bf->n_bits_examined);
}

//sets each passed pointer to the valye of the orginal variable for the relevent statistic that the bloom filter is travking
//nk for num of keys, nh to num of hits, nm to num of misses, ne to num of bits examined 
void bf_stats(BloomFilter *bf, uint32_t *nk, uint32_t *nh, uint32_t *nm, uint32_t *ne) {
    *nk = bf->n_keys;
    *nh = bf->n_hits;
    *nm = bf->n_misses; 
    *ne = bf->n_bits_examined;
}

