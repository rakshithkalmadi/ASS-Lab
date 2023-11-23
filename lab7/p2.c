#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

// Process structure
typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
} Process;

// Queue structure
typedef struct {
    Process* processes[MAX_PROCESSES];
    int front, rear;
} Queue;

// Function prototypes
Queue* createQueue();
void enqueue(Queue* q, Process* process);
Process* dequeue(Queue* q);
int isQueueEmpty(Queue* q);

// Scheduling policies
void roundRobin(Queue* queue);
void priority(Queue* queue);
void firstComeFirstServe(Queue* queue);

int main() {
    Queue* queue1 = createQueue(); // Round Robin
    Queue* queue2 = createQueue(); // Priority
    Queue* queue3 = createQueue(); // First Come First Serve

    // Initialize processes (you can modify this with your own processes)
    Process* processes[MAX_PROCESSES];
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        processes[i] = (Process*)malloc(sizeof(Process));
        processes[i]->process_id = i + 1;
        processes[i]->arrival_time = i * 2;
        processes[i]->burst_time = (i + 1) * 3;
        processes[i]->priority = (i + 1) % 5;
        processes[i]->remaining_time = processes[i]->burst_time;

        // Enqueue processes based on priority
        if (processes[i]->priority <= 2) {
            enqueue(queue1, processes[i]); // Round Robin
        } else if (processes[i]->priority <= 4) {
            enqueue(queue2, processes[i]); // Priority
        } else {
            enqueue(queue3, processes[i]); // First Come First Serve
        }
    }

    // Schedule processes based on different policies
    roundRobin(queue1);
    priority(queue2);
    firstComeFirstServe(queue3);

    // Clean up: free allocated memory
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        free(processes[i]);
    }

    free(queue1);
    free(queue2);
    free(queue3);

    return 0;
}

// Function to create an empty queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = -1;
    return queue;
}

// Function to check if the queue is empty
int isQueueEmpty(Queue* q) {
    return q->front == -1;
}

// Function to enqueue a process into the queue
void enqueue(Queue* q, Process* process) {
    if (q->rear == MAX_PROCESSES - 1) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }

    if (isQueueEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear++;
    }

    q->processes[q->rear] = process;
}

// Function to dequeue a process from the queue
Process* dequeue(Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return NULL;
    }

    Process* process = q->processes[q->front];

    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }

    return process;
}

// Round Robin scheduling policy
void roundRobin(Queue* queue) {
    printf("Round Robin Queue:\n");
    while (!isQueueEmpty(queue)) {
        Process* process = dequeue(queue);
        printf("Running Process %d (Time: %d)\n", process->process_id, process->remaining_time);

        // Simulate execution (decrement remaining time)
        process->remaining_time -= 2;

        // Enqueue the process back if it's not finished
        if (process->remaining_time > 0) {
            enqueue(queue, process);
        }
    }
}

// Priority scheduling policy
void priority(Queue* queue) {
    printf("\nPriority Queue:\n");
    while (!isQueueEmpty(queue)) {
        Process* process = dequeue(queue);
        printf("Running Process %d (Priority: %d)\n", process->process_id, process->priority);

        // Simulate execution (decrement remaining time)
        process->remaining_time -= 3;

        // Enqueue the process back if it's not finished
        if (process->remaining_time > 0) {
            enqueue(queue, process);
        }
    }
}

// First Come First Serve scheduling policy
void firstComeFirstServe(Queue* queue) {
    printf("\nFirst Come First Serve Queue:\n");
    while (!isQueueEmpty(queue)) {
        Process* process = dequeue(queue);
        printf("Running Process %d (Arrival Time: %d)\n", process->process_id, process->arrival_time);

        // Simulate execution (decrement remaining time)
        process->remaining_time -= 4;

        // Enqueue the process back if it's not finished
        if (process->remaining_time > 0) {
            enqueue(queue, process);
        }
    }
}
