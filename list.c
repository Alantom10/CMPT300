#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


Node array_of_nodes[LIST_MAX_NUM_NODES];
List array_of_lists[LIST_MAX_NUM_HEADS];

int headCount = 0;
int nodeCount = 0;
bool flag = true;

int nextFreeNode;
int nextFreeListHead;


//Helper function which prints out our lists.
void printList(List* pList)
{
    printf ("List items are: ");
    Node* currItem = pList->head;
    for (int i = 0; i < pList->count; i++) {
        printf("%d ",*(int *)currItem->item);
        currItem = currItem->next;
    }
    printf ("\n");
}


// Initialize statically allocated List and Node arrays
List* List_create(){
    // Initialize all the nodes and list heads when the program is run
     if(flag){
         flag = false;

         // Initializing all nodes
         for (int i = 0; i < LIST_MAX_NUM_NODES; i++){
             array_of_nodes[i].item = NULL;
             array_of_nodes[i].next = NULL;
             array_of_nodes[i].prev = NULL;
             array_of_nodes[i].serialNum = i;
             if (i == LIST_MAX_NUM_NODES-1) {   // if its the last node
                 array_of_nodes[i].nextFreeNode = -1;
             } else {
                 array_of_nodes[i].nextFreeNode = i+1;
             }
         }
         nextFreeNode = 0;  // Initializing the first free node

         // Initializing all heads
         for (int j = 0; j < LIST_MAX_NUM_HEADS; j++) {
             array_of_lists[j].head = NULL;
             array_of_lists[j].tail = NULL;
             array_of_lists[j].count = 0;
             array_of_lists[j].curr = NULL;
             array_of_lists[j].beforeStart = false;
             array_of_lists[j].beyondEnd = false;
             array_of_lists[j].serialNum = j;
             if (j == LIST_MAX_NUM_HEADS-1) {   // if its the last head
                 array_of_lists[j].nextFreeList = -1;
             } else {
                 array_of_lists[j].nextFreeList = j+1;
             }
         }
         nextFreeListHead = 0;  // Initializing the first free head
     }

     // condition if all the heads are exhausted. Returns NULL
    if (headCount >= LIST_MAX_NUM_HEADS){
        printf("Error: Cannot create new list. List heads are full!\n");
        return NULL;
    } else {    // else creates new list by using up a free list head
        int index = nextFreeListHead;
        nextFreeListHead = array_of_lists[index].nextFreeList;
        array_of_lists[index].nextFreeList = -1;
        headCount++;
        printf("Created new list!\n");
        return &array_of_lists[index];
    }
}


// Returns the count of the list
int List_count(List* pList) {
    return pList->count;
}


// Returns the first item of the list
void* List_first(List* pList) {
    if (pList->count == 0) {    // if list is empty returns NULL
        printf("Error: List is empty!\n");
        pList->curr = NULL;
        return NULL;
    } else {
        pList->curr = pList->head;
        return pList->curr->item;
    }
}


// Returns the last item of the list
void* List_last(List* pList) {
    if (pList->count == 0) {    // if list is empty returns NULL
        printf("Error: List is empty!\n");
        pList->curr = NULL;
        return NULL;
    } else {
        pList->curr = pList->tail;
        return pList->curr->item;
    }
}


// Returns the next item of the list
void* List_next(List* pList) {
    if (pList->beforeStart) {   // If current node is before the start of the list
        pList->curr = pList->head;
        pList->beforeStart = false;
        return pList->curr->item;
    } else if (pList->beyondEnd) {   // If current node is after the end of the list
        pList->curr = NULL;
        return NULL;
    } else if (pList->curr == pList->tail) {   // If current node is the tail
        pList->beyondEnd = true;
        pList->curr = pList->curr->next;
        return NULL;
    } else {
        pList->curr = pList->curr->next;
        return pList->curr->item;
    }
}


// Returns the previous item of the list
void* List_prev(List* pList) {
    if (pList->beforeStart) {   // If current node is before the start of the list
        pList->curr = NULL;
        return NULL;
    } else if (pList->beyondEnd) {   // If current node is after the end of the list
        pList->curr = pList->tail;
        pList->beyondEnd = false;
        return pList->curr->item;
    } else if (pList->curr == pList->head) {   // If current node is the head
        pList->beforeStart = true;
        pList->curr = pList->curr->prev;
        return NULL;
    } else {
        pList->curr = pList->curr->prev;
        return pList->curr->item;
    }
}


