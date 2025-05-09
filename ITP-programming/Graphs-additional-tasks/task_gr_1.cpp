//Дан неориентированный граф. Вывести Эйлеров путь или Эйлеров цикл, если он существует.
//Дан ориентированный граф.Если это возможно, реализовать топологическую сортировку
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//для стека и очереди
struct queue {
    int inf;
    queue* next;
};

void push(queue*& h, queue*& t, int x) {
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

int pop(queue*& h, queue*& t) {
    queue* r = h;
    int i = h->inf;
    h = h->next;
    if (!h)
        t = NULL;
    delete r;
    return i;
}

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

//ввод графа
vector<vector<int>> createlist() {
    int n, m;
    bool isori;

    cout << "введите количество вершин (N): ";
    cin >> n;
    cout << "введите количество ребер (M): ";
    cin >> m;
    cout << "граф ориентированный? 1 - да, 0 - нет: ";
    cin >> isori;

    vector<vector<int>> Gr;
    Gr.resize(n);

    cout << "введите " << m << " ребер в формате x y:" << endl;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;

        if (isori) {
            if (x >= n || y >= n) {
                cout << "error: вершины " << x << " или " << y << " вне диапазона" << endl;
                continue;
            }
            Gr[x].push_back(y);
        }
        else {
            if (x >= n || y >= n) {
                cout << "error: вершины " << x << " или " << y << " вне диапазона" << endl;
                continue;
            }
            Gr[x].push_back(y);
            Gr[y].push_back(x);
        }
    }

    for (int i = 0; i < n; ++i) {
        sort(Gr[i].begin(), Gr[i].end());
        Gr[i].erase(unique(Gr[i].begin(), Gr[i].end()), Gr[i].end());
    }

    return Gr;
}

void printlist(vector<vector<int>>& Gr) {
    cout << endl << "cписок смежности:" << endl;
    for (int i = 0; i < Gr.size(); ++i) {
        cout << i << ": ";
        for (int vertex : Gr[i]) {
            cout << vertex << " ";
        }
        cout << endl;
    }
}

bool iseyler(vector<vector<int>>& Gr, int& start, int& end) {
    vector<int> degree(Gr.size(), 0);
    for (int i = 0; i < Gr.size(); ++i) {
        degree[i] = Gr[i].size();
    }

    int cnt = 0;
    start = end = -1;

    for (int i = 0; i < degree.size(); ++i) {
        if (degree[i] % 2 != 0) {
            cnt++;
            if (start == -1) start = i;
            else if (end == -1) end = i;
            else return false; //больше двух вершин с нечетной степенью
        }
    }

    if (cnt == 0) {
        start = 0;
        end = -1;
        return true;
    }
    else if (cnt == 2) {
        return true;
    }
    else {
        return false;
    }
}
//поиск эйлерова пути/цикла
void findpath(vector<vector<int>> Gr) {
    int start, end;
    if (!iseyler(Gr, start, end)) {
        cout << "граф не содержит Эйлеров путь или цикл" << endl;
        return;
    }

    bool isCycle = (end == -1);

    if (!isCycle) {
    }

    stack* eylerpath = NULL;
    stack* vertexStack = NULL;
    if (isCycle) {
        push(vertexStack, 0);  //если это цикл, начинаем с вершины 0
    }
    else {
        push(vertexStack, start);  //если это путь, начинаем с начальной вершины
    }
    vector<vector<int>> tempGr = Gr;

    while (vertexStack) {
        int current = vertexStack->inf;
        if (!tempGr[current].empty()) {
            int next = tempGr[current].back();
            tempGr[current].pop_back();
            vector<int>::iterator it = find(tempGr[next].begin(), tempGr[next].end(), current);
            if (it != tempGr[next].end()) {
                tempGr[next].erase(it);
            }
            push(vertexStack, next);
        }
        else {
            push(eylerpath, pop(vertexStack));
        }
    }

    if (!isCycle) {
        stack* temp = eylerpath;
        int last = -1;
        while (temp) {
            last = temp->inf;
            temp = temp->next;
        }
        if (last != end) {
            reverse(eylerpath);
        }
    }

    if (isCycle) {
    cout << "Эйлеров цикл: ";
} else {
    cout << "Эйлеров путь: ";
}
    while (eylerpath) {
        cout << pop(eylerpath);
        if (eylerpath) cout << " -> ";
    }
    cout << endl;
}
//топологическая сортировка
void tophelp(int v, vector<bool>& visited, stack*& result, vector<vector<int>>& Gr) {
    visited[v] = true;
    for (size_t i = 0; i < Gr[v].size(); i++) {
        int u = Gr[v][i];
        if (visited[u] == false) {
            tophelp(u, visited, result, Gr);
        }
    }
    push(result, v);
}

void topologicalsort(vector<vector<int>>& Gr) {
    stack* result = NULL;
    vector<bool> visited(Gr.size(), false);

    for (int i = 0; i < Gr.size(); ++i) {
        if (!visited[i])
            tophelp(i, visited, result, Gr);
    }

    cout << "топологическая сортировка: ";
    while (result) {
        cout << pop(result) << " ";
    }
    cout << endl;
}



int main() {
    setlocale(LC_ALL, "RUS");
    cout << "задача 1: Эйлеров путь/цикл (выберите неориентированный граф)" << endl;
    vector<vector<int>> gr1 = createlist();
    printlist(gr1);
    findpath(gr1);
    cout << "\nзадача 2: топологическая сортировка (выберите ориентированный граф)" << endl;
    vector<vector<int>> gr2 = createlist();
    printlist(gr2);
    topologicalsort(gr2);
    return 0;
}
