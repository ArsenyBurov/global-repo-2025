//тимсорт
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int mr(int n) {//вычисляем minrun (поставим n>=8, чтобы использовать функцию слияния)
    int r = 0;
    while (n >= 8) {
        if (n % 2 != 0) {  
            r = 1;  
        }
        n = n / 2;   
    }
    return n + r;
}


void insertionSort(vector<int>& arr, int left, int right) {//сортировка вставками
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {//слияние
    int len1 = mid - left + 1, len2 = right - mid;
    vector<int> leftArr(len1), rightArr(len2);

    for (int i = 0; i < len1; i++) leftArr[i] = arr[left + i];
    for (int i = 0; i < len2; i++) rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < len1 && j < len2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < len1) arr[k++] = leftArr[i++];
    while (j < len2) arr[k++] = rightArr[j++];
}

void timsort(vector<int>& arr) {//основная функция для тимсорта
    int n = arr.size();
    int minRun = mr(n);
    for (int i = 0; i < n; i += minRun) {//сортировка массивов размером minrun
        insertionSort(arr, i, min(i + minRun - 1, n - 1));
    }
    for (int size = minRun; size < n; size = 2 * size) {//слияние подмассивов
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, n - 1);
            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}


int main() {
    int n, x;
    cout << "n ";
    cin >> n;
    vector<int> vec;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = ";
        cin >> x;
        vec.push_back(x);

    }
    timsort(vec);
    for (vector<int>::iterator iter = vec.begin(); iter != vec.end(); iter++) {
        cout << *iter << " ";
    }
    return 0;
}
