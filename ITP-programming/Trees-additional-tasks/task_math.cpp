#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;


struct tree {
    char inf;
    tree* left;
    tree* right;
    tree* parent;
};
struct stack {
    tree* inf;
    stack* next;
};


HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

//функции для стека
void push(stack*& h, tree* x) {
    stack* r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

tree* pop(stack*& h) {
    tree* i = h->inf;
    stack* r = h;
    h = h->next;
    delete r;
    return i;
}

//функция для нового узла
tree* node(char x) {
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = n->parent = NULL;
    return n;
}

//приоритет операторов
int prior(char op) {
    if (op == '(') return 1;
    if (op == '+' || op == '-') return 2;
    if (op == '*' || op == '/') return 3;
    return 0;
}

//Функция построения дерева из выражения
tree* create_tree(string str) {
    stack* st = NULL;
    stack* nodes = NULL;

    for (unsigned int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') continue;

        if (isdigit(str[i])) {
            push(nodes, node(str[i]));
        }
        else if (str[i] == '(') {
            push(st, node(str[i]));
        }
        else if (str[i] == ')') {
            while (st && st->inf->inf != '(') {
                tree* op = pop(st);
                op->right = pop(nodes);
                op->left = pop(nodes);
                push(nodes, op);
            }
            pop(st);
        }
        else {
            while (st && prior(st->inf->inf) >= prior(str[i])) {
                tree* op = pop(st);
                op->right = pop(nodes);
                op->left = pop(nodes);
                push(nodes, op);
            }
            push(st, node(str[i]));
        }
    }

    while (st) {
        tree* op = pop(st);
        op->right = pop(nodes);
        op->left = pop(nodes);
        push(nodes, op);
    }

    return pop(nodes);
}

void max_height(tree* x, short& max, short deepness = 1) {
    if (deepness > max) max = deepness;
    if (x->left) max_height(x->left, max, deepness + 1);
    if (x->right) max_height(x->right, max, deepness + 1);
}


bool isSizeOfConsoleCorrect(const short& width, const short& height) {
    GetConsoleScreenBufferInfo(outp, &csbInfo);
    COORD szOfConsole = csbInfo.dwSize;
    if (szOfConsole.X < width && szOfConsole.Y < height)
        cout << "Please increase the height and width of the terminal. ";
    else if (szOfConsole.X < width)
        cout << "Please increase the width of the terminal. ";
    else if (szOfConsole.Y < height)
        cout << "Please increase the height of the terminal. ";

    if (szOfConsole.X < width || szOfConsole.Y < height) {
        cout << "Size of your terminal now: " << szOfConsole.X << ' ' << szOfConsole.Y
            << ". Minimum required: " << width << ' ' << height << ".\n";
        return false;
    }
    return true;
}

void print_helper(tree* x, const COORD pos, const short offset) {
    if (!x) return;

    SetConsoleCursorPosition(outp, pos);
    cout << setw(offset + 1) << x->inf;
    if (x->left) print_helper(x->left, { pos.X, short(pos.Y + 1) }, offset >> 1);
    if (x->right) print_helper(x->right, { short(pos.X + offset), short(pos.Y + 1) }, offset >> 1);
}


void print_tree(tree* tr) {
    if (tr) {
        short max = 1;
        max_height(tr, max);
        short width = 1 << (max + 1);
        short max_w = 128;
        if (width > max_w) width = max_w;

        while (!isSizeOfConsoleCorrect(width, max)) system("pause");

        for (short i = 0; i < max; ++i) cout << '\n';


        GetConsoleScreenBufferInfo(outp, &csbInfo);
        COORD endPos = csbInfo.dwCursorPosition;

        print_helper(tr, { 0, short(endPos.Y - max) }, width >> 1);
        SetConsoleCursorPosition(outp, endPos);
    }
}

//обход для префиксной формы
void preorder(tree* tr) {
    if (tr) {
        cout << tr->inf << " ";
        preorder(tr->left);
        preorder(tr->right);
    }
}


//обход для постфиксной формы
void postorder(tree* tr) {
    if (tr) {
        postorder(tr->left);
        postorder(tr->right);
        cout << tr->inf << " ";
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    string exp;
    cout << "введите математическое выражение без пробелов: ";
    getline(cin, exp);
    string allowed = "+-*/()0123456789 ";
    tree* tr = create_tree(exp);
    cout << "\nдерево:\n";
    print_tree(tr);
    cout << "\n\nпрефиксная форма: ";
    preorder(tr);
    cout << "\nпостфиксная форма: ";
    postorder(tr);
    cout << endl;
    return 0;
}
