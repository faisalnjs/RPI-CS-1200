#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// BAD: returns pointer to local vector (dangling)
std::vector<int>* get_local_vector(int n) {
    std::vector<int> v;
    int* p;
    for (int i = 0; i < n; ++i) {
        p = &v[0];
        v.push_back(rand() % 10); // random element
    }
    return &v;  // dangling pointer
}

// GOOD: returns pointer to heap-allocated vector
std::vector<int>* get_heap_vector(int n) {
    std::vector<int>* p = new std::vector<int>;
    for (int i = 0; i < n; ++i)
        p->push_back(rand() % 10); // random element
    return p;  // safe pointer
}

// This program demonstrates two concepts 
// which are frequently mentioned in memory security: 
// dangling pointer and use-after-free.
// A dangling pointer is a pointer that still stores the memory address
// of an object or variable that has already been deallocated (deleted) or has gone out of scope.
// Use-after-free is the action of accessing/modifying memory via a dangling pointer.
int main() {
    std::srand(std::time(nullptr)); // seed random numbers

    int local_size  = 4 + rand() % 6;   // 4–9 elements
    int heap_size   = 4 + rand() % 6;   // 4–9 elements

    std::vector<int>* vec_ptr_local;  // dangling pointer
    std::vector<int>* vec_ptr_heap;   // safe heap pointer

    // Dangling pointer from local vector
    vec_ptr_local = get_local_vector(local_size);

    // Safe pointer from heap-allocated vector
    vec_ptr_heap  = get_heap_vector(heap_size);

    // Print local vector pointer
    std::cout << "Dangling local vector pointer:\n";
    for (int i = 0; i < local_size; ++i) {
        std::cout << "element " << i << " = " << (*vec_ptr_local)[i] << "\n";
    }

    // Print heap vector pointer
    std::cout << "\nHeap vector pointer:\n";
    for (int i = 0; i < heap_size; ++i) {
        std::cout << "element " << i << " = " << (*vec_ptr_heap)[i] << "\n";
    }

    // Free heap memory
    delete vec_ptr_heap;
    std::cout << "\nHeap vector pointer after delete (undefined behavior!): ";
    std::cout << (*vec_ptr_heap)[0] << "\n";

    return 0;
}