//Дан неориентированный граф. 
//Вывести количество вершин, смежных с данной.
#include <iostream>
#include <vector>
#include <algorithm> //для sort и unique

using namespace std;

vector<vector<int>> createlist() {
    int n, m;
    bool isori;//флаг для проверки на ориентированный граф

    cout << "введите количество вершин (N): ";
    cin >> n;
    cout << "введите количество ребер (M): ";
    cin >> m;
    cout << "граф ориентированный? 1 - да, 0 - нет: ";
    cin >> isori;

    vector<vector<int>> Gr;
    Gr.resize(n); // Выделяем память под N строк

    cout << "введите " << m << " ребер в формате x y:" << endl;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;

        if (isori) {
            if (x > n || y > n) {
                cout << "error" << x << " " << y << endl;
                continue;
            }
            Gr[x].push_back(y);
        }
        else {
            if (x > n || y > n) {
                cout << "error" << x << " " << y << endl;
                continue;
            }
            Gr[x].push_back(y);
            Gr[y].push_back(x);
        }
    }

    // Сортировка и удаление дубликатов
    for (int i = 0; i < n; ++i) {
        sort(Gr[i].begin(), Gr[i].end());
        Gr[i].erase(unique(Gr[i].begin(), Gr[i].end()), Gr[i].end());
    }

    return Gr;
}


void printlist(const vector<vector<int>>& Gr) {
    cout << endl << "cписок смежности:" << endl;
    for (int i = 0; i < Gr.size(); ++i) {
        cout << i << ": ";
        for (int vertex : Gr[i]) {
            cout << vertex << " ";
        }
        cout << endl;
    }
}


int main() {
    int k;
    setlocale(LC_ALL, "RUS");
    vector<vector<int>> orig = createlist();
    printlist(orig);
    cout << "введите вершину: ";
    cin >> k;
    cout <<endl<< orig[k].size() << endl;
    return 0;
}
