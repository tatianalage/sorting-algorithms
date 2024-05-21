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
void unoptimizedBubbleSort(Node<T>** head) {
    bool bUnordered = true;
    while (bUnordered) {
        bUnordered = false;
        Node<T>* currNode = *head;
        while (currNode->ptrNext != nullptr) {
            if (currNode->iData > currNode->ptrNext->iData) {
                SortingAlgorithms::swap(currNode->iData, currNode->ptrNext->iData);
                bUnordered = true;
            }
            currNode = currNode->ptrNext;
        }
    }
}

template<typename T>
void optimizedBubbleSort(Node<T>** head) {
    Node<T>* lastNode = nullptr;
    do {
        bool bUnordered = false;
        Node<T>* currNode = *head;
        while (currNode->ptrNext != lastNode) {
            if (currNode->iData > currNode->ptrNext->iData) {
                SortingAlgorithms::swap(currNode->iData, currNode->ptrNext->iData);
                bUnordered = true;
            }
            currNode = currNode->ptrNext;
        }
        lastNode = currNode;
    } while (lastNode != *head);
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

template Node<int>* createNode<int>(int);
template void insertNodeEnd<int>(Node<int>**, int);
template void unoptimizedBubbleSort<int>(Node<int>**);
template void optimizedBubbleSort<int>(Node<int>**);
template void printList<int>(Node<int>*);
template void generateRandomList<int>(Node<int>**, int);
template void copyList<int>(Node<int>**, Node<int>**);
template void isSorted<int>(Node<int>**);
