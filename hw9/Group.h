#ifndef GROUP_H
#define GROUP_H

#include <iostream>
#include <queue>
#include <string>

#include "Video.h"

// Class for the group
class Group {
 public:
  std::string value;                         // Value of the group (hashtag or song ID)
  std::string musicName;                     // Music name for the group
  std::string musicAuthor;                   // Music author for the group
  std::priority_queue<Video> videos;         // Videos in the group
  int64_t totalViews = 0;                    // Total views in the group
  Group() {};                                // Create a group
  Group(const std::string& groupValue);      // Create a group from a given value
  bool operator<(const Group& other) const;  // Overload the less than operator for the group
};

#endif
