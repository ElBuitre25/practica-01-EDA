#include <iostream>
#include <vector>
#include <chrono>
#include "dataset/create_random_dataset.h"
#include "heap_sort.h"
#include "red_black_tree.h"

int main()
{   
    std::vector<std::string> dataset;
    dataset=create_random_dataset("data/words_alpha.txt");

    // QuickSort
    auto inicio_quick = std::chrono::high_resolution_clock::now();
    // quickSort(dataset);
    auto fin_quick = std::chrono::high_resolution_clock::now();
    auto tiempo_quick = std::chrono::duration_cast<std::chrono::milliseconds>(fin_quick - inicio_quick).count();

    // HeapSort
    std::vector<std::string> heap_dataset = dataset;
    auto inicio_heap = std::chrono::high_resolution_clock::now();
    // heapSort(dataset);
    auto fin_heap = std::chrono::high_resolution_clock::now();
    auto tiempo_heap = std::chrono::duration_cast<std::chrono::milliseconds>(fin_heap - inicio_heap).count();

   // Red-Black Tree
auto inicio_rb = std::chrono::high_resolution_clock::now();

RedBlackTree rb_tree;
for (const auto& word : dataset) {
    rb_tree.insert(word);
}

std::vector<std::string> rb_dataset = rb_tree.inorder();

auto fin_rb = std::chrono::high_resolution_clock::now();
auto tiempo_rb = std::chrono::duration_cast<std::chrono::milliseconds>(fin_rb - inicio_rb).count();
    // Resultados
    std::cout << "QuickSort : " << tiempo_quick << " ms" << std::endl;
    std::cout << "HeapSort  : " << tiempo_heap  << " ms" << std::endl;
    std::cout << "HeapSort  : " << estimate_memory_mb(heap_dataset) << " MB estimados" << std::endl;
    std::cout << "RedBlack  : " << tiempo_rb << " ms" << std::endl;
    std::cout << "RB memory : " << rb_tree.estimate_memory_mb() << " MB estimados" << std::endl;

    return 0;
}
