#ifndef QUERY_H
#define QUERY_H

#include <map>
#include <string>
#include <vector>

#include "Result.h"

// Struct for the query
struct Query {
  std::string original = "";                             // Original query string
  std::string query = "";                                // Query string
  bool phrase = false;                                   // Phrase query
  std::vector<Result> results;                           // Results for the query
  Query(std::string line);                               // Create a query from a line
  void RankResults(std::map<std::string, Page>& pages);  // Rank the query results
};

#endif
