#include "Users.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "User.h"

std::ofstream outputFile;  // Initialize output file stream

User* addUser(User*& users) {  // Add a user to the end of the list
  User* newUser = new User();  // Initialize newUser
  if (!users) {
    users = newUser;  // First user
    return newUser;
  }
  User* currentUser = users;                                          // Update the list
  while (currentUser->nextUser) currentUser = currentUser->nextUser;  // Update the list
  currentUser->nextUser = newUser;                                    // Update the list
  return newUser;
}

void removeUser(User*& users, const std::string& phoneNumber) {       // Remove a user from the list by phoneNumber
  User* currentUser = users;                                          // Update the list
  User* previousUser = nullptr;                                       // Update the list
  while (currentUser && (currentUser->phoneNumber != phoneNumber)) {  // Update the list
    previousUser = currentUser;                                       // Update the list
    currentUser = currentUser->nextUser;                              // Update the list
  }
  if (!currentUser) return;                          // No current user
  if (previousUser) {                                // There is a previous user
    previousUser->nextUser = currentUser->nextUser;  // Update the list
  } else {
    users = currentUser->nextUser;  // No previous user
  }
  delete currentUser;  // Remove the user
}

User* registerUsers(std::string usersFileName) {  // Create a users list from a users file
  std::ifstream usersFile(usersFileName);         // READ users file
  if (!usersFile.is_open()) {
    std::cerr << "Failed to open the users file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  std::string line;

  User* users = nullptr;  // Initialize the list

  // Users file -> users list
  while (getline(usersFile, line)) {                         // For each line in the users file...
    User* thisUser = addUser(users);                         // Create a user from the line
    thisUser->name = line.substr(0, line.find(" "));         // Set the name of the user
    line.erase(0, line.find(" ") + 1);                       // Clean data
    thisUser->age = stoi(line.substr(0, line.find(" ")));    // Set the age of the user
    line.erase(0, line.find(" ") + 1);                       // Clean data
    thisUser->gender = line.substr(0, line.find(" "));       // Set the gender of the user
    line.erase(0, line.find(" ") + 1);                       // Clean data
    thisUser->phoneNumber = line.substr(0, line.find(" "));  // Set the phone number of the user
    std::istringstream iss(line.substr(0, line.find(" ")));
    std::string phoneNumberInt;
    while (std::getline(iss, phoneNumberInt, '_')) phoneNumberInt += phoneNumberInt;  // Set the phone number string of the user
    thisUser->phoneNumberInt = stod(phoneNumberInt);                                  // Set the phone number integer of the user
    line.erase(0, line.find(" ") + 1);                                                // Clean data
    std::istringstream iss2(line.substr(0, line.find(" ")));
    std::string profession;
    while (std::getline(iss2, profession, '_')) thisUser->profession += profession + " ";  // Set the profession of the user
    thisUser->profession.pop_back();                                                       // Remove the extra space
    line.erase(0, line.find(" ") + 1);                                                     // Clean data
    std::istringstream iss3(line.substr(0, line.find(" ")));
    std::string school;
    while (std::getline(iss3, school, '_')) thisUser->school += school + " ";  // Set the school of the user
    thisUser->school.pop_back();                                               // Remove the extra space
    line.erase(0, line.find(" ") + 1);                                         // Clean data
    thisUser->latitude = stod(line.substr(0, line.find(" ")));                 // Set the latitude of the user
    line.erase(0, line.find(" ") + 1);                                         // Clean data
    thisUser->longitude = stod(line.substr(0, line.find(" ")));                // Set the longitude of the user
    line.erase(0, line.find(" ") + 1);                                         // Clean data
    thisUser->premium = (line.substr(0, line.find(" ")) == "true");            // Set the premium status of the user
    line.erase(0, line.find(" ") + 1);                                         // Clean data
    thisUser->minAgePreference = stoi(line.substr(0, line.find(" ")));         // Set the minimum age preference of the user
    line.erase(0, line.find(" ") + 1);                                         // Clean data
    thisUser->maxAgePreference = stoi(line.substr(0, line.find(" ")));         // Set the maximum age preference of the user
    line.erase(0, line.find(" ") + 1);                                         // Clean data
    thisUser->maxDistancePreference = stod(line.substr(0, line.find(" ")));    // Set the maximum distance preference of the user
    line.erase(0, line.find(" ") + 1);                                         // Clean data
    thisUser->genderPreference = line.substr(0, line.find(" "));               // Set the gender preference of the user
    line.erase(0, line.find(" ") + 1);                                         // Clean data

    // Other Useful Code
    // From https://github.com/jidongxiao/CSCI1200-DataStructures/tree/master/hws/online_dating#other-useful-code
    std::istringstream iss4(line.substr(0, line.find(" ")));
    std::string phoneNumber;
    while (std::getline(iss4, phoneNumber, '_')) thisUser->usersLiked.push_back(phoneNumber);  // Set the users that the user has liked
  }
  return users;
}

void deconstructUsers(User*& users) {  // Deconstruct the users list
  while (users) {                      // While there are users...
    User* currentUser = users;         // Initialize currentUser
    users = users->nextUser;           // Update the list
    delete currentUser;                // Remove the user
  }
}

// Calculate Distance Based on Haversine Formula
// From https://github.com/jidongxiao/CSCI1200-DataStructures/tree/master/hws/online_dating#calculate-distance-based-on-haversine-formula
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
  const double radiusOfEarth = 6371.0;
  lat1 *= M_PI / 180.0;
  lon1 *= M_PI / 180.0;
  lat2 *= M_PI / 180.0;
  lon2 *= M_PI / 180.0;
  double dLat = lat2 - lat1;
  double dLon = lon2 - lon1;
  double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
  double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
  double distanceKM = radiusOfEarth * c;
  double distanceMiles = distanceKM * 0.621371;
  return distanceMiles;
}

