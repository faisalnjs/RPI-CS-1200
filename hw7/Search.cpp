#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Page.h"
#include "Query.h"

void StartSearch(std::map<std::string, Page>& pages, std::vector<Query>& queries) {            // Start the query search
  for (Query& query : queries) {                                                               // For every query...
    for (std::pair<const std::string, Page>& pagePair : pages) pagePair.second.Search(query);  // For every page, search the page for query (iterate by reference)
    query.RankResults(pages);                                                                  // Rank the query results
  }
}
