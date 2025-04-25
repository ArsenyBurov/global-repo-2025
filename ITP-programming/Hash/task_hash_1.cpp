//Метод деления по зарплате
//В файле содержатся данные о сотрудниках предприятия: фамилия, должность, дата рождения (день, месяц, год), стаж работы, зарплата (не менее 20 человек).  
//Файл прикрепить. Выполнить открытое и закрытое хэширование (лучше две разных программы). 
// Продемонстрировать поиск элемента (и в том и в другом случае) и удаление элемента (для открытого хэширования).  
//Хэш-функция и ключ хэширования - выбираете в опросе. 
//Программа должна демонстрировать - хэширование,
// вывод полученной хэш - таблицы, возможность ввода элемента, его поиск(вывести все данные, 
// соответствующие этому элементу).
// В случае открытого хэширования - удаление всех данных, соответствующих этому элементу.
//Для открытого хэширования использовать самостоятельно написанные функции для двусвязного списка.
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

//узел двусвязного списка для хранения данных сотрудников
struct list {
    people inf;
    list* next;
    list* prev;
};

//функция для преобразования строки даты в структуру date
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

//функция для чтения данных из файла
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

//функция для печати данных сотрудника
void print(people x) {
    cout << setw(12) << left << x.surname;
    cout << setw(15) << left << x.position;
    if (x.dob.dd < 10) cout << left << '0' << x.dob.dd << '.';
    else cout << left << x.dob.dd << '.';
    if (x.dob.mm < 10) cout << '0' << x.dob.mm << '.';
    else cout << x.dob.mm << '.';
    cout << left << setw(6) << x.dob.yy;
    cout << setw(10) << left << x.exp;
    cout << setw(10) << left << x.salary << endl;
}

// Вставка элемента в конец списка
void push(list*& h, list*& t, people x) {
    list* r = new list;
    r->inf = x;
    r->next = NULL;
    if (!h && !t) {
        r->prev = NULL;
        h = r;
    }
    else {
        t->next = r;
        r->prev = t;
    }
    t = r;
}

// Удаление узла из списка
void del_node(list*& h, list*& t, list* r) {
    if (!r) return;

    if (r == h && r == t) {
        h = t = NULL;
    }
    else if (r == h) {
        h = h->next;
        h->prev = NULL;
    }
    else if (r == t) {
        t = t->prev;
        t->next = NULL;
    }
    else {
        r->next->prev = r->prev;
        r->prev->next = r->next;
    }
    delete r;
}

//удаление всего списка
void del_list(list*& h, list*& t) {
    while (h) {
        list* p = h;
        h = h->next;
        if (h) h->prev = NULL;
        else t = NULL;
        delete p;
    }
}

// Хэш-функция методом деления
int hash_function(int salary, int table_size) {
    return salary % table_size;
}

//создание хэш-таблицы
void create_hash_table(vector<people>& data, vector<list*>& heads, vector<list*>& tails, int table_size) {
    heads.resize(table_size, NULL);
    tails.resize(table_size, NULL);

    for (size_t i = 0; i < data.size(); i++) {
        people& person = data[i];
        int index = hash_function(person.salary, table_size);
        push(heads[index], tails[index], person);
    }
}

//поиск сотрудников по зарплате
void search_by_salary(vector<list*>& heads, int salary, int table_size) {
    int index = hash_function(salary, table_size);
    list* current = heads[index];
    bool found = false;

    cout << "\nрезультаты поиска для зарплаты " << salary << ":\n";
    while (current) {
        if (current->inf.salary == salary) {
            print(current->inf);
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "сотрудники с зарплатой " << salary << " не найдены.\n";
    }
}

//удаление сотрудников по зарплате
void delete_by_salary(vector<list*>& heads, vector<list*>& tails, int salary, int table_size) {
    int index = hash_function(salary, table_size);
    list* current = heads[index];
    bool deleted = false;

    while (current) {
        list* next_node = current->next;
        if (current->inf.salary == salary) {
            del_node(heads[index], tails[index], current);
            deleted = true;
        }
        current = next_node;
    }

    if (deleted) {
        cout << "все сотрудники с зарплатой " << salary << " удалены.\n";
    }
    else {
        cout << "сотрудники с зарплатой " << salary << " не найдены.\n";
    }
}

// Вывод хэш-таблицы
void print_hash_table(vector<list*>& heads, int table_size) {
    cout << "\nхэш-таблица (ключ - зарплата):\n";
    for (int i = 0; i < table_size; ++i) {
        cout << "[" << i << "]: ";
        list* current = heads[i];
        while (current) {
            cout << current->inf.salary << " (" << current->inf.surname << ") -> ";
            current = current->next;
        }
        cout <<"NULL\n";
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    vector<people> employees = inFile();

    //выбор размера хэш-таблицы (простое число)
    int table_size = 23; //выбираем простое число

    //создание хэш-таблицы
    vector<list*> heads, tails;
    create_hash_table(employees, heads, tails, table_size);

    //ыывод хэш-таблицы
    print_hash_table(heads, table_size);

    //работа поиска
    int salary_to_search;
    cout << "\nвведите зарплату для поиска: ";
    cin >> salary_to_search;
    search_by_salary(heads, salary_to_search, table_size);

    //работа с удалением
    int salary_to_delete;
    cout << "\nвведите зарплату для удаления: ";
    cin >> salary_to_delete;
    delete_by_salary(heads, tails, salary_to_delete, table_size);

    //вывод обновленной таблицы
    print_hash_table(heads, table_size);

    //освобождаем память
    for (int i = 0; i < table_size; ++i) {
        del_list(heads[i], tails[i]);
    }

    return 0;
}