void updateUsers(User*& users, std::string phoneNumber) {  // Modify users with the current user's information
  User* currentUser = users;                               // Initialize currentUser
  User* self = nullptr;                                    // Initialize self
  while (currentUser) {                                    // While there are users...
    currentUser->self = false;                             // Clear previous self flag
    if (currentUser->phoneNumber == phoneNumber) {         // If the user is the current user...
      currentUser->self = true;                            // User is self
      self = currentUser;                                  // Set self
    }
    currentUser = currentUser->nextUser;  // Update the list
  }
  if (!self) {
    std::cerr << "Current user not found." << std::endl;  // User does not exist
    return;
  }
  currentUser = users;                                         // Reinitialize currentUser
  int minAgePreference = self->minAgePreference;               // Minimum age preference of the user
  int maxAgePreference = self->maxAgePreference;               // Maximum age preference of the user
  double maxDistancePreference = self->maxDistancePreference;  // Maximum distance preference of the user
  std::string genderPreference = self->genderPreference;       // Gender preference of the user
  while (currentUser) {                                        // While there are users...
    currentUser->matchedPreferences = false;
    currentUser->liked = false;
    if (currentUser->phoneNumber == phoneNumber) {  // Skip the current user
      currentUser = currentUser->nextUser;          // Update the list
      continue;
    }
    currentUser->distance = calculateDistance(currentUser->latitude, currentUser->longitude, self->latitude, self->longitude);  // Set the distance from the current user
    bool matchedByAge = (currentUser->age >= minAgePreference) && (currentUser->age <= maxAgePreference);                       // The user is a match by age
    // std::cout << "Debug: " << currentUser->name << " - Age: " << currentUser->age << ", Min: " << minAgePreference << ", Max: " << maxAgePreference << ", Matched by Age: " << matchedByAge << std::endl;  // Debug - check age match
    bool matchedByDistance = currentUser->distance <= maxDistancePreference;  // The user is a match by distance
    // std::cout << "Debug: " << currentUser->name << " " << currentUser->age << " - Distance: " << currentUser->distance << ", Max: " << maxDistancePreference << ", Matched by Distance: " << (currentUser->distance <= maxDistancePreference) << std::endl;  // Debug - check distance match
    bool matchedByGender = false;  // Initialize matchedByGender
    if (genderPreference == "Male") {
      if (currentUser->gender == "Male") matchedByGender = true;  // The user is a match by gender
    } else if (genderPreference == "Female") {
      if (currentUser->gender == "Female") matchedByGender = true;  // The user is a match by gender
    } else {
      matchedByGender = true;
    }
    // std::cout << "Debug: " << currentUser->name << " " << currentUser->age << " - Gender: " << currentUser->gender << ", Preference: " << genderPreference << ", Matched by Gender: " << matchedByGender << std::endl;  // Debug - check gender match
    if (matchedByAge && matchedByDistance && matchedByGender) currentUser->matchedPreferences = true;  // The user is matched with this user
    // if (matchedByAge && matchedByDistance && matchedByGender) std::cout << currentUser->name << " " << currentUser->age << " is a match!" << std::endl;  // Debug - check matches
    bool hasLikedCurrentUser = false;                                  // Initialize hasLikedCurrentUser
    for (const std::string& likedUser : currentUser->usersLiked) {     // For each user in the current user's usersLiked...
      if (likedUser == self->phoneNumber) hasLikedCurrentUser = true;  // The current user is in the user's usersLiked
    }
    if (hasLikedCurrentUser) currentUser->liked = true;  // The user has liked the current user
    currentUser = currentUser->nextUser;                 // Update the list
  }
}

