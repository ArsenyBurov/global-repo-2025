//Создать стек, содержащий целые числа. 
// Создать новый стек, вставив новый элемент после первого 
// (первого, введенного с клавиатуры или из файла) четного элемента. Порядок следования чисел в новом стеке должен совпадать с первоначальным. 
// Например, было 1 2 3 4 5 6 7 8 9, стало  1 2 0 3 4 5 6 7 8 9 
#include<iostream>
using namespace std;

struct stack {
    int inf;
    stack* next;
};

void push(stack*& h, int x) {
    stack* r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

int pop(stack*& h) {
    int i = h->inf;
    stack* r = h;
    h = h->next;
    delete r;
    return i;
}

void reverse(stack*& h) {
    stack* head1 = NULL;
    while (h)
        push(head1, pop(h));
    h = head1;
}

stack* result(stack*& h, int y) {
    stack* temp = NULL;     //временный стек для хранения элементов в правильном порядке
    stack* res = NULL;      //результирующий стек
    bool inserted = false;  //флаг для вставки элемента только один раз

    reverse(h);

    
    while (h) {//проходим по элементам
        int c = pop(h);
        push(temp, c);  //сохраняем элемент во временный стек

        
        if (c % 2 == 0 && !inserted) {
            push(temp, y);    
            inserted = true;
        }
    }

    reverse(temp);
    return temp;
}

int main() {
    int n, y;
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
    cin >> y;
    stack* res = result(head, y);
    while (res)
        cout << pop(res) << " ";
    cout << endl;

    return 0;
}
