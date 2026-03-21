#ifndef RESULT_H
#define RESULT_H

#include <string>

struct Page;  // Avoid circular include

// Struct for the result
struct Result {
  Page* page = nullptr;         // Pointer to the page of the result (non-owning)
  std::string snippet;          // Snippet of the result
  double score = 1.0;           // Score of the result
  Result(Page& pageReference);  // Create a result from a page
};

#endif
