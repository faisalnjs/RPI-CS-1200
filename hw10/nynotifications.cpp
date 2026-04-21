#include <fstream>
#include <iostream>
#include <queue>

#include "Notification.h"

void importPosts(std::string postsFileName, const std::string& username, std::vector<std::string>& posts) {  // Import posts from the given file name
  std::ifstream postsFile(postsFileName);                                                                    // READ posts file
  if (!postsFile.is_open()) throw std::string("Failed to open the posts file.");                             // Error if file cannot be opened

  std::string line;

  // Posts file -> posts list
  while (getline(postsFile, line)) {                            // For each line in the posts file...
    int start = 0;                                              // Initialize the starting index
    int key_start = line.find("ownerUsername", start);          // Find "ownerUsername"
    int value_start = key_start + 16;                           // Calculate the starting index
    int value_end = line.find("\"", value_start);               // Find the ending index
    int len = value_end - value_start;                          // Calculate the length of ownerUsername
    std::string ownerUsername = line.substr(value_start, len);  // Get ownerUsername
    if (ownerUsername == username) {                            // If the line matches the target username...
      start = 0;                                                // Initialize the starting index
      key_start = line.find("id", start);                       // Find "id"
      value_start = key_start + 5;                              // Calculate the starting index
      value_end = line.find("\"", value_start);                 // Find the ending index
      len = value_end - value_start;                            // Calculate the length of id
      std::string postId = line.substr(value_start, len);       // Get id
      posts.push_back(postId);                                  // Add the postId to the posts list
    }
  }

  std::cout << "Posts imported: " << posts.size() << std::endl;  // Print the number of posts imported

  postsFile.close();  // Done with posts file
}

void importEvents(const std::string& eventsFileName, const std::string& username, std::priority_queue<Notification*>& notifications, const std::vector<std::string>& posts, bool& likes, bool& tags, bool& comments, bool& newFollowers, bool& messageRequests) {  // Import events from the given file name
  std::ifstream eventsFile(eventsFileName);                                                                                                                                                                                                                        // READ events file
  if (!eventsFile.is_open()) throw std::string("Failed to open the events file.");                                                                                                                                                                                 // Error if file cannot be opened

  std::string line;

  // Events file -> notifications priority queue
  while (getline(eventsFile, line)) {                      // For each line in the events file...
    size_t currentPosition = line.find(" ");               // Initialize currentPosition
    std::string user = line.substr(0, currentPosition);    // Get the user from the line
    if (user == username) continue;                        // User is the target; skip
    line.erase(0, currentPosition + 1);                    // Clean data
    currentPosition = line.find(" ");                      // Find the next space
    std::string action = line.substr(0, currentPosition);  // Get the action from the line
    line.erase(0, currentPosition + 1);                    // Clean data
    currentPosition = line.find(" ");                      // Find the next space
    std::string target = line.substr(0, currentPosition);  // Get the target from the line
    bool targetIsPost = false;                             // Initialize targetIsPost
    for (const std::string& post : posts) {                // For each post in the user's posts...
      if (post == target) {                                // If the target is a post in the target's posts...
        targetIsPost = true;                               // Set targetIsPost to true
        break;
      }
    }
    if ((target != username) && !targetIsPost) continue;                                     // Target is not the target and target is not in the target's posts; skip
    Notification* lastNotification = notifications.empty() ? nullptr : notifications.top();  // Get the last notification
    if ((action == "likes") && likes) {                                                      // If the action is a like and the user has the likes preference...
      if (lastNotification && (lastNotification->type == 1)) {                               // If the last notification is a like notification for the same post...
        lastNotification->users.insert(lastNotification->users.begin(), user);               // Add the user to the existing like notification
      } else {
        Notification* newNotification = new LikeNotification(user, target);  // Create a like notification
        notifications.push(newNotification);                                 // Add a like notification
      }
    } else if ((action == "tags") && tags) {                                    // If the action is a tag and the user has the tags preference...
      if (lastNotification && (lastNotification->type == 2)) {                  // If the last notification is a tag notification...
        lastNotification->users.insert(lastNotification->users.begin(), user);  // Add the user to the existing tag notification
      } else {
        Notification* newNotification = new TagNotification(user);  // Create a tag notification
        notifications.push(newNotification);                        // Add a tag notification
      }
    } else if ((action == "comments_on") && comments) {                         // If the action is a comment and the user has the comments preference...
      if (lastNotification && (lastNotification->type == 3)) {                  // If the last notification is a comment notification for the same post...
        lastNotification->users.insert(lastNotification->users.begin(), user);  // Add the user to the existing comment notification
      } else {
        Notification* newNotification = new CommentNotification(user, target);  // Create a comment notification
        notifications.push(newNotification);                                    // Add a comment notification
      }
    } else if ((action == "follows") && newFollowers) {                         // If the action is a follow and the user has the new followers preference...
      if (lastNotification && (lastNotification->type == 4)) {                  // If the last notification is a follow notification...
        lastNotification->users.insert(lastNotification->users.begin(), user);  // Add the user to the existing follow notification
      } else {
        Notification* newNotification = new FollowNotification(user);  // Create a follow notification
        notifications.push(newNotification);                           // Add a follow notification
      }
    } else if ((action == "messageRequests") && messageRequests) {              // If the action is a message request and the user has the message requests preference...
      if (lastNotification && (lastNotification->type == 5)) {                  // If the last notification is a message request notification...
        lastNotification->users.insert(lastNotification->users.begin(), user);  // Add the user to the existing message request notification
      } else {
        Notification* newNotification = new MessageRequestNotification(user);  // Create a message request notification
        notifications.push(newNotification);                                   // Add a message request notification
      }
    }
  }

  std::cout << "Notifications imported: " << notifications.size() << std::endl;  // Print the number of notifications imported

  eventsFile.close();  // Done with events file
}

