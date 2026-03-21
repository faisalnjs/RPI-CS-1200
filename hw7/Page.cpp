#include "Page.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <regex>
#include <set>
#include <string>

#include "Query.h"
#include "Result.h"

Page::Page() {                              // Create an empty page
  path = "";                                // Initialize path
  contents = "";                            // Initialize contents
  title = "";                               // Initialize title
  description = "";                         // Initialize description
  body = "";                                // Initialize body
  keywords = std::map<std::string, int>();  // Initialize keywords
  references = std::set<std::string>();     // Initialize references
  score = 0.0;                              // Initialize score
};

Page::Page(std::map<std::string, Page>& pages, std::string directory, std::string filePath) {  // Create a page with given directory and file path
  path = filePath;                                                                             // Initialize path
                                                                                               //   std::cout << "Crawling page: " << path << std::endl;                                         // Output the page being crawled
  std::ifstream fileStream(filePath);                                                          // READ page file
  if (!fileStream.is_open()) {
    std::cerr << "Failed to open the page file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  // Other Useful Code
  // From From https://github.com/jidongxiao/CSCI1200-DataStructures/tree/master/hws/search_engine#provided-functions
  std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
  // std::cout << "File content: " << fileContent << std::endl; // Output the page being crawled
  contents = fileContent;
  fileStream.close();

  title = fileContent.substr(fileContent.find("<title>") + 7);  // Set title
  title = title.substr(0, title.find("</title>"));              // Set title

  description = fileContent.substr(fileContent.find("description") + 22);  // Set description
  description = description.substr(0, description.find('"'));              // Set description

  std::size_t bodyStart = fileContent.find('>', fileContent.find("<body")) + 1;              // Initialize bodyStart
  body = fileContent.substr(bodyStart, fileContent.find("</body>", bodyStart) - bodyStart);  // Set body

  // function to parse an HTML file and extract links to local files
  // From https://github.com/jidongxiao/CSCI1200-DataStructures/tree/master/hws/search_engine#provided-functions
  std::regex linkRegex("<a\\s+[^>]*href\\s*=\\s*['\"]([^'\"]+)['\"][^>]*>");
  std::smatch match;
  std::string::const_iterator start = fileContent.cbegin();
  while (std::regex_search(start, fileContent.cend(), match, linkRegex)) {
    std::string link = match[1].str();

    // Useful String Functions
    // From https://github.com/jidongxiao/CSCI1200-DataStructures/tree/master/hws/search_engine#useful-string-functions
    std::string newDirectory;
    size_t lastSlashPos = filePath.find_last_of('/');
    if (lastSlashPos != std::string::npos) newDirectory = filePath.substr(0, lastSlashPos + 1);

    std::string fullLink = newDirectory + link;                                                         // Initialize fullLink
    if (link.find("../") != std::string::npos) {                                                        // If the link is not in the current directory...
      std::string currentPath = newDirectory + link;                                                    // Initialize currentPath
      std::string result;                                                                               // Initialize result
      std::string parts[256];                                                                           // Initialize parts
      int initialPart = 0;                                                                              // Initialize initialPart
      std::size_t currentPart = 0;                                                                      // Initialize currentPart
      while (currentPart < currentPath.size()) {                                                        // While there are more parts in the currentPath...
        while ((currentPart < currentPath.size()) && (currentPath[currentPart] == '/')) ++currentPart;  // Skip slashes
        if (currentPart >= currentPath.size()) break;                                                   // No more parts
        std::size_t pathStart = currentPart;                                                            // Initialize pathStart
        while ((currentPart < currentPath.size()) && (currentPath[currentPart] != '/')) ++currentPart;  // Move to the end of the part
        std::string part = currentPath.substr(pathStart, (currentPart - pathStart));                    // Initialize part
        if (part == "..") {                                                                             // If ..
          if ((initialPart > 0) && (parts[initialPart - 1] != "..")) {
            --initialPart;  // Remove previous non-.. part
          } else {
            parts[initialPart++] = part;  // Add part
          };
        } else if (!part.empty()) {
          parts[initialPart++] = part;  // Add part
        };
      };
      for (int part = 0; part < initialPart; ++part) {  // For every part...
        result += parts[part];                          // Add the part
        result.push_back('/');                          // Add slash
      };
      result.pop_back();  // Remove trailing slash
      fullLink = result;
    };
    if (match.size() > 1) references.insert(fullLink);  // Add the link to references
    start = match.suffix().first;
  };
  pages[filePath] = *this;                                              // Add the page to pages
  for (const std::string& link : references) {                          // For every reference...
    if (pages.find(link) == pages.end()) Page(pages, directory, link);  // Crawl reference (recursive)
  };
};

void Page::Search(Query& query) {                                                                                                       // Search the page for the query
  if (query.phrase) {                                                                                                                   // Phrase query
    std::size_t currentPosition = 0;                                                                                                    // Initialize currentPosition
    while (true) {                                                                                                                      // While there are query occurrences...
      currentPosition = contents.find(query.query, currentPosition);                                                                    // Find the query in the contents
      if (currentPosition == std::string::npos) break;                                                                                  // No more occurrences
      bool previousCharacterGood = (currentPosition == 0) || !std::isalnum(static_cast<unsigned char>(contents[currentPosition - 1]));  // Check previous character
      std::size_t position = currentPosition + query.query.size();                                                                      // Initialize position
      bool nextCharacterGood = (position >= contents.size()) || !std::isalnum(static_cast<unsigned char>(contents[position]));          // Check next character
      if (!(previousCharacterGood && nextCharacterGood)) {                                                                              // Query occurrence is not a whole word
        ++currentPosition;
        continue;
      };
      std::size_t queryPosition = std::string::npos;                                                                                                    // Initialize queryPosition
      for (std::size_t occurrence = body.find(query.query, 0); occurrence != std::string::npos; occurrence = body.find(query.query, occurrence + 1)) {  // For every query occurrence...
        bool previousCharacterGood = (occurrence == 0) || !std::isalnum(static_cast<unsigned char>(body[occurrence - 1]));                              // Check previous character
        std::size_t position = occurrence + query.query.size();                                                                                         // Initialize position
        bool nextCharacterGood = (position >= body.size()) || !std::isalnum(static_cast<unsigned char>(body[position]));                                // Check next character
        if (previousCharacterGood && nextCharacterGood) {                                                                                               // Query occurrence is a whole word
          queryPosition = occurrence;                                                                                                                   // Set queryPosition
          break;
        };
      };
      std::size_t periodPosition = (queryPosition < body.size()) ? body.rfind('.', queryPosition) : body.rfind('.');                          // Initialize periodPosition
      std::size_t nextPeriodPosition = periodPosition + 1;                                                                                    // Initialize nextPeriodPosition
      while ((nextPeriodPosition < body.size()) && std::isspace(static_cast<unsigned char>(body[nextPeriodPosition]))) ++nextPeriodPosition;  // Skip whitespace
      Result result(*this);                                                                                                                   // Initialize result
      result.snippet = body.substr(nextPeriodPosition, 120);                                                                                  // Set the snippet of the result
      query.results.push_back(result);                                                                                                        // Add the result to the query results
      break;
    };
  } else {                                                                                                                                                            // Non-phrase query
    std::istringstream stream(query.query);                                                                                                                           // Initialize stream
    std::vector<std::string> words;                                                                                                                                   // Initialize words
    for (std::string word; stream >> word;) words.push_back(word);                                                                                                    // Add all words to words
    bool allWordsFound = true;                                                                                                                                        // Initialize allWordsFound
    for (const std::string& word : words) {                                                                                                                           // For every word in the query...
      bool found = false;                                                                                                                                             // Initialize found
      for (std::size_t currentPosition = contents.find(word, 0); currentPosition != std::string::npos; currentPosition = contents.find(word, currentPosition + 1)) {  // For every word occurrence...
        bool previousCharacterGood = (currentPosition == 0) || !std::isalnum(static_cast<unsigned char>(contents[currentPosition - 1]));                              // Check previous character
        std::size_t position = currentPosition + word.size();                                                                                                         // Initialize position
        bool nextCharacterGood = (position >= contents.size()) || !std::isalnum(static_cast<unsigned char>(contents[position]));                                      // Check next character
        if (previousCharacterGood && nextCharacterGood) {                                                                                                             // Whole word
          found = true;                                                                                                                                               // Set found
          break;
        };
      };
      if (!found) {             // Word not found
        allWordsFound = false;  // Set allWordsFound
        break;
      };
    };
    if (!allWordsFound) return;                                                                                                                                           // Not all words found
    std::size_t snippetPosition = std::string::npos;                                                                                                                      // Initialize snippetPosition
    for (std::size_t currentPosition = body.find(query.query, 0); currentPosition != std::string::npos; currentPosition = body.find(query.query, currentPosition + 1)) {  // For every query occurrence...
      bool previousCharacterGood = (currentPosition == 0) || !std::isalnum(static_cast<unsigned char>(body[currentPosition - 1]));                                        // Check previous character
      std::size_t position = currentPosition + query.query.size();                                                                                                        // Initialize position
      bool nextCharacterGood = (position >= body.size()) || !std::isalnum(static_cast<unsigned char>(body[position]));                                                    // Check next character
      if (previousCharacterGood && nextCharacterGood) {                                                                                                                   // Whole word
        snippetPosition = currentPosition;                                                                                                                                // Set snippetPosition
        break;
      };
    };
    if (snippetPosition == std::string::npos) {                                                                                                                         // If no query occurrence found...
      const std::string& firstWord = words[0];                                                                                                                          // Get the first word in the query
      for (std::size_t currentPosition = body.find(firstWord, 0); currentPosition != std::string::npos; currentPosition = body.find(firstWord, currentPosition + 1)) {  // For every first word occurrence...
        bool previousCharacterGood = (currentPosition == 0) || !std::isalnum(static_cast<unsigned char>(body[currentPosition - 1]));                                    // Check previous character
        std::size_t position = currentPosition + firstWord.size();                                                                                                      // Initialize position
        bool nextCharacterGood = (position >= body.size()) || !std::isalnum(static_cast<unsigned char>(body[position]));                                                // Check next character
        if (previousCharacterGood && nextCharacterGood) {                                                                                                               // Whole word
          snippetPosition = currentPosition;                                                                                                                            // Set snippetPosition
          break;
        };
      };
    };
    std::size_t periodPosition = (snippetPosition < body.size()) ? body.rfind('.', snippetPosition) : body.rfind('.');                    // Initialize periodPosition
    std::size_t nextPeriodPosition = (periodPosition == std::string::npos) ? 0 : periodPosition + 1;                                      // Initialize nextPeriodPosition
    while (nextPeriodPosition < body.size() && std::isspace(static_cast<unsigned char>(body[nextPeriodPosition]))) ++nextPeriodPosition;  // Skip whitespace
    Result result(*this);                                                                                                                 // Initialize result
    result.snippet = body.substr(nextPeriodPosition, 120);                                                                                // Set the snippet of the result
    query.results.push_back(result);                                                                                                      // Add the result to the query results
  };
};
