#ifndef BUSINESS_H
#define BUSINESS_H
#include <string>
#include <vector>

// Class for the business
class Business {
 private:
  std::string original;                 // Original line from the businesses file
  std::string name;                     // Name of the business
  std::string city;                     // City of the business
  std::string postal_code;              // Postal code of the business
  double stars;                         // Rating of the business
  int reviews;                          // Number of reviews of the business
  int price;                            // Price of the business
  std::vector<std::string> categories;  // Categories of the business

 public:
  Business(std::string& line);                        // Create a business from a line in the businesses file
  std::string importPostalCode();                     // Get the postal code of the business
  int importReviews();                                // Get the number of reviews of the business
  std::vector<std::string> importCategoriesVector();  // Get the categories of the business as a vector
  std::string importName();                           // Get the name of the business
  std::string importCity();                           // Get the city of the business
  std::string importCategories();                     // Get the categories of the business
  double importRating();                              // Get the rating of the business
  int importPrice();                                  // Get the price of the business
  std::string getName() const { return name; }
  std::string getPostalCode() const { return postal_code; }
  std::string getCity() const { return city; }
  double getRating() const { return stars; }
  int getReviews() const { return reviews; }
  int getPrice() const { return price; }
  std::string getCategories();
  std::vector<std::string> getCategoriesVector() const { return categories; }
};

#endif
