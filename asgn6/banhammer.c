//This contains main() and may contain the other (global) functions necessary to complete
//the assignment. Local functions must be declared static in the file that uses them

//newspeak and badspeak shouldnt be commited to the repo

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "bf.h"
#include "bv.h"
#include "city.h"
#include "ht.h"
#include "messages.h"
#include "node.h"
#include "parser.h"


int main(int argc, char **argv) {
    int opt;
    uint32_t hash_table_size = 10000;
    uint32_t num_of_bf_entries = 524288; //pow(2,19);
    uint8_t  move_to_frontrule = 0; // Unused
    uint8_t  print_stats = 0;

    while ((opt = getopt(argc, argv, "hmst:f:")) != -1) {
        switch (opt) {
        case 'h':
            printf("%5s %-12s This help menu.\n", "-h", "");
            printf("%5s %-12s Size specifies that the hash table will have size entries (the default will be 10000).\n", "-t", "");
            printf("%5s %-12s Size specifies that the Bloom filter will have size entries(the default will be 219).\n", "-f", "");
            printf("%5s %-12s Will enable the move-to-front rule. By default, the move-to-frontrule is disabled.\n", "-m", "");
            printf("%5s %-12s Will enable the printing of statistics to stdout.\n", "-s", "");
            return 1;
        case 't':
            hash_table_size = strtoul(optarg, NULL, 10);
            break;
        case 'f':
            num_of_bf_entries = strtoul(optarg, NULL, 10);
            break;
        case 'm':
            move_to_frontrule = 1;
            break;
        case 's':
            print_stats = 1;
            break;
        case '?':
            return 1;
        }
    }

    // Print entries for debug
    printf("\nhash_table_size %u num_of_bf_entries %u move_to_frontrule %d print_stats %d\n", hash_table_size, num_of_bf_entries, move_to_frontrule, print_stats);

    // Init bloom filter and hash table
    BloomFilter *bf = bf_create(num_of_bf_entries);

    HashTable *ht = ht_create(hash_table_size, true);

    Node *nd = node_create(NULL, NULL);

    // Read files
    FILE *bsf = fopen("badspeak.txt", "r");
    FILE *nsf = fopen("newspeak.txt", "r");

    char bs_line[256];
    char ns_line[256];
    char os_line[256];
    //char os_word[256];
    //char ns_word[256];

	bf_print(bf);
	ht_print(ht);
	
    while (fscanf(bsf, "%s\n", bs_line) != EOF) {
      bf_insert(bf, bs_line);
      ht_insert(ht, bs_line, NULL);
      //printf("\nBS %s", bs_line);
    }
    fclose(bsf);
    
    //size_t i;
    //int j, wc = 0;
    while (fscanf(nsf, "%s %s\n", os_line, ns_line) != EOF) {
      // Separate oldspeak and newspeak
      bf_insert(bf, os_line);
      ht_insert(ht, os_line, ns_line);
      // for (i=0; i <= strlen(ns_line);i++) {
      //   if (ns_line[i] == ' ') {
      //     j = 0;
      //     wc++;
      //   } else {
      //     if (wc == 0) {
      //       os_word[j] = ns_line[i];
      //     }
      //     else {
      //       ns_word[j] = ns_line[i];
      //     }
      //  }
      //}

      // bf_insert(bf, os_word);
      // ht_insert(ht, os_word, ns_word);
      //printf("\noldspeak: %s, newspeak: %s", os_line, ns_line);
    }
    fclose(nsf);

	//Debug print bf and ht
	bf_print(bf);
	ht_print(ht);
	//ht_count(ht);
	

    // Read stdin
    printf("Please enter words: \n");
    char *line = NULL;
    size_t line_len = 0;
    ssize_t line_Size = 0;
    char *parse_word = 0;
    int thoughtcrime = 0;
    char thoughtcrime_list[256][256];
    int Rightspeak = 0;
    char oldspeak_wd_list[256][256];
    int wd_num = 0;
  
    line_Size = getline(&line, &line_len, stdin);
    printf("You entered %s, which has %zu chars.\n", line, line_Size -1);

    // Parse words
    FILE *psf = fopen("parser.txt", "w");

    Parser *psr = parser_create(psf);

    while (true) { // How to end this loop
      if (!next_word(psr, parse_word)) {
          break;
      }
      else if (bf_probe(bf, parse_word)) { // Parse word and check Bloom filter

        nd = ht_lookup(ht, parse_word);

        // for newspeak translation
        if (nd->newspeak == NULL) {
          thoughtcrime = 1;
          memcpy(thoughtcrime_list[wd_num], parse_word, 100); // Size need to fixed
        } else {
          Rightspeak = 1;
          memcpy(oldspeak_wd_list[wd_num], nd->newspeak, 100); // Size need to fixed
        }
      }

    } // While

    // Print actions
    if (thoughtcrime && Rightspeak) {
      printf("%s", mixspeak_message);

      wd_num = 0;
      while (thoughtcrime_list[wd_num] != 0) {
        printf("\n%s", thoughtcrime_list[wd_num]);
        wd_num++;
      }

      wd_num = 0;
      while (oldspeak_wd_list[wd_num] != 0) {
        printf("\n%s", oldspeak_wd_list[wd_num]);
        wd_num++;
      }

    }

    if (thoughtcrime && !Rightspeak) {
      printf("%s", badspeak_message);
      
      wd_num = 0;
      while (thoughtcrime_list[wd_num] != 0) {
        printf("\n%s", thoughtcrime_list[wd_num]);
        wd_num++;
      }

    }

    if (!thoughtcrime && Rightspeak) {
      printf("%s", goodspeak_message);

      wd_num = 0;
      while (oldspeak_wd_list[wd_num] != 0) {
        printf("\n%s", oldspeak_wd_list[wd_num]);
        wd_num++;
      }

    }

    float bits_examined_per_miss = 0.0;
    float false_positives = 0.0;
    float bloom_filter_load = 0.0;
    float average_seek_length = 0.0;
    uint32_t nk, nh, nm, ne;

    if (print_stats) {

      ht_stats(ht, &nk, &nh, &nm, &ne);
      
      if (nm)
      	bits_examined_per_miss = (ne - hash_table_size * nh) / nm; //chnaged * -
      	
      if (nh)
      	false_positives = nm / nh;
      
      if (bf_size(bf))
      	bloom_filter_load = bf_count(bf) / bf_size(bf);
      	
      if (nh + nm)
      	average_seek_length = ne / (nh + nm);
      
      printf("\nht keys: %d", nk);
      printf("\nht hits: %d", nh);
      printf("\nht misses: %d", nm);
      printf("\nht probes: %d", ne);

      bf_stats(bf, &nk, &nh, &nm, &ne);

      printf("\nbf keys: %d", nk);
      printf("\nbf hits: %d", nh);
      printf("\nbf misses: %d", nm);
      printf("\nbf bits examined: %d", ne);

      printf("\nBits examined per miss: %f", bits_examined_per_miss);
      printf("\nFalse positives: %f Average seek length: %f", false_positives, average_seek_length);
      printf("\nBloom filter load: %f", bloom_filter_load);
    }

    // Make sure to add all memory free here.
    free(line);
    free(parse_word);
    fclose(psf);

  return 0;



}



