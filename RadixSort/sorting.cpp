#include "sorting.h"
#include <cstdlib>
#include <ctime>

template <typename T>
Node<T> *createNode(T iData)
{
    Node<T> *newNode = (Node<T> *)malloc(sizeof(Node<T>));
    newNode->ptrNext = nullptr;
    newNode->ptrPrev = nullptr;
    newNode->iData = iData;
    return newNode;
}

template <typename T>
void insertNodeEnd(Node<T> **head, T iData)
{
    Node<T> *newNode = createNode(iData);
    if (*head)
    {
        Node<T> *temp = *head;
        while (temp->ptrNext)
        {
            temp = temp->ptrNext;
        }
        temp->ptrNext = newNode;
        newNode->ptrPrev = temp;
    }
    else
    {
        *head = newNode;
    }
}

/*
template <typename T>
void unoptimizedRadixSort(Node<T> **head)
{
    if(!*head){
        cout << "List is empty" << endl;
        return;
    }
    Node<T>*tmpNode = *head;
    T maxValue = tmpNode->iData;

    while(tmpNode)
    {
        if (tmpNode->iData > maxValue)
            maxValue = tmpNode->iData;
        tmpNode = tmpNode->ptrNext;
    }
    Node<T>*lastNode = tmpNode;

    int exp = 1;
    wile(maxValue/exp > 0){
        //Lista de nós
        Node<T>*bucket[10] = {nullptr};
        for(Node<T>*nodePass = *head; nodePass != nullptr ; nodePass = nodePass->ptrNext){
            int bucketIdx = (nodePass/exp)%10;
            for(i = 1; i < 10 ; i++){
                bucket[i] = bucket[i-1];
            }
            for(Node<T>*nodePrev = lastNode; nodePrev != nullptr ; nodePrev  = nodePrev->prtPrev){
                
            }


        }


    }

}
*/

template <typename T>
void optimizedRadixSort(Node<T> **head)
{
    if (*head == nullptr)
        return;

    Node<T> *tmpNode = *head;
    T maxValue = tmpNode->iData;
    while (tmpNode != nullptr)
    {
        if (tmpNode->iData > maxValue)
            maxValue = tmpNode->iData;
        tmpNode = tmpNode->ptrNext;
    }

    int exp = 1;
    while (maxValue / exp > 0)
    {
        Node<T> *buckets[10] = {nullptr};
        Node<T> *bucketTails[10] = {nullptr};

        tmpNode = *head;
        while (tmpNode != nullptr)
        {
            int bucketIdx = (tmpNode->iData / exp) % 10;
            Node<T> *nextNode = tmpNode->ptrNext;

            if (buckets[bucketIdx] == nullptr)
            {
                buckets[bucketIdx] = tmpNode;
                tmpNode->ptrPrev = nullptr;
                tmpNode->ptrNext = nullptr;
                bucketTails[bucketIdx] = tmpNode;
            }
            else
            {
                bucketTails[bucketIdx]->ptrNext = tmpNode;
                tmpNode->ptrPrev = bucketTails[bucketIdx];
                tmpNode->ptrNext = nullptr;
                bucketTails[bucketIdx] = tmpNode;
            }
            tmpNode = nextNode;
        }

        Node<T> *newHead = nullptr;
        Node<T> *newTail = nullptr;
        for (int i = 0; i < 10; ++i)
        {
            if (buckets[i] != nullptr)
            {
                if (newHead == nullptr)
                {
                    newHead = buckets[i];
                    newTail = bucketTails[i];
                }
                else
                {
                    newTail->ptrNext = buckets[i];
                    buckets[i]->ptrPrev = newTail;
                    newTail = bucketTails[i];
                }
            }
        }
        *head = newHead;
        exp *= 10;
    }
}

template <typename T>
void printList(Node<T> *head)
{
    Node<T> *temp = head;
    while (temp)
    {
        std::cout << temp->iData << " ";
        temp = temp->ptrNext;
    }
    std::cout << std::endl;
}

template <typename T>
void generateRandomList(Node<T> **head, int size)
{
    srand(time(nullptr));
    for (int i = 0; i < size; ++i)
    {
        T randomNum = rand() % 100;
        insertNodeEnd(head, randomNum);
    }
}

template <typename T>
void copyList(Node<T> **head1, Node<T> **head2)
{
    if (*head1 == nullptr)
    {
        return;
    }
    Node<T> *temp = *head1;
    while (temp)
    {
        insertNodeEnd(head2, temp->iData);
        temp = temp->ptrNext;
    }
}

template <typename T>
void isSorted(Node<T> **head)
{
    Node<T> *temp = *head;
    while (temp->ptrNext)
    {
        if (temp->iData > temp->ptrNext->iData)
        {
            std::cout << "NOT SORTED" << std::endl;
            exit(1);
        }
        temp = temp->ptrNext;
    }
}

template Node<int> *createNode<int>(int);
template void insertNodeEnd<int>(Node<int> **, int);
template void unoptimizedRadixSort<int>(Node<int> **);
template void optimizedRadixSort<int>(Node<int> **);
template void printList<int>(Node<int> *);
template void generateRandomList<int>(Node<int> **, int);
template void copyList<int>(Node<int> **, Node<int> **);
template void isSorted<int>(Node<int> **);
