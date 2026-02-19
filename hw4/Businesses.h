#ifndef BUSINESSES_H
#define BUSINESSES_H
#include <list>
#include <string>

#include "Business.h"

// Class for the businesses
class Businesses {
 private:
  std::list<Business> businesses;  // Initialize empty list for the businesses
 public:
  Businesses(const std::string& businessesFileName);                                                          // Create a businesses vector from a businesses file
  std::list<Business> getBusinesses() const&;                                                                 // Get businesses
  std::list<Business> getBusinesses(const std::string& zipcode);                                              // Get filtered businesses by zipcode
  std::list<Business> getBusinesses(const std::string& zipcode, const std::vector<std::string>& categories);  // Get filtered businesses by zipcode and categories
};

#endif
