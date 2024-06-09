#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

namespace Queues {

template <typename T>
Queue<T>* createQueue() {
    Queue<T>* ptrQueue = (Queue<T>*)malloc(sizeof(Queue<T>));
    if (ptrQueue == NULL) {
        fprintf(stderr, "Error creating queue: malloc\n");
        exit(1);
    }
    ptrQueue->ptrFront = ptrQueue->ptrRear = NULL;
    return ptrQueue;
}

template <typename T>
void enqueue(Queue<T>* ptrQueue, T data) {
    QueueNode<T>* ptrTemp = (QueueNode<T>*)malloc(sizeof(QueueNode<T>));
    if (ptrTemp == NULL) {
        fprintf(stderr, "Error adding to queue: malloc\n");
        exit(1);
    }
    ptrTemp->data = data;
    ptrTemp->ptrNext = NULL;
    if (ptrQueue->ptrRear == NULL) {
        ptrQueue->ptrFront = ptrQueue->ptrRear = ptrTemp;
        return;
    }
    ptrQueue->ptrRear->ptrNext = ptrTemp;
    ptrQueue->ptrRear = ptrTemp;
}

template <typename T>
T dequeue(Queue<T>* ptrQueue) {
    if (ptrQueue->ptrFront == NULL)
        return NULL;
    QueueNode<T>* ptrTemp = ptrQueue->ptrFront;
    T data = ptrTemp->data;
    ptrQueue->ptrFront = ptrQueue->ptrFront->ptrNext;
    if (ptrQueue->ptrFront == NULL)
        ptrQueue->ptrRear = NULL;
    free(ptrTemp);
    return data;
}

template <typename T>
bool isQueueEmpty(Queue<T>* ptrQueue) {
    return (ptrQueue->ptrFront == NULL);
}

template <typename T>
void deleteQueue(Queue<T>* ptrQueue) {
    while (!isQueueEmpty(ptrQueue)) {
        dequeue(ptrQueue);
    }
    free(ptrQueue);
}

} 