// Returns the current item of the list
void* List_curr(List* pList) {
    if (pList->count == 0) {    // If the list is empty returns NULL
        printf("Error: List is empty!\n");
        return NULL;
    } else if (pList->beforeStart || pList->beyondEnd) {   // If current node is before the start of the list or after the end
        return NULL;
    } else {
        return pList->curr->item;
    }
}


// Adds the new item to list directly after the current item
int List_add(List* pList, void* pItem) {
    if (nodeCount >= LIST_MAX_NUM_NODES) {  // If all nodes are exhausted returns -1
        printf("Error: Cannot add more nodes\n");
        return -1;
    }

    int freeNodeIndex = nextFreeNode;
    nextFreeNode = array_of_nodes[freeNodeIndex].nextFreeNode;
    array_of_nodes[freeNodeIndex].nextFreeNode = -1;
    nodeCount++;

    if (pList->count == 0) {  // If list is empty
        array_of_nodes[freeNodeIndex].item = pItem;
        array_of_nodes[freeNodeIndex].next = NULL;
        array_of_nodes[freeNodeIndex].prev = NULL;

        pList->head = &array_of_nodes[freeNodeIndex];
        pList->tail = &array_of_nodes[freeNodeIndex];
        pList->curr = &array_of_nodes[freeNodeIndex];
        pList->count++;

        return 0;

    } else if (pList->beforeStart) {  // If current is before the start of the list
        array_of_nodes[freeNodeIndex].item = pItem;
        array_of_nodes[freeNodeIndex].next = pList->head;
        array_of_nodes[freeNodeIndex].prev = NULL;

        pList->head->prev = &array_of_nodes[freeNodeIndex];
        pList->head = &array_of_nodes[freeNodeIndex];
        pList->curr = &array_of_nodes[freeNodeIndex];
        pList->beforeStart = false;
        pList->count++;

        return 0;

    } else if (pList->beyondEnd || pList->curr == pList->tail) {  // If current is after the end of the list or is the tail
        array_of_nodes[freeNodeIndex].item = pItem;
        array_of_nodes[freeNodeIndex].next = NULL;
        array_of_nodes[freeNodeIndex].prev = pList->tail;

        pList->tail->next = &array_of_nodes[freeNodeIndex];
        pList->tail = &array_of_nodes[freeNodeIndex];
        pList->curr = &array_of_nodes[freeNodeIndex];
        pList->beyondEnd = false;
        pList->count++;

        return 0;

    } else {
        array_of_nodes[freeNodeIndex].item = pItem;
        array_of_nodes[freeNodeIndex].next = pList->curr->next;
        array_of_nodes[freeNodeIndex].prev = pList->curr;

        pList->curr->next->prev = &array_of_nodes[freeNodeIndex];
        pList->curr->next = &array_of_nodes[freeNodeIndex];
        pList->curr = &array_of_nodes[freeNodeIndex];
        pList->count++;

        return 0;

    }
}


// Adds item to pList directly before the current item
int List_insert(List* pList, void* pItem) {
    if (nodeCount >= LIST_MAX_NUM_NODES) {  // If all nodes are exhausted returns -1
        printf("Error: Cannot add more nodes\n");
        return -1;
    }

    int freeNodeIndex = nextFreeNode;
    nextFreeNode = array_of_nodes[freeNodeIndex].nextFreeNode;
    array_of_nodes[freeNodeIndex].nextFreeNode = -1;
    nodeCount++;

    if (pList->count == 0) {  // If list is empty
        array_of_nodes[freeNodeIndex].item = pItem;
        array_of_nodes[freeNodeIndex].next = NULL;
        array_of_nodes[freeNodeIndex].prev = NULL;

        pList->head = &array_of_nodes[freeNodeIndex];
        pList->tail = &array_of_nodes[freeNodeIndex];
        pList->curr = &array_of_nodes[freeNodeIndex];
        pList->count++;

        return 0;

    } else if (pList->beforeStart || pList->curr == pList->head) {  // If current is before the start of the list or is the tail
        array_of_nodes[freeNodeIndex].item = pItem;
        array_of_nodes[freeNodeIndex].next = pList->head;
        array_of_nodes[freeNodeIndex].prev = NULL;

        pList->head->prev = &array_of_nodes[freeNodeIndex];
        pList->head = &array_of_nodes[freeNodeIndex];
        pList->curr = &array_of_nodes[freeNodeIndex];
        pList->beforeStart = false;
        pList->count++;

        return 0;

    } else if (pList->beyondEnd) {  // If current is after the end of the list
        array_of_nodes[freeNodeIndex].item = pItem;
        array_of_nodes[freeNodeIndex].next = NULL;
        array_of_nodes[freeNodeIndex].prev = pList->tail;

        pList->tail->next = &array_of_nodes[freeNodeIndex];
        pList->tail = &array_of_nodes[freeNodeIndex];
        pList->curr = &array_of_nodes[freeNodeIndex];
        pList->beyondEnd = false;
        pList->count++;

        return 0;

    } else {
        array_of_nodes[freeNodeIndex].item = pItem;
        array_of_nodes[freeNodeIndex].next = pList->curr;
        array_of_nodes[freeNodeIndex].prev = pList->curr->prev;

        pList->curr->prev->next = &array_of_nodes[freeNodeIndex];
        pList->curr->prev = &array_of_nodes[freeNodeIndex];
        pList->curr = &array_of_nodes[freeNodeIndex];
        pList->count++;

        return 0;

    }
}


