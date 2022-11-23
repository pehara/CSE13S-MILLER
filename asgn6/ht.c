//Contains the implementation of the hash table ADT.
#include "ll.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ht.h"
#include "ll.h"
#include "city.h"

struct HashTable {
    uint64_t salt;
    uint32_t size;
    uint32_t n_keys;
    uint32_t n_hits;
    uint32_t n_misses;
    uint32_t n_examined;
    bool mtf;
    LinkedList ** lists;
};

HashTable *ht_create(uint32_t size , bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht != NULL) {
        ht->mtf = mtf;
        ht->salt = 0x9846e4f157fe8840;
        ht->n_hits = ht->n_misses = ht->n_examined = 0;
        ht->n_keys = 0;
        ht->size = size;
        ht->lists = (LinkedList **) calloc(size , sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

//destructor for hash table
void ht_delete(HashTable **ht) {
    free(*ht);
    ht = NULL;
}

//returns hash tables size
uint32_t ht_size(HashTable *ht) {
    return (ht->size);
}

//searches for an entry node
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    uint64_t annoying_orange = hash(ht->salt, oldspeak) % ht_size(ht);
    Node *nl = NULL;
    
    if (ht->lists[annoying_orange] == NULL) {
        return NULL;
    }
    ht->n_examined++;
    
    nl = ll_lookup(ht->lists[annoying_orange], oldspeak);
    
    if (nl != NULL) {
    	ht->n_hits++;
    	//printf("\nHT nhits");
    }
    else {
    	ht->n_misses++;
        //printf("\nHT n_misses");
    }
    return (nl);
}

//inserts specified old speak
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint64_t banana = hash(ht->salt, oldspeak) % ht_size(ht);
    //printf("\nHT has %llu", banana);
    if (ht->lists[banana] == NULL) {
        ht->lists[banana] = ll_create(ht->mtf);
    }
    ll_insert(ht->lists[banana], oldspeak, newspeak);
    ht->n_keys++;
}

//returns num of non NULL linked lists in the hash table
uint32_t ht_count(HashTable *ht) {
    return (ll_length(*ht->lists));
}

//a debug function
void ht_print(HashTable *ht) {
    printf("\nNum Keys: %u, num of hits: %u, num of misses: %u, num of links examined: %u\n", ht->n_keys, ht->n_hits, ht->n_misses, ht->n_examined); //finish later
}

//sets nk to number of keys, nh to number of hits, nm to number of misses
//and ne to number of links examined 
void ht_stats(HashTable *ht, uint32_t *nk, uint32_t *nh, uint32_t *nm, uint32_t *ne) {
    *nk = ht->n_keys;
    *nh = ht->n_hits;
    *nm = ht->n_misses;
    *ne = ht->n_examined;
}
