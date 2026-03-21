#include "Query.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "Page.h"
#include "Result.h"

Query::Query(std::string line) {                 // Create a query from a line
  original = line;                               // Set the original query string to the line
  if (line.empty()) return;                      // Empty line
  if (line[0] == '"') {                          // Phrase query
    phrase = true;                               // Set phrase to true
    line.erase(0, 1).erase(line.size() - 1, 1);  // Remove quotes
  };
  query = line;  // Set the query string to the line
};

void Query::RankResults(std::map<std::string, Page>& pages) {                                                                             // Rank the query results
  std::istringstream stream(query);                                                                                                       // Initialize stream
  std::vector<std::string> keywords;                                                                                                      // Initialize keywords
  for (std::string keyword; stream >> keyword;) keywords.push_back(keyword);                                                              // For every keyword in the query, add to keywords
  if (keywords.empty()) return;                                                                                                           // No keywords
  double totalContentLength = 0.0;                                                                                                        // Initialize totalContentLength
  for (std::pair<const std::string, Page>& page : pages) totalContentLength += static_cast<double>(page.second.contents.size());          // Calculate the total content length of all pages
  std::vector<int> totalOccurrences(keywords.size(), 0);                                                                                  // Initialize totalOccurrences
  for (std::pair<const std::string, Page>& page : pages) {                                                                                // For every page...
    const std::string& contents = page.second.contents;                                                                                   // Get the page contents
    for (size_t keywordIndex = 0; keywordIndex < keywords.size(); ++keywordIndex) {                                                       // For every keyword...
      const std::string& keyword = keywords[keywordIndex];                                                                                // Get the keyword
      if (keyword.empty() || (contents.size() < keyword.size())) continue;                                                                // Skip if at end of document
      size_t currentPosition = 0;                                                                                                         // Initialize currentPosition
      while ((currentPosition = contents.find(keyword, currentPosition)) != std::string::npos) {                                          // While there are keyword occurrences...
        size_t position = currentPosition + keyword.size();                                                                               // Initialize position
        bool previousCharacterGood = (currentPosition == 0) || !std::isalnum(static_cast<unsigned char>(contents[currentPosition - 1]));  // Check previous character
        bool nextCharacterGood = (position >= contents.size()) || !std::isalnum(static_cast<unsigned char>(contents[position]));          // Check next character
        if (previousCharacterGood && nextCharacterGood) ++totalOccurrences[keywordIndex];                                                 // Keyword is good
        ++currentPosition;
      };
    };
  };
  for (Result& result : results) {                                                                                                        // For every result...
    Page* currentPage = result.page;                                                                                                      // Get the page of the result
    if (!currentPage) continue;                                                                                                           // No page
    const std::string& contents = currentPage->contents;                                                                                  // Get the page contents
    double documentLength = static_cast<double>(contents.size());                                                                         // Initialize documentLength
    double keywordDensityScore = 0.0;                                                                                                     // Initialize keywordDensityScore
    for (size_t keywordIndex = 0; keywordIndex < keywords.size(); ++keywordIndex) {                                                       // For every keyword...
      const std::string& keyword = keywords[keywordIndex];                                                                                // Get the keyword
      if (keyword.empty() || (contents.size() < keyword.size())) continue;                                                                // Skip if at end of document
      int occurrences = 0;                                                                                                                // Initialize occurrences
      size_t currentPosition = 0;                                                                                                         // Initialize currentPosition
      while ((currentPosition = contents.find(keyword, currentPosition)) != std::string::npos) {                                          // While there are keyword occurrences...
        size_t position = currentPosition + keyword.size();                                                                               // Initialize position
        bool previousCharacterGood = (currentPosition == 0) || !std::isalnum(static_cast<unsigned char>(contents[currentPosition - 1]));  // Check previous character
        bool nextCharacterGood = (position >= contents.size()) || !std::isalnum(static_cast<unsigned char>(contents[position]));          // Check next character
        if (previousCharacterGood && nextCharacterGood) ++occurrences;                                                                    // Keyword is good
        ++currentPosition;
      };
      double overallDensity = (totalContentLength > 0.0) ? (static_cast<double>(totalOccurrences[keywordIndex]) / totalContentLength) : 0.0;              // Initialize overallDensity
      if ((overallDensity > 0.0) && (documentLength > 0.0)) keywordDensityScore += static_cast<double>(occurrences) / (documentLength * overallDensity);  // Calculate the keyword density score of the page
    };
    double backlinksScore = 0.0;                                                                                                                // Initialize backlinksScore
    for (std::pair<const std::string, Page>& page : pages) {                                                                                    // For every other page...
      if (page.first == currentPage->path) continue;                                                                                            // Skip if current page
      if (page.second.references.count(currentPage->path)) backlinksScore += 1.0 / (1.0 + static_cast<double>(page.second.references.size()));  // Calculate the backlinks score of the page
    };
    result.score = 0.5 * keywordDensityScore + 0.5 * backlinksScore;  // Calculate the overall score of the page
    currentPage->score = result.score;
  };
  std::sort(results.begin(), results.end(), [](Result const& a, Result const& b) {  // Sort the results by score
    return a.score > b.score;
  });
};

void CreateQueries(std::vector<Query>& queries, std::string queriesFileName) {  // Create the queries from the queries file
  std::ifstream queriesFile(queriesFileName);                                   // READ queries file
  if (!queriesFile.is_open()) {
    std::cerr << "Failed to open the queries file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  std::string line;

  // Queries file -> queries list
  while (getline(queriesFile, line)) {  // For each line in the queries file...
    Query newQuery(line);               // Create a query from a line
    queries.push_back(newQuery);        // Add the new query to list
  };
};

void OutputQueries(std::vector<Query>& queries) {                                // Output query results
  int currentQuery = 1;                                                          // Current query number
  for (Query& query : queries) {                                                 // For every query...
    std::ofstream outputFile("out" + std::to_string(currentQuery) + ".txt");  // Ready the WRITE query output file
    if (!outputFile.is_open()) {
      std::cerr << "Failed to open the output file." << std::endl;  // Error if file cannot be opened
      exit(1);
    }
    if (query.results.empty()) {
      outputFile << "Your search - " << query.original << " - did not match any documents." << std::endl;  // No results found
    } else {
      outputFile << "Matching documents: \n"
                 << std::endl;                                                     // Output the matching documents
      for (const Result& result : query.results) {                                 // For every result...
        if (result.page) {                                                         // If the result has a page...
          outputFile << "Title: " << result.page->title << std::endl;              // Output the title of the page
          outputFile << "URL: " << result.page->path << std::endl;                 // Output the URL of the page
          outputFile << "Description: " << result.page->description << std::endl;  // Output the description of the page
          outputFile << "Snippet: " << result.snippet << std::endl;                // Output the snippet of the page
          if (&result != &query.results.back()) outputFile << std::endl;           // Output separator
        }
      }
    };
    currentQuery++;
  };
};