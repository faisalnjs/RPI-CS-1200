#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Board.h"
#include "Letter.h"

// Initialize global variables
std::string puzzleFileName;              // Initialize puzzleFileName
std::string outputFileName;              // Initialize outputFileName
std::string numberOfSolutions;           // Initialize numberOfSolutions
int boardWidth = 0;                      // Initialize boardWidth
int boardHeight = 0;                     // Initialize boardHeight
std::vector<std::string> wantedWords;    // Initialize wantedWords
std::vector<std::string> unwantedWords;  // Initialize unwantedWords
std::vector<Board> solutionsFound;       // Initialize solutionsFound

// Every possible direction combination
int directionsHorizontal[8] = {1, 1, 0, -1, -1, -1, 0, 1};  // Initialize the possible horizontal directions
int directionsVertical[8] = {0, 1, 1, 1, 0, -1, -1, -1};    // Initialize the possible vertical directions

bool hasUnwantedWords(std::vector<std::string> boardData) {                                     // Check if the boardData contains any unwanted words
  int height = (int)boardData.size();                                                           // Get the height of the boardData, convert from size_t to int
  int width = (int)boardData[0].size();                                                         // Get the width of the boardData, convert from size_t to int
  for (std::string word : unwantedWords) {                                                      // For every unwanted word...
    for (int row = 0; row < height; ++row) {                                                    // For every row...
      for (int column = 0; column < width; ++column) {                                          // For every column...
        for (int directionCombination = 0; directionCombination < 8; ++directionCombination) {  // For every possible direction combination...
          int directionRow = directionsVertical[directionCombination];                          // Get the vertical direction for this direction
          int directionColumn = directionsHorizontal[directionCombination];                     // Get the horizontal direction for this direction
          bool hasUnwanted = true;                                                              // Initialize hasUnwanted
          for (int wordLetter = 0; wordLetter < (int)word.size(); ++wordLetter) {               // For every letter in the unwanted word...
            int currentRow = row + (directionRow * wordLetter);                                 // Initialize currentRow
            int currentColumn = column + (directionColumn * wordLetter);                        // Initialize currentColumn
            if ((currentRow < 0) || (currentRow >= height) || (currentColumn < 0) || (currentColumn >= width) || (boardData[currentRow][currentColumn] != word[wordLetter])) {
              hasUnwanted = false;  // Does not match an unwanted word
              break;
            }
          }
          if (hasUnwanted) return true;  // An unwanted word was not not found
        }
      }
    }
  }
  return false;  // An unwanted word was not found
}

void verifyBoard(std::vector<std::string> boardData, int startingRow, int startingColumn) {  // Add board to solutions
  int currentLetter = (startingRow * boardWidth) + startingColumn;                           // Initialize currentLetter
  int area = boardWidth * boardHeight;                                                       // Area of the board
  while (currentLetter < area) {                                                             // While the current letter is in the board...
    int currentRow = currentLetter / boardWidth;                                             // Initialize currentRow
    int currentColumn = currentLetter % boardWidth;                                          // Initialize currentColumn
    if (boardData[currentRow][currentColumn] == ' ') break;                                  // Unfilled board
    ++currentLetter;
  }
  if (currentLetter == area) {                   // Last letter in the board
    bool duplicateFound = false;                 // Initialize duplicateFound
    for (const Board& board : solutionsFound) {  // For every solution...
      if (board.data == boardData) {
        duplicateFound = true;  // Board is already a solution
        break;
      }
    }
    if (!duplicateFound) {                      // New good board
      Board newBoard(boardWidth, boardHeight);  // Initialize newBoard
      newBoard.data = boardData;                // Set the data of newBoard
      solutionsFound.push_back(newBoard);       // Add good board to solutions
    }
    return;
  }
  int currentRow = currentLetter / boardWidth;                                            // Initialize currentRow
  int currentColumn = currentLetter % boardWidth;                                         // Initialize currentColumn
  for (char currentLetter = 'a'; currentLetter <= 'z'; ++currentLetter) {                 // For every letter...
    boardData[currentRow][currentColumn] = currentLetter;                                 // Set the current letter
    if (!hasUnwantedWords(boardData)) verifyBoard(boardData, currentRow, currentColumn);  // Verify board with the current letter
    if ((numberOfSolutions == "one_solution") && !solutionsFound.empty()) return;         // Return only one solution
  }
}

