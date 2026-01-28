#ifndef RIDER_H
#define RIDER_H
#include <string>

struct Rider {
  bool exists = false;
  std::string firstName;
  std::string lastName;
  std::string gender;
  std::string age;
  std::string phoneNumber;
  std::string rating;
  std::string pickupLocationName;
  double pickupLatitude;
  double pickupLongitude;
  std::string dropoffLocationName;
  double dropoffLatitude;
  double dropoffLongitude;
  std::string vehiclePreference;
  std::string currentState;
  std::string currentDriverFirstName;
  std::string currentDriverLastName;
  std::string currentDriverPhoneNumber;
};

#endif