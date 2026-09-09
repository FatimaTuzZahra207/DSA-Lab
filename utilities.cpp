#include "utilities.h"

namespace utilities {
    int add(int a, int b) {
        return a + b;
    }

    std::vector<int> find_all_indices(const int arr[], int size, int key) {
        std::vector<int> indices;
        for (int i = 0; i < size; ++i) {
            if (arr[i] == key) {
                indices.push_back(i);
            }
        }
        return indices;
    }
}