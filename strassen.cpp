#include <iostream>
#include <vector>
#include <random>

std::vector<std::vector<int>> generateRandomMatrix(int rows, int cols, int min, int max) {
    std::vector<std::vector<int>> randomMatrix(rows, std::vector<int>(cols));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            randomMatrix[i][j] = distribution(gen);
        }
    }

    return randomMatrix;
}


std::vector<std::vector<int>> subtractMatrix(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2) {
    int n = matrix1.size();
    std::vector<std::vector<int>> result(n, std::vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }

    return result;
}

std::vector<std::vector<int>> addMatrix(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2) {
    int n = matrix1.size();
    std::vector<std::vector<int>> result(n, std::vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    return result;
}

/*std::vector<std::vector<int>> strassenMatrixMultiplication(
    const std::vector<std::vector<int>>& matrix1,
    const std::vector<std::vector<int>>& matrix2) {

    int n = matrix1.size();

    if (n == 1) {
        std::vector<std::vector<int>> result = { {matrix1[0][0] * matrix2[0][0]} };
        return result;
    }

    int new_n = n / 2;

    std::vector<std::vector<int>> A11(new_n, std::vector<int>(new_n));
    std::vector<std::vector<int>> A12(new_n, std::vector<int>(new_n));
    std::vector<std::vector<int>> A21(new_n, std::vector<int>(new_n));
    std::vector<std::vector<int>> A22(new_n, std::vector<int>(new_n));

    std::vector<std::vector<int>> B11(new_n, std::vector<int>(new_n));
    std::vector<std::vector<int>> B12(new_n, std::vector<int>(new_n));
    std::vector<std::vector<int>> B21(new_n, std::vector<int>(new_n));
    std::vector<std::vector<int>> B22(new_n, std::vector<int>(new_n));

    for (int i = 0; i < new_n; i++) {
        for (int j = 0; j < new_n; j++) {
            A11[i][j] = matrix1[i][j];
            A12[i][j] = matrix1[i][j + new_n];
            A21[i][j] = matrix1[i + new_n][j];
            A22[i][j] = matrix1[i + new_n][j + new_n];

            B11[i][j] = matrix2[i][j];
            B12[i][j] = matrix2[i][j + new_n];
            B21[i][j] = matrix2[i + new_n][j];
            B22[i][j] = matrix2[i + new_n][j + new_n];
        }
    }

    std::vector<std::vector<int>> M1 = strassenMatrixMultiplication(addMatrix(A11, A22), addMatrix(B11, B22));
    std::vector<std::vector<int>> M2 = strassenMatrixMultiplication(addMatrix(A21, A22), B11);
    std::vector<std::vector<int>> M3 = strassenMatrixMultiplication(A11, subtractMatrix(B12, B22));
    std::vector<std::vector<int>> M4 = strassenMatrixMultiplication(A22, subtractMatrix(B21, B11));
    std::vector<std::vector<int>> M5 = strassenMatrixMultiplication(addMatrix(A11, A12), B22);
    std::vector<std::vector<int>> M6 = strassenMatrixMultiplication(subtractMatrix(A21, A11), addMatrix(B11, B12));
    std::vector<std::vector<int>> M7 = strassenMatrixMultiplication(subtractMatrix(A12, A22), addMatrix(B21, B22));

    std::vector<std::vector<int>> C11 = addMatrix(subtractMatrix(addMatrix(M1, M4), M5), M7);
    std::vector<std::vector<int>> C12 = addMatrix(M3, M5);
    std::vector<std::vector<int>> C21 = addMatrix(M2, M4);
    std::vector<std::vector<int>> C22 = addMatrix(subtractMatrix(addMatrix(M1, M3), M2), M6);

    std::vector<std::vector<int>> result(2 * new_n, std::vector<int>(2 * new_n));

    for (int i = 0; i < new_n; i++) {
        for (int j = 0; j < new_n; j++) {
            result[i][j] = C11[i][j];
            result[i][j + new_n] = C12[i][j];
            result[i + new_n][j] = C21[i][j];
            result[i + new_n][j + new_n] = C22[i][j];
        }
    }

    return result;
}*/

std::vector<std::vector<int>> strassenMatrixMultiplication(
    const std::vector<std::vector<int>>& matrix1,
    const std::vector<std::vector<int>>& matrix2) {

    int n = matrix1.size();

    if (n == 1) {
        std::vector<std::vector<int>> result = { {matrix1[0][0] * matrix2[0][0]} };
        return result;
    }

    int new_n = n / 2;

    std::vector<std::vector<int>> A11(new_n, std::vector<int>(new_n));
    std::vector<std::vector<int>> A12(new_n, std::vector<int>(new_n));
    std::vector<std::vector<int>> A21(new_n, std::vector<int>(new_n));
    std::vector<std::vector<int>> A22(new_n, std::vector<int>(new_n));

    std::vector<std::vector<int>> B11(new_n, std::vector<int>(new_n));
    std::vector<std::vector<int>> B12(new_n, std::vector<int>(new_n));
    std::vector<std::vector<int>> B21(new_n, std::vector<int>(new_n));
    std::vector<std::vector<int>> B22(new_n, std::vector<int>(new_n));

    for (int i = 0; i < new_n; i++) {
        for (int j = 0; j < new_n; j++) {
            A11[i][j] = matrix1[i][j];
            A12[i][j] = matrix1[i][j + new_n];
            A21[i][j] = matrix1[i + new_n][j];
            A22[i][j] = matrix1[i + new_n][j + new_n];

            B11[i][j] = matrix2[i][j];
            B12[i][j] = matrix2[i][j + new_n];
            B21[i][j] = matrix2[i + new_n][j];
            B22[i][j] = matrix2[i + new_n][j + new_n];
        }
    }

    std::vector<std::vector<int>> M1 = addMatrix(A21, A22);
    std::vector<std::vector<int>> M2 = subtractMatrix(M1, A11);
    std::vector<std::vector<int>> M3 = subtractMatrix(A11,A21);
    std::vector<std::vector<int>> M4 = subtractMatrix(A12, M2);
    std::vector<std::vector<int>> M5 = subtractMatrix(B12,B11);
    std::vector<std::vector<int>> M6 = subtractMatrix(B22, M5);
    std::vector<std::vector<int>> M7 = subtractMatrix(B22, B12);
    std::vector<std::vector<int>> M8 = subtractMatrix(M6, B21);
    std::vector<std::vector<int>> P1 = strassenMatrixMultiplication(M2, M6);
    std::vector<std::vector<int>> P2 = strassenMatrixMultiplication(A11, B11);
    std::vector<std::vector<int>> P3 = strassenMatrixMultiplication(A12, B21);
    std::vector<std::vector<int>> P4 = strassenMatrixMultiplication(M3, M7);
    std::vector<std::vector<int>> P5 = strassenMatrixMultiplication(M1, M5);
    std::vector<std::vector<int>> P6 = strassenMatrixMultiplication(M4, B22);
    std::vector<std::vector<int>> P7 = strassenMatrixMultiplication(A22, M8);
    std::vector<std::vector<int>> T1 = addMatrix(P1, P2);
    std::vector<std::vector<int>> T2 = addMatrix(T1, P4);


    std::vector<std::vector<int>> C11 = addMatrix(P2,P3);
    std::vector<std::vector<int>> C12 = addMatrix(T1,(addMatrix(P5,P6)));
    std::vector<std::vector<int>> C21 = subtractMatrix(T2, P7);
    std::vector<std::vector<int>> C22 = addMatrix(T2,P5);

    std::vector<std::vector<int>> result(2 * new_n, std::vector<int>(2 * new_n));

    for (int i = 0; i < new_n; i++) {
        for (int j = 0; j < new_n; j++) {
            result[i][j] = C11[i][j];
            result[i][j + new_n] = C12[i][j];
            result[i + new_n][j] = C21[i][j];
            result[i + new_n][j + new_n] = C22[i][j];
        }
    }

    return result;
}


int main() {
    std::vector<std::vector<int>> matrix1 = { {1, 2,3,4}, {5, 6,7,8} ,{9,10,11,12},{5, 6,7,8} };
    std::vector<std::vector<int>> matrix2 = { {10,11,12,13}, {13, 14,15,16}, {16,17,18,19},{5, 6,7,8} };
    //std::vector<std::vector<int>> matrix1 = generateRandomMatrix(8, 8, 1, 10);
    //std::vector<std::vector<int>> matrix2 = generateRandomMatrix(8, 8, 1, 10);

    std::vector<std::vector<int>> result = strassenMatrixMultiplication(matrix1, matrix2);

    std::cout << "Matrix 1:" << std::endl;
    for (const auto& row : matrix1) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Matrix 2:" << std::endl;
    for (const auto& row : matrix2) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Result:" << std::endl;
    for (const auto& row : result) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}


