//Дан набор точек. Построить выпуклую оболочку, которая содержит все данные точки 
//(вывести  все точки многоугольника подряд против часовой стрелки).
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct point {//создание точки по координатам
    int x, y;

    point(int initial_x = 0, int initial_y = 0) {
        x = initial_x;
        y = initial_y;
    }
};

struct stack {
    point point;
    stack* next;
};

void push(stack*& head, point p) {//добавление в стек
    stack* new_node = new stack;
    new_node->point = p;
    new_node->next = head;
    head = new_node;
}

point pop(stack*& head) {//удаление из стека
    if (head == nullptr) {
        cout << "извлечение из пустого стека" << endl;
        return point();
    }
    point result = head->point;
    stack* temp = head;
    head = head->next;
    delete temp;
    return result;
}

point top(stack* head) {//получаем верхний элемент
    if (head == nullptr) {
        cout << "пустой стек" << endl;
        return point();
    }
    return head->point;
}

point next_to_top(stack* head) {//получаем следующий за верхним элемент
    if (head == nullptr || head->next == nullptr) {
        cout << "недостаточно элементов в стеке!" << endl;
        return point();
    }
    return head->next->point;
}

bool isEmpty(stack* head) {
    return head == nullptr;
}
//определяем ориентацию тройки точек
int orientation(point p, point q, point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) {
        return 0;//точки лежат на одной прямой
    }
    else if (val > 0) {
        return 1;//поворот по часовой стрелке
    }
    else {
        return 2;//поворот против часовой стрелки
    }
}


vector<point> convex_hull(vector<point> points) {//построение выпуклой оболочки
    int n = points.size();
    if (n < 3) return {};
    //ищем стартовую точку с наименьшй координатой по Y
    int min_idx = 0;
    for (int i = 1; i < n; i++) {
        if ((points[i].y < points[min_idx].y) ||
            (points[i].y == points[min_idx].y && points[i].x < points[min_idx].x)) {
            min_idx = i;
        }
    }
    swap(points[0], points[min_idx]);
    point p0 = points[0];
    //сортировка точек
    sort(points.begin() + 1, points.end(), [p0](point& a, point& b) {
        int o = orientation(p0, a, b);
        if (o == 0) {
            int dist1 = (p0.x - a.x) * (p0.x - a.x) + (p0.y - a.y) * (p0.y - a.y);
            int dist2 = (p0.x - b.x) * (p0.x - b.x) + (p0.y - b.y) * (p0.y - b.y);
            return dist1 > dist2;
        }
        return (o == 2);
        });

    //удаляем коллинеарные точки
    int m = 1;
    for (int i = 1; i < n; i++) {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;
        points[m++] = points[i];
    }

    if (m < 3) return {};

    stack* hull_stack = nullptr;
    push(hull_stack, points[0]);
    push(hull_stack, points[1]);

    for (int i = 2; i < m; i++) {
        while (hull_stack->next != nullptr &&
            orientation(next_to_top(hull_stack), top(hull_stack), points[i]) != 2) {
            pop(hull_stack);
        }
        push(hull_stack, points[i]);
    }

    vector<point> hull;
    while (!isEmpty(hull_stack)) {
        hull.push_back(pop(hull_stack));
    }
    reverse(hull.begin(), hull.end());
    return hull;
}

int main() {
    setlocale(LC_ALL, "RUS");
    vector<point> points;
    int n, x, y;

    cout << "количество точек: ";
    cin >> n;

    cout << "введите координаты точек (x y):" << endl;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        points.push_back(point(x, y));
    }

    vector<point> hull = convex_hull(points);
    cout << "точки выпуклой оболочки в порядке против часовой стрелки:" << endl;
    for (size_t i = 0; i < hull.size(); i++) {
        point current_point = hull[i];
        cout << "точка " << (i + 1) << ": (" << current_point.x;
        cout << ", " << current_point.y << ")" << endl;
    }

    return 0;
}
