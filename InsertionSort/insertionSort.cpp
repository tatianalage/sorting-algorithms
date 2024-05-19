#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <initializer_list>
#include <fstream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::srand;
using std::string;
using std::time;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::nanoseconds;
using std::ofstream;

typedef struct _node
{
    struct _node *ptrNext;
    struct _node *ptrPrev;
    int iData;
} Node;

Node *createNode(int iData);
void insertNodeEnd(Node **head, int iData);
void swapData(Node *node1, Node *node2);
void unoptimizedInsertionSort(Node **head);
void optimizedInsertionSort(Node **head);
void printList(Node *head);
void generateRandomList(Node **head, int size);
void copyList(Node **head1, Node **head2);
void isSorted(Node **head);

int main()
{
    ofstream outputFile("sorting_times.txt");
    if (!outputFile.is_open())
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    const int listSize = 10000;
    const int numLists = 100;

    long long unoptimizedDurations[numLists];
    long long optimizedDurations[numLists];

    for (int i = 0; i < numLists; i++)
    {
        Node *head1 = nullptr;
        Node *head2 = nullptr;

        generateRandomList(&head1, listSize);
        copyList(&head1, &head2);

        auto start_unoptimized = high_resolution_clock::now();
        unoptimizedInsertionSort(&head1);
        auto stop_unoptimized = high_resolution_clock::now();

        isSorted(&head1);

        auto start_optimized = high_resolution_clock::now();
        optimizedInsertionSort(&head2);
        auto stop_optimized = high_resolution_clock::now();

        isSorted(&head2);

        auto duration_unoptimized = duration_cast<nanoseconds>(stop_unoptimized - start_unoptimized).count();
        auto duration_optimized = duration_cast<nanoseconds>(stop_optimized - start_optimized).count();

        unoptimizedDurations[i] = duration_unoptimized;
        optimizedDurations[i] = duration_optimized;

        outputFile << "List #" << i + 1 << ": Unoptimized - " << duration_unoptimized << " ns, Optimized - " << duration_optimized << " ns" << endl;
    }

    return 0;
}

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

void unoptimizedInsertionSort(Node **head)
{
    for (Node *node1 = *head; node1 != nullptr; node1 = node1->ptrNext)
    {
        for (Node *node2 = node1; node2 != nullptr; node2 = node2->ptrPrev)
        {
            if (node2->ptrPrev != nullptr && node2->iData < node2->ptrPrev->iData)
            {
                swapData(node2, node2->ptrPrev);
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
        cout << temp->iData << " ";
        temp = temp->ptrNext;
    }
    cout << endl;
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
            cout << "NOT SORTED" << endl;
            exit(1);
        }
        tmp = tmp->ptrNext;
    }
}
