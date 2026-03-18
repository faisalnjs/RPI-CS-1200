// MyQueue.cpp
#include <iostream>
#include <stack>
#include <cassert>

template <class T>
class MyQueue {
private:
    std::stack<T> s_in;  // For pushing
    std::stack<T> s_out; // For popping/front

public:
    // complete the member functions here: push, pop, front, empty, size. Add helper functions if needed.
    void push(const T& value) {
        s_in.push(value);
    };
    T pop() {
        if (s_out.empty()) { // Move everything from s_in to s_out
            while (!s_in.empty()) {
                s_out.push(s_in.top());
                s_in.pop();
            };
        };
        T popping = front();
        if (!s_out.empty()) s_out.pop(); // Regular pop
        return popping;
    };
    T front() {
        if (s_out.empty()) { // Move everything from s_in to s_out
            while (!s_in.empty()) {
                s_out.push(s_in.top());
                s_in.pop();
            };
        };
        if (!s_out.empty()) return s_out.top(); // Regular front
        throw std::runtime_error("Empty queue");
    };
    // bool empty() {
    //     return s_out.empty();
    // };
    size_t size() {
        return s_out.size();
    };
};

int main() {
    MyQueue<int> q;

    std::cout << "--- Testing MyQueue (FIFO via Stacks) ---" << std::endl;

    q.push(1);
    q.push(2);
    q.push(3);

    std::cout << "Front: " << q.front() << " (Expected 1)" << std::endl;
    assert(q.front() == 1);

    std::cout << "Popping: " << q.pop() << " (Expected 1)" << std::endl;

    q.push(4); // Testing push after some pops

    std::cout << "Front: " << q.front() << " (Expected 2)" << std::endl;
    assert(q.front() == 2);

    q.pop(); // Pop 2
    q.pop(); // Pop 3

    std::cout << "Front after more pops: " << q.front() << " (Expected 4)" << std::endl;
    assert(q.front() == 4);

    assert(q.size() == 1);
    std::cout << "\nAll tests passed successfully!" << std::endl;

    return 0;
}