#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <initializer_list>
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

typedef struct _node
{
    struct _node *ptrNext;
    struct _node *ptrPrev;
    int iData;
} Node;

Node *createNode(int iData);
void insertNodeEnd(Node **head, int iData);
void swapData(Node *node1, Node *node2);
void printList(Node *head);
void generateRandomList(Node **head, int size);
void copyList(Node **head1, Node **head2);
void isSorted(Node **head);
void unoptimizedSelectionSort(Node **head);
void optimizedSelectionSort(Node **head);
double mean(const long long data[], int size);
double variance(const long long data[], int size);
double standardDeviation(const long long data[], int size);
int mode(const long long data[], int size);

int main()
{
    int sizes[] = {1000, 5000, 8000, 10000, 15000};
    int num_tests = 5; 
    
    for (int size : sizes)
    {
        double mean_unoptimized = 0.0;
        double mean_optimized = 0.0;
        double stdev_unoptimized = 0.0;
        double stdev_optimized = 0.0;
        int mode_unoptimized = 0;
        int mode_optimized = 0;
        
        long long unoptimized_times[num_tests] = {0};
        long long optimized_times[num_tests] = {0};

        for (int rep = 0; rep < num_tests; ++rep)
        {
            Node *head1 = nullptr;
            Node *head2 = nullptr;

            generateRandomList(&head1, size);
            copyList(&head1, &head2);

            auto start_unoptimized = high_resolution_clock::now();
            unoptimizedSelectionSort(&head1);
            auto stop_unoptimized = high_resolution_clock::now();
            auto duration_unoptimized = duration_cast<nanoseconds>(stop_unoptimized - start_unoptimized);
            mean_unoptimized += duration_unoptimized.count();
            
            isSorted(&head1);

            auto start_optimized = high_resolution_clock::now();
            optimizedSelectionSort(&head2);
            auto stop_optimized = high_resolution_clock::now();
            auto duration_optimized = duration_cast<nanoseconds>(stop_optimized - start_optimized);
            mean_optimized += duration_optimized.count();
            
            isSorted(&head2);
            mode_unoptimized += duration_unoptimized.count();
            mode_optimized += duration_optimized.count();
            
            unoptimized_times[rep] = duration_unoptimized.count();
            optimized_times[rep] = duration_optimized.count();
        }
        
       // Calculating mean
        mean_unoptimized /= num_tests;
        mean_optimized /= num_tests;

        // Calculating mode
        mode_unoptimized /= num_tests;
        mode_optimized /= num_tests;
        
        // Calculating standard deviation
        stdev_unoptimized = standardDeviation(unoptimized_times, num_tests);
        stdev_optimized = standardDeviation(optimized_times, num_tests);

        // Printing the results
        cout << "LIST SIZE: " << size << endl;
        cout << "Unoptimized Selection Sort:" << endl;
        cout << "  Mean: " << mean_unoptimized << " nanoseconds" << endl;
        cout << "  Mode: " << mode_unoptimized << " nanoseconds" << endl;
        cout << "  Standard Deviation: " << stdev_unoptimized << " nanoseconds" << endl;
        cout << endl;
        cout << "Optimized Selection Sort:" << endl;
        cout << "  Mean: " << mean_optimized << " nanoseconds" << endl;
        cout << "  Mode: " << mode_optimized << " nanoseconds" << endl;
        cout << "  Standard Deviation: " << stdev_optimized << " nanoseconds" << endl;
        cout << endl;
        cout << "=============================================" << endl;
        cout << endl;
        
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

double mean(const long long data[], int size)
{
    double sum = 0.0;
    for (int i = 0; i < size; ++i)
    {
        sum += data[i];
    }
    return sum / size;
}

double variance(const long long data[], int size)
{
    double mean_value = mean(data, size);
    double sum_sq_diff = 0.0;
    for (int i = 0; i < size; ++i)
    {
        sum_sq_diff += (data[i] - mean_value) * (data[i] - mean_value);
    }
    return sum_sq_diff / size;
}

double standardDeviation(const long long data[], int size)
{
    return sqrt(variance(data, size));
}

int mode(const long long data[], int size)
{
    int freq_map[100] = {0};
    for (int i = 0; i < size; ++i)
    {
        freq_map[data[i]]++;
    }
    int max_freq = 0;
    int mode_value = 0;
    for (int i = 0; i < 100; ++i)
    {
        if (freq_map[i] > max_freq)
        {
            max_freq = freq_map[i];
            mode_value = i;
        }
    }
    return mode_value;
}