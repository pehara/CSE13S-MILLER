//this file contains my implementation of huffman encoder
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>

#include "defines.h"
#include "huffman.h"
#include "pq.h"
#include "node.h"
#include "code.h"
#include "io.h"
#include "stack.h"

uint64_t histogram[ALPHABET];

int main(int argc, char **argv) {
    int opt;
    char *infile_name = "orig_message.txt";
	int infile = 0; //STDIN
	char *outfile_name = "enc_message.txt";
	int outfile = 1; // STDOUT, STD ERR is 2
    uint8_t print_stats = 0;

	uint8_t in_buf[BLOCK];
	int in_buf_size;
	int i;
	Code table[ALPHABET];
	
    while ((opt = getopt(argc, argv, "hvi:o:")) != -1) {
        switch (opt) {
        case 'h':
            printf("%5s This help menu.\n", "-h");
            printf("%5s Specifies the input file to encode using Huffman coding (the default is stdin).\n", "-i");
            printf("%5s Specifies the output file to write the compressed input to (the default is stdout).\n", "-o");
            printf("%5s Prints compression statistics to stderr.\n", "-v");
            return 1;
        case 'i':
            infile_name = optarg;
            break;
        case 'o':
            outfile_name = optarg;
            break;
        case 'v':
            print_stats = 1;
            break;
        case '?':
            return 1;
        }
    }
			
	// Open files
	infile = open(infile_name, O_RDONLY);
	if (infile < 0) {
        printf("File open error"); 
        exit(1);
    }
	
	outfile = open(outfile_name, O_RDWR);
	//if (outfile < 0) {
    //    printf("File open error"); 
    //    exit(1);
    //}
	    
	// Read input file
	in_buf_size = read_bytes(infile, in_buf, BLOCK);

    printf("\n-----------------------------------------\n");
	// Create histogram
	for (i=0; i<in_buf_size; i++) {
        histogram[in_buf[i]]++; //histogram increment
        printf("%c", in_buf[i]);
    }
    printf("\n-----------------------------------------\n");

    if (histogram[0] == 0) {
        histogram[0] = 1;
    }

    if (histogram[1] == 0) {
        histogram[1] = 1;
    }
        
    printf("\n------------- Freq -------------------");
	for (i=0; i<ALPHABET; i++) {
		if (histogram[i]) {
        	printf("\nChar %c Freq %lu", i, histogram[i]);
    	}
    }
    printf("\n-----------------------------------------\n");
        	
    // Construct Huffman tree
    Node *huffman_node = build_tree(histogram);
    
    /*
    node_print(huffman_node);
    node_print(huffman_node->right);
    node_print(huffman_node->left);
    node_print(huffman_node->right->right);
    node_print(huffman_node->right->left);
    node_print(huffman_node->left->right);
	*/
                   
    // Construct code table
    build_codes(huffman_node, table);
    
    //printf("\n\nWorks up to here encode 1 \n");
        
    // Emit Huffman tree to a file
    dump_tree(outfile, huffman_node);

    //printf("\n\nWorks up to here encode 2 \n");
    
    // Encode input file
    

    if (print_stats) {
		//100*(1-(compressed size/uncompressed size));
    }

	// Close files
	close(infile);
	close(outfile);

  return 0;

}
