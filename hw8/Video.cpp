#include "Video.h"

#include <fstream>
#include <iostream>
#include <string>

#include "Comment.h"

Video::Video(const std::string& commentsFileName, std::vector<Comment>& comments) {  // Create a video with the given comments file name and comments list
  std::ifstream commentsFile(commentsFileName);                                      // READ comments file
  if (!commentsFile.is_open()) {
    std::cerr << "Failed to open the businesses file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  std::string line;

  // Comments file -> comments list
  while (getline(commentsFile, line)) {  // For each line in the comments file...
    Comment newComment(line);            // Create a comment from the line
    comments.push_back(newComment);      // Add the new comment to list
  }

  // Testing - check to see if everything was added to the list correctly
  //   for (Comment& comment : comments) {
  //     std::cout << "Debug: Comment - " << comment.importId() << " ... " << comment.importAuthor() << " ... " << comment.importLikeCount() << " ... " << comment.importReplyCount() << " ... " << comment.importIsReply() << " ... " << comment.importParentCommentId() << " ... " << comment.importPublishedDate() << " ... " << comment.importCrawledDate() << " ... " << comment.importIsVideoOwner() << " ... " << comment.importComment() << std::endl;
  //   }

  commentsFile.close();  // Done with comments file
}

Video::~Video() {                                       // Destructor for the video
  for (Comment* comment : newComments) delete comment;  // Delete each comment in newComments
  newComments.clear();                                  // Clear the list of new comments
}

void Video::makeTree(std::vector<Comment>& commentsVector) {  // Make the tree of comments
  for (Comment& comment : commentsVector) {                   // For each comment in the comments
    if (comment.is_reply) {                                   // If the comment is a reply...
      for (Comment& parentComment : commentsVector) {         // For each comment in the comments...
        if (parentComment.id == comment.parent_comment_id) {  // If the comment's parent comment ID matches the parent comment's ID...
          parentComment.children.push_back(&comment);         // Add the comment to the children of the parent comment
        }
      }
    } else {                         // If the comment is not a reply...
      comments.push_back(&comment);  // Add the comment to the list of comments for the video
    }
  }
}

Comment* findInTree(Comment* comment, const std::string& id) {  // Find a comment with the given comment ID in the subtree of a comment (recursive)
  if (!comment) return nullptr;                                 // No comment
  if (comment->id == id) return comment;                        // If the current comment's ID matches the given comment ID, return the comment
  for (Comment* child : comment->children) {                    // For each child of the current comment...
    Comment* found = findInTree(child, id);                     // Search the subtree of the child comment for the comment with the given ID (recursive)
    if (found) return found;                                    // Return the comment
  }
  return nullptr;
}

Comment* Video::findComment(const std::string& id) {  // Find a comment with the given comment ID in the tree of comments
  for (Comment* top : comments) {                     // For each top-level comment...
    Comment* found = findInTree(top, id);             // Search the subtree of the top-level comment for the comment with the given ID
    if (found) return found;                          // Return the comment
  }
  return nullptr;
}

void deleteCommentSubtree(Comment* comment) {                            // Delete a comment and children (recursive)
  if (!comment) return;                                                  // No comment
  std::cout << "Debug: Delete - " << comment->id << std::endl;           // Debug - check which comment is being cleaned up
  for (Comment* child : comment->children) deleteCommentSubtree(child);  // Continue recursive function for children
}

void getTreeCommentIds(Comment* comment, std::vector<std::string>& treeCommentIds) {  // Get the IDs of a comment and children (recursive)
  if (!comment) return;                                                               // No comment
  treeCommentIds.push_back(comment->id);                                              // Add the ID of the comment to the list of IDs
  for (Comment* child : comment->children) getTreeCommentIds(child, treeCommentIds);  // Continue recursive function for children
}

void outputSubtree(std::ostream& stream, Comment* comment, int indentCount) {     // Output a comment and children (recursive)
  if (!comment) return;                                                           // No comment
  std::string indent(indentCount * 4, ' ');                                       // Calculate indent
  stream << indent << comment->author << " " << comment->published_date << '\n';  // Output the author and published date of the comment
  stream << indent << comment->comment << '\n';                                   // Output the content of the comment
  stream << indent << "\U0001F44D " << comment->like_count << '\n';               // Output the like count of the comment
  if (!comment->children.empty()) {                                               // If the comment has children...
    if (comment->reply_count == 1) {                                              // If the comment has one child...
      stream << indent << "1 reply" << '\n';                                      // Output "1 reply"
    } else {                                                                      // If the comment has more than one child...
      stream << indent << comment->reply_count << " replies" << '\n';             // Output the number of replies
    }
  }
  for (Comment* child : comment->children) outputSubtree(stream, child, indentCount + 1);  // Output the subtree of each child comment (recursive)
}

void Video::deleteComment(std::vector<Comment*>& topComments, const std::string& id) {                                    // Delete a comment with the given comment ID from the tree of comments (recursive)
  for (std::size_t commentPosition = 0; commentPosition < topComments.size(); ++commentPosition) {                        // For each top-level comment...
    Comment* comment = topComments[commentPosition];                                                                      // Get the current comment
    if (comment->id == id) {                                                                                              // If the current comment's ID matches the given comment ID...
      topComments.erase(topComments.begin() + commentPosition);                                                           // Remove the comment from the list of top-level comments
      deleteCommentSubtree(comment);                                                                                      // Cleanup subtree (no direct delete)
      std::vector<std::string> treeCommentIds;                                                                            // Initialize treeCommentIds
      getTreeCommentIds(comment, treeCommentIds);                                                                         // Get the IDs of the comment and children
      for (std::vector<Comment*>::iterator currentComment = newComments.begin(); currentComment != newComments.end();) {  // For each comment in the list of new comments...
        bool inChild = false;                                                                                             // Initialize inChild to false
        for (const std::string& commentId : treeCommentIds) {                                                             // For each ID in the list of IDs of the comment and children...
          if (commentId == (*currentComment)->id) {                                                                       // If the comment's ID matches the ID of the comment or a child comment...
            inChild = true;                                                                                               // Set inChild to true
            break;
          }
        }
        if (inChild) {                                         // If the comment is in the subtree of the deleted comment...
          delete *currentComment;                              // Delete the comment
          currentComment = newComments.erase(currentComment);  // Remove the comment from the list of new comments
        } else {
          ++currentComment;  // Move to the next comment in the list of new comments
        }
      }
    } else {
      deleteComment(comment->children, id);  // Traverse the tree to find the comment (recursive)
    }
  }
}

void Video::processActions(const std::string& actionsFileName, const std::string& outputFileName) {  // Process the actions
  std::ifstream actionsFile(actionsFileName);                                                        // READ actions file
  if (!actionsFile.is_open()) {
    std::cerr << "Failed to open the actions file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  std::ofstream outputFile(outputFileName);  // Ready the WRITE output file
  if (!outputFile.is_open()) {
    std::cerr << "Failed to open the output file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  std::string line;

  while (getline(actionsFile, line)) {                       // For each line in the actions file...
    std::string action = line.substr(0, line.find(" "));     // Get the action
    std::cout << "Debug: Action - " << action << std::endl;  // Debug - check action
    size_t firstSpace = line.find(" ");
    if (firstSpace != std::string::npos) line.erase(0, firstSpace + 1);
    if (action == "reply_to_video") {                                       // If the action is to reply to the video...
      Comment* newComment = new Comment();                                  // Initialize newComment
      newComments.push_back(newComment);                                    // Add the comment to newComments
      size_t currentPosition = line.find(" ");                              // Initialize currentPosition
      newComment->id = line.substr(0, currentPosition);                     // Set the ID of the new comment
      line.erase(0, currentPosition + 1);                                   // Clean data
      currentPosition = line.find(" ");                                     // Find the next space
      newComment->author = line.substr(0, currentPosition);                 // Set the author of the new comment
      line.erase(0, currentPosition + 1);                                   // Clean data
      int key_start = line.find('"');                                       // Find '"'
      int value_start = key_start + 1;                                      // Calculate the starting index
      int value_end = line.find('"', value_start);                          // Find the ending index
      int len = value_end - value_start;                                    // Calculate the length of the comment
      newComment->comment = line.substr(value_start, len);                  // Get the content of the comment
      comments.push_back(newComment);                                       // Add the new comment to the list of comments for the video
    } else if (action == "reply_to_comment") {                              // If the action is to reply to a comment...
      Comment* newComment = new Comment();                                  // Initialize newComment
      newComments.push_back(newComment);                                    // Add the comment to newComments
      size_t currentPosition = line.find(" ");                              // Initialize currentPosition
      newComment->parent_comment_id = line.substr(0, currentPosition);      // Set the parent comment ID of the new comment
      line.erase(0, currentPosition + 1);                                   // Clean data
      currentPosition = line.find(" ");                                     // Find the next space
      newComment->id = line.substr(0, currentPosition);                     // Set the ID of the new comment
      line.erase(0, currentPosition + 1);                                   // Clean data
      currentPosition = line.find(" ");                                     // Find the next space
      newComment->author = line.substr(0, currentPosition);                 // Set the author of the new comment
      line.erase(0, currentPosition + 1);                                   // Clean data
      int key_start = line.find('"');                                       // Find '"'
      int value_start = key_start + 1;                                      // Calculate the starting index
      int value_end = line.find('"', value_start);                          // Find the ending index
      int len = value_end - value_start;                                    // Calculate the length of the comment
      newComment->comment = line.substr(value_start, len);                  // Get the content of the comment
      Comment* parentComment = findComment(newComment->parent_comment_id);  // Find parent comment
      if (parentComment) {                                                  // Parent comment found
        newComment->is_reply = true;                                        // Set is_reply to true
        parentComment->children.push_back(newComment);                      // Add the new comment to the children of the parent comment
        parentComment->reply_count++;                                       // Increment parent comment reply_count
      } else {                                                              // Parent comment not found
        newComment->is_reply = false;                                       // Set is_reply to false
        comments.push_back(newComment);                                     // Add the new comment to the list of comments for the video as a top-level comment
      }
    } else if (action == "like_comment") {                                                    // If the action is to like a comment...
      Comment* comment = findComment(line);                                                   // Find the comment
      if (comment) comment->like_count++;                                                     // Increment comment like_count
    } else if (action == "delete_comment") {                                                  // If the action is to delete a comment...
      deleteComment(comments, line);                                                          // Delete the comment with the given comment ID from the tree of comments
    } else if (action == "display_comment") {                                                 // If the action is to display a comment...
      Comment* comment = findComment(line);                                                   // Find the comment
      if (comment) {                                                                          // If the comment is found...
        outputSubtree(outputFile, comment, 0);                                                // Output the subtree of the comment
      } else {                                                                                // If the comment is not found...
        for (Comment* topComment : comments) processOutput(outputFile, line, topComment, 0);  // Process the output for each top-level comment
      }
    }
  }

  actionsFile.close();  // Done with actions file
  outputFile.close();   // Done with output file
}

void Video::processOutput(std::ostream& stream, const std::string& displayOnly, Comment* comment, int indentCount = 0) {  // Process the output
  if (!comment) return;                                                                                                   // No comment
  //   if (indentCount == 0) std::cout << "Debug: Top-level comment - " << comment->id << std::endl;  // Debug - check top-level comment
  size_t commentStartsWith = comment->id.find(displayOnly);                       // Check if the comment's ID starts with the displayOnly string
  if (commentStartsWith == std::string::npos) return;                             // If the comment's ID does not start with the displayOnly string, skip the comment
  std::cout << "Debug: Output - " << comment->id << std::endl;                    // Debug - check which comment is being outputted
  std::string indent(indentCount * 4, ' ');                                       // Calculate indent
  stream << indent << comment->author << " " << comment->published_date << '\n';  // Output author and published date
  stream << indent << comment->comment << '\n';                                   // Output comment content
  stream << indent << "\U0001F44D " << comment->like_count << '\n';               // Output like count
  if (!comment->children.empty()) {                                               // If there are replies to the comment...
    if (comment->children.size() == 1) {                                          // If there is exactly one reply...
      stream << indent << "1 reply" << '\n';                                      // Output "1 reply"
    } else {                                                                      // If there are more than 1 replies...
      stream << indent << comment->children.size() << " replies" << '\n';         // Output reply count
    }
  }
  for (Comment* child : comment->children) processOutput(stream, displayOnly, child, indentCount + 1);  // Process the output for the children of the comment (recursive)
}