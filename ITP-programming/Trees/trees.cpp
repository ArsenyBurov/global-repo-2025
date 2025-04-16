//Дан список целых чисел. Построить дерево бинарного поиска. 
// Вывести путь от корня до узла Х. 
#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;

//глобальные переменные для работы с консолью
HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

//struct tree {
//    int inf;
//    tree* left;
//    tree* right;
//    tree* parent;
//};
//
////создание узла, информационное поле равно x, остальные - NULL
//tree* node(int x) {
//    tree* n = new tree;
//    n->inf = x;
//    n->left = n->right = n->parent = NULL;
//    return n;
//}
//
////вставка элемента в дерево бинарного поиска
//void insert(tree*& tr, int x) {
//    tree* n = node(x);
//    if (!tr) tr = n; //если дерево пустое - корень
//    else {
//        tree* y = tr;
//        while (y) { //ищем куда вставлять
//            if (n->inf > y->inf) { //правая ветка
//                if (y->right) y = y->right;
//                else {
//                    n->parent = y; //узел становится правым ребенком
//                    y->right = n;
//                    break;
//                }
//            }
//            else if (n->inf < y->inf) { //левая ветка
//                if (y->left) y = y->left;
//                else {
//                    n->parent = y; //узел становится левым ребенком
//                    y->left = n;
//                    break;
//                }
//            }
//            else { //если элемент уже существует
//                delete n;
//                break;
//            }
//        }
//    }
//}
//
////поиск элемента в дереве бинарного поиска
//tree* find(tree* tr, int x) {
//    if (!tr || tr->inf == x) return tr; //нашли или дошли до конца ветки
//    if (x < tr->inf)
//        return find(tr->left, x); //ищем по левой ветке
//    else
//        return find(tr->right, x); //ищем по правой ветке
//}
//
////функция для вычисления высоты дерева
////высота узла - максимальная длина пути от узла до листа
//void max_height(tree* x, short& max, short deepness = 1) {
//    if (deepness > max) max = deepness;
//    if (x->left) max_height(x->left, max, deepness + 1);
//    if (x->right) max_height(x->right, max, deepness + 1);
//}
//
////функция проверки размера консоли
//bool isSizeOfConsoleCorrect(const short& width, const short& height) {
//    GetConsoleScreenBufferInfo(outp, &csbInfo);
//    COORD szOfConsole = csbInfo.dwSize;
//    if (szOfConsole.X < width || szOfConsole.Y < height) {
//        cout << "Please increase the size of the terminal. Size now: "
//            << szOfConsole.X << "x" << szOfConsole.Y
//            << ". Minimum required: " << width << "x" << height << ".\n";
//        return false;
//    }
//    return true;
//}
//
////вспомогательная функция для печати дерева
//void print_helper(tree* x, const COORD pos, const short offset) {
//    SetConsoleCursorPosition(outp, pos);
//    cout << right << setw(offset + 1) << x->inf;
//    if (x->left) print_helper(x->left, { pos.X, short(pos.Y + 1) }, offset >> 1);
//    if (x->right) print_helper(x->right, { short(pos.X + offset), short(pos.Y + 1) }, offset >> 1);
//}
//
////основная функция печати дерева
//void printTree(tree* tr) {
//    if (tr) {
//        short max = 1;
//        max_height(tr, max); //вычисляем высоту дерева
//        short width = 1 << (max + 1); //вычисляем ширину для печати
//        short max_w = 128;
//        if (width > max_w) width = max_w;
//
//        while (!isSizeOfConsoleCorrect(width, max)) {
//            system("pause");
//        }
//
//        //резервируем место для вывода
//        for (short i = 0; i < max; ++i) cout << '\n';
//
//        GetConsoleScreenBufferInfo(outp, &csbInfo);
//        COORD endPos = csbInfo.dwCursorPosition;
//
//        //выводим дерево
//        print_helper(tr, { 0, short(endPos.Y - max) }, width >> 1);
//        SetConsoleCursorPosition(outp, endPos);
//    }
//    else {
//        cout << "The tree is empty." << endl;
//    }
//}
//
////вывод пути от узла до корня
//void printpath(tree* node) {
//    if (!node) return;
//
//    //cчитаем глубину до корня
//    int depth = 0;
//    tree* current = node;
//    while (current) {
//        depth++;
//        current = current->parent;
//    }
//
//    int* path = new int[depth];
//    int count = 0;
//    current = node;
//    while (current) {
//        path[count++] = current->inf;
//        current = current->parent;
//    }
//    for (int i = count - 1; i >= 0; --i) {//выводим путь от корня к узлу
//        cout << path[i];
//        if (i > 0) cout << " -> ";
//    }
//    cout << endl;
//
//    delete[] path; //освобождаем память
//}
//
//int main() {
//    tree* tr = NULL;
//    int n, x;
//    cout << "n: ";
//    cin >> n;
//    cout << "enter " << n << " elements: ";
//    for (int i = 0; i < n; ++i) {
//        cin >> x;
//        insert(tr, x); //вставляем элементы в дерево
//    }
//
//    //печатаем дерево
//    cout << endl << "the tree:" << endl;
//    printTree(tr);
//
//    cout << endl << "x: ";
//    cin >> x;
//
//    tree* target = find(tr, x); //ищем элемент в дереве
//    if (!target) {
//        cout << "node " << x << " not found in the tree" << endl;
//    }
//    else {
//        cout << "path to " << x << ": ";
//        printpath(target); //выводим путь к элементу
//    }
//
//    return 0;
//}

