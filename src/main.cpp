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
    std::cout << "Dataset cargado: " << dataset.size() << " palabras\n";

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

    // --- Red-Black Tree: insercion + inorder = ordenado ---
    RedBlackTree rbt;
    auto t4 = std::chrono::high_resolution_clock::now();
    for (const auto& word : dataset)
        rbt.insert(word);
    std::vector<std::string> rbt_result = rbt.inorder();
    auto t5 = std::chrono::high_resolution_clock::now();
    long ms_rbt = std::chrono::duration_cast<std::chrono::milliseconds>(t5 - t4).count();
    double mem_rbt = rbt.estimate_memory_mb();

    std::cout << "\n===== Resultados de ordenamiento (100,000 palabras) =====\n\n";
    std::cout << "Algoritmo        Tiempo (ms)    Memoria estimada\n";
    std::cout << "-------------------------------------------------\n";
    std::cout << "QuickSort        " << ms_quick << " ms\t\t" << mem_quick << " MB\n";
    std::cout << "HeapSort         " << ms_heap  << " ms\t\t" << mem_heap  << " MB\n";
    std::cout << "Red-Black Tree   " << ms_rbt   << " ms\t\t" << mem_rbt   << " MB\n";

    // Primeras palabras de cada algoritmo para verificar que todos ordenan correctamente
    std::cout << "\n-- Verificacion (primeras 10 palabras) --\n";
    std::cout << "QuickSort : ";
    for (int i = 0; i < 10; i++) std::cout << qs_data[i] << " ";
    std::cout << "\n";
    std::cout << "HeapSort  : ";
    for (int i = 0; i < 10; i++) std::cout << hs_data[i] << " ";
    std::cout << "\n";
    std::cout << "RBT       : ";
    for (int i = 0; i < 10; i++) std::cout << rbt_result[i] << " ";
    std::cout << "\n";

    // Determinar el mas rapido
    long mejor_tiempo = ms_quick;
    std::string ganador = "QuickSort";
    if (ms_heap < mejor_tiempo) { mejor_tiempo = ms_heap; ganador = "HeapSort"; }
    if (ms_rbt  < mejor_tiempo) { mejor_tiempo = ms_rbt;  ganador = "Red-Black Tree"; }

    std::cout << "\n===== Analisis comparativo =====\n";
    std::cout << "\nComplejidad algoritmica (Big O):\n";
    std::cout << "  QuickSort      O(n log n) promedio | O(n^2) peor caso\n";
    std::cout << "  HeapSort       O(n log n) garantizado en todos los casos\n";
    std::cout << "  Red-Black Tree O(n log n) insercion + O(n) recorrido inorder\n";

    std::cout << "\nAlgoritmo mas rapido en esta ejecucion: " << ganador
              << " (" << mejor_tiempo << " ms)\n";

    std::cout << "\nPor que la complejidad teorica no siempre refleja el tiempo real:\n";
    std::cout << "  - QuickSort aprovecha localidad de cache al trabajar in-place en el vector.\n";
    std::cout << "    Los accesos a memoria son secuenciales y el hardware los predice bien.\n";
    std::cout << "  - HeapSort tambien es O(n log n) pero accede al vector de forma no lineal\n";
    std::cout << "    (indices 2i+1, 2i+2), lo que genera mas cache misses.\n";
    std::cout << "  - Red-Black Tree tiene overhead de punteros y allocations dinamicas por nodo.\n";
    std::cout << "    Cada insercion aloca memoria en el heap, lo que es costoso.\n";

    std::cout << "\nVentajas y desventajas de cada estructura:\n";
    std::cout << "  QuickSort: rapido en la practica, in-place (poca memoria extra),\n";
    std::cout << "             pero no garantiza O(n log n) si el pivote es malo.\n";
    std::cout << "  HeapSort:  O(n log n) garantizado siempre, util cuando se necesita\n";
    std::cout << "             certeza, pero mas lento que QuickSort en promedio.\n";
    std::cout << "  RBT:       permite busqueda/insercion/borrado O(log n) en cualquier\n";
    std::cout << "             momento, no solo al final. Costo: ~" << mem_rbt << " MB vs "
              << mem_quick << " MB del vector.\n";

    return 0;
}
