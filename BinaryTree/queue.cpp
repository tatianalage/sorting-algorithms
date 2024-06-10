#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

namespace Queues {

template <typename T>
Queue<T>* createQueue() {
    Queue<T>* ptrQueue = (Queue<T>*)malloc(sizeof(Queue<T>));
    if (ptrQueue == nullptr) {
        fprintf(stderr, "Error creating queue: malloc\n");
        exit(1);
    }
    ptrQueue->ptrFront = ptrQueue->ptrRear = nullptr;
    return ptrQueue;
}

template <typename T>
void enqueue(Queue<T>* ptrQueue, T data) {
    QueueNode<T>* ptrTemp = (QueueNode<T>*)malloc(sizeof(QueueNode<T>));
    if (ptrTemp == nullptr) {
        fprintf(stderr, "Error adding to queue: malloc\n");
        exit(1);
    }
    ptrTemp->data = data;
    ptrTemp->ptrNext = nullptr;
    if (ptrQueue->ptrRear == nullptr) {
        ptrQueue->ptrFront = ptrQueue->ptrRear = ptrTemp;
        return;
    }
    ptrQueue->ptrRear->ptrNext = ptrTemp;
    ptrQueue->ptrRear = ptrTemp;
}

template <typename T>
T dequeue(Queue<T>* ptrQueue) {
    if (ptrQueue->ptrFront == nullptr)
        return T(); // Return default-constructed instance for non-pointer types
    QueueNode<T>* ptrTemp = ptrQueue->ptrFront;
    T data = ptrTemp->data;
    ptrQueue->ptrFront = ptrQueue->ptrFront->ptrNext;
    if (ptrQueue->ptrFront == nullptr)
        ptrQueue->ptrRear = nullptr;
    free(ptrTemp); 
    return data;
}

template <typename T>
bool isQueueEmpty(Queue<T>* ptrQueue) {
    return (ptrQueue->ptrFront == nullptr);
}

template <typename T>
void deleteQueue(Queue<T>* ptrQueue) {
    while (!isQueueEmpty(ptrQueue)) {
        dequeue(ptrQueue);
    }
    free(ptrQueue);
}

// Explicit template instantiation
template Queue<int>* createQueue<int>();
template void enqueue<int>(Queue<int>*, int);
template int dequeue<int>(Queue<int>*);
template bool isQueueEmpty<int>(Queue<int>*);
template void deleteQueue<int>(Queue<int>*);

}
