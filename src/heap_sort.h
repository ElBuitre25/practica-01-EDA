#pragma once
#include <vector>
#include <string>

void heapify(std::vector<std::string>& arr, int n, int i); 

void build_max_heap(std::vector<std::string>& arr);

void heap_sort(std::vector<std::string>& arr);
double estimate_memory_mb(const std::vector<std::string>& arr);