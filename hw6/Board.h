#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>

// Class for the board
class Board {
 public:
  std::vector<std::string> data;           // Data of the board
  Board(int boardWidth, int boardHeight);  // Create a board with given width and height
};

#endif