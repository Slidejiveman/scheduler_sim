#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>


#define NUM_NODES 30
#define DEBUG

/* type definitions */
// these nodes will be strung together in a doubly-linked queue
typedef struct _node {
    int ptid;             // process/thread ID
    int prio;             // priority. Lower # is higher priority
    char desc[12];        // description of process/thread
    struct _node *next;    // pointer to next node in list
    struct _node *prev;    // pointer to previous node in list
} node;

/* function prototypes */
void init_queue();
void init_node();
void enqueue();
bool is_empty();

/* global variables */
node *CURRENT = NULL;
node *HEAD    = NULL;
node *TAIL    = NULL;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
int i;

/* methods */

// initializes data and creates threads
int main(int argc, char *argv[]) 
{
    // initialize doubly-linked queue
    init_queue();
    return EXIT_SUCCESS;
}

// Creates a doubly-linked queue with initialized nodes
void init_queue()
{
    for (i = 0; i < NUM_NODES; ++i)
    {
        node *new_node = (node*) malloc(sizeof(node));
        if (new_node == NULL) return;
        init_node(new_node, i);    
        enqueue(new_node);
#ifdef DEBUG       
       printf("New node ptid: %d prio: %d\n", new_node->ptid, new_node->prio);
#endif
    }
}

// Initialize a new node
void init_node(node *new_node, int i)
{
    new_node->ptid = i;
    new_node->prio = rand() % 70 + 31; // values 30-100
    new_node->desc[0] = 'n';
    new_node->desc[1] = '\0';    
}

// add new node to the end of the queue
void enqueue(node *new_node)
{
    if (!is_empty()) 
    { 
        TAIL->next = new_node;
        new_node->prev = TAIL;
    }
    else
        HEAD = new_node;
    TAIL = new_node; 

#ifdef DEBUG
    printf("TAIL ptid: %d HEAD ptid: %d\n", TAIL->ptid, HEAD->ptid);
#endif
  
}

// determines if the doubly-linked queue is empty
bool is_empty() 
{
    return HEAD == NULL;
}
