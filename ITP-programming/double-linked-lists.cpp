//Создать двусвязный список из целых чисел. 
// Удалить все повторяющиеся элементы, оставив только их последние вхождения. 
// Например, было 1 2 2 1 3 4 5 1 2 5 4 3 5. Стало 1 2 4 3 5.
#include <iostream>
using namespace std;

struct list {
    int inf;
    list* next;
    list* prev;
};

void push(list*& h, list*& t, int x) {
    list* r = new list;
    r->inf = x;
    r->next = NULL;
    if (!h && !t) { //если список пуст
        r->prev = NULL;
        h = r;
    }
    else {
        t->next = r;
        r->prev = t;
    }
    t = r;
}

void print(list* h) {
    list* p = h;
    while (p) {
        cout << p->inf << " ";
        p = p->next;
    }
    cout << endl;
}


void delete_node(list*& h, list*& t, list* node) {//функция удаления узла из списка

    if (node == h && node == t) { //единственный элемент
        h = t = NULL;
    }
    else if (node == h) { //удаляем голову
        h = h->next;
        h->prev = NULL;
    }
    else if (node == t) { //удаляем хвост
        t = t->prev;
        t->next = NULL;
    }
    else { //удаление из середины
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    delete node;
}

bool is_last(list* node) {//флаг для проверки является ли текущий элемент последним вхождением
    if (!node) return false;
    int val = node->inf;//запоминаем значение
    list* current = node->next;
    while (current) {
        if (current->inf == val) {
            return false;
        }
        current = current->next;
    }
    return true;
}

void result(list*& h, list*& t) {
    if (!h || !h->next) return; //если список пуст или содержит 1 элемент

    list* current = h;
    while (current) {
        list* next_node = current->next; //сохраняем следующий узел перед возможным удалением

        if (!is_last(current)) {
            delete_node(h, t, current);
        }

        current = next_node;
    }
}

void del_list(list*& h, list*& t) {//функция удаления списка
    while (h) {
        list* p = h;
        h = h->next;
        if (h) h->prev = NULL;
        else t = NULL;
        delete p;
    }
}

int main() {
    list* head = NULL, * tail = NULL;
    int n, x;

    cout << "n: ";
    cin >> n;

    int* a = new int[n]; 

    cout << "elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> a[i]; 
        push(head, tail, a[i]); 
    }
    result(head, tail);

    cout << "res: ";
    print(head);


    del_list(head, tail);

    return 0;
}
