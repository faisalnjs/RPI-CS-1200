#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "Group.h"
#include "Video.h"

void importVideos(const std::string& VideosFileName, std::unordered_set<Video, VideoHash, VideoEqual>& Videos, std::unordered_map<std::string, Group>& groups, std::string groupType) {  // Import videos from the given file name into the given set of all videos and assign videos to groups based on their hashtags or sounds
  std::ifstream VideosFile(VideosFileName);                                                                                                                                              // READ videos file
  if (!VideosFile.is_open()) throw std::string("Failed to open the videos file.");                                                                                                       // Error if file cannot be opened

  std::string line;

  // Videos file -> videos list
  while (getline(VideosFile, line)) {                                               // For each line in the videos file...
    Video newVideo(line);                                                           // Create a video from the line
    if (groupType == "hashtag") {                                                   // If grouping by hashtag...
      for (const std::pair<const std::string, int>& hashtag : newVideo.hashtags) {  // For each hashtag in the video...
        for (int i = 0; i < hashtag.second; i++) {                                  // For the number of times the hashtag appears in the video...
          if (groups.find(hashtag.first) == groups.end()) {                         // If the group for the hashtag doesn't exist...
            Group newGroup(hashtag.first);                                          // Create a new group for the hashtag
            groups[hashtag.first] = newGroup;                                       // Add the new group to the groups map
          };
          groups[hashtag.first].videos.push(newVideo);         // Add the video to the group
          groups[hashtag.first].totalViews += newVideo.views;  // Add the views of the video to the total views of the group
        };
      };
    } else if (groupType == "sound") {                        // If grouping by sound...
      newVideo.originalMusic = newVideo.importMusic();        // Get the original music line from the videos file for the video
      std::string musicId = newVideo.importMusicId();         // Get the music ID for the video
      if (groups.find(musicId) == groups.end()) {             // If the group for the music ID doesn't exist...
        Group newGroup(musicId);                              // Create a new group for the music ID
        newGroup.musicName = newVideo.importMusicName();      // Get the music name for the video and set it for the group
        newGroup.musicAuthor = newVideo.importMusicAuthor();  // Get the music author for the video and set it for the group
        groups[musicId] = newGroup;                           // Add the new group to the groups map
      };
      groups[musicId].videos.push(newVideo);         // Add the video to the group
      groups[musicId].totalViews += newVideo.views;  // Add the views of the video to the total views of the group
    } else {
      throw std::string("Invalid group type. Must be 'hashtag' or 'sound'.");  // Error if group type is invalid
    };
    Videos.insert(newVideo);  // Add the new video to set
  }

  // Testing - check to see if everything was added to the set correctly
  std::cout << Videos.size() << " videos found." << std::endl;  // Debug - check the size of videos
  // for (const auto& video : Videos) {  // For each video in the set...
  //   std::cout << video.id << std::endl;     // Debug - print the id of the video
  //   std::cout << video.title << std::endl;  // Debug - print the title of the video
  //   std::cout << video.views << std::endl;  // Debug - print the views of the video
  //   std::cout << video.cover << std::endl;  // Debug - print the cover of the video
  //   std::cout << video.webVideo << std::endl;  // Debug - print the web video URL of the video
  //   std::cout << video.musicId << std::endl;  // Debug - print the music ID for the video
  //   std::cout << video.musicName << std::endl;  // Debug - print the music name for the video
  //   std::cout << video.musicAuthor << std::endl;  // Debug - print the music author for the video
  // }

  // Testing - check to see if groups were created correctly
  std::cout << groups.size() << " groups found." << std::endl;  // Debug - check the size of groups
  // for (const std::pair<const std::string, Group>& pair : groups) {  // For each group in the map...
  //   if (pair.second.videos.size() > 1) {
  //     std::cout << pair.first << std::endl;  // Debug - print the value of the group
  //     // std::cout << pair.second.musicName << std::endl;                                  // Debug - print the music name for the group
  //     std::cout << pair.second.totalViews << std::endl;                                 // Debug - print the total views for the group
  //     std::cout << pair.second.videos.size() << std::endl;                              // Debug - print the number of videos in the group
  //     std::priority_queue<Video> videosCopy = pair.second.videos;                       // Create a copy of the priority queue of videos for the group
  //     while (!videosCopy.empty()) {                                                     // While the copy is not empty...
  //       Video video = videosCopy.top();                                                 // Get the video with the most views in the copy
  //       std::cout << "  " << video.id << ": " << video.views << " views" << std::endl;  // Debug - print the id and views of the video
  //       videosCopy.pop();                                                               // Remove the video from the copy
  //     }
  //   }
  // }

  VideosFile.close();  // Done with videos file
}

