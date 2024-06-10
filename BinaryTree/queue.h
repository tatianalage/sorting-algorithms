#ifndef QUEUE_H
#define QUEUE_H

namespace Queues {

template <typename T>
struct QueueNode {
    T data;
    QueueNode* ptrNext;
};

template <typename T>
struct Queue {
    QueueNode<T>* ptrFront;
    QueueNode<T>* ptrRear;
};

template <typename T>
Queue<T>* createQueue();

template <typename T>
void enqueue(Queue<T>* ptrQueue, T data);

template <typename T>
T dequeue(Queue<T>* ptrQueue);

template <typename T>
bool isQueueEmpty(Queue<T>* ptrQueue);

template <typename T>
void deleteQueue(Queue<T>* ptrQueue);

} // namespace Queues

#endif // QUEUE_H