// Adds item to the end of pList
int List_append(List* pList, void* pItem) {
    if (nodeCount >= LIST_MAX_NUM_NODES) {  // If all nodes are exhausted returns -1
        printf("Error: Cannot add more nodes\n");
        return -1;
    }

    int freeNodeIndex = nextFreeNode;
    nextFreeNode = array_of_nodes[freeNodeIndex].nextFreeNode;
    array_of_nodes[freeNodeIndex].nextFreeNode = -1;
    nodeCount++;

    if (pList->count == 0) {  // If list is empty
        array_of_nodes[freeNodeIndex].item = pItem;
        array_of_nodes[freeNodeIndex].next = NULL;
        array_of_nodes[freeNodeIndex].prev = NULL;

        pList->head = &array_of_nodes[freeNodeIndex];
        pList->tail = &array_of_nodes[freeNodeIndex];
        pList->curr = &array_of_nodes[freeNodeIndex];
        pList->count++;

        return 0;

    } else if (pList->beforeStart) {  // If current is before the start of the list
        array_of_nodes[freeNodeIndex].item = pItem;
        array_of_nodes[freeNodeIndex].prev = pList->tail;
        array_of_nodes[freeNodeIndex].next = NULL;

        pList->tail->next = &array_of_nodes[freeNodeIndex];
        pList->tail = &array_of_nodes[freeNodeIndex];
        pList->curr = &array_of_nodes[freeNodeIndex];
        pList->beforeStart = false;
        pList->count++;

        return 0;

    } else if (pList->beyondEnd) {  // If current is after the end of the list
        array_of_nodes[freeNodeIndex].item = pItem;
        array_of_nodes[freeNodeIndex].next = NULL;
        array_of_nodes[freeNodeIndex].prev = pList->tail;

        pList->tail->next = &array_of_nodes[freeNodeIndex];
        pList->tail = &array_of_nodes[freeNodeIndex];
        pList->curr = &array_of_nodes[freeNodeIndex];
        pList->beyondEnd = false;
        pList->count++;

        return 0;

    } else {
        array_of_nodes[freeNodeIndex].item = pItem;
        array_of_nodes[freeNodeIndex].next = NULL;
        array_of_nodes[freeNodeIndex].prev = pList->tail;

        pList->tail->next = &array_of_nodes[freeNodeIndex];
        pList->tail = &array_of_nodes[freeNodeIndex];
        pList->curr = &array_of_nodes[freeNodeIndex];
        pList->count++;
        
        return 0;

    }
}