void outputProfiles(User* users, std::string outputFileName, std::string phoneNumber, std::string hidePhoneNumber, bool heading) {  // Show Profiles
  if (!outputFile.is_open()) outputFile.open(outputFileName);                                                                       // Ready the WRITE output file
  if (!outputFile.is_open()) {
    std::cerr << "Failed to open the output file." << std::endl;  // Error if file cannot be opened
    deconstructUsers(users);                                      // Deconstruct the users list
    exit(1);
  }
  User* currentUser = users;                                          // Initialize currentUser
  User* self = nullptr;                                               // Initialize self
  while (currentUser) {                                               // While there are users...
    if (currentUser->phoneNumber == phoneNumber) self = currentUser;  // Find and set self
    currentUser = currentUser->nextUser;                              // Update the list
  }
  if (!self) {
    std::cerr << "Current user not found." << std::endl;  // User does not exist
    exit(1);
  }
  if (heading) {
    outputFile << "profiles shown to " << self->name << ":" << std::endl;  // Output heading
    outputFile << std::endl;                                               // Output separator
  }
  currentUser = users;                                                                // Reinitialize currentUser
  bool firstProfile = true;                                                           // Initialize firstProfile
  bool noProfiles = true;                                                             // Initialize noProfiles
  while (currentUser) {                                                               // While there are users...
    if (!hidePhoneNumber.empty() && (currentUser->phoneNumber == hidePhoneNumber)) {  // Skip the current user
      currentUser = currentUser->nextUser;                                            // Update the list
      continue;
    }
    if (currentUser->matchedPreferences) {                                                               // If the user is matched with the current user's preferences...
      noProfiles = false;                                                                                // At least one profile
      if ((!firstProfile && !heading) || (!firstProfile && heading)) outputFile << std::endl;            // Output separator
      outputFile << currentUser->name << " " << currentUser->age << std::endl;                           // Output profile name and age
      if (currentUser->profession != "Undisclosed") outputFile << currentUser->profession << std::endl;  // Output profile profession
      if (currentUser->school != "Undisclosed") outputFile << currentUser->school << std::endl;          // Output profile school
      if (firstProfile) firstProfile = false;                                                            // Update firstProfile
    }
    currentUser = currentUser->nextUser;  // Update the list
  }
  if (noProfiles) outputFile << "There are no users matching with your preference at this moment." << std::endl;  // No profiles found
}

void outputProfiles(User* users, std::string outputFileName, std::string phoneNumber) {
  outputProfiles(users, outputFileName, phoneNumber, "", false);
}

User* sortByPhone(User* users) {                 // Sort the users list by phone number
  if (!users || !users->nextUser) return users;  // Empty list or single user
  User* currentUser = users;                     // Initialize currentUser
  User* nextUser = users->nextUser;              // Initialize nextUser
  while (nextUser && nextUser->nextUser) {       // While there are at least two users...
    currentUser = currentUser->nextUser;         // Update currentUser
    nextUser = nextUser->nextUser->nextUser;     // Update nextUser
  }
  User* secondHalf = currentUser->nextUser;    // Initialize secondHalf
  currentUser->nextUser = nullptr;             // Split the list into two halves
  User* firstUser = sortByPhone(users);        // Sort the first half
  User* secondUser = sortByPhone(secondHalf);  // Sort the second half
  User tempUser;                               // Temporary user for merging
  User* sortedUsers = &tempUser;               // Initialize sortedUsers
  while (firstUser && secondUser) {            // While there are users in both halves...
    if (firstUser->phoneNumberInt <= secondUser->phoneNumberInt) {
      sortedUsers->nextUser = firstUser;  // Prioritize first
      firstUser = firstUser->nextUser;    // Update the list
    } else {
      sortedUsers->nextUser = secondUser;  // Prioritize second
      secondUser = secondUser->nextUser;   // Update the list
    }
    sortedUsers = sortedUsers->nextUser;  // Update the list
  }
  sortedUsers->nextUser = firstUser ? firstUser : secondUser;  // Add the remaining users
  return tempUser.nextUser;
}

