//Создать стек, содержащий целые числа. Перед  всеми простыми числами вставить новое число. 
// Порядок следования в результате должен совпадать с порядком следования ввода. 
// Например, было 1 2 3 4 5 6 7 8 9. Стало 1 0 2 0 3 4 0 5 6 0 7 8 9
#include<iostream>
using namespace std;

struct stack {
    int inf;
    stack* next;
};

void push(stack*& h, int x) {
    stack* r = new stack; //создаем новый элемент
    r->inf = x; //поле inf = x
    r->next = h; //следующим элементов является h
    h = r; //теперь r является головой

}

int pop(stack*& h) {
    int i = h->inf;//значение первого элемента
    stack* r = h;//указатель на голову стека
    h = h->next;//переносим указатель на следующий элемент
    delete r;//удаляем первый элемент
    return i;//возвращаем значение

}

void reverse(stack*& h) {//"обращение"стека
    stack* head1 = NULL;//инициализация буферного стека
    while (h)//пока стек не пуст
        push(head1, pop(h));//переписываем из одного стека в другой
    h = head1;//переобозначаем указатели
}

bool isPrime(int n) {//функция для проверки на простое число
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

stack* result(stack*& h, int m) {
    stack* temp = NULL;
    stack* res = NULL;
    int newl = m;

    while (h) {//сначала перекладываем элементы в temp 
        push(temp, pop(h));
    }
    while (temp) {
        int current = pop(temp);
        if (isPrime(current)) {
            push(res, current);
            push(res, newl);
        }
        else {
            push(res, current);
        }
    }

    return res;
}

int main() {
    int n, m;
    cout << "n = ";
    cin >> n;
    stack* head = NULL;
    int x;
    cout << "elements: ";
    for (int i = 0; i < n; i++) {
        cin >> x;
        push(head, x);
    }
    cout << "new element: ";
    cin >> m;
    reverse(head);//переворачиваем стек

    stack* res = result(head,m);//результат

    while (res)
        cout << pop(res) << " ";
    cout << endl;

    return 0;
}
