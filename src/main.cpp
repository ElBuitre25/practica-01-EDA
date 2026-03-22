#include <iostream>
#include <vector>
#include <chrono>
#include "dataset/create_random_dataset.h"
#include "heap_sort.h"

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

    // AVL
    auto inicio_avl = std::chrono::high_resolution_clock::now();
    // avlSort(dataset);
    auto fin_avl = std::chrono::high_resolution_clock::now();
    auto tiempo_avl = std::chrono::duration_cast<std::chrono::milliseconds>(fin_avl - inicio_avl).count();

    // Resultados
    std::cout << "QuickSort : " << tiempo_quick << " ms" << std::endl;
    std::cout << "HeapSort  : " << tiempo_heap  << " ms" << std::endl;
    std::cout << "HeapSort  : " << estimate_memory_mb(heap_dataset) << " MB estimados" << std::endl;
    std::cout << "AVL       : " << tiempo_avl   << " ms" << std::endl;


    return 0;
}
