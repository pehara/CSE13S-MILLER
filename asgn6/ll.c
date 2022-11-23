//Contains the implementation of the linked list ADT.
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ll.h"
#include "node.h"

struct LinkedList {
    uint32_t length;
    Node *head; // Head sentinel node.
    Node *tail; // Tail sentinel node.
    bool mtf;
};

//constructor for linked list
LinkedList *ll_create(bool mtf) {
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
    if (ll) {
        ll->length = 2;
        ll->head = node_create(NULL, NULL);
        ll->tail = node_create(NULL, NULL);
        ll->mtf = mtf;
        //linking list
        //creates two nodes to add onto, such as x and y onto
        ll->head->next = NULL;
        ll->head->prev = ll->tail->next;
        ll->tail->prev = NULL;
        //printf("\nLL create");
    }
    return ll;
}

Node *ll_node(LinkedList *ll) {
   return ll->head;
}

//destructor for linked list
void ll_delete(LinkedList **ll) {
    Node *gudetama = (*ll)->head;
    while (gudetama != NULL) {
        Node *converse = gudetama->next;
        node_delete(&gudetama);
        gudetama = converse;
    }
    free(*ll);
    ll = NULL;
}

//returns lenth for linked list
uint32_t ll_length(LinkedList *ll) {
    uint32_t length = 0;
    struct Node *n;

    for(n = ll->head->prev; n != NULL; n = n->prev) {
        length++;
        printf("\nll length %u", length);
    }

    return (length); //return ll->length pos
}

//searches for a node with oldspeak
Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    struct Node* n = ll->head;
    //n = ll_node(ll); //ll->head;

    //if the list is empty

    if(ll->head == NULL) {
        return NULL;
    }

    while (n->oldspeak != oldspeak) {
        if (n->next == NULL) {
            return NULL;
        }
        else {
            n = n->next;
           
        }
    }

    return n;
}

//int ll_insert_cnt = 0;

//inserts a new node containing specified oldspeak and newspeak
void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    if (ll_lookup(ll, oldspeak) != NULL) {
        return;
    }
    Node *new_node = node_create(oldspeak, newspeak);

    //Node *nnn = ll->head->next;
    
    //ihtc->next = NULL; //nnn;
    //ihtc->prev = ll->head->;

    //ll->head->next = ihtc;
    //nnn->prev = ihtc;
    //printf("\nLL insert");
    
    /*
    ll->tail->next = ll->head->next;
	ll->tail->prev = ll->head->prev;

	ll->head->next = new_node->next;
	ll->head->prev = new_node->prev;
	*/
	
	new_node->prev = ll->head->next;
    ll->head = new_node;

	//ll_insert_cnt++;
	//printf("\nLL insert count %d", ll_insert_cnt);
}




//ptint out each node but head and tail
void ll_print(LinkedList *ll) {
	printf("\nLL print nodes\n");
    //Node *n;

	while (ll->head != NULL) {
		ll->head = ll->head->prev;
	    printf("\nLL print nodes in the link list\n");
	}
	
    //for(n = ll->head->prev; n != NULL; n = n->prev) {
    //    node_print(n);
    //}
    
    
}

//copies num of linked list lookups tp n seeks and links traversed with n links
void ll_stats(uint32_t *n_seeks, uint32_t *n_links) {
    //skip and come back!!!, this is not correct ???
    n_seeks++;
    n_links++;
}