//Дан список целых чисел. Построить дерево бинарного поиска. Вывести 
// все листья дерева

//struct tree {
//    int inf;
//    tree* left;
//    tree* right;
//    tree* parent;
//};
//
////создание нового узла
//tree* node(int x) {
//    tree* n = new tree;
//    n->inf = x;
//    n->left = n->right = n->parent = NULL;
//    return n;
//}
//
////вставка элемента в дерево
//void insert(tree*& tr, int x) {
//    tree* n = node(x);
//    if (!tr) tr = n; //если дерево пустое - корень
//    else {
//        tree* y = tr;
//        while (y) { //ищем куда вставлять
//            if (n->inf > y->inf) { //правая ветка
//                if (y->right) y = y->right;
//                else {
//                    n->parent = y; //узел становится правым ребенком
//                    y->right = n;
//                    break;
//                }
//            }
//            else if (n->inf < y->inf) { //левая ветка
//                if (y->left) y = y->left;
//                else {
//                    n->parent = y; //узел становится левым ребенком
//                    y->left = n;
//                    break;
//                }
//            }
//            else { //если элемент уже существует
//                delete n;
//                break;
//            }
//        }
//    }
//}
//
////функция для вывода листьев дерева
//void printleaves(tree* tr) {
//    if (tr) {
//        if (!tr->left && !tr->right) { //если узел - лист
//            cout << tr->inf << " ";
//        }
//        printleaves(tr->left); //рекурсивно обходим левое поддерево
//        printleaves(tr->right); //рекурсивно обходим правое поддерево
//    }
//}
//
////функция для вычисления высоты дерева
//void max_height(tree* x, short& max, short deepness = 1) {
//    if (deepness > max) max = deepness;
//    if (x->left) max_height(x->left, max, deepness + 1);
//    if (x->right) max_height(x->right, max, deepness + 1);
//}
//
////функция проверки размера консоли
//bool isSizeOfConsoleCorrect(const short& width, const short& height) {
//    GetConsoleScreenBufferInfo(outp, &csbInfo);
//    COORD szOfConsole = csbInfo.dwSize;
//    if (szOfConsole.X < width || szOfConsole.Y < height) {
//        cout << "Please increase the size of the terminal. Size now: "
//            << szOfConsole.X << "x" << szOfConsole.Y
//            << ". Minimum required: " << width << "x" << height << ".\n";
//        return false;
//    }
//    return true;
//}
//
////вспомогательная функция для печати дерева
//void print_helper(tree* x, const COORD pos, const short offset) {
//    SetConsoleCursorPosition(outp, pos);
//    cout << right << setw(offset + 1) << x->inf;
//    if (x->left) print_helper(x->left, { pos.X, short(pos.Y + 1) }, offset >> 1);
//    if (x->right) print_helper(x->right, { short(pos.X + offset), short(pos.Y + 1) }, offset >> 1);
//}
//
////основная функция печати дерева
//void printTree(tree* tr) {
//    if (tr) {
//        short max = 1;
//        max_height(tr, max);
//        short width = 1 << (max + 1);
//        short max_w = 128;
//        if (width > max_w) width = max_w;
//
//        while (!isSizeOfConsoleCorrect(width, max)) {
//            system("pause");
//        }
//
//        //резервируем место для вывода
//        for (short i = 0; i < max; ++i) cout << '\n';
//
//        GetConsoleScreenBufferInfo(outp, &csbInfo);
//        COORD endPos = csbInfo.dwCursorPosition;
//
//        //выводим дерево
//        print_helper(tr, { 0, short(endPos.Y - max) }, width >> 1);
//
//        //возвращаем курсор в конец
//        SetConsoleCursorPosition(outp, endPos);
//    }
//    else {
//        cout << "The tree is empty." << endl;
//    }
//}
//
//int main() {
//    tree* tr = NULL;
//    int n, x;
//
//    cout << "n: ";
//    cin >> n;
//
//    cout << "enter " << n << "elements: ";
//    for (int i = 0; i < n; ++i) {
//        cin >> x;
//        insert(tr, x);
//    }
//
//    //печатаем дерево
//    cout << endl << "tree:" << endl;
//    printTree(tr);
//
//    //выводим все листья
//    cout << endl << "leaves: ";
//    printleaves(tr);
//    cout << endl;
//
//    return 0;
//}

