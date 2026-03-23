#include "quick_sort.h"

// elegimos el pivote como la mediana entre el primero, el del medio y el ultimo
// esto evita el peor caso cuando el arreglo ya esta casi ordenado
int mediana_tres(std::vector<std::string>& arr, int low, int high) {
    int mid = low + (high - low) / 2;

    if (arr[low] > arr[mid])  std::swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) std::swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) std::swap(arr[mid], arr[high]);

    std::swap(arr[mid], arr[high]);
    return high;
}

int particionar(std::vector<std::string>& arr, int low, int high) {
    mediana_tres(arr, low, high);
    std::string pivote = arr[high];

    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivote) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quick_sort(std::vector<std::string>& arr, int low, int high) {
    if (low >= high) return;

    int pi = particionar(arr, low, high);
    quick_sort(arr, low, pi - 1);
    quick_sort(arr, pi + 1, high);
}

double estimate_memory_mb_quick(const std::vector<std::string>& arr) {
    size_t total = sizeof(std::vector<std::string>) + arr.capacity() * sizeof(std::string);
    for (int i = 0; i < (int)arr.size(); i++)
        total += arr[i].capacity();
    return static_cast<double>(total) / (1024.0 * 1024.0);
}
