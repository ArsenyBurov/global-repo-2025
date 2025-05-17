//Определить является ли число простым, используя алгоритм Миллера-Рабина
#include <iostream>
#include <random>
#include <cmath>

using namespace std;

//возведение в степень
long long mod_pow(long long a, long long b, long long n) {
    long long result = 1;
    a = a % n;

    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % n;
        }
        a = (a * a) % n;
        b = b / 2;
    }

    return result;
}

//функция для проверки свидетеля простоты
bool witness(long long a, long long n) {
    long long t = 0;
    long long u = n - 1;

    //находим t и u такие, что n-1 = 2^t * u
    while (u % 2 == 0) {
        u /= 2;
        t++;
    }

    long long prev = mod_pow(a, u, n);
    long long curr;

    for (long long i = 0; i < t; i++) {
        curr = (prev * prev) % n;
        if (curr == 1 && prev != 1 && prev != n - 1) {
            return true;
        }
        prev = curr;
    }

    if (curr != 1) {
        return true;
    }

    return false;
}

//основная функция проверки на простоту Миллера-Рабина
bool miller_rabin(long long n, long long k = 5) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    random_device rd;//генерация случайного числа
    mt19937 gen(rd());
    uniform_int_distribution<long long> dis(2, n - 2);

    for (int i = 0; i < k; i++) {
        long long a = dis(gen);
        if (witness(a, n)) {
            return false; // точно составное
        }
    }

    return true; // вероятно простое
}

int main() {
    setlocale(LC_ALL, "RUS");
    long long x;
    cout << "введите число: ";
    cin >> x;
    if (miller_rabin(x)) {
        cout << x << " - простое число." << endl;
    }
    else {
        cout << x << " - составное число." << endl;
    }
    return 0;
}
