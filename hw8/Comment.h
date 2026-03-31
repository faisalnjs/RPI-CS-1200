#ifndef COMMENT_H
#define COMMENT_H

#include <iostream>
#include <vector>

// Class for the comment
class Comment {
 public:
  std::string original;                          // Original line from the comments file
  std::string id;                                // ID of the comment
  std::string author;                            // Author of the comment
  int like_count = 0;                            // Like count of the comment
  int reply_count = 0;                           // Reply count of the comment
  bool is_reply = false;                         // Whether the comment is a reply
  std::string parent_comment_id;                 // Parent comment ID of the comment
  std::string published_date = "0 seconds ago";  // Published date of the comment
  std::string crawled_date;                      // Crawled date of the comment
  bool is_video_owner = false;                   // Whether the comment is made by the video owner
  std::string comment;                           // Content of the comment
  std::vector<Comment*> children;                // Children of the comment
  Comment() {};                                  // Create a comment
  Comment(std::string& line);                    // Create a comment from a line in the comments file
  std::string importId();                        // Get the ID of the comment
  std::string importAuthor();                    // Get the author of the comment
  int importLikeCount();                         // Get the like count of the comment
  int importReplyCount();                        // Get the reply count of the comment
  bool importIsReply();                          // Get whether the comment is a reply
  std::string importParentCommentId();           // Get the parent comment ID of the comment
  std::string importPublishedDate();             // Get the published date of the comment
  std::string importCrawledDate();               // Get the crawled date of the comment
  bool importIsVideoOwner();                     // Get whether the comment is made by the video owner
  std::string importComment();                   // Get the content of the comment
};

#endif
