#include "binary_tree.h"
#include "queue.h"
#include "queue.cpp"
#include "binary_tree.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::ofstream;

using namespace BinaryTree;
using namespace Queues;

Node<int>* populateTree(int numNodes) {
    Node<int>* root = NULL;
    for (int i = 0; i < numNodes; i++) {
        int value = rand() % 1000;
        root = insertNode(root, value);
    }
    return root;
}

double measureDFS(Node<int>* root, int value) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    Node<int>* result = BinaryTree::searchNodeDFS(root, value);
    std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
    if (result != NULL) {
        // printf("DFS: Node with value %d found.\n", value);
    } else {
        printf("DFS: Node with value %d not found.\n", value);
    }
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

double measureBFS(Node<int>* root, int value) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    Node<int>* result = BinaryTree::searchNodeBFS(root, value);
    std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
    if (result != NULL) {
        // printf("BFS: Node with value %d found.\n", value);
    } else {
        printf("BFS: Node with value %d not found.\n", value);
    }
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

double measureListCreation(int numElements) {
    Queues::Queue<int*>* myQueue = Queues::createQueue<int*>();
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numElements; i++) {
        int* value = (int*)malloc(sizeof(int));
        *value = rand() % 1000;
        Queues::enqueue(myQueue, value);
    }
    std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
    Queues::deleteQueue(myQueue);
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

double measureTreeCreation(int numNodes) {
    Node<int>* root = NULL;
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numNodes; i++) {
        int value = rand() % 1000;
        root = BinaryTree::insertNode(root, value);
    }
    std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

int main() {
    srand(time(NULL));
    ofstream outputFile("performance_times.txt");
    if (!outputFile.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    const int numNodes[] = {10000, 30000, 50000}; 
    const int numElements[] = {10000, 30000, 50000}; 
    int totalTests = 1000; 
    int totalCombinations = sizeof(numNodes) / sizeof(numNodes[0]) * sizeof(numElements) / sizeof(numElements[0]);
    int testsPerCombination = totalTests / totalCombinations;
    int remainingTests = totalTests % totalCombinations;
    int testCount = 0;

    for (int n = 0; n < sizeof(numNodes) / sizeof(numNodes[0]); ++n) {
        for (int e = 0; e < sizeof(numElements) / sizeof(numElements[0]); ++e) {
            long long dfsDurations[testsPerCombination];
            long long bfsDurations[testsPerCombination];
            long long listCreationDurations[testsPerCombination];
            long long treeCreationDurations[testsPerCombination];

            int searchValue = rand() % 1000; // Define search value for each combination

            for (int i = 0; i < testsPerCombination; i++) {
                treeCreationDurations[i] = measureTreeCreation(numNodes[n]);
            }

            Node<int>* root = populateTree(numNodes[n]);
            for (int i = 0; i < testsPerCombination; i++) {
                dfsDurations[i] = measureDFS(root, searchValue);
                bfsDurations[i] = measureBFS(root, searchValue);
            }

            for (int i = 0; i < testsPerCombination; i++) {
                listCreationDurations[i] = measureListCreation(numElements[e]);
            }

            for (int i = 0; i < testsPerCombination; i++) {
                outputFile << "Test #" << ++testCount << " (Nodes: " << numNodes[n] << ", Elements: " << numElements[e] << "): Tree Creation - " << treeCreationDurations[i] << " ns, "
                           << "DFS - " << dfsDurations[i] << " ns, "
                           << "BFS - " << bfsDurations[i] << " ns, "
                           << "List Creation - " << listCreationDurations[i] << " ns" << endl;
            }
        }
    }
    outputFile.close();
    return 0;
}