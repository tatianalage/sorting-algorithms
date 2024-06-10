#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include "binary_tree.h"
#include "queue.h"
#include "binary_tree.cpp"
#include "queue.cpp"

BinaryTree::Node<int>* createCompleteBinaryTree(int n) {
    BinaryTree::Node<int>* root = nullptr;
    if (n <= 0)
        return root;

    root = BinaryTree::createNode(1);
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(1, n);

    for (int i = 1; i <= n; i++) {
        int random_number = dist(rng)*10;
        BinaryTree::insertNode(root, random_number);
    }

    return root;
}

Queues::Queue<int>* createLinkedList(int n) {
    Queues::Queue<int>* queue = Queues::createQueue<int>();
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(1, n);
    for (int i = 0; i < n; ++i) {
        int random_number = dist(rng);
        Queues::enqueue(queue, random_number);
    }
    return queue;
}

bool searchInLinkedList(Queues::Queue<int>* queue, int target) {
    Queues::Queue<int>* temp = Queues::createQueue<int>();
    bool found = false;

    while (!Queues::isQueueEmpty(queue)) {
        int element = Queues::dequeue(queue);
        Queues::enqueue(temp, element);
        if (element == target) {
            found = true;
            break;
        }
    }

    while (!Queues::isQueueEmpty(temp)) {
        int element = Queues::dequeue(temp);
        Queues::enqueue(queue, element);
    }

    Queues::deleteQueue(temp);
    return found;
}

bool searchInBinaryTreeBFS(BinaryTree::Node<int>* root, int target) {
    if (root == nullptr) {
        std::cout << "Tree is empty" << std::endl;
        return false;
    }

    Queues::Queue<BinaryTree::Node<int>*>* queue = Queues::createQueue<BinaryTree::Node<int>*>();
    Queues::enqueue(queue, root);

    while (!Queues::isQueueEmpty(queue)) {
        BinaryTree::Node<int>* current = Queues::dequeue(queue);
        //std::cout << "Visiting node with value: " << current->iPayload << std::endl;

        if (current->iPayload == target) {
            Queues::deleteQueue(queue);
            return true;
        }

        if (current->ptrLeft != nullptr) {
            Queues::enqueue(queue, current->ptrLeft);
        }

        if (current->ptrRight != nullptr) {
            Queues::enqueue(queue, current->ptrRight);
        }
    }

    Queues::deleteQueue(queue);
    return false;
}

bool searchInBinaryTreeDFS(BinaryTree::Node<int>* root, int target) {
    if (root == nullptr)
        return false;

    if (root->iPayload == target) {
        return true;
    }

    bool foundLeft = searchInBinaryTreeDFS(root->ptrLeft, target);
    if (foundLeft)
        return true;

    bool foundRight = searchInBinaryTreeDFS(root->ptrRight, target);
    if (foundRight)
        return true;

    return false;
}

int main() {
    std::ofstream outputFile("tempos.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing\n";
        return 1;
    }

    int testCount = 0;

    for (int n = 100; n <= 100000; n += 1000) {
        auto start_tree_creation = std::chrono::high_resolution_clock::now();
        BinaryTree::Node<int>* tree_root = createCompleteBinaryTree(n);
        auto end_tree_creation = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_tree_creation = end_tree_creation - start_tree_creation;
        double tree_creation_seconds = elapsed_tree_creation.count();

        auto start_list_creation = std::chrono::high_resolution_clock::now();
        Queues::Queue<int>* linked_list = createLinkedList(n);
        auto end_list_creation = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_list_creation = end_list_creation - start_list_creation;
        double list_creation_seconds = elapsed_list_creation.count();

        int target = n / 2;
        auto start_tree_search_bfs = std::chrono::high_resolution_clock::now();
        bool found_bfs = searchInBinaryTreeBFS(tree_root, target);
        auto end_tree_search_bfs = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_tree_search_bfs = end_tree_search_bfs - start_tree_search_bfs;
        double tree_search_bfs_seconds = elapsed_tree_search_bfs.count();

        auto start_tree_search_dfs = std::chrono::high_resolution_clock::now();
        bool found_dfs = searchInBinaryTreeDFS(tree_root, target);
        auto end_tree_search_dfs = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_tree_search_dfs = end_tree_search_dfs - start_tree_search_dfs;
        double tree_search_dfs_seconds = elapsed_tree_search_dfs.count();

        auto start_list_search = std::chrono::high_resolution_clock::now();
        bool found = searchInLinkedList(linked_list, target);
        auto end_list_search = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_list_search = end_list_search - start_list_search;
        double list_search_seconds = elapsed_list_search.count();

        outputFile << "Test #" << ++testCount << " (Nodes: " << n << "):  "
                   << "Tree Creation: " << tree_creation_seconds << " seconds  "
                   << "List Creation: " << list_creation_seconds << " seconds  "
                   << "Tree Search (BFS): " << tree_search_bfs_seconds << " seconds  "
                   << "Tree Search (DFS): " << tree_search_dfs_seconds << " seconds  "
                   << "List Search: " << list_search_seconds << " seconds\n";

        Queues::deleteQueue(linked_list);
    }
    outputFile.close();
    return 0;
}