// Adds item to the front of pList
int List_prepend(List* pList, void* pItem) {
    if (nodeCount >= LIST_MAX_NUM_NODES) {  // If all nodes are exhausted returns -1
        printf("Error: Cannot add more nodes\n");
        return -1;
    }

    int freeNodeIndex = nextFreeNode;
    nextFreeNode = array_of_nodes[freeNodeIndex].nextFreeNode;
    array_of_nodes[freeNodeIndex].nextFreeNode = -1;
    nodeCount++;

    if (pList->count == 0) {  // If list is empty
        array_of_nodes[freeNodeIndex].item = pItem;
        array_of_nodes[freeNodeIndex].next = NULL;
        array_of_nodes[freeNodeIndex].prev = NULL;

        pList->head = &array_of_nodes[freeNodeIndex];
        pList->tail = &array_of_nodes[freeNodeIndex];
        pList->curr = &array_of_nodes[freeNodeIndex];
        pList->count++;

        return 0;

    } else if (pList->beforeStart) {  // If current is before the start of the list
        array_of_nodes[freeNodeIndex].item = pItem;
        array_of_nodes[freeNodeIndex].prev = NULL;
        array_of_nodes[freeNodeIndex].next = pList->head;

        pList->head->prev = &array_of_nodes[freeNodeIndex];
        pList->head = &array_of_nodes[freeNodeIndex];
        pList->curr = &array_of_nodes[freeNodeIndex];
        pList->beforeStart = false;
        pList->count++;

        return 0;

    } else if (pList->beyondEnd) {  // If current is after the end of the list
        array_of_nodes[freeNodeIndex].item = pItem;
        array_of_nodes[freeNodeIndex].prev = NULL;
        array_of_nodes[freeNodeIndex].next = pList->head;

        pList->head->prev = &array_of_nodes[freeNodeIndex];
        pList->head = &array_of_nodes[freeNodeIndex];
        pList->curr = &array_of_nodes[freeNodeIndex];
        pList->beyondEnd = false;
        pList->count++;

        return 0;

    } else {
        array_of_nodes[freeNodeIndex].item = pItem;
        array_of_nodes[freeNodeIndex].prev = NULL;
        array_of_nodes[freeNodeIndex].next = pList->head;

        pList->head->prev = &array_of_nodes[freeNodeIndex];
        pList->head = &array_of_nodes[freeNodeIndex];
        pList->curr = &array_of_nodes[freeNodeIndex];
        pList->count++;
        
        return 0;

    }
}


// Return current item and take it out of pList
void* List_remove(List* pList) {
    if (pList->count == 0) {    // If list is empty
        printf("Error: List is empty.\n");
        return NULL;
    } else if (pList->beforeStart || pList->beyondEnd) {    // If current is before the start or after the end of the list
        return NULL;
    } else if (pList->count == 1 && pList->curr) {     // If list only has one node
        void* tempItem = pList->curr->item;
        int serialNum = pList->curr->serialNum;

        pList->head = NULL;
        pList->tail = NULL;
        pList->curr = NULL;
        pList->count--;
        nodeCount--;

        array_of_nodes[serialNum].next = NULL;
        array_of_nodes[serialNum].prev = NULL;
        array_of_nodes[serialNum].item = NULL;
        if (nextFreeNode == -1) {
            nextFreeNode = serialNum;
        } else {
            array_of_nodes[serialNum].nextFreeNode = nextFreeNode;
            nextFreeNode = serialNum;
        }

        return tempItem;
    } else {
        void* tempItem = pList->curr->item;
        int serialNum = pList->curr->serialNum;
        nodeCount--;

        if (pList->curr == pList->tail) {   // If current node is the tail
            pList->tail = pList->tail->prev;
            pList->beyondEnd = true;
            pList->tail->next = NULL;
            pList->curr = NULL;
            pList->count--;
        } else if(pList->curr == pList->head) {   // If current node is the head
            pList->head = pList->head->next;
            pList->head->prev = NULL;
            pList->curr = pList->head;
            pList->count--;
        } else {
            pList->curr->prev->next = pList->curr->next;
            pList->curr->next->prev = pList->curr->prev;
            pList->curr = pList->curr->next;
            pList->count--;
        }

        // Freeing the node to be reused
        array_of_nodes[serialNum].next = NULL;
        array_of_nodes[serialNum].prev = NULL;
        array_of_nodes[serialNum].item = NULL;
        if (nextFreeNode == -1) {
            nextFreeNode = serialNum;
        } else {
            array_of_nodes[serialNum].nextFreeNode = nextFreeNode;
            nextFreeNode = serialNum;
        }

        return tempItem;
    }
}


// Adds pList2 to the end of pList1
void List_concat(List* pList1, List* pList2) {
    if (pList1->tail && pList2->head) { // If pList1 has a tail and pList2 has a head
        pList1->tail->next = pList2->head;
        pList2->head->prev = pList1->tail;
        pList1->tail = pList2->tail;
        pList1->count += pList2->count;
    } else if (pList1->count == 0 && pList2->head) { // If pList1 is empty and pList2 has a head
        pList1->head = pList2->head;
        pList1->tail = pList2->tail;
        pList1->curr = NULL;
        pList1->beforeStart = true;
        pList1->count = pList2->count;
    }

    // Freeing pList2 to be reused
    int listSerialNum = pList2->serialNum;

    array_of_lists[listSerialNum].count = 0;
    array_of_lists[listSerialNum].head = NULL;
    array_of_lists[listSerialNum].tail = NULL;
    array_of_lists[listSerialNum].curr = NULL;
    array_of_lists[listSerialNum].beforeStart = false;
    array_of_lists[listSerialNum].beyondEnd = false;

    if (nextFreeListHead == -1) {
        nextFreeListHead = listSerialNum;
    } else {
        array_of_lists[listSerialNum].nextFreeList = nextFreeListHead;
        nextFreeListHead = listSerialNum;
    }

    headCount--;
}


