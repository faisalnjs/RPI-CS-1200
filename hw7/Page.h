#ifndef PAGE_H
#define PAGE_H

#include <map>
#include <set>
#include <string>

#include "Query.h"

// Struct for the page
struct Page {
  std::string path;                                                                       // Path of the page
  std::string contents;                                                                   // Contents of the page
  std::string title;                                                                      // Title of the page
  std::string description;                                                                // Description of the page
  std::string body;                                                                       // Body of the page
  std::map<std::string, int> keywords;                                                    // Keywords on the page
  std::set<std::string> references;                                                       // References on the page
  double score = 0.0;                                                                     // Score of the page
  Page();                                                                                 // Create an empty page
  Page(std::map<std::string, Page>& pages, std::string directory, std::string filePath);  // Create a page with given directory and file path
  void Search(Query& query);                                                              // Search the page for the query
};

#endif
