#include <iostream>
#include <fstream>
#include "sorting.h"

using namespace std;
using namespace Sorting;

int main() {
    ofstream outputFile("sorting_times.txt");
    if (!outputFile.is_open()) {
        cout << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    const int listSize = 10000;
    const int numLists = 100;

    for (int i = 0; i < numLists; i++) {
        Node<int> *head1 = nullptr;
        Node<int> *head2 = nullptr;
        generateRandomList(&head1, listSize);
        copyList(&head1, &head2);

        testSortingAlgorithm("Bubble Sort Não Otimizado", unoptimizedBubbleSort, head1, outputFile);

        testSortingAlgorithm("Bubble Sort Otimizado", optimizedBubbleSort, head2, outputFile);
    }

    outputFile.close();

    return 0;
}
