#include "Notification.h"

Notification::Notification(const std::string& user) {  // Create a notification from a user
  users.insert(users.begin(), user);                   // Add the user to the queue
}

LikeNotification::LikeNotification(const std::string& user, const std::string& likedPost) {  // Create a like notification from a user and a post
  type = 1;                                                                                  // Notification type for like
  appended = " liked your post.";                                                            // Text to append to the like notification
  users.insert(users.begin(), user);                                                         // Add the user to the queue
  post = likedPost;                                                                          // Set the associated post
}

TagNotification::TagNotification(const std::string& user) {  // Create a tag notification from a user
  type = 2;                                                  // Notification type for tag
  appended = " tagged you in a post.";                       // Text to append to the tag notification
  users.insert(users.begin(), user);                         // Add the user to the queue
}

CommentNotification::CommentNotification(const std::string& user, const std::string& likedPost) {  // Create a comment notification from a user and a post
  type = 3;                                                                                        // Notification type for comment
  appended = " commented on your post.";                                                           // Text to append to the comment notification
  users.insert(users.begin(), user);                                                               // Add the user to the queue
  post = likedPost;                                                                                // Set the associated post
}

FollowNotification::FollowNotification(const std::string& user) {  // Create a follow notification from a user
  type = 4;                                                        // Notification type for follow
  appended = " started following you.";                            // Text to append to the follow notification
  users.insert(users.begin(), user);                               // Add the user to the queue
}

MessageRequestNotification::MessageRequestNotification(const std::string& user) {  // Create a message request notification from a user
  type = 5;                                                                        // Notification type for message request
  appended = " wants to send you a message.";                                      // Text to append to the message request notification
  users.insert(users.begin(), user);                                               // Add the user to the queue
}