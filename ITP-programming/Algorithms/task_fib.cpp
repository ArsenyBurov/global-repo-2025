//Реализовать поиск числа Фиббоначчи следующими способами:
//Через рекуррентные соотношения.
//Через золотое сечение.
//С использованием матриц.
//Сравнить время работы алгоритмов.
#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>//для работы со временем

using namespace std;
using namespace std::chrono;//для работы со временем

//рекурсивная функция
long long fib_rec_help(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fib_rec_help(n - 1) + fib_rec_help(n - 2);
}

//через рекуррентные соотношения
long long fib_recurrence(int n) {
    auto start = high_resolution_clock::now();//замер времени
    long long result = fib_rec_help(n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "время работы рекурсивного метода: " << duration.count() << " микросекунд" << endl;
    return result;
}

//через золотое сечение
long long fib_gold(int n) {
    auto start = high_resolution_clock::now();//замер времени

    long long result;
    if (n <= 0) result = 0;
    else {
        double phi = (1 + sqrt(5)) / 2;//формула для золотого сечения
        result = round(pow(phi, n) / sqrt(5));
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "время работы метода золотого сечения: " << duration.count() << " микросекунд" << endl;

    return result;
}

//функция для умножения матриц
void multiply_matrix(long long f[2][2], long long m[2][2]) {
    long long a = f[0][0] * m[0][0] + f[0][1] * m[1][0];
    long long b = f[0][0] * m[0][1] + f[0][1] * m[1][1];
    long long c = f[1][0] * m[0][0] + f[1][1] * m[1][0];
    long long d = f[1][0] * m[0][1] + f[1][1] * m[1][1];

    f[0][0] = a;
    f[0][1] = b;
    f[1][0] = c;
    f[1][1] = d;
}

//функция для возведения матрицы в степень
void power_matrix(long long f[2][2], int n) {
    if (n <= 1) return;

    long long m[2][2] = { {1, 1}, {1, 0} };

    power_matrix(f, n / 2);
    multiply_matrix(f, f);

    if (n % 2 != 0) {
        multiply_matrix(f, m);
    }
}

//метод матриц
long long fib_matrix(int n) {
    auto start = high_resolution_clock::now();//замер времени

    long long result;
    if (n <= 0) result = 0;
    else {
        long long f[2][2] = { {1, 1}, {1, 0} };
        power_matrix(f, n - 1);
        result = f[0][0];
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "время работы матричного метода: " << duration.count() << " микросекунд" << endl;

    return result;
}

int main() {
    setlocale(LC_ALL, "RUS");
    int n;
    cout << "введите номер числа Фибоначчи: ";
    cin >> n;

    if (n < 0) {
        cout << "номер должен быть неотрицательным" << endl;
        return 1;
    }
    if (n >= 40) {//при n>=40 первый метод будет работать очень долго
        cout << "\n2. метод золотого сечения:" << endl;
        long long fib_gr = fib_gold(n);
        cout << "результат: " << fib_gr << endl;

        cout << "\n3. матричный метод:" << endl;
        long long fib_mat = fib_matrix(n);
        cout << "результат: " << fib_mat << endl;
        cout << "\n1. рекурсивный метод (число может быть слишком большим для рекурсии):" << endl;
        long long fib_rec = fib_recurrence(n);
        cout << "результат: " << fib_rec << endl;

    }
    else {
        cout << "\n1. рекурсивный метод:" << endl;
        long long fib_rec = fib_recurrence(n);
        cout << "результат: " << fib_rec << endl;

        cout << "\n2. метод золотого сечения:" << endl;
        long long fib_gr = fib_gold(n);
        cout << "результат: " << fib_gr << endl;

        cout << "\n3. матричный метод:" << endl;
        long long fib_mat = fib_matrix(n);
        cout << "результат: " << fib_mat << endl;
    }


    return 0;
}
