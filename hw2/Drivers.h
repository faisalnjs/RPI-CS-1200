#ifndef DRIVERS_H
#define DRIVERS_H
#include <string>
#include <vector>

#include "Driver.h"

// Class for the drivers
class Drivers {
 private:
  std::vector<Driver> drivers = {};  // Establish empty vector for the drivers
 public:
  Drivers(const std::string& driversFileName);                      // Create a drivers vector from a drivers file
  std::vector<Driver> getDrivers() const&;                          // Get drivers
  std::vector<Driver> updateDriver(const Driver& updatedDrivers);  // Update driver
};

#endif