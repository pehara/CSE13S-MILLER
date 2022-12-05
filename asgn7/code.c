//implementation of the code ADT
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "code.h"

//constructor 
Code code_init(void) {
	Code c;
	
	c.top = 0; //code val is not a pointer
	memset(c.bits, 0, MAX_CODE_SIZE);

	return c;
}


//returns the size
uint32_t code_size(Code *c) {

	int i;
	uint32_t num_set_bits = 0;
	
	for (i=0;i<MAX_CODE_SIZE;i++) {
		if ((*c).bits[i]) { //changed to (*c) from c
			num_set_bits++; // Count number of set bits
		}	
	}
	
    return (num_set_bits);
}

//Returns true if the Code is empty and false otherwise
bool code_empty(Code *c) {

	int i;
	uint32_t num_set_bits = 0;
	
	for (i=0;i<MAX_CODE_SIZE;i++) {
		if ((*c).bits[i]) { //changed to (*c) from c
			num_set_bits++; // Count number of set bits
		}	
	}
	
	return num_set_bits; // Return true if num_set_bits > 0 else false

}

//Returns true if the Code is full and false otherwise
bool code_full(Code *c) {
	if (code_size(c) == MAX_CODE_SIZE) {
		return true;
	} else {
		return false;
	}
}

//Sets the bit at index i in the Code, 
//setting it to 1. If i is out of range, return false. Otherwise, return true
bool code_set_bit(Code *c, uint32_t i) {
	
	if (i < 0 || i > MAX_CODE_SIZE-1) // Check for out of range
		return false;
	
	// Set bit
	(*c).bits[i] = 1; //changed to (*c) from c, bit to bits
	
	return true;
}

//Clears the bit at index i in the Code, clearing it to 0. If i is out of range, 
//return false. Otherwise, return true 
bool code_clr_bit(Code *c, uint32_t i) {
	
	if (i < 0 || i > MAX_CODE_SIZE-1) // Check for out of range
		return false;
	
	// Set bit
	c->bits[i] = 0; //changed to (*c) from c, bit to bits
	
	return true;
}



//Gets the bit at index i in the Code. If i is out of range, or if 
//bit i is equal to 0, return false. Return true
//if and only if bit i is equal to 1
bool code_get_bit(Code *c, uint32_t i) {
	if (i < 0 || i > MAX_CODE_SIZE-1) // Check for out of range
		return false;
			
	if (c->bits[i])	
		return true;
	else
		return false;	
			
}

//Pushes a bit onto the Code
bool code_push_bit(Code *c, uint8_t bit) {
	int i;
		
	if (code_full(c)) 
		return false; // Code is full
			
	// Shift by 1
	for (i=0;i<MAX_CODE_SIZE;i++) {
		(*c).bits[i+1] = (*c).bits[i]; //changed to (*c) from c, bit to bits
	}	
		
	// Push bit into the first position
	(*c).bits[0] = bit; //changed to (*c) from c, bit to bits
	
	return true;	
}

//Pops a bit off the Code
bool code_pop_bit(Code *c, uint8_t *bit) {
	int i;
	uint8_t pop_bit;
	
	bit = &pop_bit;		
			
	if (code_empty(c)) 
		return false; // Code is empty
    			
	// Pop first bit		
    //printf("\n\nWorks up to here Code 1 %d\n", *bit);     
	pop_bit = c->bits[0]; //changed to (*c) from c, bit to bits
    			
	// Shift by 1
	for (i=0;i<MAX_CODE_SIZE;i++) {
		(*c).bits[i] = (*c).bits[i+1]; //changed to (*c) from c, bit to bits
	}	

	return *bit;
}

//debug function
void code_print(Code *c) {
	int i;
	
	printf("\nCode Top : %d bits : ", c->top);
	for (i=0;i<MAX_CODE_SIZE;i++) {
		printf("%d", c->bits[i]);
	}
}

