#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Usage: ./io.out input.json output.txt" << std::endl;
    exit(1);
  }

  std::string inputFileName = std::string(argv[1]);
  std::ifstream inputFile(inputFileName);
  if (!inputFile.is_open()) {
    std::cerr << "Failed to open the input file." << std::endl;
    exit(1);
  }

  std::string outputFileName = std::string(argv[2]);
  std::ofstream outputFile(outputFileName);
  if (!outputFile.is_open()) {
    std::cerr << "Failed to open the output file." << std::endl;
    exit(1);
  }

  std::string line;
  std::string username;

  while (getline(inputFile, line)) {
    username = line.substr(line.find("\"username\": \"") + 13);
    username = username.substr(0, username.find("\","));
    std::cout << username << std::endl;
    outputFile << username << std::endl;
  }

  inputFile.close();
  outputFile.close();
  return 0;
}
