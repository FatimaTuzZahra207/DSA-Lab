#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>

namespace utilities {
    int add(int a, int b);

    // Task 3: Find all indices of key in an array
    std::vector<int> find_all_indices(const int arr[], int size, int key);
}

#endif