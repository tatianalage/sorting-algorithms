// main.cpp
#include "sorting.h"
#include "sorting.cpp"
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

int main()
{
    std::ofstream outputFile("sorting_times.txt");
    if (!outputFile.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
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

        auto start_unoptimized = std::chrono::high_resolution_clock::now();
        unoptimizedInsertionSort(&head1);
        auto stop_unoptimized = std::chrono::high_resolution_clock::now();

        isSorted(&head1);

        auto start_optimized = std::chrono::high_resolution_clock::now();
        optimizedInsertionSort(&head2);
        auto stop_optimized = std::chrono::high_resolution_clock::now();

        isSorted(&head2);

        auto duration_unoptimized = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_unoptimized - start_unoptimized).count();
        auto duration_optimized = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_optimized - start_optimized).count();

        unoptimizedDurations[i] = duration_unoptimized;
        optimizedDurations[i] = duration_optimized;

        outputFile << "List #" << i + 1 << ": Unoptimized - " << duration_unoptimized << " ns, Optimized - " << duration_optimized << " ns" << std::endl;
    }

    return 0;
}
