//implementation of of the I/O module
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "io.h"

int read_num_bytes = 0;
int read_num_bit = 0;

uint8_t write_bit_buf[BLOCK];
int write_num_bytes = 0;

//peforms read function
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int bufsize;

    bufsize = read(infile, buf, nbytes);
    buf[bufsize] = '\0';
    
    return bufsize;
}

//peforms write function
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int bufsize;
	
    bufsize = write(outfile, buf, nbytes);
  
    return bufsize;
}

// Fix me later
/*
//read in a block of bytes into a buffer and dole out bits one at a time
bool read_bit(int infile, uint8_t *bit){
	int i;
	uint8_t buf[BLOCK];
	
	if (!read_num_bytes) { // No bytes in the buffer
		read_num_bytes = read_bytes(infile, buf, BLOCK); 
		read_num_bit = 8*read_num_bytes; // Each byte has 8 bits
	}

	if (read_num_bit != 0 && read_num_bit%8 == 0) {
		for (i=0;i<read_num_bytes;i++){
			buf[i] = buf[i+1]; // Shift bytes left
		}
		read_num_bytes--;
	}
	
	//bit = (buf[read_num_bytes-1] >> (7-read_num_bit % 8)) & 0x01; // Shift bits and return 1 bit	

	bit = &buf[0];
	
	read_num_bit--;
	
	return read_num_bit;

}
*/

//Each bit in the code c will be buffered into the buffer
void write_code(int outfile, Code *c){
	int i;

	for (i=0;i<MAX_CODE_SIZE/8;i++){
		write_bit_buf[i] = c->bits[0+i] << 7 | c->bits[1+i] << 6 | c->bits[2+i] << 5 | c->bits[3+i] << 4 | 
						   c->bits[4+i] << 3 | c->bits[5+i] << 2 | c->bits[6+i] << 1 | c->bits[7+i];
	}

	write_num_bytes = write_num_bytes + MAX_CODE_SIZE/8;
	
	// Write when the buffer is full
	if (write_num_bytes == BLOCK) {
		write_bytes(outfile, write_bit_buf, BLOCK);
		write_num_bytes = 0;
	}
	
}

//write out any leftover, buffered bits
void flush_codes(int outfile) {
	if (!write_num_bytes) {
		write_bytes(outfile, write_bit_buf, write_num_bytes);
		write_num_bytes = 0;
	}
}
