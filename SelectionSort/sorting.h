
#ifndef SORTING_H
#define SORTING_H

#include <iostream>

namespace SortingAlgorithms {
    template<typename T>
    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }
}

typedef struct _node
{
    struct _node *ptrNext;
    struct _node *ptrPrev;
    int iData;
} Node;

Node *createNode(int iData);
void insertNodeEnd(Node **head, int iData);
void swapData(Node *node1, Node *node2);
void printList(Node *head);
void generateRandomList(Node **head, int size);
void copyList(Node **head1, Node **head2);
void isSorted(Node **head);
void unoptimizedSelectionSort(Node **head);
void optimizedSelectionSort(Node **head);

#endif // SORTING_H
