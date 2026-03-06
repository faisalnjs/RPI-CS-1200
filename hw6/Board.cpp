#include "Board.h"

#include <string>

Board::Board(int boardWidth, int boardHeight) {       // Create a board with given width and height
  for (int i = 0; i < boardHeight; ++i) {             // For every row...
    std::string row;                                  // Initialize the row string
    for (int j = 0; j < boardWidth; ++j) row += ' ';  // For every column, add a placeholder space
    data.push_back(row);                              // Append the row
  }
}