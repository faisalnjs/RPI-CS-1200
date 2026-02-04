#include <iostream>
#include <cstdlib>   // for rand()
#include <ctime>     // for time()

struct Point {
    int x;
    int y;
};

// f3 allocates a new Point on heap
int f3(Point* p) {
    int z = rand() % 100 + 1; // 1..100
    Point* q = new Point{rand() % 50, rand() % 50}; // new dynamic Point
    std::cout << "In f3, z = " << z << ", q->x = " << q->x << ", q->y = " << q->y << "\n";

    p->x += z;   // modify main Point
    int result = z + p->y + q->x; // use heap object

    delete q; // free heap memory
    return result;
}

// f2 allocates an integer array
int f2(Point* p) {
    int y = rand() % 50 + 1; // 1..50
    int* arr = new int[3]{rand() % 10, rand() % 10, rand() % 10}; // dynamic array

    int result = f3(p) + arr[1];
    delete[] arr; // free array
    std::cout << "In f2, sum = " << result + y << "\n";
    return result + y;
}

// f1 allocates another Point on heap
int f1(Point* p) {
    int x = rand() % 20 + 1; // 1..20
    Point* r = new Point{rand() % 5, rand() % 5};

    int total = f2(p) + x + p->x + r->y;
    delete r; // free heap object
    std::cout << "In f1, total = " << total << "\n";
    return total;
}

int main() {
    std::srand(std::time(nullptr));           // seed random generator
    Point* pt = new Point{rand() % 10, rand() % 10}; // randomized Point

    int val = f1(pt) + pt->y;
    std::cout << "In main, val = " << val << "\n";

    delete pt;
    return 0;
}