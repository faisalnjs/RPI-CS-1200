#include "Comment.h"

Comment::Comment(std::string& line) {           // Create a comment from a line in the comments file
  original = line;                              // Store the original line
  id = importId();                              // Get the ID of the comment
  author = importAuthor();                      // Get the author of the comment
  like_count = importLikeCount();               // Get the like count of the comment
  reply_count = importReplyCount();             // Get the reply count of the comment
  is_reply = importIsReply();                   // Get whether the comment is a reply
  parent_comment_id = importParentCommentId();  // Get the parent comment ID of the comment
  published_date = importPublishedDate();       // Get the published date of the comment
  crawled_date = importCrawledDate();           // Get the crawled date of the comment
  is_video_owner = importIsVideoOwner();        // Get whether the comment is made by the video owner
  comment = importComment();                    // Get the content of the comment
}

std::string Comment::importId() {                      // Get the ID of the comment
  int start = 0;                                       // Initialize the starting index
  int key_start = original.find("comment_id", start);  // Find "comment_id"
  int value_start = key_start + 14;                    // Calculate the starting index
  int value_end = original.find("\"", value_start);    // Find the ending index
  int len = value_end - value_start;                   // Calculate the length of the ID
  std::string id = original.substr(value_start, len);  // Get the ID of the comment
  return id;
}

std::string Comment::importAuthor() {                      // Get the author of the comment
  int start = 0;                                           // Initialize the starting index
  int key_start = original.find("author", start);          // Find "author"
  int value_start = key_start + 10;                        // Calculate the starting index
  int value_end = original.find("\"", value_start);        // Find the ending index
  int len = value_end - value_start;                       // Calculate the length of the author
  std::string author = original.substr(value_start, len);  // Get the author of the comment
  return author;
}

int Comment::importLikeCount() {                             // Get the like count of the comment
  int start = 0;                                             // Initialize the starting index
  int key_start = original.find("like_count", start);        // Find "like_count"
  int value_start = key_start + 13;                          // Calculate the starting index
  int value_end = original.find(",", value_start);           // Find the ending index
  int len = value_end - value_start;                         // Calculate the length of the like count
  int like_count = stoi(original.substr(value_start, len));  // Get the like count of the comment and convert it to an integer
  return like_count;
}

int Comment::importReplyCount() {                             // Get the reply count of the comment
  int start = 0;                                              // Initialize the starting index
  int key_start = original.find("reply_count", start);        // Find "reply_count"
  int value_start = key_start + 14;                           // Calculate the starting index
  int value_end = original.find(",", value_start);            // Find the ending index
  int len = value_end - value_start;                          // Calculate the length of the reply count
  int reply_count = stoi(original.substr(value_start, len));  // Get the reply count of the comment and convert it to an integer
  return reply_count;
}

bool Comment::importIsReply() {                                   // Get whether the comment is a reply
  int start = 0;                                                  // Initialize the starting index
  int key_start = original.find("is_reply", start);               // Find "is_reply"
  int value_start = key_start + 11;                               // Calculate the starting index
  int value_end = original.find(",", value_start);                // Find the ending index
  int len = value_end - value_start;                              // Calculate the length of the is_reply value
  bool is_reply = (original.substr(value_start, len) == "true");  // Get whether the comment is a reply and convert it to a boolean
  return is_reply;
}

std::string Comment::importParentCommentId() {                        // Get the parent comment ID of the comment
  int start = 0;                                                      // Initialize the starting index
  int key_start = original.find("parent_comment_id", start);          // Find "parent_comment_id"
  int value_start = key_start + 21;                                   // Calculate the starting index
  int value_end = original.find("\"", value_start);                   // Find the ending index
  int len = value_end - value_start;                                  // Calculate the length of the parent comment ID
  std::string parent_comment_id = original.substr(value_start, len);  // Get the parent comment ID of the comment
  return parent_comment_id;
}

std::string Comment::importPublishedDate() {                       // Get the published date of the comment
  int start = 0;                                                   // Initialize the starting index
  int key_start = original.find("published_date", start);          // Find "published_date"
  int value_start = key_start + 18;                                // Calculate the starting index
  int value_end = original.find("\"", value_start);                // Find the ending index
  int len = value_end - value_start;                               // Calculate the length of the published date
  std::string published_date = original.substr(value_start, len);  // Get the published date of the comment
  return published_date;
}

std::string Comment::importCrawledDate() {                       // Get the crawled date of the comment
  int start = 0;                                                 // Initialize the starting index
  int key_start = original.find("crawled_date", start);          // Find "crawled_date"
  int value_start = key_start + 16;                              // Calculate the starting index
  int value_end = original.find("\"", value_start);              // Find the ending index
  int len = value_end - value_start;                             // Calculate the length of the crawled date
  std::string crawled_date = original.substr(value_start, len);  // Get the crawled date of the comment
  return crawled_date;
}

bool Comment::importIsVideoOwner() {                                    // Get whether the comment is made by the video owner
  int start = 0;                                                        // Initialize the starting index
  int key_start = original.find("is_video_owner", start);               // Find "is_video_owner"
  int value_start = key_start + 18;                                     // Calculate the starting index
  int value_end = original.find(",", value_start);                      // Find the ending index
  int len = value_end - value_start;                                    // Calculate the length of the is_video_owner value
  bool is_video_owner = (original.substr(value_start, len) == "true");  // Get whether the comment is made by the video owner and convert it to a boolean
  return is_video_owner;
}

std::string Comment::importComment() {                      // Get the content of the comment
  int start = 0;                                            // Initialize the starting index
  int key_start = original.find("\"comment\"", start);      // Find "comment"
  int value_start = key_start + 12;                         // Calculate the starting index
  int value_end = original.find("\"", value_start);         // Find the ending index
  int len = value_end - value_start;                        // Calculate the length of the comment
  std::string comment = original.substr(value_start, len);  // Get the content of the comment
  return comment;
}