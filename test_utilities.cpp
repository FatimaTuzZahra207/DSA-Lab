#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "utilities.h"

// ... Keep existing tests for previous tasks intact ...

utilities::Matrix generate_random_matrix(int size) {
    utilities::Matrix mat(size, std::vector<int>(size));
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            mat[i][j] = rand() % 10;
    return mat;
}

void test_strassen() {
    // Test 1: 2x2 Matrix
    utilities::Matrix A2 = {{1, 2}, {3, 4}};
    utilities::Matrix B2 = {{5, 6}, {7, 8}};
    auto naive2 = utilities::multiply_naive(A2, B2);
    auto strassen2 = utilities::multiply_strassen(A2, B2);
    std::cout << "Strassen 2x2 test: " 
              << (naive2 == strassen2 ? "PASS" : "FAIL") << "\n";

    // Test 2: 4x4 Matrix
    utilities::Matrix A4 = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    utilities::Matrix B4 = {{2, 3, 4, 5}, {6, 7, 8, 9}, {1, 0, 1, 0}, {0, 1, 0, 1}};
    auto naive4 = utilities::multiply_naive(A4, B4);
    auto strassen4 = utilities::multiply_strassen(A4, B4);
    std::cout << "Strassen 4x4 test: " 
              << (naive4 == strassen4 ? "PASS" : "FAIL") << "\n";

    // Test 3: Random values comparison (4x4)
    auto Arand = generate_random_matrix(4);
    auto Brand = generate_random_matrix(4);
    auto naive_rand = utilities::multiply_naive(Arand, Brand);
    auto strassen_rand = utilities::multiply_strassen(Arand, Brand);
    std::cout << "Strassen random 4x4 matrix test: " 
              << (naive_rand == strassen_rand ? "PASS" : "FAIL") << "\n";
}

int main() {
    test_strassen();
    return 0;
}