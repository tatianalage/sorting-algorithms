#include "sorting.h"
#include <cstdlib>
#include <ctime>

template<typename T>
Node<T>* createNode(T iData) {
    Node<T>* newNode = (Node<T>*)malloc(sizeof(Node<T>));
    newNode->ptrNext = nullptr;
    newNode->ptrPrev = nullptr;
    newNode->iData = iData;
    return newNode;
}

template<typename T>
void insertNodeEnd(Node<T>** head, T iData) {
    Node<T>* newNode = createNode(iData);
    if (*head) {
        Node<T>* temp = *head;
        while (temp->ptrNext) {
            temp = temp->ptrNext;
        }
        temp->ptrNext = newNode;
        newNode->ptrPrev = temp;
    } else {
        *head = newNode;
    }
}

template<typename T>
void unoptimizedInsertionSort(Node<T>** head) {
    for (Node<T>* node1 = *head; node1 != nullptr; node1 = node1->ptrNext) {
        for (Node<T>* node2 = node1; node2 != nullptr; node2 = node2->ptrPrev) {
            if (node2->ptrPrev != nullptr && node2->iData < node2->ptrPrev->iData) {
                SortingAlgorithms::swap(node2->iData, node2->ptrPrev->iData);
            }
        }
    }
}

template<typename T>
void optimizedInsertionSort(Node<T>** head) {
    Node<T>* sortedNode = nullptr;
    Node<T>* currentNode = *head;
    while (currentNode != nullptr) {
        Node<T>* nextNode = currentNode->ptrNext;
        if (sortedNode == nullptr || currentNode->iData < sortedNode->iData) {
            currentNode->ptrNext = sortedNode;
            if (sortedNode != nullptr) {
                sortedNode->ptrPrev = currentNode;
            }
            sortedNode = currentNode;
            sortedNode->ptrPrev = nullptr;
        } else {
            Node<T>* temp = sortedNode;
            while (temp->ptrNext != nullptr && temp->ptrNext->iData < currentNode->iData) {
                temp = temp->ptrNext;
            }
            currentNode->ptrNext = temp->ptrNext;
            if (temp->ptrNext != nullptr) {
                temp->ptrNext->ptrPrev = currentNode;
            }
            temp->ptrNext = currentNode;
            currentNode->ptrPrev = temp;
        }
        currentNode = nextNode;
    }
    *head = sortedNode;
}

template<typename T>
void printList(Node<T>* head) {
    Node<T>* temp = head;
    while (temp) {
        std::cout << temp->iData << " ";
        temp = temp->ptrNext;
    }
    std::cout << std::endl;
}

template<typename T>
void generateRandomList(Node<T>** head, int size) {
    srand(time(nullptr));
    for (int i = 0; i < size; ++i) {
        T randomNum = rand() % 100;
        insertNodeEnd(head, randomNum);
    }
}

template<typename T>
void copyList(Node<T>** head1, Node<T>** head2) {
    if (*head1 == nullptr) {
        return;
    }
    Node<T>* temp = *head1;
    while (temp) {
        insertNodeEnd(head2, temp->iData);
        temp = temp->ptrNext;
    }
}

template<typename T>
void isSorted(Node<T>** head) {
    Node<T>* temp = *head;
    while (temp->ptrNext) {
        if (temp->iData > temp->ptrNext->iData) {
            std::cout << "NOT SORTED" << std::endl;
            exit(1);
        }
        temp = temp->ptrNext;
    }
}

// Explicit template instantiation for int to match the main program's usage
template Node<int>* createNode<int>(int);
template void insertNodeEnd<int>(Node<int>**, int);
template void unoptimizedInsertionSort<int>(Node<int>**);
template void optimizedInsertionSort<int>(Node<int>**);
template void printList<int>(Node<int>*);
template void generateRandomList<int>(Node<int>**, int);
template void copyList<int>(Node<int>**, Node<int>**);
template void isSorted<int>(Node<int>**);
