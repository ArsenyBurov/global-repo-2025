//Дан неориентированный взвешенный граф. 
//Найти кратчайшее расстояние от заданной вершины до всех остальных вершин.
//Вывести не только длину пути, но и сам этот путь. Алгоритм выбираете самостоятельно.
//в решении реализован алгоритм Дейкстры
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int INF = 1e9;

struct queue {
    int vertex;
    int distance;
    queue* next;
};

void push(queue*& head, queue*& tail, int vertex, int distance) {
    queue* new_node = new queue;
    new_node->vertex = vertex;
    new_node->distance = distance;
    new_node->next = NULL;

    if (!head) {
        head = tail = new_node;
    }
    else if (distance < head->distance) {
        new_node->next = head;
        head = new_node;
    }
    else {
        queue* current = head;
        while (current->next && current->next->distance <= distance) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
        if (!new_node->next) {
            tail = new_node;
        }
    }
}

int pop(queue*& head, queue*& tail) {
    if (!head) return -1;

    queue* temp = head;
    int vertex = head->vertex;
    head = head->next;
    if (!head) tail = NULL;
    delete temp;
    return vertex;
}
//ввод графа
vector<vector<pair<int, int>>> createlist() {
    int n, m;

    cout << "Введите количество вершин (N): ";
    cin >> n;
    cout << "Введите количество ребер (M): ";
    cin >> m;

    vector<vector<pair<int, int>>> graph(n);

    cout << "Введите " << m << " ребер в формате x y w (w - вес ребра):" << endl;
    for (int i = 0; i < m; ++i) {
        int x, y, w;
        cin >> x >> y >> w;

        if (x >= n || y >= n) {
            cout << "Ошибка: вершины " << x << " или " << y << " вне диапазона" << endl;
            continue;
        }

        graph[x].push_back(make_pair(y, w));
        graph[y].push_back(make_pair(x, w));
    }

    for (int i = 0; i < n; ++i) {
        sort(graph[i].begin(), graph[i].end());
        graph[i].erase(unique(graph[i].begin(), graph[i].end()), graph[i].end());
    }

    return graph;
}
//вывод путей
void printpaths(vector<int>& dist, vector<int>& prev, int start) {
    cout << "кратчайшие расстояния от вершины " << start << ":\n";
    for (int i = 0; i < dist.size(); ++i) {
        cout << "до вершины " << i << ": ";
        if (dist[i] == INF) {
            cout << "нет пути\n";
            continue;
        }
        cout << "расстояние = " << dist[i] << ", путь: ";

        vector<int> path;
        int current = i;
        while (current != -1) {
            path.push_back(current);
            current = prev[current];
        }
        reverse(path.begin(), path.end());

        for (size_t j = 0; j < path.size(); ++j) {
            if (j > 0) cout << " -> ";
            cout << path[j];
        }
        cout << endl;
    }
}
//алгоритм дейкстры
void deykstr(vector<vector<pair<int, int>>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INF);
    vector<int> prev(n, -1);
    vector<bool> visited(n, false);

    dist[start] = 0;

    queue* head = NULL;
    queue* tail = NULL;
    push(head, tail, start, 0);

    while (head) {
        int u = pop(head, tail);
        if (visited[u]) continue;
        visited[u] = true;

        for (size_t i = 0; i < graph[u].size(); ++i) {
            int neighbor_vertex = graph[u][i].first;
            int edge_weight = graph[u][i].second;

            if (dist[u] != INF && dist[neighbor_vertex] > dist[u] + edge_weight) {
                dist[neighbor_vertex] = dist[u] + edge_weight;
                prev[neighbor_vertex] = u;
                push(head, tail, neighbor_vertex, dist[neighbor_vertex]);
            }
        }
    }

    printpaths(dist, prev, start);
}

int main() {
    setlocale(LC_ALL, "RUS");
    vector<vector<pair<int, int>>> graph = createlist();
    int start;
    cout << "введите начальную вершину: ";
    cin >> start;

    if (start >= graph.size()) {
        cout << "ошибка: начальная вершина вне диапазона\n";
        return 1;
    }
    deykstr(graph, start);
    return 0;
}
