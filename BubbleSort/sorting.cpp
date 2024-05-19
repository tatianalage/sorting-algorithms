#include "sorting.h"


using namespace std;
using namespace chrono;

namespace Sorting {

    template<typename T>
    Node<T> *createNode(T iData) {
        Node<T> *newNode = new Node<T>;
        newNode->ptrNext = nullptr;
        newNode->ptrPrev = nullptr;
        newNode->iData = iData;
        return newNode;
    }

    template<typename T>
    void insertNodeEnd(Node<T> **head, T iData) {
        Node<T> *newNode = createNode(iData);
        if (*head) {
            Node<T> *temp = *head;
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
    void swapData(Node<T> *node1, Node<T> *node2) {
        T temp = node1->iData;
        node1->iData = node2->iData;
        node2->iData = temp;
    }

    template<typename T>
    void unoptimizedBubbleSort(Node<T> **head) {
        bool unordered = true;
        while (unordered) {
            unordered = false;
            Node<T> *currNode = *head;
            while (currNode->ptrNext) {
                if (currNode->iData > currNode->ptrNext->iData) {
                    swapData(currNode, currNode->ptrNext);
                    unordered = true;
                }
                currNode = currNode->ptrNext;
            }
        }
    }

    template<typename T>
    void optimizedBubbleSort(Node<T> **head) {
        Node<T> *lastNode = *head;
        while (lastNode->ptrNext) {
            lastNode = lastNode->ptrNext;
        }
        bool unordered = true;
        while (unordered) {
            unordered = false;
            Node<T> *currNode = *head;
            while (currNode != lastNode && currNode != nullptr) {
                if (currNode->iData > currNode->ptrNext->iData) {
                    swapData(currNode, currNode->ptrNext);
                    unordered = true;
                }
                currNode = currNode->ptrNext;
            }
            lastNode = lastNode->ptrPrev;
        }
    }

}
