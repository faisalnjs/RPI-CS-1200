#include <fstream>
#include <iostream>
#include <map>
#include <string>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: ./main.out input.txt" << std::endl;
    return 1;
  }

  std::string inputFileName = argv[1];
  std::ifstream inputFile(inputFileName);
  if (!inputFile.is_open()) {
    std::cerr << "Failed to open the input file." << std::endl;
    return 1;
  }

  std::map<int, int> numbers;
  std::map<int, int> modes;
  std::string line;

  while (std::getline(inputFile, line)) {
    int number = std::stoi(line);
    std::pair<std::map<int, int>::iterator, bool> inserted = numbers.insert(std::make_pair(number, 1));
    if (!inserted.second) {
      inserted.first->second++;
    } else {
      inserted.first->second = 1;
    }
  }

  inputFile.close();

  int numberFrequency = 0;

  for (std::pair<int, int> pair : numbers) {
    if (pair.second > numberFrequency) {
      numberFrequency = pair.second;
      modes.clear();
      modes.insert(std::make_pair(pair.first, 0));
    } else if (pair.second == numberFrequency) {
      modes.insert(std::make_pair(pair.first, 0));
    }
  }

  std::cout << "Mode(s): ";
  for (std::pair<int, int> pair : modes) std::cout << pair.first << " ";
  std::cout << std::endl;

  return 0;
}
