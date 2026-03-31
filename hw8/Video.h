#ifndef VIDEO_H
#define VIDEO_H

#include <iostream>
#include <string>
#include <vector>

#include "Comment.h"

// Class for the video
class Video {
 public:
  std::string id;                                                                                               // ID of the video
  std::vector<Comment*> comments;                                                                               // Comments of the video
  std::vector<Comment*> newComments;                                                                            // Comments created by actions
  Video() {};                                                                                                   // Create a video
  ~Video();                                                                                                     // Destructor for the video
  Video(const std::string& commentsFileName, std::vector<Comment>& comments);                                   // Create a video with the given comments file name and comments list
  void makeTree(std::vector<Comment>& commentsVector);                                                          // Make the tree of comments
  void processActions(const std::string& actionsFileName, const std::string& outputFileName);                   // Process the actions
  Comment* findComment(const std::string& id);                                                                  // Find a comment with the given comment ID in the tree of comments
  void deleteComment(std::vector<Comment*>& topComments, const std::string& id);                                // Delete a comment with the given comment ID from the tree of comments (recursive)
  void processOutput(std::ostream& stream, const std::string& displayOnly, Comment* comment, int indentCount);  // Process the output
};

#endif
