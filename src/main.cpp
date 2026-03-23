#include <iostream>
#include <vector>
#include <chrono>
#include "dataset/create_random_dataset.h"
#include "quick_sort.h"
#include "heap_sort.h"
#include "red_black_tree.h"

int main() {
    std::vector<std::string> dataset;
    dataset = create_random_dataset("data/words_alpha.txt");

    if (dataset.empty()) {
        std::cerr << "Error cargando el dataset" << std::endl;
        return 1;
    }

    // cada algoritmo necesita su propia copia porque ordenan in-place
    std::vector<std::string> qs_data = dataset;
    std::vector<std::string> hs_data = dataset;

    // ---- QuickSort ----
    auto inicio_qs = std::chrono::high_resolution_clock::now();
    quick_sort(qs_data, 0, (int)qs_data.size() - 1);
    auto fin_qs = std::chrono::high_resolution_clock::now();
    auto tiempo_qs = std::chrono::duration_cast<std::chrono::milliseconds>(fin_qs - inicio_qs).count();

    // ---- HeapSort ----
    auto inicio_hs = std::chrono::high_resolution_clock::now();
    heap_sort(hs_data);
    auto fin_hs = std::chrono::high_resolution_clock::now();
    auto tiempo_hs = std::chrono::duration_cast<std::chrono::milliseconds>(fin_hs - inicio_hs).count();

    // ---- Red-Black Tree ----
    // se inserta cada palabra y el inorder nos da el resultado ordenado
    RedBlackTree rbt;
    auto inicio_rbt = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < (int)dataset.size(); i++)
        rbt.insert(dataset[i]);
    std::vector<std::string> rbt_result = rbt.inorder();
    auto fin_rbt = std::chrono::high_resolution_clock::now();
    auto tiempo_rbt = std::chrono::duration_cast<std::chrono::milliseconds>(fin_rbt - inicio_rbt).count();

    std::cout << "\n--- Tiempos de ejecucion ---" << std::endl;
    std::cout << "QuickSort:      " << tiempo_qs  << " ms" << std::endl;
    std::cout << "HeapSort:       " << tiempo_hs  << " ms" << std::endl;
    std::cout << "Red-Black Tree: " << tiempo_rbt << " ms" << std::endl;

    std::cout << "\n--- Memoria estimada ---" << std::endl;
    std::cout << "QuickSort:      " << estimate_memory_mb_quick(qs_data) << " MB" << std::endl;
    std::cout << "HeapSort:       " << estimate_memory_mb(hs_data)       << " MB" << std::endl;
    std::cout << "Red-Black Tree: " << rbt.estimate_memory_mb()          << " MB" << std::endl;

    // imprimir las primeras palabras de cada uno para verificar que esten ordenadas
    std::cout << "\n--- Verificacion (primeras 10 palabras) ---" << std::endl;
    std::cout << "QuickSort: ";
    for (int i = 0; i < 10; i++) std::cout << qs_data[i] << " ";
    std::cout << std::endl;

    std::cout << "HeapSort:  ";
    for (int i = 0; i < 10; i++) std::cout << hs_data[i] << " ";
    std::cout << std::endl;

    std::cout << "RBT:       ";
    for (int i = 0; i < 10; i++) std::cout << rbt_result[i] << " ";
    std::cout << std::endl;

    std::cout << "\n--- Analisis ---" << std::endl;
    std::cout << "Los tres algoritmos tienen complejidad O(n log n) en promedio," << std::endl;
    std::cout << "pero en la practica QuickSort suele ser el mas rapido porque trabaja" << std::endl;
    std::cout << "directamente sobre el vector y aprovecha mejor el cache del procesador." << std::endl;
    std::cout << "HeapSort garantiza O(n log n) siempre, pero los accesos no son secuenciales" << std::endl;
    std::cout << "(va a indices 2i+1 y 2i+2), lo que genera mas cache misses." << std::endl;
    std::cout << "El RBT usa mas memoria porque cada nodo tiene 3 punteros (padre, izq, der)" << std::endl;
    std::cout << "mas el color, pero la ventaja es que el arbol queda ordenado en todo momento." << std::endl;

    return 0;
}
