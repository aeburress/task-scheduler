/**
 * A set of functions for creating and manipulating a linked list of Event structs.
 * Each linked list has a head and a tail pointer, and a count of nodes on the list.
 *
 * Author: Alex Burress
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/**
 * A struct representing a process.
 */
typedef struct Process {
	int burstTime;
	int remainingBurst;
	int arrivalTime;
	int waitTime;
	int turnaroundTime;
	int lastAllocated;
} Process;


/**
 * A linked list node. It holds a pointer to a Process and a pointer to another
 * node.
 */
typedef struct ListNode{
	Process* data;
	struct ListNode* next;
} ListNode;

/**
 * A double ended, singly linked list struct. It has head and tail pointers
 * for pointing at the first and last nodes respectively, and an int for
 * storing the count of nodes on the list.
 */
typedef struct {
	ListNode* head;
	ListNode* tail;
	int count;
} LinkedList;

/**
 * Creates an empty linked list.
 */
LinkedList* createList();

/**
 * Creates a node for the passed-in Process and inserts the node at the start of
 * the list.
 */
void insertFirst(LinkedList* list, Process* process);

/**
 * Creates a node for the passed-in Process, and inserts the node at the end
 * of the list.
 */
void insertLast(LinkedList* list, Process* process);

void enqueue(LinkedList* list, Process* process);

/**
 * Removes the first node from the list, extracts and returns a pointer to
 * its Process, and frees the leftover node. Returns NULL if the passed-in list
 * has no nodes.
 */
Process* removeFirst(LinkedList* list);

Process* dequeue(LinkedList* list);

/**
 * Deletes the n'th element on the linked list along with its node. The
 * passed-in int elNo represents n. Elements have a 0-based count.
 * i.e. if elNo = 0, the first node on the list is deleted. The variable
 * 'previous' is used to keep track of the node preceding to the node being
 * deleted. When the n'th node is deleted, previous->next is pointed to the
 * deleted node's next address.
 */
void deleteNthElement(LinkedList* list, int elNo);

/**
 * Returns a pointer to the n'th element on the list, where the count for n
 * is 0-based. i.e. if elNo = 0, the first event on the list is retrieved. 
 */
Process* retrieveElement(LinkedList* list, int elNo);

/**
 * Frees each list node and event from memory, and the list itself.
 */
void freeList(LinkedList* list);

#endif
