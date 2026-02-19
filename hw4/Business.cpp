#include "Business.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

Business::Business(std::string& line) {   // Create a business from a line in the businesses file
  original = line;                        // Store the original line
  name = importName();                    // Get the name of the business
  city = importCity();                    // Get the city of the business
  postal_code = importPostalCode();       // Get the postal code of the business
  stars = importRating();                 // Get the rating of the business
  reviews = importReviews();              // Get the number of reviews of the business
  price = importPrice();                  // Get the price of the business
  categories = importCategoriesVector();  // Get the categories of the business as a vector
}

std::string Business::importPostalCode() {                      // Get the postal code of the business
  int start = 0;                                                // Initialize the starting index
  int key_start = original.find("postal_code", start);          // Find "postal_code"
  int value_start = key_start + 14;                             // Calculate the starting index
  int value_end = original.find("\"", value_start);             // Find the ending index
  int len = value_end - value_start;                            // Calculate the length of the postal code
  std::string postal_code = original.substr(value_start, len);  // Get the postal code
  return postal_code;
}

int Business::importReviews() {                           // Get the number of reviews of the business
  int start = 0;                                          // Initialize the starting index
  int key_start = original.find("review_count", start);   // Find "review_count"
  if ((size_t)key_start == std::string::npos) return 0;   // No review count found
  int value_start = key_start + 14;                       // Calculate the starting index
  int value_end = original.find(",", value_start);        // Find the ending index
  int len = value_end - value_start;                      // Calculate the length of the review count
  int reviews = stoi(original.substr(value_start, len));  // Get the number of reviews and convert it to an integer
  return reviews;
}

std::vector<std::string> Business::importCategoriesVector() {  // Get the categories of the business as a vector
  std::vector<std::string> categoriesVector;                   // Initialize the categories vector
  std::string categories = importCategories();                 // Get the categories of the business as a string
  size_t positionIndex = 0;                                    // Initialize the position index
  std::string categoryString;                                  // Initialize the category string
  while (categories.find(", ") != std::string::npos) {         // While there are more categories...
    positionIndex = categories.find(", ");                     // Find the next comma and space
    categoryString = categories.substr(0, positionIndex);      // Get the next category
    categoriesVector.push_back(categoryString);                // Add the category to the vector
    categories.erase(0, positionIndex + 2);                    // Clean data
  };
  categoriesVector.push_back(categories);  // Add the last category to the vector
  return categoriesVector;
}

std::string Business::importCity() {                     // Get the city of the business
  int start = 0;                                         // Initialize the starting index
  int key_start = original.find("city", start);          // Find "city"
  int value_start = key_start + 7;                       // Calculate the starting index
  int value_end = original.find("\"", value_start);      // Find the ending index
  int len = value_end - value_start;                     // Calculate the length of the city
  std::string city = original.substr(value_start, len);  // Get the city
  return city;
}

std::string Business::getCategories() {                        // Get the categories of the business as a string
  std::string categoriesString;                                // Initialize the categories string
  for (size_t i = 0; i < categories.size(); i++) {             // For each category...
    categoriesString += categories[i];                         // Add the category to the string
    if (i != categories.size() - 1) categoriesString += ", ";  // If it's not the last category, add a comma and space
  };
  return categoriesString;
}

// Get Business Name
// From https://github.com/jidongxiao/CSCI1200-DataStructures/blob/master/hws/yelp_businesses/README.md
std::string Business::importName() {
  int start = 0;
  int key_start = original.find("name", start);
  int value_start = key_start + 7;
  int value_end = original.find("\"", value_start);
  int len = value_end - value_start;
  std::string name = original.substr(value_start, len);
  return name;
}

// Get Categories
// From https://github.com/jidongxiao/CSCI1200-DataStructures/blob/master/hws/yelp_businesses/README.md
std::string Business::importCategories() {
  int start = 0;
  int key_start = original.find("categories", start);
  int value_start = key_start + 13;
  int value_end = original.find("\"", value_start);
  int len = value_end - value_start;
  std::string categories = original.substr(value_start, len);
  return categories;
}

// Get Rating
// From https://github.com/jidongxiao/CSCI1200-DataStructures/blob/master/hws/yelp_businesses/README.md
double Business::importRating() {
  int start = 0;
  int key_start = original.find("stars", start);
  int value_start = key_start + 7;
  int value_end = original.find("\"", value_start);
  int len = value_end - value_start - 1;
  double stars = stod(original.substr(value_start, len));
  return stars;
}

// Get Price Level
// From https://github.com/jidongxiao/CSCI1200-DataStructures/blob/master/hws/yelp_businesses/README.md
int Business::importPrice() {
  int start = 0;
  int key_start = original.find("RestaurantsPriceRange2", start);
  if ((size_t)key_start == std::string::npos) return -1;  // Cast to size_t
  int value_start = key_start + 25;
  int value_end = original.find("\"", value_start);
  int len = value_end - value_start;
  if (original.substr(value_start, len) == "None") return -1;  // RestaurantsPriceRange2 is None
  int price = stoi(original.substr(value_start, len));
  return price;
}