void outputNotifications(const std::string& outputFileName, std::priority_queue<Notification*> notifications) {  // Output the notifications to the given file name
  std::ofstream outputFile(outputFileName);                                                                      // OPEN output file
  if (!outputFile.is_open()) throw std::string("Failed to open the output file.");                               // Error if file cannot be opened

  int notificationNumber = 0;                                                                                                                                   // Initialize notificationNumber
  while (!notifications.empty()) {                                                                                                                              // While the priority queue is not empty...
    Notification* notification = notifications.top();                                                                                                           // Get the earliest notification
    if (notificationNumber < 100) {                                                                                                                             // If the limit has not been reached...
      if (notification->users.size() > 3) {                                                                                                                     // If notification aggregation is needed...
        std::string lastUser = notification->users[0];                                                                                                          // Get the last user in the notification
        std::string secondToLastUser = notification->users[1];                                                                                                  // Get the second to last user in the notification
        outputFile << lastUser << ", " << secondToLastUser << " and " << (notification->users.size() - 2) << " others" << notification->appended << std::endl;  // Output the aggregated notification
        notificationNumber++;
      } else {                                                                               // If there are 3 or fewer users in the notification...
        while (!notification->users.empty() && (notificationNumber < 100)) {                 // While there are still users in the notification and the limit has not been reached...
          outputFile << notification->users.front() << notification->appended << std::endl;  // Output the notification for the user
          notification->users.erase(notification->users.begin());                            // Remove the user from the notification
          notificationNumber++;
        }
      }
    }
    delete notification;  // Clean up pointers
    notifications.pop();
  };

  outputFile.close();  // Done with output file
}