void outputMatches(User* users, std::string outputFileName, std::string phoneNumber, std::string hidePhoneNumber, bool heading) {  // Show Matches
  if (!outputFile.is_open()) outputFile.open(outputFileName);                                                                      // Ready the WRITE output file
  if (!outputFile.is_open()) {
    std::cerr << "Failed to open the output file." << std::endl;  // Error if file cannot be opened
    deconstructUsers(users);                                      // Deconstruct the users list
    exit(1);
  }
  User* currentUser = users;                                          // Initialize currentUser
  User* self = nullptr;                                               // Initialize self
  while (currentUser) {                                               // While there are users...
    if (currentUser->phoneNumber == phoneNumber) self = currentUser;  // Find and set self
    currentUser = currentUser->nextUser;                              // Update the list
  }
  if (!self) {
    std::cerr << "Current user not found." << std::endl;  // User does not exist
    exit(1);
  }
  if (heading) {
    outputFile << self->name << "'s match list:" << std::endl;  // Output heading
    outputFile << std::endl;                                    // Output separator
  }
  std::vector<User*> userVector;                                                      // Initialize userVector
  for (User* user = users; user; user = user->nextUser) userVector.push_back(user);   // Migrate from list to vector
  std::sort(userVector.begin(), userVector.end(), [](User* userOne, User* userTwo) {  // Sort by phone number
    return userOne->phoneNumberInt < userTwo->phoneNumberInt;
  });
  bool firstMatch = true;                                                             // Initialize firstMatch
  bool noMatches = true;                                                              // Initialize noMatches
  bool isLikedByCurrentUser = false;                                                  // Initialize isLikedByCurrentUser
  bool hasLikedCurrentUser = false;                                                   // Initialize hasLikedCurrentUser
  for (User* currentUser : userVector) {                                              // Iterate sorted users (non-destructive)
    if (!hidePhoneNumber.empty() && (currentUser->phoneNumber == hidePhoneNumber)) {  // Skip the current user
      continue;
    }
    isLikedByCurrentUser = false;                                              // Initialize isLikedByCurrentUser
    hasLikedCurrentUser = false;                                               // Initialize hasLikedCurrentUser
    for (const std::string& likedUser : self->usersLiked) {                    // For each user in self's usersLiked...
      if (likedUser == currentUser->phoneNumber) isLikedByCurrentUser = true;  // The user is in self's usersLiked
    }
    for (const std::string& likedUser : currentUser->usersLiked) {  // For each user in the current user's usersLiked...
      if (likedUser == phoneNumber) hasLikedCurrentUser = true;     // The current user is in the user's usersLiked
    }
    if (isLikedByCurrentUser && hasLikedCurrentUser) {                                                   // If the user is matched with the current user...
      noMatches = false;                                                                                 // At least one match
      if ((!firstMatch && !heading) || (!firstMatch && heading)) outputFile << std::endl;                // Output separator
      outputFile << currentUser->name << " " << currentUser->age << std::endl;                           // Output match name and age
      if (currentUser->profession != "Undisclosed") outputFile << currentUser->profession << std::endl;  // Output match profession
      if (currentUser->school != "Undisclosed") outputFile << currentUser->school << std::endl;          // Output match school
      if (firstMatch) firstMatch = false;                                                                // Update firstMatch
    }
  }
  if (noMatches) outputFile << "You do not have any matches at this moment." << std::endl;  // No matches found
}

void outputMatches(User* users, std::string outputFileName, std::string phoneNumber) {  // Show Matches
  outputMatches(users, outputFileName, phoneNumber, "", false);
}

void outputLikes(User* users, std::string outputFileName, std::string phoneNumber) {  // Show All Users Who Swiped Right on This User
  if (!outputFile.is_open()) outputFile.open(outputFileName);                         // Ready the WRITE output file
  if (!outputFile.is_open()) {
    std::cerr << "Failed to open the output file." << std::endl;  // Error if file cannot be opened
    deconstructUsers(users);                                      // Deconstruct the users list
    exit(1);
  }
  User* currentUser = users;                                          // Initialize currentUser
  User* self = nullptr;                                               // Initialize self
  while (currentUser) {                                               // While there are users...
    if (currentUser->phoneNumber == phoneNumber) self = currentUser;  // Find and set self
    currentUser = currentUser->nextUser;                              // Update the list
  }
  if (!self) {
    std::cerr << "Current user not found." << std::endl;  // User does not exist
    exit(1);
  }
  if (!self->premium) {
    outputFile << "Only premium users can view who liked you." << std::endl;  // Not a premium user
    return;
  }
  currentUser = users;                                                                                   // Reinitialize currentUser
  bool firstLike = true;                                                                                 // Initialize firstLike
  bool noLikes = true;                                                                                   // Initialize noLikes
  while (currentUser) {                                                                                  // While there are users...
    if (currentUser->liked) {                                                                            // If the user has liked the current user...
      noLikes = false;                                                                                   // At least one Like
      if (!firstLike) outputFile << std::endl;                                                           // Output separator
      outputFile << currentUser->name << " " << currentUser->age << std::endl;                           // Output Like name and age
      if (currentUser->profession != "Undisclosed") outputFile << currentUser->profession << std::endl;  // Output Like profession
      if (currentUser->school != "Undisclosed") outputFile << currentUser->school << std::endl;          // Output Like school
      if (firstLike) firstLike = false;                                                                  // Update firstLike
    }
    currentUser = currentUser->nextUser;  // Update the list
  }
  if (noLikes) outputFile << "You have not received any likes so far." << std::endl;  // No likes found
}

