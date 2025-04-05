#include "alloc.h"

void dealloc(char *pointer){
    //if nothing to deallocate
    if(allocated == NULL){
        perror("allocated is empty");
        return;
    }
    if(pointer == NULL){
        perror("pointer is NULL");
        return;
    }
    //find allocated memory and delete it
    memory *allocated_current = allocated;
    memory *allocated_previous = NULL;
    while(allocated_current != NULL){
        //found node
        if(allocated_current -> start == pointer){
            //if allocated is not at the beggining of the linked list
            if(allocated_previous != NULL){
                allocated_previous -> next = allocated_current -> next;
            }
            else{
                allocated = allocated_current -> next;
            }
            break;
        }
        //didnt find node
        allocated_previous = allocated_current;
        allocated_current = allocated_current -> next;
    }

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //will reuse allocated_current(the pointer that is being deallocated) to put into the available link list since the start and size are the same. Just need to change next.
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    if(allocated_current == NULL){
        perror("could not find address");
        return;
    }

    allocated_current->next = NULL;

    memory *free_current = available;
    memory *free_previous = NULL;
    //add back into available linked list
    while(free_current != NULL){
        /*
            free_previous - the node that will be before the new node being inserted
            allocated_current - the node that is going to be inserted
            free_current - the node that will be after the new node being inserted
        */
        //found where to insert node
        if(free_current -> start > allocated_current -> start){
            //inserted node should be the first node of the Linked List
            if(free_previous == NULL){
                allocated_current -> next = free_current;
                available = allocated_current;
            }
            //insert in between free_previous and free_current
            else{
                allocated_current->next = free_current;
                free_previous->next = allocated_current;
            }
            //merge with the memory before allocated_current (new node) if adjacent
            if(free_previous != NULL && free_previous -> start + free_previous -> size == allocated_current -> start){
                free_previous -> size += allocated_current -> size;
                free_previous -> next = free_current;
                free(allocated_current);
                allocated_current = free_previous;
            }
            //merge memory after allocated_current (new node) if adjacent
            if(free_current -> start == allocated_current -> start + allocated_current -> size){
                allocated_current -> size += free_current -> size;
                allocated_current -> next = free_current -> next;
                free(free_current);
                //if you should insert at beginning
                if(free_previous == NULL){
                    available = allocated_current;
                }
            }
            break;
        }
        //didn't find where to insert
        else{
            free_previous = free_current;
            free_current = free_current -> next;
        }
    }
    // if the node should be inserted at the end of the list
    if (free_current == NULL) {
        //if available is empty
        if (free_previous == NULL) {
            available = allocated_current;
        }
        else {
            //insert at the end
            free_previous->next = allocated_current;
            // Merge with previous node if adjacent
            if (free_previous->start + free_previous->size == allocated_current->start) {
                free_previous->size += allocated_current->size;
                free_previous->next = NULL;
                free(allocated_current);
            }
        }
    }
}