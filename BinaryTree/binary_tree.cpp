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
    if (ptrStartingNode == nullptr) return nullptr;

    Queues::Queue<Node<T>*>* ptrQueue = Queues::createQueue<Node<T>*>();
    Queues::enqueue(ptrQueue, ptrStartingNode);

    while (!Queues::isQueueEmpty(ptrQueue)) {
        Node<T>* ptrCurrentNode = Queues::dequeue(ptrQueue);
        if (ptrCurrentNode->iPayload == iData) {
            Queues::deleteQueue(ptrQueue);
            return ptrCurrentNode;
        }
        if (ptrCurrentNode->ptrLeft != nullptr) {
            Queues::enqueue(ptrQueue, ptrCurrentNode->ptrLeft);
        }
        if (ptrCurrentNode->ptrRight != nullptr) {
            Queues::enqueue(ptrQueue, ptrCurrentNode->ptrRight);
        }
    }

    Queues::deleteQueue(ptrQueue);
    return nullptr;
}

template <typename T>
Node<T>* searchNodeDFS(Node<T>* ptrStartingNode, T iData) {
    if (ptrStartingNode == NULL) return NULL;
    if (iData == ptrStartingNode->iPayload) return ptrStartingNode;
    Node<T>* result = searchNodeDFS(ptrStartingNode->ptrLeft, iData);
    if (result != nullptr) return result;
    return searchNodeDFS(ptrStartingNode->ptrRight, iData);
}


template <typename T>
void traversePreOrder(Node<T>* ptrStartingNode) {
    if (ptrStartingNode != NULL) {
        printf("%d ", ptrStartingNode->iPayload);
        traversePreOrder(ptrStartingNode->ptrLeft);
        traversePreOrder(ptrStartingNode->ptrRight);
    }
}

template <typename T>
void traverseInOrder(Node<T>* ptrStartingNode) {
    if (ptrStartingNode != NULL) {
        traverseInOrder(ptrStartingNode->ptrLeft);
        //printf("%d ", ptrStartingNode->iPayload);
        traverseInOrder(ptrStartingNode->ptrRight);
    }
}

template <typename T>
void traversePostOrder(Node<T>* ptrStartingNode) {
    if (ptrStartingNode != NULL) {
        traversePostOrder(ptrStartingNode->ptrLeft);
        traversePostOrder(ptrStartingNode->ptrRight);
        //printf("%d ", ptrStartingNode->iPayload);
    }
}

template <typename T>
int treeHeight(Node<T>* ptrStartingNode) {
    if (ptrStartingNode == NULL) {
        return 0;
    } else {
        int leftHeight = treeHeight(ptrStartingNode->ptrLeft);
        int rightHeight = treeHeight(ptrStartingNode->ptrRight);

        if (leftHeight > rightHeight) {
            return(leftHeight + 1);
        } else {
            return(rightHeight + 1);
        }
    }
}

// Explicit template instantiation
template Node<int>* createNode<int>(int);
template Node<int>* insertNode<int>(Node<int>*, int);
template Node<int>* searchNodeBFS<int>(Node<int>*, int);
template Node<int>* searchNodeDFS<int>(Node<int>*, int);
template void traversePreOrder<int>(Node<int>*);
template void traverseInOrder<int>(Node<int>*);
template void traversePostOrder<int>(Node<int>*);
template int treeHeight<int>(Node<int>*);

}
