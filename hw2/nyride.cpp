#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Driver.h"
#include "Drivers.h"
#include "Rider.h"
#include "Riders.h"

using namespace std;

// Calculate Distance Based on Haversine Formula
// From https://github.com/jidongxiao/CSCI1200-DataStructures/tree/master/hws/ride_sharing#calculate-distance-based-on-haversine-formula
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

int main(int argc, char* argv[]) {
  if (argc != 8) {
    std::cout << "Usage: ./nyride.out drivers.txt riders.txt output0.txt output1.txt output2.txt phoneNumber request|cancel" << std::endl;  // Read inputs
    exit(1);
  }

  std::string action = std::string(argv[7]);

  if ((action != "request") && (action != "cancel")) {  // Initial action validation
    std::cerr << "Action must be request|cancel." << std::endl;
    exit(1);
  }

  // Drivers file
  std::string driversFileName = std::string(argv[1]);
  std::ifstream driversFile(driversFileName);  // READ drivers file
  if (!driversFile.is_open()) {
    std::cerr << "Failed to open the drivers file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  // Riders file
  std::string ridersFileName = std::string(argv[2]);
  std::ifstream ridersFile(ridersFileName);  // READ riders file
  if (!ridersFile.is_open()) {
    std::cerr << "Failed to open the riders file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  // Output0 file
  std::string output0FileName = std::string(argv[3]);
  std::ofstream output0File(output0FileName);  // Ready the WRITE output0 file
  if (!output0File.is_open()) {
    std::cerr << "Failed to open the output0 file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  // Output1 file
  std::string output1FileName = std::string(argv[4]);
  std::ofstream output1File(output1FileName);  // Ready the WRITE output1 file
  if (!output1File.is_open()) {
    std::cerr << "Failed to open the output1 file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  // Output2 file
  std::string output2FileName = std::string(argv[5]);
  std::ofstream output2File(output2FileName);  // Ready the WRITE output2 file
  if (!output2File.is_open()) {
    std::cerr << "Failed to open the output2 file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  Drivers drivers(driversFileName);  // Create drivers vector from drivers file
  Riders riders(ridersFileName);     // Create riders vector from riders file

  driversFile.close();  // Done with drivers file
  ridersFile.close();   // Done with riders file

  std::string phoneNumber = std::string(argv[6]);

  if ((phoneNumber.length() != 12) || (phoneNumber[3] != '-') || (phoneNumber[7] != '-')) {  // Initial phone number validation
    std::cerr << "Phone number is invalid." << std::endl;
    output0File << "Phone number is invalid." << std::endl;
    exit(1);
  }

  Rider foundRider;  // Match phone number to rider, if any

  for (const Rider& rider : riders.getRiders()) {  // For all riders
    if (rider.phoneNumber == phoneNumber) {        // If matched phone number found
      foundRider = rider;                          // Set matched rider
      break;
    }
  }

  Driver foundDriver;  // Match phone number to driver, if any

  for (const Driver& driver : drivers.getDrivers()) {  // For all drivers
    if (driver.phoneNumber == phoneNumber) {           // If matched phone number found
      foundDriver = driver;                            // Set matched driver
      break;
    }
  }

  if (action == "request") {
    if (!foundRider.exists) {  // If no rider found
      std::cerr << "Account does not exist." << std::endl;
      output0File << "Account does not exist." << std::endl;
      exit(1);
    }
    Driver closestDriver;
    double closestDistance = 0.0;
    for (const Driver& driver : drivers.getDrivers()) {                                                                                                                         // For all drivers
      double calculatedDistance = calculateDistance(foundRider.pickupLatitude, foundRider.pickupLongitude, driver.currentLatitude, driver.currentLongitude);                    // Calculate distance between rider and driver
      if ((driver.currentState == "Available") && (driver.vehicleType == foundRider.vehiclePreference) && (!closestDriver.exists || (calculatedDistance < closestDistance))) {  // If they are available and closer to the currently chosen driver
        closestDriver = driver;                                                                                                                                                 // Set chosen driver
        break;
      }
    }
    std::vector<Driver> updatedDrivers = drivers.getDrivers();
    std::vector<Rider> updatedRiders = riders.getRiders();
    std::string calculatedDistanceString = std::to_string(closestDistance);                                 // Convert distance to string
    calculatedDistanceString = calculatedDistanceString.substr(0, calculatedDistanceString.find(".") + 2);  // Limit to 1 decimal place
    output0File << "Ride requested for rider " << foundRider.firstName << ", looking for an " << foundRider.vehiclePreference << " vehicle." << std::endl;
    output0File << "Pick Up Location: " << foundRider.pickupLocationName << ", Drop Off Location: " << foundRider.dropoffLocationName << "." << std::endl;
    if (foundRider.currentState == "Driver_on_the_way") {
      // Output to output0
      output0File << "You have already requested a ride and your driver is on the way to the pickup location." << std::endl;
    } else if (foundRider.currentState == "During_the_trip") {
      // Output to output0
      output0File << "You can not request a ride at this moment as you are already on a trip." << std::endl;
    } else if (closestDriver.exists) {  // Closest driver was found
      // Output to output0
      output0File << "We have found the closest driver " << closestDriver.firstName << "(" << closestDriver.rating << ") for you." << std::endl;
      output0File << closestDriver.firstName << " is now " << calculatedDistanceString << " miles away from you." << std::endl;
      // Update driver
      closestDriver.currentState = "On_the_way_to_pickup";
      closestDriver.currentRiderFirstName = foundRider.firstName;
      closestDriver.currentRiderLastName = foundRider.lastName;
      closestDriver.currentRiderPhoneNumber = foundRider.phoneNumber;
      updatedDrivers = drivers.updateDriver(closestDriver);
      // Update rider
      foundRider.currentState = "Driver_on_the_way";
      foundRider.currentDriverFirstName = closestDriver.firstName;
      foundRider.currentDriverLastName = closestDriver.lastName;
      foundRider.currentDriverPhoneNumber = closestDriver.phoneNumber;
      updatedRiders = riders.updateRider(foundRider);
    } else {  // Closest driver was not found
      // Output to output0
      output0File << "Sorry we can not find a driver for you at this moment." << std::endl;
    }
    // Output to output1
    for (const Driver& driver : updatedDrivers) {
      output1File << driver.firstName << " " << driver.lastName << " " << driver.gender << " " << driver.age << " " << driver.phoneNumber << " " << driver.rating << " " << driver.currentLatitude << " " << driver.currentLongitude << " " << driver.vehicleType << " " << driver.currentState << " " << driver.currentRiderFirstName << " " << driver.currentRiderLastName << " " << driver.currentRiderPhoneNumber << std::endl;
    }
    // Output to output2
    for (const Rider& rider : updatedRiders) {
      output2File << rider.firstName << " " << rider.lastName << " " << rider.gender << " " << rider.age << " " << rider.phoneNumber << " " << rider.rating << " " << rider.pickupLocationName << " " << rider.pickupLatitude << " " << rider.pickupLongitude << " " << rider.dropoffLocationName << " " << rider.dropoffLatitude << " " << rider.dropoffLongitude << " " << rider.vehiclePreference << " " << rider.currentState << " " << rider.currentDriverFirstName << " " << rider.currentDriverLastName << " " << rider.currentDriverPhoneNumber << std::endl;
    }
  } else if (action == "cancel") {
  }

  output0File.close();  // Done with output0 file
  output1File.close();  // Done with output1 file
  output2File.close();  // Done with output2 file
  return 0;
}