// Deletes pList
void List_free(List* pList, FREE_FN pItemFreeFn) {
    if (pList->count == 0) {    // If pList is empty
        // Freeing the list to reuse
        int listSerialNum = pList->serialNum;

        array_of_lists[listSerialNum].count = 0;
        array_of_lists[listSerialNum].head = NULL;
        array_of_lists[listSerialNum].tail = NULL;
        array_of_lists[listSerialNum].curr = NULL;
        array_of_lists[listSerialNum].beforeStart = false;
        array_of_lists[listSerialNum].beyondEnd = false;

        if (nextFreeListHead == -1) {
            nextFreeListHead = listSerialNum;
        } else {
            array_of_lists[listSerialNum].nextFreeList = nextFreeListHead;
            nextFreeListHead = listSerialNum;
        }

        headCount--;
        printf("List has been freed\n");
    } else {
        pList->curr = pList->head;
        pList->beforeStart = false;
        pList->beyondEnd = false;
        while (pList->curr != NULL) {   // Freeing all nodes present in the list to reuse
            (*pItemFreeFn)(pList->curr->item);
            void* a = List_remove(pList);

            nodeCount--;
        }

        // Freeing the list to reuse
        int listSerialNum = pList->serialNum;

        array_of_lists[listSerialNum].count = 0;
        array_of_lists[listSerialNum].head = NULL;
        array_of_lists[listSerialNum].tail = NULL;
        array_of_lists[listSerialNum].curr = NULL;
        array_of_lists[listSerialNum].beforeStart = false;
        array_of_lists[listSerialNum].beyondEnd = false;

        if (nextFreeListHead == -1) {
            nextFreeListHead = listSerialNum;
        } else {
            array_of_lists[listSerialNum].nextFreeList = nextFreeListHead;
            nextFreeListHead = listSerialNum;
        }

        headCount--;
        printf("List has been freed\n");
    }
}


// Return last item and take it out of pList
void* List_trim(List* pList) {
    if (pList->count == 0) {    // If list is empty
        printf("Error: Cannot trim empty list");
        return NULL;
    } else if (pList->count == 1) { // If list size is 1
        pList->curr = pList->tail;
        void* tempItem = List_remove(pList);

        return tempItem;
    } else {
        pList->curr = pList->tail;
        void* tempItem = pList->curr->item;
        int serialNum = pList->curr->serialNum;
        nodeCount--;

        pList->tail = pList->tail->prev;
        pList->tail->next = NULL;
        pList->curr = pList->tail;
        pList->count--;

        // Freeing the node to reuse
        array_of_nodes[serialNum].next = NULL;
        array_of_nodes[serialNum].prev = NULL;
        array_of_nodes[serialNum].item = NULL;
        if (nextFreeNode == -1) {
            nextFreeNode = serialNum;
        } else {
            array_of_nodes[serialNum].nextFreeNode = nextFreeNode;
            nextFreeNode = serialNum;
        }

        return tempItem;
    }
}


// Search pList, starting at the current item, until the end is reached or a match is found
void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg) {
    if (pList->count == 0) {    // If list is empty
        printf("Error: List is empty.\n");
		return NULL;
    } else if (pList->beforeStart) {    // If current is before the start of the list
        pList->curr = pList->head;
        pList->beforeStart = false;
    } else if (pList->beyondEnd) {    // If current is after the end of the list
        printf("Error: Item not found.\n");
		pList->curr = NULL;
		return NULL;
    }

    // Searching through all the nodes in the list
    while(pList->curr != NULL && !pList->beforeStart && !pList->beyondEnd)
	{
		if ((*pComparator)(pList->curr->item, pComparisonArg)) {    // If item matched the value being searched for
			printf("Item found: %d\n", *(int *)pList->curr->item);
			return pList->curr->item;
        } else {
			pList->curr = pList->curr->next;
		}
	}

    // If item is not found
    printf("Error: Item not found.\n");
	pList->curr = NULL;
	pList->beyondEnd = true;
	return NULL;
}