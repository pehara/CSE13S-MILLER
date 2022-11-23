//Contains the implementation of the node ADT.
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "node.h"

/*
char *peh_strdup(const char *s) {
  size_t size = strlen(s) + 1;
        
  char *strp;
  strp = malloc(size);
  if (strp) {
    memcpy(strp, s, size);
  }
  return strp;
}
*/

//constructor for node
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->oldspeak = oldspeak; //peh_strdup(oldspeak);
        n->newspeak = newspeak; //peh_strdup(newspeak);
        n->next = NULL;
        n->prev = NULL;
    }
    return n;
}

//destructor for a node
void node_delete(Node **n) {
    free(n);
    n = NULL;
}

//debug function
void node_print(Node *n) {
    //printf("\nNode print\n");
    if (n->oldspeak != NULL && n->newspeak != NULL) {
    	printf("%s -> %s\n", n->oldspeak , n->newspeak);
    }
   	if (n->oldspeak != NULL && n->newspeak == NULL) {
		printf("%s\n", n->oldspeak);
    }
}
