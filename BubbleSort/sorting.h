#ifndef SORTING_H
#define SORTING_H

#include <fstream>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <cstdlib>

namespace Sorting {

    template<typename T>
    struct Node {
        Node *ptrNext;
        Node *ptrPrev;
        T iData;
    };

    template<typename T>
    Node<T> *createNode(T iData);

    template<typename T>
    void insertNodeEnd(Node<T> **head, T iData);

    template<typename T>
    void unoptimizedBubbleSort(Node<T> **head);

    template<typename T>
    void optimizedBubbleSort(Node<T> **head);

    template<typename T>
    void printList(Node<T> *head);

    template<typename T>
    void generateRandomList(Node<T> **head, int size);

    template<typename T>
    void copyList(Node<T> **head1, Node<T> **head2);

    template<typename T>
    bool isSorted(Node<T> *head);

    template<typename T>
    void testSortingAlgorithm(const char *algorithmName, void (*sortFunc)(Node<T> **), Node<T> *head, std::ofstream &outputFile);

}
#endif 
