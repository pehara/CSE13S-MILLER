//huffman coding module interface
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "huffman.h"
#include "pq.h"
#include "node.h"
#include "code.h"
#include "io.h"
#include "stack.h"
#include "defines.h"


bool is_leaf(Node *node);

Code c;

struct PriorityQueue { /// This should ideally be in the header file ???
  unsigned size;
  unsigned capacity;
  struct Node **array;
};

//Constructor
Node *build_tree(uint64_t hist[static ALPHABET]) {
    PriorityQueue *q;
    Node *parent;
    int i;
    Node *left;
    Node *right;
    Node *root;

    q = pq_create(ALPHABET); //create a priority queue
        
    // Create nodes for all valid symbols with frequency greater than 0
    for (i=0; i<ALPHABET; i++) {
    	if (hist[i]) {
    		//Node *n = node_create(i, hist[i]);
    		//parent = node_join(q, n);
    		//enqueue(q, n);
        	q->array[q->size] = node_create(i, hist[i]); //create a node when histogram size is non zero
        	q->size++; // Increment queue count 
        }
    }

	// Combine nodes and build the queue
    while(pq_size(q) > 1) {
        dequeue(q, &left); //dequeing nodes left child
        dequeue(q, &right); //right child

        parent = node_join(left, right); //join nodes together

        enqueue(q, parent); //enques joined parent node
    }

	//printf("\nTree size %d", q->size);
	
    dequeue(q, &root); //dequeing nodes root

	//q->size = 7;
	
	// Init code
	c = code_init(); // Find an another place

    return root;
}



//popualates code table
void build_codes(Node *root, Code table[static ALPHABET]) {

    uint8_t *bit = 0;

    //printf("\n\nWorks up to here 1\n");
    
    if (root != NULL) {
		//printf("\n\nWorks up to here 1.1\n");  
		//printf("\nR(%d)", root->right == NULL ? 1:0);  
		//printf("\nL(%d)", root->left == NULL ? 1:0);  

		if (is_leaf(root)) {
			//printf("\n\nWorks up to here 2\n");	
			table[root->symbol] = c;
		}
    }
    else {
      	//left node
    	code_push_bit(&c, 0);
		build_codes(root->left, table);
      	code_pop_bit(&c, bit);     	
      
        //right node
        code_push_bit(&c, 1);
        build_codes(root->right, table);      	
      	code_pop_bit(&c, bit);       	
	}
	
}

//post order traversal of tree
void dump_tree(int outfile, Node *root) {
  //printf("\n\nWorks up to here huffman 1 \n");
	uint8_t buf;
	
    if(root != NULL) {
    	//dump_tree(outfile, root->left);
	    //dump_tree(outfile, root->right); //segfault here
        
        if (is_leaf(root)) {
        	buf = 'L';
        	write_bytes(outfile, &buf, 1);
        	buf = root->symbol;
          write_bytes(outfile, &buf, 1);
        }
        else {
            buf = 'I';
        	write_bytes(outfile, &buf, 1);
        }
    }
}

//reconstructs tree
/*
Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {


}
*/

//destructor
void delete_tree(Node **root) {
    free(*root);
    *root = NULL;
}

bool is_leaf(Node *node) {
	int val;
			
	if (!(node->left) && !(node->right)) {
		val = 1;
	}
	else {
		val = 0;
	}
	
  	return val;
}

void print_hf_array(int array[], int n) {
  int i;
  for (i = 0; i < n; ++i)
    printf("%d", array[i]);

  printf("\n");
}

void print_hufcodes(struct Node *root, int array[], int top) {
  if (root->left) {
    array[top] = 0;
    print_hufcodes(root->left, array, top + 1);
  }
  if (root->right) {
    array[top] = 1;
    print_hufcodes(root->right, array, top + 1);
  }
  if (is_leaf(root)) {
    printf("  %c   | ", root->symbol);
    print_hf_array(array, top);
  }
}


