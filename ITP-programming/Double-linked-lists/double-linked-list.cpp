//Создать двусвязный список, содержащий целые числа. После всех чисел, равных последнему числу, вставить максимальный элемент. 
// Например, было 8 2 1 6 8 8 1 2 2 8 2. Стало 8 2 8 1 6 8 8 1 2 8 2 8 8 2 8 
#include <iostream>
using namespace std;


struct list {//структура двусвязного списка
    int inf;
    list* next;
    list* prev;
};

list* find(list* h, int x) {
    list* p = h;    //указатель на голову
    while (p) {      //пока не дошли до конца списка
        if (p->inf == x) break; //если нашли, прекращаем цикл
        p = p->next;    //переход к следующему элементу
    }
    return p;    //возвращаем указатель
}

//функция добавления элемента в конец списка
void push(list*& h, list*& t, int x) {
    list* r = new list;
    r->inf = x;
    r->next = NULL;
    if (!h && !t) { //если список пуст
        r->prev = NULL;
        h = r; //новый элемент становится головой
    }
    else {
        t->next = r;
        r->prev = t;
    }
    t = r; //новый элемент становится хвостом
}

//функция печати списка
void print(list* h) {
    list* p = h;
    while (p) {
        cout << p->inf << " ";
        p = p->next;
    }
    cout << endl;
}

int find_max(list* h) {//функция поиска максимального элемента в списке
    if (!h) return 0; //если список пуст
    int max_val = h->inf;
    list* p = h->next;
    while (p) {
        if (p->inf > max_val) {
            max_val = p->inf;
        }
        p = p->next;
    }
    return max_val;
}

void insert_after(list*& h, list*& t, list* r, int y) {//функция вставки элемента после указанного
    list* p = new list;
    p->inf = y;
    if (r == t) { //если вставляем после хвоста
        p->next = NULL;
        p->prev = r;
        r->next = p;
        t = p; //новый элемент становится хвостом
    }
    else { //вставка в середину списка
        r->next->prev = p;
        p->next = r->next;
        p->prev = r;
        r->next = p;
    }
}

void result(list*& h, list*& t) {
    if (!h) return;

    int last_val = t->inf;// значение последнего элемента
    int max_val = find_max(h);

    list* p = h;
    while (p) {
        list* found = find(p, last_val); //ищем следующий элемент, равный последнему
        if (!found) break; //если не нашли, выходим

        insert_after(h, t, found, max_val);
        p = found->next->next; //перескакиваем через вставленный элемент
    }
}

void del_list(list*& h, list*& t) {//функция удаления списка (очистка памяти)
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
