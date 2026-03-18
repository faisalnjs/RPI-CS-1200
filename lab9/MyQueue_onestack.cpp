// MyQueue_onestack.cpp
#include <iostream>
#include <stack>
#include <cassert>

template <class T>
class MyQueueRecursive {
private:
    std::stack<T> s;

public:
    // complete the member functions here: push, pop, front, empty, size. Add helper functions if needed.
    void push(const T& value) {
        s.push(value);
    };
    T pop() {
        if (s.empty()) throw std::runtime_error("Empty queue");
        T firstValue = s.top();
        s.pop();
        if (s.empty()) return firstValue;
        T nextValue = pop();
        s.push(firstValue);
        return nextValue;
    };
    T front() {
        if (s.empty()) throw std::runtime_error("Empty queue");
        T firstValue = s.top();
        s.pop();
        if (s.empty()) {
            s.push(firstValue);
            return firstValue;
        };
        T nextValue = front();
        s.push(firstValue);
        return nextValue;
    };
    bool empty() const {
        return s.empty();
    };
    size_t size() const {
        return s.size();
    };
};

int main() {
    MyQueueRecursive<int> q;

    q.push(10);
    q.push(20);
    q.push(30);

    std::cout << "Front (Recursive): " << q.front() << " (Expected 10)" << std::endl;
    assert(q.pop() == 10);

    q.push(40);

    std::cout << "Next Pop: " << q.pop() << " (Expected 20)" << std::endl;
    assert(q.size() == 2);

    std::cout << "Recursive Queue logic works!" << std::endl;
    return 0;
}