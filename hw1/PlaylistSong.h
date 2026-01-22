#ifndef SONG_H
#define SONG_H
#include <string>

struct PlaylistSong {
  std::string name;
  std::string artist;
  bool current;
};

#endif