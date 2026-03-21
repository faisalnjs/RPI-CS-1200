#include "Result.h"

#include <string>

#include "Page.h"

Result::Result(Page& pageReference) {  // Create a result from a page
  page = &pageReference;               // store non-owning pointer
  score = pageReference.score;         // initialize score from page's score
};