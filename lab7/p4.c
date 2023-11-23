#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3
#define MAX_PAGES 12

typedef struct {
    int page_id;
    int referenced;
} Page;

typedef struct {
    Page pages[MAX_FRAMES];
    int count;
} FrameTable;

int isPageInMemory(FrameTable* frameTable, int page_id) {
    for (int i = 0; i < frameTable->count; ++i) {
        if (frameTable->pages[i].page_id == page_id) {
            return 1; // Page is in memory
        }
    }
    return 0; // Page is not in memory
}

void addToMemory(FrameTable* frameTable, int page_id) {
    if (frameTable->count < MAX_FRAMES) {
        // Add page to an empty frame
        frameTable->pages[frameTable->count].page_id = page_id;
        frameTable->pages[frameTable->count].referenced = 1;
        frameTable->count++;
    } else {
        // Use Second Chance algorithm to replace a page
        int replaced = 0;
        while (!replaced) {
            for (int i = 0; i < frameTable->count; ++i) {
                if (frameTable->pages[i].referenced) {
                    // Set the reference bit to 0 and move to the next frame
                    frameTable->pages[i].referenced = 0;
                } else {
                    // Replace the page and set the reference bit to 1
                    frameTable->pages[i].page_id = page_id;
                    frameTable->pages[i].referenced = 1;
                    replaced = 1;
                    break;
                }
            }
        }
    }
}

void simulateLRU(FrameTable* frameTable, int pages[], int num_pages) {
    int page_faults = 0;
    int hits = 0;

    for (int i = 0; i < num_pages; ++i) {
        int page_id = pages[i];

        if (isPageInMemory(frameTable, page_id)) {
            // Page hit
            hits++;
        } else {
            // Page fault
            page_faults++;
            addToMemory(frameTable, page_id);
        }
    }

    // Print results
    printf("Total Page Faults: %d\n", page_faults);
    printf("Hit Ratio: %.2f%%\n", (float)hits / num_pages * 100);
}

int main() {
    FrameTable frameTable = { .count = 0 };

    // Example sequence of page references
    int page_reference_sequence[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};

    // Simulate LRU approximation page replacement using Second Chance algorithm
    simulateLRU(&frameTable, page_reference_sequence, sizeof(page_reference_sequence) / sizeof(int));

    return 0;
}