void importUser(const std::string& usersFileName, const std::string& username, bool& pauseAll, bool& likes, bool& tags, bool& comments, bool& newFollowers, bool& messageRequests) {  // Import the user's notification preferences from the given file name
  std::ifstream usersFile(usersFileName);                                                                                                                                             // READ users file
  if (!usersFile.is_open()) throw std::string("Failed to open the users file.");                                                                                                      // Error if file cannot be opened

  std::string line;
  bool userFound = false;  // Initialize userFound

  // Users file -> user preferences
  while (getline(usersFile, line)) {                                                  // For each line in the users file...
    std::string lineUsername = line.substr(line.find("\"username\": \"") + 13);       // Get the substring starting from the username field
    lineUsername = lineUsername.substr(0, lineUsername.find("\""));                   // Get the username from the substring
    if (lineUsername == username) {                                                   // If the line matches the target username...
      userFound = true;                                                               // Set userFound to true
      std::string preferences = line.substr(line.find("\"notifications\": [") + 18);  // Get the preferences substring
      preferences = preferences.substr(0, preferences.find("]}"));                    // Get the preferences from the substring
      int start = 0;                                                                  // Initialize the starting index
      int key_start = preferences.find("pauseAll", start);                            // Find "pauseAll"
      int value_start = key_start + 12;                                               // Calculate the starting index
      int value_end = preferences.find("\"", value_start);                            // Find the ending index
      int len = value_end - value_start;                                              // Calculate the length of pauseAll
      pauseAll = preferences.substr(value_start, len) == "true";                      // Get the pauseAll preference
      start = value_end;                                                              // Update the starting index
      key_start = preferences.find("likes", start);                                   // Find "likes"
      value_start = key_start + 9;                                                    // Calculate the starting index
      value_end = preferences.find("\"", value_start);                                // Find the ending index
      len = value_end - value_start;                                                  // Calculate the length of likes
      likes = preferences.substr(value_start, len) == "true";                         // Get the likes preference
      start = value_end;                                                              // Update the starting index
      key_start = preferences.find("tags", start);                                    // Find "tags"
      value_start = key_start + 8;                                                    // Calculate the starting index
      value_end = preferences.find("\"", value_start);                                // Find the ending index
      len = value_end - value_start;                                                  // Calculate the length of tags
      tags = preferences.substr(value_start, len) == "true";                          // Get the tags preference
      start = value_end;                                                              // Update the starting index
      key_start = preferences.find("comments", start);                                // Find "comments"
      value_start = key_start + 12;                                                   // Calculate the starting index
      value_end = preferences.find("\"", value_start);                                // Find the ending index
      len = value_end - value_start;                                                  // Calculate the length of comments
      comments = preferences.substr(value_start, len) == "true";                      // Get the comments preference
      start = value_end;                                                              // Update the starting index
      key_start = preferences.find("newFollowers", start);                            // Find "newFollowers"
      value_start = key_start + 16;                                                   // Calculate the starting index
      value_end = preferences.find("\"", value_start);                                // Find the ending index
      len = value_end - value_start;                                                  // Calculate the length of newFollowers
      newFollowers = preferences.substr(value_start, len) == "true";                  // Get the newFollowers preference
      start = value_end;                                                              // Update the starting index
      key_start = preferences.find("messageRequests", start);                         // Find "messageRequests"
      value_start = key_start + 19;                                                   // Calculate the starting index
      value_end = preferences.find("\"", value_start);                                // Find the ending index
      len = value_end - value_start;                                                  // Calculate the length of messageRequests
      messageRequests = preferences.substr(value_start, len) == "true";               // Get the messageRequests preference
      break;
    }
  }
  if (!userFound) throw std::string("User not found in users file.");  // Error if user is not found in users file

  usersFile.close();  // Done with users file
}

int main(int argc, char* argv[]) {
  if (argc != 6) {
    std::cout << "Usage: ./nynotifications.out posts.json users.json events.txt output.txt username" << std::endl;  // Read inputs
    exit(1);
  }

  std::string postsFileName = std::string(argv[1]);   // Get the posts file name
  std::string usersFileName = std::string(argv[2]);   // Get the users file name
  std::string eventsFileName = std::string(argv[3]);  // Get the events file name
  std::string outputFileName = std::string(argv[4]);  // Get the output file name
  std::string username = std::string(argv[5]);        // Get the target username

  try {
    std::vector<std::string> posts;                                                                       // Create a vector for all posts
    bool pauseAll = false;                                                                                // Initialize pauseAll
    bool likes = false;                                                                                   // Initialize likes
    bool tags = true;                                                                                     // Initialize tags
    bool comments = true;                                                                                 // Initialize comments
    bool newFollowers = true;                                                                             // Initialize newFollowers
    bool messageRequests = true;                                                                          // Initialize messageRequests
    std::priority_queue<Notification*> notifications;                                                     // Create a priority queue for the notifications
    importUser(usersFileName, username, pauseAll, likes, tags, comments, newFollowers, messageRequests);  // Import the user's notification preferences from the given file name
    if (pauseAll) {
      outputNotifications(outputFileName, notifications);  // Notifications are paused; output nothing
      return 0;
    }
    importPosts(postsFileName, username, posts);                                                                         // Import posts from the given file name
    importEvents(eventsFileName, username, notifications, posts, likes, tags, comments, newFollowers, messageRequests);  // Import events from the given file name
    outputNotifications(outputFileName, notifications);                                                                  // Output the notifications to the given file name
  } catch (const std::string& e) {
    std::cerr << "Error: " << e << std::endl;  // Catch any string exceptions and print the error message
    return 1;
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;  // Catch any exceptions and print the error message
    return 1;
  }

  return 0;
}