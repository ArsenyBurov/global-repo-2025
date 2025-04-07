//Создать двусвязный список, содержащий целые числа. 
// Удалить лишние элементы так, чтобы каждый элемент был не больше среднего арифметического всех элементов, следующих за ним. 
// Например, для списка 5 2 9 1 3 7 1 2 9, результат должен быть 2 1 3 1 2 9.
#include <iostream>
using namespace std;


struct list {
    int inf;
    list* next;
    list* prev;
};

//вставка элемента в конец списка
void push(list*& h, list*& t, int x) {
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


void print(list* h) {
    list* p = h;
    while (p) {
        cout << p->inf << " ";
        p = p->next;
    }
    cout << endl;
}


void del_node(list*& h, list*& t, list* r) {//функция для удаления элемента
    if (!r) return;

    if (r == h && r == t) {//единственный элемент списка
        h = t = NULL;
    }
    else if (r == h) {//удаляем голову списка
        h = h->next;//сдвигаем голову
        h->prev = NULL;
    }
    else if (r == t) {//удаляем хвост списка
        t = t->prev;//сдвигаем хвост
        t->next = NULL;
    }
    else {
        r->next->prev = r->prev;//для следующего от r предыдущим становится r->prev
        r->prev->next = r->next;//для предыдущего от r следующим становится r->next
    }
    delete r;//удаляем r
}


int calc_avg(list* node) {//функция для среднего арифмитического
    if (!node || !node->next) return 0;

    int sum = 0;
    int count = 0;
    list* p = node->next;

    while (p) {
        sum += p->inf;
        count++;
        p = p->next;
    }

    return sum / count;
}


void result(list*& h, list*& t) {
    if (!h || !h->next) return;

    list* current = h;
    while (current) {
        list* next_node = current->next;//сохраняем ссылку на следующий элемент

        int avg = calc_avg(current);

        if (current->next && current->inf > avg) {
            del_node(h, t, current);
        }

        current = next_node;
    }
}


void del_list(list*& h, list*& t) {
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

    cout << "elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> x;
        push(head, tail, x);
    }

    result(head, tail);

    cout << "res: ";
    print(head);

    del_list(head, tail);

    return 0;
}
