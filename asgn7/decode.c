//this file contains my implementation of huffman decoder
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "defines.h"
#include "huffman.h"
#include "pq.h"
#include "node.h"
#include "code.h"
#include "io.h"
#include "stack.h"

//main program for decode
int main(int argc, char **argv) {
    int opt;
    char *infile_name = "enc_message.txt";
	int infile = 0;
	char *outfile_name = "dec_message.txt";
	int outfile = 1; 
    uint8_t  print_stats = 0;

	uint8_t in_buf[BLOCK];
	int in_buf_size;
	//int i;
	//Code table[ALPHABET];
	//Node root;

    while ((opt = getopt(argc, argv, "hvi:o:")) != -1) {
        switch (opt) {
        case 'h':
            printf("%5s This help menu.\n", "-h");
            printf("%5s Specifies the input file to decode using Huffman coding (the default is stdin).\n", "-i");
            printf("%5s Specifies the output file to write the decompressed file to (the default is stdout).\n", "-o");
            printf("%5s Prints decompression statistics to stderr.\n", "-v");
            return 1;
        case 'i':
            infile = strtoul(optarg, NULL, 10);
            break;
        case 'o':
            outfile = strtoul(optarg, NULL, 10);
            break;
        case 'v':
            print_stats = 1;
            break;
        case '?':
            return 1;
        }
    }

    //read header from the infile & verify magic num
    infile = open(infile_name, O_RDONLY);
    if (infile < 0) {
        printf("File open error"); 
        exit(1);
    }
    
	outfile = open(outfile_name, O_WRONLY);
    
    // Read input file
	in_buf_size = read_bytes(infile, in_buf, BLOCK);
	
	if (!(in_buf[0] == 0xBE && in_buf[1] == 0xEF && in_buf[2] == 0xBB && in_buf[3] == 0xAD)) {
        //error message if magic num does not match
        printf("Invalid file, magic number did not match"); 
        exit(1);
    }

    //struct stat fs;
    //int r;
    //r = stat(outfile_name,&fs);
    //r = chmod(outfile_name, fs.st_mode | S_IWGRP + S_IWOTH);
    fchmod(outfile, S_IRWXO);

    //read the dumped tree from infile
    //size of dumped tree = tree_size
    //creat an array for infile that is tree_size bytes long
    //rebuild tree()
    
    //int tree_size;
    // Read this from the infile
	//dump_tree(outfile, root);

	/*
    //reconstruct the huffman tree
    while(tree_dump > 0) {
        //itterate through the contents

        if(tree_dump[] = L) {
            //symbol for leaf node

            node_create();
        }

        if(tree_dump[] = I) {
            //pop to get to the right child
            Node* right_ = stack_pop(stack, node);
            //pop second time to get to the left child
            Node* left_ = stack_pop(stack,node);

            //join left and right nodes
            Node* parent_ = node_join(left_, right_);

            stack_push(stack, parent_);
        }

        //make the remaining node the root of the tree

    } 

    // reconstruct the huffman tree
    // rebuild_tree(nbytes, *tree);

    //read infile one bit at a time
    for(read_bit(infile, uint8_t *bit)) {
        
        //begin at root of tree
        if(read_bit(infile, uint8_t *bit) = 0) {
            //go to left most child
        }

        //else a bit value of 1 is read
        if() {
            //go to right most child
        }

        //leaf node
        if() {
            //write leaf nodes symbol to outfile
        }

    }
	*/

	// Debug
	printf("\ninbufsize - %d", in_buf_size);
	
    if (print_stats) {
		// 100*(1-(compressed size/uncompressed size))

    }

	
	// Close files
	close(infile);
	close(outfile);
}
