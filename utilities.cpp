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

    int find_substring(const std::string& text, const std::string& pattern) {
        if (pattern.empty()) {
            return 0; // Empty pattern matches at index 0
        }

        size_t pos = text.find(pattern);
        if (pos != std::string::npos) {
            return static_cast<int>(pos);
        }
        return -1;
    }
}