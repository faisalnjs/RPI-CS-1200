#include <iostream>
#include <unordered_set>

bool isGood(int n) {
  std::unordered_set<int> digits;                         // Initialize digits
  while ((n != 1) && (digits.find(n) == digits.end())) {  // While n is not 1 and n is not in digits...
    digits.insert(n);                                     // Add n to digits
    int sumOfSquares = 0;                                 // Initialize sumOfSquares
    while (n > 0) {                                       // While n is greater than 0...
      int digit = n % 10;                                 // Get the last digit of n
      sumOfSquares += digit * digit;                      // Add the square of the digit to sumOfSquares
      n /= 10;                                            // Remove the last digit from n
    };
    n = sumOfSquares;  // Set n to sumOfSquares
  };
  return n == 1;  // Return true if n is 1, false otherwise
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