//Дан список целых чисел. Построить дерево бинарного поиска. 
//Удалить все четные элементы.
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
    tree* parent;
};

//создание узла
tree* node(int x) {
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = n->parent = NULL;
    return n;
}

//вставка элемента в дерево бинарного поиска
void insert(tree*& tr, int x) {
    tree* n = node(x);
    if (!tr) tr = n; //если дерево пустое - корень
    else {
        tree* y = tr;
        while (y) { //ищем куда вставлять
            if (n->inf > y->inf) { //правая ветка
                if (y->right) y = y->right;
                else {
                    n->parent = y; //узел становится правым ребенком
                    y->right = n;
                    break;
                }
            }
            else if (n->inf < y->inf) { //левая ветка
                if (y->left) y = y->left;
                else {
                    n->parent = y; //узел становится левым ребенком
                    y->left = n;
                    break;
                }
            }
            else {
                delete n;
                break;
            }
        }
    }
}

//поиск элемента в дереве бинарного поиска
tree* find(tree* tr, int x) {
    if (!tr || tr->inf == x) return tr; //нашли или дошли до конца ветки
    if (x < tr->inf)
        return find(tr->left, x); //ищем по левой ветке
    else
        return find(tr->right, x); //ищем по правой ветке
}

//поиск минимального элемента
tree* Min(tree* tr) {
    if (!tr->left) return tr; //нет левого ребенка
    else return Min(tr->left); //идем по левой ветке до конца
}

//поиск максимального элемента
tree* Max(tree* tr) {
    if (!tr->right) return tr; //нет правого ребенка
    else return Max(tr->right); //идем по правой ветке до конца
}

