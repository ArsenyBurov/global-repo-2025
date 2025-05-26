//Реализовать игру Ханойские башни.
//высота башни равна 5
#include <iostream>
#include <vector>
#include <windows.h> //для system("cls")
using namespace std;

//отображение башен в консоли
void display_towers(vector<int>& t1, vector<int>& t2, vector<int>& t3) {
    system("cls"); //очищаем консоль
    cout << "Ханойские башни (Управление: 1-6 для ходов, 0 - выход)\n";
    cout << "1: 1->2  2: 1->3  3: 2->1\n";
    cout << "4: 2->3  5: 3->1  6: 3->2\n\n";

    //находим максимальную высоту из башен для вывода
    int max_height = max(max(t1.size(), t2.size()), t3.size());

    //вывод башен
    for (int i = max_height - 1; i >= 0; i--) {
        cout << " ";
        if (i < t1.size()) cout << t1[i]; else cout << "|";
        cout << "  ";
        if (i < t2.size()) cout << t2[i]; else cout << "|";
        cout << "  ";
        if (i < t3.size()) cout << t3[i]; else cout << "|";
        cout << endl;
    }

    cout << "-------------------\n";
    cout << " 1  2  3 \n\n";
}

//проверка возможности перемещения
bool move_check(vector<int>& from, vector<int>& to) {
    return !from.empty() && (to.empty() || from.back() < to.back());
}

//перемещение кольца
void move_ring(vector<int>& from, vector<int>& to) {
    if (move_check(from, to)) {
        to.push_back(from.back());
        from.pop_back();
    }
}

//проверка победы (все 5 колец на 3й башне)
bool win_check(vector<int>& t3) {
    return t3.size() == 5;
}

int main() {
    setlocale(LC_ALL, "RUS");
    vector<int> tower1 = { 5, 4, 3, 2, 1 };
    vector<int> tower2;
    vector<int> tower3;

    while (true) {
        display_towers(tower1, tower2, tower3);
        if (win_check(tower3)) {
            cout << "Вы победили!\n";
            break;
        }
        cout << "введите ход (1-6, 0 - выход): ";
        int c;
        cin >> c;
        switch (c) {
        case 1: move_ring(tower1, tower2); break;//ввод хода
        case 2: move_ring(tower1, tower3); break;
        case 3: move_ring(tower2, tower1); break;
        case 4: move_ring(tower2, tower3); break;
        case 5: move_ring(tower3, tower1); break;
        case 6: move_ring(tower3, tower2); break;
        case 0: cout << "игра завершена.\n"; return 0;
        }
    }

    return 0;
}