void outputUnmatch(User* users, std::string outputFileName, std::string phoneNumber, std::string phoneNumber2) {  // Unmatch Someone
  User* currentUser = users;                                                                                      // Initialize currentUser
  User* self = nullptr;                                                                                           // Initialize self
  while (currentUser) {                                                                                           // While there are users...
    if (currentUser->phoneNumber == phoneNumber) self = currentUser;                                              // Find and set self
    currentUser = currentUser->nextUser;                                                                          // Update the list
  }
  std::vector<std::string> newUsersLiked;                               // Initialize newUsersLiked
  for (const std::string& likedUser : self->usersLiked) {               // For each user in self's usersLiked...
    if (likedUser != phoneNumber2) newUsersLiked.push_back(likedUser);  // If the user is not the other user, add to newUsersLiked
  }
  self->usersLiked = newUsersLiked;                                        // Update self's usersLiked
  newUsersLiked.clear();                                                   // Clear newUsersLiked
  currentUser = users;                                                     // Reinitialize currentUser
  while (currentUser) {                                                    // While there are users...
    if (currentUser->phoneNumber == phoneNumber2) {                        // If the user is the other user...
      for (const std::string& likedUser : currentUser->usersLiked) {       // For each user in the other user's usersLiked...
        if (likedUser != phoneNumber) newUsersLiked.push_back(likedUser);  // If the user is not self, add to newUsersLiked
      }
      currentUser->usersLiked = newUsersLiked;  // Update the other user's usersLiked
      break;
    }
    currentUser = currentUser->nextUser;  // Update the list
  }
  outputMatches(users, outputFileName, phoneNumber, "", true);   // Output matches
  outputFile << std::endl;                                       // Output separator
  outputFile << "======" << std::endl;                           // Output separator
  outputFile << std::endl;                                       // Output separator
  outputMatches(users, outputFileName, phoneNumber2, "", true);  // Output matches
}

void outputBlock(User* users, std::string outputFileName, std::string phoneNumber, std::string phoneNumber2) {  // Block Someone
  User* currentUser = users;                                                                                    // Initialize currentUser
  User* self = nullptr;                                                                                         // Initialize self
  while (currentUser) {                                                                                         // While there are users...
    if (currentUser->phoneNumber == phoneNumber) self = currentUser;                                            // Find and set self
    currentUser = currentUser->nextUser;                                                                        // Update the list
  }
  std::vector<std::string> newUsersLiked;                               // Initialize newUsersLiked
  for (const std::string& likedUser : self->usersLiked) {               // For each user in self's usersLiked...
    if (likedUser != phoneNumber2) newUsersLiked.push_back(likedUser);  // If the user is not the other user, add to newUsersLiked
  }
  self->usersLiked = newUsersLiked;                                        // Update self's usersLiked
  newUsersLiked.clear();                                                   // Clear newUsersLiked
  currentUser = users;                                                     // Reinitialize currentUser
  while (currentUser) {                                                    // While there are users...
    if (currentUser->phoneNumber == phoneNumber2) {                        // If the user is the other user...
      for (const std::string& likedUser : currentUser->usersLiked) {       // For each user in the other user's usersLiked...
        if (likedUser != phoneNumber) newUsersLiked.push_back(likedUser);  // If the user is not self, add to newUsersLiked
      }
      currentUser->usersLiked = newUsersLiked;  // Update the other user's usersLiked
      break;
    }
    currentUser = currentUser->nextUser;  // Update the list
  }
  outputProfiles(users, outputFileName, phoneNumber, phoneNumber2, true);  // Output profiles
  outputFile << std::endl;                                                 // Output separator
  outputFile << "======" << std::endl;                                     // Output separator
  outputFile << std::endl;                                                 // Output separator
  updateUsers(users, phoneNumber2);                                        // Update users
  outputProfiles(users, outputFileName, phoneNumber2, phoneNumber, true);  // Output profiles
}