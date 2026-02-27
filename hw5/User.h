#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <vector>

// Class for the user
class User {
 public:
  bool self = false;                    // Whether the user is self
  std::string name;                     // Name of the user
  int age;                              // Age of the user
  std::string gender;                   // Gender of the user
  std::string phoneNumber;              // Phone number of the user
  int phoneNumberInt;                   // Phone number integer of the user
  std::string profession;               // Profession of the user
  std::string school;                   // School of the user
  double latitude;                      // latitude of the user
  double longitude;                     // Longitude of the user
  bool premium = false;                 // Premium status of the user
  int minAgePreference;                 // Minimum age preference of the user
  int maxAgePreference;                 // Maximum age preference of the user
  double maxDistancePreference;         // Maximum distance preference of the user
  std::string genderPreference;         // Gender preference of the user
  std::vector<std::string> usersLiked;  // Users that the user has liked
  double distance = 0;                  // Distance from the current user
  bool matchedPreferences = false;      // Whether the user's preferences match with the current user's preferences
  bool liked = false;                   // Whether the user has liked the current user
  User* nextUser = nullptr;             // The next user
  User();                               // Create a user
};

#endif
