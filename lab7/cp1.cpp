#include <iostream>

class Point {
 public:
  unsigned int x;
  unsigned int y;
  Point(unsigned int startingX, unsigned int startingY) {
    x = startingX;
    y = startingY;
  };
};

// Time complexity O(2^(x+y))
int countPaths(Point currentPoint) {
  if ((currentPoint.x == 0) && (currentPoint.y == 0)) return 1;
  unsigned int totalPaths = 0;
  if (currentPoint.x > 0) totalPaths += countPaths(Point(currentPoint.x - 1, currentPoint.y));
  if (currentPoint.y > 0) totalPaths += countPaths(Point(currentPoint.x, currentPoint.y - 1));
  //   std::cout << totalPaths << std::endl;
  return totalPaths;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " x y" << std::endl;
    return 1;
  }
  Point inputPoint(std::stoi(argv[1]), std::stoi(argv[2]));
  std::cout << "(" << inputPoint.x << ", " << inputPoint.y << ")" << std::endl;
  std::cout << countPaths(inputPoint) << std::endl;
  return 0;
}