//поиск следующего элемента
tree* Next(tree* tr, int x) {
    tree* n = find(tr, x);
    if (!n) return NULL;

    if (n->right) //если есть правый ребенок
        return Min(n->right); //min по правой ветке

    tree* y = n->parent; //родитель
    while (y && n == y->right) { //пока не дошли до корня или узел - правый ребенок
        n = y; //идем вверх по дереву
        y = y->parent;
    }
    return y; //возвращаем родителя
}

//удаление узла из дерева бинарного поиска
void Delete(tree*& tr, tree* v) {
    if (!v) return;

    tree* p = v->parent;

    //1.удаление листа
    if (!v->left && !v->right) {
        if (!p) tr = NULL;
        else {
            if (p->left == v) p->left = NULL;
            else p->right = NULL;
        }
        delete v;
    }
    //2.удаление узла с одним ребенком
    else if (!v->left || !v->right) {
        tree* child = v->left ? v->left : v->right;
        if (p) {
            if (p->left == v) p->left = child;
            else p->right = child;
            child->parent = p;
        }
        else {
            tr = child;
            child->parent = NULL;
        }
        delete v;
    }
    //3.удаление узла с двумя детьми
    else {
        tree* succ = Min(v->right); //следующий за удаляемым узлом
        v->inf = succ->inf; //присваиваем значение
        Delete(tr, succ);
    }
}

//удаление всех четных узлов
void deleteEvenNodes(tree*& tr) {
    if (!tr) return;

    deleteEvenNodes(tr->left);
    deleteEvenNodes(tr->right);

    if (tr->inf % 2 == 0) {
        tree* toDelete = tr;
        Delete(tr, toDelete);
        if (tr) deleteEvenNodes(tr); //проверяем новый корень, если он изменился
    }
}

//определение максимальной высоты дерева
void max_height(tree* x, short& max, short deepness = 1) {
    if (deepness > max) max = deepness;
    if (x->left) max_height(x->left, max, deepness + 1);
    if (x->right) max_height(x->right, max, deepness + 1);
}

//проверка размера консоли
bool isSizeOfConsoleCorrect(const short& width, const short& height) {
    GetConsoleScreenBufferInfo(outp, &csbInfo);
    COORD szOfConsole = csbInfo.dwSize;
    if (szOfConsole.X < width || szOfConsole.Y < height) {
        cout << "Please increase the size of the terminal. Size now: "
            << szOfConsole.X << "x" << szOfConsole.Y
            << ". Minimum required: " << width << "x" << height << ".\n";
        return false;
    }
    return true;
}

//вспомогательная функция для вывода дерева
void print_helper(tree* x, const COORD pos, const short offset) {
    SetConsoleCursorPosition(outp, pos);
    cout << right << setw(offset + 1) << x->inf;
    if (x->left) print_helper(x->left, { pos.X, short(pos.Y + 1) }, offset >> 1);
    if (x->right) print_helper(x->right, { short(pos.X + offset), short(pos.Y + 1) }, offset >> 1);
}

//вывод дерева в консоль
void printTree(tree* tr) {
    if (tr) {
        short max = 1;
        max_height(tr, max);
        short width = 1 << (max + 1);
        short max_w = 128;
        if (width > max_w) width = max_w;

        while (!isSizeOfConsoleCorrect(width, max)) {
            system("pause");
        }

        for (short i = 0; i < max; ++i) cout << '\n';

        GetConsoleScreenBufferInfo(outp, &csbInfo);
        COORD endPos = csbInfo.dwCursorPosition;

        print_helper(tr, { 0, short(endPos.Y - max) }, width >> 1);

        SetConsoleCursorPosition(outp, endPos);
    }
    else {
        cout << "The tree is empty." << endl;
    }
}

int main() {
    tree* tr = NULL;
    int n, x;
    cout << "n: ";
    cin >> n;
    cout << "enter " << n << " elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> x;
        insert(tr, x);
    }

    cout << "tree:" << endl;
    printTree(tr);
    cout << endl;

    deleteEvenNodes(tr);

    cout << "tree after deletinп elements:" << endl;
    printTree(tr);

    return 0;
}
