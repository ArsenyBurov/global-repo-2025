//Основная — линейное хеширование, вспомогательная — метод деления по году
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

ifstream in("bazaeng.txt");

struct date {
    int dd, mm, yy;
};

struct people {
    string surname;
    string position;
    date dob;
    int exp;
    int salary;
    bool is_empty; // Флаг пустой ячейки
};

date strdate(string str) {
    date x;
    x.dd = stoi(str.substr(0, 2));
    x.mm = stoi(str.substr(3, 2));
    x.yy = stoi(str.substr(6, 4));
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
        temp.is_empty = false;
        x.push_back(temp);
    }
    return x;
}

void print(people x) {
    if (x.is_empty) {
        cout << setw(12) << left << "NULL";
        cout << setw(15) << left << "NULL";
        cout << setw(12) << left << "NULL";
        cout << setw(6) << left << "NULL";
        cout << setw(10) << left << "NULL" << endl;
        return;
    }

    cout << setw(12) << left << x.surname;
    cout << setw(15) << left << x.position;
    cout << setw(2) << right << setfill('0') << x.dob.dd << ".";
    cout << setw(2) << right << setfill('0') << x.dob.mm << ".";
    cout << setw(6) << left << setfill(' ') << x.dob.yy;
    cout << setw(10) << left << x.exp;
    cout << setw(10) << left << x.salary << endl;
}

int hash_delenie(int year, int table_size) {
    return year % table_size;
}

int linehash(int year, int i, int table_size) {
    return (hash_delenie(year, table_size) + i) % table_size;
}

vector<people> create_hash_table(vector<people>& employees, int table_size) {
    vector<people> hash_table(table_size);

    //делаем все ячейки пустыми
    for (int cell = 0; cell < table_size; cell++) {
        hash_table[cell].is_empty = true;
    }

    //добавляем каждого сотрудника в таблицу
    for (int emp_num = 0; emp_num < employees.size(); emp_num++) {
        int try_count = 0;  //счетчик для попытки вставки
        int hash = linehash(employees[emp_num].dob.yy, try_count, table_size);

        //пробуем найти свободное место
        while (try_count < table_size) {
            if (hash_table[hash].is_empty) {
                hash_table[hash] = employees[emp_num];
                hash_table[hash].is_empty = false;
                break;
            }
            try_count++;
            hash = linehash(employees[emp_num].dob.yy, try_count, table_size);
        }

        if (try_count >= table_size) {
            cout << "ошибка " << employees[emp_num].surname << endl;
        }
    }

    return hash_table;
}


void search_in_hash_table(vector<people>& hash_table, int search_year) {
    int i = 0;
    int table_size = hash_table.size();
    bool found = false;

    while (i < table_size) {
        int hash = linehash(search_year, i, table_size);

        if (hash_table[hash].is_empty) {
            // Достигли пустой ячейки - прекращаем поиск
            break;
        }

        if (!hash_table[hash].is_empty && hash_table[hash].dob.yy == search_year) {
            cout << "\nнайден сотрудник:\n";
            print(hash_table[hash]);
            found = true;
        }

        i++;
    }

    if (!found) {
        cout << "\nсотрудники с годом рождения " << search_year << " не найдены." << endl;
    }
}

void print_hash_table(vector<people>& hash_table) {

    for (int i = 0; i < hash_table.size(); i++) {
        cout << setw(5) << left << i;
        print(hash_table[i]);
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    vector<people> employees = inFile();
    int table_size = 41;

    vector<people> hash_table = create_hash_table(employees, table_size);

    print_hash_table(hash_table);

    int search_year;
    cout << "\nВведите год рождения для поиска: ";
    cin >> search_year;

    search_in_hash_table(hash_table, search_year);

    return 0;
}
