#include "Video.h"

#include <iostream>
#include <regex>
#include <string>

Video::Video(std::string& line) {     // Create a video from a line in the videos file
  original = line;                    // Store the original line
  id = importId();                    // Get the ID of the video
  title = importTitle();              // Get the title of the video
  views = importViews();              // Get the number of views for the video
  cover = importCover();              // Get the cover URL of the video
  webVideo = importWebVideo();        // Get the web video URL of the video
  originalMusic = importMusic();      // Get the original music line from the videos file
  musicId = importMusicId();          // Get the music ID for the video
  musicName = importMusicName();      // Get the music name for the video
  musicAuthor = importMusicAuthor();  // Get the music author for the video
  hashtags = importHashtags();        // Get the hashtags for the video
}

bool Video::operator<(const Video& other) const {  // Overload the less than operator for the video
  if (views == other.views) return id < other.id;  // If views are equal, compare by ID
  return views < other.views;                      // Compare by views
}

std::string Video::importId() {                        // Get the ID of the video
  int start = 0;                                       // Initialize the starting index
  int key_start = original.find("id", start);          // Find "id"
  int value_start = key_start + 5;                     // Calculate the starting index
  int value_end = original.find("\"", value_start);    // Find the ending index
  int len = value_end - value_start;                   // Calculate the length of the ID
  std::string id = original.substr(value_start, len);  // Get the ID of the video
  return id;
}

std::string Video::importTitle() {                        // Get the title of the video
  int start = 0;                                          // Initialize the starting index
  int key_start = original.find("text", start);           // Find "text"
  int value_start = key_start + 7;                        // Calculate the starting index
  int value_end = original.find("\"", value_start);       // Find the ending index
  int len = value_end - value_start;                      // Calculate the length of the title
  std::string title = original.substr(value_start, len);  // Get the title of the video
  return title;
}

int Video::importViews() {                              // Get the number of views for the video
  int start = 0;                                        // Initialize the starting index
  int key_start = original.find("playCount", start);    // Find "playCount"
  int value_start = key_start + 11;                     // Calculate the starting index
  int value_end = original.find(",", value_start);      // Find the ending index
  int len = value_end - value_start;                    // Calculate the length of the views
  int views = stoi(original.substr(value_start, len));  // Get the number of views for the video and convert it to an integer
  return views;
}

std::string Video::importCover() {                        // Get the cover URL of the video
  int start = 0;                                          // Initialize the starting index
  int key_start = original.find("coverUrl", start);       // Find "coverUrl"
  int value_start = key_start + 11;                       // Calculate the starting index
  int value_end = original.find("\"", value_start);       // Find the ending index
  int len = value_end - value_start;                      // Calculate the length of the cover URL
  std::string cover = original.substr(value_start, len);  // Get the cover URL of the video
  return cover;
}

std::string Video::importWebVideo() {                        // Get the web video URL of the video
  int start = 0;                                             // Initialize the starting index
  int key_start = original.find("webVideoUrl", start);       // Find "webVideoUrl"
  int value_start = key_start + 14;                          // Calculate the starting index
  int value_end = original.find("\"", value_start);          // Find the ending index
  int len = value_end - value_start;                         // Calculate the length of the web video URL
  std::string webVideo = original.substr(value_start, len);  // Get the web video URL of the video
  return webVideo;
}

std::string Video::importMusic() {                                // Get the original music line from the videos file
  int start = 0;                                                  // Initialize the starting index
  int key_start = original.find("musicMeta", start);              // Find "musicMeta"
  int value_start = key_start + 12;                               // Calculate the starting index
  int value_end = original.find("}", value_start) + 1;            // Find the ending index
  int len = value_end - value_start;                              // Calculate the length of the original music line
  std::string originalMusic = original.substr(value_start, len);  // Get the original music line from the videos file
  return originalMusic;
}

std::string Video::importMusicId() {                        // Get the music ID for the video
  int start = 0;                                            // Initialize the starting index
  int key_start = original.find("musicId", start);          // Find "musicId"
  int value_start = key_start + 10;                         // Calculate the starting index
  int value_end = original.find("\"", value_start);         // Find the ending index
  int len = value_end - value_start;                        // Calculate the length of the music ID
  std::string musicId = original.substr(value_start, len);  // Get the music ID for the video
  return musicId;
}

std::string Video::importMusicName() {                        // Get the music name for the video
  int start = 0;                                              // Initialize the starting index
  int key_start = original.find("musicName", start);          // Find "musicName"
  int value_start = key_start + 12;                           // Calculate the starting index
  int value_end = original.find("\"", value_start);           // Find the ending index
  int len = value_end - value_start;                          // Calculate the length of the music name
  std::string musicName = original.substr(value_start, len);  // Get the music name for the video
  return musicName;
}

std::string Video::importMusicAuthor() {                        // Get the music author for the video
  int start = 0;                                                // Initialize the starting index
  int key_start = original.find("musicAuthor", start);          // Find "musicAuthor"
  int value_start = key_start + 14;                             // Calculate the starting index
  int value_end = original.find("\"", value_start);             // Find the ending index
  int len = value_end - value_start;                            // Calculate the length of the music author
  std::string musicAuthor = original.substr(value_start, len);  // Get the music author for the video
  return musicAuthor;
}

std::unordered_map<std::string, int> Video::importHashtags() {                     // Get the hashtags for the video
  std::unordered_map<std::string, int> hashtags;                                   // Initialize the set of hashtags
  std::regex hashtagRegex("#([\\w\\u0080-\\uFFFF]+)");                             // Define a regular expression to match hashtags
  std::sregex_iterator hashtagIterator(title.begin(), title.end(), hashtagRegex);  // Create an iterator for matching
  std::sregex_iterator endIterator;                                                // Create an iterator for matching
  while (hashtagIterator != endIterator) {                                         // Iterate over the matches and extract the hashtags
    std::smatch match = *hashtagIterator;                                          // Iterate over the matches and extract the hashtags
    std::string hashtag = match.str(1);                                            // Extract the first capturing group
    if (hashtags.find(hashtag) == hashtags.end()) {                                // If the hashtag is not already in the set...
      hashtags[hashtag] = 1;                                                       // Add the hashtag to the set
    } else {                                                                       // If the hashtag is already in the set...
      hashtags[hashtag]++;                                                         // Increment its count
    };
    ++hashtagIterator;
  };
  return hashtags;
}