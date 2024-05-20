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

template<typename T>
struct Node {
    Node<T>* ptrNext;
    Node<T>* ptrPrev;
    T iData;
};

template<typename T>
Node<T>* createNode(T iData);

template<typename T>
void insertNodeEnd(Node<T>** head, T iData);

template<typename T>
void unoptimizedRadixSort(Node<T>** head);

template<typename T>
void optimizedRadixSort(Node<T>** head);

template<typename T>
void printList(Node<T>* head);

template<typename T>
void generateRandomList(Node<T>** head, int size);

template<typename T>
void copyList(Node<T>** head1, Node<T>** head2);

template<typename T>
void isSorted(Node<T>** head);

#endif

