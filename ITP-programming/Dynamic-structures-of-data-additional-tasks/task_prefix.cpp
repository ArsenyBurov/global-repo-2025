//Дано математическое выражение.Вывести его в префиксной форме
#include <iostream>
#include <string>
using namespace std;

struct stack {
    char inf;
    stack* next;
};


void push(stack*& h, char x) {
    stack* r = new stack; //создаем новый элемент
    r->inf = x;//поле inf = x
    r->next = h;//следующим элементов является h
    h = r; //теперь r является головой
}

char pop(stack*& h) {
    char i = h->inf; //значение первого элемента
    stack* r = h;//указатель на голову стека
    h = h->next;//переносим указатель на следующий элемент
    delete r;//удаляем первый элемент
    return i;//возвращаем значение
}


int prior(char op) {//функция для определения приоритета операций
    if (op == '(') return 1;
    if (op == '+' || op == '-') return 2;
    if (op == '*' || op == '/') return 3;
    return 0;
}


string reverseString(string str) {//функция для переворота строки
    int left = 0;
    int right = str.length() - 1;
    while (left < right) {
        swap(str[left++], str[right--]);
    }
    return str;
}


string toprefix(string infix) {//основная функция для перевода в префиксную форму
    stack* znak = NULL; //стек для операторов
    string prefix;//результирующая строка
    string reversedInfix = reverseString(infix);//переворачиваем исходную строку


    for (size_t i = 0; i < reversedInfix.length(); ++i) {
        if (reversedInfix[i] == '(') reversedInfix[i] = ')';
        else if (reversedInfix[i] == ')') reversedInfix[i] = '(';
    }

    //обрабатываем перевернутое выражение
    for (int i = 0; i < reversedInfix.length(); i++) {
        char current = reversedInfix[i];


        if (isalnum(current)) {//если текущий символ буква или цифра
            prefix += current; //добавляем в результирующую строку
        }
     
        else if (current == '(') { //если символ - открывающая скобка
            push(znak, current); //кладем в стек
        }
        else if (current == ')') { //если символ - закрывающая скобка
            while (znak != NULL && znak->inf != '(') {
                prefix += pop(znak); //переносим операторы в результирующую строку
            }
            if (znak != NULL) {//удаляем '(' из стека
                pop(znak);
            }
        }
        else {//работаем с операторами +-*/
            while (znak != NULL && prior(znak->inf) > prior(current)) {
                prefix += pop(znak); 
            }
            push(znak, current); //кладем текущий оператор в стек
        }
    }

    while (znak != NULL) {
        prefix += pop(znak);
    }
    prefix = reverseString(prefix);//переворачиваем результат

    return prefix;
}

int main() {
    setlocale(LC_ALL, "RUS");
    string infix;
    cout << "введите выражение без пробелов: ";
    getline(cin, infix);
    string prefix = toprefix(infix);
    cout << "префиксная форма: " << prefix << endl;
    return 0;
}
