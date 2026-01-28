#include "Drivers.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Driver.h"

Drivers::Drivers(const std::string& driversFileName) {  // Create a drivers vector from a drivers file
  std::ifstream driversFile(driversFileName);           // READ drivers file
  if (!driversFile.is_open()) {
    std::cerr << "Failed to open the drivers file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  std::string line;

  // Drivers file -> drivers vector
  while (getline(driversFile, line)) {
    int nextSpaceFound = line.find(" ");                                                // Get the first space
    std::vector<std::string> driverAttributes;                                          // Initialize the driver attributes vector
    driverAttributes.push_back(line.substr(0, nextSpaceFound));                         // Push the first attribute
    while (line.find(" ") != std::string::npos) {                                       // While the space exists
      line.erase(0, nextSpaceFound + 1);                                                // Remove the first attribute + space
      nextSpaceFound = line.find(" ");                                                  // Find the next space
      if ((size_t)nextSpaceFound == std::string::npos) nextSpaceFound = line.length();  // If no space found, use the last character
      driverAttributes.push_back(line.substr(0, nextSpaceFound));                       // Push the next attribute
    }
    Driver newDriver;
    newDriver.exists = true;
    newDriver.firstName = driverAttributes[0];
    newDriver.lastName = driverAttributes[1];
    newDriver.gender = driverAttributes[2];
    newDriver.age = driverAttributes[3];
    newDriver.phoneNumber = driverAttributes[4];
    newDriver.rating = driverAttributes[5];
    newDriver.currentLatitude = std::stod(driverAttributes[6]);
    newDriver.currentLongitude = std::stod(driverAttributes[7]);
    newDriver.vehicleType = driverAttributes[8];
    newDriver.currentState = driverAttributes[9];
    newDriver.currentRiderFirstName = driverAttributes[10];
    newDriver.currentRiderLastName = driverAttributes[11];
    newDriver.currentRiderPhoneNumber = driverAttributes[12];
    drivers.push_back(newDriver);  // Add the new driver to vector
  }

  // Testing - check to see if everything was added to the vector correctly
  // for (const Driver& driver : drivers) {
  //   std::cout << "Debug: Driver - " << driver.firstName << " " << driver.lastName << " ... " << driver.currentRiderPhoneNumber << std::endl;
  // }

  driversFile.close();  // Done with drivers file
}

std::vector<Driver> Drivers::getDrivers() const& {  // Get drivers
  return drivers;
}

std::vector<Driver> Drivers::updateDriver(const Driver& updatedDriver) {  // Update driver
  for (size_t i = 0; i < drivers.size(); i++) {
    if (drivers[i].phoneNumber == updatedDriver.phoneNumber) {
      drivers[i] = updatedDriver;
      break;
    }
  }
  return drivers;
}