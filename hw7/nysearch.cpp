#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Page.h"
#include "Query.h"
#include "Result.h"

// Initialize global variables
std::map<std::string, Page> pages;  // Initialize pages
std::vector<Query> queries;         // Initialize queries

void CreateQueries(std::vector<Query>& queries, std::string queriesFileName);       // Create the queries from the queries file
void StartSearch(std::map<std::string, Page>& pages, std::vector<Query>& queries);  // Start the query search
void OutputQueries(std::vector<Query>& queries);                                    // Output query results

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Usage: ./nysearch.out input.txt input.txt" << std::endl;  // Read inputs
    exit(1);
  }

  std::string filePath = std::string(argv[1]);         // Get the input file path name
  std::string queriesFileName = std::string(argv[2]);  // Get the input queries file name

  // Useful String Functions
  // From https://github.com/jidongxiao/CSCI1200-DataStructures/tree/master/hws/search_engine#useful-string-functions
  std::string directory;
  size_t lastSlashPos = filePath.find_last_of('/');
  if (lastSlashPos != std::string::npos) directory = filePath.substr(0, lastSlashPos + 1);

  Page(pages, directory, filePath);  // Crawl the pages (recursive)

  std::cout << "Pages found: " << pages.size() << std::endl;  // Output the number of pages found

  CreateQueries(queries, queriesFileName);  // Create the queries from the queries file

  std::cout << "Queries found: " << queries.size() << std::endl;  // Output the number of queries found

  StartSearch(pages, queries);  // Start the query search

  OutputQueries(queries);  // Output the query results

  return 0;
}