#include <iostream>

int main(int argc, char* argv[]) {
    int product = 1;
    for (int i = 1; i < argc; ++i) {
        product *= std::atoi(argv[i]);
    }
    std::cout << "product of integers: " << product << std::endl;
    return 0;
}