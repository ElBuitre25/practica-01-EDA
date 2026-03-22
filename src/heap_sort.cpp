#include "heap_sort.h"
#include <cstddef>

void heapify(std::vector<std::string>& arr, int n, int i) {
    int largest_index = i;
    int left_child = 2 * i + 1;
    int right_child = 2 * i + 2;

    if (left_child < n && arr[left_child] > arr[largest_index])
        largest_index = left_child; 

    if (right_child < n && arr[right_child] > arr[largest_index])
        largest_index = right_child;

    if (largest_index != i) {
        std::swap(arr[i], arr[largest_index]);
        heapify(arr, n, largest_index); 
    }
}

void build_max_heap(std::vector<std::string>& arr) {
    int total_size = static_cast<int>(arr.size());
    for (int current_index = total_size / 2 - 1; current_index >= 0; current_index--)
        heapify(arr, total_size, current_index);
}

void heap_sort(std::vector<std::string>& arr) {
    int arr_size = static_cast<int>(arr.size());

    build_max_heap(arr);

    for (int sorted_boundary = arr_size - 1; sorted_boundary > 0; sorted_boundary--) {
        std::swap(arr[0], arr[sorted_boundary]);
        heapify(arr, sorted_boundary, 0);
    }
}

double estimate_memory_mb(const std::vector<std::string>& arr) {
    return 0.0; 
}