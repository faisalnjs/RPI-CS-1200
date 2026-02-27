#include <fstream>
#include <iostream>
#include <string>

#include "User.h"
#include "Users.h"

int main(int argc, char* argv[]) {
  if (argc < 5) {
    std::cout << "Usage: ./nydate.out input.txt output.txt phoneNumber action phoneNumber2?" << std::endl;  // Read inputs
    exit(1);
  }

  std::string action = std::string(argv[4]);  // Get the input action
  if (((action == "unmatch") || (action == "block")) && (argc < 6)) {
    std::cout << "Usage: ./nydate.out input.txt output.txt phoneNumber action phoneNumber2?" << std::endl;  // Read inputs
    exit(1);
  }

  // Users file
  std::string usersFileName = std::string(argv[1]);
  std::ifstream usersFile(usersFileName);  // READ users file
  if (!usersFile.is_open()) {
    std::cerr << "Failed to open the users file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  // Output file
  std::string outputFileName = std::string(argv[2]);
  std::ofstream outputFile(outputFileName);  // Ready the WRITE output file
  if (!outputFile.is_open()) {
    std::cerr << "Failed to open the output file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  outputFile.close();  // Done with output file

  std::string phoneNumber2;                          // Initialize phoneNumber2
  if (argv[5]) phoneNumber2 = std::string(argv[5]);  // Get the input phoneNumber2
  std::string phoneNumber = std::string(argv[3]);    // Get the input phoneNumber

  User* users = registerUsers(usersFileName);  // Create a users list from a users file
  updateUsers(users, phoneNumber);  // Modify users with the current user's information

  usersFile.close();  // Done with users file

  //   std::cout << "Debug: Phone Number - " << phoneNumber << std::endl;     // Debug - check phone number
  //   std::cout << "Debug: Action - " << action << std::endl;                // Debug - check action
  //   std::cout << "Debug: Phone Number 2 - " << phoneNumber2 << std::endl;  // Debug - check phone number 2

  if (action == "profile") {
    outputProfiles(users, outputFileName, phoneNumber);  // Show Profiles
  } else if (action == "match") {
    outputMatches(users, outputFileName, phoneNumber);  // Show Matches
  } else if (action == "like") {
    outputLikes(users, outputFileName, phoneNumber);  // Show All Users Who Swiped Right on This User
  } else if (action == "unmatch") {
    users = sortByPhone(users);                                       // Sort users by phone number
    outputUnmatch(users, outputFileName, phoneNumber, phoneNumber2);  // Unmatch Someone
  } else if (action == "block") {
    outputBlock(users, outputFileName, phoneNumber, phoneNumber2);  // Block Someone
  } else {
    std::cerr << "Invalid action." << std::endl;  // Invalid action
  }

  deconstructUsers(users);  // Deconstruct the users list

  return 0;
}