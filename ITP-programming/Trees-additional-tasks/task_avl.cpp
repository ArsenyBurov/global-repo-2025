//Дано дерево. Вывести путь от корня до узла X
#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

struct tree {
    int inf;
    tree* left;
    tree* right;
    int height;
};

tree* node(int x) {
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}

int height(tree* t) {//считаем высоту
    if (t != nullptr) {
        return t->height;
    }
    else {
        return 0;
    }
}

int balance_factor(tree* t) {
    return height(t->right) - height(t->left);
}

void update_height(tree* t) {//обновление высоту
    int hl = height(t->left); 
    int hr = height(t->right); 

    if (hl > hr) {
        t->height = hl + 1;
    }
    else {
        t->height = hr + 1;
    }
}

tree* rotate_right(tree* t) {//правый поворот
    tree* q = t->left;
    t->left = q->right;
    q->right = t;
    update_height(t);
    update_height(q);
    return q;
}

tree* rotate_left(tree* t) {//левый поворот
    tree* p = t->right;
    t->right = p->left;
    p->left = t;
    update_height(t);
    update_height(p);
    return p;
}

tree* balance(tree* t) {//балансировка узла
    update_height(t);
    if (balance_factor(t) == 2) {
        if (balance_factor(t->right) < 0)
            t->right = rotate_right(t->right);
        return rotate_left(t);
    }
    if (balance_factor(t) == -2) {
        if (balance_factor(t->left) > 0)
            t->left = rotate_left(t->left);
        return rotate_right(t);
    }
    return t;
}

tree* insert(tree* t, int x) {//вставка нового элемента
    if (!t) return node(x);
    if (x < t->inf)
        t->left = insert(t->left, x);
    else
        t->right = insert(t->right, x);
    return balance(t);
}

tree* find_min(tree* t) {
    if (t->left != nullptr) {
        return find_min(t->left);
    }
    else {
        return t;  
    }
}

tree* remove_min(tree* t) {//удаление минимального узла
    if (!t->left) return t->right;
    t->left = remove_min(t->left);
    return balance(t);
}

tree* remove(tree* t, int x) {//функция для удаления узла
    if (!t) return nullptr;

    if (x < t->inf) {
        t->left = remove(t->left, x);
    }
    else if (x > t->inf) {
        t->right = remove(t->right, x);
    }
    else {
        if (!t->left) {
            tree* temp = t->right;
            delete t;
            return temp;
        }
        else if (!t->right) {
            tree* temp = t->left;
            delete t;
            return temp;
        }
        else {
            tree* maxLeft = t->left;
            while (maxLeft->right) {
                maxLeft = maxLeft->right;
            }
            t->inf = maxLeft->inf;
            t->left = remove(t->left, maxLeft->inf);
        }
    }

    return balance(t);
}

void inorder(tree* t) {//обход
    if (t) {
        inorder(t->left);
        cout << t->inf << " ";
        inorder(t->right);
    }
}

void print_path(tree* tr, int x) {//путь от корня до узла
    tree* current = tr;
    bool found = false;

    while (current) {
        cout << current->inf;
        if (current->inf == x) {
            found = true;
            break;
        }

        if (x < current->inf) {
            cout << " -> ";
            current = current->left;
        }
        else {
            cout << " -> ";
            current = current->right;
        }
    }

    if (!found)
        cout << "\nNode not found!";
    cout << endl;
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

void input_tree(tree*& root) {//ввод дерева
    int n, x;
    cout << "количество элементов: ";
    cin >> n;
    cout << "введите " << n << " элементов: ";
    for (int i = 0; i < n; ++i) {
        cin >> x;
        root = insert(root, x);
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    tree* root = NULL;
    input_tree(root);
    cout << "\nAVL дерево:\n";
    print(root);
    cout << "\n\n";
    cout << "обход: ";
    inorder(root);
    cout << "\n\n";
    int search_value;
    cout << "введити узел для вывода пути от корня: ";
    cin >> search_value;
    cout << " " << search_value << ": ";
    print_path(root, search_value);
    int delete_value;
    cout << "\nвведите узел для удаления: ";
    cin >> delete_value;
    root = remove(root, delete_value);
    cout << "\nдерево после удаления " << delete_value << ":\n";
    print(root);
    return 0;
}
