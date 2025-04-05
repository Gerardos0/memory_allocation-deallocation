#include "alloc.h"

char *page = NULL;
memory *available = NULL;
memory *allocated = NULL;

char *alloc(int buffer){
    //if wanted memory is not a multiple of 8
    if(buffer % MINALLOC != 0){
        return NULL;
    }

    //look for a node that has enough memory to give to user
    memory *previous = NULL;
    memory *current = available;
    while(current != NULL){
        if(current -> size >= buffer){
            break;
        }
        else{
            previous = current;
            current = current -> next;
        }
    }
    //if no memory available
    if(current == NULL){
        return NULL;
    }

    //create a node to put into the allocated(used) linked list
    memory *new_allocation = (memory *)malloc(sizeof(memory));
    if(new_allocation == NULL){
        perror("allocation failed");
        return NULL;
    }

    //add to linked list
    new_allocation -> start = current -> start;
    new_allocation -> size = buffer;
    new_allocation -> next = allocated;
    allocated = new_allocation;


    //split the memory(node) if the amount of memory the node has is more than what is wanted
    if(current -> size != buffer){
        current -> start = current -> start + buffer;
        current -> size = current -> size - buffer;
    }
    //else delete the node since it has no more memory
    else{
        if(previous != NULL){
            previous -> next = current -> next;
        }
        else{
            available = current -> next;
        }
        free(current);
    }
    //return pointer to memory allocated
    return new_allocation -> start;
}
