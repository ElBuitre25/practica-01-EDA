#include "quick_sort.h"

// Escoge el pivote como la mediana entre primero, medio y ultimo
// para evitar el peor caso con datos ya ordenados
static int mediana_tres(std::vector<std::string>& arr, int low, int high) {
    int mid = low + (high - low) / 2;

    if (arr[low] > arr[mid]) std::swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) std::swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) std::swap(arr[mid], arr[high]);

    // deja el pivote en high-1
    std::swap(arr[mid], arr[high]);
    return high;
}

static int particionar(std::vector<std::string>& arr, int low, int high) {
    int pivot_idx = mediana_tres(arr, low, high);
    std::string pivot = arr[pivot_idx];

    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
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
    for (const auto& s : arr)
        total += s.capacity();
    return static_cast<double>(total) / (1024.0 * 1024.0);
}
