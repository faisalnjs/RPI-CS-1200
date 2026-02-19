#include "Businesses.h"

#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include "Business.h"

Businesses::Businesses(const std::string& businessesFileName) {  // Create a businesses list from a businesses file
  std::ifstream businessesFile(businessesFileName);              // READ businesses file
  if (!businessesFile.is_open()) {
    std::cerr << "Failed to open the businesses file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  std::string line;

  // Businesses file -> businesses list
  while (getline(businessesFile, line)) {  // For each line in the businesses file...
    Business newBusiness(line);            // Create a business from the line
    businesses.push_back(newBusiness);     // Add the new business to list
  }

  // Testing - check to see if everything was added to the list correctly
  // for (Business& business : businesses) {
  //   std::cout << "Debug: Business - " << business.getName() << " ... " << business.getCity() << " ... " << business.getPostalCode() << " ... " << business.getRating() << " ... " << business.getCategories() << std::endl;
  // }

  businessesFile.close();  // Done with businesses file
}

std::list<Business> Businesses::getBusinesses() const& {  // Get businesses
  return businesses;
}

std::list<Business> Businesses::getBusinesses(const std::string& zipcode) {           // Get filtered businesses by zipcode
  std::list<Business> filteredBusinesses;                                             // Initialize the filtered businesses list
  for (Business& business : businesses) {                                             // For each business...
    if (business.getPostalCode() == zipcode) filteredBusinesses.push_back(business);  // Add matching business to the list
  }
  //   std::cout << "Debug: Number of businesses in " << zipcode << " - " << filteredBusinesses.size() << std::endl;  // Debug - check number of businesses in the zipcode
  return filteredBusinesses;
}

std::list<Business> Businesses::getBusinesses(const std::string& zipcode, const std::vector<std::string>& categories) {  // Get filtered businesses by zipcode and categories
  std::list<Business> filteredBusinesses;                                                                                // Initialize the filtered businesses list
  for (Business& business : businesses) {                                                                                // For each business...
    bool categoryMatch = false;                                                                                          // Initialize category match boolean
    for (const std::string& category : categories) {                                                                     // For each input category...
      for (const std::string& businessCategory : business.getCategoriesVector()) {                                       // For each business category...
        if (businessCategory.find(category) != std::string::npos) categoryMatch = true;                                  // Category matched
      }
    }
    if ((business.getPostalCode() == zipcode) && categoryMatch) filteredBusinesses.push_back(business);  // Add matching business to the list
  }
  return filteredBusinesses;
}