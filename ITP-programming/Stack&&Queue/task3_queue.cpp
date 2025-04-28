//Создать очередь из целых чисел. Удалить все повторяющиеся элементы, оставив только их первые вхождения.
// Например, было 1 2 2 1 3 4 5 1 2 5 4 3 5. Стало 1 2 3 4 5.
#include<iostream>
using namespace std;

struct queue {
    int inf;
    queue* next;
};

void push(queue*& h, queue*& t, int x) { //вставка элемента в очередь
    queue* r = new queue;    //создаем новый элемент
    r->inf = x;
    r->next = NULL;    //всегда последний
    if (!h && !t) {    //если очередь пуста
        h = t = r;    //это и голова и хвост
    }
    else {
        t->next = r;    //r - следующий для хвоста
        t = r;    //теперь r - хвост
    }
}

int pop(queue*& h, queue*& t) { //удаление элемента из очереди
    queue* r = h;    //создаем указатель на голову
    int i = h->inf;    //сохраняем значение головы
    h = h->next;    //сдвигаем указатель на следующий элемент
    if (!h)    //если удаляем последний элемент из очереди
        t = NULL;
    delete r;    //удаляем первый элемент
    return i;
}

bool contains(queue* h, int x) { //проверка, содержится ли элемент в очереди
    while (h) {
        if (h->inf == x) {
            return true;
        }
        h = h->next;
    }
    return false;
}

void rmdubl(queue*& h, queue*& t) {
    queue* resH = NULL, * resT = NULL; //результирующая очередь
  

    while (h) {
        int x = pop(h, t); //извлекаем первый элемент
        if (!contains(resH, x)) { //если его еще нет в результирующей очереди
            push(resH, resT, x); //добавляем в результат
        }
    }

    h = resH; //обновляем исходную очередь
    t = resT;
}

int main() {
    int n;
    int x;
    cout << "n: ";
    cin >> n;

    queue* h = NULL, * t = NULL; //исходная очередь

    cout << "elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> x;
        push(h, t, x); //заполняем очередь
    }

    rmdubl(h, t); //удаляем дубликаты

    cout << "res: ";
    while (h) {
        cout << pop(h, t) << " ";
    }
    cout << endl;

    return 0;
}
