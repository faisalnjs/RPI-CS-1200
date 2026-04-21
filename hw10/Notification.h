#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <iostream>
#include <queue>
#include <string>

// Class for the notification
class Notification {
 public:
  int type = 0;                            // Notification type
  std::string appended = "";               // Text to append to the notification
  std::vector<std::string> users;  // Users doing the action
  std::string post;                        // Post associated with the notification
  Notification() = default;                // Create a notification
  Notification(const std::string& user);   // Create a notification from a user
};

// LikeNotification extends Notification
class LikeNotification : public Notification {
 public:
  LikeNotification(const std::string& user, const std::string& likedPost);  // Create a like notification from a user and a post
};

// TagNotification extends Notification
class TagNotification : public Notification {
 public:
  TagNotification(const std::string& user);  // Create a tag notification from a user
};

// CommentNotification extends Notification
class CommentNotification : public Notification {
 public:
  CommentNotification(const std::string& user, const std::string& likedPost);  // Create a comment notification from a user and a post
};

// FollowNotification extends Notification
class FollowNotification : public Notification {
 public:
  FollowNotification(const std::string& user);  // Create a follow notification from a user
};

// MessageRequestNotification extends Notification
class MessageRequestNotification : public Notification {
 public:
  MessageRequestNotification(const std::string& user);  // Create a message request notification from a user
};

#endif
