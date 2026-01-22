#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Playlist.h"
#include "PlaylistSong.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cout << "Usage: ./nyplaylists.out playlist.txt actions.txt output.txt" << std::endl;  // Read inputs
    exit(1);
  }

  // Starting playlist file
  std::string startingPlaylistFileName = std::string(argv[1]);
  std::ifstream startingPlaylistFile(startingPlaylistFileName);  // READ starting playlist file
  if (!startingPlaylistFile.is_open()) {
    std::cerr << "Failed to open the starting playlist file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  // Actions file
  std::string actionsFileName = std::string(argv[2]);
  std::ifstream actionsFile(actionsFileName);  // READ actions file
  if (!actionsFile.is_open()) {
    std::cerr << "Failed to open the actions file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  // Output file
  std::string outputFileName = std::string(argv[3]);
  std::ofstream outputFile(outputFileName);  // Ready the WRITE output file
  if (!outputFile.is_open()) {
    std::cerr << "Failed to open the output file." << std::endl;  // Error if file cannot be opened
    exit(1);
  }

  Playlist playlist(startingPlaylistFileName);  // Create playlist from starting playlist file

  startingPlaylistFile.close();  // Starting playlist no longer needed, close

  // Testing - check to see if everything was added to the vector correctly
  // for (const PlaylistSong& song : songs) {
  //   std::cout << song.name << std::endl;
  //   std::cout << song.artist << std::endl;
  //   std::cout << song.current << std::endl;
  // }

  std::string line;

  std::string action;
  std::string name;
  std::string artist;
  size_t moveSongTo;

  // Modify the playlist from the actions given
  while (getline(actionsFile, line)) {
    line = line.substr(0, line.length() - 1);                                             // Remove trailing new line (FOR WINDOWS)
    action = line.substr(0, line.find(" "));                                              // Get action
    if (line.find(" ") == std::string::npos) action = line;  // If there is no space, the entire line is the action
    if (action == "") continue;                                                           // If there is no action, skip the line
    if (action == "next") {                                                               // If wants to go to the next song
      PlaylistSong nowPlaying = playlist.next();                                          // Skip to the next song, and get the next song
      std::cout << "Skipped to next song, now playing " << nowPlaying.name << " by " << nowPlaying.artist << "." << std::endl;
      playlist.statusUpdate();
    } else if (action == "previous") {            // If wants to go the previous song
      PlaylistSong nowPlaying = playlist.prev();  // Go to the previous song, and get the previous song
      std::cout << "Going to previous song, now playing " << nowPlaying.name << " by " << nowPlaying.artist << "." << std::endl;
      playlist.statusUpdate();
    } else {
      name = line.substr(line.find(" \"") + 2);        // Get the song name + rest of string
      name = name.substr(0, name.find("\" "));         // Remove the rest of the string after the song name
      artist = line.substr(line.find("\" ") + 2);      // Get the artist(s) name(s)
      if (action == "move") {
        moveSongTo = std::stoi(artist.substr(artist.length() - 1));  // The last character in the artist is a number, the position to move the song to
        artist = artist.substr(0, artist.length() - 2);              // Remove moveSongTo and the space from the artist string
        if (!playlist.isInPlaylist(name, artist)) {                  // If the song does not exist, skip
          std::cout << name << " by " << artist << " does not exist in the playlist." << std::endl;
          continue;  // Skip if the song does not exist
        }
        std::cout << "Moving " << name << " by " << artist << " to position " << moveSongTo << "." << std::endl;
        playlist.move(name, artist, moveSongTo);  // Move the song to the new position
        playlist.statusUpdate();
      } else if (action == "remove") {
        if (!playlist.isInPlaylist(name, artist)) {  // If the song does not exist, skip
          std::cout << name << " by " << artist << " does not exist in the playlist." << std::endl;
          continue;  // Skip if the song does not exist
        }
        std::cout << "Removing " << name << " by " << artist << " from the playlist." << std::endl;
        playlist.remove(name, artist);  // Remove the song from the playlist
        playlist.statusUpdate();
      } else if (action == "add") {
        std::cout << "Adding " << name << " by " << artist << " to the playlist." << std::endl;
        playlist.add(name, artist);  // Add the new song to the end of the playlist
        playlist.statusUpdate();
      }
    }
  }

  actionsFile.close();  // Actions file no longer needed, close

  // Push all the songs to the output file
  for (const PlaylistSong& song : playlist.songs) {
    outputFile << "\"" << song.name << "\" " << song.artist;
    if (song.current) outputFile << " current";
    outputFile << std::endl;
  }

  outputFile.close();
  return 0;
}
