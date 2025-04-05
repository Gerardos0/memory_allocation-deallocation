#include "alloc.h"

int clean_up(){
    if(page == NULL){
        return -1;
    }
    //deallocate allocateed 4kb
    char status = munmap(page, PAGESIZE);
    if(status == -1){
        perror("munmap failed");
        return -1;
    }

    //daellocate the linked lists
    memory *current = available;
    while(current != NULL){
        memory *temp = current;
        current = current -> next;
        free(temp);
    }

    current = allocated;
    while(current != NULL){
        memory *temp = current;
        current = current -> next;
        free(temp);
    }
    //set all pointers to NULL
    page = NULL;
    available = NULL;
    allocated = NULL;
    //return success
    return 0;
}