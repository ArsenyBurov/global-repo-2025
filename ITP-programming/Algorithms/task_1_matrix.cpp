//Реализовать перемножение двух матриц, используя алгоритм Штрасена
#include <iostream>
#include <vector>

using namespace std;

//функция для сложения двух матриц
vector<vector<int>> matrixadd(const vector<vector<int>>& A,
    const vector<vector<int>>& B) {
    size_t n = A.size();
    vector<vector<int>> result(n, vector<int>(n, 0));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }

    return result;
}

//функция для вычитания двух матриц
vector<vector<int>> matrixsubtract(const vector<vector<int>>& A,
    const vector<vector<int>>& B) {
    size_t n = A.size();
    vector<vector<int>> result(n, vector<int>(n, 0));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }

    return result;
}

//функция для умножения матриц по алгоритму Штрассена
vector<vector<int>> strassen(const vector<vector<int>>& A,
    const vector<vector<int>>& B) {
    size_t n = A.size();
    if (n == 1) {
        vector<vector<int>> C(1, vector<int>(1, 0));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    //раззделение матрицы на подматрицы
    size_t newsize = n / 2;
    vector<vector<int>> A11(newsize, vector<int>(newsize));
    vector<vector<int>> A12(newsize, vector<int>(newsize));
    vector<vector<int>> A21(newsize, vector<int>(newsize));
    vector<vector<int>> A22(newsize, vector<int>(newsize));
    vector<vector<int>> B11(newsize, vector<int>(newsize));
    vector<vector<int>> B12(newsize, vector<int>(newsize));
    vector<vector<int>> B21(newsize, vector<int>(newsize));
    vector<vector<int>> B22(newsize, vector<int>(newsize));
    for (size_t i = 0; i < newsize; ++i) {
        for (size_t j = 0; j < newsize; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newsize];
            A21[i][j] = A[i + newsize][j];
            A22[i][j] = A[i + newsize][j + newsize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newsize];
            B21[i][j] = B[i + newsize][j];
            B22[i][j] = B[i + newsize][j + newsize];
        }
    }

    vector<vector<int>> M1 = strassen(matrixadd(A11, A22), matrixadd(B11, B22));
    vector<vector<int>> M2 = strassen(matrixadd(A21, A22), B11);
    vector<vector<int>> M3 = strassen(A11, matrixsubtract(B12, B22));
    vector<vector<int>> M4 = strassen(A22, matrixsubtract(B21, B11));
    vector<vector<int>> M5 = strassen(matrixadd(A11, A12), B22);
    vector<vector<int>> M6 = strassen(matrixsubtract(A21, A11), matrixadd(B11, B12));
    vector<vector<int>> M7 = strassen(matrixsubtract(A12, A22), matrixadd(B21, B22));

    //ыычисляем подматрицы результата
    vector<vector<int>> C11 = matrixadd(matrixsubtract(matrixadd(M1, M4), M5), M7);
    vector<vector<int>> C12 = matrixadd(M3, M5);
    vector<vector<int>> C21 = matrixadd(M2, M4);
    vector<vector<int>> C22 = matrixadd(matrixsubtract(matrixadd(M1, M3), M2), M6);

    //результат из подматриц
    vector<vector<int>> result(n, vector<int>(n));
    for (size_t i = 0; i < newsize; ++i) {
        for (size_t j = 0; j < newsize; ++j) {
            result[i][j] = C11[i][j];
            result[i][j + newsize] = C12[i][j];
            result[i + newsize][j] = C21[i][j];
            result[i + newsize][j + newsize] = C22[i][j];
        }
    }

    return result;
}

//ввод матрицы
vector<vector<int>> create(size_t size) {
    vector<vector<int>> matrix(size, vector<int>(size));

    cout << "введите матрицу " << size << "x" << size << ":\n";
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            cin >> matrix[i][j];
        }
    }

    return matrix;
}

//вывод матрицы
void printMatrix(const vector<vector<int>>& matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    int size;
    cout << "введите размер матриц (должен быть степенью двойки): ";
    cin >> size;
    if ((size & (size - 1)) != 0 || size <= 0) {
        cout << "ошибка: размер матрицы должен быть положительной степенью двойки\n";
        return 1;
    }
    cout << "матрица A:\n";
    vector<vector<int>> A = create(size);
    cout << "матрица B:\n";
    vector<vector<int>> B = create(size);
    vector<vector<int>> C = strassen(A, B);
    cout << "умножение:\n";
    printMatrix(C);

    return 0;
}
