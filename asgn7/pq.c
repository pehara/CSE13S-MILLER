//my implementation of priority queue ADT
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pq.h"
#include "defines.h"
#include "node.h"

//pq is min heap
struct PriorityQueue {
  unsigned size;
  unsigned capacity;
  struct Node **array;
};

void queue_sort(PriorityQueue *q);

//constructor for priority queue
PriorityQueue *pq_create(uint32_t capacity) {
    struct PriorityQueue *q  = (struct PriorityQueue *)malloc(sizeof(struct PriorityQueue));
    
    q->size = 0;
    q->capacity = capacity;
    q->array = (struct Node **)malloc(q->capacity * sizeof(struct Node *));

	// sort_queue
	queue_sort(q);
	
    return q;
}

//destructor for priority queue
void pq_delete(PriorityQueue **q) {
    free(*q);
    *q = NULL;
}

//Returns true if the priority queue is empty and false otherwise
bool pq_empty(PriorityQueue *q) {
    if (q->size == 0) {
        return true;
    }
    else {
        return false;
    }
}

//Returns true if the priority queue is full and false otherwise
bool pq_full(PriorityQueue *q) {
    if (q->size == q->capacity) {
        return true;
    }
    else {
        return false;
    }
}

//Returns the number of items currently in the priority queue
uint32_t pq_size(PriorityQueue *q) {
    return(q->size);
}

//Enqueues a node into the priority queue, return false if full, true if not full
bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q)) {
        return false;
    }

	// Add the new node to end of the queue
    q->array[q->size] = n;
    q->size++;    

	// Sort the queue, lower frequency (highest frequency) is last    
	queue_sort(q);
		    
    return true;

}

//Dequeues a node from the priority queue, passing it back through the double pointer n
//Returns false if the priority queue is empty prior to dequeuing a node and true otherwise
bool dequeue(PriorityQueue *q, Node **n) {
    if(pq_empty(q)) {
        return false;
    }

	// Return dequeue node
    *n = q->array[q->size-1];
        
	//node_delete(q->array[q->size-1]);

	// Decrement queue size by 1
    q->size--;
    
    // Sort the queue, lower frequency (highest frequency) is last    
    queue_sort(q);
    	
    return true;
}

//A debug function to print a priority queue.
void pq_print(PriorityQueue *q) {
	printf("\nPQ size : %d, capacity : %d", q->size, q->capacity);
}

// Queue sort
uint32_t next_gap(uint32_t n) {
    uint32_t a;

    if (n > 1) {
        if (n <= 2) {
            a = 1;
        }
        else {
            a = (5 * n) / 11;
        }
    }
    else {
        a = 1;
    }

    return a;
}

// Using shell sort to sort
void queue_sort(PriorityQueue *q) {
    uint32_t i;
    uint32_t j;
    Node tempArr;
    uint32_t gap;
    uint32_t n_elements;

	n_elements = q->size;

    //shell sorting
    for (gap = n_elements - 1; gap > 0; gap = next_gap(gap)) {
        //printf("gap %d\n", gap); //delete
        for (i = gap; i < n_elements; i++) {
            //printf("i %d\n", i); //delete
            j = i;
            tempArr = *q->array[i];
            while (j >= gap && tempArr.frequency < q->array[j - gap]->frequency) {
                //printf("j %d\n", j); //delete
                q->array[j] = q->array[j - gap];
                j = j - gap;
            }
            q->array[j] = &tempArr;
        }

        if (gap == 1) {
            break;
        }
    }
    
    // Reverse to descending order
    for (i = 0; i < n_elements; i++) {
    	tempArr = *q->array[i];
    	q->array[i] = q->array[n_elements-i-1];
    	q->array[n_elements-i-1] = &tempArr;
    }

}

