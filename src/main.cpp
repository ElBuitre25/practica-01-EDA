#include <iostream>
#include <vector>
#include <chrono>
#include "dataset/create_random_dataset.h"
#include "quick_sort.h"
#include "heap_sort.h"
#include "red_black_tree.h"

int main() {
    std::vector<std::string> dataset = create_random_dataset("data/words_alpha.txt");
    if (dataset.empty()) {
        std::cerr << "No se pudo cargar el dataset." << std::endl;
        return 1;
    }

    // --- QuickSort ---
    std::vector<std::string> qs_data = dataset;
    auto t0 = std::chrono::high_resolution_clock::now();
    quick_sort(qs_data, 0, (int)qs_data.size() - 1);
    auto t1 = std::chrono::high_resolution_clock::now();
    long ms_quick = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    double mem_quick = estimate_memory_mb_quick(qs_data);

    // --- HeapSort ---
    std::vector<std::string> hs_data = dataset;
    auto t2 = std::chrono::high_resolution_clock::now();
    heap_sort(hs_data);
    auto t3 = std::chrono::high_resolution_clock::now();
    long ms_heap = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count();
    double mem_heap = estimate_memory_mb(hs_data);

    // --- Red-Black Tree (inorder = ordenado) ---
    RedBlackTree rbt;
    auto t4 = std::chrono::high_resolution_clock::now();
    for (const auto& word : dataset)
        rbt.insert(word);
    std::vector<std::string> rbt_result = rbt.inorder();
    auto t5 = std::chrono::high_resolution_clock::now();
    long ms_rbt = std::chrono::duration_cast<std::chrono::milliseconds>(t5 - t4).count();
    double mem_rbt = rbt.estimate_memory_mb();

    std::cout << "\n===== Resultados de ordenamiento (100,000 palabras) =====\n\n";
    std::cout << "Algoritmo       Tiempo (ms)   Memoria estimada\n";
    std::cout << "------------------------------------------------\n";
    std::cout << "QuickSort       " << ms_quick << " ms\t\t" << mem_quick << " MB\n";
    std::cout << "HeapSort        " << ms_heap  << " ms\t\t" << mem_heap  << " MB\n";
    std::cout << "Red-Black Tree  " << ms_rbt   << " ms\t\t" << mem_rbt   << " MB\n";

    std::cout << "\n===== Analisis comparativo =====\n";
    std::cout << "QuickSort   O(n log n) promedio, O(n^2) peor caso. Trabaja in-place sobre el vector.\n";
    std::cout << "HeapSort    O(n log n) garantizado. Usa el mismo vector como heap, buena localidad.\n";
    std::cout << "RBT inorder O(n log n) insercion + O(n) recorrido. Mayor uso de memoria por punteros.\n";

    std::cout << "\nPrimeras 10 palabras ordenadas (QuickSort): ";
    for (int i = 0; i < 10; i++) std::cout << qs_data[i] << " ";
    std::cout << "\n";

    return 0;
}
