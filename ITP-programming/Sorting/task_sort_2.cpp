//10. Сначала по должности, потом по зарплате с помощью гномьей сортировки.
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

ifstream in("bazaeng.txt");
ofstream out("b2.txt");

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
    while (in >> temp.surname >> temp.position) { 
        string tmp;
        in >> tmp; 
        temp.dob = strdate(tmp);
        in >> temp.exp >> temp.salary; 
        x.push_back(temp);
    }
    return x;
}

void print(people x) {
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

// функция для сравнения двух сотрудников по должности и зарплате
bool compare(people& a, people& b) {
    if (a.position != b.position) {
        return a.position > b.position; // cначала сортируем по должности (по алфавиту)
        //return a.position < b.position;
    }
    else {
        return a.salary < b.salary; 
    }
}

// гномья сортировка
void gnomeSort(vector<people>& a) {
    int n = a.size();
    int ix = 0;

    while (ix < n) {
        if (ix == 0 || compare(a[ix], a[ix - 1])) {
            ix++;
        }
        else {
            swap(a[ix], a[ix - 1]);
            ix--;
        }
    }
}

int main() {
    vector<people> x;
    x = inFile();
    gnomeSort(x);
    for (size_t i = 0; i < x.size(); ++i) {
        print(x[i]);
    }
    return 0;
}
