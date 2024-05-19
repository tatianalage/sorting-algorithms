#include "sorting.h"
#include "sorting.cpp"

int main() {
    std::ofstream outputFile("sorting_times.txt");
    if (!outputFile.is_open()) {
        std::cout << "Error opening file!" << std::endl;
        return 1;
    }

    const int listSize = 10000;
    const int numLists = 100;

    long long unoptimizedDurations[numLists];
    long long optimizedDurations[numLists];

    for (int i = 0; i < numLists; i++) {
        Node<int>* head1 = nullptr;
        Node<int>* head2 = nullptr;

        generateRandomList(&head1, listSize);
        copyList(&head1, &head2);

        auto start_unoptimized = std::chrono::high_resolution_clock::now();
        unoptimizedBubbleSort(&head1);
        auto stop_unoptimized = std::chrono::high_resolution_clock::now();

        isSorted(&head1);

        auto start_optimized = std::chrono::high_resolution_clock::now();
        optimizedBubbleSort(&head2);
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
