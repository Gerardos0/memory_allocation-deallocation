#ifndef ALLOC_H
#define ALLOC_H

/*============================  Includes  ============================*/

#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

/*===========================  Constants  ============================*/

#define PAGESIZE 4096   // Made buffer size 4kb
#define MINALLOC 8      // Need to allocate at least 8 bytes

/*===============  Linked list node for memory blocks  ===============*/

typedef struct memory {
    int size;              // Size of the memory block in node
    char *start;           // Starting address of the block
    struct memory *next;   // Pointer to next block
} memory;

/*=======================  Function Prototype  =======================*/

int main(void);
int init_alloc(void);
int clean_up(void);
char *alloc(int size);
void dealloc(char *ptr);

/*========================  Global Variables  ========================*/

extern char *page;             // Base address of allocated page
extern memory *available;      // List of free nodes
extern memory *allocated;      // List of used nodes

#endif // ALLOC_H