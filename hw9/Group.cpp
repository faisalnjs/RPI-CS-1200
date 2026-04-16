#include "Group.h"

#include <iostream>
#include <queue>
#include <string>

#include "Video.h"

Group::Group(const std::string& groupValue) {  // Create a group from a given value
  value = groupValue;
}

bool Group::operator<(const Group& other) const {  // Overload the less than operator for the group
  if (videos.size() == other.videos.size()) {
    if (totalViews == other.totalViews) return value > other.value;  // If rankings are equal, compare by value
    return totalViews < other.totalViews;                            // If rankings are still equal, compare by total views
  };
  return videos.size() < other.videos.size();  // Compare by videos
}