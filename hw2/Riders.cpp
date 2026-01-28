#include "Riders.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Rider.h"

Riders::Riders(const std::string& ridersFileName) {  // Create a riders vector from a riders file
  std::ifstream ridersFile(ridersFileName);          // READ riders file
  if (!ridersFile.is_open()) {
    std::cerr << "Failed to open the riders file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  std::string line;

  // Riders file -> riders vector
  while (getline(ridersFile, line)) {
    int nextSpaceFound = line.find(" ");                                                // Get the first space
    std::vector<std::string> ridersAttributes;                                          // Initialize the riders attributes vector
    ridersAttributes.push_back(line.substr(0, nextSpaceFound));                         // Push the first attribute
    while (line.find(" ") != std::string::npos) {                                       // While the space exists
      line.erase(0, nextSpaceFound + 1);                                                // Remove the first attribute + space
      nextSpaceFound = line.find(" ");                                                  // Find the next space
      if ((size_t)nextSpaceFound == std::string::npos) nextSpaceFound = line.length();  // If no space found, use the last character
      ridersAttributes.push_back(line.substr(0, nextSpaceFound));                       // Push the next attribute
    }
    Rider newRider;
    newRider.exists = true;
    newRider.firstName = ridersAttributes[0];
    newRider.lastName = ridersAttributes[1];
    newRider.gender = ridersAttributes[2];
    newRider.age = ridersAttributes[3];
    newRider.phoneNumber = ridersAttributes[4];
    newRider.rating = ridersAttributes[5];
    newRider.pickupLocationName = ridersAttributes[6];
    newRider.pickupLatitude = std::stod(ridersAttributes[7]);
    newRider.pickupLongitude = std::stod(ridersAttributes[8]);
    newRider.dropoffLocationName = ridersAttributes[9];
    newRider.dropoffLatitude = std::stod(ridersAttributes[10]);
    newRider.dropoffLongitude = std::stod(ridersAttributes[11]);
    newRider.vehiclePreference = ridersAttributes[12];
    newRider.currentState = ridersAttributes[13];
    newRider.currentDriverFirstName = ridersAttributes[14];
    newRider.currentDriverLastName = ridersAttributes[15];
    newRider.currentDriverPhoneNumber = ridersAttributes[16];
    riders.push_back(newRider);  // Add the new rider to vector
  }

  // Testing - check to see if everything was added to the vector correctly
  // for (const Rider& rider : riders) {
  //   std::cout << "Debug: Rider - " << rider.firstName << " " << rider.lastName << " ... " << rider.currentDriverPhoneNumber << std::endl;
  // }

  ridersFile.close();  // Done with riders file
}

std::vector<Rider> Riders::getRiders() const& {  // Get riders
  return riders;
}

std::vector<Rider> Riders::updateRider(const Rider& updatedRider) {  // Update rider
  for (size_t i = 0; i < riders.size(); i++) {
    if (riders[i].phoneNumber == updatedRider.phoneNumber) {
      riders[i] = updatedRider;
      break;
    }
  }
  return riders;
}