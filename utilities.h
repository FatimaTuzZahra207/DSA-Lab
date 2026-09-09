#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>
#include <unordered_map>

namespace utilities {
    int add(int a, int b);

    // Task 3: Find all indices of key in an array
    std::vector<int> find_all_indices(const int arr[], int size, int key);

    // Task 4: Find first occurrence of a substring (pattern) in text
    int find_substring(const std::string& text, const std::string& pattern);

    // Task 5: Generate Pascal's Triangle up to n rows
    std::vector<std::vector<int>> generate_pascals_triangle(int n);

    // Task 6: Find mode(s) in an array
    std::vector<int> find_modes(const int arr[], int size);

    // Task 7: Matrix Multiplication Algorithms
    using Matrix = std::vector<std::vector<int>>;
    Matrix multiply_naive(const Matrix& A, const Matrix& B);
    Matrix multiply_strassen(const Matrix& A, const Matrix& B);
}

#endif