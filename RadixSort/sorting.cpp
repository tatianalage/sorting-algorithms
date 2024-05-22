#include "sorting.h"
#include <cstdlib>
#include <ctime>

using namespace std;

namespace SortingAlgorithms
{

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

    template <typename T>
    void optimizedRadixSort(Node<T> **head)
    {
        if (!*head)
        {
            cout << "List is empty" << endl;
            return;
        }

        Node<T> *tmpNode = *head;
        T maxValue = tmpNode->iData;

        while (tmpNode)
        {
            if (tmpNode->iData > maxValue)
                maxValue = tmpNode->iData;
            tmpNode = tmpNode->ptrNext;
        }

        int exp = 1;

        while (maxValue / exp > 0)
        {
            Node<T> *bucket[10] = {nullptr};
            Node<T> *bucketEnd[10] = {nullptr};

            tmpNode = *head;
            while (tmpNode)
            {
                int bucketIdx = (tmpNode->iData / exp) % 10;
                if (bucket[bucketIdx] == nullptr)
                {
                    bucket[bucketIdx] = tmpNode;
                }
                else
                {
                    bucketEnd[bucketIdx]->ptrNext = tmpNode;
                }
                bucketEnd[bucketIdx] = tmpNode;
                tmpNode = tmpNode->ptrNext;
            }

            for (int i = 0; i < 10; i++) {
                cout << "Bucket " << i << ": ";
                printList(bucket[i]);
            }
            cout << endl;       

            Node<T> *newHead = nullptr;
            Node<T> *newTail = nullptr;
            for (int i = 0; i < 10; i++)
            {
                if (bucket[i])
                {
                    if (!newHead)
                    {
                        newHead = bucket[i];
                        newTail = bucketEnd[i];
                    }
                    else
                    {
                        newTail->ptrNext = bucket[i];
                        newTail = bucketEnd[i];
                    }
                }
            }
            newTail->ptrNext = nullptr;
            *head = newHead;
            exp *= 10;
        }
        std::cout << "\nSorted Linked List: ";
        printList(*head);
    }

    template <typename T>
    void unoptimizedRadixSort(Node<T> **head)
    {
        optimizedRadixSort(head);
    }

    template <typename T>
    void printList(Node<T> *head)
    {
        Node<T> *temp = head;
        while (temp)
        {
            cout << temp->iData << " ";
            temp = temp->ptrNext;
        }
        cout << endl;
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
                cout << "NOT SORTED" << endl;
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
}
