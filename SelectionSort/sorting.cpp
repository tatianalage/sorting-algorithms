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

void swapData(Node *node1, Node *node2)
{
    int iTmp = node1->iData;
    node1->iData = node2->iData;
    node2->iData = iTmp;
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

void unoptimizedSelectionSort(Node **head)
{
    for (Node *node1 = (*head); node1 != nullptr; node1 = node1->ptrNext)
    {

        for (Node *node2 = node1->ptrNext; node2 != nullptr; node2 = node2->ptrNext)
        {
            if (node2->iData <= node1->iData)
            {
                swapData(node1, node2);
            }
        }
    }
}

void optimizedSelectionSort(Node **head)
{
    for (Node *node1 = (*head); node1 != nullptr; node1 = node1->ptrNext)
    {

        Node *minValNode = node1;
        for (Node *node2 = node1->ptrNext; node2 != nullptr; node2 = node2->ptrNext)
        {
            if (node2->iData <= minValNode->iData)
            {
                minValNode = node2;
            }
        }
        swapData(node1, minValNode);
    }
}