void generateBoard(std::vector<std::string>& boardData, int currentWord) {         // Generate a board with the current word
  if ((currentWord == (int)wantedWords.size()) && !hasUnwantedWords(boardData)) {  // Last word and no unwanted words
    verifyBoard(boardData, 0, 0);                                                  // Verify board
    return;
  }
  std::string word = wantedWords[currentWord];                                                // Get the current word
  for (int row = 0; row < boardHeight; ++row) {                                               // For every row...
    for (int column = 0; column < boardWidth; ++column) {                                     // For every column...
      for (int directionCombination = 0; directionCombination < 8; ++directionCombination) {  // For every possible direction combination...
        int directionRow = directionsVertical[directionCombination];                          // Get the vertical direction for this direction
        int directionColumn = directionsHorizontal[directionCombination];                     // Get the horizontal direction for this direction
        bool hasWanted = true;                                                                // Initialize hasWanted
        int height = (int)boardData.size();                                                   // Get the height of the boardData, convert from size_t to int
        int width = (int)boardData[0].size();                                                 // Get the width of the boardData, convert from size_t to int
        for (int wordLetter = 0; wordLetter < (int)word.size(); ++wordLetter) {               // For every letter in the wanted word...
          int currentRow = row + (directionRow * wordLetter);                                 // Initialize currentRow
          int currentColumn = column + (directionColumn * wordLetter);                        // Initialize currentColumn
          if ((currentRow < 0) || (currentRow >= height) || (currentColumn < 0) || (currentColumn >= width) || ((boardData[currentRow][currentColumn] != ' ') && (boardData[currentRow][currentColumn] != word[wordLetter]))) {
            hasWanted = false;  // Does not match a wanted word
            break;
          }
        }
        if (!hasWanted) continue;                                                // Does not match a wanted word
        std::vector<Letter> newLetters;                                          // Initialize newLetters
        for (int wordLetter = 0; wordLetter < (int)word.size(); ++wordLetter) {  // For every letter in the wanted word...
          int currentRow = row + (directionRow * wordLetter);                    // Initialize currentRow
          int currentColumn = column + (directionColumn * wordLetter);           // Initialize currentColumn
          if (boardData[currentRow][currentColumn] == ' ') {                     // Unfilled board
            boardData[currentRow][currentColumn] = word[wordLetter];             // Set to the current letter
            Letter newLetter;                                                    // Initialize newLetter
            newLetter.row = currentRow;                                          // Set the row of newLetter
            newLetter.column = currentColumn;                                    // Set the column of newLetter
            newLetters.push_back(newLetter);                                     // Add to newLetters
          }
        }
        if (!hasUnwantedWords(boardData)) {                                              // No unwanted words
          generateBoard(boardData, currentWord + 1);                                     // Add the next word to the board
          if ((numberOfSolutions == "one_solution") && !solutionsFound.empty()) return;  // Return only one solution
        }
        for (const Letter& newLetter : newLetters) boardData[newLetter.row][newLetter.column] = ' ';  // Reset the new letters
      }
    }
  }
}

