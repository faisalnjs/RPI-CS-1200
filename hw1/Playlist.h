#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <string>
#include <vector>

#include "PlaylistSong.h"

// Class for the playlist
class Playlist {
 public:
  std::vector<PlaylistSong> songs = {};                    // Establish empty vector for the songs
  Playlist(const std::string& startingPlaylistFileName) {  // Create a playlist from a starting playlist file
    // Starting playlist file
    std::ifstream startingPlaylistFile(startingPlaylistFileName);  // READ starting playlist file
    if (!startingPlaylistFile.is_open()) {
      std::cerr << "Failed to open the starting playlist file." << std::endl;  // Error if file cannot be opened
      exit(1);
    }

    std::string line;

    std::string name;
    std::string artist;
    bool current;  // Bool used for not/current playing song

    // Import starting playlist
    while (getline(startingPlaylistFile, line)) {
      line = line.substr(0, line.length() - 1);             // Remove trailing new line (FOR WINDOWS)
      name = line.substr(1, line.find("\" ") - 1);           // Get song name
      artist = line.substr(line.find("\" ") + 2);            // Get artist(s) name(s)
      current = false;                                       // Fallback to not currently playing
      if (line.find("current") != std::string::npos) {       // If the song is currently playing
        artist = artist.substr(0, artist.find(" current"));  // Fix the artist(s) name(s)
        current = true;                                      // Set song to currently playing
      }
      artist = artist.substr(0, artist.length());                           // Remove trailing new line
      std::cout << "Adding \"" << name << "\" by " << artist << std::endl;  // Debug output
      songs.push_back({name, artist, current});                             // Add the song to the internal vector
    }
    startingPlaylistFile.close();
  }

  bool isInPlaylist(const std::string& name, const std::string& artist) {
    for (const PlaylistSong& song : songs) {
      if ((song.name == name) && (song.artist == artist)) {
        return true;
      }
    }
    // for (const PlaylistSong& song : songs) {
    //   std::cout << "Debug: Playlist contains - " << song.name << " by " << song.artist << std::endl;
    // }
    // std::cout << "Debug: Song not found - " << name << " by " << artist << std::endl;
    return false;
  }

  void statusUpdate() {
    std::cout << "Playlist now has " << songs.size() << " songs." << std::endl;
  }

  void add(const std::string& name, const std::string& artist) {
    songs.push_back({name, artist, false});  // Add the new song to the end of the playlist
  }

  void remove(const std::string& name, const std::string& artist) {
    std::vector<PlaylistSong> newSongs = {};  // Establish empty vector for the new songs
    bool songRemoved = false;
    for (const PlaylistSong& song : songs) {                                  // Loop through all current songs in the playlist
      if (songRemoved || ((song.name != name) || (song.artist != artist))) {  // If this is not the song to be removed or already removed
        newSongs.push_back(song);                                             // Add the song to the new songs vector
      } else {
        songRemoved = true;
      }
    }
    songs = newSongs;  // Update the songs vector
  }

  void move(const std::string& name, const std::string& artist, size_t to) {
    if (to > songs.size()) to = songs.size();  // Adjust to end if greater than size
    bool isPlaying = false;
    size_t songIndex = songs.size();                                 // Default index to inform if song was found
    for (size_t i = 0; i < songs.size(); ++i) {                      // Loop through all current songs in the playlist
      if ((songs[i].name == name) && (songs[i].artist == artist)) {  // Find song to move
        isPlaying = songs[i].current;                                // Get whether the song is currently playing
        songIndex = i;                                               // Store the index of the song to be moved
        break;
      }
    }
    if (songIndex < songs.size()) {
      std::vector<PlaylistSong> newSongs;                                // Establish empty vector for new songs
      for (size_t i = 0; i < songs.size(); ++i) {                        // Loop through all current songs in the playlist
        if (i == to - 1) newSongs.push_back({name, artist, isPlaying});  // Insert moved song at the new position
        if (i != songIndex) newSongs.push_back(songs[i]);                // Add all other songs, skipping the moved one
      }
      songs = newSongs;  // Update the original playlist
    }
  }

  PlaylistSong next() {
    PlaylistSong nowPlaying;
    for (size_t i = 0; i < songs.size(); i++) {  // Loop through songs
      if (songs[i].current) {                    // Find currently playing song
        songs[i].current = false;                // Set the song to not currently playing
        if (i == songs.size() - 1) {             // If at the end of the playlist
          songs[0].current = true;               // Set the first song to currently playing
          nowPlaying = songs[0];
        } else {
          songs[i + 1].current = true;  // Set the next song to currently playing
          nowPlaying = songs[i + 1];
        }
        break;
      }
    }
    return nowPlaying;
  }

  PlaylistSong prev() {
    PlaylistSong nowPlaying;
    for (size_t i = 0; i < songs.size(); i++) {    // Loop through songs
      if (songs[i].current) {                      // Find currently playing song
        songs[i].current = false;                  // Set the song to not currently playing
        if (i == 0) {                              // If at the start of the playlist
          songs[songs.size() - 1].current = true;  // Set the last song to currently playing
          nowPlaying = songs[songs.size() - 1];
        } else {
          songs[i - 1].current = true;  // Set the previous song to currently playing
          nowPlaying = songs[i - 1];
        }
        break;
      }
    }
    return nowPlaying;
  }
};

#endif