void outputGroups(const std::string& outputFileName, std::unordered_map<std::string, Group>& groups, std::string groupType) {  // Output the groups to the given file name
  std::ofstream outputFile(outputFileName);                                                                                    // OPEN output file
  if (!outputFile.is_open()) throw std::string("Failed to open the output file.");                                             // Error if file cannot be opened

  if (groupType == "hashtag") {  // If grouping by hashtag...
    outputFile << "trending hashtags:" << std::endl;
  } else if (groupType == "sound") {  // If grouping by sound...
    outputFile << "trending sounds:" << std::endl;
  };
  outputFile << std::endl;

  std::priority_queue<Group> groupQueue;                                                        // Create a priority queue for the groups
  for (const std::pair<const std::string, Group>& pair : groups) groupQueue.push(pair.second);  // For each group, add the group to the priority queue

  int groupNumber = 0;                                 // Initialize groupNumber
  while (!groupQueue.empty() && (groupNumber < 20)) {  // While the priority queue is not empty...
    outputFile << "========================" << std::endl;
    Group group = groupQueue.top();                                           // Get the group with the highest ranking from the priority queue
    if (groupType == "hashtag") {                                             // If grouping by hashtag...
      outputFile << "#" << group.value << std::endl;                          // Output the hashtag of the group
      outputFile << "used " << group.videos.size() << " times" << std::endl;  // Output the video count for the group
    } else if (groupType == "sound") {                                        // If grouping by sound...
      outputFile << group.musicName << std::endl;                             // Output the music name of the group
    };
    outputFile << group.totalViews << " views" << std::endl;  // Output the total views of the group
    if (groupType == "sound") {
      outputFile << group.musicAuthor << std::endl;            // Output the music author of the group
      outputFile << "music id: " << group.value << std::endl;  // Output the music ID of the group
    };
    outputFile << std::endl;
    std::priority_queue<Video> videosCopy = group.videos;              // Create a copy of the priority queue of videos for the group
    int videoNumber = 0;                                               // Initialize videoNumber
    while (!videosCopy.empty() && (videoNumber < 3)) {                 // While the copy is not empty...
      Video video = videosCopy.top();                                  // Get the video with the most views in the copy
      outputFile << "cover url: " << video.cover << std::endl;         // Output the cover URL of the video
      outputFile << "web video url: " << video.webVideo << std::endl;  // Output the web video URL of the video
      videosCopy.pop();
      videoNumber++;
    };
    groupQueue.pop();
    groupNumber++;
    outputFile << "========================" << std::endl;
  };

  outputFile.close();  // Done with output file
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cout << "Usage: ./nytrends.out input.json output.txt hashtag|sound" << std::endl;  // Read inputs
    exit(1);
  }

  std::string inputFileName = std::string(argv[1]);   // Get the input file name
  std::string outputFileName = std::string(argv[2]);  // Get the output file name
  std::string groupType = std::string(argv[3]);       // Get the group type

  try {
    std::unordered_set<Video, VideoHash, VideoEqual> videos;  // Initialize videos
    std::unordered_map<std::string, Group> groups;            // Initialize groups
    importVideos(inputFileName, videos, groups, groupType);   // Import videos from the given file name into the given set of all videos and assign videos to groups based on their hashtags or sounds
    outputGroups(outputFileName, groups, groupType);          // Output the groups to the given file name
  } catch (const std::string& e) {
    std::cerr << "Error: " << e << std::endl;  // Catch any string exceptions and print the error message
    return 1;
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;  // Catch any exceptions and print the error message
    return 1;
  }

  return 0;
}