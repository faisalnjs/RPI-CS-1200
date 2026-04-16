#ifndef VIDEO_H
#define VIDEO_H

#include <iostream>
#include <string>
#include <unordered_map>

// Class for the video
class Video {
 public:
  std::string original;                                   // Original line from the videos file
  std::string originalMusic;                              // Original music line from the videos file
  std::string id;                                         // ID of the video
  std::string title;                                      // Title of the video
  int64_t views = 0;                                      // Number of views for the video
  std::string cover = "";                                 // Cover URL of the video
  std::string webVideo = "";                              // Web video URL of the video
  std::string musicId = "";                               // Music ID for the video
  std::string musicName = "";                             // Music name for the video
  std::string musicAuthor = "";                           // Music author for the video
  std::unordered_map<std::string, int> hashtags;          // Hashtags for the video
  Video() {};                                             // Create a video
  Video(std::string& line);                               // Create a video from a line in the videos file
  bool operator<(const Video& other) const;               // Overload the less than operator for the video
  std::string importId();                                 // Get the ID of the video
  std::string importTitle();                              // Get the title of the video
  int importViews();                                      // Get the number of views for the video
  std::string importCover();                              // Get the cover URL of the video
  std::string importWebVideo();                           // Get the web video URL of the video
  std::string importMusic();                              // Get the original music line from the videos file
  std::string importMusicId();                            // Get the music ID for the video
  std::string importMusicName();                          // Get the music name for the video
  std::string importMusicAuthor();                        // Get the music author for the video
  std::unordered_map<std::string, int> importHashtags();  // Get the hashtags for the video
};

struct VideoHash {                                    // Hash functor for video
  std::size_t operator()(const Video& Video) const {  // Hash functor for video
    return std::hash<std::string>()(Video.id);        // Hash based on the ID of the video
  }
};

struct VideoEqual {                                        // Equality functor for video
  bool operator()(const Video& a, const Video& b) const {  // Equality functor for video
    return a.id == b.id;                                   // Compare by ID
  }
};

#endif
