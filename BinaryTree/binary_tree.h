#ifndef BINARY_TREE_H
#define BINARY_TREE_H

namespace BinaryTree {

template <typename T>
struct Node {
    T iPayload;
    Node* ptrLeft;
    Node* ptrRight;
};

template <typename T>
Node<T>* createNode(T iValue);
template <typename T>
Node<T>* insertNode(Node<T>* ptrStartingNode, T iData);
template <typename T>
Node<T>* searchNodeBFS(Node<T>* ptrStartingNode, T iData);
template <typename T>
Node<T>* searchNodeDFS(Node<T>* ptrStartingNode, T iData);
template <typename T>
Node<T>* lesserLeaf(Node<T>* ptrStartingNode);
template <typename T>
Node<T>* deleteNode(Node<T>* ptrStartingNode, T iData);
template <typename T>
void traversePreOrder(Node<T>* ptrStartingNode);
template <typename T>
void traverseInOrder(Node<T>* ptrStartingNode);
template <typename T>
void traversePostOrder(Node<T>* ptrStartingNode);
template <typename T>
int treeHeight(Node<T>* ptrStartingNode);
} 

#endif 