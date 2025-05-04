//По зарплате с помощью быстрой сортировки.
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

ifstream in("bazaeng.txt");
ofstream out("b1.txt");

struct date {
    int dd, mm, yy;
};

struct people {
    string surname;
    string position;
    date dob;
    int exp;
    int salary;
};

date strdate(string str) {
    date x;
    string temp = str.substr(0, 2);
    x.dd = atoi(temp.c_str());
    temp = str.substr(3, 2);
    x.mm = atoi(temp.c_str());
    temp = str.substr(6, 4); 
    x.yy = atoi(temp.c_str());
    return x;
}

vector<people> inFile() {
    vector<people> x;
    people temp;
    while (in >> temp.surname >> temp.position) { // считываем фамилию и должность
        string tmp;
        in >> tmp; // считываем дату рождения
        temp.dob = strdate(tmp);
        in >> temp.exp >> temp.salary; // считываем стаж и зарплату
        x.push_back(temp);
    }
    return x;
}

void print(people x) {//функция для печати результата
    out << setw(12) << left << x.surname; 
    out << setw(15) << left << x.position; 
    if (x.dob.dd < 10) out << left << '0' << x.dob.dd << '.'; 
    else out << left << x.dob.dd << '.';
    if (x.dob.mm < 10) out << '0' << x.dob.mm << '.'; 
    else out << x.dob.mm << '.';
    out << left << setw(6) << x.dob.yy; 
    out << setw(10) << left << x.exp; 
    out << setw(10) << left << x.salary << endl;
}

void quickSort(vector<people>& a, int left, int right) {//быстрая сортировка
    if (left < right) {
        int p = a[(left + right) / 2].salary; // выбор опорного элемента
        int i = left, j = right;
        while (i <= j) {
            while (a[i].salary < p) i++; 
            while (a[j].salary > p) j--; 
            if (i <= j) {
                swap(a[i], a[j]); // меняем местами
                i++;
                j--;
            }
        }
        quickSort(a, left, j); // сортировка левой части
        quickSort(a, i, right); // сортировка правой части
    }
}

int main() {
    vector<people> x;
    x = inFile();
    quickSort(x, 0, x.size() - 1);
    for (size_t i = 0; i < x.size(); ++i) {
        print(x[i]);
    }
    return 0;
}
