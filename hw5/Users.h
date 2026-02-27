#ifndef USERS_H
#define USERS_H
#include <string>

#include "User.h"

User* addUser(User*& users);                                                                                                      // Add a user to the end of the list
void removeUser(User*& users, const std::string& phoneNumber);                                                                    // Remove a user from the list by phoneNumber
User* registerUsers(std::string usersFileName);                                                                                   // Create a users list from a users file
void deconstructUsers(User*& users);                                                                                              // Deconstruct the users list
void updateUsers(User*& users, std::string phoneNumber);                                                                          // Modify users with the current user's information
void outputProfiles(User* users, std::string outputFileName, std::string phoneNumber);                                            // Show Profiles
void outputProfiles(User* users, std::string outputFileName, std::string phoneNumber, std::string hidePhoneNumber, bool header);  // Show Profiles
User* sortByPhone(User* users);                                                                                                   // Sort the users list by phone number
void outputMatches(User* users, std::string outputFileName, std::string phoneNumber);                                             // Show Matches
void outputMatches(User* users, std::string outputFileName, std::string phoneNumber, std::string hidePhoneNumber, bool header);   // Show Matches
void outputLikes(User* users, std::string outputFileName, std::string phoneNumber);                                               // Show All Users Who Swiped Right on This User
void outputUnmatch(User* users, std::string outputFileName, std::string phoneNumber, std::string phoneNumber2);                   // Unmatch Someone
void outputBlock(User* users, std::string outputFileName, std::string phoneNumber, std::string phoneNumber2);                     // Block Someone

#endif
