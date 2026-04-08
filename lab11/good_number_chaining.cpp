#include <iostream>
#include <unordered_map>
#include <vector>

bool isGood(int n) {
  struct Number {
    int value;
    Number* next;
    Number(int val) : value(val), next(nullptr) {}
  };
  std::vector<Number*> numbers(10, nullptr);
  while (n != 1) {  // While n is not 1...
    // Check if n is already in the list, because then will never reach 0 (infinite loop)
    bool foundNumber = false;
    for (Number* currentNumber : numbers) {
      while (currentNumber != nullptr) {
        if (currentNumber->value == n) {
          foundNumber = true;
          break;
        };
        currentNumber = currentNumber->next;
      };
      if (foundNumber) return false;  // Will never reach 1, so return false
    };
    if (foundNumber) return false;  // Will never reach 1, so return false

    // hash function

    int index = n % 10;
    if (numbers[index] == nullptr) {
      numbers[index] = new Number(n);  // Add as new
    } else {
      Number* currentNumber = numbers[index];
      while (currentNumber->next != nullptr) currentNumber = currentNumber->next;
      currentNumber->next = new Number(n);  // Add to next of existing
    }
    int sumOfSquares = 0;             // Initialize sumOfSquares
    while (n > 0) {                   // While n is greater than 0...
      int digit = n % 10;             // Get the last digit of n
      sumOfSquares += digit * digit;  // Add the square of the digit to sumOfSquares
      n /= 10;                        // Remove the last digit from n
    }
    n = sumOfSquares;  // Set n to sumOfSquares
  }
  return true;  // Return true if n is 1, false otherwise
}

int main() {
    // Test cases
    // 2, 4, 5, 6, 17, 18, 20 are not good numbers.
    // 1, 7, 10, 13, 19, 23, 28, 68 are good numbers.

    int testCases[] = {2,4,5,6,17,18,20,1,7,10,13,19,23,28,68};

    for (int n : testCases) {
        if (isGood(n)) {
            std::cout << n << " is a good number." << std::endl;
        } else {
            std::cout << n << " is not a good number." << std::endl;
        }
    }

    return 0;
}