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
            return 0;
        }
        size_t pos = text.find(pattern);
        if (pos != std::string::npos) {
            return static_cast<int>(pos);
        }
        return -1;
    }
    std::vector<std::vector<int>> generate_pascals_triangle(int n) {
        std::vector<std::vector<int>> triangle;
        if (n <= 0) return triangle;

        for (int i = 0; i < n; ++i) {
            std::vector<int> row(i + 1, 1);
            for (int j = 1; j < i; ++j) {
                row[j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
            }
            triangle.push_back(row);
        }
        return triangle;
    }
}