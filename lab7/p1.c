#include <stdio.h>
#include <stdlib.h>

struct mab {
    int offset;
    int size;
    int allocated;
    struct mab *next;
    struct mab *prev;
};

typedef struct mab Mab;
typedef Mab *MabPtr;

// Function prototypes
MabPtr memChk(MabPtr m, int size);
MabPtr memAlloc(MabPtr m, int size);
MabPtr memFree(MabPtr m);
MabPtr memMerge(MabPtr m);
MabPtr memSplit(MabPtr m, int size);

// Helper function to print memory blocks
void printMemory(MabPtr m);

int main() {
    MabPtr memory = malloc(sizeof(Mab));
    memory->offset = 0;
    memory->size = 100; // Initial size of memory
    memory->allocated = 0;
    memory->next = NULL;
    memory->prev = NULL;

    // Allocate memory blocks
    memory = memAlloc(memory, 20);
    memory = memAlloc(memory, 30);
    memory = memAlloc(memory, 15);

    // Free a memory block
    memory = memFree(memory);

    // Print the final state of memory
    printMemory(memory);

    // Clean up: free allocated memory
    while (memory != NULL) {
        MabPtr temp = memory;
        memory = memory->next;
        free(temp);
    }

    return 0;
}

// Check if memory of a given size is available
MabPtr memChk(MabPtr m, int size) {
    while (m != NULL) {
        if (!m->allocated && m->size >= size) {
            return m;
        }
        m = m->next;
    }
    return NULL;
}

// Allocate a memory block using First Fit strategy
MabPtr memAlloc(MabPtr m, int size) {
    MabPtr block = memChk(m, size);

    if (block != NULL) {
        block->allocated = 1;
        if (block->size > size) {
            block = memSplit(block, size);
        }
    } else {
        printf("Memory allocation failed. No suitable block found.\n");
    }

    return m;
}

// Free a memory block
MabPtr memFree(MabPtr m) {
    if (m != NULL && m->allocated) {
        m->allocated = 0;
        m = memMerge(m);
    } else {
        printf("Memory free failed. Block not allocated or memory is empty.\n");
    }

    return m;
}

// Merge adjacent free memory blocks
MabPtr memMerge(MabPtr m) {
    if (m != NULL) {
        MabPtr current = m;
        while (current != NULL && !current->allocated) {
            MabPtr nextBlock = current->next;
            if (nextBlock != NULL && !nextBlock->allocated) {
                // Merge current block with the next block
                current->size += nextBlock->size;
                current->next = nextBlock->next;
                if (nextBlock->next != NULL) {
                    nextBlock->next->prev = current;
                }
                free(nextBlock);
            }
            current = current->next;
        }
    }
    return m;
}

// Split a memory block into two parts
MabPtr memSplit(MabPtr m, int size) {
    if (m != NULL && m->size > size) {
        MabPtr newBlock = malloc(sizeof(Mab));
        newBlock->offset = m->offset + size;
        newBlock->size = m->size - size;
        newBlock->allocated = 0;
        newBlock->next = m->next;
        newBlock->prev = m;
        if (m->next != NULL) {
            m->next->prev = newBlock;
        }
        m->size = size;
        m->next = newBlock;
    }
    return m;
}

// Helper function to print memory blocks
void printMemory(MabPtr m) {
    printf("Memory Layout:\n");
    while (m != NULL) {
        printf("Offset: %d, Size: %d, Allocated: %s\n",
               m->offset, m->size, m->allocated ? "Yes" : "No");
        m = m->next;
    }
}
