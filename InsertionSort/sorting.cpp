// sorting.cpp

#include "sorting.h"

Node *createNode(int iData)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->ptrNext = nullptr;
    newNode->ptrPrev = nullptr;
    newNode->iData = iData;

    return newNode;
}

void insertNodeEnd(Node **head, int iData)
{
    Node *newNode = createNode(iData);
    if (*head)
    {
        Node *temp = *head;
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

void unoptimizedInsertionSort(Node **head)
{
    for (Node *node1 = *head; node1 != nullptr; node1 = node1->ptrNext)
    {
        for (Node *node2 = node1; node2 != nullptr; node2 = node2->ptrPrev)
        {
            if (node2->ptrPrev != nullptr && node2->iData < node2->ptrPrev->iData)
            {
                SortingAlgorithms::swap(node2->iData, node2->ptrPrev->iData);
            }
        }
    }
}

void optimizedInsertionSort(Node **head)
{
    Node *sortedNode = nullptr;

    Node *currentNode = *head;
    while (currentNode != nullptr)
    {
        Node *nextNode = currentNode->ptrNext;

        if (sortedNode == nullptr || currentNode->iData < sortedNode->iData)
        {
            currentNode->ptrNext = sortedNode;
            if (sortedNode != nullptr)
            {
                sortedNode->ptrPrev = currentNode;
            }
            sortedNode = currentNode;
            sortedNode->ptrPrev = nullptr;
        }
        else
        {
            Node *temp = sortedNode;
            while (temp->ptrNext != nullptr && temp->ptrNext->iData < currentNode->iData)
            {
                temp = temp->ptrNext;
            }
            currentNode->ptrNext = temp->ptrNext;
            if (temp->ptrNext != nullptr)
            {
                temp->ptrNext->ptrPrev = currentNode;
            }
            temp->ptrNext = currentNode;
            currentNode->ptrPrev = temp;
        }

        currentNode = nextNode;
    }

    *head = sortedNode;
}

void printList(Node *head)
{
    Node *temp = head;
    while (temp)
    {
        std::cout << temp->iData << " ";
        temp = temp->ptrNext;
    }
    std::cout << std::endl;
}

void generateRandomList(Node **head, int size)
{
    srand(time(nullptr));
    for (int i = 0; i < size; ++i)
    {
        int randomNum = rand() % 100;
        insertNodeEnd(head, randomNum);
    }
}

void copyList(Node **head1, Node **head2)
{
    if (*head1 == nullptr)
    {
        return;
    }
    Node *tmp = *head1;

    while (tmp)
    {
        insertNodeEnd(head2, tmp->iData);
        tmp = tmp->ptrNext;
    }
}

void isSorted(Node **head)
{
    Node *tmp = *head;
    while (tmp->ptrNext)
    {
        if (tmp->iData > tmp->ptrNext->iData)
        {
            std::cout << "NOT SORTED" << std::endl;
            exit(1);
        }
        tmp = tmp->ptrNext;
    }
}
