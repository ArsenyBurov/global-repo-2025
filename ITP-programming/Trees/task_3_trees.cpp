//Вариант 1 задание 3
//Даны числа: 5721348096. Создать дерево бинарного поиска (написать функцию).
//Вывести дерево.Написать функцию для прямого обхода и вывести результат.
#include <iostream>
#include <vector>
#include <windows.h>
#include <iomanip>
using namespace std;

HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

struct tree {
    int inf;
    tree* left;
    tree* right;
};

tree* node(int x) {
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = NULL;
    return n;
}

tree* insert(tree* t, int x) {
    if (!t) return node(x);
    if (x < t->inf)
        t->left = insert(t->left, x);
    else if (x > t->inf)
        t->right = insert(t->right, x);
    return t;
}

void preorder(tree* t) {
    if (t) {
        cout << t->inf << " ";
        preorder(t->left);
        preorder(t->right);
    }
}

int calculate_max_height(tree* x) {
    if (!x) return 0;
    int left_height = calculate_max_height(x->left);
    int right_height = calculate_max_height(x->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

void print_helper(tree* x, const COORD pos, const short offset) {
    SetConsoleCursorPosition(outp, pos);
    cout << setw(offset + 1) << x->inf;
    if (x->left) print_helper(x->left, { pos.X, short(pos.Y + 1) }, offset >> 1);
    if (x->right) print_helper(x->right, { short(pos.X + offset), short(pos.Y + 1) }, offset >> 1);
}

void print(tree* root) {
    if (root) {
        int max = calculate_max_height(root);
        short width = 1 << (max + 1), max_w = 128;
        if (width > max_w) width = max_w;

        for (int i = 0; i < max; ++i) cout << '\n';
        GetConsoleScreenBufferInfo(outp, &csbInfo);
        COORD endPos = csbInfo.dwCursorPosition;
        print_helper(root, { 0, short(endPos.Y - max) }, width >> 1);
        SetConsoleCursorPosition(outp, endPos);
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    tree* root = NULL;

    // Элементы заданы в векторе
    vector<int> numbers = { 5, 7, 2, 1, 3, 4, 8, 0, 9, 6 };

    // Вставляем элементы из вектора в дерево
    for (size_t i = 0; i < numbers.size(); ++i) {
        int current_number = numbers[i];
        root = insert(root, current_number);
    }

    cout << "Дерево бинарного поиска:\n";
    print(root);
    cout << "\n\n";

    cout << "Прямой обход (preorder): ";
    preorder(root);
    cout << "\n";

    return 0;
}
