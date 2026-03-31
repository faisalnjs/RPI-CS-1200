#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Comment.h"
#include "Video.h"

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cout << "Usage: ./nycomments.out input.json actions.txt output.txt" << std::endl;  // Read inputs
    exit(1);
  }

  std::string inputFileName = std::string(argv[1]);    // Get the input file name
  std::string actionsFileName = std::string(argv[2]);  // Get the actions file name
  std::string outputFileName = std::string(argv[3]);   // Get the output file name

  std::vector<Comment> allComments;  // Initialize allComments

  Video myVideo(inputFileName, allComments);  // Initialize myVideo

  myVideo.makeTree(allComments);  // Make the tree of comments

  myVideo.processActions(actionsFileName, outputFileName);  // Process the actions

  return 0;
}