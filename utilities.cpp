#include "utilities.h"

namespace utilities {
    int add(int a, int b) { return a + b; }

    std::vector<int> find_all_indices(const int arr[], int size, int key) {
        std::vector<int> indices;
        for (int i = 0; i < size; ++i) {
            if (arr[i] == key) indices.push_back(i);
        }
        return indices;
    }

    int find_substring(const std::string& text, const std::string& pattern) {
        if (pattern.empty()) return 0;
        size_t pos = text.find(pattern);
        return (pos != std::string::npos) ? static_cast<int>(pos) : -1;
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

    std::vector<int> find_modes(const int arr[], int size) {
        std::vector<int> modes;
        if (size <= 0) return modes;
        std::unordered_map<int, int> counts;
        int max_freq = 0;
        for (int i = 0; i < size; ++i) {
            int freq = ++counts[arr[i]];
            if (freq > max_freq) max_freq = freq;
        }
        for (const auto& pair : counts) {
            if (pair.second == max_freq) modes.push_back(pair.first);
        }
        return modes;
    }

    // Task 7 Helper functions
    static Matrix add_matrix(const Matrix& A, const Matrix& B) {
        int n = A.size();
        Matrix C(n, std::vector<int>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                C[i][j] = A[i][j] + B[i][j];
        return C;
    }

    static Matrix sub_matrix(const Matrix& A, const Matrix& B) {
        int n = A.size();
        Matrix C(n, std::vector<int>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                C[i][j] = A[i][j] - B[i][j];
        return C;
    }

    Matrix multiply_naive(const Matrix& A, const Matrix& B) {
        int n = A.size();
        Matrix C(n, std::vector<int>(n, 0));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                for (int k = 0; k < n; ++k)
                    C[i][j] += A[i][k] * B[k][j];
        return C;
    }

    Matrix multiply_strassen(const Matrix& A, const Matrix& B) {
        int n = A.size();
        if (n == 1) return {{A[0][0] * B[0][0]}};

        int k = n / 2;
        Matrix A11(k, std::vector<int>(k)), A12(k, std::vector<int>(k)),
               A21(k, std::vector<int>(k)), A22(k, std::vector<int>(k));
        Matrix B11(k, std::vector<int>(k)), B12(k, std::vector<int>(k)),
               B21(k, std::vector<int>(k)), B22(k, std::vector<int>(k));

        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) {
                A11[i][j] = A[i][j];         A12[i][j] = A[i][j + k];
                A21[i][j] = A[i + k][j];     A22[i][j] = A[i + k][j + k];
                B11[i][j] = B[i][j];         B12[i][j] = B[i][j + k];
                B21[i][j] = B[i + k][j];     B22[i][j] = B[i + k][j + k];
            }
        }

        Matrix P1 = multiply_strassen(add_matrix(A11, A22), add_matrix(B11, B22));
        Matrix P2 = multiply_strassen(add_matrix(A21, A22), B11);
        Matrix P3 = multiply_strassen(A11, sub_matrix(B12, B22));
        Matrix P4 = multiply_strassen(A22, sub_matrix(B21, B11));
        Matrix P5 = multiply_strassen(add_matrix(A11, A12), B22);
        Matrix P6 = multiply_strassen(sub_matrix(A21, A11), add_matrix(B11, B12));
        Matrix P7 = multiply_strassen(sub_matrix(A12, A22), add_matrix(B21, B22));

        Matrix C11 = add_matrix(sub_matrix(add_matrix(P1, P4), P5), P7);
        Matrix C12 = add_matrix(P3, P5);
        Matrix C21 = add_matrix(P2, P4);
        Matrix C22 = add_matrix(add_matrix(sub_matrix(P1, P2), P3), P6);

        Matrix C(n, std::vector<int>(n));
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) {
                C[i][j] = C11[i][j];         C[i][j + k] = C12[i][j];
                C[i + k][j] = C21[i][j];     C[i + k][j + k] = C22[i][j];
            }
        }
        return C;
    }
}