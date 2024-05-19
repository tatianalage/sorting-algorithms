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

void unoptimizedBubbleSort(Node **head)
{
    bool bUnordered = true;
    while (bUnordered)
    {
        bUnordered = false;
        Node *currNode = *head;
        while (currNode->ptrNext != nullptr)
        {
            if (currNode->iData > currNode->ptrNext->iData)
            {
                SortingAlgorithms::swap(currNode->iData, currNode->ptrNext->iData);
                bUnordered = true;
            }
            currNode = currNode->ptrNext;
        }
    }
}

void optimizedBubbleSort(Node **head)
{
    Node *lastNode = *head;
    while (lastNode->ptrNext)
    {
        lastNode = lastNode->ptrNext;
    }
    bool bUnordered = true;
    while (bUnordered)
    {
        bUnordered = false;
        Node *currNode = *head;
        while (currNode != lastNode && currNode != nullptr)
        {
            if (currNode->iData > currNode->ptrNext->iData)
            {
                SortingAlgorithms::swap(currNode->iData, currNode->ptrNext->iData);
                bUnordered = true;
            }
            currNode = currNode->ptrNext;
        }
        lastNode = lastNode->ptrPrev;
    }
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
