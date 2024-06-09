// binary_tree.cpp
#include "binary_tree.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

namespace BinaryTree {

template <typename T>
Node<T>* createNode(T iValue) {
    Node<T>* ptrNode = (Node<T>*)malloc(sizeof(Node<T>));
    if (ptrNode == NULL) {
        exit(1);
    }
    ptrNode->iPayload = iValue;
    ptrNode->ptrLeft = NULL;
    ptrNode->ptrRight = NULL;
    return ptrNode;
}

template <typename T>
Node<T>* insertNode(Node<T>* ptrStartingNode, T iData) {
    if (ptrStartingNode == NULL) {
        return createNode(iData);
    }
    if (iData < ptrStartingNode->iPayload) {
        ptrStartingNode->ptrLeft = insertNode(ptrStartingNode->ptrLeft, iData);
    } else {
        ptrStartingNode->ptrRight = insertNode(ptrStartingNode->ptrRight, iData);
    }
    return ptrStartingNode;
}

template <typename T>
Node<T>* searchNodeBFS(Node<T>* ptrStartingNode, T iData) {
    if (ptrStartingNode == NULL) return NULL;

    Queues::Queue<Node<T>*>* ptrQueue = Queues::createQueue<Node<T>*>();
    Queues::enqueue(ptrQueue, ptrStartingNode);

    while (!Queues::isQueueEmpty(ptrQueue)) {
        Node<T>* ptrCurrentNode = Queues::dequeue(ptrQueue);
        if (ptrCurrentNode->iPayload == iData) {
            Queues::deleteQueue(ptrQueue);
            return ptrCurrentNode;
        }
        if (ptrCurrentNode->ptrLeft != NULL) {
            Queues::enqueue(ptrQueue, ptrCurrentNode->ptrLeft);
        }
        if (ptrCurrentNode->ptrRight != NULL) {
            Queues::enqueue(ptrQueue, ptrCurrentNode->ptrRight);
        }
    }

    Queues::deleteQueue(ptrQueue);
    return NULL;
}

template <typename T>
Node<T>* searchNodeDFS(Node<T>* ptrStartingNode, T iData) {
    if (ptrStartingNode == NULL) return NULL;
    if (iData == ptrStartingNode->iPayload) return ptrStartingNode;

    Node<T>* ptrLeftResult = searchNodeDFS(ptrStartingNode->ptrLeft, iData);
    if (ptrLeftResult != NULL) return ptrLeftResult;

    return searchNodeDFS(ptrStartingNode->ptrRight, iData);
}

template <typename T>
Node<T>* lesserLeaf(Node<T>* ptrStartingNode) {
    Node<T>* ptrCurrent = ptrStartingNode;
    while (ptrCurrent && ptrCurrent->ptrLeft != NULL) ptrCurrent = ptrCurrent->ptrLeft;
    return ptrCurrent;
}

template <typename T>
Node<T>* deleteNode(Node<T>* ptrStartingNode, T iData) {
    if (ptrStartingNode == NULL) return NULL;

    if (iData < ptrStartingNode->iPayload) ptrStartingNode->ptrLeft = deleteNode(ptrStartingNode->ptrLeft, iData);
    else if (iData > ptrStartingNode->iPayload) ptrStartingNode->ptrRight = deleteNode(ptrStartingNode->ptrRight, iData);
    else {
        Node<T>* ptrTemp = NULL;

        if (ptrStartingNode->ptrLeft == NULL) {
            ptrTemp = ptrStartingNode->ptrRight;
            free(ptrStartingNode);
            return ptrTemp;
        } else if (ptrStartingNode->ptrRight == NULL) {
            ptrTemp = ptrStartingNode->ptrLeft;
            free(ptrStartingNode);
            return ptrTemp;
        }

        ptrTemp = lesserLeaf(ptrStartingNode->ptrRight);
        ptrStartingNode->iPayload = ptrTemp->iPayload;
        ptrStartingNode->ptrRight = deleteNode(ptrStartingNode->ptrRight, ptrTemp->iPayload);
    }

    return ptrStartingNode;
}

template <typename T>
void traversePreOrder(Node<T>* ptrStartingNode) {
    if (ptrStartingNode != NULL) {
        printf(" %d", ptrStartingNode->iPayload);
        traversePreOrder(ptrStartingNode->ptrLeft);
        traversePreOrder(ptrStartingNode->ptrRight);
    }
}

template <typename T>
void traverseInOrder(Node<T>* ptrStartingNode) {
    if (ptrStartingNode != NULL) {
        traverseInOrder(ptrStartingNode->ptrLeft);
        printf(" %d", ptrStartingNode->iPayload);
        traverseInOrder(ptrStartingNode->ptrRight);
    }
}

template <typename T>
void traversePostOrder(Node<T>* ptrStartingNode) {
    if (ptrStartingNode != NULL) {
        traversePostOrder(ptrStartingNode->ptrLeft);
        traversePostOrder(ptrStartingNode->ptrRight);
        printf(" %d", ptrStartingNode->iPayload);
    }
}

template <typename T>
int treeHeight(Node<T>* ptrStartingNode) {
    if (ptrStartingNode == NULL) return 0;
    else {
        int iLeftHeight = treeHeight(ptrStartingNode->ptrLeft);
        int iRightHeight = treeHeight(ptrStartingNode->ptrRight);
        return (iLeftHeight > iRightHeight ? iLeftHeight : iRightHeight) + 1;
    }
}

}