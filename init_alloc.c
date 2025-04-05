#include "alloc.h"

int init_alloc(){
    //allocate memory
    page = mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    if (page == MAP_FAILED) {
        perror("mmap failed");
        return -1;
    }


    //node showing 4kb of available memory
    available = (memory *)malloc(sizeof(memory));
    if(available == NULL){
        perror("availble creation failed");
        munmap(page, PAGESIZE);
        return -1;
    }
    //set up node
    available -> size = PAGESIZE;
    available -> start = page;
    available -> next = NULL;
    //return success
    return 0;
}