#include <iostream>
#include <vector>
#include <string>
#include "utilities.h"

void test_find_all_indices() {
    int arr1[] = {10, 20, 10, 30, 10};
    std::vector<int> res1 = utilities::find_all_indices(arr1, 5, 10);
    std::cout << "Multiple occurrences test: " 
              << (res1 == std::vector<int>{0, 2, 4} ? "PASS" : "FAIL") << "\n";

    int arr2[] = {1, 2, 3, 4};
    std::vector<int> res2 = utilities::find_all_indices(arr2, 4, 99);
    std::cout << "Key not present test: " 
              << (res2.empty() ? "PASS" : "FAIL") << "\n";

    int arr3[] = {};
    std::vector<int> res3 = utilities::find_all_indices(arr3, 0, 5);
    std::cout << "Empty array test: " 
              << (res3.empty() ? "PASS" : "FAIL") << "\n";
}

void test_find_substring() {
    // Test 1: Pattern at the beginning
    std::cout << "Pattern at beginning test: "
              << (utilities::find_substring("hello world", "hello") == 0 ? "PASS" : "FAIL") << "\n";

    // Test 2: Pattern at the end
    std::cout << "Pattern at end test: "
              << (utilities::find_substring("hello world", "world") == 6 ? "PASS" : "FAIL") << "\n";

    // Test 3: Pattern not present
    std::cout << "Pattern not present test: "
              << (utilities::find_substring("hello world", "c++") == -1 ? "PASS" : "FAIL") << "\n";

    // Test 4: Empty pattern
    std::cout << "Empty pattern test: "
              << (utilities::find_substring("hello world", "") == 0 ? "PASS" : "FAIL") << "\n";
}

int main() {
    std::cout << "add(2,3) == 5: " 
              << (utilities::add(2, 3) == 5 ? "PASS" : "FAIL") << "\n";
              
    test_find_all_indices();
    test_find_substring();
    return 0;
}