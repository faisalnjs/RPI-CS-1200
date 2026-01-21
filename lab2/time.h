#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <string>

// Class for the time object
class Time {
 private:
  int hour;
  int minute;
  int second;

 public:
  Time();
  Time(const int& hour, const int& minute, const int& second);
  int getHour() const;
  int getMinute() const;
  int getSecond() const;
  void setHour(int setHour);
  void setMinute(int setMinute);
  void setSecond(int setSecond);
  void PrintAMPM() const;
};

#endif