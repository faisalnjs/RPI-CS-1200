#ifndef RIDERS_H
#define RIDERS_H
#include <string>
#include <vector>

#include "Rider.h"

// Class for the riders
class Riders {
 private:
  std::vector<Rider> riders = {};  // Establish empty vector for the riders
 public:
  Riders(const std::string& ridersFileName);                  // Create a riders vector from a riders file
  std::vector<Rider> getRiders() const&;                      // Get riders
  std::vector<Rider> updateRider(const Rider& updatedRider);  // Update rider
};

#endif