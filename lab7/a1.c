#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Block structure representing a memory block
typedef struct Block {
    int size;            // Size of the block
    bool isAllocated;    // Flag indicating whether the block is allocated
    struct Block* next;  // Pointer to the next block in the free list
} Block;

// Buddy System structure
typedef struct {
    int totalMemory;     // Total memory size
    int smallestBlockSize; // Smallest block size in the system
    Block* freeLists[32]; // Array of free lists for each block size (2^0 to 2^31)
} BuddySystem;

// Function prototypes
BuddySystem* initializeBuddySystem(int totalMemory);
void printBuddySystem(BuddySystem* buddySystem);
void* allocateMemory(BuddySystem* buddySystem, int size);
void deallocateMemory(BuddySystem* buddySystem, void* ptr);

// Helper function prototypes
int calculateBlockSize(int size);
int calculateBuddyIndex(int blockSize, int index);
Block* findBuddy(Block* block, int blockSize);
void removeFromFreeList(BuddySystem* buddySystem, Block* block);
void addToFreeList(BuddySystem* buddySystem, Block* block);

int main() {
    int totalMemory = 1024; // Example: Total memory size is 1024 bytes
    BuddySystem* buddySystem = initializeBuddySystem(totalMemory);

    // Allocate memory using the Buddy System
    void* ptr1 = allocateMemory(buddySystem, 64);
    void* ptr2 = allocateMemory(buddySystem, 128);

    // Print the state of the Buddy System
    printBuddySystem(buddySystem);

    // Deallocate memory
    deallocateMemory(buddySystem, ptr1);

    // Print the state of the Buddy System after deallocation
    printBuddySystem(buddySystem);

    // Deallocate memory
    deallocateMemory(buddySystem, ptr2);

    // Print the state of the Buddy System after deallocation
    printBuddySystem(buddySystem);

    // Clean up: free allocated memory
    free(buddySystem);

    return 0;
}

// Initialize the Buddy System with the specified total memory size
BuddySystem* initializeBuddySystem(int totalMemory) {
    BuddySystem* buddySystem = (BuddySystem*)malloc(sizeof(BuddySystem));
    buddySystem->totalMemory = totalMemory;
    buddySystem->smallestBlockSize = 1;

    // Initialize the free lists
    for (int i = 0; i < 32; ++i) {
        buddySystem->freeLists[i] = NULL;
    }

    // Create the initial block representing the entire memory
    Block* initialBlock = (Block*)malloc(sizeof(Block));
    initialBlock->size = totalMemory;
    initialBlock->isAllocated = false;
    initialBlock->next = NULL;

    // Add the initial block to the free list
    addToFreeList(buddySystem, initialBlock);

    return buddySystem;
}

// Allocate memory of the specified size using the Buddy System
void* allocateMemory(BuddySystem* buddySystem, int size) {
    // Calculate the block size required for the allocation
    int blockSize = calculateBlockSize(size);

    // Find the appropriate free list for the allocation
    int listIndex = (int)log2(blockSize) - buddySystem->smallestBlockSize;
    
    // Iterate through the free lists to find a suitable block
    for (int i = listIndex; i < 32; ++i) {
        if (buddySystem->freeLists[i] != NULL) {
            // Remove the block from the free list
            Block* allocatedBlock = buddySystem->freeLists[i];
            buddySystem->freeLists[i] = allocatedBlock->next;

            // Mark the block as allocated
            allocatedBlock->isAllocated = true;

            // Return the memory address of the allocated block
            return (void*)allocatedBlock;
        }
    }

    // If no suitable block is found, return NULL (out of memory)
    return NULL;
}

// Deallocate memory at the specified address using the Buddy System
void deallocateMemory(BuddySystem* buddySystem, void* ptr) {
    // Cast the pointer to the Block type
    Block* deallocatedBlock = (Block*)ptr;

    // Mark the block as deallocated
    deallocatedBlock->isAllocated = false;

    // Add the block back to the free list
    addToFreeList(buddySystem, deallocatedBlock);

    // Coalesce free blocks if possible
    int blockSize = deallocatedBlock->size;
    int buddyIndex = calculateBuddyIndex(blockSize, deallocatedBlock->size);
    Block* buddy = findBuddy(deallocatedBlock, blockSize);

    while (buddy != NULL && !buddy->isAllocated) {
        // Remove the buddy from the free list
        removeFromFreeList(buddySystem, buddy);

        // Combine the current block and its buddy into a larger block
        deallocatedBlock = (buddy < deallocatedBlock) ? buddy : deallocatedBlock;
        deallocatedBlock->size *= 2;

        // Find the new buddy index for the merged block
        buddyIndex = calculateBuddyIndex(deallocatedBlock->size, buddyIndex);
        buddy = findBuddy(deallocatedBlock, deallocatedBlock->size);
    }
}

// Print the state of the Buddy System
void printBuddySystem(BuddySystem* buddySystem) {
    printf("Buddy System State:\n");

    for (int i = 0; i < 32; ++i) {
        printf("Free List %d: ", i);
        Block* current = buddySystem->freeLists[i];

        while (current != NULL) {
            printf("[Size: %d, Allocated: %s] -> ", current->size, current->isAllocated ? "Yes" : "No");
            current = current->next;
        }

        printf("NULL\n");
    }

    printf("\n");
}

// Calculate the block size required for the allocation
int calculateBlockSize(int size) {
    int blockSize = 1;

    while (blockSize < size) {
        blockSize *= 2;
    }

    return blockSize;
}

// Calculate the index of the buddy in the free list
int calculateBuddyIndex(int blockSize, int index) {
    return (index / blockSize) % 2 == 0 ? index + blockSize : index - blockSize;
}

// Find the buddy of a block in the free list
Block* findBuddy(Block* block, int blockSize) {
    int buddyIndex = (int)((unsigned long)block / blockSize) % 2 == 0 ? block->size : -block->size;
    return (Block*)((unsigned long)block ^ buddyIndex);
}

// Remove a block from the free list
void removeFromFreeList(BuddySystem* buddySystem, Block* block) {
    int listIndex = (int)log2(block->size) - buddySystem->smallestBlockSize;

    Block* current = buddySystem->freeLists[listIndex];
    Block* prev = NULL;

    while (current != NULL && current != block) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (prev != NULL) {
            prev->next = current->next;
        } else {
            buddySystem->freeLists[listIndex] = current->next;
        }
    }
}

// Add a block to the free list
void addToFreeList(BuddySystem* buddySystem, Block* block) {
    int listIndex = (int)log2(block->size) - buddySystem->smallestBlockSize;
    block->next = buddySystem->freeLists[listIndex];
    buddySystem->freeLists[listIndex] = block;
}
