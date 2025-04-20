//Граф представлен в виде списка смежности. 
//Реализовать обход в ширину, используя очередь, и нерекурсивный обход в глубину.
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct queue {//структура очереди
    int inf;
    queue* next;
};

void push(queue*& h, queue*& t, int x) {//функция добавления элемента в очередь
    queue* r = new queue;
    r->inf = x;
    r->next = NULL;
    if (!h && !t) {
        h = t = r;
    }
    else {
        t->next = r;
        t = r;
    }
}

int pop(queue*& h, queue*& t) {//функция удаления элемента из очереди
    queue* r = h;
    int i = h->inf;
    h = h->next;
    if (!h)
        t = NULL;
    delete r;
    return i;
}

struct stack {//структура стека
    int inf;
    stack* next;
};

void push(stack*& h, int x) {//функция добавления элемента в стек
    stack* r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

int pop(stack*& h) {//функция удаления элемента из стека
    int i = h->inf;
    stack* r = h;
    h = h->next;
    delete r;
    return i;
}

void bfs(vector<vector<int>>& Gr, int N, int x) {//функция обхода в ширину 
    queue* h = NULL, * t = NULL;
    vector<int> a(N, 0);

    a[x] = 1;
    push(h, t, x);
    cout << x << " ";

    while (h) {
        int current = pop(h, t);

        for (size_t i = 0; i < Gr[current].size(); ++i) {
            int neighbor = Gr[current][i];
            if (a[neighbor] == 0) {
                a[neighbor] = 1;
                push(h, t, neighbor);
                cout << neighbor << " ";
            }
        }
    }
    for (int i = 0; i < N; ++i) {
        if (a[i] == 0) {
            bfs(Gr, N, i);
        }
    }
}


vector<int> parse(string& line) {
    vector<int> numbers;
    string n;
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == ' ') {
            if (!n.empty()) {
                numbers.push_back(stoi(n));
                n.clear();
            }
        }
        else {
            n += c;
        }
    }
    if (!n.empty()) {
        numbers.push_back(stoi(n));
    }
    return numbers;
}

int main() {
    setlocale(LC_ALL, "RUS");
    int N;
    cout << "количество вершин графа: ";
    cin >> N;
    cin.ignore();
    vector<vector<int>> Gr(N);

    cout << "список смежности через пробел:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "вершина " << i << ": ";
        string line;
        getline(cin, line);
        vector<int> neighbors = parse(line);

        Gr[i] = neighbors;
    }
    int start;
    cout << "начальная вершина для обхода: ";
    cin >> start;
    cout << "результат обхода в ширину: ";
    bfs(Gr, N, start);
    cout << endl;
    cout << endl;

    return 0;
}
