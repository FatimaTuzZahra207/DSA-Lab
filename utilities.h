#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>

namespace utilities {
    int add(int a, int b);

    //Find all indices of key in an array
    std::vector<int> find_all_indices(const int arr[], int size, int key);

   //Find first occurrence of a substring (pattern) in text
    int find_substring(const std::string& text, const std::string& pattern);

    // Task 5: Generate Pascal's Triangle up to n rows
    std::vector<std::vector<int>> generate_pascals_triangle(int n);
}

#endif