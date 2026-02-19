#include <fstream>
#include <iostream>
#include <string>

#include "Business.h"
#include "Businesses.h"

int main(int argc, char* argv[]) {
  if (argc < 4) {
    std::cout << "Usage: ./nybusinesses.out input.json output.txt zipcode categories" << std::endl;  // Read inputs
    exit(1);
  }

  // Businesses file
  std::string businessesFileName = std::string(argv[1]);
  std::ifstream businessesFile(businessesFileName);  // READ businesses file
  if (!businessesFile.is_open()) {
    std::cerr << "Failed to open the businesses file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  // Output file
  std::string outputFileName = std::string(argv[2]);
  std::ofstream outputFile(outputFileName);  // Ready the WRITE output file
  if (!outputFile.is_open()) {
    std::cerr << "Failed to open the output file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  Businesses businesses(businessesFileName);  // Create a businesses list from a businesses file

  businessesFile.close();  // Done with businesses file

  std::string zipcode = std::string(argv[3]);  // Get the input zipcode

  std::vector<std::string> categories;  // Get the input categories

  for (int i = 4; i < argc; i++) {                      // For each input category...
    std::string category = std::string(argv[i]);        // Get the category
    category = category.substr(0, category.find(","));  // Clean data
    categories.push_back(category);                     // Add category to vector
  }

  //   std::cout << "Debug: Zipcode - " << zipcode << std::endl;  // Debug - check zipcode

  //   for (const std::string& category : categories) std::cout << "Debug: Category - " << category << std::endl;  // Debug - check categories

  std::list<Business> filteredBusinesses = businesses.getBusinesses(zipcode, categories);  // Get filtered businesses

  std::cout << "Debug: Number of filtered businesses - " << filteredBusinesses.size() << std::endl;  // Debug - check number of filtered businesses

  if (filteredBusinesses.empty()) {
    outputFile << "Sorry, we couldn't find any results" << std::endl;  // No businesses found
    return 0;
  }

  // Sort by rating
  std::list<Business> sortedBusinesses;            // Initialize sorted businesses list
  for (Business& business : filteredBusinesses) {  // For each filtered business...
    if (sortedBusinesses.empty()) {                // If empty starting list
      sortedBusinesses.push_back(business);        // Add first business
    } else {
      bool businessAdded = false;                                                                                          // Initialize business added boolean
      std::list<Business>::iterator businessIterator;                                                                      // Initialize business iterator
      for (businessIterator = sortedBusinesses.begin(); businessIterator != sortedBusinesses.end(); ++businessIterator) {  // For each business...
        if (business.getRating() > businessIterator->getRating()) {                                                        // Higher rating
          sortedBusinesses.insert(businessIterator, business);                                                             // Insert the new business before the current
          businessAdded = true;                                                                                            // Mark as added
          break;
        }
      }
      if (!businessAdded) sortedBusinesses.push_back(business);  // Add to end
    }
  }

  std::cout << "Debug: Number of sorted businesses - " << sortedBusinesses.size() << std::endl;  // Debug - check number of sorted businesses

  int currentBusinessNumber = 1;                                                     // Initialize current business number
  for (Business& business : sortedBusinesses) {                                      // For each filtered and sorted business...
    outputFile << "=====================" << std::endl;                              // Output separator
    outputFile << currentBusinessNumber << ". " << business.getName() << std::endl;  // Output number and name
    int roundedDownRating = (int)business.getRating();                               // Round rating down
    for (int i = 0; i < roundedDownRating; i++) outputFile << "\u2605";              // Output whole stars
    if ((business.getRating() - roundedDownRating) >= 0.5) outputFile << "\u00BD";   // Output half star if applicable
    outputFile << " " << business.getRating() << " (";                               // Output rating
    outputFile << business.getReviews() << " review";                                // Output reviews
    if (business.getReviews() != 1) outputFile << "s";                               // Single review
    outputFile << ")" << std::endl;                                                  // End of rating line
    outputFile << business.getCity() << " ";                                         // Output city
    if (business.getPrice() > 0) {                                                   // Nonezero price
      for (int i = 0; i < business.getPrice(); i++) outputFile << "$";               // Output price
    }
    outputFile << std::endl;                              // End of city line
    outputFile << business.getCategories() << std::endl;  // Output categories
    currentBusinessNumber++;                              // Increment business number
  }
  outputFile << "=====================" << std::endl;  // Output separator

  outputFile.close();  // Done with output file

  return 0;
}