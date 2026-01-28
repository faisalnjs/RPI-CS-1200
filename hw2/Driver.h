#ifndef DRIVER_H
#define DRIVER_H
#include <string>

struct Driver {
  bool exists = false;
  std::string firstName;
  std::string lastName;
  std::string gender;
  std::string age;
  std::string phoneNumber;
  std::string rating;
  double currentLatitude;
  double currentLongitude;
  std::string vehicleType;
  std::string currentState;
  std::string currentRiderFirstName;
  std::string currentRiderLastName;
  std::string currentRiderPhoneNumber;
};

#endif