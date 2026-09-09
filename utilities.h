#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>

namespace utilities {
    int add(int a, int b);

    // Task 3: Find all indices of key in an array
    std::vector<int> find_all_indices(const int arr[], int size, int key);

    // Task 4: Find first occurrence of a substring (pattern) in text
    int find_substring(const std::string& text, const std::string& pattern);
}

#endif