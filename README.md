# Custom Memory Allocator

A lightweight memory management system implementing core allocation functionality similar to `malloc` and `free`, built to demonstrate low-level memory management concepts.

## Project Overview
This custom allocator provides:
- Dynamic memory allocation/deallocation
- Block splitting and merging
- 8-byte aligned memory blocks
- First-fit allocation strategy

Key implementation details:
- Uses `mmap` to request 4KB memory pages from the OS
- Tracks free/allocated blocks via linked lists
- Handles block coalescing to reduce fragmentation

## Features

### Memory Management
- `init_alloc()`: Initializes memory pool
- `alloc(size)`: Allocates blocks (8-byte aligned)
- `dealloc(ptr)`: Releases memory and merges adjacent blocks
- `clean_up()`: Releases all resources

### Optimization
- Splits large blocks to fulfill smaller requests
- Merges adjacent free blocks automatically
- First-fit allocation strategy for efficiency

## Technical Implementation
- **Language**: C
- **System Calls**: `mmap`, `munmap`
- **Data Structures**: Linked list for block management
- **Alignment**: Enforces 8-byte minimum allocation

## Build & Test
```sh
git clone [your-repo-url]
cd memory-allocator
make
./allocator-test  # Runs built-in test suite