void findAllSolutions() {                    // Find all solutions to the puzzle
  std::ifstream puzzleFile(puzzleFileName);  // READ puzzle file
  if (!puzzleFile.is_open()) {
    std::cerr << "Failed to open the puzzle file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }
  std::string line;
  bool firstLine = true;                                         // Initialize firstLine
  while (getline(puzzleFile, line)) {                            // For every line in the puzzle file...
    if (line.empty()) continue;                                  // Empty line
    if (firstLine) {                                             // First line
      boardWidth = std::stoi(line.substr(0, line.find(' ')));    // Get the board width
      boardHeight = std::stoi(line.substr(line.find(' ') + 1));  // Get the board height
      firstLine = false;
    } else {
      std::string firstCharacter = line.substr(0, line.find(' '));  // Get the first character
      line.erase(0, line.find(" ") + 1);                            // Clean data
      std::string word = line.substr(0, line.find(' '));            // Get the word
      if (firstCharacter == "+") {
        wantedWords.push_back(word);  // Wanted word
      } else if (firstCharacter == "-") {
        unwantedWords.push_back(word);  // Unwanted word
      }
    }
  }
  puzzleFile.close();                                                                                                                                             // Done with the puzzle file
  for (int wantedWord = 1; wantedWord < (int)wantedWords.size(); ++wantedWord) {                                                                                  // For every wanted word...
    std::string currentWord = wantedWords[wantedWord];                                                                                                            // Initialize currentWord
    int previousWantedWordPosition = wantedWord - 1;                                                                                                              // Initialize position
    while (previousWantedWordPosition >= 0) {                                                                                                                     // While the position is valid...
      std::string previousWantedWord = wantedWords[previousWantedWordPosition];                                                                                   // Initialize previousWantedWord
      if ((previousWantedWord.size() >= currentWord.size()) && ((previousWantedWord.size() != currentWord.size()) || (previousWantedWord > currentWord))) break;  // Previous wanted word is not smaller
      wantedWords[previousWantedWordPosition + 1] = previousWantedWord;                                                                                           // Previous wanted word is smaller
      --previousWantedWordPosition;                                                                                                                               // Update position
    }
    wantedWords[previousWantedWordPosition + 1] = currentWord;  // Move the current wanted word
  }
  std::vector<std::string> boardData(boardHeight, std::string(boardWidth, ' '));  // Initialize boardData
  generateBoard(boardData, 0);                                                    // Generate a board with the first word
}

void outputSolutions() {                     // Output the solutions to the puzzle
  std::ofstream outputFile(outputFileName);  // Ready the WRITE output file
  if (!outputFile.is_open()) {
    std::cerr << "Failed to open the output file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }
  if (solutionsFound.empty()) {
    outputFile << "No solutions found" << std::endl;  // No solutions found
  } else {
    if (numberOfSolutions == "one_solution") {                                                           // One solution
      Board board = solutionsFound[0];                                                                   // Get the first solution
      outputFile << "Board: " << std::endl;                                                              // Output the board
      for (int row = 0; row < boardHeight; ++row) outputFile << "  " << board.data[row] << std::endl;    // For every row, output the row
    } else {                                                                                             // All solutions
      outputFile << solutionsFound.size() << " solution(s)" << std::endl;                                // Output the number of solutions
      for (size_t solution = 0; solution < solutionsFound.size(); ++solution) {                          // For every solution...
        outputFile << "Board: " << std::endl;                                                            // Output the board
        Board board = solutionsFound[solution];                                                          // Get the solution
        for (int row = 0; row < boardHeight; ++row) outputFile << "  " << board.data[row] << std::endl;  // For every row, output the row
      }
    }
  }
  outputFile.close();  // Done with the output file
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cout << "Usage: ./inverse_word_search.out puzzle3.txt out3.txt one_solution|all_solutions" << std::endl;  // Read inputs
    exit(1);
  }
  puzzleFileName = std::string(argv[1]);     // Get the input puzzle file name
  outputFileName = std::string(argv[2]);     // Get the input output file name
  numberOfSolutions = std::string(argv[3]);  // Get the input number of solutions
  findAllSolutions();                        // Find all solutions to the puzzle
  outputSolutions();                         // Output the solutions to the puzzle
  return 0;
}